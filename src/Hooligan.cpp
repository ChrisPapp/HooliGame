#include "Hooligan.h"

void Hooligan::Init()
{
	pos = glm::vec2(200, 250);
	speed = glm::vec2(0, 0);
	width = 50;
	height = 100;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 1.0f;
}

void Hooligan::Draw()
{
	graphics::drawRect(pos.x, pos.y, width, height, br);
}

void Hooligan::Update()
{
	pos.x += 0.1;
}
