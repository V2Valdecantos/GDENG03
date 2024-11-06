#include "AppWindow.h"
#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool AppWindow::LoadTextureFromMemory(const void* data, size_t data_size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	// Load from disk into a raw RGBA buffer
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create texture
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = image_width;
	desc.Height = image_height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;

	ID3D11Texture2D* pTexture = NULL;
	D3D11_SUBRESOURCE_DATA subResource;
	subResource.pSysMem = image_data;
	subResource.SysMemPitch = desc.Width * 4;
	subResource.SysMemSlicePitch = 0;
	GraphicsEngine::get()->getID3D11Device()->CreateTexture2D(&desc, &subResource, &pTexture);

	// Create texture view
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;
	srvDesc.Texture2D.MostDetailedMip = 0;
	GraphicsEngine::get()->getID3D11Device()->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
	pTexture->Release();

	*out_width = image_width;
	*out_height = image_height;
	stbi_image_free(image_data);

	return true;
}

// Open and read a file, then forward to LoadTextureFromMemory()
bool AppWindow::LoadTextureFromFile(const char* file_name, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
{
	FILE* f = fopen(file_name, "rb");
	if (f == NULL)
		return false;
	fseek(f, 0, SEEK_END);
	size_t file_size = (size_t)ftell(f);
	if (file_size == -1)
		return false;
	fseek(f, 0, SEEK_SET);
	void* file_data = IM_ALLOC(file_size);
	fread(file_data, 1, file_size, f);
	bool ret = LoadTextureFromMemory(file_data, file_size, out_srv, out_width, out_height);
	IM_FREE(file_data);
	return ret;
}

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

	this->logoTex = NULL;
	bool ret = LoadTextureFromFile("textures//dlsu.png", &this->logoTex, &this->logoWidth, &this->logoHeight);
	IM_ASSERT(ret);
}

void AppWindow::onUpdate()
{

	Window::onUpdate();

	InputSystem::get()->update();

	if (camera)
		InputSystem::get()->showCursor(false);
	else
		InputSystem::get()->showCursor(true);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
	//Menu Toolbar
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("About")) 
	{
		if (ImGui::MenuItem("Credits")) 
		{
			credits_active = true;
		}
		if (ImGui::MenuItem("Color Picker"))
		{
			color_picker_active = true;
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	//Credits Screen
	if (credits_active) 
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 100.0f,120.0f });
		ImGui::Begin("Credits", &credits_active);
		ImGui::PopStyleVar();

		ImGui::Image((ImTextureID)(intptr_t)this->logoTex, ImVec2(this->logoWidth / 4, this->logoHeight / 4));
		ImGui::TextColored(ImVec4(1, 0, 1, 1), "V2Engine - 0.1.0");
		ImGui::Text("Developed by: Andre Vito P. Valdecantos");
		ImGui::Text("GDENG03 - XX22");
		ImGui::NewLine();
		ImGui::Text("Acknowlegments:");
		ImGui::Text("Dr. Neil Del Gallego's GDENG03 Course");
		ImGui::Text("PardCode Game Engine Tutorial");
		ImGui::Text("Dear IMGUI by ocornut");
		if (ImGui::Button("Close"))
			credits_active = false;

		ImGui::End();
	}

	//Color Picker Screeen
	if (color_picker_active)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 100.0f,120.0f });
		ImGui::Begin("Color Picker Screen", &color_picker_active);
		ImGui::PopStyleVar();

		ImGui::ColorPicker4("Color", my_color);
		ImGui::End();
	}
	
	

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
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

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
	if (key == VK_ESCAPE) 
	{
		camera = !camera;

		if (camera) 
		{
			InputSystem::get()->addListener(CameraManager::getInstance()->GetActiveCamera());
			InputSystem::get()->showCursor(false);
		}
		else 
		{
			InputSystem::get()->removeListener(CameraManager::getInstance()->GetActiveCamera());
			InputSystem::get()->showCursor(true);
		}
	}
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

}

