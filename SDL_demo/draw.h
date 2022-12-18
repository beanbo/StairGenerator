#ifndef DRAW_H
#define DRAW_H

#include "stdafx.h"
#include "graphie.h"

void draw(SDL_Surface *s, picture *pic, double p);

void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel);

void put_pixel32_sk(SDL_Surface *surface, double x, double y, double z, Uint32 pixel, double **sk);

void put_pixel32_XY(SDL_Surface* surface, double x, double y, Uint32 pixel, double** sk);

double** create_sk(
	double a00, double a01, double a02, double a03,
	double a10, double a11, double a12, double a13,
	double a20, double a21, double a22, double a23);

picture* initialize_picture(SDL_Surface *s);

#endif