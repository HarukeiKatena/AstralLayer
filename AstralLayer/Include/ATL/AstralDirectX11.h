/****************************************************************//**
 * @file AstralDirectX11.h
 *******************************************************************/
#pragma once
#include"AstralRHI.h"
#include"../AstralRendererInterface.h"


namespace AstralLayerDirectX11
{
	/****************************************************************//**
	 * ATL_RESOURCE_TYPEをD3D11_USAGEに変換
	 *******************************************************************/
	D3D11_USAGE ConvDX11Usage(ATL_RESOURCE_TYPE type);

	/****************************************************************//**
	 * MSAAで利用できる
	 *******************************************************************/
	DXGI_SAMPLE_DESC GetMSAA(ID3D11Device* pDevice, unsigned int Count);

	/****************************************************************//**
	 * DX11で利用するルートパラメーター
	 *******************************************************************/
	struct DX11RootParametor
	{
		ATL_ROOT_PARAMETER* pParameters;
		unsigned int NumRootParametors;
	};

	/****************************************************************//**
	 * DX11で利用するサンプラー
	 *******************************************************************/
	struct DX11Sampler
	{	
		unsigned int SamplerRegister;
		ATL_SHADER_VISIBILITY SamplerVisibility;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState = nullptr;
	};

	/****************************************************************//**
	 * DX11で利用するサンプラーデスク
	 *******************************************************************/
	struct DX11SamplerDesc
	{
		DX11Sampler* pSampler;
		unsigned int NumSampler;
	};
	

	/****************************************************************//**
	 * DX11で利用するパイプライン構造体
	 *******************************************************************/
	struct DX11PipeLineState
	{
		Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout = nullptr;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader = nullptr;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader = nullptr;

		Microsoft::WRL::ComPtr<ID3D11BlendState> BlendState = nullptr;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> Rasterizer = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> DepthStencil = nullptr;

		DX11RootParametor Parametor = {};
		DX11SamplerDesc Sampler = {};
	};
	
	static const int DEVICE_DEVICE = 0; //!< AstralDirectX11::DX11Device::Gethandle()のHandleで利用する定数

	/****************************************************************//**
	 * DX11デバイス
	 *******************************************************************/
	class DX11Device : public AstralRHI::RHIDevice
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Device5> m_pDevice = nullptr; //!< DX11デバイス

	public:
		
		/****************************************************************//**
		 *  デストラクタ
		 *******************************************************************/
		virtual ~DX11Device();

		/****************************************************************//**
		 * @see AstralLayer::ATLIDevice::CreateResource()
		 *******************************************************************/
		AstralLayer::ATLIResource* CreateResource(
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData
		) override;

		/****************************************************************//**
		 * @see AstralLayer::ATLIDevice::CreatePipeLine()
		 *******************************************************************/
		AstralLayer::ATLIPipeLine* CreatePipeLine(
			ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc
		)override;

		/****************************************************************//**
		 * @see AstralLayer::ATLIDevice::CreateDepthStencilView()
		 *******************************************************************/
		AstralLayer::ATLIDepthStencilView* CreateDepthStencilView(
			ATL_DEPTH_STENCIL_VIEW_DESC& Desc
		)override;

		/****************************************************************//**
		 * @see AstralLayer::ATLIDevice::CreateCommandList()
		 *******************************************************************/
		AstralLayer::ATLICommandList* CreateCommandList()override;

		/****************************************************************//**
		 * @see AstralLayer::ATLIDevice::CreateCommandQueue()
		 *******************************************************************/
		AstralLayer::ATLICommandQueue* CreateCommandQueue()override;

		/****************************************************************//**
		 * @see AstralLayer::ATLIDevice::CreateSwapChain()
		 *******************************************************************/
		AstralLayer::ATLISwapChain* CreateSwapChain(
			ATL_SWAPCHAIN_DESC& Desc,
			AstralLayer::ATLICommandQueue* pCommandQueue
		)override;

		/****************************************************************//**
		 * @see AstralLayer::ATLIDevice::CreateFence()
		 *******************************************************************/
		AstralLayer::ATLIFence* CreateFence()override;

		/****************************************************************//**
		 * @see AstralLayer::ATLIDevice::CreateRenderTrgetView()
		 *******************************************************************/
		AstralLayer::ATLIRenderTargetView* CreateRenderTargetView(
			AstralLayer::ATLISwapChain* pSwapChain,
			unsigned int ScreenWidth,
			unsigned int ScreenHeight
		)override;

		/****************************************************************//**
		 * @see AstralLayer::ATLIDevice::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 * @see AstralRHI::RHIDevice::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut, 
			int Handle
		)override;

		/****************************************************************//**
		 *  デバイス作成関数
		 * 
		 * \return 結果の正負
		 *******************************************************************/
		bool Create();
	};


	static const int COMMANDLIST_CONTEXT = 0; //!< AstralDirectX11::DX11CommandList::GetHandle()で利用する定数
	static const int COMMANDLIST_COMMAND = 1; //!< AstralDirectX11::DX11CommandList::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX11コマンドリスト
	 *******************************************************************/
	class DX11CommandList : public AstralRHI::RHICommandList
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeferredContext = nullptr;	//!< デファードコンテキスト
		ID3D11CommandList* m_pCommandList = nullptr;		//!< コマンドリスト

		DX11RootParametor* m_pRootDesc = {};				//!< DX11用ルートパラメーター

	private:
		void SetCBV(ATL_ROOT_PARAMETER* para, ID3D11Buffer* buffer);			//!< CBVをコマンドにセットする関数
		void SetSRV(ATL_ROOT_PARAMETER* para, ID3D11ShaderResourceView* srv);	//!< SRVをコマンドにセットする関数

		D3D11_PRIMITIVE_TOPOLOGY ConvToporogy(ATL_PRIMITIVE_TOPOLOGY toporogy);	//!< ATL_PRIMITIVE_TOPOLOGYをD3D11_PRIMITIVE_TOPOLOGYに変換する

	public:
		/****************************************************************//**
		 *  デストラクタ
		 *******************************************************************/
		virtual ~DX11CommandList();

		/****************************************************************//**
		 * コマンド作成関数
		 * 
		 * \param pDevice [in] DX11のデバイス
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice
		);

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::Reset()
		 *******************************************************************/
		bool Reset(
			AstralLayer::ATLIPipeLine* pPipeLine,
			AstralLayer::ATLIFence* pFence
		) override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::SetResource()
		 *******************************************************************/
		void SetResource(
			unsigned int StartRootParametorIndex,
			AstralLayer::ATLIResource* pResource,
			unsigned int NumResourceIDs,
			unsigned int* pResourceIDs
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::SetViewports()
		 *******************************************************************/
		void SetViewports(
			unsigned int NumViewports, 
			ATL_VIEWPORT* pViewports
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::SetScissorRects()
		 *******************************************************************/
		void SetScissorRects(
			unsigned int NumRects, 
			ATL_RECT* pRects
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::SetPrimitiveTopology()
		 *******************************************************************/
		void SetPrimitiveTopology(
			ATL_PRIMITIVE_TOPOLOGY Topology
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::SetVertexBuffer()
		 *******************************************************************/
		void SetVertexBuffer(
			AstralLayer::ATLIResource* pVertex, 
			unsigned int ResourceID
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::SetIndexBuffer()
		 *******************************************************************/
		void SetIndexBuffer(
			AstralLayer::ATLIResource* pIndexBuffer, 
			unsigned int ResourceID
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::ResourceBarrier()
		 *******************************************************************/
		void ResourceBarrier(
			ATL_RESOURCE_BARRIER& Barrier
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::SetRenderTargets()
		 *******************************************************************/
		void SetRenderTargets(
			AstralLayer::ATLIRenderTargetView* pRenderTargetView,
			AstralLayer::ATLIDepthStencilView* pDepthStencilView
		) override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::ClearRenderTargetView()
		 *******************************************************************/
		void ClearRenderTargetView(
			AstralLayer::ATLIRenderTargetView* pRenderTargetView,
			const float ColorRGBA[4]
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::ClearDepthStencilView()
		 *******************************************************************/
		void ClearDepthStencilView(
			AstralLayer::ATLIDepthStencilView* pDepthStencilView,
			ATL_CLEAR_FLAG ClearFlags,
			float Depth,
			unsigned char Stencil
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::DrawInstanced()
		 *******************************************************************/
		void DrawInstanced(
			unsigned int VertexCountParInstance,
			unsigned int InstanceCount,
			unsigned int StartVertexLocation,
			unsigned int StartInstanceLocation
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::DrawIndexedInstanced()
		 *******************************************************************/
		void DrawIndexedInstanced(
			unsigned int IndexCountParInstance,
			unsigned int InstanceCount,
			unsigned int StartIndexLocation,
			unsigned int BaceVertexLocation,
			unsigned int StartInstanceLocation
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::Close()
		 *******************************************************************/
		bool Close()override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandList::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHICommandList::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut, 
			int Handle
		)override;
	};

	static const int COMMANDQUEUE_CONTEXT = 0; //!< AstralDirectX11::DX11CommandQueue::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX11コマンドキュー
	 *******************************************************************/
	class DX11CommandQueue : public AstralRHI::RHICommandQueue
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext4> m_pImmidiateContext = nullptr; //!< イミディエイトコンテキスト

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX11CommandQueue();

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandQueue::ExecuteCommandLists()
		 *******************************************************************/
		bool ExecuteCommandLists(
			unsigned int NumCommandLists,
			AstralLayer::ATLICommandList* const* ppCommandLists
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandQueue::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHICommandQueue::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut,
			int Handle
		)override;

		/****************************************************************//**
		 *  コマンドキュー作成関数
		 * 
		 * \param pDevice [in] DirectX11のデバイス
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice
		);
	};

	static const int SWAPCHAIN_SWAPCHAIN = 0; //!< AstralDirectX11::DX11SwapChain::Gethandle()のHandleで利用する定数

	/****************************************************************//**
	 * DX11スワップチェイン
	 *******************************************************************/
	class DX11SwapChain : public AstralRHI::RHISwapChain
	{
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain3> m_pSwapChain = nullptr; //!< スワップチェイン

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX11SwapChain();

		/****************************************************************//**
		 * @see Astrallayer::ATLISwapChain::Present()
		 *******************************************************************/
		void Present(
			unsigned int SyncInterval
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLISwapChain::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHISwapChain::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut, 
			int Handle
		)override;

		/****************************************************************//**
		 *  スワップチェイン作成関数
		 * 
		 * \param pDevice [in] DX11のデバイス
		 * \param Desc [in] スワップチェインデスク
		 * \param pCommandQueue [in] コマンドキュー
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice,
			ATL_SWAPCHAIN_DESC& Desc,
			AstralLayer::ATLICommandQueue* pCommandQueue
		);
	};

	static const int RTV_RTV = 0; //!< AstralDirectX11::DX11RenderTargetView::Gethandle()のHandleで利用する定数

	/****************************************************************//**
	 * DX11レンダーターゲットビュー
	 *******************************************************************/
	class DX11RenderTargetView : public AstralRHI::RHIRenderTargetView
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTarget = nullptr; //<! レンダーターゲットビュー
	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		~DX11RenderTargetView();

		/****************************************************************//**
		 * @see Astrallayer::ATLIRenderTargetView::GetResource()
		 *******************************************************************/
		AstralLayer::ATLIResource* GetResource(
			AstralLayer::ATLIFence* pFence
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIRenderTargetView::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHIRenderTargetView::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut,
			int Handle
		) override;

		/****************************************************************//**
		 *  レンダーターゲットビュー作成関数
		 * 
		 * \param pDevice [in] DX11のデバイス
		 * \param pSwapChain [in] スワップチェイン　NULLでもよい
		 * \param ScreenWidth [in] 画面幅
		 * \param ScreenHeight [in] 画面高さ
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice,
			IDXGISwapChain* pSwapChain,
			unsigned int ScreenWidth,
			unsigned int ScreenHeight);
	};

	static const unsigned int DSV_DSV = 0; //!< AstralDirectX11::DX11DepthStencilView::Gethandle()のHandleで利用する定数

	/****************************************************************//**
	 * DX11デプスステンシルビュー
	 *******************************************************************/
	class DX11DepthStencilView : public AstralRHI::RHIDepthStencilView
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pView = nullptr; //!< デプスステンシルビュー

	private:
		D3D11_DSV_DIMENSION ConvDimension(ATL_DSV_DIMENSION Dimension);

	public:
		/****************************************************************//**
		 *  デストラクタ
		 *******************************************************************/
		virtual ~DX11DepthStencilView();

		/****************************************************************//**
		 * @see Astrallayer::ATLIDepthStencilView::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHIDepthStencilView::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut, 
			int Handle
		)override;

		/****************************************************************//**
		 * デプスステンシルビュー作成関数
		 * 
		 * \param pDevice [in] DX11のデバイス
		 * \param Desc [in] デプスステンシルビューのデスク
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice,
			ATL_DEPTH_STENCIL_VIEW_DESC& Desc
		);

	};

	static const int RESOURCE_FORMAT = -2;			//!< AstralDirectX11::DX11Resource::Gethandle()のHandleで利用する定数
	static const int RESOURCE_STRUCTURESIZE = -1;	//!< AstralDirectX11::DX11Resource::Gethandle()のHandleで利用する定数
	static const int RESOURCE_BUFFER = 0;			//!< AstralDirectX11::DX11Resource::Gethandle()のHandleで利用する定数

	/****************************************************************//**
	 * DX11リソース
	 *******************************************************************/
	class DX11Resource : public AstralRHI::RHIResource
	{
	protected:
		unsigned int m_StructureSize = 0;					//!< 構造体のバイト数
		unsigned int m_Width = 0;							//!< 幅
		unsigned int m_ObjectSize = 0;						//!< オブジェクト数
		Microsoft::WRL::ComPtr<ID3D11Buffer>* m_pBufferArray = nullptr;			//!< バッファー配列
		unsigned int m_UseIndex = 0;						//!< 現在選択しているインデックス
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pImmidiateContext = nullptr;	//!< イミディエイトコンテキスト
		DXGI_FORMAT m_Format = DXGI_FORMAT_UNKNOWN;			//!< フォーマット

	protected:
		static const int ALIGNMENT = 0x10;									//!< アライメント数値
		static const int DECREMENT_ALIGNMENT = ALIGNMENT - 1;				//!< アライメントを-1する
		static const int NOT_DECREMENT_ALIGNMENT = ~(DECREMENT_ALIGNMENT);	//!< アライメントを-1した数値をビット反転する
		const unsigned long CalcAlignment(unsigned long size);				//!< 指定した数値のアライメントされた数値を計算

		D3D11_BIND_FLAG ConvBindFlag(ATL_RESOURCE_FLAG flag);				//!< ATL_RESOURCE_FLAGをD3D11_BIND_FLAGに変換する
		

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX11Resource();


		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::SetSubResource()
		 *******************************************************************/
		unsigned int SetSubResource(
			const void* pData, 
			unsigned int SetByteSize
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::UpdateSubResource()
		 *******************************************************************/
		bool UpdateSubResource(
			unsigned int SubResourceID,
			unsigned int MoveByte,
			const void* pData,
			unsigned int UpdateByteSize
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHIResource::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut,
			int Handle
		)override;

		/****************************************************************//**
		 * リソース作成クラス
		 * 
		 * \param pDevice [in] DX11のデバイス
		 * \param Desc [in] リソースデスク
		 * \param pSrcData [in] 初期化データ
		 * \return 結果の正負
		 *******************************************************************/
		bool CreateResource(
			ID3D11Device* pDevice,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData);

	};

	static const int TEXTURE2D_TEXTURE = 0; //!< AstralDirectX11::DX11Texture2D::Gethandle()のHandleで利用する定数

	/****************************************************************//**
	 * DX11テクスチャ
	 *******************************************************************/
	class DX11Texture2D : public AstralRHI::RHIResource
	{
	private:
		unsigned int m_ByteSize = 0;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_pTexture = nullptr;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pSRV = nullptr;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pImmidiateContext = nullptr;

	public:
		virtual ~DX11Texture2D();

		/****************************************************************//**
		 * @see Astrallayer::ATLITexture2D::SetSubResource()
		 *******************************************************************/
		unsigned int SetSubResource(
			const void* pData, 
			unsigned int SetByteSize
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::UpdateSubResource()
		 *******************************************************************/
		bool UpdateSubResource(
			unsigned int SubResourceID,
			unsigned int MoveByte,
			const void* pData,
			unsigned int UpdateByteSize
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHIResource::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut, 
			int Handle
		)override;

		/****************************************************************//**
		 * テクスチャ2D作成
		 * 
		 * \param pDevice [in] DX11のデバイス
		 * \param Desc [in] リソースデスク
		 * \param pSrcData [in] 初期化データ
		 * \return 結果の正負
		 *******************************************************************/
		bool CreateTexture2D(
			ID3D11Device* pDevice,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData
		);
	};

	/****************************************************************//**
	 * DX11レンダーターゲットビューの戻り値で利用するリソース
	 *******************************************************************/
	class DX11RTVResource : public AstralRHI::RHIResource
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Resource> m_pBuffer = nullptr; //!< バッファー

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX11RTVResource();

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::SetSubResource()
		 *******************************************************************/
		unsigned int SetSubResource(
			const void* pData,
			unsigned int SetByteSize
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::UpdateSubResource()
		 *******************************************************************/
		bool UpdateSubResource(
			unsigned int SubResourceID,
			unsigned int MoveByte,
			const void* pData,
			unsigned int UpdateByteSize
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHIResource::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut,
			int Handle
		)override;

		/****************************************************************//**
		 * バッファーをセットする
		 * 
		 * \param pBuffer バッファーデータ
		 *******************************************************************/
		void SetBuffer(ID3D11Resource* pBuffer);
	};

	static const int FENCE_FENCE = 0; //!< AstralDirectX11::DX11Fence::Gethandle()のHandleで利用する定数

	/****************************************************************//**
	 * DX11フェンス
	 *******************************************************************/
	class DX11Fence : public AstralRHI::RHIFence
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Fence> m_pFence = nullptr;		//!< フェンスクラス
		HANDLE m_fenceEvent = NULL;				//!< イベントハンドル
		unsigned long long m_fenceValue = 0;	//!< フェンスカウンタ

	public:

		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		~DX11Fence();

		/****************************************************************//**
		 * @see Astrallayer::ATLIFence::WaitDrawDone()
		 *******************************************************************/
		void WaitDrawDone(
			AstralLayer::ATLICommandQueue* pCommandQueue,
			AstralLayer::ATLISwapChain* pSwapChain
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIFence::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHIFence::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppResource, 
			int Handle
		)override;

		/****************************************************************//**
		 * フェンス作成関数
		 * 
		 * \param pDevice [in] DX11のデバイス
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D11Device5* pDevice
		);
	};

	static const int PIPELINE_PIPELINE = 0; //!< AstralDirectX11::DX11PipeLine::Gethandle()のHandleで利用する定数 

	/****************************************************************//**
	 * DX11パイプライン
	 *******************************************************************/
	class DX11PipeLine : public AstralRHI::RHIPipeLine
	{
	private:
		DX11PipeLineState m_State = {}; //!< パイプラインステート

	private:
		D3D11_BLEND CalcBlend(ATL_BLEND blend);							//!< ATL_BLENDをD3D11_BLENDに変換する
		D3D11_BLEND_OP CalcBlendOp(ATL_BLEND_OP op);					//!< ATL_BLEND_OPをD3D11_BLEND_OPに変換する
		D3D11_FILL_MODE CalcFill(ATL_FILL_MODE fill);					//!< ATL_FILL_MODEをD3D11_FILL_MODEに変換する
		D3D11_CULL_MODE CalcCull(ATL_CULL_MODE cull);					//!< ATL_CULL_MODEをD3D11_CULL_MODEに変換する
		D3D11_DEPTH_WRITE_MASK CalcWriteMask(ATL_DEPTH_WRITE_MASK mask);//!< ATL_DEPTH_WRITE_MASKをD3D11_DEPTH_WRITE_MASKに変換する
		D3D11_COMPARISON_FUNC CalcFunc(ATL_COMPARISON_FUNC func);		//!< ATL_COMPARISON_FUNCをD3D11_COMPARISON_FUNCに変換する
		D3D11_STENCIL_OP CalcStencilOp(ATL_STENCIL_OP op);				//!< ATL_STENCIL_OPをD3D11_STENCIL_OPに変換する
		D3D11_FILTER ConvFilter(ATL_FILTER Filter);							//!< ATL_FILTERをD3D11_FILTERに変換する
		D3D11_TEXTURE_ADDRESS_MODE ConvAddressMode(ATL_ADDRESS_MODE mode);	//!< ATL_ADDRESS_MODEをD3D11_TEXTURE_ADDRESS_MODEに変換する
		D3D11_COMPARISON_FUNC ConvComparisonFunc(ATL_COMPARISON_FUNC func);	//!< ATL_COMPARISON_FUNCをD3D11_COMPARISON_FUNCに変換する
		void ConvBorderColor(ATL_BORDER_COLOR border, float* out_color);	//!< ATL_BORDER_COLORをfloat[4]に変換する


		bool CreateVertexShader(
			ID3D11Device* pDevice, 
			ATL_SHADER_BYTECODE& vs, 
			ATL_INPUT_LAYOUT_DESC& input); //!< 頂点シェーダー作成関数
		bool CreatePixelShader(ID3D11Device* pDevice, ATL_SHADER_BYTECODE& ps); //!< ピクセルシェーダー作成関数
		bool CreateBlendState(ID3D11Device* pDevice, ATL_BLEND_DESC& blend); //!< ブレンドステート作成関数
		bool CreateRasterizer(ID3D11Device* pDevice, ATL_RASTERIZER_DESC& rasterizer);//!< ラスタライザー作成関数
		bool CreateDepthStencilDesc(ID3D11Device* pDevice, ATL_DEPTH_STENCIL_DESC ds);//!< デプスステンシルデスク作成関数

		bool CreateRootSignature(ATL_ROOT_PARAMETER* root, unsigned int num); //!< ルートシグネチャー作成関数
		bool CreateSampler(ID3D11Device* pDevice, ATL_SAMPLER_DESC* sampler, unsigned int num); //!< サンプラー作成関数

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX11PipeLine();

		/****************************************************************//**
		 * @see Astrallayer::ATLIPipeLine::ImGuiRelease()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHIPipeLine::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut, 
			int Handle
		)override;

		/****************************************************************//**
		 * パイプライン作成関数
		 * 
		 * \param pDevice [in] DX11デバイス
		 * \param pRootSignature [in] ルートシグネチャー
		 * \param Desc [in] グラフィクスパイプラインデスク
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice,
			ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc
		);
	};
}
