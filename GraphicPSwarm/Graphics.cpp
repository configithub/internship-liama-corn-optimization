
/*--------------------------------------------------------
 *
 *                  Graphics.cpp
 *
 *------------------------------------------------------*/

#include <SDL/SDL.h>
#include "Swarm.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B)
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

void Slock(SDL_Surface *screen)
{
	if ( SDL_MUSTLOCK(screen) )
	{
		if ( SDL_LockSurface(screen) < 0 )
		{
			return;
		}
	}
}

void Sulock(SDL_Surface *screen)
{
	if ( SDL_MUSTLOCK(screen) )
	{
		SDL_UnlockSurface(screen);
	}
}



void DrawScene(SDL_Surface *screen, int Np, matrix* PX, matrix* PY, int T)
{
	Slock(screen);
	for(int i=0;i<Np;i++) { 
		DrawPixel(screen,(int)PX->getij(i,T),(int)PY->getij(i,T), 200, 0, 0);
	}
	Sulock(screen);
	SDL_Flip(screen);
}


void EraseScene(SDL_Surface *screen)
{
	Slock(screen);
	for(int x=0;x<640;x++) {
		for(int y=0;y<480;y++) { 
			DrawPixel(screen, x,y,0,0,0);
		}
	}
	Sulock(screen);
	SDL_Flip(screen);
}


int pentiere(double a)
{
	double pent;
	double pdec;
	pdec = modf(a, &pent);
	return (int)pent;
}






int main(int argc, char *argv[])
{

//initialisation des matrices ParticleX et ParticleY
	
	
	//choix des 2 composantes du vecteur W à projeter sur les axes X et Y
	int X = 1;
	int Y = 2;
	
	
	//indice des temps (itération de 0 à 99 par défaut)
	int T= 0;
		
	//initialisation du swarm
	Swarm* essaim;
	essaim = new Swarm(100,500);
	
	matrix* ParticleX;
	ParticleX = new matrix(essaim->Npart,essaim->Nit);


	matrix* ParticleY;
	ParticleY = new matrix(essaim->Npart,essaim->Nit);
	
	for(int j=0;j<essaim->Nit;j++) { 
		for(int i=0;i<essaim->Npart;i++) {
			if(pentiere((640.0/2.4)*(essaim->getParticleCoord(i,X)-0.6))>=639)
			{
				ParticleX->setij(i,j,639);
			}else{
				ParticleX->setij(i,j,pentiere((640.0/2.4)*(essaim->getParticleCoord(i,X)-0.6)));
			}
			if(pentiere((480.0/2.4)*(essaim->getParticleCoord(i,Y)-0.6))>=479)
			{
				ParticleY->setij(i,j,479);
			}else{
				ParticleY->setij(i,j,pentiere((480.0/2.4)*(essaim->getParticleCoord(i,Y)-0.6)));
			}
		}
		essaim->update();
	}



//fonctions graphiques

	
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

	int done = 0;
	
	 


	 



	 
	while(done == 0)
	{
		SDL_Event event;

		while ( SDL_PollEvent(&event) )
		{
			if ( event.type == SDL_QUIT )  {  done = 1;  }
		        if ( event.type == SDL_KEYDOWN )
			{
				if ( event.key.keysym.sym == SDLK_ESCAPE ) { done = 1; }
				if ( event.key.keysym.sym == SDLK_n ) { T += 1; }
				if ( event.key.keysym.sym == SDLK_b ) { T -= 1; }
				if ( T == -1 ) { done = 1; }
			}
		}
		//EraseScene(screen);
	 	DrawScene(screen,essaim->Npart,ParticleX,ParticleY,T);
	}
	 
	return 0;
}
