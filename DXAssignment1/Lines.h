#pragma once

#include "Defines.h"
#include "Drawable2D.h"
#include "Line.h"
#include "Errors.h"
#include <vector>
#include <memory>
#include <cstdlib>

/* This class stores and appends to a collection of lines. 
It includes an optional temporary line. */
class Lines : public Drawable2D {
	static D3DCOLOR colorTemp; //The color of the temporary drawing line
	static D3DCOLOR colorFinal; //The color of the final drawn lines
	std::vector<std::shared_ptr<Line>> lines; //collection of lines created
	Line* tempLine; //A temporary line to draw in a different color
public:
	//Draws all lines onto the given buffer, including the temp line if available.
	int draw(LPDIRECT3DSURFACE9 pBackSurf) override;
	//Create a new temporary line, starting at the given coordinates
	void startLine(int x, int y);
	//Move the endpoint of the temporary line, if it exists.
	void dragLine(int x, int y);
	//Freeze the new line into the collection.
	void endLine();
	Lines();
	~Lines();
};

