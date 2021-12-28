/****************************************************************//**
 * @file AstralRHI.h
 *******************************************************************/
#pragma once
#include"../AstralLayer.h"

namespace AstralRHI
{
	/****************************************************************//**
	 * リソースのRHI
	 * @see AstralLayer::ATLIResource
	 *******************************************************************/
	class RHIResource : public AstralLayer::ATLIResource
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * レンダーターゲットビューのRHI
	 * @see AstralLayer::ATLIRenderResourceView
	 *******************************************************************/
	class RHIRenderTargetView : public AstralLayer::ATLIRenderTargetView
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * デプスステンシルビューのRHI
	 * @see AstralLayer::ATLIDepthStencilView
	 *******************************************************************/
	class RHIDepthStencilView : public AstralLayer::ATLIDepthStencilView
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * デバイスのRHI
	 * @see AstralLayer::ATLIDevice
	 *******************************************************************/
	class RHIDevice : public AstralLayer::ATLIDevice
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * コマンドリストのRHI
	 * @see AstralLayer::ATLICommandList
	 *******************************************************************/
	class RHICommandList : public AstralLayer::ATLICommandList
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * パイプラインのRHI
	 * @see AstralLayer::ATLIPipeLine
	 *******************************************************************/
	class RHIPipeLine : public AstralLayer::ATLIPipeLine
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * コマンドキューのRHI
	 * @see AstralLayer::ATLICommandQueue
	 *******************************************************************/
	class RHICommandQueue : public AstralLayer::ATLICommandQueue
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * フェンスのRHI
	 * @see AstralLayer::ATLIFence
	 *******************************************************************/
	class RHIFence: public AstralLayer::ATLIFence
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * スワップチェインのRHI
	 * @see AstralLayer::ATLISwapChain
	 *******************************************************************/
	class RHISwapChain : public AstralLayer::ATLISwapChain
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};

	/****************************************************************//**
	 * ルートシグネチャーのRHI
	 * @see AstralLayer::ATLIRootSignature
	 *******************************************************************/
	class RHIRootSignature : public AstralLayer::ATLIRootSignature
	{
	public:
		virtual void GetHandle(void** ppOut, int Handle) = 0;
	};
}