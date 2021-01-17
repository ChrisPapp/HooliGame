#include <algorithm>
#include "Game.h"
#include "graphics.h"
#include "Config.h"
#include "glm/glm.hpp"

void Game::Init()
{
	SetupMenu();
}

void Game::Update()
{
	if (state == State::InGame) {
		if (!hool1.Update() || !hool2.Update()) {
			SetupMenu();
			return; // Game over
		}
		// Update projectiles and clean-up (remove invalid ones).
		projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [&](Projectile& proj)
		{
			return !proj.Update() || hool1.IsHit(proj) || hool2.IsHit(proj);
		}), projectiles.end());
	}
	else if (state == State::Menu) {
		menu.Update();
	}
}

void Game::Draw()
{
	if (state == State::InGame) {
		hool1.Draw();
		hool2.Draw();
		for (Projectile &proj : projectiles) {
			proj.Draw();
		}
	}
	else if (state == State::Menu) {
		menu.Draw();
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

glm::vec2 Game::DrawText(std::string &text, glm::vec2 &pos, float size, glm::vec3 &color)
{
	graphics::Brush br;
	br.fill_color[0] = color.x;
	br.fill_color[1] = color.y;
	br.fill_color[2] = color.z;
	// pos is top left, we want to convert it to bot left.
	// Add the text size to pos.y
	pos.y += size;
	graphics::drawText(pos.x, pos.y, size, text, br);
	return pos;
}

std::string Game::GetAssetPath(std::string &asset)
{
	return "assets/" + asset;
}

void Game::SetupMenu()
{
#define MENU_TEXT_SIZE 40.f
	graphics::setFont(GetAssetPath(std::string("PixelFont.otf")));
	state = State::Menu;
	this->menu = Menu({
		MenuElement(
			[&](glm::vec2 pos) {
				return DrawText(std::string("Hooligame"), pos, MENU_TEXT_SIZE, glm::vec3(0.f, 0.2f, 0.8f));
			}),
		MenuElement(
			[&](glm::vec2 pos, bool sel) {
				return DrawText(std::string("Start Game!"), pos, MENU_TEXT_SIZE, sel ? glm::vec3(1.f) : glm::vec3(0.6f)); 
			}, 
			[&]() { PrepareGame(); }),
		MenuElement(
			[&](glm::vec2 pos, bool sel) {
				return DrawText(std::string("Quit Game :("), pos, MENU_TEXT_SIZE, sel ? glm::vec3(1.f) : glm::vec3(0.6f));
			},
			[&]() { exit(0); }),
		}, glm::vec2(200, 200));
}

void Game::PrepareGame()
{
	// Faces right
	hool1.Init(glm::vec2(1.f, 0.f), graphics::SCANCODE_W, graphics::SCANCODE_S, graphics::SCANCODE_A, graphics::SCANCODE_D, graphics::SCANCODE_SPACE);
	// Faces left
	hool2.Init(glm::vec2(-1.f, 0.f), graphics::SCANCODE_I, graphics::SCANCODE_K, graphics::SCANCODE_J, graphics::SCANCODE_L, graphics::SCANCODE_P);

	this->state = State::InGame;
}

float GetDeltaSeconds()
{ 
	return (graphics::getDeltaTime() / 1000.f); 
}

Game *GetGame()
{ 
	return reinterpret_cast<Game *> (graphics::getUserData()); 
}
