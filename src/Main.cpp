#include "graphics.h"
#include "Game.h"
#include "Config.h"

// The custom callback function that the library calls 
// to check for and set the current application state.
void update(float ms)
{
	GetGame()->Update();
}

// The window content drawing function.
void draw()
{
	GetGame()->Draw();
}

void resize(int x, int y)
{
	GetGame()->Resize(x, y);
}

int main()
{
	Game game;
	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hooligame");
	graphics::setUserData(&game);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	graphics::setResizeFunction(resize);
	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	graphics::Brush br;
	br.fill_color[0] = 0.1f;
	br.fill_color[1] = 0.1f;
	br.fill_color[2] = 0.1f;
	graphics::setWindowBackground(br);
	game.Init();
	graphics::startMessageLoop();

	return 0;
}
