#include <array>
#include "glm/vec2.hpp"
#include "graphics.h"


class Hooligan {
public:
	void Update();
	void Draw();
	void Init(graphics::scancode_t up_key, graphics::scancode_t down_key, graphics::scancode_t left_key, graphics::scancode_t right_key);
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
		num_keys,
	};
	std::array<graphics::scancode_t, movement_keys::num_keys> keys;
};
