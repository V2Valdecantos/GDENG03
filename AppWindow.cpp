#include "AppWindow.h"



AppWindow::AppWindow()
{
}

void AppWindow::update()
{
	CameraManager::getInstance()->Update();
	ObjectManager::getInstance()->Update(EngineTime::getDeltaTime());
}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::get()->addListener(this);
	InputSystem::get()->showCursor(false);

	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	m_world_cam.setTranslation(Vector3D(0, 0, -2));

	CBData cc;
	cc.m_time = 0;

	this->m_cb = GraphicsEngine::get()->createConstantBuffer();
	this->m_cb->load(&cc, sizeof(CBData));

	Camera* camera = new Camera();
	CameraManager::getInstance()->AddCamera(camera);



		Cube* cubeObject = new Cube("Cube");
		cubeObject->setAnimSpeed(rand() / float(RAND_MAX) * (0.35f - (-0.35f)) + -0.35f);
		cubeObject->setPosition(Vector3D(0, 0.5, 5));
		cubeObject->setScale(1, 1, 1);
		cubeObject->setRotation(0, 0, 0);
		ObjectManager::getInstance()->addObject(cubeObject);

		Cube* plane = new Cube("Cube", Vector3D(1, 1, 1));
		plane->setAnimSpeed(rand() / float(RAND_MAX) * (0.35f - (-0.35f)) + -0.35f);
		plane->setPosition(Vector3D(0, -0.2, 5));
		plane->setScale(10, 0, 10);
		plane->setRotation(0, 0, 0);
		ObjectManager::getInstance()->addObject(plane);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.7, 0.6f, 0.9f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);




	update();

	for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++) 
	{
		ObjectManager::getInstance()->getObjects()[i]->draw(this);
	}
	
	m_swap_chain->present(true);


	m_old_delta = m_new_delta;
	m_new_delta = ::GetTickCount();

	m_delta_time = (m_old_delta) ? ((m_new_delta - m_old_delta) / 1000.0f) : 0;
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	//m_vb->release();
	//m_ib->release();
	m_cb->release();
	m_swap_chain->release();
	//m_vs->release();
	//m_ps->release();
	GraphicsEngine::get()->release();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
	InputSystem::get()->addListener(CameraManager::getInstance()->GetActiveCamera());
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
	InputSystem::get()->removeListener(CameraManager::getInstance()->GetActiveCamera());
}

void AppWindow::onKeyDown(int key)
{
	//if (key == 'W')
	//{
	//	for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++)
	//	{
	//		ObjectManager::getInstance()->getObjects()[i]->addRotation(2 * EngineTime::getDeltaTime(), -2 * EngineTime::getDeltaTime(), 2 * EngineTime::getDeltaTime());
	//	}
	//}
	//else if (key == 'S')
	//{
	//	for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++)
	//	{
	//		ObjectManager::getInstance()->getObjects()[i]->addRotation(-2 * EngineTime::getDeltaTime(), 2 * EngineTime::getDeltaTime(), -2* EngineTime::getDeltaTime());
	//	}
	//}
	//else if (key == 'A')
	//{
	//	
	//	m_rightward = -1.0f;
	//}
	//else if (key == 'D')
	//{
	//	
	//	m_rightward = 1.0f;
	//}
	if (key == VK_LEFT) 
	{
		for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++) 
		{
			ObjectManager::getInstance()->getObjects()[i]->addRotation(0, -1 * EngineTime::getDeltaTime(), 0);
		}
	}
	else if (key == VK_RIGHT) 
	{
		for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++)
		{
			ObjectManager::getInstance()->getObjects()[i]->addRotation(0, 1 * EngineTime::getDeltaTime(), 0);
		}
	}
	else if (key == VK_UP)
	{
		for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++)
		{
			ObjectManager::getInstance()->getObjects()[i]->addRotation(-1 * EngineTime::getDeltaTime(), 0, 0);
		}
	}
	else if (key == VK_DOWN)
	{
		for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++)
		{
			ObjectManager::getInstance()->getObjects()[i]->addRotation(1 * EngineTime::getDeltaTime(), 0, 0);
		}
	}
}

void AppWindow::onKeyUp(int key)
{
	//m_forward = 0.0f;
	//m_rightward = 0.0f;

	//if (key == 'Q') {
	//	isOrtho = !isOrtho;
	//}
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	//int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	//int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);


	//if (!isOrtho)
	//{
	//	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * m_delta_time * 0.1f;
	//	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * m_delta_time * 0.1f;
	//}



	//InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));


}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{

}
void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{

}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{

}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{

}