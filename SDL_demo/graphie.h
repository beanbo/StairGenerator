#pragma once
#include "stdafx.h"
#include <vector>

typedef double(*func_1v)(double x);

struct position { double x, y, z; } typedef position; //position ~

void change_xyz(double* x, double* y, double* z, double** sk);
bool dotInPoly(int x0, int y0, int x1, int y1, int x2, int y2, int dx, int dy);
void polygonDraw(SDL_Surface* surface, int x0, int y0, int x1, int y1, int x2, int y2, UINT32 color, double** cs);

class graphic_object
{
protected:
	double alpha;
	double** object_coordinate_system;
	//	[a12, a12, a13, xn]
	//	[a21, a22, a23, yn]
	//  [a31, a32, a33, zn]
	Uint32 basic_color;
	position pos;
public:
	graphic_object(int x = 0, int y = 0,int z = 0, Uint32 basic_color = 0, double alpha = 0);

	~graphic_object() {}

	virtual void draw(SDL_Surface *surface) {}

	position get_pos() { return pos; }

	Uint32 get_color() { return basic_color; }

	void set_cs (double **get_cs);
	double** get_cs() { return object_coordinate_system; }
};


class background : public graphic_object
{
public:
	background(Uint32 basic_color = 0, double alpha = 0) :graphic_object(0, 0, 0, basic_color, alpha) {}
	void draw(SDL_Surface *surface) override;
};

class dot : public graphic_object
{
private:
	int radius;
public:
	dot(int x = 0, int y = 0, int z = 0, int radius = 1, Uint32 basic_color = 0, double alpha = 0) :graphic_object(x, y, z, basic_color, alpha), radius(radius) {}
	void draw(SDL_Surface *surface) override;
};


class coordinats_xyz : public graphic_object
{
private:
	int length;
public:
	coordinats_xyz(int x = 0, int y = 0, int z = 0, int length = 200, Uint32 basic_color = 0, double alpha = 0) :graphic_object(x, y, z, basic_color, alpha), length(length) {}
	void draw(SDL_Surface *surface) override;
};

class circle : public graphic_object
{
private:
	int radius;
public:
	circle(int x = 0, int y = 0, int z = 0, int radius = 1, Uint32 basic_color = 0, double alpha = 0) :graphic_object(x, y, z, basic_color, alpha), radius(radius) {}
	void draw(SDL_Surface *surface) override;
};

class one_v_func : public graphic_object
{
private:
	func_1v func;
	double x1, x2, step;
public:
	one_v_func(func_1v func, double step = 0.1, int x1=-100, int x2=100, int x = 0, int y = 0,  Uint32 basic_color = 0, double alpha = 0) :graphic_object(x, y, 0, basic_color, alpha), func(func), step(step), x1(x1), x2(x2){}
	void draw(SDL_Surface *surface) override;
};

class polar_func : public graphic_object
{
private:
	func_1v y_func;
	func_1v x_func;
	double x1, x2, step;
public:
	polar_func(func_1v x_func, func_1v y_func, double step = 0.1, int x1 = -100,  int x2 = 100, int x = 0, int y = 0, Uint32 basic_color = 0, double alpha = 0) :graphic_object(x, y, 0, basic_color, alpha), y_func(y_func), step(step), x_func(x_func), x1(x1), x2(x2) {}
	void draw(SDL_Surface *surface) override;
};

class triangle : public graphic_object
{
protected:
	bool dotInTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int dx, int dy);
private:
	int x0, x1, x2, y0, y1, y2;
public:
	triangle(SDL_Surface* surface, int x0, int y0, int x1, int y1, int x2, int y2, Uint32 basic_color = 0, double alpha = 0) :graphic_object(0, 0, 0, basic_color, alpha), x0(x0), y0(y0), x1(x1), y1(y1), x2(x2), y2(y2) {}
	void draw(SDL_Surface* surface) override;
};


class line : public graphic_object
{
private:
	double x0, x1, y0, y1, z0, z1;
public:
	void change(double x0, double x1, double y0, double y1, double z0, double z1) 
	{ 
		this->x0 = x0;  this->x1 = x1;
		this->y0 = y0; this->y1 = y1; 
		this->z0 = z0; this->z1 = z1;
	}
	line(double x0, double x1, double y0, double y1, double z0, double z1, Uint32 basic_color = 0, double alpha = 0) :graphic_object(0, 0, 0, basic_color, alpha), 
		x0(x0), x1(x1), y0(y0), y1(y1), z0(z0), z1(z1) {}
	bool edgecmp(position v1, position v2) const;
	void draw(SDL_Surface *surface) override;
};

class lineal_object : public graphic_object
{
private:
	std::vector<line*> line_list;
	int number_of_lines;
public:
	line* get_line(int n) { return line_list[n]; }
	int get_number_of_lines() { return number_of_lines; }
	void insert_line(line* new_line);
	void delete_lines() { line_list.clear(); number_of_lines = 0; }
	void delete_line(int n) { line_list.erase(line_list.begin() + n); number_of_lines--; }
	lineal_object(SDL_Surface* surface, Uint32 basic_color = 0, double alpha = 0) :graphic_object(0, 0, 0, basic_color, alpha) {}
	virtual void draw(SDL_Surface* surface) {}
	
};

class box : public lineal_object
{
	int x0, x1, x2, y0, y1, y2, z0, z1, z2;
public:
	box(SDL_Surface* surface, int x0, int y0, int x1, int y1, int x2, int y2, int z0, int z1, int z2, UINT32 basic_color = 0, double alpha = 0) :lineal_object(surface, basic_color, alpha),
		x0(x0), x1(x1), x2(x2), y0(y0), y1(y1), y2(y2), z0(z0), z1(z1), z2(z2)
	{
		insert_line(new line(x0, x2, y0, y2, z0, z0, basic_color, alpha)); // Рисуем нижнее основание
		insert_line(new line(x2, x1, y2, y1, z0, z0, basic_color, alpha));
		insert_line(new line(x1, x1 - x2 + x0, y1, y0 + y1 - y2, z0, z0, basic_color, alpha));
		insert_line(new line(x1 - x2 + x0, x0, y0 + y1 - y2, y0, z0, z0, basic_color, alpha));

		insert_line(new line(x0, x2, y0, y2, z1, z1, basic_color, alpha)); // Рисуем верхнее основание
		insert_line(new line(x2, x1, y2, y1, z1, z1, basic_color, alpha));
		insert_line(new line(x1, x1 - x2 + x0, y1, y0 + y1 - y2, z1, z1, basic_color, alpha));
		insert_line(new line(x1 - x2 + x0, x0, y0 + y1 - y2, y0, z1, z1, basic_color, alpha));

		insert_line(new line(x0, x0, y0, y0, z0, z1, basic_color, alpha)); // Рисуем ребра
		insert_line(new line(x2, x2, y2, y2, z0, z1, basic_color, alpha));
		insert_line(new line(x1, x1, y1, y1, z0, z1, basic_color, alpha));
		insert_line(new line(x1 - x2 + x0, x1 - x2 + x0, y0 + y1 - y2, y0 + y1 - y2, z0, z1, basic_color, alpha));
	}
	void draw(SDL_Surface * surface) override;
};
//
//class Edgep
//{
//public:
//	Vertex* v1; 
//	Vertex* v2;
//	Edgep(Vertex *v1, Vertex *v2)
//	{
//		this->v1 = v1;
//		this->v2 = v2;
//	}
//};

class Vertex
{
public:
	double x, y, z;
	Vertex(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class polygon  : public graphic_object
{
bool front = false;
//*			 ----Видимость полигона----
//**   Если Vertex-ы расположены против часовой, то полигон лицевой
//***  Если по часовой, то полигон нелицевой и он не отрисовывается
public:
	Vertex *v1, *v2, *v3;
	bool wireframe = false;
	polygon(SDL_Surface* surface, Vertex *v1, Vertex *v2, Vertex *v3, Uint32 basic_color = 0, double alpha = 0) : graphic_object(0, 0, 0, basic_color, alpha)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
		front = orientation();
	}
	bool orientation();
	void change_polygon(double **cs);
	void draw(SDL_Surface *surface) override;
};

class stair : public lineal_object
{
	int n;
	double x, y, z, a, b, width;
	
	bool wireframe = false;
	SDL_Surface* surface;
public:
	stair(SDL_Surface* surface, double x, double y, double z, double a, double width, int n = 1, UINT32 basic_color = 0, double alpha = 0) :lineal_object(surface, basic_color, alpha), x(x), y(y), z(z), n(n), a(a), width(width), surface(surface) { initialize(); }
	void initialize();
	void draw(SDL_Surface* surface) override;
	int get_numberSteps() { return n;}
	std::vector<polygon*> polys;
	std::vector<Vertex*> vertexs;
	bool viewingWireframe();
	void plusStep(int value);
	void changeLength(int value);
	void changeMesh();
};

class lineal_rectangle : public lineal_object
{
	int x0, x1, y0, y1, z0, z1;
public:
	lineal_rectangle(SDL_Surface* surface, int x0, int y0, int z0, int x1, int y1, int z1, UINT32 basic_color = 0, double alpha = 0) :lineal_object(surface, basic_color, alpha),
		x0(x0), x1(x1), y0(y0), y1(y1), z0(z0), z1(z1)
	{
		insert_line(new line(x0, x0, y0, y1, z0, (z1 + z0)/2, basic_color, alpha));
		insert_line(new line(x0, x1, y1, y1, (z1 + z0) / 2, z1, basic_color, alpha));
		insert_line(new line(x1, x1, y1, y0, z1, (z1 + z0) / 2, basic_color, alpha));
		insert_line(new line(x1, x0, y0, y0, (z1 + z0) / 2, z0, basic_color, alpha));
	}
	void draw(SDL_Surface* surface) override;
};

class lineal_triangle : public lineal_object
{
	int x0, x1, x2, y0, y1, y2, z0, z1, z2;
public:
	lineal_triangle(SDL_Surface* surface, int x0, int y0, int x1, int y1, int x2, int y2, int z0, int z1, int z2, UINT32 basic_color = 0, double alpha = 0) :lineal_object(surface, basic_color, alpha),
		x0(x0), x1(x1), x2(x2), y0(y0), y1(y1), y2(y2), z0(z0), z1(z1), z2(z2)
	{ 
		insert_line(new line(x0, x1, y0, y1, z0, z1, basic_color, alpha));
		insert_line(new line(x1, x2, y1, y2, z1, z2, basic_color, alpha));
		insert_line(new line(x0, x2, y0, y2, z0, z2, basic_color, alpha));
	}
	void draw(SDL_Surface* surface) override;
};


class layer
{
private:
	double layer_alpha;
	Uint32 layer_basic_color;
	double** layer_coordinate_system;

	std::vector<graphic_object*> object_list;

	int obj_number;
public:
	layer(Uint32 basic_color = 0x0000FF00, double alpha = 0);

	void set_coordinate_system(double**get_cs);

	double** get_cs() { return layer_coordinate_system; }

	graphic_object* get_object(int n) { return object_list[n]; }

	void insert_object(graphic_object *new_obj);

	void draw(SDL_Surface *surface);
};



class picture
{
private:
	SDL_Surface *surface;
	Uint32 global_basic_color;
	double global_alpha;
	double** global_coordinate_system;
	std::vector<layer*> layers_list;
	int layers_number;
public:
	picture(SDL_Surface *surface, Uint32 color = 0x0000FF00, double alpha = 0);

	int x_location = 0, y_location = 0;

	SDL_Surface* get_surf() { return surface; }

	void set_cs(double**get_cs);
	double** get_cs() { return global_coordinate_system; }

	
	layer* get_layer(int n) { return layers_list[n]; }
	void insert_layer(layer *new_layer);
	void insert_object(graphic_object *new_obj, int n = 0);
	void draw();
};
