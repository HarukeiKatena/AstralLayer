#include"../Include/ATL/AstralDirectX11Factory.h"
#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayer::ATLIDevice* AstralLayerFactory::ATLDX11Factory::CreateDevice()
{
	//ATL�f�o�C�X�쐬
	AstralLayerDirectX11::DX11Device* pOut = new AstralLayerDirectX11::DX11Device();
	if (pOut->Create()== false)
	{
		ATLAssertMessage(false, "Device�̍쐬�Ɏ��s���܂���");
		delete pOut;
		pOut = nullptr;
	}

	return pOut;
}

void AstralLayerFactory::ATLDX11Factory::Release()
{
	delete this;
}
