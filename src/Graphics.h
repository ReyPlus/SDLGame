struct Color {
	Color(int r, int g, int b, int a = 255);
	int r, g, b, a;
	void update(int r, int g, int b, int a = 255);
};

class Graphics {
public:
	Graphics(struct SDL_Renderer*);
	void putPixel(int x, int y, const Color& c);
	void putLine(int x1, int y1, int x2, int y2, const Color& c);
private:
	struct SDL_Renderer* pen;
};