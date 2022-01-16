#include"AstralImGui.h"

#pragma warning(push)
#pragma warning(disable:26451)
#pragma warning(disable:6386)
#pragma warning(disable:4244)
#include"../ImGUI/imgui_impl_dx12.h"
#pragma warning(pop)

AstralImGui::DX12ImGui::~DX12ImGui()
{
	ImGui_ImplDX12_Shutdown();
	if (m_prtvHeap != nullptr)
		m_prtvHeap->Release();
	m_prtvHeap = nullptr;
}

bool AstralImGui::DX12ImGui::Create(
	AstralLayer::ATLIDevice* pDevice,
	AstralLayer::ATLICommandList* pCommandList)
{
	//dx12デバイス取得
	ID3D12Device* device = nullptr;
	reinterpret_cast<AstralRHI::RHIDevice*>(pDevice)->
		GetHandle(reinterpret_cast<void**>(&device), AstralLayerDirectX12::DEVICE_DEVICE);

	//RTVヒープ作る
	D3D12_DESCRIPTOR_HEAP_DESC desc{};
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	desc.NumDescriptors = 1;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	device->CreateDescriptorHeap(&desc,IID_PPV_ARGS(&m_prtvHeap));

	//コマンドリスト
	m_pCommandList = pCommandList;

	//DX12初期設定
	if(ImGui_ImplDX12_Init(
		device,
		2,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		m_prtvHeap,
		m_prtvHeap->GetCPUDescriptorHandleForHeapStart(),
		m_prtvHeap->GetGPUDescriptorHandleForHeapStart()
	) == false)
		return false;

	return true;
}

void AstralImGui::DX12ImGui::Begin()
{
	ImGui_ImplDX12_NewFrame();
}

AstralLayer::ATLICommandList* AstralImGui::DX12ImGui::End(
	AstralLayer::ATLIFence* pFence,
	AstralLayer::ATLIRenderTargetView* pRenderTargetView)
{
	//バックバッファを取得
	unsigned int* back = nullptr;
	reinterpret_cast<AstralRHI::RHIFence*>(pFence)->GetHandle(reinterpret_cast<void**>(&back), AstralLayerDirectX12::FENCE_BACKBUFFER);

	//RHIレンダーターゲット取得
	AstralRHI::RHIRenderTargetView* rhirtv = reinterpret_cast<AstralRHI::RHIRenderTargetView*>(pRenderTargetView);

	//RTVリソース取得
	ID3D12Resource* resource = nullptr;
	rhirtv->GetHandle(reinterpret_cast<void**>(&resource), AstralLayerDirectX12::RTV_RESOURCE + *back);

	//RTVヒープ取得
	ID3D12DescriptorHeap* rtvheap = nullptr;
	rhirtv->GetHandle(reinterpret_cast<void**>(&rtvheap),AstralLayerDirectX12::RTV_HEAP);

	//RHIコマンド取得
	AstralRHI::RHICommandList* rhicmd = reinterpret_cast<AstralRHI::RHICommandList *>(m_pCommandList);
	
	//アロケーターとコマンドリスト取得
	ID3D12CommandAllocator* allocatpr = nullptr;
	ID3D12GraphicsCommandList* list = nullptr;
	rhicmd->GetHandle(reinterpret_cast<void**>(&allocatpr), AstralLayerDirectX12::COMMANDLIST_ALLOCATOR);
	rhicmd->GetHandle(reinterpret_cast<void**>(&list), AstralLayerDirectX12::COMMANDLIST_COMMAND);

	//コマンドを書き込む
	allocatpr->Reset();
	list->Reset(allocatpr, nullptr);

	D3D12_RESOURCE_BARRIER barrier = {};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = resource;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	list->ResourceBarrier(1,&barrier);

	ID3D12Device* device = nullptr;
	rtvheap->GetDevice(IID_PPV_ARGS(&device));

	D3D12_CPU_DESCRIPTOR_HANDLE handle = rtvheap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += 
		static_cast<unsigned long long>( device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV)) * 
		static_cast<unsigned long long>(*back);
	list->OMSetRenderTargets(1, &handle, FALSE, nullptr);
	list->SetDescriptorHeaps(1, &m_prtvHeap);
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), list);

	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	list->ResourceBarrier(1, &barrier);

	list->Close();

	device->Release();

	return m_pCommandList;
}
