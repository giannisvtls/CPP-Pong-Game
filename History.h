#pragma once
#include <string>
#include <vector>

class History
{
public:
	History();
	~History();

	//"Static" screen so we only wait for user to press backspace and go back to menu
	void update();
	//Draw all the graphics for current screen
	void draw();
	//Initiate by automatically reading and storing the information
	void init();
	//Read the information from the .txt file
	void readScore();
private:
	//Struct has 4 variables since each game has P1, P2 and their respective scores
	struct Players { std::string name1; std::string score1; std::string name2; std::string score2; };
	//Vector contains information about each game
	std::vector<Players> scores;
	bool backtomenu2;
	bool statShown = false;
};