/****************************************************************//**
 * @file AstralDirectX12.h
 *******************************************************************/
#pragma once
#include"AstralRHI.h"
#include"../AstralRendererInterface.h"

namespace AstralLayerDirectX12
{
	/// @cond
	/// 前方宣言
	class DX12Device;
	class DX12CommandList;
	class DX12Resource;
	class DX12VertexBuffer;
	class DX12IndexBuffer;
	class DX12Texture2D;
	class DX12RenderTargetView;
	class DX12DepthStencilView;
	class DX12CommandQueue;
	class DX12PipeLine;
	class DX12Fence;
	class DX12SwapChain;
	class DX12DescriptorHeap;
	///@endcond
	 
	/****************************************************************//**
	*使用可能なMSAAの値を取得
	*******************************************************************/
	DXGI_SAMPLE_DESC GetMSAA(ID3D12Device * pDevice, unsigned int Count);
	
	static const int DEVICE_DEVICE = 0; //!< AstralDirectX12::DX12Device::Gethandle()のHandleで利用する定数

	/****************************************************************//**
	 * DX12デバイス
	 *******************************************************************/
	class DX12Device : public AstralRHI::RHIDevice
	{
	private:
		ID3D12Device* m_pDevice = nullptr;

	public:

		/****************************************************************//**
		 *  デストラクタ
		 *******************************************************************/
		virtual ~DX12Device();

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
		 * @see AstralLayer::ATLIDevice::Release()
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
		 * デバイス作成関数
		 * 
		 * \param pFactory [in] DXGIのファクトリー
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			IDXGIFactory1* pFactory
		);
	};

	static const int COMMANDLIST_COMMAND = 0;	//!< AstralDirectX12::DX12CommandList::GetHandle()で利用する定数
	static const int COMMANDLIST_ALLOCATOR = 1; //!< AstralDirectX12::DX12CommandList::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX11コマンドリスト
	 *******************************************************************/
	class DX12CommandList : public AstralRHI::RHICommandList
	{
	private:
		ID3D12GraphicsCommandList* m_pCommandList = nullptr;	//!< コマンドリスト
		ID3D12CommandAllocator* m_pAllocator = nullptr;			//!< アロケーター

		unsigned int m_BackBuffer = 0;							//!< バックバッファー

	private:
		D3D12_RESOURCE_STATES ConvState(ATL_RESOURCE_STATE state);							//!< ATL_RESOURCE_STATEをに変換する
		D3D12_PRIMITIVE_TOPOLOGY ConvTopology(ATL_PRIMITIVE_TOPOLOGY t);					//!< ATL_PRIMITIVE_TOPOLOGYをD3D12_PRIMITIVE_TOPOLOGYに変換する
		D3D12_CPU_DESCRIPTOR_HANDLE GetRTVHandle(AstralLayer::ATLIRenderTargetView* rtv);	//!< RTVのD3D12_CPU_DESCRIPTOR_HANDLEを受け取る
		D3D12_CPU_DESCRIPTOR_HANDLE GetDSVHandle(AstralLayer::ATLIDepthStencilView* dsv);	//!< DSVのD3D12_CPU_DESCRIPTOR_HANDLEを受け取る

	public:
		/****************************************************************//**
		 *  デストラクタ
		 *******************************************************************/
		virtual ~DX12CommandList();

		/****************************************************************//**
		 * コマンドリスト作成関数
		 * 
		 * \param pDevice [in] DX12のデバイス
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice
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
			unsigned int NumScissorRects, 
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
		 * @see Astrallayer::ATLICommandList::Release()
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

	static const int RESOURCE_DATA = -1;	//!< AstralDirectX12::DX12Resource::GetHandle()で利用する定数
	static const int RESOURCE_DRAW = 0;		//!< AstralDirectX12::DX12Resource::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX12リソース
	 *******************************************************************/
	class DX12Resource : public AstralRHI::RHIResource
	{
	protected:
		unsigned int m_StructureSize = 0;			//!< 構造体サイズ
		unsigned int m_Width = 0;					//!< 幅
		unsigned int m_ObjectSize = 0;				//!< オブジェクト数
		ID3D12Resource* m_pResourceArray = nullptr;	//!< リソース
		char* m_pSubResource = nullptr;				//!< サブリソース
		unsigned int m_UseIndex = 0;				//!< 現在選択してるインデックス

	protected:
		static const int ALIGNMENT = 0x100;									//!< アライメント数値
		static const int DECREMENT_ALIGNMENT = ALIGNMENT - 1;				//!< アライメント数値を-1する
		static const int NOT_DECREMENT_ALIGNMENT = ~(DECREMENT_ALIGNMENT);	//!< アライメント数値を-1してビットを反転する
		const unsigned long CalcAlignment(unsigned long size); //!< 指定した値をアライメントする

		/****************************************************************//**
		 * リソース作成関数
		 * 
		 * \param Device [in] DX12デバイス
		 * \param Desc [in] リソースデスク
		 * \param pSrcData [in] 初期化データ
		 * \return 結果の正負
		 *******************************************************************/
		bool CreateResource(
			ID3D12Device* Device,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData
		);
	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX12Resource();

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
		 * @see Astrallayer::ATLIResource::Release()
		 *******************************************************************/
		void Release()override;
	};

	/****************************************************************//**
	 * DX12定数バッファー
	 *******************************************************************/
	class DX12ConstantBuffer : public DX12Resource
	{
	private:
		ID3D12DescriptorHeap* m_pHeap = nullptr; //!< リソース

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX12ConstantBuffer();

		/****************************************************************//**
		 * 定数バッファ作成関数
		 * 
		 * \param pDevice [in] DX12のデバイス
		 * \param Desc [in] リソースデスク
		 * \param pSrcData [in] 初期化データ
		 * \return 結果の正負
		 *******************************************************************/
		bool CreateConstantBuffer(
			ID3D12Device* pDevice,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData
		);

		/****************************************************************//**
		 *  @see AstralRHI::RHIResource::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut, 
			int Handle
		) override;
	};

	/****************************************************************//**
	 * DX12頂点バッファー
	 *******************************************************************/
	class DX12VertexBuffer : public DX12Resource
	{
	private:
		D3D12_VERTEX_BUFFER_VIEW* m_pView = nullptr; //!< 頂点バッファービュー

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX12VertexBuffer();

		/****************************************************************//**
		 * 頂点バッファー作成関数
		 * 
		 * \param pDevice [in] DX12デバイス
		 * \param Desc [in] リソースデスク
		 * \param pSrcData [in] 初期化データ
		 * \return 結果の正負
		 *******************************************************************/
		bool CreateVertexBuffer(
			ID3D12Device* pDevice,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData
		);

		/****************************************************************//**
		 *  @see AstralRHI::RHIResource::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut, 
			int Handle
		) override;
	};

	/****************************************************************//**
	 * インデックスバッファー
	 *******************************************************************/
	class DX12IndexBuffer : public DX12Resource
	{
	private:
		D3D12_INDEX_BUFFER_VIEW* m_pView = nullptr; //!< インデックスバッファービュー

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX12IndexBuffer();

		/****************************************************************//**
		 * インデックスバッファ作成関数
		 * 
		 * \param pDevice [in] DX12のデバイス
		 * \param Desc [in] リソースデスク
		 * \param pSrcData [in] 初期化データ
		 * \return 結果の正負
		 *******************************************************************/
		bool CreateIndexBuffer(
			ID3D12Device* pDevice,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData
		);

		/****************************************************************//**
		 *  @see AstralRHI::RHIResource::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut, 
			int Handle
		) override;
	};

	static const int TEXTURE2D_HEAP = 0;	//!< AstralDirectX12::DX12Texture2D::GetHandle()で利用する定数
	static const int TEXTURE2D_TEXTURE = 1;	//!< AstralDirectX12::DX12Texture2D::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX12テクスチャ2D
	 *******************************************************************/
	class DX12Texture2D : public AstralRHI::RHIResource
	{
	private:
		ID3D12Resource* m_pTexture = nullptr;		//!< テクスチャ
		DXGI_FORMAT m_Format = DXGI_FORMAT_UNKNOWN;	//!< フォーマット
		unsigned int m_Width = 0;					//!< 幅
		unsigned int m_Height = 0;					//!< 高さ
		unsigned int m_FormatSize = 0;				//!< フォーマットサイズ
		ID3D12DescriptorHeap* m_pHeap = nullptr;	//!< ヒープ


		constexpr unsigned int CallRowPitch();	//!< 行の長さのサイズ計算
		constexpr unsigned int CallDepthPitch();//!< 全体の長さのサイズ計算
	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX12Texture2D();

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
		 * @see Astrallayer::ATLIResource::Release()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHIResource::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut, 
			int Handle
		) override;

		/****************************************************************//**
		 * テクスチャ2D作成関数
		 * 
		 * \param pDevice [in] DX12デバイス
		 * \param Desc [in] リソースデスク
		 * \param pSrcData [in] 初期化データ
		 * \return 血管お正負
		 *******************************************************************/
		bool CreateTexture(
			ID3D12Device* pDevice,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData
		);
	};

	static const int RTVRESOURCE_HEAP = 0;		//!< AstralDirectX12::DX12RTVResource::GetHandle()で利用する定数
	static const int RTVRESOURCE_RESOURCE = 1;	//!< AstralDirectX12::DX12RTVResource::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX12RenderTargetView::GetResource()で使う専用のリソース
	 * @attention このクラスの利用が終わったら必ずReleaseしてください。メモリリークの原因になります
	 *******************************************************************/
	class DX12RTVResource : public AstralRHI::RHIResource
	{
	private:
		ID3D12Resource* m_pResource = nullptr;	//!< リソースデータ
		ID3D12DescriptorHeap* m_pHeap = nullptr;//!< ヒープ

	public:
		/****************************************************************//**
		 * リソース情報をセットする
		 * 
		 * \param pResource [in] リソース
		 * \param pHeap [in] ヒープ
		 *******************************************************************/
		void SetResource(
			ID3D12Resource* pResource,
			ID3D12DescriptorHeap* pHeap
		);

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::SetSubResource()
		 * @attention この関数は機能しません
		 *******************************************************************/
		unsigned int SetSubResource(
			const void* pData, 
			unsigned int SetByteSize
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::UpdateSubResource()
		 * @attention この関数は機能しません
		 *******************************************************************/
		bool UpdateSubResource(
			unsigned int SubResourceID,
			unsigned int MoveByte,
			const void* pData,
			unsigned int UpdateByteSize
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::Release()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHIResource::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppOut,
			int Handle
		) override;
	};

	static const int RTV_HEAP = 0;		//!< AstralDirectX12::DX12RenderTargetView::GetHandle()で利用する定数
	static const int RTV_RESOURCE = 1;	//!< AstralDirectX12::DX12RenderTargetView::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX12レンダーターゲットビュー
	 *******************************************************************/
	class DX12RenderTargetView : public AstralRHI::RHIRenderTargetView
	{
	private:
		unsigned int m_ArraySize = 0;				//!< 配列サイズ
		ID3D12Resource** m_pRenderTargets = nullptr;//!< RTVリソース配列
		ID3D12DescriptorHeap* m_pHeap = nullptr;	//!< ヒープ

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX12RenderTargetView();

		/****************************************************************//**
		 * @see Astrallayer::ATLIRenderTargetView::GetResource()
		 *******************************************************************/
		AstralLayer::ATLIResource* GetResource(
			AstralLayer::ATLIFence* pFence
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIRenderTargetView::Release()
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
		 * レンダーターゲットビュー作成関数
		 * 
		 * \param pDevice [in] DX12のデバイス
		 * \param pSwapChain [in] スワップチェイン、nullでも良い
		 * \param ScreenWidth [in] 画面幅
		 * \param ScreenHeight [in] 画面高さ
		 * \return 
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice, 
			IDXGISwapChain* pSwapChain,
			unsigned int ScreenWidth,
			unsigned int ScreenHeight
		);
	};

	static const int DSV_HEAP = 0; //!< AstralDirectX12::DX12DepthStencilView::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX12デプスステンシルビュー
	 *******************************************************************/
	class DX12DepthStencilView : public AstralRHI::RHIDepthStencilView
	{
	private:
		ID3D12DescriptorHeap* m_pdsvHeap = nullptr;
		ID3D12Resource* m_pResource = nullptr;

	private:
		D3D12_DSV_DIMENSION ConvDimension(ATL_DSV_DIMENSION dimension);

	public:
		/****************************************************************//**
		 *  デストラクタ
		 *******************************************************************/
		virtual ~DX12DepthStencilView();

		/****************************************************************//**
		 * @see Astrallayer::ATLIDepthStencilView::Release()
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
		 * \param pDevice [in] DX12のデバイス
		 * \param Desc [in] デプスステンシルビューデスク
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice,
			ATL_DEPTH_STENCIL_VIEW_DESC& Desc
		);
	};

	static const int COMMANDQUEUE_QUEUE = 0; //!< AstralDirectX12::DX12CommandQueue::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX12コマンドキュー
	 *******************************************************************/
	class DX12CommandQueue : public AstralRHI::RHICommandQueue
	{
	private:
		ID3D12CommandQueue* m_pCommandQueue = nullptr; //!< コマンドキュー

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX12CommandQueue();

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandQueue::ExecuteCommandLists()
		 *******************************************************************/
		bool ExecuteCommandLists(
			unsigned int NumCommandLists,
			AstralLayer::ATLICommandList* const* ppCommandLists
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLICommandQueue::Release()
		 *******************************************************************/
		void Release()override;

		/****************************************************************//**
		 *  @see AstralRHI::RHICommandQueue::GetHandle()
		 *******************************************************************/
		void GetHandle(
			void** ppResource, 
			int Handle
		)override;

		/****************************************************************//**
		 * コマンドキュー作成関数
		 * 
		 * \param pDevice [in] DX12のデバイス
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice
		);
	};

	static const int PIPELINE_PIPELINE = 0;		//!< AstralDirectX12::DX12PipeLine::GetHandle()で利用する定数
	static const int PIPELINE_ROOTSIGNATURE = 1;//!< AstralDirectX12::DX12PipeLine::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX12パイプライン
	 *******************************************************************/
	class DX12PipeLine : public AstralRHI::RHIPipeLine
	{
	private:
		ID3D12PipelineState* m_pPipeLine = nullptr;			//!< パイプラインステート
		ID3D12RootSignature* m_pRootSignature = nullptr;	//!< ルートシグネチャー

	private:
		D3D12_FILL_MODE ConvFillMode(ATL_FILL_MODE mode);							//!< ATL_FILL_MODEをD3D12_FILL_MODEに変換する
		D3D12_CULL_MODE ConvCullMode(ATL_CULL_MODE mode);							//!< ATL_CULL_MODEをD3D12_CULL_MODEに変換する
		D3D12_BLEND ConvBlend(ATL_BLEND blend);										//!< ATL_BLENDをD3D12_BLENDに変換する
		D3D12_BLEND_OP ConvBlendOP(ATL_BLEND_OP blend);								//!< ATL_BLEND_OPをD3D12_BLEND_OPに変換する
		D3D12_DEPTH_WRITE_MASK ConvWriteMask(ATL_DEPTH_WRITE_MASK mask);			//!< ATL_DEPTH_WRITE_MASKをD3D12_DEPTH_WRITE_MASKに変換する
		D3D12_COMPARISON_FUNC ConvFunc(ATL_COMPARISON_FUNC func);					//!< ATL_COMPARISON_FUNCをD3D12_COMPARISON_FUNCに変換する
		D3D12_STENCIL_OP ConvStencilOP(ATL_STENCIL_OP op);							//!< ATL_STENCIL_OPをD3D12_STENCIL_OPに変換する
		D3D12_DESCRIPTOR_RANGE_TYPE ConvRangeType(ATL_DESCRIPTOR_TYPE type);		//!< ATL_DESCRIPTOR_TYPEをD3D12_DESCRIPTOR_RANGE_TYPEに変換する
		D3D12_SHADER_VISIBILITY ConvVisibility(ATL_SHADER_VISIBILITY visibility);	//!< ATL_SHADER_VISIBILITYをD3D12_SHADER_VISIBILITYに変換する
		D3D12_FILTER ConvFilter(ATL_FILTER Filter);									//!< ATL_FILTERをD3D12_FILTERに変換する
		D3D12_TEXTURE_ADDRESS_MODE ConvAddressMode(ATL_ADDRESS_MODE mode);			//!< ATL_ADDRESS_MODEをD3D12_TEXTURE_ADDRESS_MODEに変換する
		D3D12_COMPARISON_FUNC ConvComparisonFunc(ATL_COMPARISON_FUNC func);			//!< ATL_COMPARISON_FUNCをD3D12_COMPARISON_FUNCに変換する
		D3D12_STATIC_BORDER_COLOR ConvBorderColor(ATL_BORDER_COLOR color);			//!< ATL_BORDER_COLORをD3D12_STATIC_BORDER_COLORに変換する
		

		D3D12_BLEND_DESC CreateBlendDesc(ATL_BLEND_DESC& blend);						//!< ブレンドデスク作成関数
		D3D12_RASTERIZER_DESC CreateRasterizerDesc(ATL_RASTERIZER_DESC& rast);			//!< ラスタライザー作成関数
		D3D12_DEPTH_STENCIL_DESC CreateDepthStencilDesc(ATL_DEPTH_STENCIL_DESC& depth);	//!< デプスステンシルデスク作成関数
		D3D12_INPUT_ELEMENT_DESC* CreateInputLayout(ATL_INPUT_LAYOUT_DESC& input);		//!< インプットレイアウト作成関数


		/// ルートパラメーターとレンジを作成する関数
		void CreateRangeParametor(
			ATL_ROOT_PARAMETER* parametor, 
			unsigned int num, 
			D3D12_DESCRIPTOR_RANGE** range, 
			D3D12_ROOT_PARAMETER** root
		);
		D3D12_STATIC_SAMPLER_DESC* CreateSampler(ATL_SAMPLER_DESC* sampler, unsigned int num);			//!< サンプラーデスク作成関数
		ID3D12RootSignature* CreateRootSignature(ID3D12Device* pDevice, ATL_ROOT_SIGNATURE_DESC& root);	//!< ルートシグネチャー作成関数

		
	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX12PipeLine();

		/****************************************************************//**
		 * @see Astrallayer::ATLIPipeLine::Release()
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
		 * \param pDevice [in] DX12のデバイス
		 * \param Desc [in] パイプラインデスク
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice,
			ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc
		);
	};

	static const int FENCE_BACKBUFFER = 0; //!< AstralDirectX12::DX12Fence::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX12フェンス
	 *******************************************************************/
	class DX12Fence : public AstralRHI::RHIFence
	{
	private:
		unsigned int m_BufferIndex = 0;		//!< バックバッファー
		HANDLE m_fenceEvent = NULL;			//!< イベントハンドル
		ID3D12Fence* m_pFence = nullptr;	//!< フェンス
		unsigned long long m_fenceValue = 0;//!< フェンスカウンタ

	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		~DX12Fence();

		/****************************************************************//**
		 * @see Astrallayer::ATLIFence::WaitDrawDone()
		 *******************************************************************/
		void WaitDrawDone(
			AstralLayer::ATLICommandQueue* pCommandQueue,
			AstralLayer::ATLISwapChain* pSwapChain
		)override;

		/****************************************************************//**
		 *  @see AstralRHI::RHIFence::GetHandle()
		 *******************************************************************/
		void Release()override;

		void GetHandle(
			void** ppOut, 
			int Handle
		)override;

		/****************************************************************//**
		 * フェンス作成関数
		 * 
		 * \param pDevice [in] DX12のデバイス
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice
		);
	};

	static const int SWAPCHAIN_SWAPCHAIN = 0; //!< AstralDirectX12::DX12SwapChain::GetHandle()で利用する定数

	/****************************************************************//**
	 * DX12スワップチェイン
	 *******************************************************************/
	class DX12SwapChain : public AstralRHI::RHISwapChain
	{
	private:
		IDXGISwapChain3* m_pSwapChain = nullptr; //!< スワップチェイン


	public:
		/****************************************************************//**
		 * デストラクタ
		 *******************************************************************/
		virtual ~DX12SwapChain();

		/****************************************************************//**
		 * @see Astrallayer::ATLISwapChain::Present()
		 *******************************************************************/
		void Present(
			unsigned int SyncInterval
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLISwapChain::Release()
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
		 * スワップチェイン作成関数
		 * 
		 * \param pDevice [in] DX12のデバイス
		 * \param Desc [in] スワップチェインデスク
		 * \param pCommandQueue [in] コマンドキュー
		 * \return 結果の正負
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice,
			ATL_SWAPCHAIN_DESC& Desc,
			AstralLayer::ATLICommandQueue* pCommandQueue
		);
	};
}
