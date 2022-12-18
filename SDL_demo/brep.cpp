#include "stdafx.h"
#include "brep.h"


plane::plane(Vertex v1, Vertex v2, Vertex v3)
{
	this->v1 = v1;
	position.x = (v2.y - v1.y) * (v3.z - v1.z) - (v2.z - v1.z) * (v3.y - v1.y);
	position.y = (v2.x - v1.x) * (v3.z - v1.z) - (v2.z - v1.z) * (v3.x - v1.x);
	position.z = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);

	insert_Vertex(v1);
	insert_Vertex(v2);
	insert_Vertex(v3);

	insert_edge(0, 1);
	insert_edge(1, 2);
	insert_edge(2, 0);
}

bool plane::VertexOnThePlane(Vertex point, int tolerance) const
{
	double plane = ((point.x - v1.x) * position.x - (point.y - v1.y) * position.y + (point.z - v1.z) * position.z);
	if ( plane >= -tolerance && plane <= tolerance)
		return true;
	else return false;
}

void plane::insert_edge(unsigned int Num_v1, unsigned int Num_v2)
{
	edge new_edge;
	new_edge.v1 = vertex_list[Num_v1];
	new_edge.v2 = vertex_list[Num_v2];
	edge_list.insert(edge_list.end(), new_edge);
	number_of_edges++;
}

void plane::sp_insert_edge(unsigned int Num_v1, unsigned int Num_v2)
{
	bool fl = false;
	unsigned int N_edge;
	edge tempEdge;	 tempEdge.v1 = vertex_list[Num_v1];	tempEdge.v2 = vertex_list[Num_v1];;

	for (N_edge = 0; N_edge < number_of_edges; N_edge++)
	{
		if (edgecmp(edge_list[N_edge], tempEdge))
		{
			delete_edge(N_edge);
			fl = true;
		}
	}
	if (fl == false)
		insert_edge(Num_v1, Num_v2);
}

int plane::search_edge(Vertex* v1)
{
	for (int N_edge = 0; N_edge < number_of_edges; N_edge++)
	{
		if (vertexcmp(*v1, edge_list[N_edge].v1))
		{
			*v1 = edge_list[N_edge].v2;
			return N_edge;
		}
		if (vertexcmp(*v1, edge_list[N_edge].v2))
		{
			*v1 = edge_list[N_edge].v1;
			return N_edge;
		}
	}
	return -1;
}

unsigned int plane::search_next_edge(edge current, Vertex* v1)
{
	for (int N_edge = 0; N_edge < number_of_edges; N_edge++)
	{
		if (vertexcmp(*v1, edge_list[N_edge].v1) && !edgecmp(current, edge_list[N_edge]))
		{
			*v1 = edge_list[N_edge].v2;
			return N_edge;
		}
		if (vertexcmp(*v1, edge_list[N_edge].v2) && !edgecmp(current, edge_list[N_edge]))
		{
			*v1 = edge_list[N_edge].v1;
			return N_edge;
		}
	}
	return -1;
}

void plane::insert_Vertex(Vertex v1)
{
	vertex_list.insert(vertex_list.end(), v1);
	number_of_vertexs++;
}

void plane::delete_Vertex(Vertex v1)
{
	for(int N_vertex = 0; N_vertex < number_of_vertexs; N_vertex++)
		if(vertexcmp(v1,vertex_list[N_vertex]))
			vertex_list.erase(vertex_list.begin() + N_vertex); 
	number_of_vertexs--;
}

Vertex plane::find_smallestVertex()
{
	Vertex smallest = vertex_list[0];
	for (int N_vertex = 1; N_vertex < number_of_vertexs; N_vertex++)
		if (OneMoreThanTwo(smallest, vertex_list[N_vertex]))
			smallest = vertex_list[N_vertex];
	return smallest;
}

unsigned int plane::created_vertex(Vertex v1)
{
	for (unsigned int n = 0; n < number_of_vertexs; n++)
		if (vertexcmp(v1, vertex_list[n])) return n;
	insert_Vertex(v1);
	return number_of_vertexs-1;
}

bool plane::insert_triangle(Vertex triangle_v1, Vertex triangle_v2, Vertex triangle_v3, int tolerance)
{
	if (VertexOnThePlane(triangle_v1, tolerance) && VertexOnThePlane(triangle_v2, tolerance) && VertexOnThePlane(triangle_v3, tolerance))
	{
		unsigned int createdV1 = created_vertex(triangle_v1);
		unsigned int createdV2 = created_vertex(triangle_v2);
		unsigned int createdV3 = created_vertex(triangle_v3);

		sp_insert_edge(createdV1, createdV2);
		sp_insert_edge(createdV2, createdV3);
		sp_insert_edge(createdV3, createdV1);
		return true;
	}
	else return false;
}

void plane::create_conturs()
{						// create external contour
	Vertex firstPoint = find_smallestVertex();
	external_contour.insert(external_contour.end(), firstPoint);
	delete_Vertex(firstPoint);
	Vertex point = firstPoint;
	int N_edge = search_edge(&point);
	do
	{
		external_contour.insert(external_contour.end(), point);
		delete_Vertex(point);
		N_edge = search_next_edge(edge_list[N_edge], &point);
	} while (!vertexcmp(point,firstPoint));

	while (!vertex_list.empty()) // if vector isn't empty
	{							// Create internal contours
		std::vector<Vertex> internal_contour;
		do
		{
			firstPoint = vertex_list[0];
			internal_contour.insert(internal_contour.end(), firstPoint);
			delete_Vertex(firstPoint);
			point = firstPoint;
			N_edge = search_edge(&point);
		} while (N_edge < 0);
		do
		{
			internal_contour.insert(internal_contour.end(), point);
			delete_Vertex(point);
			N_edge = search_next_edge(edge_list[N_edge], &point);
		} while (!vertexcmp(point, firstPoint));
		if (!internal_contour.empty()) internal_contours.insert(internal_contours.end(), internal_contour);
	}
}

bool vertexcmp(Vertex v1, Vertex v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return true;
	else return false;
}

bool edgecmp(edge edge1, edge edge2)
{
	if ((vertexcmp(edge1.v1, edge2.v1) && vertexcmp(edge1.v1, edge2.v2)) || (vertexcmp(edge1.v2, edge2.v1) && vertexcmp(edge1.v1, edge2.v2)))
		return true;
	return false;
}

bool OneMoreThanTwo(Vertex v1, Vertex v2)
{
	if ((v1.x + v1.y + v1.z) > (v2.x + v2.y + v2.z)) return true;
	else return false;
}
