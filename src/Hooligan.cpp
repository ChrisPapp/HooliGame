#include "Hooligan.h"
#include "Game.h"
#include "glm/glm.hpp"
#include "Config.h"

// Maximum canvas units per second per axis
#define MAX_SPEED 750.f
// Speed increase per second
#define ACCELERATION 2000.f
// Rate of fire (projectiles per second)
#define FIRE_RATE 4

void Hooligan::Init(graphics::scancode_t up_key, graphics::scancode_t down_key,
	graphics::scancode_t left_key, graphics::scancode_t right_key, graphics::scancode_t fire_key)
{
	pos = glm::vec2(200, 250);
	dir = glm::vec2(0, 0);
	width = 50;
	height = 100;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 1.0f;
	last_fire = graphics::getGlobalTime();
	keys[movement_keys::up] = up_key;
	keys[movement_keys::down] = down_key;
	keys[movement_keys::left] = left_key;
	keys[movement_keys::right] = right_key;
	keys[movement_keys::fire] = fire_key;
}

void Hooligan::Draw()
{
	graphics::drawRect(pos.x, pos.y, width, height, br);
}

void Hooligan::Update()
{

	// Movement
	if (graphics::getKeyState(keys[movement_keys::up]) && !graphics::getKeyState(keys[movement_keys::down]))
		dir.y -= (ACCELERATION / MAX_SPEED) * DELTA_TIME;
	else if (graphics::getKeyState(keys[movement_keys::down]) && !graphics::getKeyState(keys[movement_keys::up]))
		dir.y += (ACCELERATION / MAX_SPEED) * DELTA_TIME;
	else
		signbit(dir.y) ? dir.y = glm::min(0.f, dir.y + (ACCELERATION / MAX_SPEED) * DELTA_TIME) : dir.y = glm::max(0.f, dir.y - (ACCELERATION / MAX_SPEED) * DELTA_TIME);

	if (graphics::getKeyState(keys[movement_keys::left]) && !graphics::getKeyState(keys[movement_keys::right]))
		dir.x -= (ACCELERATION / MAX_SPEED) * DELTA_TIME;
	else if (graphics::getKeyState(keys[movement_keys::right]) && !graphics::getKeyState(keys[movement_keys::left]))
		dir.x += (ACCELERATION / MAX_SPEED) * DELTA_TIME;
	else
		signbit(dir.x) ? dir.x = glm::min(0.f, dir.x + (ACCELERATION / MAX_SPEED) * DELTA_TIME) : dir.x = glm::max(0.f, dir.x - (ACCELERATION / MAX_SPEED) * DELTA_TIME);
	// Keep within [-1, 1]
	dir = glm::max(glm::min(glm::vec2(1.f), dir), glm::vec2(-1.f));
	SetPosition(pos + DELTA_TIME * MAX_SPEED * dir);


	// Fire
	if (graphics::getKeyState(keys[movement_keys::fire])) {
		Game *game = (Game *) graphics::getUserData();
		float current_time = graphics::getGlobalTime();
		if (current_time - last_fire > 1000.f / FIRE_RATE) {
			game->AddProjectile(Projectile(this->pos, glm::vec2(1.f /* Fire to the right */, dir.y)));
			last_fire = current_time;
		}
	}
}

void Hooligan::SetPosition(glm::vec2 &pos)
{
	// Ensure we are in bounds
	if (pos.x - width / 2 < 0 || pos.x + width / 2 > CANVAS_WIDTH) {
		dir.x = 0; // Simulate immediate stop
		pos.x = this->pos.x;
	}
	if (pos.y - height / 2 < 0 || pos.y + height / 2 > CANVAS_HEIGHT) {
		dir.y = 0; // Simulate immediate stop
		pos.y = this->pos.y;
	}
	this->pos = pos;
}
