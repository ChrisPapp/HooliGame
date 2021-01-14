#pragma once

#include <array>
#include "glm/vec2.hpp"
#include "graphics.h"


class Hooligan {
public:
	void Update();
	void Draw();
	void Init(graphics::scancode_t up_key, graphics::scancode_t down_key,
		graphics::scancode_t left_key, graphics::scancode_t right_key, graphics::scancode_t fire_key);
private:
	glm::vec2 pos;
	glm::vec2 dir;
	float width, height;
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
