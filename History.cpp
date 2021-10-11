#include "History.h"
#include <graphics.h>
#include "config.h"
#include "menu.h"
#include <iostream>
#include <fstream>

void History::update() {
    if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE)) {
        backtomenu2 = true;
    }
}

void History::draw() {

    graphics::Brush br;
    if (!backtomenu2) {

        graphics::setOrientation(0);
        br.texture = std::string(ASSET_PATH) + "history.png";
        br.outline_opacity = 0.0f;
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

        br.fill_color[0] = 0.0f;
        br.fill_color[1] = 0.0f;
        br.fill_color[2] = 0.0f;
        br.fill_opacity = 0.8f;

        //Draw middle box
        drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 7, 80, 50, br);
        drawRect(CANVAS_WIDTH / 2, 1.8 * CANVAS_HEIGHT / 3, 80, 350, br);

        //Draw P1 box
        drawRect(CANVAS_WIDTH / 3, CANVAS_HEIGHT / 7, 200, 50, br);
        drawRect(CANVAS_WIDTH / 3, 1.8 * CANVAS_HEIGHT / 3, 200, 350, br);

        //Draw P2 box
        drawRect(CANVAS_WIDTH - CANVAS_WIDTH / 3, CANVAS_HEIGHT / 7, 200, 50, br);
        drawRect(CANVAS_WIDTH - CANVAS_WIDTH / 3, 1.8 * CANVAS_HEIGHT / 3, 200, 350, br);

        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 1.0f;
        br.fill_color[2] = 1.0f;

        drawText(CANVAS_WIDTH / 2 - 30, 78, 20, "GAME", br);

        drawText(CANVAS_WIDTH / 3 - 50, 78, 20, "P1 SCORE", br);

        drawText(CANVAS_WIDTH - CANVAS_WIDTH / 3 - 50, 78, 20, "P2 SCORE", br);

        //Insert last 5 game scores in their respective box
        int x = 150;
        int y = 1;
        for (auto it = scores.rbegin(); it != scores.rend(); ++it) {
            if (y == 6) break;
            drawText(CANVAS_WIDTH / 2-5, x, 20, std::to_string(y), br);
            drawText(CANVAS_WIDTH / 3-10, x, 20, it->score1, br);
            drawText(CANVAS_WIDTH - CANVAS_WIDTH / 3-10, x, 20, it->score2, br);
            x += 50;
            y += 1;
        }
        
    }
}

void History::init() {
    graphics::setFont(std::string(ASSET_PATH) + "Aquatico.ttf");
    readScore();
}

void History::readScore()                   
{
    std::fstream myfile(std::string(ASSET_PATH) + "scores.txt");
    std::string line;
    
    //Store information from file in the struct, then add the struct in vector
    while (getline(myfile,line))
    {
        struct Players temp;
        myfile >> temp.name1;
        myfile >> temp.score1;
        myfile >> temp.name2;
        myfile >> temp.score2;
        scores.push_back({ temp.name1, temp.score1, temp.name2, temp.score2 });
    }
    myfile.close();
}

History::History()
{
    backtomenu2 = false;
}

History::~History()
{

}