#include "glm/vec2.hpp"
#include "graphics.h"

class Hooligan {
public:
	void Update();
	void Draw();
	void Init();
private:
	glm::vec2 pos;
	glm::vec2 speed;
	float width;
	float height;
	graphics::Brush br;
};
