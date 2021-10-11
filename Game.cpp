#include "Game.h"
#include <graphics.h>
#include "math.h"
#include "config.h"
#include "menu.h"

using namespace std;

void Game::update()
{

    if (!game_initialized) {

        if (currentBall) {
            delete currentBall;
        }

        if ((player.empty())) {
            player.push_back(new Player(1, CANVAS_WIDTH / 5, CANVAS_HEIGHT / 2));
            player.push_back(new Player(2, 4 * CANVAS_WIDTH / 5, CANVAS_HEIGHT / 2));
        }
        
        currentBall = new Ball(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 4);
    }

    if (graphics::getKeyState(graphics::SCANCODE_F1)) {
        toggleDebugMode();
    }

    if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE)) {
        currentBall = nullptr;
        backtomenu = true;
        if(debug_mode==true) toggleDebugMode();
    }

    if (graphics::getKeyState(graphics::SCANCODE_SPACE) && !game_initialized) {
        currentBall->setDir(((double)rand() / (RAND_MAX)));
        game_initialized = true;
    }
    if (graphics::getKeyState(graphics::SCANCODE_SPACE) && game_ended) {
        for (auto p : player)
        {
            delete p;
        }
        player.clear();
        game_ended = false;
        game_initialized = false;
    }

    if (player.size() > 0)
    {
        for (auto p : player)
        {
            if (game_ended == false) {
                p->update();
                if (p->getScore() == 5)
                {
                    for (auto p : player)
                    {
                        p->writeScore();
                    }
                    game_ended = true;
                }
            }
        }
    }
    if (currentBall) {
        if (game_initialized) {
            currentBall->update();
            logic();
        }
    }
   
}
void Game::logic()
{
    for (auto p : player)
    {
        if (currentBall->getX() == p->getX() && currentBall->getY() >= p->getY() - p->getHeight() / 2 && currentBall->getY() <= p->getY() + p->getHeight() / 2) {
            graphics::playSound(std::string(ASSET_PATH) + "rackethit.mp3", 5, false);
            if (currentBall->getY() < p->getY() || currentBall->getY() > p->getY()) {
                ballVy = calculateDir(p);
                currentBall->setSpeed(-currentBall->getSpeed());
                currentBall->setDir(ballVy);
            }
            else {
                currentBall->setSpeed(-currentBall->getSpeed());
            }
        }
    }

    if (currentBall->getY() == 30 || currentBall->getY() == CANVAS_HEIGHT - 30) {
        currentBall->setDir(-currentBall->getDir());
    }
    

    if (currentBall->getX() < (*player.begin())->getX()) {
        (*player.rbegin())->updateScore();
        game_initialized = false;
        for (auto p : player)
        {
            p->setY(CANVAS_HEIGHT / 2);
        }
    }
    else if(currentBall->getX() > (*player. rbegin())->getX()){
        (*player.begin())->updateScore();
        game_initialized = false;
        for (auto p : player)
        {
            p->setY(CANVAS_HEIGHT / 2);
        }
    }

}

float Game::calculateDir(const Player * p)
{
    float relativeIntersect = (float)currentBall->getY() - (float)p->getY();
    float normalizedRelativeIntersectionY = (relativeIntersect / (float)(p->getHeight() / 2));
    float bounceAngle = normalizedRelativeIntersectionY * (float)((5 * 3.14) / 12);
    float ballVy = (float)sin(bounceAngle);
    return ballVy;
}

void Game::draw()
{
    graphics::Brush cr;

    if (!backtomenu) {
        cr.fill_color[0] = 0.0f;
        cr.fill_color[1] = 0.0f;
        cr.fill_color[2] = 0.0f;
        cr.outline_opacity = 0.0f;
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, cr);
        cr.fill_color[0] = 1.0f;
        cr.fill_color[1] = 1.0f;
        cr.fill_color[2] = 1.0f;
        cr.outline_opacity = 1.0f;

        graphics::drawLine(CANVAS_WIDTH / 5, 30, 4 * CANVAS_WIDTH / 5, 30, cr);
        graphics::drawLine(CANVAS_WIDTH / 5, CANVAS_HEIGHT - 30, 4 * CANVAS_WIDTH / 5, CANVAS_HEIGHT - 30, cr);

        if (!game_initialized) {
            graphics::resetPose();
            drawText(370, 110, 20, "Press space to start", cr);
        }

        if (game_ended) {
            for (auto p : player)
            {
                if (p->getScore() == 5)
                    drawText(420, 70, 20, "Player: " + std::to_string(p->getID()) + " wins!", cr);
            }
        }

        //start game
        if (player.size() > 0)
        {
            for (auto p : player)
            {
                p->draw();
            }
            currentBall->draw();
        }
    }

    if (getDebugMode() && player.size()>0 && currentBall) 
    {
        char info[100];
        sprintf_s(info, "(%6.2f, %6.2f, %6.2f,%6.2f)", currentBall->getDir(), (float)currentBall->getSpeed(), (float)(*player.begin())->getY(), (float)(*player.rbegin())->getY());
        graphics::drawText(20, 20, 10, info, cr);
    }
}

void Game::init()
{
}

void Game::toggleDebugMode()
{
    debug_mode = !debug_mode;
}

bool Game::getDebugMode() const
{
    return debug_mode;
}


Game::Game()
{
}

Game::~Game()
{
    if (!player.empty())
    {
        for (auto p : player)
        {
            delete p;
            player.clear();
        }
    }

    if (currentBall)
    {
        delete currentBall;
    }
}
