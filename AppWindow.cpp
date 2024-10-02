#include "AppWindow.h"

AppWindow::AppWindow()
{
	//Quad* quad1 = new Quad({ -0.75f, 0.25f, 0.0f });
	//quad1->setScale(1.2f);
	//quad1->setColor({1, 0, 0.6});
	//Quad* quad2 = new Quad({ 0.25f, 0.25f, 0.0f });
	//quad2->setScale(1.2f);
	//Quad* quad3 = new Quad({ -0.25f, -0.5f, 0.0f });
	//quad3->setScale(1.2f);
}


AppWindow::~AppWindow()
{

}

void AppWindow::onCreate()
{
	Window::onCreate();
	this->renderer = new Renderer(this);
	this->renderer->BuildShaders();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	ObjectManager::getInstance()->Update();
	this->renderer->BuildShaders();
	this->renderer->Draw();

	if (fTicks >= 1) 
	{

		float x = (float(rand()) / float(RAND_MAX)) * (0.6 - (-1)) + (-1);
		float y = (float(rand()) / float(RAND_MAX)) * (0.6 - (-1)) + (-1);

		Quad* quad = new Quad({ x, y, 0 });
		quad->setScale(0.4);
		this->fTicks = 0;
	}
	this->fTicks += 0.01;
}


void AppWindow::onDestroy()
{
	Window::onDestroy();
}
