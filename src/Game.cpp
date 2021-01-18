#include <algorithm>
#include <unordered_map>
#include "Game.h"
#include "graphics.h"
#include "Config.h"
#include "glm/glm.hpp"
#include "HooliganMenuElement.h"

void Game::Init()
{
	PrepareGame();
	SetupMenu();
}

Game::~Game()
{
	delete menu;
}

void Game::Update()
{
	if (state == State::InGame) {
		if (!hool1.Update()) {
			winner_name = hool2.GetName();
			SetupMenu();
			return; // Game over
		}
		if (!hool2.Update()) {
			winner_name = hool1.GetName();
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
		menu->Update();
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
		menu->Draw();
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

glm::vec2 Game::DrawText(std::string &&text, glm::vec2 &pos, float size, glm::vec3 &&color)
{
	std::string title = std::move(text);
	glm::vec3 col = color;
	return this->DrawText(title, pos, size, col);
}

std::string Game::GetAssetPath(std::string &asset)
{
	return this->GetAssetPath(asset);
}

std::string Game::GetAssetPath(std::string &&asset)
{
	return "assets/" + asset;
}

void Game::SetupMenu()
{
#define MENU_TEXT_SIZE 40.f
	graphics::setFont(GetAssetPath(std::string("PixelFont.otf")));
	state = State::Menu;
	delete menu;
	this->menu = new Menu({
		new MenuElement(
			[&](glm::vec2 pos) {
				return DrawText(winner_name.empty() ? std::string("Hooligame") : std::string(winner_name + " won!"), pos, MENU_TEXT_SIZE, glm::vec3(0.f, 0.2f, 0.4f));
			}),
		new MenuElement(
			[&](glm::vec2 pos, bool sel) {
				return DrawText(std::string("Start Game!"), pos, MENU_TEXT_SIZE, sel ? glm::vec3(1.f) : glm::vec3(0.6f));
			}, 
			[&]() { PrepareGame(); this->state = State::InGame; }),
		new HooliganMenuElement(hool1),
		new HooliganMenuElement(hool2),
		new MenuElement(
			[&](glm::vec2 pos, bool sel) {
				return DrawText(std::string("Quit Game :("), pos, MENU_TEXT_SIZE, sel ? glm::vec3(1.f) : glm::vec3(0.6f));
			},
			[&]() { exit(0); }),
		}, glm::vec2(200, 50));
}

void Game::PrepareGame()
{
	// Faces right
	hool1.Init("Hooligan 1", glm::vec2(1.f, 0.f), graphics::SCANCODE_W, graphics::SCANCODE_S, graphics::SCANCODE_A, graphics::SCANCODE_D, graphics::SCANCODE_SPACE);
	// Faces left
	hool2.Init("Hooligan 2", glm::vec2(-1.f, 0.f), graphics::SCANCODE_UP, graphics::SCANCODE_DOWN, graphics::SCANCODE_LEFT, graphics::SCANCODE_RIGHT, graphics::SCANCODE_P);
}

float GetDeltaSeconds()
{ 
	return (graphics::getDeltaTime() / 1000.f); 
}

Game *GetGame()
{ 
	return reinterpret_cast<Game *> (graphics::getUserData()); 
}

static std::unordered_map<graphics::scancode_t, std::string> keyNameMap = {
	{graphics::SCANCODE_W, std::string("W")},
	{graphics::SCANCODE_A, std::string("A")},
	{graphics::SCANCODE_S, std::string("S")},
	{graphics::SCANCODE_D, std::string("D")},
	{graphics::SCANCODE_UP, std::string("Up Arrow")},
	{graphics::SCANCODE_DOWN, std::string("Down Arrow")},
	{graphics::SCANCODE_LEFT, std::string("Left Arrow")},
	{graphics::SCANCODE_RIGHT, std::string("Right Arrow")},
	{graphics::SCANCODE_RETURN, std::string("Enter")},
	{graphics::SCANCODE_SPACE, std::string("Space")},
	{graphics::SCANCODE_P, std::string("P")},
};

std::string &ScancodeToText(graphics::scancode_t key)
{
	assert(keyNameMap.find(key) != keyNameMap.end());
	return keyNameMap[key];
}