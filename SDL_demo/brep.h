#pragma once
#include "stdafx.h"
#include "graphie.h"
#include <vector>

//struct Vertex { double x, y, z; } typedef Vertex;

struct edge { Vertex v1, v2; } typedef edge;
struct triangle { Vertex v1, v2, v3; } typedef triangle;

class plane
{
	Vertex v1, position;
	std::vector<edge> edge_list;
	std::vector<Vertex> vertex_list;
	std::vector<Vertex> external_contour;
	std::vector<std::vector<Vertex>> internal_contours;
	unsigned int number_of_edges = 0;
	unsigned int number_of_vertexs = 0;
public:
	plane(Vertex v1, Vertex v2, Vertex v3);
	bool VertexOnThePlane(Vertex point, int tolerance) const;

	edge get_edge(unsigned int n) { return edge_list[n]; }
	void insert_edge(unsigned int Num_v1, unsigned int Num_v2);
	void delete_edge(unsigned int n) { edge_list.erase(edge_list.begin() + n); number_of_edges--; }
	void sp_insert_edge(unsigned int Num_v1, unsigned int Num_v2);
	int search_edge(Vertex *v1);
	unsigned int search_next_edge(edge current, Vertex *v1);
	
	Vertex get_Vertex(unsigned int n) { return vertex_list[n]; }
	void insert_Vertex(Vertex v1);
	void delete_Vertex(Vertex v1);
	Vertex find_smallestVertex();
	unsigned int created_vertex(Vertex v1);

	bool insert_triangle(Vertex triangle_v1, Vertex triangle_v2, Vertex triangle_v3, int tolerance);

	void create_conturs();
};

bool vertexcmp(Vertex v1, Vertex v2);
bool edgecmp(edge edge1, edge edge2);
bool OneMoreThanTwo(Vertex v1, Vertex v2);

void createBrep(std::vector<triangle> triangle_list); //должен принимать вектор треугольников