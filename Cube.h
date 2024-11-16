#pragma once
#include "GameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"

class Cube : public GameObject
{
	public:
		Cube(string name);
		Cube(string name, Vector3D color);
		~Cube();

		void Update(float deltaTime, Matrix4x4 view, Matrix4x4 proj) override;
		void draw(Window* window) override;
		void setAnimSpeed(float speed);

	private:

};

