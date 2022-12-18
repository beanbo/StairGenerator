#include "stdafx.h"
#include "draw.h"
#include "graphie.h"
#include <iostream>
#include "UserInput.h"
#include <fstream>

bool init();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
SDL_Surface* loadedSurface = NULL;

bool init()
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Stair generator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_SOFTWARE);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
		}
	}
	return success;
}
void close()
{
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		loadedSurface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
			0x00FF0000,  // R
			0x0000FF00,  // G
			0x000000FF,  // B
			0x00000000); // alpha

		gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

		if ( NULL == gTexture )
		{
			printf("Failed to load media!\n");
		}
		else
		{
			UserInputValues in;
			bool quit = false;

			bool motion_is_active = 0;
			in.pic = initialize_picture(loadedSurface);

			double p = -0.99;

			while (!quit)
			{
				SDL_RenderClear(gRenderer);
				draw(loadedSurface, in.pic, p);
				p += 0.01;
				// ���������� ������� � ������������ ������
				while (SDL_PollEvent(&in.event))
				{
					if (SDL_QUIT == in.event.type)
					{
						quit = true;
					}
					in = input(in);
					if (in.returnCode == 0) return 0;
				}
				////////
				SDL_UpdateTexture(gTexture, NULL, loadedSurface->pixels, loadedSurface->pitch);
				SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}