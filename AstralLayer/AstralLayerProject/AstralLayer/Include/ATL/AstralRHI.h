/****************************************************************//**
 * @file AstralRHI.h
 *******************************************************************/
#pragma once
#include"../AstralLayer.h"

namespace AstralRHI
{
	/****************************************************************//**
	 * ���\�[�X��RHI
	 * @see AstralLayer::ATLIResource
	 *******************************************************************/
	class RHIResource : public AstralLayer::ATLIResource
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * �����_�[�^�[�Q�b�g�r���[��RHI
	 * @see AstralLayer::ATLIRenderResourceView
	 *******************************************************************/
	class RHIRenderTargetView : public AstralLayer::ATLIRenderTargetView
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * �f�v�X�X�e���V���r���[��RHI
	 * @see AstralLayer::ATLIDepthStencilView
	 *******************************************************************/
	class RHIDepthStencilView : public AstralLayer::ATLIDepthStencilView
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * �f�o�C�X��RHI
	 * @see AstralLayer::ATLIDevice
	 *******************************************************************/
	class RHIDevice : public AstralLayer::ATLIDevice
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * �R�}���h���X�g��RHI
	 * @see AstralLayer::ATLICommandList
	 *******************************************************************/
	class RHICommandList : public AstralLayer::ATLICommandList
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * �p�C�v���C����RHI
	 * @see AstralLayer::ATLIPipeLine
	 *******************************************************************/
	class RHIPipeLine : public AstralLayer::ATLIPipeLine
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * �R�}���h�L���[��RHI
	 * @see AstralLayer::ATLICommandQueue
	 *******************************************************************/
	class RHICommandQueue : public AstralLayer::ATLICommandQueue
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * �t�F���X��RHI
	 * @see AstralLayer::ATLIFence
	 *******************************************************************/
	class RHIFence: public AstralLayer::ATLIFence
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * �X���b�v�`�F�C����RHI
	 * @see AstralLayer::ATLISwapChain
	 *******************************************************************/
	class RHISwapChain : public AstralLayer::ATLISwapChain
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * ���[�g�V�O�l�`���[��RHI
	 * @see AstralLayer::ATLIRootSignature
	 *******************************************************************/
	class RHIRootSignature : public AstralLayer::ATLIRootSignature
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};
}