#pragma once
#include"../../AstralLayer/Include/AstralLayer.h"
#include"../../AstralLayer/Include/ATL/AstralDirectX11.h"
#include"../../AstralLayer/Include/ATL/AstralDirectX12.h"

namespace AstralImGui
{
	class ATLIImGui
	{
	protected:
		AstralLayer::ATLICommandList* m_pCommandList = nullptr;

	public:
		virtual ~ATLIImGui() 
		{
			if (m_pCommandList != nullptr)
				m_pCommandList->Release();
		}

		/****************************************************************//**
		 * 特定のインターフェースに対応したImGui作成関数\n
		 * ImGui本体の作成処理はしない
		 * 
		 * \param pDevice		デバイス
		 * \param pCommandList	コマンドリスト	
		 * \return 
		 *******************************************************************/
		virtual bool Create(
			AstralLayer::ATLIDevice* pDevice,
			AstralLayer::ATLICommandList* pCommandList
		) = 0;

		/****************************************************************//**
		 * 描画開始 
		 *******************************************************************/
		virtual void Begin() = 0;

		/****************************************************************//**
		 * 描画終了 
		 * 
		 * \param pFence			フェンス
		 * \param pRenderTargetView レンダーターゲットビュー
		 * \return コマンドリスト
		 *******************************************************************/
		virtual AstralLayer::ATLICommandList* End(
			AstralLayer::ATLIFence* pFence,
			AstralLayer::ATLIRenderTargetView* pRenderTargetView) = 0;
	};

	class DX11ImGui : public ATLIImGui
	{
	public:
		virtual ~DX11ImGui();

		/****************************************************************//**
		 * @see AstralImGui::ATLIImGui::Create()
		 *******************************************************************/
		bool Create(
			AstralLayer::ATLIDevice* pDevice,
			AstralLayer::ATLICommandList* pCommandList
		)override;

		/****************************************************************//**
		 * @see AstralImGui::ATLIImGui::ImGuiBegin()
		 *******************************************************************/
		void Begin()override;

		/****************************************************************//**
		 * @see AstralImGui::ATLIImGui::ImGuiEnd()
		 *******************************************************************/
		AstralLayer::ATLICommandList* End(
			AstralLayer::ATLIFence* pFence,
			AstralLayer::ATLIRenderTargetView* pRenderTargetView
		)override;
	};

	class DX12ImGui : public ATLIImGui
	{
	private:
		ID3D12DescriptorHeap* m_prtvHeap = nullptr;

	public:
		~DX12ImGui();

		/****************************************************************//**
		 * @see AstralImGui::ATLIImGui::Create()
		 *******************************************************************/
		bool Create(
			AstralLayer::ATLIDevice* pDevice,
			AstralLayer::ATLICommandList* pCommandList
		)override;

		/****************************************************************//**
		 * @see AstralImGui::ATLIImGui::ImGuiBegin()
		 *******************************************************************/
		void Begin()override;

		/****************************************************************//**
		 * @see AstralImGui::ATLIImGui::ImGuiEnd()
		 *******************************************************************/
		AstralLayer::ATLICommandList* End(
			AstralLayer::ATLIFence* pFence,
			AstralLayer::ATLIRenderTargetView* pRenderTargetView
		)override;
	};
}
