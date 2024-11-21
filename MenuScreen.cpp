#include "MenuScreen.h"
#include "AppWindow.h"
#include "GraphicsEngine.h"

MenuScreen::MenuScreen() : UIScreen("MenuScreen")
{
	LogUtils::logHResult(
		this,
		DirectX::CreateWICTextureFromFile(
			GraphicsEngine::getInstance()->getD3DDevice(),
			L"Textures/logo.png",
			nullptr,
			creditsTexture.ReleaseAndGetAddressOf()));
}

void MenuScreen::setMaterialEditor(bool* isMaterialEditorOpen)
{
	this->isMaterialEditorOpen = isMaterialEditorOpen;
}

void MenuScreen::draw()
{

	if (!LogUtils::logBool(this, ImGui::BeginMainMenuBar())) return;

	// File header
	if (ImGui::BeginMenu("File")) {
		if (ImGui::MenuItem("Open..", "Ctrl+O"))
		{
		}
		if (ImGui::MenuItem("Save", "Ctrl+S"))
		{
		}
		if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
		{
		}

		ImGui::Separator();

		if (ImGui::MenuItem("Quit", "Ctrl+W"))
		{
		}
		ImGui::EndMenu();
	}

	// Game Object header
	if (ImGui::BeginMenu("Game Object")) {
		if (ImGui::MenuItem("Create Cube"))
		{
			onCreateCubeClicked();
		}
		if (ImGui::MenuItem("Create Physics Cube"))
		{
			onCreatePhysicsCubeClicked();
		}
		if (ImGui::MenuItem("Create Plane"))
		{
			onCreatePlaneClicked();
		}

		if (ImGui::MenuItem("Create Physics Plane"))
		{
			onCreatePhysicsPlaneClicked();
		}

		ImGui::Separator();

		if (ImGui::BeginMenu("Light"))
		{
			if (ImGui::MenuItem("Point Light"))
			{
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}

	// About header
	if (ImGui::BeginMenu("About"))
	{
		if (ImGui::MenuItem("Credits", nullptr, isCreditsOpen))
		{
			isCreditsOpen = !isCreditsOpen;
		}
		ImGui::EndMenu();
	}

	// Test header
	if (ImGui::BeginMenu("Windows"))
	{
		if(isMaterialEditorOpen != nullptr)
		if (ImGui::MenuItem("Material Editor", nullptr, *isMaterialEditorOpen))
		{
			*isMaterialEditorOpen = !(*isMaterialEditorOpen);
		}

		if (ImGui::MenuItem("Color Picker", nullptr, isColorPickerOpen))
		{
			isColorPickerOpen = !isColorPickerOpen;
		}
		ImGui::EndMenu();
	}

	// Test header
	/*if (ImGui::BeginMenu("Test"))
	{
		if (ImGui::MenuItem("Color Picker", nullptr, isColorPickerOpen))
		{
			isColorPickerOpen = !isColorPickerOpen;
		}
		ImGui::EndMenu();
	}*/

	ImGui::EndMainMenuBar();

	if (isCreditsOpen)
		showCreditsWindow();

	if (isColorPickerOpen)
		showColorPickerWindow();
}

void MenuScreen::onCreateCubeClicked()
{
}

void MenuScreen::onCreatePhysicsCubeClicked()
{
	AppWindow::getInstance()->spawnCube(15);
	
}

void MenuScreen::onCreatePlaneClicked()
{
	
}

void MenuScreen::onCreatePhysicsPlaneClicked()
{
	AppWindow::getInstance()->spawnPlane();
}

void MenuScreen::showCreditsWindow()
{
	if (ImGui::Begin("Credits", &isCreditsOpen))
	{
		constexpr ImVec2 imageSize = { 200, 200 };
		ImGui::Image(static_cast<ImTextureID>(reinterpret_cast<intptr_t>(creditsTexture.Get())), imageSize);
		ImGui::TextColored(ImVec4(0.3f, 0.4f, 1.0f, 1.0f), "URL_Engine 0.2 \n");

		ImGui::NewLine();
		ImGui::Text(
			"About: \n"
			"Developed by Uriel P. Pascual \n"
		);

		ImGui::NewLine();
		ImGui::Text(
			"Acknowledgements: \n"
			"Dr. Neil Del Gallego's GDENG03 Course \n"
			"PardCode Game Engine Tutorial \n"
			"LogUtils and MathUtils Functions borrowed from GDENG03 Group 3 \n"
		);
		ImGui::NewLine();

		ImGui::Separator();

		ImGui::Text("Dear ImGui Version: %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);

		if (ImGui::Button("OK"))
			isCreditsOpen = false;
	}
	ImGui::End();
}

void MenuScreen::showColorPickerWindow()
{
	if (ImGui::Begin("Color Picker", &isColorPickerOpen))
	{
		static ImVec4 color(1.0f, 0.0f, 1.0f, 0.5f);
		ImGui::SameLine();
		ImGui::ColorPicker4("MyColor##4", reinterpret_cast<float*>(&color), 0);
	}
	ImGui::End();
}
