#pragma once
#include "TextWriter.h"
#include "Model.h"
#include <sstream>

class FrameRate :
	public TextWriter {
	const Model* model_;
public:
	FrameRate(LPDIRECT3DDEVICE9& device, const TCHAR* path, int fontWidth, int fontHeight, Model* model);
	~FrameRate();
	virtual int draw(LPDIRECT3DSURFACE9 pBackSurf) override;
};

