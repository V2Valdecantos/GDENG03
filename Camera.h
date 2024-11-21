#pragma once
#include "GameObject.h"
#include "InputSystem.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "DeviceContext.h"
#include "Matrix4x4.h"


class Camera : public GameObject, public InputListener
{
public:
	Camera(String name);
	~Camera();
public:
	Matrix4x4 getViewMatrix();
	void update(float deltaTime, RECT windowBounds) override;
	void draw(int width, int height, float deltaTime, VertexShader* vertexShader, PixelShader* pixelShader) override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point mouse_pos) override;

	virtual void onLeftMouseDown(const Point mouse_pos) override;
	virtual void onLeftMouseUp(const Point mouse_pos) override;

	virtual void onRightMouseDown(const Point mouse_pos) override;
	virtual void onRightMouseUp(const Point mouse_pos) override;

	bool release();

private:
	void updateViewMatrix();

private:

	float ticks = 0.0f;

	float mouseDown = false;

	float m_delta_pos = 0.0f;
	float m_delta_scale = 0.0f;
	float m_delta_rot = 0.0f;

	float m_rot_x = 0.0f;
	float m_rot_y = 0.0f;

	float m_scale_cube = 1;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;

	Matrix4x4 localMatrix;


};

