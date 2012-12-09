SDL - Source code modified for OS/2
-----------------------------------


1. General info
---------------


This package contains the latest SDL binaries and headers which can be used
to create or port an application to OS/2, which uses SDL.

There are five subdirectories currently:

- SDL: (libSDL 1.2.7)
  Contains the base SDL itself.
- SDLMixer: (SDL_Mixer 1.2.5)
  Contains the SDL_Mixer library, but lacks the MP3 decoding capability. All
  other formats (supported by original SDL_Mixer) are supported.
- SDLImage: (SDL_Image 1.2.3)
  Contains the SDL_Image library. Supports every image format that is supported
  by the original SDL_Image library.
- SDLGfx: (SDL_gfx 2.0.13)
  Contains the SDL_Image library. Supports every image format that is supported
  by the original SDL_Image library.
- SDLNet: (SDL_Net 1.2.5)
  Contains the SDL_Net library. Not yet fully tested.
- SDLTTF: (SDL_ttf 2.0.6)
  Contains the SDL_TTF library.


Please note that:

SDL uses the Scitech SNAP API to have video support, so the SDL apps will 
require Scitech SNAP or Scitech Display Doctor in order to run.



2. What is missing?
-------------------

The following things are missing from this SDL implementation:
- MMX, SSE and 3DNOW! optimized video blitters?
- HW Video surfaces
- OpenGL support



3. Special Keys / Full-Screen support
-------------------------------------

There are two special hot-keys implemented:
- Alt+Home switches between fullscreen and windowed mode
- Alt+End simulates closing the window
Only the LEFT Alt key will work.



4. Joysticks on SDL/2
---------------------

The Joystick detection only works for standard joysticks (2 buttons, 2 axes
and the like). Therefore, if you use a non-standard joystick, you should
specify its features in the SDL_OS2_JOYSTICK environment variable in a batch
file or CONFIG.SYS, so SDL applications can provide full capability to your
device. The syntax is:

SET SDL_OS2_JOYSTICK=[JOYSTICK_NAME] [AXES] [BUTTONS] [HATS] [BALLS]

So, it you have a Gravis GamePad with 4 axes, 2 buttons, 2 hats and 0 balls,
the line should be:

SET SDL_OS2_JOYSTICK=Gravis_GamePad 4 2 2 0

If you want to add spaces in your joystick name, just surround it with
quotes or double-quotes:

SET SDL_OS2_JOYSTICK='Gravis GamePad' 4 2 2 0

or

SET SDL_OS2_JOYSTICK="Gravis GamePad" 4 2 2 0

   Notive However that Balls and Hats are not supported under OS/2, and the
value will be ignored... but it is wise to define these correctly because 
in the future those can be supported.
   Also the number of buttons is limited to 2 when using two joysticks,
4 when using one joystick with 4 axes, 6 when using a joystick with 3 axes
and 8 when using a joystick with 2 axes. Notice however these are limitations 
of the Joystick Port hardware, not OS/2.



5. Proportional windows
-----------------------

For some SDL applications it can be handy to have proportional windows, so
the windows will keep their aspect ratio when resized.
This can be achieved in two ways:

- Before starting the given SDL application, set the
  SDL_USE_PROPORTIONAL_WINDOW environment variable to something, e.g.:

  SET SDL_USE_PROPORTIONAL_WINDOW=1
  dosbox.exe

- If you have a HOME environment variable set, then SDL will look for a file
  in there called ".sdl.proportionals". If that file contains the name of the
  currently running SDL executable, then that process will have proportional
  windows automatically.

  Please note that this file is created automatically with default values
  at the first run.



6. Next steps...
----------------

Things to do:
- Implement missing stuffs (look for 'TODO' string in source code!)
- Finish video driver (the 'wincommon' can be a good example for missing
  things like application icon and so on...)
- Enable MMX/SSE/SSE2 acceleration functions
- Rewrite CDROM support using DOS Ioctl for better support.



7. Contacts
-----------

   You can contact the developers for bugs:

   Area					Developer		email
   General (Audio/Video/System)		Doodle			doodle@scenergy.dfmk.hu
   CDROM and Joystick			Caetano			daniel@caetano.eng.br

   Notice however that SDL/2 is 'in development' stage so ... if you want to
   help, please, be our guest and contact us!
