#include "Menu.h"
#include "graphics.h"
#include "scancodes.h"

#define OPTION_MARGIN 10

MenuElement::MenuElement(std::function<glm::vec2(glm::vec2, bool)> draw, std::function<void()> on_select)
{
	this->draw = draw;
	this->on_select = on_select;
}

MenuElement::MenuElement(std::function<glm::vec2(glm::vec2 pos)> draw)
{
	this->draw = [=](glm::vec2 pos, bool sel = false) { return draw(pos); };
}

Menu::Menu(std::vector<MenuElement*> &&options, glm::vec2 &start_coord)
{
	this->options = std::move(options);
	this->start_coord = start_coord;
	this->last_movement = graphics::getGlobalTime();

	// Select first selectable
	curr_option = 0;
	for (MenuElement *el : this->options) {
		if (el->on_select)
			break;
		curr_option++;
	}
}

Menu::~Menu()
{
	for (MenuElement *el : options) {
		delete el;
	}
}

void Menu::Draw()
{
	glm::vec2 coords = start_coord;
	for (int i = 0; i < options.size(); i ++) {
		glm::vec2 new_coords = options[i]->draw(coords, i == curr_option);
		coords.y = new_coords.y + OPTION_MARGIN;
	}
}

// Delay between menu movements, prevents moving too fast
#define DELAY 200.f
void Menu::Update()
{
	float time = graphics::getGlobalTime();
	// Do an action if enough time has passed
	if (time - last_movement > DELAY) {
		if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {
			assert(curr_option < options.size() && curr_option >= 0);
			assert(options[curr_option]->on_select);
			options[curr_option]->on_select();
			last_movement = time;
		}
		else if (graphics::getKeyState(graphics::SCANCODE_UP)) {
			MoveCursor(true);
			last_movement = time;
		}
		else if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
			MoveCursor(false);
			last_movement = time;
		}
	}
}

void Menu::MoveCursor(bool up)
{
	// Ensure target item is selectable. Wrap cursor around
	do {
		up ? curr_option-- : curr_option++;
		if (curr_option < 0 && up)
			curr_option = options.size() - 1;
		if (curr_option == options.size() && !up)
			curr_option = 0;
	} while (!options[curr_option]->on_select);
}
