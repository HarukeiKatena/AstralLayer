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
	//Context�쐬
	//IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	//�����F�ݒ�
	ImGui::StyleColorsDark();

	//WINDOWS�œ������ꍇ
#if	defined(ASTRAL_WINDOWS)
	if(ImGui_ImplWin32_Init(hWnd) == false)
		return false;
#endif

	//�Ή������C���^�[�t�F�[�X�ō쐬
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
	//�w�肵���O���t�B�b�N�C���^�[�t�F�[�X�Ńt���[���쐬
	g_pAstralImGui->Begin();

#if	defined(ASTRAL_WINDOWS)
	ImGui_ImplWin32_NewFrame();
#endif

	ImGui::NewFrame();

	
}

AstralLayer::ATLICommandList* AstralImGui::ImGuiRenderer(AstralLayer::ATLIFence* pFence, AstralLayer::ATLIRenderTargetView* pRenderTargetView)
{
	//�`��
	ImGui::Render();

	//�w�肳�ꂽ�`�惉�C�u�����̕`��I��
	return g_pAstralImGui->End(pFence, pRenderTargetView);
}

void AstralImGui::ImGuiEnd()
{
	//�r���[�|�[�g
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


// ��������I���W�i���f��(�����T���v���ۃR�s)
static bool show_demo_window = true;
static bool show_another_window = false;
static float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };

void AstralImGui::ImGuiDemo()
{
	// �����f���\��
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	//�ȒP�ȃE�B���h�E�\��
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // ����ŃE�B���h�E��\���ł���

		ImGui::Text("This is some useful text.");               // ����Ńe�L�X�g��\���ł���
		ImGui::Checkbox("Demo Window", &show_demo_window);      // ����Ń`�F�b�N�{�b�N�X��\���ł���@�`�F�b�N�{�b�N�X�Ŏw�肵���ϐ���true,false�𐧌�ł���
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // �X���C�_�[float�@����̏ꍇ0.0~1.0�Ő���ł���
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // �F�@�F���I���ł���

		if (ImGui::Button("Button"))                            // �{�^���̐��䂪�ł���
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// �t���O�ŃE�B���h�E�̕\����\�����ł���
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
}
