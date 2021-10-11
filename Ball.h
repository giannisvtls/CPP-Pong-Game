#pragma once
#include "Player.h"
#include <stdlib.h>
#include "gameobject.h"

class Ball : public GameObject{
public:
	Ball(int x, int y, int movingSpeed);
	void update() override;
	void draw() override;
	void init() override;
	float getDir() const;
	int getX() const;
	int getY() const;
	int getSpeed() const;
	void setX(int x);
	void setY(int y);
	void setDir(float dir);
	void setSpeed(int speed);
private:
	double x, y;
	double dir = 0;
	int movingSpeed;
};