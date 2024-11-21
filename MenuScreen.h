#pragma once

#include <wrl/client.h>
#include "WICTextureLoader.h"
#include "DirectXHelpers.h"

#include "UIScreen.h"

class MenuScreen final :
	public UIScreen
{
public:
	MenuScreen();

	void setMaterialEditor(bool* isMaterialEditorOpen);

private:
	void draw() override;
	void onCreateCubeClicked();
	void onCreatePhysicsCubeClicked();
	void onCreatePlaneClicked();
	void onCreatePhysicsPlaneClicked();
	void showCreditsWindow();
	void showColorPickerWindow();

	bool isColorPickerOpen = false;
	bool isCreditsOpen = false;
	bool* isMaterialEditorOpen = nullptr;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> creditsTexture;
};

