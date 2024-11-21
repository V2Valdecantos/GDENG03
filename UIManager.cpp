#include "UIManager.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::get()
{
	return sharedInstance;
}

void UIManager::initialize(const HWND windowHandle)
{
	if (!sharedInstance)
		sharedInstance = new UIManager(windowHandle);
}

void UIManager::draw() const
{

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (const auto& uiScreen : uiList)
	{
		uiScreen->draw();
	}
	//ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UIManager(const HWND windowHandle)
{
	//initialize IMGUI interface
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	// Setup Dear ImGui style
	setupImGuiStyle();

	// Setup Dear ImGui font
	const ImFont* customFont = io.Fonts->AddFontFromFileTTF(
		R"(imgui\misc\fonts\Karla-Regular.ttf)", 22.f);

	if (!customFont)
		io.Fonts->AddFontDefault();


	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getD3DDevice(), GraphicsEngine::getInstance()->getImmediateDeviceContext()->getContext());

	const std::shared_ptr<MenuScreen> menuScreen = std::make_shared<MenuScreen>();
	this->uiMap[menuScreen->getName()] = menuScreen;
	this->uiList.push_back(menuScreen);


}

UIManager::~UIManager()
{
	delete sharedInstance;
}

void UIManager::setupImGuiStyle()
{
	// Tokyo Night Storm style from ImThemes
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.0f;
	style.DisabledAlpha = 0.6000000238418579f;
	style.WindowPadding = ImVec2(15.0f, 10.10000038146973f);
	style.WindowRounding = 10.0f;
	style.WindowBorderSize = 1.0f;
	style.WindowMinSize = ImVec2(32.0f, 32.0f);
	style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style.WindowMenuButtonPosition = ImGuiDir_Left;
	style.ChildRounding = 5.0f;
	style.ChildBorderSize = 1.0f;
	style.PopupRounding = 5.0f;
	style.PopupBorderSize = 1.0f;
	style.FramePadding = ImVec2(4.0f, 3.0f);
	style.FrameRounding = 4.0f;
	style.FrameBorderSize = 0.0f;
	style.ItemSpacing = ImVec2(8.0f, 4.0f);
	style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);
	style.CellPadding = ImVec2(4.0f, 2.0f);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 6.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 10.0f;
	style.GrabRounding = 10.0f;
	style.TabRounding = 4.0f;
	style.TabBorderSize = 0.0f;
	style.TabMinWidthForCloseButton = 0.0f;
	style.ColorButtonPosition = ImGuiDir_Left;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.SelectableTextAlign = ImVec2(0.0f, 0.0f);

	style.Colors[ImGuiCol_Text] = ImVec4(0.7529411911964417f, 0.7921568751335144f, 0.9607843160629272f, 1.0f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.2549019753932953f, 0.2823529541492462f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1411764770746231f, 0.1568627506494522f, 0.2313725501298904f, 1.0f);
	style.Colors[ImGuiCol_ChildBg] = ImVec4(0.1415455490350723f, 0.1563405692577362f, 0.2313725501298904f, 0.7058823704719543f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.1415455490350723f, 0.1563405692577362f, 0.2313725501298904f, 0.7058823704719543f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.6614994406700134f, 0.6949518918991089f, 0.8392156958580017f, 0.501960813999176f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.2543022036552429f, 0.2832040190696716f, 0.407843142747879f, 0.501960813999176f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.2549019753932953f, 0.2823529541492462f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.4786158800125122f, 0.6400314569473267f, 0.9686274528503418f, 0.4000000059604645f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.4786158800125122f, 0.6400314569473267f, 0.9686274528503418f, 0.6705882549285889f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.1411764770746231f, 0.1568627506494522f, 0.2313725501298904f, 1.0f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.2549019753932953f, 0.2823529541492462f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.1372549086809158f, 0.1372549086809158f, 0.1372549086809158f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.01960784383118153f, 0.01960784383118153f, 0.01960784383118153f, 0.5299999713897705f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3098039329051971f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.407843142747879f, 0.407843142747879f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.5098039507865906f, 0.5098039507865906f, 0.5098039507865906f, 1.0f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.7333333492279053f, 0.6039215922355652f, 0.9686274528503418f, 1.0f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.7333333492279053f, 0.6039215922355652f, 0.9686274528503418f, 1.0f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.7942906618118286f, 0.6929580569267273f, 0.9785407781600952f, 1.0f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.2549019753932953f, 0.2823529541492462f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.47843137383461f, 0.6392157077789307f, 0.9686274528503418f, 0.5137255191802979f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.47843137383461f, 0.6352941393852234f, 0.9686274528503418f, 0.6980392336845398f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.2549019753932953f, 0.2823529541492462f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.47843137383461f, 0.6392157077789307f, 0.9686274528503418f, 0.5137255191802979f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.47843137383461f, 0.6352941393852234f, 0.9686274528503418f, 0.6980392336845398f);
	style.Colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
	style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 0.7799999713897705f);
	style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.6700000166893005f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.949999988079071f);
	style.Colors[ImGuiCol_Tab] = ImVec4(0.2549019753932953f, 0.2823529541492462f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_TabHovered] = ImVec4(0.47843137383461f, 0.6352941393852234f, 0.9686274528503418f, 0.7682403326034546f);
	style.Colors[ImGuiCol_TabActive] = ImVec4(0.47843137383461f, 0.6352941393852234f, 0.9686274528503418f, 0.6995707750320435f);
	style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.1411764770746231f, 0.1568627506494522f, 0.2313725501298904f, 1.0f);
	style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.2549019753932953f, 0.2823529541492462f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.0f, 0.6196078658103943f, 0.3921568691730499f, 1.0f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.9686274528503418f, 0.4627451002597809f, 0.5568627715110779f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.8784313797950745f, 0.686274528503418f, 0.407843142747879f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6196078658103943f, 0.3921568691730499f, 1.0f);
	style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1019607856869698f, 0.105882354080677f, 0.1490196138620377f, 1.0f);
	style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
	style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
	style.Colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3499999940395355f);
	style.Colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);
}