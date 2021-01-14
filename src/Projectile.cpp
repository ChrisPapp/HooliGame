#include "graphics.h"
#include "Projectile.h"

Projectile::Projectile(glm::vec2 &pos, glm::vec2 &dir)
{
	this->pos = pos;
	this->dir = dir;
	width = 20.f;
	height = 20.f;
	speed = 0.2f;
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
	pos += speed * dir;
	return true;
}
