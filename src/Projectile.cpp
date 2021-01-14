#include "glm/glm.hpp"
#include "graphics.h"
#include "Game.h"
#include "Projectile.h"
#include "Config.h"

Projectile::Projectile(glm::vec2 &pos, glm::vec2 &dir)
{
	this->pos = pos;
	this->dir = glm::normalize(dir);
	width = 20.f;
	height = 20.f;
	speed = 1300.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
}

void Projectile::Draw()
{
	graphics::drawRect(pos.x, pos.y, width, height, br);
}

bool Projectile::Update()
{
	return SetPosition(pos + speed * DELTA_TIME * dir);
}

bool Projectile::SetPosition(glm::vec2 &pos)
{
	// Ensure we are in bounds

	if (pos.x + width / 2 < 0 || pos.x - width / 2 > CANVAS_WIDTH ||
		pos.y + height / 2 < 0 || pos.y - height / 2 > CANVAS_HEIGHT) {
		return false;
	}
	this->pos = pos;
	return true;
}
