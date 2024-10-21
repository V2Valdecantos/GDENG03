#include "AppWindow.h"
#include <Windows.h>
#include "Vector3D.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "GameObject.h"
#include "Cube.h"
#include "ObjectManager.h"


AppWindow::AppWindow()
{
}

void AppWindow::update()
{
	CBData cc;
	cc.m_time = ::GetTickCount();

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;


	Matrix4x4 temp;

	m_delta_scale += m_delta_time / 0.55f;

	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));

	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f,1.5f, 0), m_delta_pos));

	//cc.m_world *= temp;

	/*cc.m_world.setScale(Vector3D(m_scale_cube, m_scale_cube, m_scale_cube));

	temp.setIdentity();
	temp.setRotationZ(0.0f);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	cc.m_world *= temp;

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	cc.m_world *= temp;*/

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;


	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;


	world_cam.inverse();




	cc.m_view = world_cam;
	/*cc.m_proj.setOrthoLH
	(
		(this->getClientWindowRect().right - this->getClientWindowRect().left)/300.0f,
		(this->getClientWindowRect().bottom - this->getClientWindowRect().top)/300.0f,
		-4.0f,
		4.0f
	);*/




	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);


	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);


	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
	ObjectManager::getInstance()->Update(EngineTime::getDeltaTime(), cc.m_view);
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


	//Cube* cubeObject = new Cube("Cube1");
	//cubeObject->setAnimSpeed(rand() / float(RAND_MAX) * (0.35f - (-0.35f)) + -0.35f);
	//cubeObject->setPosition(Vector3D(0, 0.9, 0));
	//cubeObject->setScale(1, 1, 1);
	//cubeObject->setRotation(0, 0, 0);
	//ObjectManager::getInstance()->addObject(cubeObject);

	//Cube* cubeObject2 = new Cube("Cube");
	//cubeObject2->setAnimSpeed(rand() / float(RAND_MAX) * (0.35f - (-0.35f)) + -0.35f);
	//cubeObject2->setPosition(Vector3D(- 1.5, 2.0, 1));
	//cubeObject2->setScale(1, 1, 1);
	//cubeObject2->setRotation(0, 0, 0);
	//ObjectManager::getInstance()->addObject(cubeObject2);

	//Cube* cubeObject3 = new Cube("Cube3");
	//cubeObject3->setAnimSpeed(rand() / float(RAND_MAX) * (0.35f - (-0.35f)) + -0.35f);
	//cubeObject3->setPosition(Vector3D(-1.5, 3, -2));
	//cubeObject3->setScale(1, 1, 1);
	//cubeObject3->setRotation(0, 0, 0);
	//ObjectManager::getInstance()->addObject(cubeObject3);

	/* 15 CARDS */
	for (int i = 0; i < 15; i++) {
		/*float x = rand() / float(RAND_MAX) * (0.75f - (-0.75f)) + -0.75f;
		float y = rand() / float(RAND_MAX) * (0.75f - (-0.75f)) + -0.75f;*/


		Cube* cubeObject = new Cube("Cube");
		cubeObject->setAnimSpeed(rand() / float(RAND_MAX) * (0.35f - (-0.35f)) + -0.35f);
		cubeObject->setPosition(Vector3D(10, 10, 0));
		cubeObject->setScale(0.01, 1.5, 1);
		cubeObject->setRotation(0, 0, 0);
		ObjectManager::getInstance()->addObject(cubeObject);
	}

	/* CARD TRANSFORMS */

	//card1
	ObjectManager::getInstance()->getObjects()[0]->setRotation(0, 0, -0.349066);
	ObjectManager::getInstance()->getObjects()[0]->setPosition(0, 0, 0);
	//card2
	ObjectManager::getInstance()->getObjects()[1]->setRotation(0, 0, 0.349066);
	ObjectManager::getInstance()->getObjects()[1]->setPosition(0.25, 0, 0);
	//card3
	ObjectManager::getInstance()->getObjects()[2]->setRotation(0, 0, -0.349066);
	ObjectManager::getInstance()->getObjects()[2]->setPosition(0.5, 0, 0);
	//card4
	ObjectManager::getInstance()->getObjects()[3]->setRotation(0, 0, 0.349066);
	ObjectManager::getInstance()->getObjects()[3]->setPosition(0.75, 0, 0);
	//card5
	ObjectManager::getInstance()->getObjects()[4]->setRotation(0, 0, -0.349066);
	ObjectManager::getInstance()->getObjects()[4]->setPosition(1, 0, 0);
	//card6
	ObjectManager::getInstance()->getObjects()[5]->setRotation(0, 0, 0.349066);
	ObjectManager::getInstance()->getObjects()[5]->setPosition(1.25, 0, 0);

	//card7
	ObjectManager::getInstance()->getObjects()[6]->setRotation(0, 0, 1.5708);
	ObjectManager::getInstance()->getObjects()[6]->setPosition(0.25, 0.35, 0);
	//card8
	ObjectManager::getInstance()->getObjects()[7]->setRotation(0, 0, 1.5708);
	ObjectManager::getInstance()->getObjects()[7]->setPosition(1, 0.35, 0);

	//card9
	ObjectManager::getInstance()->getObjects()[8]->setRotation(0, 0, -0.349066);
	ObjectManager::getInstance()->getObjects()[8]->setPosition(0.25, 0.7, 0);
	//card10
	ObjectManager::getInstance()->getObjects()[9]->setRotation(0, 0, 0.349066);
	ObjectManager::getInstance()->getObjects()[9]->setPosition(0.5, 0.7, 0);
	//card11
	ObjectManager::getInstance()->getObjects()[10]->setRotation(0, 0, -0.349066);
	ObjectManager::getInstance()->getObjects()[10]->setPosition(0.75, 0.7, 0);
	//card12
	ObjectManager::getInstance()->getObjects()[11]->setRotation(0, 0, 0.349066);
	ObjectManager::getInstance()->getObjects()[11]->setPosition(1, 0.7, 0);

	//card13
	ObjectManager::getInstance()->getObjects()[12]->setRotation(0, 0, 1.5708);
	ObjectManager::getInstance()->getObjects()[12]->setPosition(0.625, 1.05, 0);

	//card14
	ObjectManager::getInstance()->getObjects()[13]->setRotation(0, 0, -0.349066);
	ObjectManager::getInstance()->getObjects()[13]->setPosition(0.5, 1.4, 0);
	//card15
	ObjectManager::getInstance()->getObjects()[14]->setRotation(0, 0, 0.349066);
	ObjectManager::getInstance()->getObjects()[14]->setPosition(0.75, 1.4, 0);



}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0, 0.3f, 0.4f, 1);
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
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{
	if (key == 'W')
	{
		//m_rot_x += 3.14f*m_delta_time;
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 3.14f*m_delta_time;
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 3.14f*m_delta_time;
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 3.14f*m_delta_time;
		m_rightward = 1.0f;
	}
	else if (key == VK_LEFT) 
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
	m_forward = 0.0f;
	m_rightward = 0.0f;
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
	int width = (this->getClientWindowRect().right - this->getClientWindowRect().left);
	int height = (this->getClientWindowRect().bottom - this->getClientWindowRect().top);



	m_rot_x += (mouse_pos.m_y - (height / 2.0f)) * m_delta_time * 0.1f;
	m_rot_y += (mouse_pos.m_x - (width / 2.0f)) * m_delta_time * 0.1f;



	InputSystem::get()->setCursorPosition(Point((int)(width / 2.0f), (int)(height / 2.0f)));


}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 0.5f;
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
	m_scale_cube = 2.0f;
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
	m_scale_cube = 1.0f;
}