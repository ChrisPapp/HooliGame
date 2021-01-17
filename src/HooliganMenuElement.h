#include "Menu.h"

struct HooliganMenuElement : MenuElement {
	HooliganMenuElement(Hooligan &hool);

	Hooligan &hooligan;
	int selection;

	void OnSelect();
	glm::vec2 Draw(glm::vec2 pos, bool selected);
};