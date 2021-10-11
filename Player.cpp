#include "player.h"
#include "graphics.h"
#include <fstream>
#include <iostream>
#include "config.h"

using namespace std;

Player::Player(){
	id = -1;
	x = -1;
	y = -1;
}
Player::Player(int id, int x, int y) {
	this->id = id;
	this->x = x;
	this->y = y;
}

void Player::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_W) && id == 1) //if input = W
	{
		this->y -= 2;
	}
	if (graphics::getKeyState(graphics::SCANCODE_S) && id == 1) //if input = S
	{
		this->y += 2;
	}
	if (graphics::getKeyState(graphics::SCANCODE_UP) && id == 2) //if input = ARROWUP
	{
		this->y -= 2;
	}
	if (graphics::getKeyState(graphics::SCANCODE_DOWN) && id == 2) //if input = ARROWDOWN
	{
		this->y += 2;
	}

	if (y < getHeight()) y = getHeight();
	if (y > CANVAS_HEIGHT - getHeight()) y = CANVAS_HEIGHT - getHeight();
}

void Player::draw()
{
	graphics::Brush br;

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.outline_opacity = 0.0f;
	graphics::drawRect(x, y, CANVAS_WIDTH/150, this->getHeight(), br);
	int width;
	if (getID() == 1) {
		width = 50;
	}
	else {
		width = CANVAS_WIDTH - 50;
	}
	graphics::drawText(width, CANVAS_HEIGHT/2, 20, to_string(getScore()), br);
}

void Player::writeScore() {

	fstream oFile(std::string(ASSET_PATH) + "scores.txt");
	oFile.seekg(0, ios::end);
	if (!oFile.is_open())
	{
		cout << "Failure" << endl;
		return;
	}
	oFile << endl;
	string text = "Player" + to_string(getID()) + " " + to_string(getScore());
	oFile << text;
	oFile.close();
}

void Player::init()
{
}

int Player::getHeight() const
{
	return this->height;
}

int Player::getX() const
{
	return this->x;
}

int Player::getY() const
{
	return this->y;
}

int Player::getID() const
{
	return id;
}

int Player::getScore() const
{
	return score;
}

void Player::setX(int x)
{
	this->x = x;
}

void Player::setY(int y)
{
	this->y = y;
}

void Player::setID(int id)
{
	this->id = id;
}

void Player::updateScore()
{
	this->score++;
}

void Player::resetScore()
{
	this->score = 0;
}
