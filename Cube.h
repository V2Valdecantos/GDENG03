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

		void Update(float deltaTime, Matrix4x4 m_view) override;
		void draw(Window* window) override;
		void setAnimSpeed(float speed);

	private:
		VertexBuffer* m_vb;
		VertexShader* m_vs;
		ConstantBuffer* m_cb;
		PixelShader* m_ps;
		IndexBuffer* m_ib;
		CBData cbData;
		float ticks = 0.0f;
		float deltaPos = 0.0f;
		float deltaScale = 0.0f;
		float deltaTime = 0.0f;
		float speed = 10.0f;
};

