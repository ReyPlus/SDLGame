#include "Base_GUI.h"

//---------BASE_CONTAINER---------//
Base_Container::Base_Container(Graphics* gfx): gfx(gfx) { rect.x = 0; rect.y = 0; rect.w = 0; rect.h = 0; }
Base_Container::Base_Container(int x, int y, int w, int h, Graphics* gfx): gfx(gfx) { rect.x = x; rect.y = y; rect.w = w; rect.h = h; }
void Base_Container::modifyPos(int x, int y) { rect.x = x; rect.y = y; }
void Base_Container::modifySize(int w, int h) { rect.w = w; rect.h = h; }

//---------BASE_CLICKABLE---------//
Base_Clickable::Base_Clickable(Graphics* gfx) : Base_Container(gfx) {}
Base_Clickable::Base_Clickable(int x, int y, int w, int h, Graphics* gfx) : Base_Container(x, y, w, h, gfx) {}
bool Base_Clickable::isHovering(int x, int y) {	return (x <= rect.x + rect.w) && (x >= rect.x) && (y <= rect.y + rect.h) && (y >= rect.y); }

bool Base_Clickable::checkClicked(int x, int y) {
	static bool cond; cond = isHovering(x, y);
	if (cond) click();
	return cond;
}

//---------BASE_SWITCH---------//
Base_Switch::Base_Switch(Graphics* gfx) : Base_Clickable(gfx) {}
Base_Switch::Base_Switch(int x, int y, int w, int h, Graphics* gfx) : Base_Clickable(x, y, w, h, gfx) {}
void Base_Switch::click() { switched = !switched; }
bool Base_Switch::getState() { return switched; }

//---------BASE_BAR---------//
Base_Bar::Base_Bar(int x, int y, int w, int h, Graphics* gfx, double start, double min, double max, double step) : min(min), max(max), current(start), step(step), Base_Container(x, y, w, h, gfx) {}
Base_Bar::Base_Bar(Graphics* gfx, double start, double min, double max, double step) : min(min), max(max), current(start), step(step), Base_Container(gfx) {}

void Base_Bar::takeSteps(int steps) {
	current += steps * step;
	if (current > max) current = max;
	else if (current < min) current = min;
}

//---------BASE_SLIDER---------//
Base_Slider::Base_Slider(int x, int y, int w, int h, Graphics* gfx, double start, double min, double max, double step) : Base_Bar(x, y, w, h, gfx, start, min, max, step) {}
Base_Slider::Base_Slider(Graphics* gfx, double start, double min, double max, double step) : Base_Bar(gfx, start, min, max, step) {}

void Base_Slider::setCurrent(int x) {
	current = (double)x;
	if (current > max) current = max;
	else if (current < min) current = min;
}