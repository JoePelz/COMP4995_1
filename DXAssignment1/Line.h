#pragma once
struct Line {
	int x;
	int y;
	int dx;
	int dy;
	Line() { x = 0; y = 0; dx = 0; dy = 0; }
	Line(int x0, int y0, int x1, int y1) : x(x0), y(y0), dx(x1-x0), dy(y1-y0) {}
	~Line() {}
};

