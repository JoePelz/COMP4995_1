#pragma once

#include <d3d9.h>

class Drawable2D {
public:
	virtual int draw(LPDIRECT3DSURFACE9 pBackSurf) const { OutputDebugString(TEXT("What happened?\n")); return S_OK; }

	Drawable2D() {
	}

	~Drawable2D() {
	}
};

