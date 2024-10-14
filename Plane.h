#pragma once
#include "GameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"
class Plane : public GameObject
{
public:
	Plane(string name, void* shaderByteCode, size_t sizeShader);
	~Plane();

	void update(float deltaTime) override;
	void draw(Window* window) override;

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;
	CBData cbData;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaScale = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
};

