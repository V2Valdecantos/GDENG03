#include "AppWindow.h"

#include "InputSystem.h"

AppWindow::AppWindow()
{
	//Quad* quad1 = new Quad({ -0.75f, 0.25f, 0.0f });
	//quad1->setScale(1.2f);
	//quad1->setColor({1, 0, 0.6});
	//Quad* quad2 = new Quad({ 0.25f, 0.25f, 0.0f });
	//quad2->setScale(1.2f);
	//Quad* quad3 = new Quad({ -0.25f, -0.5f, 0.0f });
	//quad3->setScale(1.2f);
	//Circle* circle1 = new Circle({0.0f,0.0f,0.0f }, { 0.5f,-0.3f,0}, 0.0f);
}


AppWindow::~AppWindow()
{

}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::get()->addListener(this);
	this->renderer = new Renderer(this);
	this->renderer->BuildShaders();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();
	ObjectManager::getInstance()->Update();
	this->renderer->BuildShaders();
	this->renderer->Draw();

	//Create a cube every 2 seconds
	//if (fTicks >= 2) 
	//{
	//	float x = (float(rand()) / float(RAND_MAX)) * (0.6 - (-1)) + (-1);
	//	float y = (float(rand()) / float(RAND_MAX)) * (0.6 - (-1)) + (-1);

	//	Circle* circle = new Circle({ 0, 0, 0 }, {x, y}, 0.05f);
	//	this->fTicks = 0;
	//}
	//this->fTicks += EngineTime::getDeltaTime();
}


void AppWindow::onDestroy()
{
	Window::onDestroy();
}

void AppWindow::onKeyDown(int key)
{
	if (key == VK_ESCAPE)
	{
		std::cout << "INPUT: ESCAPE" << std::endl;
		ObjectManager::getInstance()->clearObjects();
		this->onDestroy();
		this->m_is_run = false;
	}
}

void AppWindow::onKeyUp(int key)
{
	if (key == VK_SPACE)
	{
		std::cout << "INPUT: SPACE" << std::endl;
		float x = (float(rand()) / float(RAND_MAX)) * (0.6 - (-1)) + (-1);
		float y = (float(rand()) / float(RAND_MAX)) * (0.6 - (-1)) + (-1);

		Circle* circle = new Circle({ 0, 0, 0 }, { x, y }, 0.05f);
	}
	if (key == VK_BACK)
	{
		std::cout << "INPUT: BACKSPACE" << std::endl;
		ObjectManager::getInstance()->popObject();
	}
	if (key == VK_DELETE)
	{
		std::cout << "INPUT: DELETE" << std::endl;
		ObjectManager::getInstance()->clearObjects();
	}

}