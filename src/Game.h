#pragma once
#include "Hooligan.h"

class Game {
public:
	void update();
	void draw();
	void init();
private:
	Hooligan hool;
};