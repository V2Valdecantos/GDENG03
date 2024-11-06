#include "AppWindow.h"


AppWindow::AppWindow()
{
}

void AppWindow::update()
{

}


AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	InputSystem::get()->addListener(this);
	//InputSystem::get()->showCursor(false);

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
	InputSystem::get()->addListener(CameraManager::getInstance()->GetActiveCamera());


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

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

		// Setup Platform/Renderer backends
		ImGui_ImplWin32_Init(this->m_hwnd);
		ImGui_ImplDX11_Init(GraphicsEngine::get()->getID3D11Device(), GraphicsEngine::get()->getID3D11DeviceContext());
}

void AppWindow::onUpdate()
{
	// Poll and handle messages (inputs, window resize, etc.)
// See the WndProc() function below for our to dispatch events to the Win32 backend.

	MSG msg;
	while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	Window::onUpdate();


	InputSystem::get()->update();
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	
	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 100.0f,120.0f });
	ImGui::Begin("About", &credits_active);
	ImGui::PopStyleVar();

	ImGui::TextColored(ImVec4(1, 0, 1, 1), "V2Engine - 0.1.0");
	ImGui::Text("Developed by: Andre Vito Valdecantos");
	ImGui::Text("GDENG03 - XX22");
	ImGui::NewLine();
	ImGui::NewLine();
	if (ImGui::Button("Close"))
		credits_active = false;

	ImGui::End();

	ImGui::Render();
	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.7, 0.6f, 0.9f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	CameraManager::getInstance()->Update();
	ObjectManager::getInstance()->Update(EngineTime::getDeltaTime());

	for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++) 
	{
		ObjectManager::getInstance()->getObjects()[i]->draw(this);
	}

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
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
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
	InputSystem::get()->addListener(CameraManager::getInstance()->GetActiveCamera());
	InputSystem::get()->showCursor(false);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
	InputSystem::get()->removeListener(CameraManager::getInstance()->GetActiveCamera());
	InputSystem::get()->showCursor(true);
}

void AppWindow::onKeyDown(int key)
{
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

}

void AppWindow::onMouseMove(const Point& mouse_pos)
{

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

	if (!rMouse) 
	{
		rMouse = true;
		InputSystem::get()->showCursor(true);
		InputSystem::get()->removeListener(CameraManager::getInstance()->GetActiveCamera());
	}
	else 
	{
		rMouse = false;
		InputSystem::get()->showCursor(false);
		InputSystem::get()->addListener(CameraManager::getInstance()->GetActiveCamera());
	}


}

