#include "glm/vec2.hpp"

class Projectile
{
public:
	Projectile(glm::vec2 &pos, glm::vec2 &dir);

private:
	glm::vec2 pos;
	glm::vec2 dir;
};