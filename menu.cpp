#include "menu.h"
#include <graphics.h>
#include "Game.h"
#include "config.h"

Menu::~Menu()
{
    delete mygame;
    delete myHistory;
}

void Menu::update()
{
    graphics::MouseState mouse;
    graphics::getMouseState(mouse);
    if (mouse.button_left_pressed && mouse.cur_pos_x > 510 && mouse.cur_pos_x < 770 && mouse.cur_pos_y > 135 && mouse.cur_pos_y < 200)
    {
        if (mainmenu) {
            if (mygame) delete mygame;
            mygame = new Game();
            mainmenu = false;
        }
    }

    if(mygame)
        mygame->update();

    if (mouse.button_left_pressed && mouse.cur_pos_x > 520 && mouse.cur_pos_x < 770 && mouse.cur_pos_y > 265 && mouse.cur_pos_y < 330)
    { 
        if (mainmenu) {
            myHistory = new History();
            myHistory->init();
            mainmenu = false;
        }
    }

    if (myHistory)
        myHistory->update();

    if (graphics::getKeyState(graphics::SCANCODE_BACKSPACE)) {
        if (mygame || myHistory)
        {
            mainmenu = true;
        }
    }
}

void Menu::draw()
{
    if(mainmenu){
        graphics::Brush br;

        graphics::setOrientation(0);
        br.texture = std::string(ASSET_PATH) + "menubg.png";
        br.outline_opacity = 0.0f;
        graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

        br.fill_color[0] = 0.0f;
        br.fill_color[1] = 0.0f;
        br.fill_color[2] = 0.0f;
        br.fill_opacity = 0.8f;
        drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 5, 200, 50, br);
        drawRect(CANVAS_WIDTH / 2, 2 * CANVAS_HEIGHT / 5, 200, 50, br);
        br.fill_color[0] = 1.0f;
        br.fill_color[1] = 1.0f;
        br.fill_color[2] = 1.0f;

        drawText(433, 108, 20, "START GAME!", br);
        drawText(457, 208, 20, "HISTORY", br);
    }
    if (mygame)
        mygame->draw();
    if (myHistory)
        myHistory->draw();
}

void Menu::init()
{
    graphics::setFont(std::string(ASSET_PATH) + "Aquatico.ttf");
}
