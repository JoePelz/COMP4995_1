#pragma once

#include "Defines.h"
#include "Drawable2D.h"
#include "Line.h"
#include "Errors.h"
#include <vector>
#include <memory>
#include <cstdlib>

class Lines :
	public Drawable2D {
	std::vector<std::shared_ptr<Line>> lines;
	Line* tempLine;
public:
	int draw(LPDIRECT3DSURFACE9 pBackSurf) const override;
	void startLine(int x, int y);
	void dragLine(int x, int y);
	void endLine();
	Lines();
	~Lines();
};

