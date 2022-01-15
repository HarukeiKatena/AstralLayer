/****************************************************************//**
 * @file AstralDirectX12Factory.h
 *******************************************************************/
#pragma once
#include"../AstralLayerFactory.h"
#include"AstralDirectX12.h"

namespace AstralLayerFactory
{
	/****************************************************************//**
	 * DX12ファクトリー
	 *******************************************************************/
	class ATLDX12Factory : public ATLIFactory
	{
	private:
		Microsoft::WRL::ComPtr<IDXGIFactory4> m_pFactory = nullptr; //!< ファクトリー

	private:
		IDXGIFactory4* CreateFactory(); //!< ファクトリ作成関数

	public:
		/****************************************************************//**
		 * コンストラクタ
		 *******************************************************************/
		ATLDX12Factory();

		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~ATLDX12Factory();

		/****************************************************************//**
		 *  @see AstralLayerFactory::ATLIFactory::CreateDevice()
		 *******************************************************************/
		AstralLayer::ATLIDevice* CreateDevice()override;

		/****************************************************************//**
		 *  @see AstralLayerFactory::ATLIFactory::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 * DirectX12のデバッグ機能をONにする
		 *******************************************************************/
		void EnableDebug();
	};
}