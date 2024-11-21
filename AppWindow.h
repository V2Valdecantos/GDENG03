#pragma once
#include "Window.h"
#include "GameObject.h"
#include "Camera.h";
#include "Cube.h"
#include "Plane.h"
#include "list"
#include "InputSystem.h"
#include "InputListener.h"
#include "GraphicsEngine.h"
#include "SceneCameraHandler.h"
#include "UIManager.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "BaseComponentSystem.h"
#include <vector>

class AppWindow : public Window, public InputListener
{

public:
	static AppWindow* getInstance();
	static void initialize();
	static void destroy();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	//Inherited via InputSystem
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point mouse_pos) override;

	virtual void onLeftMouseDown(const Point mouse_pos) override;
	virtual void onLeftMouseUp(const Point mouse_pos) override;

	virtual void onRightMouseDown(const Point mouse_pos) override;
	virtual void onRightMouseUp(const Point mouse_pos) override;

	virtual void onFocus() override;
	virtual void onDefocus() override;

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&) {};
	AppWindow& operator =(AppWindow const&) {};
	static AppWindow* sharedInstance;

public:
	void spawnCube(int nCubeAmount);
	void spawnPlane();
	void initializeEngine();
	bool isRunning();

private:
	SwapChain* swapChain;
	std::vector<Cube*> cube_list;
	Cube* m_plane;

	bool bRunning = false;
	bool shouldRotate = false;

};
