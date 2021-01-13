#pragma once
#include <vector>
#include "Hooligan.h"
#include "Projectile.h"

class Game {
public:
	void Update();
	void Draw();
	void Init();
	void AddProjectile(Projectile &&proj);
private:
	Hooligan hool;
	std::vector<Projectile> projectiles;
};