#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11Fence::~DX11Fence()
{
	
}

void AstralLayerDirectX11::DX11Fence::GetHandle(
	void** ppResource, 
	int Handle)
{
	Handle;
	*ppResource = m_pFence.Get();
}

void AstralLayerDirectX11::DX11Fence::WaitDrawDone(AstralLayer::ATLICommandQueue* pCommandQueue, AstralLayer::ATLISwapChain* pSwapChain)
{
	//コマンドキューを取得
	ID3D11DeviceContext4* cq = nullptr;
	reinterpret_cast<AstralRHI::RHICommandQueue*>(pCommandQueue)->
		GetHandle(reinterpret_cast<void**>(&cq), COMMANDQUEUE_CONTEXT);

	//スワップチェインを取得
	IDXGISwapChain3* swap = nullptr;
	reinterpret_cast<AstralRHI::RHISwapChain*>(pSwapChain)->
		GetHandle(reinterpret_cast<void**>(&swap), SWAPCHAIN_SWAPCHAIN);

	//現在のFence値がコマンド終了後にFenceに書き込まれるようにする
	unsigned long long fvalue = m_fenceValue;
	cq->Signal(m_pFence.Get(), fvalue);
	m_fenceValue++;

	//コマンドキューが終了していないことを確認する
	if (m_pFence->GetCompletedValue() < fvalue)
	{
		m_pFence->SetEventOnCompletion(fvalue, m_fenceEvent);
		WaitForSingleObject(m_fenceEvent, INFINITE);//待つ
		CloseHandle(m_fenceEvent);
	}
}

void AstralLayerDirectX11::DX11Fence::Release()
{
	delete this;
}

bool AstralLayerDirectX11::DX11Fence::Create(ID3D11Device5* pDevice)
{
	//フェンス作成
	if (FAILED(
		pDevice->CreateFence(
		0,
		D3D11_FENCE_FLAG_NONE,
		IID_PPV_ARGS(&m_pFence))
	))
		return false;

	return true;
}