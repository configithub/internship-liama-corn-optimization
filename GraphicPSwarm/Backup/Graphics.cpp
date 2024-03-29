/*--------------------------------------------------------
 *
 *                  Graphics.cpp
 *
 *------------------------------------------------------*/

#include "Graphics.h"

void Graphics::DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
	Uint32 color = SDL_MapRGB(screen->format, R, G, B);
	switch (screen->format->BytesPerPixel)
	{
		case 1: // Assuming 8-bpp
		{
			Uint8 *bufp;
			bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
			*bufp = color;
		}
		break;
		case 2: // Probably 15-bpp or 16-bpp
		{
			Uint16 *bufp;
			bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
			*bufp = color;
		}
		break;
		case 3: // Slow 24-bpp mode, usually not used
		{
			Uint8 *bufp;
			bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
			if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
			{
				bufp[0] = color;
				bufp[1] = color >> 8;
				bufp[2] = color >> 16;
			} else {
				bufp[2] = color;
				bufp[1] = color >> 8;
				bufp[0] = color >> 16;
			}
		}
		break;
		case 4: // Probably 32-bpp
		{
			Uint32 *bufp;
			bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
			*bufp = color;
		}
		break;
	}
}

void Graphics::Slock(SDL_Surface *screen)
{
	if ( SDL_MUSTLOCK(screen) )
	{
		if ( SDL_LockSurface(screen) < 0 )
		{
			return;
		}
	}
}

void Graphics::Sulock(SDL_Surface *screen)
{
	if ( SDL_MUSTLOCK(screen) )
	{
		SDL_UnlockSurface(screen);
	}
}



void DrawScene(SDL_surface *screen, Graphics  *gfx)
{ 
	gfx->Slock(screen);
	for(int x=0;x<640;x++)
	{
		for(int y=0;y<480;y++)
		{
			gfx->DrawPixel(screen, x,y,y/2,y/2,x/3);
		}
	}
	gfx->Sulock(screen);
	SDL_Flip(screen);
}



int main(int argc, char *argv[])
{

	 if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 )
	 {
		printf("Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	 }
	 atexit(SDL_Quit);

	 SDL_Surface *screen;
	 screen=SDL_SetVideoMode(640,480,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	 if ( screen == NULL )
  	 {
	 	printf("Unable to set 640x480 video: %s\n", SDL_GetError());
		exit(1);
	 }

	 // DRAWING GOES HERE

	 Graphics* gfx;
	 gfx = new Graphics();
	 while(done == 0)
	 {
		 SDL_Event event;

		 while ( SDL_PollEvent(&event) )
		 {
			 if ( event.type == SDL_QUIT )  {  done = 1;  }
		         if ( event.type == SDL_KEYDOWN )
			 {
				 if ( event.key.keysym.sym == SDLK_ESCAPE ) { done = 1; }
			 }
		 }
	 	DrawScene(screen,gfx);
	 }
	 
	 return 0;
}
