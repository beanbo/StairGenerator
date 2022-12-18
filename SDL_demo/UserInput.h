#pragma once
void CreateObj(stair* st);
struct UserInputValues {

	SDL_Event event;
	bool motion_is_active = 0;
	picture* pic = nullptr;
	int x = 0;
	int y = 0;
	double Rotate_Z = 0;
	double Rotate_X = 0;
	double Rotate_Y = 0;
	int returnCode = 1;
	

} typedef UserInputValues;

UserInputValues input(UserInputValues in);

void GetObj(stair* st, UserInputValues in);