#include <algorithm>
#include "Game.h"
#include "graphics.h"
#include "Config.h"

void Game::Init()
{
	hool.Init(graphics::SCANCODE_W, graphics::SCANCODE_S, graphics::SCANCODE_A, graphics::SCANCODE_D);
}

void Game::Update()
{
	hool.Update();
	// Update projectiles and clean-up (remove invalid ones).
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile& proj)
	{
		return proj.Update();
	}), projectiles.end());
}

void Game::Draw()
{

	hool.Draw();
	for (Projectile &proj : projectiles) {
		proj.Update();
	}
}

void Game::AddProjectile(Projectile &&proj)
{
	this->projectiles.push_back(proj);
}