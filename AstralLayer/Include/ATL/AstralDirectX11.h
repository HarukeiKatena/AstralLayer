/****************************************************************//**
 * @file AstralDirectX11.h
 *******************************************************************/
#pragma once
#include"AstralRHI.h"
#include"../AstralRendererInterface.h"


namespace AstralLayerDirectX11
{
	/****************************************************************//**
	 * ATL_RESOURCE_TYPE��D3D11_USAGE�ɕϊ�
	 *******************************************************************/
	D3D11_USAGE ConvDX11Usage(ATL_RESOURCE_TYPE type);

	/****************************************************************//**
	 * MSAA�ŗ��p�ł���
	 *******************************************************************/
	DXGI_SAMPLE_DESC GetMSAA(ID3D11Device* pDevice, unsigned int Count);

	/****************************************************************//**
	 * DX11�ŗ��p���郋�[�g�p�����[�^�[
	 *******************************************************************/
	struct DX11RootParametor
	{
		ATL_ROOT_PARAMETER* pParameters;
		unsigned int NumRootParametors;
	};

	/****************************************************************//**
	 * DX11�ŗ��p����T���v���[
	 *******************************************************************/
	struct DX11Sampler
	{	
		unsigned int SamplerRegister;
		ATL_SHADER_VISIBILITY SamplerVisibility;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> pSamplerState = nullptr;
	};

	/****************************************************************//**
	 * DX11�ŗ��p����T���v���[�f�X�N
	 *******************************************************************/
	struct DX11SamplerDesc
	{
		DX11Sampler* pSampler;
		unsigned int NumSampler;
	};
	

	/****************************************************************//**
	 * DX11�ŗ��p����p�C�v���C���\����
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
	
	static const int DEVICE_DEVICE = 0; //!< AstralDirectX11::DX11Device::Gethandle()��Handle�ŗ��p����萔

	/****************************************************************//**
	 * DX11�f�o�C�X
	 *******************************************************************/
	class DX11Device : public AstralRHI::RHIDevice
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Device5> m_pDevice = nullptr; //!< DX11�f�o�C�X

	public:
		
		/****************************************************************//**
		 *  �f�X�g���N�^
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
		 *  �f�o�C�X�쐬�֐�
		 * 
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create();
	};


	static const int COMMANDLIST_CONTEXT = 0; //!< AstralDirectX11::DX11CommandList::GetHandle()�ŗ��p����萔
	static const int COMMANDLIST_COMMAND = 1; //!< AstralDirectX11::DX11CommandList::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX11�R�}���h���X�g
	 *******************************************************************/
	class DX11CommandList : public AstralRHI::RHICommandList
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pDeferredContext = nullptr;	//!< �f�t�@�[�h�R���e�L�X�g
		ID3D11CommandList* m_pCommandList = nullptr;		//!< �R�}���h���X�g

		DX11RootParametor* m_pRootDesc = {};				//!< DX11�p���[�g�p�����[�^�[

	private:
		void SetCBV(ATL_ROOT_PARAMETER* para, ID3D11Buffer* buffer);			//!< CBV���R�}���h�ɃZ�b�g����֐�
		void SetSRV(ATL_ROOT_PARAMETER* para, ID3D11ShaderResourceView* srv);	//!< SRV���R�}���h�ɃZ�b�g����֐�

		D3D11_PRIMITIVE_TOPOLOGY ConvToporogy(ATL_PRIMITIVE_TOPOLOGY toporogy);	//!< ATL_PRIMITIVE_TOPOLOGY��D3D11_PRIMITIVE_TOPOLOGY�ɕϊ�����

	public:
		/****************************************************************//**
		 *  �f�X�g���N�^
		 *******************************************************************/
		virtual ~DX11CommandList();

		/****************************************************************//**
		 * �R�}���h�쐬�֐�
		 * 
		 * \param pDevice [in] DX11�̃f�o�C�X
		 * \return ���ʂ̐���
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

	static const int COMMANDQUEUE_CONTEXT = 0; //!< AstralDirectX11::DX11CommandQueue::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX11�R�}���h�L���[
	 *******************************************************************/
	class DX11CommandQueue : public AstralRHI::RHICommandQueue
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext4> m_pImmidiateContext = nullptr; //!< �C�~�f�B�G�C�g�R���e�L�X�g

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 *  �R�}���h�L���[�쐬�֐�
		 * 
		 * \param pDevice [in] DirectX11�̃f�o�C�X
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice
		);
	};

	static const int SWAPCHAIN_SWAPCHAIN = 0; //!< AstralDirectX11::DX11SwapChain::Gethandle()��Handle�ŗ��p����萔

	/****************************************************************//**
	 * DX11�X���b�v�`�F�C��
	 *******************************************************************/
	class DX11SwapChain : public AstralRHI::RHISwapChain
	{
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain3> m_pSwapChain = nullptr; //!< �X���b�v�`�F�C��

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 *  �X���b�v�`�F�C���쐬�֐�
		 * 
		 * \param pDevice [in] DX11�̃f�o�C�X
		 * \param Desc [in] �X���b�v�`�F�C���f�X�N
		 * \param pCommandQueue [in] �R�}���h�L���[
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice,
			ATL_SWAPCHAIN_DESC& Desc,
			AstralLayer::ATLICommandQueue* pCommandQueue
		);
	};

	static const int RTV_RTV = 0; //!< AstralDirectX11::DX11RenderTargetView::Gethandle()��Handle�ŗ��p����萔

	/****************************************************************//**
	 * DX11�����_�[�^�[�Q�b�g�r���[
	 *******************************************************************/
	class DX11RenderTargetView : public AstralRHI::RHIRenderTargetView
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTarget = nullptr; //<! �����_�[�^�[�Q�b�g�r���[
	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 *  �����_�[�^�[�Q�b�g�r���[�쐬�֐�
		 * 
		 * \param pDevice [in] DX11�̃f�o�C�X
		 * \param pSwapChain [in] �X���b�v�`�F�C���@NULL�ł��悢
		 * \param ScreenWidth [in] ��ʕ�
		 * \param ScreenHeight [in] ��ʍ���
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice,
			IDXGISwapChain* pSwapChain,
			unsigned int ScreenWidth,
			unsigned int ScreenHeight);
	};

	static const unsigned int DSV_DSV = 0; //!< AstralDirectX11::DX11DepthStencilView::Gethandle()��Handle�ŗ��p����萔

	/****************************************************************//**
	 * DX11�f�v�X�X�e���V���r���[
	 *******************************************************************/
	class DX11DepthStencilView : public AstralRHI::RHIDepthStencilView
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pView = nullptr; //!< �f�v�X�X�e���V���r���[

	private:
		D3D11_DSV_DIMENSION ConvDimension(ATL_DSV_DIMENSION Dimension);

	public:
		/****************************************************************//**
		 *  �f�X�g���N�^
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
		 * �f�v�X�X�e���V���r���[�쐬�֐�
		 * 
		 * \param pDevice [in] DX11�̃f�o�C�X
		 * \param Desc [in] �f�v�X�X�e���V���r���[�̃f�X�N
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice,
			ATL_DEPTH_STENCIL_VIEW_DESC& Desc
		);

	};

	static const int RESOURCE_FORMAT = -2;			//!< AstralDirectX11::DX11Resource::Gethandle()��Handle�ŗ��p����萔
	static const int RESOURCE_STRUCTURESIZE = -1;	//!< AstralDirectX11::DX11Resource::Gethandle()��Handle�ŗ��p����萔
	static const int RESOURCE_BUFFER = 0;			//!< AstralDirectX11::DX11Resource::Gethandle()��Handle�ŗ��p����萔

	/****************************************************************//**
	 * DX11���\�[�X
	 *******************************************************************/
	class DX11Resource : public AstralRHI::RHIResource
	{
	protected:
		unsigned int m_StructureSize = 0;					//!< �\���̂̃o�C�g��
		unsigned int m_Width = 0;							//!< ��
		unsigned int m_ObjectSize = 0;						//!< �I�u�W�F�N�g��
		Microsoft::WRL::ComPtr<ID3D11Buffer>* m_pBufferArray = nullptr;			//!< �o�b�t�@�[�z��
		unsigned int m_UseIndex = 0;						//!< ���ݑI�����Ă���C���f�b�N�X
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pImmidiateContext = nullptr;	//!< �C�~�f�B�G�C�g�R���e�L�X�g
		DXGI_FORMAT m_Format = DXGI_FORMAT_UNKNOWN;			//!< �t�H�[�}�b�g

	protected:
		static const int ALIGNMENT = 0x10;									//!< �A���C�����g���l
		static const int DECREMENT_ALIGNMENT = ALIGNMENT - 1;				//!< �A���C�����g��-1����
		static const int NOT_DECREMENT_ALIGNMENT = ~(DECREMENT_ALIGNMENT);	//!< �A���C�����g��-1�������l���r�b�g���]����
		const unsigned long CalcAlignment(unsigned long size);				//!< �w�肵�����l�̃A���C�����g���ꂽ���l���v�Z

		D3D11_BIND_FLAG ConvBindFlag(ATL_RESOURCE_FLAG flag);				//!< ATL_RESOURCE_FLAG��D3D11_BIND_FLAG�ɕϊ�����
		

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 * ���\�[�X�쐬�N���X
		 * 
		 * \param pDevice [in] DX11�̃f�o�C�X
		 * \param Desc [in] ���\�[�X�f�X�N
		 * \param pSrcData [in] �������f�[�^
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool CreateResource(
			ID3D11Device* pDevice,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData);

	};

	static const int TEXTURE2D_TEXTURE = 0; //!< AstralDirectX11::DX11Texture2D::Gethandle()��Handle�ŗ��p����萔

	/****************************************************************//**
	 * DX11�e�N�X�`��
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
		 * �e�N�X�`��2D�쐬
		 * 
		 * \param pDevice [in] DX11�̃f�o�C�X
		 * \param Desc [in] ���\�[�X�f�X�N
		 * \param pSrcData [in] �������f�[�^
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool CreateTexture2D(
			ID3D11Device* pDevice,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData
		);
	};

	/****************************************************************//**
	 * DX11�����_�[�^�[�Q�b�g�r���[�̖߂�l�ŗ��p���郊�\�[�X
	 *******************************************************************/
	class DX11RTVResource : public AstralRHI::RHIResource
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Resource> m_pBuffer = nullptr; //!< �o�b�t�@�[

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 * �o�b�t�@�[���Z�b�g����
		 * 
		 * \param pBuffer �o�b�t�@�[�f�[�^
		 *******************************************************************/
		void SetBuffer(ID3D11Resource* pBuffer);
	};

	static const int FENCE_FENCE = 0; //!< AstralDirectX11::DX11Fence::Gethandle()��Handle�ŗ��p����萔

	/****************************************************************//**
	 * DX11�t�F���X
	 *******************************************************************/
	class DX11Fence : public AstralRHI::RHIFence
	{
	private:
		Microsoft::WRL::ComPtr<ID3D11Fence> m_pFence = nullptr;		//!< �t�F���X�N���X
		HANDLE m_fenceEvent = NULL;				//!< �C�x���g�n���h��
		unsigned long long m_fenceValue = 0;	//!< �t�F���X�J�E���^

	public:

		/****************************************************************//**
		 * �f�X�g���N�^
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
		 * �t�F���X�쐬�֐�
		 * 
		 * \param pDevice [in] DX11�̃f�o�C�X
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D11Device5* pDevice
		);
	};

	static const int PIPELINE_PIPELINE = 0; //!< AstralDirectX11::DX11PipeLine::Gethandle()��Handle�ŗ��p����萔 

	/****************************************************************//**
	 * DX11�p�C�v���C��
	 *******************************************************************/
	class DX11PipeLine : public AstralRHI::RHIPipeLine
	{
	private:
		DX11PipeLineState m_State = {}; //!< �p�C�v���C���X�e�[�g

	private:
		D3D11_BLEND CalcBlend(ATL_BLEND blend);							//!< ATL_BLEND��D3D11_BLEND�ɕϊ�����
		D3D11_BLEND_OP CalcBlendOp(ATL_BLEND_OP op);					//!< ATL_BLEND_OP��D3D11_BLEND_OP�ɕϊ�����
		D3D11_FILL_MODE CalcFill(ATL_FILL_MODE fill);					//!< ATL_FILL_MODE��D3D11_FILL_MODE�ɕϊ�����
		D3D11_CULL_MODE CalcCull(ATL_CULL_MODE cull);					//!< ATL_CULL_MODE��D3D11_CULL_MODE�ɕϊ�����
		D3D11_DEPTH_WRITE_MASK CalcWriteMask(ATL_DEPTH_WRITE_MASK mask);//!< ATL_DEPTH_WRITE_MASK��D3D11_DEPTH_WRITE_MASK�ɕϊ�����
		D3D11_COMPARISON_FUNC CalcFunc(ATL_COMPARISON_FUNC func);		//!< ATL_COMPARISON_FUNC��D3D11_COMPARISON_FUNC�ɕϊ�����
		D3D11_STENCIL_OP CalcStencilOp(ATL_STENCIL_OP op);				//!< ATL_STENCIL_OP��D3D11_STENCIL_OP�ɕϊ�����
		D3D11_FILTER ConvFilter(ATL_FILTER Filter);							//!< ATL_FILTER��D3D11_FILTER�ɕϊ�����
		D3D11_TEXTURE_ADDRESS_MODE ConvAddressMode(ATL_ADDRESS_MODE mode);	//!< ATL_ADDRESS_MODE��D3D11_TEXTURE_ADDRESS_MODE�ɕϊ�����
		D3D11_COMPARISON_FUNC ConvComparisonFunc(ATL_COMPARISON_FUNC func);	//!< ATL_COMPARISON_FUNC��D3D11_COMPARISON_FUNC�ɕϊ�����
		void ConvBorderColor(ATL_BORDER_COLOR border, float* out_color);	//!< ATL_BORDER_COLOR��float[4]�ɕϊ�����


		bool CreateVertexShader(
			ID3D11Device* pDevice, 
			ATL_SHADER_BYTECODE& vs, 
			ATL_INPUT_LAYOUT_DESC& input); //!< ���_�V�F�[�_�[�쐬�֐�
		bool CreatePixelShader(ID3D11Device* pDevice, ATL_SHADER_BYTECODE& ps); //!< �s�N�Z���V�F�[�_�[�쐬�֐�
		bool CreateBlendState(ID3D11Device* pDevice, ATL_BLEND_DESC& blend); //!< �u�����h�X�e�[�g�쐬�֐�
		bool CreateRasterizer(ID3D11Device* pDevice, ATL_RASTERIZER_DESC& rasterizer);//!< ���X�^���C�U�[�쐬�֐�
		bool CreateDepthStencilDesc(ID3D11Device* pDevice, ATL_DEPTH_STENCIL_DESC ds);//!< �f�v�X�X�e���V���f�X�N�쐬�֐�

		bool CreateRootSignature(ATL_ROOT_PARAMETER* root, unsigned int num); //!< ���[�g�V�O�l�`���[�쐬�֐�
		bool CreateSampler(ID3D11Device* pDevice, ATL_SAMPLER_DESC* sampler, unsigned int num); //!< �T���v���[�쐬�֐�

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 * �p�C�v���C���쐬�֐�
		 * 
		 * \param pDevice [in] DX11�f�o�C�X
		 * \param pRootSignature [in] ���[�g�V�O�l�`���[
		 * \param Desc [in] �O���t�B�N�X�p�C�v���C���f�X�N
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D11Device* pDevice,
			ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc
		);
	};
}
