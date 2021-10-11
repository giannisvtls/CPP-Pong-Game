#pragma once
#include "Game.h"
#include "History.h" //added

class Menu 
{
	Game * mygame = nullptr;
	bool mainmenu = true;
	History* myHistory = nullptr; //added

public:
	~Menu();
	//Waiting input from the user
	void update();
	//Draw the starting menu
	void draw();
	void init();
};
