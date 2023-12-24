#include "Graphics.h"

class Base_Container {
public:
	Base_Container(Graphics* gfx);
	Base_Container(int x, int y, int w, int h, Graphics* gfx);
	virtual void modifyPos(int x, int y);
	virtual void modifySize(int w, int h);
	virtual void draw() = 0;
protected:
	SDL_Rect rect;
	Graphics* gfx;
};

class Base_Clickable : public Base_Container {
public:
	Base_Clickable(Graphics* gfx);
	Base_Clickable(int x, int y, int w, int h, Graphics* gfx);

	virtual bool isHovering(int x, int y);
	virtual void click() = 0;
	virtual void draw() = 0;
	virtual bool checkClicked(int x, int y);

	virtual ~Base_Clickable() {};
protected:

};

class Base_Switch : public Base_Clickable {
public:
	Base_Switch(Graphics* gfx);
	Base_Switch(int x, int y, int w, int h, Graphics* gfx);
	void click();
	bool getState();
protected:
	bool switched = false;
};