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
	void Init(std::string name,glm::vec2 face_dir, graphics::scancode_t up_key, graphics::scancode_t down_key,
		graphics::scancode_t left_key, graphics::scancode_t right_key, graphics::scancode_t fire_key);
	bool IsHit(Projectile &proj);
	void SetBounds(Collidable &&coll);
	void SetPosition(glm::vec2 &pos);
	void DrawHooligan(glm::vec2 &pos, float width, float height);
	void SetTexture(std::string &texture_name);
	std::string &GetName() { return name; };
	enum movement_keys {
		up,
		down,
		left,
		right,
		fire,
		num_keys,
	};
	std::string &GetKeyName(enum movement_keys key);
private:
	glm::vec2 dir;
	glm::vec2 face_dir;
	graphics::Brush br, heart_br;

	std::string name;
	std::string texture_name;
	std::array<graphics::scancode_t, movement_keys::num_keys> keys;
	float last_fire;

	float lives;

	// Space where this player can move around
	Collidable bounds;

	void DrawLives();
};
