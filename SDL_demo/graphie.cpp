#include "graphie.h"
#include "stdafx.h"
#include "draw.h"
#include <iostream>

double ** initialize_default_cs()
{
	double ** cs = new double*[3];

	for (int i = 0; i < 3; i++)
	{
		cs[i] = new double[4];
		for (int j = 0; j < 4; j++)
		{
			if (i != j) cs[i][j] = 0;
			else cs[i][j] = 1;
		}
	}
	return cs;
}

graphic_object::graphic_object(int x, int y, int z, Uint32 basic_color, double alpha)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
	this->basic_color = basic_color;
	this->alpha = alpha;
	object_coordinate_system = initialize_default_cs();
}

void graphic_object::set_cs(double **get_cs)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			object_coordinate_system[i][j] = get_cs[i][j];
}


void background::draw(SDL_Surface *surface)
{
	for (int i = 0; i < surface->w; i += 1)
		for (int j = 1; j < surface->h; j += 1)
			put_pixel32(surface, i, j, get_color());
}

void dot::draw(SDL_Surface *surface)
{
	for (double i = 1; i < 2*radius; i += 0.1)
		for (double j = 1; j < 2*radius; j += 0.1)
		{
			put_pixel32_sk(surface, get_pos().x - radius + i, get_pos().y - radius + j, 0, get_color(), get_cs());
		}
}

void coordinats_xyz::draw(SDL_Surface *surface)
{
	for (int i = -length; i < length; i++)
		if (i % 10)
		{
			put_pixel32_sk(surface, 0 + get_pos().x, i + get_pos().y, 0 + get_pos().z, get_color(), get_cs()); // y
			put_pixel32_sk(surface, i + get_pos().x, 0 + get_pos().y, 0 + get_pos().z, get_color(), get_cs()); // x
			put_pixel32_sk(surface, 0 + get_pos().x, 0 + get_pos().y, i + get_pos().z, get_color(), get_cs()); // z
		}
		else i += 2;

}


void lineal_rectangle::draw(SDL_Surface* surface)
{
	for (int i = 0; i < get_number_of_lines(); i++)
		get_line(i)->draw(surface);
}

void box::draw(SDL_Surface* surface)
{
	for (int i = 0; i < get_number_of_lines(); i++)
		get_line(i)->draw(surface);
}

void stair::initialize()
{
	b = 2 * a;
	b = -b;
	double height = a * n;
	double length = b * n;
	
	polys.insert(polys.end(),
		new polygon(surface, 
			new Vertex(x, y, z),
			new Vertex(x, width + y, height + z),
			new Vertex(x, y, height + z),
			basic_color + 1233,alpha));

	polys.insert(polys.end(),
		new polygon(surface,
			new Vertex(x, width + y, height + z),
			new Vertex(x, y, z),
			new Vertex(x, width + y, z),
			basic_color + 1233, alpha));

	polys.insert(polys.end(),
		new polygon(surface,
			new Vertex(x, y, z),
			new Vertex(x + length, y, z),
			new Vertex(x, width + y, z),
			basic_color + 950, alpha));

	polys.insert(polys.end(),
		new polygon(surface,
			new Vertex(x + length, y, z),
			new Vertex(x + length, y + width, z),
			new Vertex(x, width + y, z),
			basic_color  +950, alpha));

	//insert_line(new line(x, x, width + y, y, height + z, height + z, basic_color, alpha));
	//insert_line(new line(x, x, y, y, z, height + z, basic_color, alpha));
	//insert_line(new line(x, length + x, y, y, z, z, basic_color, alpha));
	for (int step = 0; step < n; step++)
	{
		polys.insert(polys.end(),
			new polygon(surface,
				new Vertex(b * (step + 1) + x, y, height - a * step + z),
				new Vertex(b * step + x, y, height - a * step + z),
				new Vertex(b * step + x, width + y, height - a * step + z),
				basic_color + step*7, alpha));

		polys.insert(polys.end(),
			new polygon(surface,
				new Vertex(b * (step + 1) + x, width + y, height - a * step + z),
				new Vertex(b * (step + 1) + x, y, height - a * step + z),
				new Vertex(b * step + x, width + y, height - a * step + z),
				basic_color + step * 7, alpha));

		polys.insert(polys.end(),
			new polygon(surface,
				new Vertex(b * (step + 1) + x, width + y, height - a * step + z),
				new Vertex(b * (step + 1) + x, width + y, height - a * (1 + step) + z),
				new Vertex(b * (step + 1) + x, y, height - a * (1 + step) + z),
				basic_color + 1233 + step * 5, alpha));

		polys.insert(polys.end(),
			new polygon(surface,
				new Vertex(b * (step + 1) + x, width + y, height - a * step + z),
				new Vertex(b * (step + 1) + x, y, height - a * (1 + step) + z),
				new Vertex(b * (step + 1) + x, y, height - a * step + z),
				basic_color + 1233 + step * 5, alpha));

		polys.insert(polys.end(),
			new polygon(surface,
				new Vertex(b * (step + 1) + x, y, height - a * (1 + step) + z),
				new Vertex(x, y, z),
				new Vertex(b * (step + 1) + x, y, height - a * step + z),
				basic_color + 700 + step * 5, alpha));

		polys.insert(polys.end(),
			new polygon(surface,
				new Vertex(x, y, z),
				new Vertex(b * step + x, y, height - a * step + z),
				new Vertex(b * (step + 1) + x, y, height - a * step + z),
				basic_color + 700 + step * 5, alpha));

		polys.insert(polys.end(),
			new polygon(surface,
				new Vertex(x, y + width, z),
				new Vertex(b * (step + 1) + x, y + width, height - a * (1 + step) + z),
				new Vertex(b * (step + 1) + x, y + width, height - a * step + z),
				basic_color + 700 + step * 5, alpha));

		polys.insert(polys.end(),
			new polygon(surface,
				new Vertex(b * step + x, y + width, height - a * step + z),
				new Vertex(x, y + width, z),
				new Vertex(b * (step + 1) + x, y + width, height - a * step + z),
				basic_color + 700 + step * 5, alpha));

	//	insert_line(new line(b * step + x, b * (step + 1) + x, y, y, height - a * step + z, height - a * step + z, basic_color, alpha));//                                 /   /
	//	insert_line(new line(b * step + x, b * (step + 1) + x, width + y, width + y, height - a * step + z, height - a * step + z, basic_color, alpha));//                /   /

	//	insert_line(new line(b * (step + 1) + x, b * (step + 1) + x, y, y, height - a * step + z, height - a * (1 + step) + z, basic_color, alpha));//                    |   |
	//	insert_line(new line(b * (step + 1) + x, b * (step + 1) + x, width + y, width + y, height - a * step + z, height - a * (1 + step) + z, basic_color, alpha));//    |   |

	//	insert_line(new line(b * (step + 1) + x, b * (step + 1) + x, y, width + y, height - a * step + z, height - a * step + z, basic_color, alpha));//              -----
	//	insert_line(new line(b * (step + 1) + x, b * (step + 1) + x, y, width + y, height - a * (1 + step) + z, height - a * (1 + step) + z, basic_color, alpha));//  -----
	}
}

void stair::draw(SDL_Surface* surface)
{

	for (int i = 0; i < get_number_of_lines(); i++)
		get_line(i)->draw(surface);
	for (int i = polys.size() - 1; i >= 0; i--)
		polys[i]->draw(surface);
}

bool stair::viewingWireframe()
{
	wireframe = !wireframe;
	for (int i = polys.size() - 1; i >= 0; i--)
		polys[i]->wireframe = wireframe;

	return false;
}

void stair::plusStep(int value)
{
	if ((n + value) > 0)
	{

		n += value;
		delete_lines();
		polys.clear();
		initialize();
	}
}

void stair::changeLength(int value)
{
	if ((a + value) > 0)
	{
		a += value;
		delete_lines();
		polys.clear();
		initialize();
	}
}

void stair::changeMesh()
{
	for (int i = 0; i < polys.size(); i++)
		polys[i]->change_polygon(get_cs());
}

void change_xyz(double* x, double* y, double* z, double** sk)
{
	{
		if (sk != nullptr)
		{
			double temp = *x, temp1 = *y;
			*x = (sk[0][0] * (*x)) + (sk[0][1] * (*y)) + (sk[0][2] * (*z)) +sk[0][3];
			*y = (sk[1][0] * temp) + (sk[1][1] * (*y)) + (sk[1][2] * (*z)) +sk[1][3];
			*z = (sk[2][0] * temp) + (sk[2][1] * temp1) + (sk[2][2] * (*z)) +sk[2][3];
		}
	}

}

void lineal_triangle::draw(SDL_Surface* surface)
{
	for (int i = 0; i < get_number_of_lines(); i++)
		get_line(i)->draw(surface);
}


void circle::draw(SDL_Surface *surface)
{
	for (double i =  - radius; i <  radius; i += 0.1)
		for (double j =  - radius; j <  radius; j += 0.1)
		{
			if ( pow(i, 2) + pow(j, 2) <= pow(radius, 2))
			put_pixel32_sk(surface, get_pos().x  + i, get_pos().y + j, 0, get_color(), get_cs());
		}
}

void one_v_func::draw(SDL_Surface *surface)
{
	for (double t = x1; t < x2; t += step)
		put_pixel32_sk(surface, get_pos().x + t, get_pos().y + func(t), 0, get_color(), get_cs());
}

void polar_func::draw(SDL_Surface *surface)
{
	for (double t = x1; t < x2; t += step)
		put_pixel32_sk(surface, get_pos().x + x_func(t), get_pos().y + y_func(t), 0, get_color(), get_cs());
}

void triangle::draw(SDL_Surface* surface)
{
	int minX, maxX, minY, maxY;
	minX = maxX = x0;
	minY = maxY = y0;
	if (minX > x1) minX = x1;
	else if (maxX < x1) maxX = x1;
	if (minX > x2) minX = x2;
	else if (maxX < x2) maxX = x2;
	if (minY > y1) minY = y1;
	else if (maxY < y1) maxY = y1;
	if (minY > y2) minY = y2;
	else if (maxY < y2) maxY = y2;
	for (int XtoMax = minX; XtoMax < maxX; XtoMax++)
		for (int YtoMax = minY; YtoMax < maxY; YtoMax++)
		{
			if (dotInTriangle(x0, y0, x1, y1, x2, y2, XtoMax, YtoMax))
				put_pixel32_sk(surface, XtoMax, YtoMax, 0, get_color(), get_cs());
		}

}

bool triangle::dotInTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int dx, int dy)
{
	int a = (x0 - dx) * (y1 - y0) - (x1 - x0) * (y0 - dy); //a = (x0 - dx) * (y1 - y0) * (z2 - z1) - (x1 - x0) * (y0 - dy) * (z2 - z1);  
	int b = (x1 - dx) * (y2 - y1) - (x2 - x1) * (y1 - dy); //b = (x1 - dx) * (y2 - y1) * (z0 - z2) - (x2 - x1) * (y1 - dy) * (z0 - z2);
	int c = (x2 - dx) * (y0 - y2) - (x0 - x2) * (y2 - dy); //c = (x2 - dx) * (y0 - y2) * (z1 - z0) - (x0 - x2) * (y2 - dy) * (z1 - z0);
	if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
		return true;
	else return false;
}


bool line::edgecmp(position v1, position v2) const
{
	if (   ((this->x0 == v1.x) || (this->x0 == v2.x))    // compare X positions
		&& ((this->x1 == v1.x) || (this->x1 == v2.x))

		&& ((this->y0 == v1.y) || (this->y0 == v2.y)) // compare Y positions
		&& ((this->y1 == v1.y) || (this->y1 == v2.y))

		&& ((this->z0 == v1.z) || (this->z0 == v2.z)) // compare Z positions
		&& ((this->z1 == v1.z) || (this->z1 == v2.z)))
		return true;
	return false;
}

void line::draw(SDL_Surface* surface)
{ 
	//int y01 = y0 / (2 * z0 + 1);
	//int z01 = z0 / (2 * z0 + 1);
	//int x01 = x0 / (2 * z0 + 1);
	//int y10 = y1 / (2 * z1 + 1);
	//int z10 = z1 / (2 * z1 + 1);
	//int x10 = x1 / (2 * z1 + 1);

	int x00 = y0 + x0;
	//x00 = x00 / (2 * z0 + 1);
	int y00 = z0 + x0;
	//y00 = y00 / (2 * z0 + 1);
	int x11 = y1 + x1;
	//x11 = x11 / (2 * z1 + 1);
	int y11 = z1 + x1;
	//y11 = y11 / (2 * z1 + 1);
	if (x11 < x00)
	{
		int temp = x11;
		x11 = x00;
		x00 = temp;
		int temp1 = y11;
		y11 = y00;
		y00 = temp1;
	}
	bool event = false;
	int delax = x00 - x11;
	int delay = y11 - y00;
	if (abs(delay) > abs(delax)) event = true;
	int evX = 1, evY = 1;
	if (delay < 0) evY = -1;
	if (delax < 0) evX = -1;
	int x = x00, y = y00, error = 0;
	put_pixel32_XY(surface, x, y, get_color(), get_cs());
	if (event == false)
	{
		do {
			error += delay * evY;
			if (error > 0)
			{
				error -= delax * evX;
				y += evY;
			}
			x -= evX;
			put_pixel32_XY(surface, x, y, get_color(), get_cs());
		} while (x != x11 || y != y11);
	}
	else
	{
		do {
			error += evX * delax;
			if (error > 0)
			{
				error -= evY * delay;
				x -= evX;
			}
			y += evY;
			put_pixel32_XY(surface, x, y, get_color(), get_cs());
		} while (x != x11 || y != y11);
	}
}

void draw_edge(SDL_Surface* surface, Vertex v1, Vertex v2, Uint32 basic_color = 0, double alpha = 0, double **sk = nullptr)
{
	int x00 = v1.y + v1.x;
	//x00 = x00 / (2 * z0 + 1);
	int y00 = v1.z + v1.x;
	//y00 = y00 / (2 * z0 + 1);
	int x11 = v2.y + v2.x;
	//x11 = x11 / (2 * z1 + 1);
	int y11 = v2.z + v2.x;
	//y11 = y11 / (2 * z1 + 1);
	if (x11 < x00)
	{
		int temp = x11;
		x11 = x00;
		x00 = temp;
		int temp1 = y11;
		y11 = y00;
		y00 = temp1;
	}
	bool event = false;
	int delax = x00 - x11;
	int delay = y11 - y00;
	if (abs(delay) > abs(delax)) event = true;
	int evX = 1, evY = 1;
	if (delay < 0) evY = -1;
	if (delax < 0) evX = -1;
	int x = x00, y = y00, error = 0;
	put_pixel32_XY(surface, x, y, basic_color, sk);
	if (event == false)
	{
		do {
			error += delay * evY;
			if (error > 0)
			{
				error -= delax * evX;
				y += evY;
			}
			x -= evX;
			put_pixel32_XY(surface, x, y, basic_color, sk);
		} while (x != x11 || y != y11);
	}
	else
	{
		do {
			error += evX * delax;
			if (error > 0)
			{
				error -= evY * delay;
				x -= evX;
			}
			y += evY;
			put_pixel32_XY(surface, x, y, basic_color, sk);
		} while (x != x11 || y != y11);
	}
}

layer::layer(Uint32 basic_color, double alpha)
{
	this->layer_basic_color = basic_color;
	this->layer_alpha = alpha;
	obj_number = 0;

	layer_coordinate_system = initialize_default_cs();
}

void layer::set_coordinate_system(double ** get_cs)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			layer_coordinate_system[i][j] = get_cs[i][j];
}

void layer::insert_object(graphic_object * new_obj)
{
	object_list.insert(object_list.end(), new_obj);
	obj_number++;
}

void layer::draw(SDL_Surface * surface)
{
	for (int i = 0; i < obj_number; i++)
		object_list[i]->draw(surface);
}

picture::picture(SDL_Surface *surface, Uint32 color, double alpha)
{
	this->surface = surface;
	this->global_basic_color = color;
	this->global_alpha = alpha;
	layers_number = 0;
	global_coordinate_system = initialize_default_cs();
}

void picture::set_cs(double ** get_cs)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			global_coordinate_system[i][j] = get_cs[i][j];
}

void picture::insert_layer(layer * new_layer)
{
	layers_list.insert(layers_list.end(), new_layer);
	layers_number++;
}

void picture::insert_object(graphic_object * new_obj, int n)
{
	layers_list[n]->insert_object(new_obj);
}

void picture::draw()
{
	for (int i = 0; i < layers_number; i++)
		layers_list[i]->draw(get_surf());
}

void lineal_object::insert_line(line* new_line)
{
	line_list.insert(line_list.end(), new_line);
	number_of_lines++;
}

bool polygon::orientation()
{
	double	x1 = (*v1).x + (*v1).y, x2 = (*v2).x + (*v2).y, x3 = (*v3).x + (*v3).y,
		y1 = (*v1).z + (*v1).x, y2 = (*v2).z + (*v2).x, y3 = (*v3).z + (*v3).x;

	double
	dx1 = x2 - x1,
	dx2 = x3 - x2,
	dy1 = y2 - y1,
	dy2 = y3 - y2,
	r = dx1 * dy2 - dx2 * dy1;

	//std::cout << "x1: " << x1 << std::endl;
	//std::cout << "y1: " << y1 << std::endl;
	//std::cout << "x2: " << x2 << std::endl;
	//std::cout << "y2: " << y2 << std::endl;
	//std::cout << "x3: " << x3 << std::endl;
	//std::cout << "y3: " << y3 << std::endl;
	//if (r > 0)
	//	std::cout << "Против часовой стрелки" << std::endl;
	//else if (r < 0)
	//	std::cout << "По часовой стрелке" << std::endl;
	//else
	//	std::cout << "Отрезки лежат на одной прямой" << std::endl;
	//std::cout << r << std::endl;
	if (r < 0) return false;
	return true;
}

void polygon::change_polygon(double **cs)
{
	change_xyz(&(*v1).x, &(*v1).y, &(*v1).z, cs);
	change_xyz(&(*v2).x, &(*v2).y, &(*v2).z, cs);
	change_xyz(&(*v3).x, &(*v3).y, &(*v3).z, cs);
	front = orientation();
}

void polygon::draw(SDL_Surface* surface)
{
	if (front)
	{
		draw_edge(surface, (*v1), (*v2), get_color(), alpha, get_cs());
		draw_edge(surface, (*v2), (*v3), get_color(), alpha, get_cs());
		draw_edge(surface, (*v3), (*v1), get_color(), alpha, get_cs());
		double	x1 = (*v1).x + (*v1).y, x2 = (*v2).x + (*v2).y, x3 = (*v3).x + (*v3).y,
			y1 = (*v1).z + (*v1).x, y2 = (*v2).z + (*v2).x, y3 = (*v3).z + (*v3).x;

		if(!wireframe) polygonDraw(surface, x1, y1, x2, y2, x3, y3, get_color(), get_cs());
	}
}

void polygonDraw(SDL_Surface* surface, int x0, int y0, int x1, int y1, int x2, int y2, UINT32 color, double** cs)
{
	int minX, maxX, minY, maxY;
	minX = maxX = x0;
	minY = maxY = y0;
	if (minX > x1) minX = x1;
	else if (maxX < x1) maxX = x1;
	if (minX > x2) minX = x2;
	else if (maxX < x2) maxX = x2;
	if (minY > y1) minY = y1;
	else if (maxY < y1) maxY = y1;
	if (minY > y2) minY = y2;
	else if (maxY < y2) maxY = y2;
	for (int XtoMax = minX; XtoMax < maxX; XtoMax++)
		for (int YtoMax = minY; YtoMax < maxY; YtoMax++)
		{
			if (dotInPoly(x0, y0, x1, y1, x2, y2, XtoMax, YtoMax))
				put_pixel32_XY(surface, XtoMax, YtoMax, color, cs);
		}
}

bool dotInPoly(int x0, int y0, int x1, int y1, int x2, int y2, int dx, int dy)
{
	int a = (x0 - dx) * (y1 - y0) - (x1 - x0) * (y0 - dy); //a = (x0 - dx) * (y1 - y0) * (z2 - z1) - (x1 - x0) * (y0 - dy) * (z2 - z1);  
	int b = (x1 - dx) * (y2 - y1) - (x2 - x1) * (y1 - dy); //b = (x1 - dx) * (y2 - y1) * (z0 - z2) - (x2 - x1) * (y1 - dy) * (z0 - z2);
	int c = (x2 - dx) * (y0 - y2) - (x0 - x2) * (y2 - dy); //c = (x2 - dx) * (y0 - y2) * (z1 - z0) - (x0 - x2) * (y2 - dy) * (z1 - z0);
	if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
		return true;
	else return false;
}