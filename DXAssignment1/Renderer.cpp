#include "Renderer.h"

int Renderer::startEngine(HWND hwnd, Model& model) {
	HRESULT r = 0;//return values

	pD3D_ = Direct3DCreate9(D3D_SDK_VERSION);//COM object
	if (pD3D_ == NULL) {
		Errors::SetError(TEXT("Could not create IDirect3D9 object"));
		return E_FAIL;
	}

	//4th argument is TRUE or FALSE, where FALSE means fullscreen.
	r = InitDirect3DDevice(hwnd, model.getWidth(), model.getHeight(), WINDOWED_MODE, D3DFMT_X8R8G8B8, pD3D_, &pDevice_);
	if (FAILED(r)) {//FAILED is a macro that returns false if return value is a failure - safer than using value itself
		Errors::SetError(TEXT("Initialization of the device failed"));
		return E_FAIL;
	}

	r = pDevice_->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer_);
	if (FAILED(r)) {
		Errors::SetError(TEXT("Couldn't get backbuffer"));
	}

	return S_OK;
}

int Renderer::stopEngine() {
	if (pBackBuffer_) {
		pBackBuffer_->Release();//release lock
		pBackBuffer_ = 0;
	}
	if (pDevice_) {
		pDevice_->Release();
		pDevice_ = 0;
	}
	if (pD3D_) {
		pD3D_->Release();
		pD3D_ = 0;
	}
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

Renderer::Renderer() : pD3D_(0), pDevice_(0), pBackBuffer_(0) {
}

Renderer::~Renderer() {
	stopEngine();
}

//Accessor for the render device
LPDIRECT3DDEVICE9& Renderer::getDevice() {
	return pDevice_;
}

int Renderer::render(Model & model) {
	if (!pDevice_) {
		Errors::SetError(TEXT("Cannot render because there is no device"));
		return E_FAIL;
	}

	PreScene2D(model);

	//For future use...
	//Scene3D(model);

	PostScene2D(model);

	pDevice_->Present(NULL, NULL, NULL, NULL);//swap over buffer to primary surface
	return S_OK;
}

void Renderer::PreScene2D(Model& model) {
	//clear the display area with colour almost-black, ignore stencil buffer
	//pDevice->Clear(0, 0, D3DCLEAR_TARGET, CLEAR_COLOR, 1.0f, 0);

	//draw BG elements
	for (auto d : model.getBG()) {
		d->draw(pBackBuffer_);
	}
}

void Renderer::Scene3D(Model& model) {
	//no 3d yet.
}

void Renderer::PostScene2D(Model& model) {
	//draw foreground elements
	for (auto d : model.getFG()) {
		d->draw(pBackBuffer_);
	}
}