#pragma once

#include <array>
#include "glm/vec2.hpp"
#include "graphics.h"
#include "Collidable.h"
#include "Projectile.h"

class Hooligan : public Collidable {
public:
	// Returns true while this Hooligan is alive
	bool Update();
	void Draw();
	void Init(glm::vec2 face_dir, graphics::scancode_t up_key, graphics::scancode_t down_key,
		graphics::scancode_t left_key, graphics::scancode_t right_key, graphics::scancode_t fire_key);
	bool IsHit(Projectile &proj);
	void SetBounds(Collidable &&coll);
private:
	glm::vec2 dir;
	glm::vec2 face_dir;
	graphics::Brush br;

	enum movement_keys {
		up,
		down,
		left,
		right,
		fire,
		num_keys,
	};
	std::array<graphics::scancode_t, movement_keys::num_keys> keys;
	float last_fire;

	void SetPosition(glm::vec2 &pos);

	float lives;

	// Space where this player can move around
	Collidable bounds;
};
