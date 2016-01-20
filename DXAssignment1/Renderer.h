#pragma once

#include "Model.h"
#include "Errors.h"
#include "Defines.h"
#include <d3d9.h>
#include <d3dx9.h>


class Renderer {
	LPDIRECT3D9 pD3D; //COM object
	LPDIRECT3DDEVICE9 pDevice; //graphics device

	void Draw(int Pitch, DWORD* pData);

	// Set up the Direct3D display, with a specific width, height, fullscreen mode, and more.
	int InitDirect3DDevice(HWND hWndTarget, int Width, int Height, BOOL bWindowed, D3DFORMAT FullScreenFormat, LPDIRECT3D9 pD3D, LPDIRECT3DDEVICE9* ppDevice);

	// Handles 2D drawing on the background before the main 3D scene.
	void PreScene2D(Model&);

	// Render the 3D scene provided in Model
	void Scene3D(Model&);

	// Handles 2D drawing on the frame after the 3D work is complete.
	void PostScene2D(Model&);
public:
	Renderer();
	~Renderer();
	
	// Create the Direct3D COM object and initialize the device.
	int startEngine(HWND hwnd, Model& model);
	
	// Release the device context, and the Direct3D COM object.
	int stopEngine();

	/* Main rendering function, called directly on every frame.
	Engine::render delegates to PreScene2D, Scene3D, and PostScene2D to draw.
	*/
	int render(Model& model);

	LPDIRECT3DDEVICE9& getDevice();
};

