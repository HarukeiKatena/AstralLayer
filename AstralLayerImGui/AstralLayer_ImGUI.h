/****************************************************************//**
 * AstralLayer�p��ImGui�Ǘ����C�u����
 *******************************************************************/
#pragma once
#include"ImGUI/imgui.h"

/// @cond
/// �O���錾
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
	 * �E�B���h�E�v���V�[�W���ɋL������
	*******************************************************************/
	bool ImGuiWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	/****************************************************************//**
	 * ImGui���g����悤�ɂ���֐�
	 *******************************************************************/
	bool ImGuiInit(
		HWND hWnd,
		AstralLayer::ATLIDevice* pDevice);

	/****************************************************************//**
	 * ImGui�`��J�n
	 *******************************************************************/
	void ImGuiBegin();

	/****************************************************************//**
	 * ImGui�`��
	 * ATLICommandQueue::ExecuteCommandLists()�̑O�ɋL������
	 *******************************************************************/
	AstralLayer::ATLICommandList* ImGuiRenderer(
		AstralLayer::ATLIFence* pFence,
		AstralLayer::ATLIRenderTargetView* pRenderTargetView);

	/****************************************************************//**
	 * ImGui�`��I��
	 * ATLISwapChain::Present()�̒��O�ɋL������
	 *******************************************************************/
	void ImGuiEnd();

	/****************************************************************//**
	 * ImGui���
	 *******************************************************************/
	void ImGuiRelease();

	/****************************************************************//**
	 * ImGUI�f��
	 *******************************************************************/
	void ImGuiDemo();
}





