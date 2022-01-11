#include"../Include/ATL/AstralDirectX11Factory.h"
#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayer::ATLIDevice* AstralLayerFactory::ATLDX11Factory::CreateDevice()
{
	//ATLデバイス作成
	AstralLayerDirectX11::DX11Device* pOut = new AstralLayerDirectX11::DX11Device();
	if (pOut->Create()== false)
	{
		ATLAssertMessage(false, "Deviceの作成に失敗しました");
		delete pOut;
		pOut = nullptr;
	}

	return pOut;
}

void AstralLayerFactory::ATLDX11Factory::Release()
{
	delete this;
}
