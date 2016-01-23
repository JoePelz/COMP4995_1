#include "Lines.h"



Lines::Lines() {
}


Lines::~Lines() {
}

int Lines::draw(LPDIRECT3DSURFACE9 pBackSurf) {
	HRESULT hr;
	D3DLOCKED_RECT LockedRect;//locked area of display memory(buffer really) we are drawing to
	DWORD* pData;

	int adx, ady;

	//lock the back buffer, so we can edit the pixels
	hr = pBackSurf->LockRect(&LockedRect, NULL, 0);
	if (FAILED(hr)) {
		Errors::SetError(TEXT("Lines::draw Could not lock the back buffer"));
	}
	pData = (DWORD*)(LockedRect.pBits);

	//line from (100, 100)
	//       to (200, 400)
	for (auto& line : lines) {
		adx = std::abs(line->dx);
		ady = std::abs(line->dy);

		/* TODO: clean this up by changing it to  x + t(vx) + y + t(vy) over the range t == 0..Max(adx, ady)
		*/
		if (ady >= adx) {
			for (int dy = 0; dy < ady; dy++) {
				pData[MAP((line->x + line->dx * dy / ady), (line->y + line->dy * dy / ady))] = D3DCOLOR_XRGB(192, 255, 0);
			}
		} else {
			for (int dx = 0; dx < adx; dx++) {
				pData[MAP((line->x + line->dx * dx / adx), (line->y + line->dy * dx / adx))] = D3DCOLOR_XRGB(192, 255, 0);
			}
		}
	}

	if (tempLine != NULL) {
		adx = std::abs(tempLine->dx);
		ady = std::abs(tempLine->dy);

		if (ady >= adx) {
			for (int dy = 0; dy < ady; dy++) {
				pData[MAP((tempLine->x + tempLine->dx * dy / ady), (tempLine->y + tempLine->dy * dy / ady))] = D3DCOLOR_XRGB(0, 192, 128);
			}
		} else {
			for (int dx = 0; dx < adx; dx++) {
				pData[MAP((tempLine->x + tempLine->dx * dx / adx), (tempLine->y + tempLine->dy * dx / adx))] = D3DCOLOR_XRGB(0, 192, 128);
			}
		}
	}

	pBackSurf->UnlockRect();
	pData = 0;

	return S_OK;
}

void Lines::startLine(int x, int y) {
	if (tempLine != NULL) {
		delete tempLine;
	}
	tempLine = new Line(x, y, x, y);
}

void Lines::dragLine(int x, int y) {
	if (tempLine == NULL) {
		Errors::SetError(TEXT("Lines::dragLine: tempLine is null."));
		return;
	}
	tempLine->dx = x - tempLine->x;
	tempLine->dy = y - tempLine->y;
}

void Lines::endLine() {
	if (tempLine == NULL) {
		Errors::SetError(TEXT("Lines::endLine: tempLine is null."));
		return;
	}
	std::shared_ptr<Line> l(tempLine);
	lines.push_back(l);
	tempLine = NULL;
}