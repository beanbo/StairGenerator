#include "draw.h"
#include "stdafx.h"
#include "stdio.h""
#include "graphie.h"

#define RGB32(r, g, b) static_cast<uint32_t>((((static_cast<uint32_t>(b) << 8) | g) << 8) | r)


double polar_flower_x(double t)
{
	return (3 * 30 * t / (1 + pow(t, 3)));
}

double polar_flower_y(double t)
{
	return (3 * 30 * pow(t, 2) / (1 + pow(t, 3)));
}


double** create_sk(
	double a00, double a01, double a02, double a03,
	double a10, double a11, double a12, double a13,
	double a20, double a21, double a22, double a23)
{
	double **s = new double*[3];

	for (int i = 0; i < 3; i++)
	{
		s[i] = new double[4];
	}

	s[0][0] = a00;		s[0][1] = a01;		s[0][2] = a02;		s[0][3] = a03;

	s[1][0] = a10;		s[1][1] = a11;		s[1][2] = a12;		s[1][3] = a13;

	s[2][0] = a20;		s[2][1] = a21;		s[2][2] = a22;		s[2][3] = a23;

	return s;
}


void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	assert(NULL != surface);

	if ((abs(x) < SCREEN_WIDTH) && (abs(y) < SCREEN_HEIGHT))
	{
		Uint32 *pixels = (Uint32 *)surface->pixels;
		pixels[(y * surface->w) + x] = pixel;
	}
}

Uint32 get_pixel32(SDL_Surface *surface, int x, int y)
{
	assert(NULL != surface);
	assert(x < SCREEN_WIDTH);
	assert(y < SCREEN_HEIGHT);

	Uint32 *pixels = (Uint32 *)surface->pixels;
	return pixels[(y * surface->w) + x];
}


void big_dot(SDL_Surface *surface, int x, int y, int width, Uint32 pixel)
{
	for (int i = 0; i <= width; i++)
		for (int j = 0; j <= width; j++)
		{
			put_pixel32_sk(surface, x - (width / 2) + i, y - (width / 2) + j, 0, pixel, nullptr);
		}

}


position change_cs(double x, double y, double **sk)
{
	position p;
	if (sk != nullptr)
	{
		int temp = x, temp1 = y;
		p.x = (sk[0][0] * x) + (sk[0][1] * y)+ sk[0][2];
		p.y = (sk[1][0] * temp) + (sk[1][1] * y) + sk[1][2];
		
	}
	return p;
}



void put_pixel32_sk(SDL_Surface *surface, double x, double y, double z, Uint32 pixel, double **sk)
{
	assert(NULL != surface);

	double tempX = x;
	x = y + x;
	y = z + tempX;
	position p = change_cs(x, y, sk);

	int x_screen = (int)(p.x + surface->w / 2);
	int y_screen = (int)(-p.y + surface->h / 2);

	if ((abs(x_screen) < SCREEN_WIDTH) && (abs(y_screen) < SCREEN_HEIGHT))
	{
		Uint32 *pixels = (Uint32 *)surface->pixels;
		pixels[(y_screen * surface->w) + x_screen] = pixel;
	}
}

void put_pixel32_XY(SDL_Surface* surface, double x, double y, Uint32 pixel, double** sk)
{
	assert(NULL != surface);

	position p = change_cs(x, y, sk);

	int x_screen = (int)(p.x + surface->w / 2);
	int y_screen = (int)(-p.y + surface->h / 2);

	if ((abs(x_screen) < SCREEN_WIDTH) && (abs(y_screen) < SCREEN_HEIGHT))
	{
		Uint32* pixels = (Uint32*)surface->pixels;
		pixels[(y_screen * surface->w) + x_screen] = pixel;
	}
}



picture* initialize_picture(SDL_Surface *s)
{
	picture *pic = new picture(s, RGB32(255, 255, 255), 0);

	pic->insert_layer(new layer());

	pic->insert_object(new background(RGB32(255, 255, 255), 0), 0);
	pic->insert_object(new coordinats_xyz(0, 0, 0, 200, RGB32(2, 155, 22), 0), 0);
	//pic->insert_object(new dot(0, 0, 0, 7, RGB32(78, 56, 255), 0), 0);
	//pic->insert_object(new polygon(s, new Vertex(0, -50, -60), new Vertex(-100, -50, 0), new Vertex(0, 0, 50), RGB32(155, 15, 235), 0), 0);
	//pic->insert_object(new box(s, 0, 0, 100, 150, 0, 100, 0, 100, 0, RGB32(125, 75, 235), 0), 0);
	pic->insert_object(new stair(s, 50, 50, 50, 12, -100, 5, RGB32(200, 149, 145), 0), 0);
	//pic->insert_object(new circle(0, 0, 20, 4, RGB32(255, 235, 25), 0), 0);
	//pic->insert_object(new triangle(s, -100, -25, -30, 50, 25, 25, RGB32(155, 15, 235), 0), 0);
	//pic->insert_object(new lineal_rectangle(s, 0, 0, 0, 100, 100, 0, RGB32(15, 235, 155), 0), 0);
	return pic;
}

 void draw(SDL_Surface *s, picture* pic, double p)
 {
	/*pic->get_layer(0)->get_object(2)->set_cs(create_sk(cos(p), -sin(p ), 0, 1,
													   sin(p), cos(p ), 0, 1,
													   0, 0, 1, 0));*/
	//pic->get_layer(0)->get_object(4)->set_cs(create_sk(3 * cos(p * 10), sin(p * 10),pic->x_location, -sin(p * 10), 3 * cos(p * 10), pic->y_location));
	pic->draw();
}
	// или использу€ макрос можно получить код цвета:
	//   RGB32(0, 255, 0) эквивалентно записи 0x0000FF00


 // l->get_object(5)->set_cs(create_sk(cos(p), sin(p), 0, -1 * sin(p), cos(p), 0));