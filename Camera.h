#pragma once
#pragma message ("Camera is defined")
#include "GameObject.h"
#include "InputListener.h"
#include "InputSystem.h"
#include "GraphicsEngine.h"
#include "EngineTime.h"
#include "ConstantBuffer.h"
#include "Structs.h"

class GameObject;
class Camera : public GameObject, public InputListener
{
	public:
		Camera();
		~Camera();

		void Update(float deltaTime, Matrix4x4 view, Matrix4x4 proj) override;
		void UpdateViewMatrix();
		bool isActive();
		void setActive(bool active);
		void draw(Window* window) override;
		
		void ToggleOrtho();
		Matrix4x4 getViewMatrix();
		Matrix4x4 getProjMatrix();

		void onKeyDown(int key) override;
		void onKeyUp(int key) override;

		//MOUSE pure virtual callback functions
		void onMouseMove(const Point& mouse_pos) override;

		void onLeftMouseDown(const Point& mouse_pos) override;
		void onLeftMouseUp(const Point& mouse_pos) override;

		void onRightMouseDown(const Point& mouse_pos) override;
		void onRightMouseUp(const Point& mouse_pos) override;

	private:
		bool active;
		bool isOrtho = false;
		Matrix4x4 viewMatrix;
		Matrix4x4 projMatrix;
		Matrix4x4 worldMatrix;
		float m_forward;
		float m_rightward;
};

