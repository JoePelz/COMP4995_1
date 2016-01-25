#pragma once
/* Simple struct to hold a line by start point and delta x,y. */
struct Line {
	int x;
	int y;
	int dx;
	int dy;
	Line() { x = 0; y = 0; dx = 0; dy = 0; }
	/* ctor for lines, created from 2 points. */
	Line(int x0, int y0, int x1, int y1) : x(x0), y(y0), dx(x1-x0), dy(y1-y0) {}
	~Line() {}
};

