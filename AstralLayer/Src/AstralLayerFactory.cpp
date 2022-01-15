#include"../Include/AstralLayer.h"
#include"../Include/AstralLayerFactory.h"
#include"../Include/ATL/AstralDirectX11Factory.h"
#include"../Include/ATL/AstralDirectX12Factory.h"
#include"../Include/AstralDebug.h"

AstralLayerFactory::ATLIFactory* AstralLayerFactory::CreateAstralFactory(
	ATL_GRAPHIC_INTERFACE GraphicInterface)
{
	switch (GraphicInterface)
	{
#if defined(ATLGI_DX11)//DirectX11
	case ATL_GRAPHIC_INTERFACE::DirectX11: return new AstralLayerFactory::ATLDX11Factory();
#endif

#if defined(ATLGI_DX12)//DirectX12
	case ATL_GRAPHIC_INTERFACE::DirectX12: return new AstralLayerFactory::ATLDX12Factory();
#endif
	default: return nullptr;
	}
}
