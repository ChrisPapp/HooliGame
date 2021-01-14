#pragma once
#include <vector>
#include "Hooligan.h"
#include "Projectile.h"

#define DELTA_TIME (graphics::getDeltaTime() / 1000.f)

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