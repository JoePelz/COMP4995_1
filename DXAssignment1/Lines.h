#pragma once

#include "Defines.h"
#include "Drawable2D.h"
#include "Line.h"
#include "Errors.h"
#include <vector>
#include <memory>

class Lines :
	public Drawable2D {
	std::vector<std::shared_ptr<Line>> lines;
public:
	int draw(LPDIRECT3DSURFACE9 pBackSurf) const override;
	Lines();
	~Lines();
};

