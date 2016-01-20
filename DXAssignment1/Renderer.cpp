#include "Renderer.h"


int Renderer::startEngine(HWND hwnd, Model& model) {
	HRESULT r = 0;//return values

	pD3D = Direct3DCreate9(D3D_SDK_VERSION);//COM object
	if (pD3D == NULL) {
		Errors::SetError(TEXT("Could not create IDirect3D9 object"));
		return E_FAIL;
	}

	//4th argument is TRUE or FALSE, where FALSE means fullscreen.
	r = InitDirect3DDevice(hwnd, model.getWidth(), model.getHeight(), WINDOWED_MODE, D3DFMT_X8R8G8B8, pD3D, &pDevice);
	if (FAILED(r)) {//FAILED is a macro that returns false if return value is a failure - safer than using value itself
		Errors::SetError(TEXT("Initialization of the device failed"));
		return E_FAIL;
	}

	return S_OK;
}

int Renderer::stopEngine() {
	if (pDevice)
		pDevice->Release();

	if (pD3D)
		pD3D->Release();

	return S_OK;
}

int Renderer::InitDirect3DDevice(HWND hWndTarget, int Width, int Height, BOOL bWindowed, D3DFORMAT FullScreenFormat, LPDIRECT3D9 pD3D, LPDIRECT3DDEVICE9* ppDevice) {
	D3DPRESENT_PARAMETERS d3dpp;//rendering info
	D3DDISPLAYMODE d3ddm;//current display mode info
	HRESULT r = 0;

	if (*ppDevice)
		(*ppDevice)->Release();

	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	r = pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
	if (FAILED(r)) {
		Errors::SetError(TEXT("Could not get display adapter information"));
		return E_FAIL;
	}

	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferFormat = bWindowed ? d3ddm.Format : FullScreenFormat;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//D3DSWAPEFFECT_COPY;
	d3dpp.hDeviceWindow = hWndTarget;
	d3dpp.Windowed = bWindowed;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = 0;//default refresh rate
	d3dpp.PresentationInterval = bWindowed ? 0 : D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	r = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWndTarget, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, ppDevice);
	if (FAILED(r)) {
		Errors::SetError(TEXT("Could not create the render device"));
		return E_FAIL;
	}

	return S_OK;
}

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

//Accessor for the render device
LPDIRECT3DDEVICE9& Renderer::getDevice() {
	return pDevice;
}

int Renderer::render(Model & model) {
	if (!pDevice) {
		Errors::SetError(TEXT("Cannot render because there is no device"));
		return E_FAIL;
	}

	PreScene2D(model);

	Scene3D(model);

	PostScene2D(model);

	pDevice->Present(NULL, NULL, NULL, NULL);//swap over buffer to primary surface
	return S_OK;
}

void Renderer::PreScene2D(Model& model) {
	HRESULT hr;
	LPDIRECT3DSURFACE9 pBackSurf = 0;

	//clear the display area with colour almost-black, ignore stencil buffer
	pDevice->Clear(0, 0, D3DCLEAR_TARGET, CLEAR_COLOR, 1.0f, 0);

	//get pointer to backbuffer
	hr = pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackSurf);
	if (FAILED(hr)) {
		Errors::SetError(TEXT("Couldn't get backbuffer"));
	}

	//draw BG elements
	for (auto d : model.getBG()) {
		d->draw(pBackSurf);
	}

	pBackSurf->Release();//release lock
	pBackSurf = 0;
}

void Renderer::Scene3D(Model& model) {
	//no 3d yet.
}

void Renderer::PostScene2D(Model& model) {
	HRESULT hr;
	LPDIRECT3DSURFACE9 pBackSurf = 0;

	//get the back buffer
	hr = pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackSurf);
	if (FAILED(hr)) {
		Errors::SetError(TEXT("PostScene2D: Couldn't get backbuffer"));
	}

	/*
	D3DLOCKED_RECT LockedRect;//locked area of display memory(buffer really) we are drawing to
	DWORD* pData;

	//lock the back buffer, so we can edit the pixels
	hr = pBackSurf->LockRect(&LockedRect, NULL, 0);
	if (FAILED(hr)) {
		Errors::SetError(TEXT("PostScene2D: Could not lock the back buffer"));
	}
	pData = (DWORD*)(LockedRect.pBits);
	//DRAW CODE GOES HERE - use pData
	Draw(LockedRect.Pitch, pData);

	//line from (100, 100)
	//       to (200, 400)
	for (int dy = 0; dy < 300; dy++) {
		pData[MAP2(100 + dy/3, (100 + dy))] = D3DCOLOR_XRGB(255, 0, 0);
	}

	pBackSurf->UnlockRect();
	pData = 0;

	*/


	//draw foreground elements
	for (auto d : model.getFG()) {
		d->draw(pBackSurf);
	}


	pBackSurf->Release();//release lock
	pBackSurf = 0;
}