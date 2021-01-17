#pragma once
#include <vector>
#include "Collidable.h"
#include "Hooligan.h"
#include "Projectile.h"
#include "Menu.h"

class Game {
	enum class State {
		Menu,
		InGame,
	};
public:
	void Update();
	void Draw();
	void Init();
	void AddProjectile(Projectile &&proj);
	void Resize(int x, int y);
	AABB &GetBounds() { return bounds; };
private:
	Hooligan hool1, hool2;
	std::vector<Projectile> projectiles;
	AABB bounds;
	State state;
	Menu menu;
	glm::vec2 DrawText(std::string &text, glm::vec2 &pos, float size, glm::vec3 &color);
	std::string GetAssetPath(std::string &asset);
	void SetupMenu();
	void PrepareGame();
};

float GetDeltaSeconds();
Game *GetGame();