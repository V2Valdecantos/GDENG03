#include "Renderer.h"

Renderer::Renderer()
{
	this->window = window;
	this->OnCreate();
	this->vertexCount = ObjectManager::getInstance()->getVertexList().size();
}

Renderer::~Renderer()
{
	this->OnDestroy();
}

Renderer::Renderer(AppWindow* window)
{
	this->window = window;
	this->OnCreate();
	this->vertexCount = ObjectManager::getInstance()->getVertexList().size();
}

void Renderer::OnCreate()
{
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->window->getClientWindowRect();
	m_swap_chain->init(this->window->getHWND(), rc.right - rc.left, rc.bottom - rc.top);

	//std::cout << "Objects: " << ObjectManager::getInstance()->getObjects().size() << std::endl;
	//std::cout << "Vertices: " << ObjectManager::getInstance()->getVertexList().size() << std::endl;
}

void Renderer::OnUpdate()
{

}

void Renderer::OnDestroy()
{
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}

void Renderer::BuildShaders()
{
	std::vector<vertex> vec_vert = ObjectManager::getInstance()->getVertexList();

	vertex* list = new vertex[ObjectManager::getInstance()->getVertexList().size()];
	std::copy(vec_vert.begin(), vec_vert.end(), list);

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ObjectManager::getInstance()->getVertexList().size();


	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

void Renderer::Draw()
{
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->window->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++)
	{
		ObjectManager::getInstance()->getObjects()[i]->Draw();
	}

	m_swap_chain->present(true);
}
