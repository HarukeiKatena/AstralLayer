#include "../Include/ATL/AstralDirectX12Factory.h"
#include "../Include/AstralDebug.h"

IDXGIFactory4* AstralLayerFactory::ATLDX12Factory::CreateFactory()
{
#if defined(ATL_DEBUG)
	EnableDebug();
#endif

	//ファクトリー作成
	IDXGIFactory4* pOut = nullptr;
	if (FAILED(CreateDXGIFactory1(IID_PPV_ARGS(&pOut))))
		return nullptr;

	return pOut;
}

AstralLayerFactory::ATLDX12Factory::ATLDX12Factory()
{
	m_pFactory = this->CreateFactory();
}

AstralLayerFactory::ATLDX12Factory::~ATLDX12Factory()
{

}

AstralLayer::ATLIDevice* AstralLayerFactory::ATLDX12Factory::CreateDevice()
{
	//デバイス作成
	AstralLayerDirectX12::DX12Device* pOut = new AstralLayerDirectX12::DX12Device();
	if (pOut->Create(m_pFactory.Get()) == false)
	{
		ATLAssertMessage(false, "Deviceの作成に失敗しました");
		delete pOut;
		pOut = nullptr;
	}

	return pOut;
}

void AstralLayerFactory::ATLDX12Factory::EnableDebug()
{
	//デバッグモード
	ID3D12Debug* DebugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController))))
	{
		DebugController->EnableDebugLayer();//成功したらデバッグ開始
		DebugController->Release();

	}
}

void AstralLayerFactory::ATLDX12Factory::Release()
{
	delete this;
}
