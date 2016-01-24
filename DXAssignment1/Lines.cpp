#include "Lines.h"



Lines::Lines() {
}


Lines::~Lines() {
}

int Lines::draw(LPDIRECT3DSURFACE9 pBackSurf) {
	HRESULT hr;
	D3DLOCKED_RECT LockedRect;//locked area of display memory(buffer really) we are drawing to
	DWORD* pData;

	int dx, dy, sx, sy, err, e2, i, iend;

	//lock the back buffer, so we can edit the pixels
	hr = pBackSurf->LockRect(&LockedRect, NULL, 0);
	if (FAILED(hr)) {
		Errors::SetError(TEXT("Lines::draw Could not lock the back buffer"));
	}
	pData = (DWORD*)(LockedRect.pBits);

	//line from (100, 100)
	//       to (200, 400)
	for (auto& line : lines) {
		i = line->x + line->y * LockedRect.Pitch / 4; //starting point
		iend = i + line->dx + line->dy * LockedRect.Pitch / 4; //ending point
		dx = abs(line->dx);     // pixels travelled in x
		dy = abs(line->dy);     // pixels traveled in y
		sx = line->dx > 0 ? 1 : -1; // +1 if going right, -1 if going left or vertical
		sy = line->dy > 0 ? 1 : -1; // +1 if going up, -1 if going down or horizontal
		err = (dx>dy ? dx : -dy) / 2;// TODO: figure out what's going on.

		for (;;) {
			pData[i] = D3DCOLOR_XRGB(192, 255, 0);
			if (i == iend) //below the pixel assignment to ensure both endpoints get colored.
				break;
			e2 = err;
			if (e2 > -dx) { 
				err -= dy; 
				i += sx; 
			}
			if (e2 < dy) { 
				err += dx; 
				i += sy * LockedRect.Pitch / 4; 
			}
		}
	}

	if (tempLine != NULL) {
		i = tempLine->x + tempLine->y * LockedRect.Pitch / 4; //starting point
		iend = i + tempLine->dx + tempLine->dy * LockedRect.Pitch / 4; //ending point
		dx = abs(tempLine->dx);     // pixels travelled in x
		dy = abs(tempLine->dy);     // pixels traveled in y
		sx = tempLine->dx > 0 ? 1 : -1; // +1 if going right, -1 if going left or vertical
		sy = tempLine->dy > 0 ? 1 : -1; // +1 if going up, -1 if going down or horizontal
		err = (dx>dy ? dx : -dy) / 2;// TODO: figure out what's going on.

		for (;;) {
			pData[i] = D3DCOLOR_XRGB(160, 192, 0);
			if (i == iend) //below the pixel assignment to ensure both endpoints get colored.
				break;
			e2 = err;
			if (e2 > -dx) {
				err -= dy;
				i += sx;
			}
			if (e2 < dy) {
				err += dx;
				i += sy * LockedRect.Pitch / 4;
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