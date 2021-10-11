#include "graphics.h"
#include "menu.h"
#include "config.h"
 
// The custom callback function that the library calls 
// to check for and set the current application state.
 
void update(float ms)
{
    Menu* menu = reinterpret_cast<Menu *> (graphics::getUserData());
    menu->update();
}

void draw()
{
    Menu* menu = reinterpret_cast<Menu *> (graphics::getUserData());
    menu->draw();
}

int main()
{
    Menu menu;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "A Simple Pong Game");
 
    graphics::setUserData(&menu);
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
    menu.init();
    graphics::startMessageLoop();
 
    return 0;
}
