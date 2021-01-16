#include <algorithm>
#include "Game.h"
#include "graphics.h"
#include "Config.h"

void Game::Init()
{
	// Faces right
	hool1.Init(glm::vec2(1.f, 0.f), graphics::SCANCODE_W, graphics::SCANCODE_S, graphics::SCANCODE_A, graphics::SCANCODE_D, graphics::SCANCODE_SPACE);
	// Faces left
	hool2.Init(glm::vec2(-1.f, 0.f), graphics::SCANCODE_I, graphics::SCANCODE_K, graphics::SCANCODE_J, graphics::SCANCODE_L, graphics::SCANCODE_P);
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
	float x_f = (float)x, y_f = (float)y;
	this->bounds = AABB(glm::vec2(x_f / 2, y_f / 2), x_f, y_f);
	
	// Hool1 moves to the left area of the screen
	hool1.SetBounds(Collidable(AABB(glm::vec2(x_f / 4, y_f / 2), x_f / 2, y_f)));
	// Hool2 moves to the right area of the screen
	hool2.SetBounds(Collidable(AABB(glm::vec2(3 * x_f / 4, y_f / 2), x_f / 2, y_f)));
}

float GetDeltaSeconds()
{ 
	return (graphics::getDeltaTime() / 1000.f); 
}

Game *GetGame()
{ 
	return reinterpret_cast<Game *> (graphics::getUserData()); 
}