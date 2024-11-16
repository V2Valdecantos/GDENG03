#pragma once
#include "Window.h"

#include "GameObject.h"

#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Matrix4x4.h"

#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


#include "ObjectManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Cube.h"

#include "Component.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"




class GameObject;
class AppWindow : public Window, public InputListener
{
public:
	AppWindow();

	void update();

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;
	LRESULT CALLBACK WndProc(HWND windowHandle, UINT msg, WPARAM param, LPARAM lparam);

	bool LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	bool LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

private:
	SwapChain* m_swap_chain;
	//VertexBuffer* m_vb;
	//VertexShader* m_vs;
	//PixelShader* m_ps;
	ConstantBuffer* m_cb;
	//IndexBuffer* m_ib;
private:
	long m_old_delta;
	long m_new_delta;
	float m_delta_time;

	float m_delta_pos;
	float m_delta_scale;
	float m_delta_rot;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;

	float g_ResizeWidth = 0;
	float g_ResizeHeight = 0;
	ID3D11ShaderResourceView* logoTex;
	int logoWidth;
	int logoHeight;
	float my_color[4];

	bool isOrtho = false;
	bool credits_active = false;
	bool color_picker_active = false;
	bool show_demo_window = false;
	bool camera = true;
};
