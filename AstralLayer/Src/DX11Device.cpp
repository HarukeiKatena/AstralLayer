#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11Device::~DX11Device()
{
	//デバイス解放
	if (m_pDevice != nullptr)
		m_pDevice->Release();
}

bool AstralLayerDirectX11::DX11Device::Create()
{
	//DXデバイス作成
	ID3D11Device* pDevice = nullptr;
	HRESULT hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&pDevice,
		nullptr,
		nullptr
	);
	ATLAssertMessage(SUCCEEDED(hr), "Deviceの作成に失敗しました");
	if (FAILED(hr))
		return false;

	//デバイスをDevice5にキャスト
	m_pDevice = reinterpret_cast<ID3D11Device5*>(pDevice);

	//フラグセット
	m_gi = ATL_GRAPHIC_INTERFACE::DirectX11;

	return true;
}

AstralLayer::ATLIResource* AstralLayerDirectX11::DX11Device::CreateResource(
	ATL_RESOURCE_DESC& Desc, 
	const void* pSrcData)
{
	//エラーチェック
	ATLAssert(Desc.Flag != ATL_RESOURCE_FLAG::UNKNOWN);

	//作成処理
    if (Desc.Flag == ATL_RESOURCE_FLAG::CONSTANTBUFFER || 
		Desc.Flag == ATL_RESOURCE_FLAG::VERTEXBUFFER || 
		Desc.Flag == ATL_RESOURCE_FLAG::INDEXBUFFER)
    {
		//リソース作成
		DX11Resource* pOut = new DX11Resource();
		if (pOut->CreateResource(m_pDevice, Desc, pSrcData) == false)
		{
			ATLAssertMessage(false, "Resourceの作成に失敗しました");
			delete pOut;
			pOut = nullptr;
		}
		return pOut;
    }
    else if (Desc.Flag == ATL_RESOURCE_FLAG::TEXTURE2D)
    {
		//テクスチャ2D作成
		DX11Texture2D* pOut = new DX11Texture2D();
		if (pOut->CreateTexture2D(m_pDevice, Desc, pSrcData) == false)
		{
			ATLAssertMessage(false, "Resourceの作成に失敗しました");
			delete pOut;
			pOut = nullptr;
		}
		return pOut;
    }
	return nullptr;
}

AstralLayer::ATLIPipeLine* AstralLayerDirectX11::DX11Device::CreatePipeLine(
	ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc)
{
	//パイプライン作成
	DX11PipeLine* pOut = new DX11PipeLine();
	if (pOut->Create(m_pDevice, Desc) == false)
	{
		ATLAssertMessage(false, "PipeLineの作成に失敗しました");
		delete pOut;
		pOut = nullptr;
	}

	return pOut;
}

AstralLayer::ATLIDepthStencilView* AstralLayerDirectX11::DX11Device::CreateDepthStencilView(
	ATL_DEPTH_STENCIL_VIEW_DESC& Desc)
{
	//デプスステンシルビュー作成
	DX11DepthStencilView* pOut = new DX11DepthStencilView();
	if (pOut->Create(m_pDevice, Desc) == false)
	{
		ATLAssertMessage(false, "デプスステンシルビューの作成に失敗しました");
		delete pOut;
		pOut = nullptr;
	}
	return pOut;;
}

AstralLayer::ATLICommandList* AstralLayerDirectX11::DX11Device::CreateCommandList()
{
	//コマンドリスト作成
	DX11CommandList* pOut = new DX11CommandList();
	if (pOut->Create(m_pDevice) == false) 
	{
		ATLAssertMessage(false, "CommandListの作成に失敗しました");
		delete pOut;
		pOut = nullptr;
	}

	return pOut;
}

AstralLayer::ATLICommandQueue* AstralLayerDirectX11::DX11Device::CreateCommandQueue()
{
	//コマンドキュー作成
	DX11CommandQueue* pOut = new DX11CommandQueue();
	if (pOut->Create(m_pDevice) == false)
	{
		ATLAssertMessage(false, "CommandQueueの作成に失敗しました");
		delete pOut;
		pOut = nullptr;
	}
	return pOut;
}

AstralLayer::ATLISwapChain* AstralLayerDirectX11::DX11Device::CreateSwapChain(
	ATL_SWAPCHAIN_DESC& Desc, 
	AstralLayer::ATLICommandQueue* pCommandQueue)
{
	//スワップチェイン作成
	DX11SwapChain* pOut = new DX11SwapChain();
	if (pOut->Create(m_pDevice, Desc, pCommandQueue) == false)
	{
		ATLAssertMessage(false, "SwapChainの作成に失敗しました");
		delete pOut;
		pOut = nullptr;
	}
	return pOut;
}

AstralLayer::ATLIFence* AstralLayerDirectX11::DX11Device::CreateFence()
{
	//フェンスの作成
	DX11Fence* pOut = new DX11Fence();
	if (pOut->Create(m_pDevice) == false)
	{
		ATLAssertMessage(false, "フェンスの作成に失敗しました");
		delete pOut;
		pOut = nullptr;
	}
	return pOut;
}

AstralLayer::ATLIRenderTargetView* AstralLayerDirectX11::DX11Device::CreateRenderTargetView(
	AstralLayer::ATLISwapChain* SwapChain, 
	unsigned int ScreenWidth, 
	unsigned int ScreenHeight)
{
	//スワップチェインを受け取る　NULLの場合は受け取らない
	IDXGISwapChain* swap = nullptr;
	if (SwapChain != nullptr)
		reinterpret_cast<AstralRHI::RHISwapChain*>(SwapChain)->
		GetHandle(reinterpret_cast<void**>(&swap), SWAPCHAIN_SWAPCHAIN);

	//レンダーターゲットビュー作成
	DX11RenderTargetView* pOut = new DX11RenderTargetView();
	if (pOut->Create(m_pDevice, swap, ScreenWidth, ScreenHeight) == false)
	{
		ATLAssertMessage(false, "レンダーターゲットビューの作成に失敗しました");
		delete pOut;
		pOut = nullptr;
	}
	return pOut;
}

void AstralLayerDirectX11::DX11Device::Release()
{
	delete this;
}

void AstralLayerDirectX11::DX11Device::GetHandle(
	void** Resource, 
	int Handle)
{
	Handle;
	*Resource = m_pDevice;
}
