#pragma once

#include <Windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Errors.h"

class TextWriter {
	LPDIRECT3DSURFACE9 alphabet_;
	int width_;
	int height_;

	int TextWriter::LoadImageToSurface(LPDIRECT3DDEVICE9& device, const TCHAR* const pathname);
public:
	TextWriter(LPDIRECT3DDEVICE9& device, const TCHAR* path, int fontWidth, int fontHeight);
	~TextWriter();
};

