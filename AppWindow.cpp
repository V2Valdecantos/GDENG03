#include "AppWindow.h"

AppWindow::AppWindow()
{
	Quad* quad1 = new Quad({ -0.75f, 0.25f, 0.0f });
	quad1->setScale(1.2f);
	quad1->setColor({1, 0, 0.6});
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
	this->renderer = new Renderer(this);
	this->renderer->BuildShaders();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	this->renderer->Draw();
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}
