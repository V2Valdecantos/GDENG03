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
		Cube(string name, void* shaderByteCode, size_t sizeShader);
		~Cube();

		void update(float deltaTime) override;
		void draw(Window* window) override;
		void setAnimSpeed(float speed);

	private:
		SwapChain* m_swap_chain;
		VertexBuffer* m_vb;
		VertexShader* m_vs;
		PixelShader* m_ps;
		ConstantBuffer* m_cb;
		IndexBuffer* m_ib;
		CBData cbData;
		float ticks = 0.0f;
		float deltaPos = 0.0f;
		float deltaScale = 0.0f;
		float deltaTime = 0.0f;
		float speed = 10.0f;
};

