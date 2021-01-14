#pragma once

#include <array>
#include "glm/vec2.hpp"
#include "graphics.h"
#include "Collidable.h"
#include "Projectile.h"

class Hooligan : public Collidable {
public:
	void Update();
	void Draw();
	void Init(graphics::scancode_t up_key, graphics::scancode_t down_key,
		graphics::scancode_t left_key, graphics::scancode_t right_key, graphics::scancode_t fire_key);
	bool IsHit(Projectile &proj);
private:
	glm::vec2 dir;
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
};
