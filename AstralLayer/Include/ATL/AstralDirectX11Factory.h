/****************************************************************//**
 * @file AstralDirectX11Factory.h
 *******************************************************************/
#pragma once
#include"../AstralLayerFactory.h"

namespace AstralLayerFactory
{
	/****************************************************************//**
	 * DirectX11のファクトリー
	 * @see AstralLayerFactory::ATLIFactory
	 *******************************************************************/
	class ATLDX11Factory : public ATLIFactory
	{
	public:
		/****************************************************************//**
		 *  @see AstralLayerFactory::ATLIFactory::CreateDevice()
		 *******************************************************************/
		AstralLayer::ATLIDevice* CreateDevice()override;

		/****************************************************************//**
		 *  @see AstralLayerFactory::ATLIFactory::ImGuiRelease()
		 *******************************************************************/
		void Release()override;
	};
}