#include "Hooligan.h"
#include "Game.h"
#include "glm/glm.hpp"
#include "Config.h"

// Maximum canvas units per second per axis
#define MAX_SPEED 750.f
// Speed increase per second
#define ACCELERATION 2000.f
// Rate of fire (projectiles per second)
#define FIRE_RATE 4

#define INIT_LIVES 25

void Hooligan::Init(glm::vec2 face_dir, graphics::scancode_t up_key, graphics::scancode_t down_key,
	graphics::scancode_t left_key, graphics::scancode_t right_key, graphics::scancode_t fire_key)
{
	dir = glm::vec2(0, 0);
	bbox.half_dims = glm::vec2(25, 50);
	SetPosition(this->bounds.bbox.center);
	this->face_dir = face_dir;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 1.0f;
	heart_br.fill_color[0] = 1.0f;
	heart_br.fill_color[1] = 0.0f;
	heart_br.fill_color[2] = 0.0f;
	last_fire = graphics::getGlobalTime();
	keys[movement_keys::up] = up_key;
	keys[movement_keys::down] = down_key;
	keys[movement_keys::left] = left_key;
	keys[movement_keys::right] = right_key;
	keys[movement_keys::fire] = fire_key;
	lives = INIT_LIVES;
}

void Hooligan::Draw()
{
	DrawHooligan();
	DrawLives();
}

void Hooligan::DrawHooligan()
{
	graphics::drawRect(this->bbox.center.x, this->bbox.center.y, this->bbox.half_dims.x * 2, this->bbox.half_dims.y * 2, br);
}

void Hooligan::DrawLives()
{
	// Draw lives
	float width = 20.0f, height = 20.0f, margin = 10.0f;
	// Top left of player bounds
	glm::vec2 heart_pos((MIN_DIM(this->bounds.bbox, x) + width + margin), (MIN_DIM(this->bounds.bbox, y) + height + margin));
	for (int i = 0; i < lives; i++) {
		graphics::drawRect(heart_pos.x, heart_pos.y, width, height, heart_br);
		// Advance draw position
		heart_pos.x += (width + margin);
		if (heart_pos.x > MAX_DIM(this->bounds.bbox, x) - width - margin) { // Go down a row
			heart_pos.x = (MIN_DIM(this->bounds.bbox, x) + width + margin);
			heart_pos.y += (height + margin);
		}
	}
}

bool Hooligan::Update()
{
	if (lives <= 0)
		return false; // RIP...
	// Movement
	if (graphics::getKeyState(keys[movement_keys::up]) && !graphics::getKeyState(keys[movement_keys::down]))
		dir.y -= (ACCELERATION / MAX_SPEED) * GetDeltaSeconds();
	else if (graphics::getKeyState(keys[movement_keys::down]) && !graphics::getKeyState(keys[movement_keys::up]))
		dir.y += (ACCELERATION / MAX_SPEED) * GetDeltaSeconds();
	else
		signbit(dir.y) ? dir.y = glm::min(0.f, dir.y + (ACCELERATION / MAX_SPEED) * GetDeltaSeconds()) : dir.y = glm::max(0.f, dir.y - (ACCELERATION / MAX_SPEED) * GetDeltaSeconds());

	if (graphics::getKeyState(keys[movement_keys::left]) && !graphics::getKeyState(keys[movement_keys::right]))
		dir.x -= (ACCELERATION / MAX_SPEED) * GetDeltaSeconds();
	else if (graphics::getKeyState(keys[movement_keys::right]) && !graphics::getKeyState(keys[movement_keys::left]))
		dir.x += (ACCELERATION / MAX_SPEED) * GetDeltaSeconds();
	else
		signbit(dir.x) ? dir.x = glm::min(0.f, dir.x + (ACCELERATION / MAX_SPEED) * GetDeltaSeconds()) : dir.x = glm::max(0.f, dir.x - (ACCELERATION / MAX_SPEED) * GetDeltaSeconds());
	// Keep within [-1, 1]
	dir = glm::max(glm::min(glm::vec2(1.f), dir), glm::vec2(-1.f));
	SetPosition(this->bbox.center + GetDeltaSeconds() * MAX_SPEED * dir);


	// Fire
	if (graphics::getKeyState(keys[movement_keys::fire])) {
		Game *game = (Game *) graphics::getUserData();
		float current_time = graphics::getGlobalTime();
		if (current_time - last_fire > 1000.f / FIRE_RATE) {
			game->AddProjectile(Projectile(this->bbox.center, glm::vec2(face_dir.x, face_dir.y + dir.y), this));
			last_fire = current_time;
		}
	}
	return true;
}

void Hooligan::SetBounds(Collidable &&coll)
{
	this->bounds = coll;
	// Move to the center, to prevent being trapped out of bounds
	SetPosition(this->bounds.bbox.center);
}

void Hooligan::SetPosition(glm::vec2 &pos)
{
	glm::vec2 last = this->bbox.center;
	this->bbox.center = pos;
	if (this->bounds.Collide(*this) != CollisionType::Contains) {
		this->bbox.center = last;
		dir = glm::vec2(0);
	}
}

bool Hooligan::IsHit(Projectile &proj)
{
	// We cannot attack ourselves
	if (proj.GetSource() == this)
		return false;
	if (this->Collide(proj) == Outside)
		return false;
	dir += proj.GetDirection(); // Simulate being pushed back
	lives--;
	return true;
}
