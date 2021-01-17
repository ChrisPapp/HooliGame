#include "glm/glm.hpp"
#include "graphics.h"
#include "Game.h"
#include "Projectile.h"

Projectile::Projectile(glm::vec2 &pos, glm::vec2 &dir, Hooligan *source)
{
	this->bbox.center = pos;
	this->bbox.half_dims = glm::vec2(10, 10);
	this->dir = glm::normalize(dir);
	this->source = source;
	speed = 1300.0f;
	br.outline_opacity = 1.f;
	br.texture = GetGame()->GetAssetPath(std::string("yellow.png"));
}

void Projectile::Draw()
{
	graphics::drawRect(this->bbox.center.x, this->bbox.center.y, this->bbox.half_dims.x * 2, this->bbox.half_dims.y * 2, br);
}

bool Projectile::Update()
{
	return SetPosition(this->bbox.center + speed * GetDeltaSeconds() * dir);
}

bool Projectile::SetPosition(glm::vec2 &pos)
{
	// Ensure canvas contains this projectile
	if (Collidable(GetGame()->GetBounds()).Collide(*this) != Contains)
		return false;
	this->bbox.center = pos;
	return true;
}
