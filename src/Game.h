#pragma once
#include <vector>
#include "Collidable.h"
#include "Hooligan.h"
#include "Projectile.h"

class Game {
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
};

float GetDeltaSeconds();
Game *GetGame();