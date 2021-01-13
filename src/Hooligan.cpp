#include "Hooligan.h"
#include "glm/glm.hpp"

#define SPEED_CAP 50.f
#define SPEED_MODIFIER 0.08f

void Hooligan::Init(graphics::scancode_t up_key, graphics::scancode_t down_key, graphics::scancode_t left_key, graphics::scancode_t right_key)
{
	pos = glm::vec2(200, 250);
	dir = glm::vec2(0, 0);
	width = 50;
	height = 100;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 1.0f;
	keys[movement_keys::up] = up_key;
	keys[movement_keys::down] = down_key;
	keys[movement_keys::left] = left_key;
	keys[movement_keys::right] = right_key;
}

void Hooligan::Draw()
{
	graphics::drawRect(pos.x, pos.y, width, height, br);
}

void Hooligan::Update()
{
	if (graphics::getKeyState(keys[movement_keys::up]) && !graphics::getKeyState(keys[movement_keys::down]))
		dir.y = glm::max(--dir.y, -SPEED_CAP);
	else if (graphics::getKeyState(keys[movement_keys::down]) && !graphics::getKeyState(keys[movement_keys::up]))
		dir.y = glm::min(++dir.y, SPEED_CAP);
	else
		dir.y = dir.y / 2.0f;

	if (graphics::getKeyState(keys[movement_keys::left]) && !graphics::getKeyState(keys[movement_keys::right]))
		dir.x = glm::max(--dir.x, -SPEED_CAP);
	else if (graphics::getKeyState(keys[movement_keys::right]) && !graphics::getKeyState(keys[movement_keys::left]))
		dir.x = glm::min(++dir.x, SPEED_CAP);
	else
		dir.x = dir.x / 2.0f;

	pos += SPEED_MODIFIER * dir;
}
