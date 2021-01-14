#pragma once
#include "glm/vec2.hpp"

class Hooligan;

class Projectile : public Collidable
{
public:
	Projectile(glm::vec2 &pos, glm::vec2 &dir, Hooligan *source);

	void Draw();
	// Returns False if this projectile is no longer valid (e.g. out of range)
	bool Update();
	// Get pointer to the bad person who threw this.
	Hooligan *GetSource() { return source; };
	glm::vec2 &GetDirection() { return dir; };
private:
	float speed;
	graphics::Brush br;
	glm::vec2 dir;
	Hooligan *source;
	bool SetPosition(glm::vec2 &pos);
};