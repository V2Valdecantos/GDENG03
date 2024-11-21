#pragma once
#include "GraphicsEngine.h"
#include "SceneCameraHandler.h"
#include "GameObject.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"
#include "DeviceContext.h"
#include "Matrix4x4.h"
#include "PhysicsComponent.h"
#include "WICTextureLoader.h"
#include <string>

class Plane : GameObject
{
public:
    Plane(String name, RECT windowBounds);
    ~Plane();

    void init(ID3D11Device* device);
    void update(float deltaTime, RECT windowBounds) override;
    void draw(int width, int height, float deltaTime, VertexShader* vertexShader, PixelShader* pixelShader) override;
    void setAnimSpeed(float speed);
    //void updatePlanePosition(float m_delta_time, RECT windowBounds);
    bool release();

private:
    float ticks = 0.0f;
    float m_delta_pos = 0.0f;
    float m_delta_scale = 0.0f;
    float m_delta_rot = 0.0f;
    float m_speed = 1.0f;
    VertexBuffer* m_vb;
    ConstantBuffer* m_cb;
    IndexBuffer* m_ib;
    VertexShader* m_vs;
    PixelShader* m_ps;
    PhysicsComponent* phs;
};