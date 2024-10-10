#pragma once

#include <iostream>
#include "AppWindow.h"
#include "ObjectManager.h"
#include "Quad.h"
#include "Circle.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Structs.h"

class AppWindow;

class Renderer
{
	public:
		Renderer();
		~Renderer();
		Renderer(AppWindow* window);
		void OnCreate();
		void OnUpdate();
		void OnDestroy();

		void BuildShaders();
		/*void SetSolidColor(vec3 color);*/
		void Draw();

	private:
		int vertexCount;
		size_t size_shader = 0;
		void* shader_byte_code = nullptr;

		SwapChain* m_swap_chain;
		VertexBuffer* m_vb;
		VertexShader* m_vs;
		PixelShader* m_ps;
		PixelShader* g_ps;
		std::vector<ID3D10ShaderResourceView*> textureSRV;
		ID3D10EffectShaderResourceVariable* pTextureSR;
		AppWindow* window;
};

