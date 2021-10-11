#pragma once
#include "gameobject.h"
#include "config.h"

class Player : public GameObject{
public:
	Player();
	Player(int id,int x, int y);
	void update() override;
	void draw() override;
	void init() override;
	int getHeight() const;
	int getX() const;
	int getY() const;
	int getID() const;
	int getScore() const;
	void setX(int x);
	void setY(int y);
	void setID(int id);
	void updateScore();
	void writeScore();
	void resetScore();
private:
	int id ,x, y;
	int score = 0;
	int height = CANVAS_HEIGHT / 8;
};
