#include "Controller.h"

//Static
long CALLBACK Controller::windowLoop(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	LPCREATESTRUCT cs;
	//Controller* ctrl;
	switch (uMessage) {
	case WM_CREATE:
	{
		//save the pointer to the controller class
		cs = (LPCREATESTRUCT)lParam;
		if ((LONG)cs->lpCreateParams) {
			SetClassLongPtr(hWnd, 0, (LONG)cs->lpCreateParams);
		}

		//ctrl = (Controller*)GetClassLongPtr(hWnd, 0);
		//ctrl->setHWnd(hWnd);
		
		return 0;
	}
	case WM_PAINT:
	{
		ValidateRect(hWnd, NULL);//basically saying - yeah we took care of any paint msg without any overhead
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
	{
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	}
}

int Controller::GameStartup() {
	if (FAILED(renderEngine.startEngine(hWnd, gameModel))) {
		Errors::SetError(TEXT("Initialization Failed"));
		GameShutdown();
		return E_FAIL;
	}

	Background* bg = new Background(renderEngine.getDevice());
	bg->setImage(TEXT(DEFAULT_BITMAP));
	std::shared_ptr<Drawable2D> drawable(bg);
	gameModel.addBG(drawable);

	return S_OK;
}

int Controller::GameLoop() {
	renderEngine.render(gameModel);

	if (GetAsyncKeyState(VK_ESCAPE))
		PostQuitMessage(0);

	return S_OK;
}

int Controller::GameShutdown() {
	renderEngine.stopEngine();
	return S_OK;
}

Controller::Controller(HINSTANCE hInstance)
	: hInstance(hInstance) {
}


Controller::~Controller() {
}

void Controller::setHWnd(const HWND newHWnd) {
	hWnd = newHWnd;
}