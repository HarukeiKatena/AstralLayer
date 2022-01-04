/****************************************************************//**
 * @file AstralDirectX12.h
 *******************************************************************/
#pragma once
#include"AstralRHI.h"
#include"../AstralRendererInterface.h"

namespace AstralLayerDirectX12
{
	/// @cond
	/// �O���錾
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
	*�g�p�\��MSAA�̒l���擾
	*******************************************************************/
	DXGI_SAMPLE_DESC GetMSAA(ID3D12Device * pDevice, unsigned int Count);
	
	static const int DEVICE_DEVICE = 0; //!< AstralDirectX12::DX12Device::Gethandle()��Handle�ŗ��p����萔

	/****************************************************************//**
	 * DX12�f�o�C�X
	 *******************************************************************/
	class DX12Device : public AstralRHI::RHIDevice
	{
	private:
		ID3D12Device* m_pDevice = nullptr;

	public:

		/****************************************************************//**
		 *  �f�X�g���N�^
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
		 * �f�o�C�X�쐬�֐�
		 * 
		 * \param pFactory [in] DXGI�̃t�@�N�g���[
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			IDXGIFactory1* pFactory
		);
	};

	static const int COMMANDLIST_COMMAND = 0;	//!< AstralDirectX12::DX12CommandList::GetHandle()�ŗ��p����萔
	static const int COMMANDLIST_ALLOCATOR = 1; //!< AstralDirectX12::DX12CommandList::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX11�R�}���h���X�g
	 *******************************************************************/
	class DX12CommandList : public AstralRHI::RHICommandList
	{
	private:
		ID3D12GraphicsCommandList* m_pCommandList = nullptr;	//!< �R�}���h���X�g
		ID3D12CommandAllocator* m_pAllocator = nullptr;			//!< �A���P�[�^�[

		unsigned int m_BackBuffer = 0;							//!< �o�b�N�o�b�t�@�[

	private:
		D3D12_RESOURCE_STATES ConvState(ATL_RESOURCE_STATE state);							//!< ATL_RESOURCE_STATE���ɕϊ�����
		D3D12_PRIMITIVE_TOPOLOGY ConvTopology(ATL_PRIMITIVE_TOPOLOGY t);					//!< ATL_PRIMITIVE_TOPOLOGY��D3D12_PRIMITIVE_TOPOLOGY�ɕϊ�����
		D3D12_CPU_DESCRIPTOR_HANDLE GetRTVHandle(AstralLayer::ATLIRenderTargetView* rtv);	//!< RTV��D3D12_CPU_DESCRIPTOR_HANDLE���󂯎��
		D3D12_CPU_DESCRIPTOR_HANDLE GetDSVHandle(AstralLayer::ATLIDepthStencilView* dsv);	//!< DSV��D3D12_CPU_DESCRIPTOR_HANDLE���󂯎��

	public:
		/****************************************************************//**
		 *  �f�X�g���N�^
		 *******************************************************************/
		virtual ~DX12CommandList();

		/****************************************************************//**
		 * �R�}���h���X�g�쐬�֐�
		 * 
		 * \param pDevice [in] DX12�̃f�o�C�X
		 * \return ���ʂ̐���
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

	static const int RESOURCE_DATA = -1;	//!< AstralDirectX12::DX12Resource::GetHandle()�ŗ��p����萔
	static const int RESOURCE_DRAW = 0;		//!< AstralDirectX12::DX12Resource::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX12���\�[�X
	 *******************************************************************/
	class DX12Resource : public AstralRHI::RHIResource
	{
	protected:
		unsigned int m_StructureSize = 0;			//!< �\���̃T�C�Y
		unsigned int m_Width = 0;					//!< ��
		unsigned int m_ObjectSize = 0;				//!< �I�u�W�F�N�g��
		ID3D12Resource* m_pResourceArray = nullptr;	//!< ���\�[�X
		char* m_pSubResource = nullptr;				//!< �T�u���\�[�X
		unsigned int m_UseIndex = 0;				//!< ���ݑI�����Ă�C���f�b�N�X

	protected:
		static const int ALIGNMENT = 0x100;									//!< �A���C�����g���l
		static const int DECREMENT_ALIGNMENT = ALIGNMENT - 1;				//!< �A���C�����g���l��-1����
		static const int NOT_DECREMENT_ALIGNMENT = ~(DECREMENT_ALIGNMENT);	//!< �A���C�����g���l��-1���ăr�b�g�𔽓]����
		const unsigned long CalcAlignment(unsigned long size); //!< �w�肵���l���A���C�����g����

		/****************************************************************//**
		 * ���\�[�X�쐬�֐�
		 * 
		 * \param Device [in] DX12�f�o�C�X
		 * \param Desc [in] ���\�[�X�f�X�N
		 * \param pSrcData [in] �������f�[�^
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool CreateResource(
			ID3D12Device* Device,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData
		);
	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
	 * DX12�萔�o�b�t�@�[
	 *******************************************************************/
	class DX12ConstantBuffer : public DX12Resource
	{
	private:
		ID3D12DescriptorHeap* m_pHeap = nullptr; //!< ���\�[�X

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
		 *******************************************************************/
		virtual ~DX12ConstantBuffer();

		/****************************************************************//**
		 * �萔�o�b�t�@�쐬�֐�
		 * 
		 * \param pDevice [in] DX12�̃f�o�C�X
		 * \param Desc [in] ���\�[�X�f�X�N
		 * \param pSrcData [in] �������f�[�^
		 * \return ���ʂ̐���
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
	 * DX12���_�o�b�t�@�[
	 *******************************************************************/
	class DX12VertexBuffer : public DX12Resource
	{
	private:
		D3D12_VERTEX_BUFFER_VIEW* m_pView = nullptr; //!< ���_�o�b�t�@�[�r���[

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
		 *******************************************************************/
		virtual ~DX12VertexBuffer();

		/****************************************************************//**
		 * ���_�o�b�t�@�[�쐬�֐�
		 * 
		 * \param pDevice [in] DX12�f�o�C�X
		 * \param Desc [in] ���\�[�X�f�X�N
		 * \param pSrcData [in] �������f�[�^
		 * \return ���ʂ̐���
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
	 * �C���f�b�N�X�o�b�t�@�[
	 *******************************************************************/
	class DX12IndexBuffer : public DX12Resource
	{
	private:
		D3D12_INDEX_BUFFER_VIEW* m_pView = nullptr; //!< �C���f�b�N�X�o�b�t�@�[�r���[

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
		 *******************************************************************/
		virtual ~DX12IndexBuffer();

		/****************************************************************//**
		 * �C���f�b�N�X�o�b�t�@�쐬�֐�
		 * 
		 * \param pDevice [in] DX12�̃f�o�C�X
		 * \param Desc [in] ���\�[�X�f�X�N
		 * \param pSrcData [in] �������f�[�^
		 * \return ���ʂ̐���
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

	static const int TEXTURE2D_HEAP = 0;	//!< AstralDirectX12::DX12Texture2D::GetHandle()�ŗ��p����萔
	static const int TEXTURE2D_TEXTURE = 1;	//!< AstralDirectX12::DX12Texture2D::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX12�e�N�X�`��2D
	 *******************************************************************/
	class DX12Texture2D : public AstralRHI::RHIResource
	{
	private:
		ID3D12Resource* m_pTexture = nullptr;		//!< �e�N�X�`��
		DXGI_FORMAT m_Format = DXGI_FORMAT_UNKNOWN;	//!< �t�H�[�}�b�g
		unsigned int m_Width = 0;					//!< ��
		unsigned int m_Height = 0;					//!< ����
		unsigned int m_FormatSize = 0;				//!< �t�H�[�}�b�g�T�C�Y
		ID3D12DescriptorHeap* m_pHeap = nullptr;	//!< �q�[�v


		constexpr unsigned int CallRowPitch();	//!< �s�̒����̃T�C�Y�v�Z
		constexpr unsigned int CallDepthPitch();//!< �S�̂̒����̃T�C�Y�v�Z
	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 * �e�N�X�`��2D�쐬�֐�
		 * 
		 * \param pDevice [in] DX12�f�o�C�X
		 * \param Desc [in] ���\�[�X�f�X�N
		 * \param pSrcData [in] �������f�[�^
		 * \return ���ǂ�����
		 *******************************************************************/
		bool CreateTexture(
			ID3D12Device* pDevice,
			ATL_RESOURCE_DESC& Desc,
			const void* pSrcData
		);
	};

	static const int RTVRESOURCE_HEAP = 0;		//!< AstralDirectX12::DX12RTVResource::GetHandle()�ŗ��p����萔
	static const int RTVRESOURCE_RESOURCE = 1;	//!< AstralDirectX12::DX12RTVResource::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX12RenderTargetView::GetResource()�Ŏg����p�̃��\�[�X
	 * @attention ���̃N���X�̗��p���I�������K��Release���Ă��������B���������[�N�̌����ɂȂ�܂�
	 *******************************************************************/
	class DX12RTVResource : public AstralRHI::RHIResource
	{
	private:
		ID3D12Resource* m_pResource = nullptr;	//!< ���\�[�X�f�[�^
		ID3D12DescriptorHeap* m_pHeap = nullptr;//!< �q�[�v

	public:
		/****************************************************************//**
		 * ���\�[�X�����Z�b�g����
		 * 
		 * \param pResource [in] ���\�[�X
		 * \param pHeap [in] �q�[�v
		 *******************************************************************/
		void SetResource(
			ID3D12Resource* pResource,
			ID3D12DescriptorHeap* pHeap
		);

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::SetSubResource()
		 * @attention ���̊֐��͋@�\���܂���
		 *******************************************************************/
		unsigned int SetSubResource(
			const void* pData, 
			unsigned int SetByteSize
		)override;

		/****************************************************************//**
		 * @see Astrallayer::ATLIResource::UpdateSubResource()
		 * @attention ���̊֐��͋@�\���܂���
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

	static const int RTV_HEAP = 0;		//!< AstralDirectX12::DX12RenderTargetView::GetHandle()�ŗ��p����萔
	static const int RTV_RESOURCE = 1;	//!< AstralDirectX12::DX12RenderTargetView::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX12�����_�[�^�[�Q�b�g�r���[
	 *******************************************************************/
	class DX12RenderTargetView : public AstralRHI::RHIRenderTargetView
	{
	private:
		unsigned int m_ArraySize = 0;				//!< �z��T�C�Y
		ID3D12Resource** m_pRenderTargets = nullptr;//!< RTV���\�[�X�z��
		ID3D12DescriptorHeap* m_pHeap = nullptr;	//!< �q�[�v

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 * �����_�[�^�[�Q�b�g�r���[�쐬�֐�
		 * 
		 * \param pDevice [in] DX12�̃f�o�C�X
		 * \param pSwapChain [in] �X���b�v�`�F�C���Anull�ł��ǂ�
		 * \param ScreenWidth [in] ��ʕ�
		 * \param ScreenHeight [in] ��ʍ���
		 * \return 
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice, 
			IDXGISwapChain* pSwapChain,
			unsigned int ScreenWidth,
			unsigned int ScreenHeight
		);
	};

	static const int DSV_HEAP = 0; //!< AstralDirectX12::DX12DepthStencilView::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX12�f�v�X�X�e���V���r���[
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
		 *  �f�X�g���N�^
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
		 * �f�v�X�X�e���V���r���[�쐬�֐�
		 * 
		 * \param pDevice [in] DX12�̃f�o�C�X
		 * \param Desc [in] �f�v�X�X�e���V���r���[�f�X�N
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice,
			ATL_DEPTH_STENCIL_VIEW_DESC& Desc
		);
	};

	static const int COMMANDQUEUE_QUEUE = 0; //!< AstralDirectX12::DX12CommandQueue::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX12�R�}���h�L���[
	 *******************************************************************/
	class DX12CommandQueue : public AstralRHI::RHICommandQueue
	{
	private:
		ID3D12CommandQueue* m_pCommandQueue = nullptr; //!< �R�}���h�L���[

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 * �R�}���h�L���[�쐬�֐�
		 * 
		 * \param pDevice [in] DX12�̃f�o�C�X
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice
		);
	};

	static const int PIPELINE_PIPELINE = 0;		//!< AstralDirectX12::DX12PipeLine::GetHandle()�ŗ��p����萔
	static const int PIPELINE_ROOTSIGNATURE = 1;//!< AstralDirectX12::DX12PipeLine::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX12�p�C�v���C��
	 *******************************************************************/
	class DX12PipeLine : public AstralRHI::RHIPipeLine
	{
	private:
		ID3D12PipelineState* m_pPipeLine = nullptr;			//!< �p�C�v���C���X�e�[�g
		ID3D12RootSignature* m_pRootSignature = nullptr;	//!< ���[�g�V�O�l�`���[

	private:
		D3D12_FILL_MODE ConvFillMode(ATL_FILL_MODE mode);							//!< ATL_FILL_MODE��D3D12_FILL_MODE�ɕϊ�����
		D3D12_CULL_MODE ConvCullMode(ATL_CULL_MODE mode);							//!< ATL_CULL_MODE��D3D12_CULL_MODE�ɕϊ�����
		D3D12_BLEND ConvBlend(ATL_BLEND blend);										//!< ATL_BLEND��D3D12_BLEND�ɕϊ�����
		D3D12_BLEND_OP ConvBlendOP(ATL_BLEND_OP blend);								//!< ATL_BLEND_OP��D3D12_BLEND_OP�ɕϊ�����
		D3D12_DEPTH_WRITE_MASK ConvWriteMask(ATL_DEPTH_WRITE_MASK mask);			//!< ATL_DEPTH_WRITE_MASK��D3D12_DEPTH_WRITE_MASK�ɕϊ�����
		D3D12_COMPARISON_FUNC ConvFunc(ATL_COMPARISON_FUNC func);					//!< ATL_COMPARISON_FUNC��D3D12_COMPARISON_FUNC�ɕϊ�����
		D3D12_STENCIL_OP ConvStencilOP(ATL_STENCIL_OP op);							//!< ATL_STENCIL_OP��D3D12_STENCIL_OP�ɕϊ�����
		D3D12_DESCRIPTOR_RANGE_TYPE ConvRangeType(ATL_DESCRIPTOR_TYPE type);		//!< ATL_DESCRIPTOR_TYPE��D3D12_DESCRIPTOR_RANGE_TYPE�ɕϊ�����
		D3D12_SHADER_VISIBILITY ConvVisibility(ATL_SHADER_VISIBILITY visibility);	//!< ATL_SHADER_VISIBILITY��D3D12_SHADER_VISIBILITY�ɕϊ�����
		D3D12_FILTER ConvFilter(ATL_FILTER Filter);									//!< ATL_FILTER��D3D12_FILTER�ɕϊ�����
		D3D12_TEXTURE_ADDRESS_MODE ConvAddressMode(ATL_ADDRESS_MODE mode);			//!< ATL_ADDRESS_MODE��D3D12_TEXTURE_ADDRESS_MODE�ɕϊ�����
		D3D12_COMPARISON_FUNC ConvComparisonFunc(ATL_COMPARISON_FUNC func);			//!< ATL_COMPARISON_FUNC��D3D12_COMPARISON_FUNC�ɕϊ�����
		D3D12_STATIC_BORDER_COLOR ConvBorderColor(ATL_BORDER_COLOR color);			//!< ATL_BORDER_COLOR��D3D12_STATIC_BORDER_COLOR�ɕϊ�����
		

		D3D12_BLEND_DESC CreateBlendDesc(ATL_BLEND_DESC& blend);						//!< �u�����h�f�X�N�쐬�֐�
		D3D12_RASTERIZER_DESC CreateRasterizerDesc(ATL_RASTERIZER_DESC& rast);			//!< ���X�^���C�U�[�쐬�֐�
		D3D12_DEPTH_STENCIL_DESC CreateDepthStencilDesc(ATL_DEPTH_STENCIL_DESC& depth);	//!< �f�v�X�X�e���V���f�X�N�쐬�֐�
		D3D12_INPUT_ELEMENT_DESC* CreateInputLayout(ATL_INPUT_LAYOUT_DESC& input);		//!< �C���v�b�g���C�A�E�g�쐬�֐�


		/// ���[�g�p�����[�^�[�ƃ����W���쐬����֐�
		void CreateRangeParametor(
			ATL_ROOT_PARAMETER* parametor, 
			unsigned int num, 
			D3D12_DESCRIPTOR_RANGE** range, 
			D3D12_ROOT_PARAMETER** root
		);
		D3D12_STATIC_SAMPLER_DESC* CreateSampler(ATL_SAMPLER_DESC* sampler, unsigned int num);			//!< �T���v���[�f�X�N�쐬�֐�
		ID3D12RootSignature* CreateRootSignature(ID3D12Device* pDevice, ATL_ROOT_SIGNATURE_DESC& root);	//!< ���[�g�V�O�l�`���[�쐬�֐�

		
	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 * �p�C�v���C���쐬�֐�
		 * 
		 * \param pDevice [in] DX12�̃f�o�C�X
		 * \param Desc [in] �p�C�v���C���f�X�N
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice,
			ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc
		);
	};

	static const int FENCE_BACKBUFFER = 0; //!< AstralDirectX12::DX12Fence::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX12�t�F���X
	 *******************************************************************/
	class DX12Fence : public AstralRHI::RHIFence
	{
	private:
		unsigned int m_BufferIndex = 0;		//!< �o�b�N�o�b�t�@�[
		HANDLE m_fenceEvent = NULL;			//!< �C�x���g�n���h��
		ID3D12Fence* m_pFence = nullptr;	//!< �t�F���X
		unsigned long long m_fenceValue = 0;//!< �t�F���X�J�E���^

	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 * �t�F���X�쐬�֐�
		 * 
		 * \param pDevice [in] DX12�̃f�o�C�X
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice
		);
	};

	static const int SWAPCHAIN_SWAPCHAIN = 0; //!< AstralDirectX12::DX12SwapChain::GetHandle()�ŗ��p����萔

	/****************************************************************//**
	 * DX12�X���b�v�`�F�C��
	 *******************************************************************/
	class DX12SwapChain : public AstralRHI::RHISwapChain
	{
	private:
		IDXGISwapChain3* m_pSwapChain = nullptr; //!< �X���b�v�`�F�C��


	public:
		/****************************************************************//**
		 * �f�X�g���N�^
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
		 * �X���b�v�`�F�C���쐬�֐�
		 * 
		 * \param pDevice [in] DX12�̃f�o�C�X
		 * \param Desc [in] �X���b�v�`�F�C���f�X�N
		 * \param pCommandQueue [in] �R�}���h�L���[
		 * \return ���ʂ̐���
		 *******************************************************************/
		bool Create(
			ID3D12Device* pDevice,
			ATL_SWAPCHAIN_DESC& Desc,
			AstralLayer::ATLICommandQueue* pCommandQueue
		);
	};
}
