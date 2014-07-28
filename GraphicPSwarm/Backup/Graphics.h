/*--------------------------------------------------------
 *
 *                  Graphics.h
 *
 *------------------------------------------------------*/


#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <stdio.h>
#include <stdlib.h>

#include <SDL/SDL.h>

class Graphics
{
	public :
	void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B);
	void Slock(SDL_Surface *screen);
	void Sulock(SDL_Surface *screen);
};

#endif


