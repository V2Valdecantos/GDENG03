#include "AppWindow.h"


struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};


__declspec(align(16))
struct CBData
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_time;
};


AppWindow::AppWindow()
{
}

//void AppWindow::updateQuadPosition()
//{
//	CBData cc;
//	cc.m_time = ::GetTickCount();
//
//	m_delta_pos += m_delta_time / 10.0f;
//	if (m_delta_pos > 1.0f)
//		m_delta_pos = 0;
//
//
//	Matrix4x4 temp;
//
//	m_delta_scale += m_delta_time / 0.55f;
//
//	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
//	
//	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f,1.5f, 0), m_delta_pos));
//
//	//cc.m_world *= temp;
//
//	cc.m_world.setScale(Vector3D(1, 1, 1));
//
//	temp.setIdentity();
//	temp.setRotationZ(m_delta_scale);
//	cc.m_world *= temp;
//
//	temp.setIdentity();
//	temp.setRotationY(m_delta_scale);
//	cc.m_world *= temp;
//
//	temp.setIdentity();
//	temp.setRotationX(m_delta_scale);
//	cc.m_world *= temp;
//
//
//	cc.m_view.setIdentity();
//	cc.m_proj.setOrthoLH
//	(
//		(this->getClientWindowRect().right - this->getClientWindowRect().left)/300.0f,
//		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/300.0f,
//		-4.0f,
//		4.0f
//	);
//
//
//	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
//}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::get()->addListener(this);
	GraphicsEngine::get()->init();
	m_swap_chain=GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	//vertex vertex_list[] = 
	//{
	//	//X - Y - Z
	//	//FRONT FACE
	//	{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
	//	{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
	//	{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
	//	{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

	//	//BACK FACE
	//	{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
	//	{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
	//	{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
	//	{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	//};

	//m_vb=GraphicsEngine::get()->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(vertex_list);


	//unsigned int index_list[]=
	//{
	//	//FRONT SIDE
	//	0,1,2,  //FIRST TRIANGLE
	//	2,3,0,  //SECOND TRIANGLE
	//	//BACK SIDE
	//	4,5,6,
	//	6,7,4,
	//	//TOP SIDE
	//	1,6,5,
	//	5,2,1,
	//	//BOTTOM SIDE
	//	7,0,3,
	//	3,4,7,
	//	//RIGHT SIDE
	//	3,2,5,
	//	5,4,3,
	//	//LEFT SIDE
	//	7,6,1,
	//	1,0,7
	//};

	//
	//m_ib=GraphicsEngine::get()->createIndexBuffer();
	//UINT size_index_list = ARRAYSIZE(index_list);

	//m_ib->load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);

	for (int i = 0; i < 100; i++) {
		float x = rand() / float(RAND_MAX) * (0.75f - (-0.75f)) + -0.75f;
		float y = rand() / float(RAND_MAX) * (0.75f - (-0.75f)) + -0.75f;


		Cube* cubeObject = new Cube("Cube", shader_byte_code, size_shader);
		cubeObject->setAnimSpeed(rand() / float(RAND_MAX) * (0.35f - (-0.35f)) + -0.35f);
		cubeObject->setPosition(Vector3D(x, y, 0.0f));
		cubeObject->setScale(0.25f, 0.25f, 0.25f);
		cubeObject->setRotation(0, 0, 0);
		this->objectList.push_back(cubeObject);
	}

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0.5f, 0.5f, 1);

	RECT windowRect = this->getClientWindowRect();
	int width = windowRect.right - windowRect.left;
	int height = windowRect.bottom - windowRect.top;

	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(width, height);

	
	for (int i = 0; i < this->objectList.size(); i++) {
		this->objectList[i]->update(EngineTime::getDeltaTime());
		this->objectList[i]->draw(width, height, this->m_vs, this->m_ps);
	}

	m_swap_chain->present(true);

	std::cout << this->objectList[0]->getLocalPosition().m_y << std::endl;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//m_cb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onKeyDown(int key)
{
}

void AppWindow::onKeyUp(int key)
{
}
