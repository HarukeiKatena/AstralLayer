#include"AstralImGui.h"
#include"../ImGUI/imgui_impl_dx11.h"

AstralImGui::DX11ImGui::~DX11ImGui()
{
	ImGui_ImplDX11_Shutdown();
}

bool AstralImGui::DX11ImGui::Create(
	AstralLayer::ATLIDevice* pDevice,
	AstralLayer::ATLICommandList* pCommandList)
{

	//dx11デバイス取得
	ID3D11Device* device = nullptr;
	reinterpret_cast<AstralRHI::RHIDevice*>(pDevice)->
		GetHandle(reinterpret_cast<void**>(&device), AstralLayerDirectX11::DEVICE_DEVICE);

	//DeviceContext取得
	ID3D11DeviceContext* dcon = nullptr;
	reinterpret_cast<AstralRHI::RHICommandList*>(pCommandList)->
		GetHandle(reinterpret_cast<void**>(&dcon), AstralLayerDirectX11::COMMANDLIST_CONTEXT);

	//DX11初期設定
	if(ImGui_ImplDX11_Init(device, dcon) == false)
		return false;

	m_pCommandList = pCommandList;

	return true;
}

void AstralImGui::DX11ImGui::Begin()
{
	ImGui_ImplDX11_NewFrame();
}

AstralLayer::ATLICommandList* AstralImGui::DX11ImGui::End(
	AstralLayer::ATLIFence* pFence,
	AstralLayer::ATLIRenderTargetView* pRenderTargetView)
{
	//コマンドリセット
	m_pCommandList->Reset(nullptr, pFence);

	//レンダーターゲットを取得
	ID3D11RenderTargetView* rtv = nullptr;
	reinterpret_cast<AstralRHI::RHIRenderTargetView*>(pRenderTargetView)->
		GetHandle(reinterpret_cast<void**>(&rtv),AstralLayerDirectX11::RTV_RTV);

	//デファードコンテキスト取得
	ID3D11DeviceContext* dcon = nullptr;
	reinterpret_cast<AstralRHI::RHICommandList*>(m_pCommandList)->
		GetHandle(reinterpret_cast<void**>(&dcon), AstralLayerDirectX11::COMMANDLIST_CONTEXT);

	dcon->OMSetRenderTargets(1, &rtv, nullptr);

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	m_pCommandList->Close();

	return m_pCommandList;
}
