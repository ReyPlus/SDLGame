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

class Base_Bar : public Base_Container {
public:
	Base_Bar(int x, int y, int w, int h, Graphics* gfx, double start = 0.0, double min = 0.0, double max = 100.0, double step = 1.0);
	Base_Bar(Graphics* gfx, double start = 0.0, double min = 0.0, double max = 100.0, double step = 1.0);
	void takeSteps(int steps);
protected:
	double current = 0.0;
	double min = 0.0;
	double max = 100.0;
	double step = 1.0;
};

class Base_Slider : public Base_Bar {
public:
	Base_Slider(int x, int y, int w, int h, Graphics* gfx, double start = 0.0, double min = 0.0, double max = 100.0, double step = 1.0);
	Base_Slider(Graphics* gfx, double start = 0.0, double min = 0.0, double max = 100.0, double step = 1.0);
	void setCurrent(int x);
	virtual bool isDragged(int x, int y) = 0;
	virtual bool isClicked(int x, int y) = 0;
};