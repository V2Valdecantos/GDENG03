#include "AppWindow.h"

AppWindow::AppWindow()
{
	Quad* quad1 = new Quad({ -0.75f, 0.25f, 0.0f });
	quad1->setScale(1.2f);
	Quad* quad2 = new Quad({ 0.25f, 0.25f, 0.0f });
	quad2->setScale(1.2f);
	Quad* quad3 = new Quad({ -0.25f, -0.5f, 0.0f });
	quad3->setScale(1.2f);
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain=GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	
	std::cout << "Objects: " << ObjectManager::getInstance()->getObjects().size() << std::endl;
	std::cout << "Vertices: " << ObjectManager::getInstance()->getVertexList().size() << std::endl;
	int vertex_count = ObjectManager::getInstance()->getObjects().size() * 4;
	std::vector<vertex> vec_vert = ObjectManager::getInstance()->getVertexList();

	vertex list[12];
	std::copy(vec_vert.begin(), vec_vert.end(), list);

	m_vb=GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs=GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	//RAINBOW PS
	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	//GREEN
	GraphicsEngine::get()->compilePixelShader(L"GreenPixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	g_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f,0.4f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(g_ps);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//// draw the rainbow quad and triangle
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(7, 0);

	////switch shaders and draw the quad
	//GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(g_ps);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(4, 7);
	 
	//int v_drawn = 0;
	//for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++) 
	//{
	//	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(ObjectManager::getInstance()->getObjects().at(i)->GetVertices().size(), v_drawn);
	//	v_drawn += int(ObjectManager::getInstance()->getObjects().at(i)->GetVertices().size());
	//}

	for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++) 
	{
		ObjectManager::getInstance()->getObjects()[i]->Draw();
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}
