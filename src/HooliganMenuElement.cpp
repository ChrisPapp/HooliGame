#include <array>
#include "glm/vec3.hpp"
#include "Hooligan.h"
#include "Game.h"
#include "HooliganMenuElement.h"

static std::array<std::string, 4> textures = {
	std::string("red"),
	std::string("yellow"),
	std::string("green"),
	std::string("black"),
};

HooliganMenuElement::HooliganMenuElement(Hooligan &hool) :
hooligan(hool)
{
	selection = 0;
	this->draw = [this](glm::vec2 pos, bool sel) {return this->Draw(pos, sel); };
	this->on_select = [this]() {this->OnSelect(); };
	hooligan.SetTexture(textures[0]); // Default
}

void HooliganMenuElement::OnSelect()
{
	selection = selection < textures.size() - 1 ? ++selection : 0;
	hooligan.SetTexture(textures[selection]);
}

glm::vec2 HooliganMenuElement::Draw(glm::vec2 pos, bool selected)
{
#define HOOL_WIDTH 50.f
#define HOOL_HEIGHT 100.f
#define TEXT_SIZE 40.f
#define PADDING 5.f
	pos = GetGame()->DrawText(std::string("Change " + hooligan.GetName() + " color"), pos, TEXT_SIZE, selected ? glm::vec3(1.f) : glm::vec3(0.6f));
	// Hooligan accepts center coordinate, therefore move it a bit to the left and a bit down
	glm::vec2 hooligan_pos = pos + glm::vec2(HOOL_WIDTH, HOOL_HEIGHT / 1.7f);
	hooligan.DrawHooligan(hooligan_pos, HOOL_WIDTH, HOOL_HEIGHT);
	// Draw the keys to the right of the hooligan
	glm::vec2 keys_pos(pos.x + HOOL_WIDTH * 2.0f, pos.y + PADDING);
	keys_pos = GetGame()->DrawText(std::string("Move Up -> " + hooligan.GetKeyName(Hooligan::movement_keys::up)), keys_pos, TEXT_SIZE / 2.f, selected ? glm::vec3(1.f) : glm::vec3(0.6f));
	keys_pos = GetGame()->DrawText(std::string("Move Down -> " + hooligan.GetKeyName(Hooligan::movement_keys::down)), keys_pos, TEXT_SIZE / 2.f, selected ? glm::vec3(1.f) : glm::vec3(0.6f));
	keys_pos = GetGame()->DrawText(std::string("Move Left -> " + hooligan.GetKeyName(Hooligan::movement_keys::left)), keys_pos, TEXT_SIZE / 2.f, selected ? glm::vec3(1.f) : glm::vec3(0.6f));
	keys_pos = GetGame()->DrawText(std::string("Move Right -> " + hooligan.GetKeyName(Hooligan::movement_keys::right)), keys_pos, TEXT_SIZE / 2.f, selected ? glm::vec3(1.f) : glm::vec3(0.6f));
	keys_pos = GetGame()->DrawText(std::string("Throw Rock -> " + hooligan.GetKeyName(Hooligan::movement_keys::fire)), keys_pos, TEXT_SIZE / 2.f, selected ? glm::vec3(1.f) : glm::vec3(0.6f));

	// Advance actual position down, so the next menu element is drawn under the hooligan
	pos.y += HOOL_HEIGHT;
	return pos;
}