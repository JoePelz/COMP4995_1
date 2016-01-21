#include "TextWriter.h"



TextWriter::TextWriter(LPDIRECT3DDEVICE9& device, const TCHAR* path, int fontWidth, int fontHeight) 
: alphabet_(0), width_(fontWidth), height_(fontHeight) {
	LoadImageToSurface(device, path);
}


TextWriter::~TextWriter() {
	alphabet_->Release();
}

int TextWriter::LoadImageToSurface(LPDIRECT3DDEVICE9& device, const TCHAR* const pathname) {
	HRESULT r;
	HBITMAP hBitmap;
	BITMAP Bitmap;

	hBitmap = (HBITMAP)LoadImage(NULL, pathname, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hBitmap == NULL) {
		Errors::SetError(TEXT("Unable to load bitmap"));
		return E_FAIL;
	}

	GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
	DeleteObject(hBitmap);//we only needed it for the header info to create a D3D surface

	//create surface for bitmap
	r = device->CreateOffscreenPlainSurface(Bitmap.bmWidth, Bitmap.bmHeight, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &alphabet_, NULL);

	if (FAILED(r)) {
		Errors::SetError(TEXT("Unable to create surface for bitmap load"));
		return E_FAIL;
	}

	//load bitmap onto surface
	r = D3DXLoadSurfaceFromFile(alphabet_, NULL, NULL, pathname, NULL, D3DX_DEFAULT, 0, NULL);
	if (FAILED(r)) {
		Errors::SetError(TEXT("Unable to load file to surface"));
		return E_FAIL;
	}

	return S_OK;
}