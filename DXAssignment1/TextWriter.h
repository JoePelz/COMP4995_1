#pragma once

#include <Windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "Errors.h"
#include "Drawable2D.h"

class TextWriter : public Drawable2D {
	LPDIRECT3DSURFACE9 alphabet_;
	int charWidth_;
	int charHeight_;
	int imgWidth_;
	int imgHeight_;
	int charsPerRow_;
	BOOL bTransparent_;
	D3DCOLOR colorKey_;
	std::string text_;
	int posx_;
	int posy_;

	int LoadImageToSurface(LPDIRECT3DDEVICE9& device, const TCHAR* const pathname);
	void PrintChar(int x, int y, char Character, DWORD* pDestData, int DestPitch) const;
public:
	TextWriter(LPDIRECT3DDEVICE9& device, const TCHAR* path, int fontWidth, int fontHeight);
	~TextWriter();
	void setTransparentColor(D3DCOLOR colorKey);
	void setText(const std::string& text);
	void setText(const std::string&& text);
	void setPosition(int x, int y);
	virtual int draw(LPDIRECT3DSURFACE9 pBackSurf) const;
};

