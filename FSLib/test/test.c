// Standard C includes
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <process.h>
#include <string.h>
// Then the needed OS/2 API stuffs
#define INCL_TYPES
#define INCL_WIN
#define INCL_DOS
#define INCL_DOSERRORS
#define INCL_GPI
#include <os2.h>
// The main FSLib include file
#include "FSLib.h"


#define FULLSCREENWIDTH  1024
#define FULLSCREENHEIGHT 768

#define PI 3.1415

int iPMThreadState;
FSLib_VideoMode SrcBufferDesc;
char *pchSrcBuffer;
HWND hClient, hFrame;
int  iImageState = 0;

#ifdef DEBUG_BUILD
void MorphToPM()
{
  PPIB pib;
  PTIB tib;

  DosGetInfoBlocks(&tib, &pib);

  // Change flag from VIO to PM:
  if (pib->pib_ultype==2) pib->pib_ultype = 3;
}
#endif



MRESULT EXPENTRY WndProc(HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  switch (msg)
  {
    case WM_CHAR:  // Keypress notification
      if (SHORT1FROMMP(mp1) & KC_KEYUP)
      {
	printf("HWScanKeyMap[0x%0x] = SDLK_;\n", CHAR4FROMMP(mp1)); // HW scan code
      }

      if (SHORT1FROMMP (mp2) == 'f')
	FSLib_ToggleFSMode(hwnd, !FSLib_QueryFSMode(hwnd));

      if (SHORT1FROMMP (mp2) == 'q')
	WinPostMsg(hwnd, WM_CLOSE, 0, 0);
      break;
    case WM_PAINT:
      {
	HPS hps;
	RECTL rcl;
        int iTop, iLeft, iWidth, iHeight;
        int iXScaleError, iYScaleError;
        int iXScaleError2, iYScaleError2;
        SWP swp;

        hps = WinBeginPaint(hwnd,0,&rcl);

	// Re-blit the modified area!
        // For this, we have to calculate the points, scaled!
        WinQueryWindowPos(hwnd, &swp);

        iXScaleError = (SrcBufferDesc.uiXResolution-1) / swp.cx;
        iYScaleError = (SrcBufferDesc.uiYResolution-1) / swp.cy;
        if (iXScaleError<0) iXScaleError = 0;
        if (iYScaleError<0) iYScaleError = 0;
        iXScaleError2 = (swp.cx-1)/(SrcBufferDesc.uiXResolution);
        iYScaleError2 = (swp.cy-1)/(SrcBufferDesc.uiYResolution);
        if (iXScaleError2<0) iXScaleError2 = 0;
        if (iYScaleError2<0) iYScaleError2 = 0;

        iTop = (swp.cy - rcl.yTop) * SrcBufferDesc.uiYResolution / swp.cy - iYScaleError;
	iLeft = rcl.xLeft * SrcBufferDesc.uiXResolution / swp.cx - iXScaleError;
        iWidth = ((rcl.xRight-rcl.xLeft) * SrcBufferDesc.uiXResolution + swp.cx-1)
          / swp.cx + 2*iXScaleError;
        iHeight = ((rcl.yTop-rcl.yBottom) * SrcBufferDesc.uiYResolution + swp.cy-1)
          / swp.cy + 2*iYScaleError;

        iWidth+=iXScaleError2;
        iHeight+=iYScaleError2;

        if (iTop<0) iTop = 0;
        if (iLeft<0) iLeft = 0;
        if (iTop+iHeight>SrcBufferDesc.uiYResolution) iHeight = SrcBufferDesc.uiYResolution-iTop;
        if (iLeft+iWidth>SrcBufferDesc.uiXResolution) iWidth = SrcBufferDesc.uiXResolution-iLeft;

//        printf("[WM_PAINT] : Blit (%d %d) size (%d %d)\n", iLeft, iTop, iWidth, iHeight);

        FSLib_BitBlt(hwnd, pchSrcBuffer, iTop, iLeft, iWidth, iHeight);
        //FSLib_BitBlt(hwnd, pchSrcBuffer, 0, 0, SrcBufferDesc.uiXResolution, SrcBufferDesc.uiYResolution);

	WinEndPaint(hps);
      }
      return 0;

    case WM_FSLIBNOTIFICATION:
      {
//	printf("[WM_FSLIBNOTIFICATION]\n");
	if ((int)mp1 == FSLN_TOGGLEFSMODE)
	{
          // FS mode changed, reblit image!
//          FSLib_BitBlt(hwnd, pchSrcBuffer, 0, 0, SrcBufferDesc.uiXResolution, SrcBufferDesc.uiYResolution);
          // Do this from WM_PAINT, so mouse will also be hidden if needed.
          WinInvalidateRect(hwnd, NULL, TRUE);
	}
      }
      return (MRESULT) 1;

    default:
      break;
  }
  return WinDefWindowProc(hwnd, msg, mp1, mp2);
}


void PMThread(void *pParm)
{
  HAB ab;
  HMQ mq;
  QMSG msg;
  ULONG fcf;
  RECTL rectl;


  iPMThreadState = 1;

  ab=WinInitialize(0);
  mq=WinCreateMsgQueue(ab,0);
  if (mq==0)
  {
#ifdef DEBUG_BUILD
    printf("Could not create message queue!\n");
    fflush(stdout);
#endif
  }

  fcf =FCF_TITLEBAR |
       FCF_SYSMENU |
       FCF_MINBUTTON |
       FCF_MAXBUTTON |
       FCF_SIZEBORDER |
       FCF_TASKLIST;


  if (!FSLib_CreateWindow(HWND_DESKTOP, 0, &fcf,
                          "FSLib test window",
                          0, 0, // We don't have resources
                          &SrcBufferDesc,
                          WndProc,
                          &hClient, &hFrame))
  {
#ifdef DEBUG_BUILD
    printf("Could not create FSLib window!\n");
#endif
  }

  // Calculate frame window size from client window size
  rectl.xLeft = 0;
  rectl.yBottom = 0;
  rectl.xRight = FULLSCREENWIDTH; // Noninclusive
  rectl.yTop = FULLSCREENHEIGHT; // Noninclusive
  WinCalcFrameRect(hFrame, &rectl, FALSE);

  WinSetWindowPos( hFrame,
                   HWND_TOP,
                   (WinQuerySysValue (HWND_DESKTOP, SV_CXSCREEN) - (rectl.xRight-rectl.xLeft)) / 2,
                   (WinQuerySysValue (HWND_DESKTOP, SV_CYSCREEN) - (rectl.yTop-rectl.yBottom)) / 2,
                   (rectl.xRight-rectl.xLeft),
                   (rectl.yTop-rectl.yBottom),
		   SWP_SIZE | SWP_ACTIVATE | SWP_SHOW | SWP_MOVE);


#ifdef DEBUG_BUILD
  printf("Entering message loop\n");
  fflush(stdout);
#endif

  iPMThreadState = 1;

  while (WinGetMsg(ab, (PQMSG)&msg, 0, 0, 0))
      WinDispatchMsg(ab, (PQMSG) &msg);

  WinDestroyWindow(hFrame);
  WinDestroyMsgQueue(mq);
  WinTerminate(ab);

  iPMThreadState = 2;
  _endthread();
}


void ModifySrcImageAndBlit()
{
  char *pchData = pchSrcBuffer;
  int x,y;

  // Prepare bitmap
  // Make it black:
  memset(pchData, 0, SrcBufferDesc.uiYResolution * SrcBufferDesc.uiScanLineSize);
  // Create a pattern:
  for (y=0; y<SrcBufferDesc.uiYResolution; y++)
  {
    for (x=0; x<SrcBufferDesc.uiXResolution; x++)
    {
      pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 0] = 0;   // x
      pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 1] = 0;   // B
      pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 2] = 0;   // G
      pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 3] = 255; // R

      if ((x==0) || (x==SrcBufferDesc.uiXResolution-1) ||
          (y==0) || (y==SrcBufferDesc.uiYResolution-1) ||
          (x==y))
      {
        pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 0] = 0;   // x
        pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 1] = 0;   // B
        pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 2] = 255; // G
        pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 3] = 0;   // R
      }
    }
  }
  // Create a moving stuff in the image
  iImageState++;
  while (iImageState>359) iImageState-=360;

  x = (SrcBufferDesc.uiXResolution/2) + (SrcBufferDesc.uiXResolution/2-2) * sin(iImageState * PI/180);
  y = (SrcBufferDesc.uiYResolution/2) + (SrcBufferDesc.uiYResolution/2-2) * cos(iImageState * PI/180);

  pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 0] = 0;   // x
  pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 1] = 255; // B
  pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 2] = 255; // G
  pchData[y*SrcBufferDesc.uiScanLineSize + x*4 + 3] = 255; // R


  // Blit the whole stuff!
  WinInvalidateRect(hClient, NULL, TRUE);
  /*FSLib_BitBlt(hClient,
	       pchSrcBuffer,
	       0, 0,
	       SrcBufferDesc.uiXResolution,
               SrcBufferDesc.uiYResolution);*/
}


int main(void)
{
  FSLib_VideoMode_p pVideoModeList;

#ifdef DEBUG_BUILD
  MorphToPM();
  // Make stdout and stderr unbuffered
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);
#endif

  printf("Starting main()...\n");
  if (!FSLib_Initialize())
  {
    printf("Could not initialize FSLib!\n");
    return 0;
  }

#ifdef DEBUG_BUILD
  pVideoModeList = FSLib_GetVideoModeList();
  if (!pVideoModeList)
  {
    printf("Could not query video mode list!\n");
  } else
  {
    FSLib_VideoMode_p pVideoMode;
    pVideoMode = pVideoModeList;
    printf("Fullscreen video modes available:\n");
    while (pVideoMode)
    {
      printf("[%4dx%4d/%2d bpp]  ", pVideoMode->uiXResolution, pVideoMode->uiYResolution, pVideoMode->uiBPP);
      pVideoMode = pVideoMode->pNext;
    }
    printf("\n");
    FSLib_FreeVideoModeList(pVideoModeList);
  }
#endif

  // Prepare the source buffer we want to use.
  // We'll need the buffer itself, and a buffer descriptor.
  // First, we'll prepare the descriptor:
  SrcBufferDesc.uiXResolution  = FULLSCREENWIDTH;
  SrcBufferDesc.uiYResolution  = FULLSCREENHEIGHT;
  SrcBufferDesc.uiBPP          = 32;
  SrcBufferDesc.uiScanLineSize = SrcBufferDesc.uiXResolution * (SrcBufferDesc.uiBPP+7)/8;
  FSLib_SetPixelFormat(&(SrcBufferDesc.PixelFormat), FSLIB_PIXELFORMAT_RGBA_32BPP);
  // Then allocate memory for the buffer!
  pchSrcBuffer = (char *) malloc(SrcBufferDesc.uiScanLineSize * SrcBufferDesc.uiYResolution);

  // Start PM thread:
  iPMThreadState = 0;
  _beginthread(&PMThread, 0, 16384, NULL);
  while (!iPMThreadState) DosSleep(1);

  // Build first image and blit it.
  ModifySrcImageAndBlit();

  // While the PM thread runs, we blit some images sometimes.
  while (iPMThreadState==1)
  {
    DosSleep(100);
    ModifySrcImageAndBlit();
  }

  printf("Uninitializing everything...\n");
  free(pchSrcBuffer); pchSrcBuffer = NULL;

  FSLib_Uninitialize();

  printf("All done, bye!\n");
  return 0;
}

