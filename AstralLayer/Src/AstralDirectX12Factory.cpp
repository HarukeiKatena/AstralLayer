#include "../Include/ATL/AstralDirectX12Factory.h"
#include "../Include/AstralDebug.h"

IDXGIFactory4* AstralLayerFactory::ATLDX12Factory::CreateFactory()
{
#if defined(ATL_DEBUG)
	EnableDebug();
#endif

	//�t�@�N�g���[�쐬
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
	//�f�o�C�X�쐬
	AstralLayerDirectX12::DX12Device* pOut = new AstralLayerDirectX12::DX12Device();
	if (pOut->Create(m_pFactory.Get()) == false)
	{
		ATLAssertMessage(false, "Device�̍쐬�Ɏ��s���܂���");
		delete pOut;
		pOut = nullptr;
	}

	return pOut;
}

void AstralLayerFactory::ATLDX12Factory::EnableDebug()
{
	//�f�o�b�O���[�h
	ID3D12Debug* DebugController;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&DebugController))))
	{
		DebugController->EnableDebugLayer();//����������f�o�b�O�J�n
		DebugController->Release();

	}
}

void AstralLayerFactory::ATLDX12Factory::Release()
{
	delete this;
}
