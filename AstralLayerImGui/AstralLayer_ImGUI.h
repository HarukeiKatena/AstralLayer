/****************************************************************//**
 * AstralLayer用のImGui管理ライブラリ
 *******************************************************************/
#pragma once
#pragma warning(push)
#pragma warning(disable:26451)
#pragma warning(disable:6386)
#pragma warning(disable:4244)
#include"ImGUI/imgui.h"
#pragma warning(pop)
/// @cond
/// 前方宣言
namespace AstralLayer
{
	class ATLIDevice;
	class ATLICommandQueue;
	class ATLIRenderTargetView;
	class ATLICommandList;
	class ATLIFence;
}
/// @endcond
 
namespace AstralImGui
{
	/****************************************************************//**
	 * ウィンドウプロシージャに記入する
	*******************************************************************/
	bool ImGuiWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	/****************************************************************//**
	 * ImGuiを使えるようにする関数
	 *******************************************************************/
	bool ImGuiInit(
		HWND hWnd,
		AstralLayer::ATLIDevice* pDevice);

	/****************************************************************//**
	 * ImGui描画開始
	 *******************************************************************/
	void ImGuiBegin();

	/****************************************************************//**
	 * ImGui描画
	 * ATLICommandQueue::ExecuteCommandLists()の前に記入する
	 *******************************************************************/
	AstralLayer::ATLICommandList* ImGuiRenderer(
		AstralLayer::ATLIFence* pFence,
		AstralLayer::ATLIRenderTargetView* pRenderTargetView);

	/****************************************************************//**
	 * ImGui描画終了
	 * ATLISwapChain::Present()の直前に記入する
	 *******************************************************************/
	void ImGuiEnd();

	/****************************************************************//**
	 * ImGui解放
	 *******************************************************************/
	void ImGuiRelease();

	/****************************************************************//**
	 * ImGUIデモ
	 *******************************************************************/
	void ImGuiDemo();
}





