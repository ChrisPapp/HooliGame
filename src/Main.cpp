#include "graphics.h"
#include "Game.h"
#include "Config.h"

// The custom callback function that the library calls 
// to check for and set the current application state.
void update(float ms)
{
	Game *game = reinterpret_cast<Game *> (graphics::getUserData());
	game->Update();
}

// The window content drawing function.
void draw()
{
	Game *game = reinterpret_cast<Game *> (graphics::getUserData());
	game->Draw();
}

int main()
{
	Game game;
	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hooligame");
	graphics::setUserData(&game);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);
	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);
	graphics::Brush br;
	br.fill_color[0] = 0.0;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	graphics::setWindowBackground(br);
	game.Init();
	graphics::startMessageLoop();

	return 0;
}
