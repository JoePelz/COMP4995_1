#pragma once
#include "Drawable2D.h"
#include "d3dx9.h"
#include "Errors.h"

class Background :
	public Drawable2D {
	LPDIRECT3DSURFACE9 background_;
	const LPDIRECT3DDEVICE9& device_;

	int LoadImageToSurface(const TCHAR* const pathname, LPDIRECT3DSURFACE9& surface) const;
public:
	Background(LPDIRECT3DDEVICE9& D3DDevice);
	~Background();
	virtual int draw(LPDIRECT3DSURFACE9 pBackSurf) override;
	int setImage(const TCHAR* path);
};

