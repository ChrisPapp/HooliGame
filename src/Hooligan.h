#include "glm/vec2.hpp"
#include "graphics.h"

class Hooligan {
public:
	void update();
	void draw();
	void init();
private:
	glm::vec2 pos;
	glm::vec2 speed;
	float width;
	float height;
	graphics::Brush br;
};
