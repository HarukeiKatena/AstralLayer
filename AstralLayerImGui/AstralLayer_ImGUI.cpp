#include"../AstralLayer/Include/AstralLayer.h"
#include "AstralLayer_ImGUI.h"

#include"AstralImGui/AstralImGui.h"


#if	defined(ASTRAL_WINDOWS)
#pragma warning(push)
#pragma warning(disable:26451)
#pragma warning(disable:6386)
#pragma warning(disable:4244)
#include"ImGUI/imgui_impl_win32.h"
#pragma warning(pop)
#endif

static AstralImGui::ATLIImGui* g_pAstralImGui = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool AstralImGui::ImGuiWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return ImGui_ImplWin32_WndProcHandler(hWnd,msg,wParam,lParam);
}

bool AstralImGui::ImGuiInit(
	HWND hWnd, 
	AstralLayer::ATLIDevice* pDevice)
{
	//Context作成
	//IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	//初期色設定
	ImGui::StyleColorsDark();

	//WINDOWSで動かす場合
#if	defined(ASTRAL_WINDOWS)
	if(ImGui_ImplWin32_Init(hWnd) == false)
		return false;
#endif

	//対応したインターフェースで作成
	if (pDevice->GetGraphicsInterface() == ATL_GRAPHIC_INTERFACE::DirectX11)		//DirectX11
		g_pAstralImGui = new AstralImGui::DX11ImGui();
	else if (pDevice->GetGraphicsInterface() == ATL_GRAPHIC_INTERFACE::DirectX12)	//DirectX12
		g_pAstralImGui = new AstralImGui::DX12ImGui();
	else
		return false;

	AstralLayer::ATLICommandList* command = pDevice->CreateCommandList();
	
	if (g_pAstralImGui->Create(pDevice, command) == false)
	{
		ImGuiRelease();
		return false;
	}

	

	return true;
}

void AstralImGui::ImGuiBegin()
{
	//指定したグラフィックインターフェースでフレーム作成
	g_pAstralImGui->Begin();

#if	defined(ASTRAL_WINDOWS)
	ImGui_ImplWin32_NewFrame();
#endif

	ImGui::NewFrame();

	
}

AstralLayer::ATLICommandList* AstralImGui::ImGuiRenderer(AstralLayer::ATLIFence* pFence, AstralLayer::ATLIRenderTargetView* pRenderTargetView)
{
	//描画
	ImGui::Render();

	//指定された描画ライブラリの描画終了
	return g_pAstralImGui->End(pFence, pRenderTargetView);
}

void AstralImGui::ImGuiEnd()
{
	//ビューポート
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void AstralImGui::ImGuiRelease()
{
	delete g_pAstralImGui;

#if	defined(ASTRAL_WINDOWS)
	ImGui_ImplWin32_Shutdown();
#endif
	ImGui::DestroyContext();
}


// ここからオリジナルデモ(公式サンプル丸コピ)
static bool show_demo_window = true;
static bool show_another_window = false;
static float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };

void AstralImGui::ImGuiDemo()
{
	// 公式デモ表示
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	//簡単なウィンドウ表示
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // これでウィンドウを表示できる

		ImGui::Text("This is some useful text.");               // これでテキストを表示できる
		ImGui::Checkbox("Demo Window", &show_demo_window);      // これでチェックボックスを表示できる　チェックボックスで指定した変数のtrue,falseを制御できる
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // スライダーfloat　今回の場合0.0~1.0で制御できる
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // 色　色が選択できる

		if (ImGui::Button("Button"))                            // ボタンの制御ができる
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// フラグでウィンドウの表示非表示ができる
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
}
