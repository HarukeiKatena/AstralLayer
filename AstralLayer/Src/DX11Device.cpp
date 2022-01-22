#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11Device::~DX11Device()
{
	/*
	//メモリーリークチェック用
	ID3D11Debug* debug = nullptr;
	if (SUCCEEDED(m_pDevice->QueryInterface(IID_PPV_ARGS(&debug))))
	{
		debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL | D3D11_RLDO_IGNORE_INTERNAL);
		debug->Release();
	}*/
}

bool AstralLayerDirectX11::DX11Device::Create()
{
	//アダプター準備
	IDXGIAdapter1* pAdapter;
	IDXGIAdapter1* vAdapters[8] = {};
	IDXGIFactory1* pFactory = NULL;

	unsigned int id = 0;

	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&pFactory))))
		return false;

	for (unsigned int i = 0; S_OK == pFactory->EnumAdapters1(i, &pAdapter); i++)
	{
		DXGI_ADAPTER_DESC1 desc{};
		pAdapter->GetDesc1(&desc);

		if (desc.Flags == DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			pAdapter->Release();
			continue;
		}

		for (unsigned int c = 0; c <= id; c++)
		{
			if (vAdapters[c] == nullptr)
			{
				vAdapters[c] = pAdapter;
				break;
			}

			DXGI_ADAPTER_DESC1 check{};
			vAdapters[c]->GetDesc1(&check);

			//ビデオメモリがチェック先より大きい場合
			if (check.DedicatedVideoMemory < desc.DedicatedVideoMemory)
			{
				IDXGIAdapter1* save = vAdapters[c];
				vAdapters[c] = pAdapter;
				vAdapters[c + 1] = save;
				desc = check;
			}
		}

		id++;

		//IDが8を超えたらアダプターの列挙を終える
		if (id >= 8)
			break;
	}

	pFactory->Release();

	//DXデバイス作成
	ID3D11Device* pDevice = nullptr;
	for (unsigned int i = 0; i < id; i++)
	{
		if (pDevice != nullptr)//作成に成功していた場合解放作業に入る
		{
			vAdapters[i]->Release();
			vAdapters[i] = nullptr;
			continue;
		}

		D3D11CreateDevice(
			vAdapters[i],
			D3D_DRIVER_TYPE_UNKNOWN,
			nullptr,
			0,	//デバッグする際はここをD3D11_CREATE_DEVICE_DEBUGにする
			nullptr,
			0,
			D3D11_SDK_VERSION,
			&pDevice,
			nullptr,
			nullptr
		);

		//成功失敗関係なしに利用したら解放する
		vAdapters[i]->Release();
		vAdapters[i] = nullptr;
	}

	if (pDevice == nullptr)
		return false;

	//デバイスをDevice5にキャスト
	pDevice->QueryInterface(IID_PPV_ARGS(&m_pDevice));

	pDevice->Release();

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
		if (pOut->CreateResource(m_pDevice.Get(), Desc, pSrcData) == false)
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
		if (pOut->CreateTexture2D(m_pDevice.Get(), Desc, pSrcData) == false)
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
	if (pOut->Create(m_pDevice.Get(), Desc) == false)
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
	if (pOut->Create(m_pDevice.Get(), Desc) == false)
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
	if (pOut->Create(m_pDevice.Get()) == false)
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
	if (pOut->Create(m_pDevice.Get()) == false)
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
	if (pOut->Create(m_pDevice.Get(), Desc, pCommandQueue) == false)
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
	if (pOut->Create(m_pDevice.Get()) == false)
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
	if (pOut->Create(m_pDevice.Get(), swap, ScreenWidth, ScreenHeight) == false)
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
	*Resource = m_pDevice.Get();
}
