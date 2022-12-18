#include "stdafx.h"
#include "graphie.h"
#include <iostream>
#include"UserInput.h"
#include "draw.h"
#include <fstream>

using namespace std;


 UserInputValues input(UserInputValues in)
{
	
	switch (in.event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (in.event.button.button == SDL_BUTTON_LEFT) // Нажата левая клавиша мыши 
			in.motion_is_active = true;
		break;	
	case SDL_MOUSEBUTTONUP:
		if (in.event.button.button == SDL_BUTTON_LEFT) // Отпущена левая клавиша мыши
			in.motion_is_active = false;
		break;

	case SDL_KEYDOWN:
		if (in.event.key.keysym.sym == SDLK_w)
		{
			in.Rotate_Z = 0.05;
			//printf("%f\n", in.Rotate_Z);

			in.pic->get_layer(0)->get_object(2)->set_cs(create_sk(

				cos(in.Rotate_Z), -sin(in.Rotate_Z), 0, 0,
				sin(in.Rotate_Z), cos(in.Rotate_Z),  0, 0,
						0,					0,		 1, 0
			
			));
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->changeMesh();
	//		static_cast<polygon*>(in.pic->get_layer(0)->get_object(2))->change_polygon();
/*
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->delete_lines();
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->initialize();*/
		}
		if (in.event.key.keysym.sym == SDLK_s)
		{
			in.Rotate_Z = -0.05;
			//printf("%f\n", in.Rotate_Z);

			in.pic->get_layer(0)->get_object(2)->set_cs(create_sk(

				cos(in.Rotate_Z), -sin(in.Rotate_Z), 0, 0,
				sin(in.Rotate_Z), cos(in.Rotate_Z),  0, 0,
						0,				 0,			 1, 0
			
			));
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->changeMesh();
//			static_cast<polygon*>(in.pic->get_layer(0)->get_object(2))->change_polygon();
/*
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->delete_lines();
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->initialize();*/
		}
		if (in.event.key.keysym.sym == SDLK_a)
		{
			in.Rotate_X = -0.05;
			//printf("%f\n", in.Rotate_Z);

			in.pic->get_layer(0)->get_object(2)->set_cs(create_sk(

				1,		 0,					0,			 0,
				0, cos(in.Rotate_X), sin(in.Rotate_X),   0,
				0, -sin(in.Rotate_X), cos(in.Rotate_X),  0
			
			));
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->changeMesh();
	//		static_cast<polygon*>(in.pic->get_layer(0)->get_object(2))->change_polygon();
	
			//static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->delete_lines();
			//static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->initialize();
		}
		if (in.event.key.keysym.sym == SDLK_d)
		{
			in.Rotate_X = 0.05;
		//	printf("%f\n", in.Rotate_X);

			in.pic->get_layer(0)->get_object(2)->set_cs(create_sk(

				1,		 0,					0,			 0,
				0, cos(in.Rotate_X), sin(in.Rotate_X),   0,
				0, -sin(in.Rotate_X), cos(in.Rotate_X),  0
			
			));
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->changeMesh();
		//	static_cast<polygon*>(in.pic->get_layer(0)->get_object(2))->change_polygon();
/*
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->delete_lines();
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->initialize();*/
		}
		if (in.event.key.keysym.sym == SDLK_q)
		{
			in.Rotate_Y = -0.05;
		//	printf("%f\n", in.Rotate_Y);

			in.pic->get_layer(0)->get_object(2)->set_cs(create_sk(

				cos(in.Rotate_Y),  0, sin(in.Rotate_Y), 0,
				     	0,	       1,          0,       0,
				-sin(in.Rotate_X), 0, cos(in.Rotate_X), 0
			
			));
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->changeMesh();
//			static_cast<polygon*>(in.pic->get_layer(0)->get_object(2))->change_polygon();
/*
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->delete_lines();
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->initialize();*/
		}
		if (in.event.key.keysym.sym == SDLK_e)
		{
			in.Rotate_Y = +0.05;
		//	printf("%f\n", in.Rotate_Y);

			in.pic->get_layer(0)->get_object(2)->set_cs(create_sk(

				cos(in.Rotate_Y), 0, sin(in.Rotate_Y), 0,
				       0,         1,         0,        0,
				-sin(in.Rotate_X),0, cos(in.Rotate_X), 0
			
			));
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->changeMesh();
	//		static_cast<polygon*>(in.pic->get_layer(0)->get_object(2))->change_polygon();
/*
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->delete_lines();
			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->initialize();
		*/
		}
		if (in.event.key.keysym.sym == SDLK_z)
		{
			/*in.pic->get_layer(0)->get_object(2)->set_cs(create_sk(

				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 1

			)); */

			static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->viewingWireframe();
			//		static_cast<polygon*>(in.pic->get_layer(0)->get_object(2))->change_polygon();
		/*
					static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->delete_lines();
					static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->initialize();
				*/
		}
		break;
	case SDL_KEYUP:
		// Нажатие ESC

		if (in.event.key.keysym.sym == SDLK_ESCAPE)
		{
			in.returnCode = 0;
			return in;
		}
		// Нажатие стрелочки вправо
		if (in.event.key.keysym.sym == SDLK_RIGHT)
		{
			stair* str = static_cast<stair*>(in.pic->get_layer(0)->get_object(2));
			str->plusStep(1);
		}
		// Нажатие стрелочки влево
		if (in.event.key.keysym.sym == SDLK_LEFT)
		{
			stair* str = static_cast<stair*>(in.pic->get_layer(0)->get_object(2));
			str->plusStep(-1);
		}
		if (in.event.key.keysym.sym == SDLK_f)
		{
			CreateObj(static_cast<stair*>(in.pic->get_layer(0)->get_object(2)));
		}

		if (in.event.key.keysym.sym == SDLK_g)
		{
			GetObj((static_cast<stair*>(in.pic->get_layer(0)->get_object(2))), in);
			//static_cast<stair*>(in.pic->get_layer(0)->get_object(2))->initialize();
		}
		// Нажатие стрелочки вверх
		if (in.event.key.keysym.sym == SDLK_UP)
		{
			stair* str = static_cast<stair*>(in.pic->get_layer(0)->get_object(2));
			str->changeLength(1);
			//str->viewingWireframe();
		}
		// Нажатие стрелочки вниз
		if (in.event.key.keysym.sym == SDLK_DOWN)
		{
			stair* str = static_cast<stair*>(in.pic->get_layer(0)->get_object(2));
			str->changeLength(-1);
			
		}
		
		break;
	case SDL_QUIT:
		in.returnCode = 0;
		return in;
	}
	if (in.motion_is_active)
	{
		SDL_GetMouseState(&in.x, &in.y); // Получить координаты мыши
		in.pic->x_location = in.x - SCREEN_WIDTH / 2;
		in.pic->y_location = -in.y + SCREEN_HEIGHT / 2;
	}
	 return in;
 }

void CreateObj(stair* st)
 {
	cout << "Укажите путь и имя файла" << endl;
	string name;
	cin >> name;
	name += ".obj";
	 ofstream file(name, ios_base::out | ios_base::trunc);
	 if (!file.is_open()) // если файл небыл открыт
	 {
		 cout << "Файл не может быть открыт или создан\n"; // напечатать соответствующее сообщение
	 }
	 for (int i = (*st).polys.size() - 1; i >= 0; i--)
	 {
		 file << "v ";
		 file << (*st).polys[i]->v1->x << " ";
		 file << (*st).polys[i]->v1->y << " ";
		 file << (*st).polys[i]->v1->z << endl;

		 file << "v ";
		 file << (*st).polys[i]->v2->x << " ";
		 file << (*st).polys[i]->v2->y << " ";
		 file << (*st).polys[i]->v2->z << endl;

		 file << "v ";
		 file << (*st).polys[i]->v3->x << " ";
		 file << (*st).polys[i]->v3->y << " ";
		 file << (*st).polys[i]->v3->z << endl;
	 }

	 file << "g Stair" << endl;

	 for (int i = ((*st).polys.size()) * 3; i >= 1; i--)
	 {
		 file << "f ";
		 file << i << " ";
		 i--;
		 file << i << " ";
		 i--;
		 file << i << endl;
	 }
	 file.close();
 }

void GetObj(stair* st, UserInputValues in)
{
	st->vertexs.clear();
	st->polys.clear();
	cout << "Укажите путь и имя файла" << endl;
	string name;
	cin >> name;
	name += ".obj";
	ifstream file(name, ios_base::in);
	char buff[50];
	double location_x, location_y, location_z;
	int p1, p2, p3;
	if (!file.is_open()) // если файл небыл открыт
	{
		cout << "Файл не может быть открыт или создан\n"; // напечатать соответствующее сообщение
	}
	int count=0;
	while (!file.eof())
	{
		file >> buff; // считали первое слово из файла
		if (buff[0] == 'v') // переносим точки
		{
			file >> location_x;
			file >> location_y;
			file >> location_z;
			st->vertexs.push_back(new Vertex(location_x, location_y, location_z));
		}
		else if (buff[0] == 'f')  // переносим полигоны
		{
			count++;
			file >> p1;
			file >> p2;
			file >> p3;
			st->polys.push_back(new polygon(in.pic->get_surf(), st->vertexs[p3-1], st->vertexs[p2-1], st->vertexs[p1-1], 9541064-count*2));
		}
		else if (buff[0] == 'g')  // узнаем имя объекта
		{
			file >> buff;
		}
	}
	file.close(); // закрываем файл
}