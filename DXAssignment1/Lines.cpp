#include "Lines.h"



Lines::Lines() {
}


Lines::~Lines() {
}

int Lines::draw(LPDIRECT3DSURFACE9 pBackSurf) const {
	HRESULT hr;
	D3DLOCKED_RECT LockedRect;//locked area of display memory(buffer really) we are drawing to
	DWORD* pData;

	//lock the back buffer, so we can edit the pixels
	hr = pBackSurf->LockRect(&LockedRect, NULL, 0);
	if (FAILED(hr)) {
	Errors::SetError(TEXT("Lines::draw Could not lock the back buffer"));
	}
	pData = (DWORD*)(LockedRect.pBits);

	//line from (100, 100)
	//       to (200, 400)
	for (int dy = 0; dy < 300; dy++) {
	pData[MAP(100 + dy/3, (100 + dy))] = D3DCOLOR_XRGB(192, 255, 0);
	}

	pBackSurf->UnlockRect();
	pData = 0;

	return S_OK;
}