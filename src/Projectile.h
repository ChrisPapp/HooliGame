#pragma once
#include "glm/vec2.hpp"

class Projectile
{
public:
	Projectile(glm::vec2 &pos, glm::vec2 &dir);

	void Draw();
	// Returns False if this projectile is no longer valid (e.g. out of range)
	bool Update();

private:
	float width, height, speed;
	graphics::Brush br;
	glm::vec2 pos;
	glm::vec2 dir;
};