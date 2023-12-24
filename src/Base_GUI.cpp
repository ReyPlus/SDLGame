#include "Base_GUI.h"

Base_Container::Base_Container(Graphics* gfx): gfx(gfx) {
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

Base_Container::Base_Container(int x, int y, int w, int h, Graphics* gfx): gfx(gfx) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void Base_Container::modifyPos(int x, int y) {
	rect.x = x;
	rect.y = y;
}

void Base_Container::modifySize(int w, int h) {
	rect.w = w;
	rect.h = h;
}

Base_Clickable::Base_Clickable(Graphics* gfx) : Base_Container(gfx) {}
Base_Clickable::Base_Clickable(int x, int y, int w, int h, Graphics* gfx) : Base_Container(x, y, w, h, gfx) {}

bool Base_Clickable::isHovering(int x, int y) {
	return (x <= rect.x + rect.w) && (x >= rect.x) 
		&& (y <= rect.y + rect.h) && (y >= rect.y);
}

bool Base_Clickable::checkClicked(int x, int y) {
	static bool cond;
	cond = isHovering(x, y);
	if (cond) click();
	return cond;
}