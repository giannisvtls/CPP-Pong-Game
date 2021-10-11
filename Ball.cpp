#include "Ball.h"
#include <graphics.h>

Ball::Ball(int x, int y, int movingSpeed)
{
	setX(x);
	setY(y);
	setSpeed(movingSpeed);
}

void Ball::update()
{
	this->x = this->x + movingSpeed;
	this->y = this->y + dir;

}

void Ball::draw()
{
	graphics::Brush br;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.outline_opacity = 0.0f;
	graphics::drawDisk(x, y, 4, br);
}

void Ball::init()
{
}

float Ball::getDir() const
{
	return dir;
}

int Ball::getX() const
{
	return x;
}

int Ball::getY() const
{
	return y;
}



int Ball::getSpeed() const
{
	return movingSpeed;
}

void Ball::setX(int x)
{
	this->x = x;
}

void Ball::setY(int y)
{
	this->y = y;
}

void Ball::setDir(float d)
{
	dir = d;
}

void Ball::setSpeed(int speed)
{
	movingSpeed = speed;
}
