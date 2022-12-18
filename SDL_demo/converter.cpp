#include "converter.h"
#include <fstream>

using namespace std;

converter::converter(stair* st)
{
	ofstream myfile;
	myfile.open("E:\example.txt");
	myfile << "Writing this to a file.\n";
	myfile.close();
	ofstream file("E:\stair.txt", ios_base::out | ios_base::trunc);
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

	for (int i = ((*st).polys.size() - 1) * 3; i >= 0; i--)
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
