#pragma once
#include "Player.h"
#include "Ball.h"
#include <vector> 

class Game
{
public:
	//Waits for user inputs
	void update();
	//Draws the UI
	void draw();
	void init();
	//Handles all the physics required to play the game
	void logic();
	float calculateDir(const Player * p);
	void toggleDebugMode();
	bool getDebugMode() const;
	Game();
	~Game();
private:
	bool debug_mode = false;
	std::vector<Player*> player;
	Ball* currentBall = nullptr;
	bool backtomenu = false;
	bool game_initialized = false;
	bool game_ended = false;
	float ballVy = 0.0;
};