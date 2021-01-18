#pragma once
#include <functional>
#include <vector>
#include "glm/vec2.hpp"
#include "graphics.h"

struct MenuElement {
	// Selectable element. Draw function is called when drawing it, on_select when selected.
	// pos is the position the last element was drawn on. You can use it to draw this element below the last.
	// sel is whether the cursor is above this element.
	MenuElement(std::function<glm::vec2(glm::vec2 pos, bool sel)> draw, std::function<void()> on_select);
	// Non-selectable element. The cursor will skip this element.
	MenuElement(std::function<glm::vec2(glm::vec2 pos)> draw);
	MenuElement() = default;
	std::function<glm::vec2(glm::vec2, bool)> draw;
	std::function<void()> on_select;
};

class Menu {
public:
	Menu(std::vector<MenuElement*> &&options, glm::vec2 &&start_coord);
	Menu() = default;
	virtual ~Menu();
	void Update();
	void Draw();
	void MoveCursor(bool up);

private:
	int curr_option;
	std::vector<MenuElement*> options;
	glm::vec2 start_coord;
	graphics::Brush br;
	float last_movement;
};