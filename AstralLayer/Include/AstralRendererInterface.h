/****************************************************************//**
 * @file AstralRendererInterface.h
 * @brief ���C�u�����ǂݍ��ݗp�w�b�_�[
 * 
 * - �w�肵���C���^�[�t�F�[�X�̂ݎg�������ꍇ\n\n
 * 
 * DirectX11\n
 * ATLRI_DIRECTX11\n\n
 * 
 * DirectX12\n
 * ATLRI_DIRECTX12\n\n
 * 
 * OpenGL\n
 * ATLRI_OPENGL\n\n
 * 
 * Vulkan\n
 * ATLRI_VULKAN
 *******************************************************************/
#pragma once

//-------------------------------------------------------------
// Windows�`�F�b�N
//-------------------------------------------------------------
#if defined(_WIN32) || defined(_WIN64)
#define ASTRAL_WINDOWS (1)
#include<Windows.h>
#endif

//-------------------------------------------------------------
// Mac�`�F�b�N
//-------------------------------------------------------------
#if defined(macintosh) || defined(Macintosh) || (defined(__APPLE__) && defined(__MACH__))
#define ASTRAL_MAC (1)
#endif

//=============================================================
// �����_�[�G���W���`�F�b�N
//=============================================================
#if defined(ATLRI_DIRECTX11) && defined(ASTRAL_WINDOWS)

//-------------------------------------------------------------
// DirectX11
#define ATLGI_DX11(1)
//-------------------------------------------------------------

#elif defined(ATLRI_DIRECTX12) && defined(ASTRAL_WINDOWS)

// DirectX12
#define ATLGI_DX12(1)

#elif defined(ATLRI_OPENGL)

//OpenGL


#elif defined(ATLRI_VULKAN)

//Vulkan


#else//���w��̏ꍇ

//-------------------------------------------------------------
//���w��̏ꍇ
#if defined(ASTRAL_WINDOWS)//������Windows�̂�
#define ATLGI_DX11 (1)
#define ATLGI_DX12 (1)
#else//Windows�ȊO�̏ꍇ��p��define��`
#define ATLGI_NOTDX11 (1)
#define ATLGI_NOTDX12 (1)
#endif
//-------------------------------------------------------------

#endif//�G���W���`�F�b�N

//-------------------------------------------------------------
// ���C�u�����ǂݍ���
//-------------------------------------------------------------
#if defined(ATLGI_DX11) || defined(ATLGI_DX12)
#include<dxgi1_4.h>
#pragma comment(lib, "dxgi.lib")
#include<wrl.h>
#endif

#if defined(ATLGI_DX12)
//-------------------------------------------------------------
//DirectX12
#include <d3d12.h>
#pragma comment (lib, "d3d12.lib")
//-------------------------------------------------------------
#endif

#if defined(ATLGI_DX11)
//-------------------------------------------------------------
//DirectX11
#include <d3d11_4.h>
#pragma comment (lib, "d3d11.lib")
//-------------------------------------------------------------
#endif

/****************************************************************//**
 * �O���t�B�b�N�C���^�[�t�F�[�X
 *******************************************************************/
enum class ATL_GRAPHIC_INTERFACE
{
	DirectX11,
	DirectX12,
	//OpenGL,
	//Vulkan,
};