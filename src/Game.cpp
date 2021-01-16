#include <algorithm>
#include "Game.h"
#include "graphics.h"
#include "Config.h"

void Game::Init()
{
	hool1.Init(graphics::SCANCODE_W, graphics::SCANCODE_S, graphics::SCANCODE_A, graphics::SCANCODE_D, graphics::SCANCODE_SPACE);
	hool2.Init(graphics::SCANCODE_I, graphics::SCANCODE_K, graphics::SCANCODE_J, graphics::SCANCODE_L, graphics::SCANCODE_P);
}

void Game::Update()
{
	if (!hool1.Update() || !hool2.Update())
		return; // Game over
	// Update projectiles and clean-up (remove invalid ones).
	projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [&](Projectile& proj)
	{
		return !proj.Update() || hool1.IsHit(proj) || hool2.IsHit(proj);
	}), projectiles.end());
}

void Game::Draw()
{

	hool1.Draw();
	hool2.Draw();
	for (Projectile &proj : projectiles) {
		proj.Draw();
	}
}

void Game::AddProjectile(Projectile &&proj)
{
	this->projectiles.push_back(proj);
}

void Game::Resize(int x, int y)
{
	this->bounds = AABB(glm::vec2((float)x / 2, (float)y / 2), (float)x, (float)y);
}

float GetDeltaSeconds()
{ 
	return (graphics::getDeltaTime() / 1000.f); 
}

Game *GetGame()
{ 
	return reinterpret_cast<Game *> (graphics::getUserData()); 
}