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

/****************************************************************//**
 * �E�B���h�E�v���V�[�W���ɋL������
 *******************************************************************/
bool ImGuiWndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

/****************************************************************//**
 * ImGui���g����悤�ɂ���֐�
 *******************************************************************/
bool ImGUIInit(
	HWND hWnd,
	AstralLayer::ATLIDevice* pDevice);

/****************************************************************//**
 * ImGui�`��J�n
 *******************************************************************/
void ImGuiBegin();

/****************************************************************//**
 * ImGui�`��I��
 *******************************************************************/
AstralLayer::ATLICommandList* ImGuiEnd(
	AstralLayer::ATLIFence* pFence,
	AstralLayer::ATLIRenderTargetView* pRenderTargetView);

/****************************************************************//**
 * ImGui���
 *******************************************************************/
void ImGuiRelease();

/****************************************************************//**
 * ImGUI�f��
 *******************************************************************/
void ImGuiDemo();



