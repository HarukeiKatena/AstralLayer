/****************************************************************//**
 * @file AstralLayer.h
 *******************************************************************/
#pragma once
#include"AstralRendererInterface.h"
#include"AstralInfo.h"


namespace AstralLayer
{
	/// @cond
	/// �O���錾
	class ATLICommandList;
	class ATLIPipeLine;
	class ATLIFence;
	class ATLICommandQueue;
	class ATLISwapChain;
	class ATLIRootSignature;
	class ATLIResource;
	class ATLIRenderTargetView;
	class ATLIDepthStencilView;
	/// @endcond
	

	/****************************************************************//**
	 * �f�o�C�X�N���X
	 *******************************************************************/
	class ATLIDevice
	{
	public:
		/****************************************************************//**
		 *  ���\�[�X�N���X�쐬�֐�
		 * 
		 * \param Desc [in] ���\�[�X�N���X
		 * \param pSrcData [in] �������f�[�^\n
		 *                      ATL_RESOURCE_DESC��ByteStructure * Width * Height�𒴂��Ă͂Ȃ�Ȃ�
		 * \return ���\�[�X�N���X
		 *******************************************************************/
		virtual ATLIResource* CreateResource(
			ATL_RESOURCE_DESC& Desc ,
			const void* pSrcData
		) = 0;

		/****************************************************************//**
		 *  �p�C�v���C���N���X�쐬�֐�
		 * 
		 * \param pRootSignature [in] ���[�g�V�O�l�`���[�N���X
		 * \param Desc [in] �O���t�B�N�X�p�C�v���C���f�X�N
		 * \return �p�C�v���C���N���X
		 *******************************************************************/
		virtual ATLIPipeLine* CreatePipeLine(
			ATLIRootSignature* pRootSignature,
			ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc
		) = 0;

		/****************************************************************//**
		 *  �f�v�X�X�e���V���r���[�N���X�쐬�֐�
		 * 
		 * \param Desc [in] �f�v�X�X�e���V���r���[�f�X�N
		 * \return �f�v�X�X�e���V���r���[�N���X
		 *******************************************************************/
		virtual ATLIDepthStencilView* CreateDepthStencilView(
			ATL_DEPTH_STENCIL_VIEW_DESC& Desc
		) = 0;

		/****************************************************************//**
		 *  �R�}���h���X�g�N���X�쐬�֐�
		 * 
		 * \return �R�}���h���X�g�N���X
		 *******************************************************************/
		virtual ATLICommandList* CreateCommandList() = 0;

		/****************************************************************//**
		 *  �R�}���h�L���[�N���X�쐬�֐�
		 * 
		 * \return �R�}���h�L���[�N���X
		 *******************************************************************/
		virtual ATLICommandQueue* CreateCommandQueue() = 0;

		/****************************************************************//**
		 *  �X���b�v�`�F�C���N���X�쐬�֐�
		 * 
		 * \param Desc [in] �X���b�v�`�F�C���f�X�N
		 * \param pCommandQueue [in] �R�}���h�L���[�N���X 
		 * \return �X���b�v�`�F�C���N���X
		 *******************************************************************/
		virtual ATLISwapChain* CreateSwapChain(
			ATL_SWAPCHAIN_DESC& Desc, 
			ATLICommandQueue* pCommandQueue
		) = 0;

		/****************************************************************//**
		 *  ���[�g�V�O�l�`���[�N���X�쐬�֐�
		 * 
		 * \param Desc [in] ���[�g�V�O�l�`���[�f�X�N
		 * \return ���[�g�V�O�l�`���[�N���X
		 *******************************************************************/
		virtual ATLIRootSignature* CreateRootSignature(
			ATL_ROOT_SIGNATURE_DESC& Desc
		) = 0;

		/****************************************************************//**
		 *  �t�F���X�N���X�쐬�֐�
		 * 
		 * \return �t�F���X�N���X
		 *******************************************************************/
		virtual ATLIFence* CreateFence() = 0;

		//-------------------------------------------------------------------
		// �����_�[�^�[�Q�b�g�r���[�쐬
		// [ATLISwapChain*] SwapChain : NULL�̏ꍇ�`��p�ł͂Ȃ�RTV�𐶐�����
		// [unsigned int] ScreenWidth : ��ʕ�
		// [unsigned int] ScreenHeight : ��ʍ���
		//-------------------------------------------------------------------

		/****************************************************************//**
		 *  �����_�[�^�[�Q�b�g�r���[�N���X�쐬�֐�
		 * 
		 * \param pSwapChain [in] �X���b�v�`�F�C���N���X\n
		 *                        null�ł͂Ȃ��ꍇ�X���b�v�`�F�C������o�b�t�@���擾���č쐬����Anull�̏ꍇ�����Ńo�b�t�@���쐬���Ă���RTV���쐬����
		 * \param ScreenWidth [in] ��ʕ�
		 * \param ScreenHeight [in] ��ʍ���
		 * \return �����_�[�^�[�Q�b�g�r���[�N���X
		 *******************************************************************/
		virtual ATLIRenderTargetView* CreateRenderTargetView(
			ATLISwapChain* pSwapChain,
			unsigned int ScreenWidth,
			unsigned int ScreenHeight
		) = 0;

		/****************************************************************//**
		 *  ���
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * �R�}���h���X�g�N���X
	 *******************************************************************/
	class ATLICommandList
	{
	public:
		/****************************************************************//**
		 *  �R�}���h���Z�b�g����֐�
		 * 
		 * \param pPipeLine [in] �p�C�v���C���N���X
		 * \param pFence [in] �t�F���X�N���X
		 * \return ���ʂ̐���
		 *******************************************************************/
		virtual bool Reset(
			ATLIPipeLine* pPipeLine, 
			ATLIFence* pFence
		) = 0;

		/****************************************************************//**
		 *  ���[�g�V�O�l�`���[���Z�b�g����
		 * 
		 * \param pRootSignature [in] ���[�g�V�O�l�`���[�N���X
		 *******************************************************************/
		virtual void SetGraphicsRootSignature(
			ATLIRootSignature* pRootSignature
		) = 0;

		/****************************************************************//**
		 *  ���\�[�X���Z�b�g����֐�
		 * 
		 * \param StartRootParametorIndex [in] ���[�g�p�����[�^�[�Ŏw�肵���p�����[�^�[�̔ԍ�
		 * \param pResource [in] �Z�b�g���郊�\�[�X�N���X
		 * \param NumResourceIDs [in] ���\�[�XID�̐�
		 * \param pResourceIDs [in] ATLIResource::SetSubResource()�̖߂�l\n
		 *                          pResource�Ŏw�肵�����\�[�X��ATL_RESOURCE_DESC��NumObject��1��Type��ATL_RESOURCE_TYPE::DEFAULT�̏ꍇ��null���w��
		 *******************************************************************/
		virtual void SetResource(
			unsigned int StartRootParametorIndex, 
			ATLIResource* pResource, 
			unsigned int NumResourceIDs,
			unsigned int* pResourceIDs
		) = 0;

		/****************************************************************//**
		 *  �r���[�|�[�g���Z�b�g����֐�
		 * 
		 * \param NumViewports [in] �r���[�|�[�g�̐�
		 * \param pViewports [in] �r���[�|�[�g
		 *******************************************************************/
		virtual void SetViewports(
			unsigned int NumViewports, 
			ATL_VIEWPORT* pViewports
		) = 0;

		/****************************************************************//**
		 *  ���N�g�Z�b�g����֐�
		 * 
		 * \param NumRects [in] ���N�g�̐�
		 * \param pRects [in] ���N�g
		 *******************************************************************/
		virtual void SetScissorRects(
			unsigned int NumRects, 
			ATL_RECT* pRects
		) = 0;

		/****************************************************************//**
		 *  �v���~�e�B�u�g�|���W�[���w��
		 * 
		 * \param Topology ���p����g�|���W�[
		 *******************************************************************/
		virtual void SetPrimitiveTopology(
			ATL_PRIMITIVE_TOPOLOGY Topology
		) = 0;

		/****************************************************************//**
		 *  ���_�o�b�t�@�[���Z�b�g����֐�
		 * 
		 * \param pVertexBuffer [in] ���_�o�b�t�@�[
		 * \param ResourceID [in] ATLIResource::SetSubResource()�̖߂�l\n
		 *                        pVertexBuffer�Ŏw�肵�����\�[�X��ATL_RESOURCE_DESC��NumObject��1��Type��ATL_RESOURCE_TYPE::DEFAULT�̏ꍇ��0���w��
		 *******************************************************************/
		virtual void SetVertexBuffer(
			ATLIResource* pVertexBuffer, 
			unsigned int ResourceID
		) = 0;

		/****************************************************************//**
		 *  �C���f�b�N�X�o�b�t�@�[���Z�b�g����֐�
		 * 
		 * \param pIndexBuffer [in] ���_�o�b�t�@�[
		 * \param ResourceID [in] ATLIResource::SetSubResource()�̖߂�l\n
		 *                        pIndexBuffer�Ŏw�肵�����\�[�X��ATL_RESOURCE_DESC��NumObject��1��Type��ATL_RESOURCE_TYPE::DEFAULT�̏ꍇ��0���w��
		 *******************************************************************/
		virtual void SetIndexBuffer(
			ATLIResource* pIndexBuffer, 
			unsigned int ResourceID
		) = 0;

		/****************************************************************//**
		 *  ���\�[�X�o���A���Z�b�g����֐�
		 * 
		 * \param Barrier
		 *******************************************************************/
		virtual void ResourceBarrier(
			ATL_RESOURCE_BARRIER& Barrier
		) = 0;

		/****************************************************************//**
		 *  �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���r���[���Z�b�g����֐�
		 * 
		 * \param pRenderTargetView [in] �����_�[�^�[�Q�b�g�r���[�N���X
		 * \param pDepthStencilView [in] �f�v�X�X�e���V���r���[�N���X
		 *******************************************************************/
		virtual void SetRenderTargets(
			ATLIRenderTargetView* pRenderTargetView,
			ATLIDepthStencilView* pDepthStencilView
		) = 0;

		/****************************************************************//**
		 *  �N���A���郌���_�[�^�[�Q�b�g�r���[���w�肷��֐�
		 * 
		 * \param pRenderTargetView [in] �����_�[�^�[�Q�b�g�r���[�N���X
		 * \param ColorRGBA [in] ��ʃN���A����F
		 *******************************************************************/
		virtual void ClearRenderTargetView(
			ATLIRenderTargetView* pRenderTargetView,
			const float ColorRGBA[4]
		) = 0;

		/****************************************************************//**
		 *  �N���A����f�v�X�X�e���V���r���[
		 * 
		 * \param pDepthStencilView [in] �f�v�X�X�e���V���r���[�N���X
		 * \param ClearFlags [in] �N���A�t���O
		 * \param Depth [in] �[�x�o�b�t�@���N���A����B0�`1�̊ԂŃN�����v����܂�
		 * \param Stencil [in] �N���A����X�e���V���o�b�t�@
		 *******************************************************************/
		virtual void ClearDepthStencilView(
			ATLIDepthStencilView* pDepthStencilView,
			ATL_CLEAR_FLAG ClearFlags,
			float Depth,
			unsigned char Stencil
		) = 0;

		/****************************************************************//**
		 *  �C���f�b�N�X�������Ȃ��A�C���X�^���X�����ꂽ�v���~�e�B�u��`�悷��
		 * 
		 * \param VertexCountParInstance [in] �`�悷�钸�_��
		 * \param InstanceCount [in] �`�悷��C���X�^���X�̐�
		 * \param StartVertexLocation [in] �ŏ��̒��_�C���f�b�N�X�̈ʒu
		 * \param StartInstanceLocation [in] ���_�o�b�t�@����C���X�^���X�P�ʂ̃f�[�^��ǂݍ��ޑO�ɁA�e�C���f�b�N�X�ɒǉ������l
		 *******************************************************************/
		virtual void DrawInstanced(
			unsigned int VertexCountParInstance,
			unsigned int InstanceCount,
			unsigned int StartVertexLocation,
			unsigned int StartInstanceLocation
		) = 0;

		/****************************************************************//**
		 *  �C���f�b�N�X�������Ă���A�C���X�^���X�����ꂽ�v���~�e�B�u��`�悷��
		 * 
		 * \param IndexCountParInstance [in] �`�悷��C���f�b�N�X��
		 * \param InstanceCount [in] �`�悷��C���X�^���X�̐�
		 * \param StartIndexLocation [in] �ŏ��̃C���f�b�N�X�̈ʒu
		 * \param BaceVertexLocation [in] ���_�o�b�t�@���璸�_��ǂݍ��ޑO�Ɋe�C���f�b�N�X�ɒǉ������l
		 * \param StartInstanceLocation [in] ���_�o�b�t�@����C���X�^���X�P�ʂ̃f�[�^��ǂݍ��ޑO�ɁA�e�C���f�b�N�X�ɒǉ������l
		 *******************************************************************/
		virtual void DrawIndexedInstanced(
			unsigned int IndexCountParInstance,
			unsigned int InstanceCount,
			unsigned int StartIndexLocation,
			unsigned int BaceVertexLocation,
			unsigned int StartInstanceLocation
		) = 0;

		/****************************************************************//**
		 *  �R�}���h�����֐�
		 * 
		 * \return ���ʂ̐���
		 *******************************************************************/
		virtual bool Close() = 0;

		/****************************************************************//**
		 *  ���
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * �p�C�v���C���N���X
	 *******************************************************************/
	class ATLIPipeLine
	{
	public:
		/****************************************************************//**
		 *  ���
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * �R�}���h�L���[�N���X
	 *******************************************************************/
	class ATLICommandQueue
	{
	public:
		/****************************************************************//**
		 *  �R�}���h���������񂾃R�}���h���X�g�����s����
		 * 
		 * \param NumCommandLists [in] �R�}���h�̐�
		 * \param ppCommandLists [in] �R�}���h���X�g
		 * \return ���ʂ̐���
		 *******************************************************************/
		virtual bool ExecuteCommandLists(
			unsigned int NumCommandLists,
			AstralLayer::ATLICommandList* const* ppCommandLists
		) = 0;

		/****************************************************************//**
		 *  ���
		 *******************************************************************/
		virtual void Release() = 0;

	};

	/****************************************************************//**
	 * �t�F���X�N���X
	 *******************************************************************/
	class ATLIFence
	{
	public:
		/****************************************************************//**
		 *  �`�抮����҂�
		 * 
		 * \param pCommandQueue [in] �R�}���h�L���[�N���X
		 * \param pSwapChain [in] �X���b�v�`�F�C���N���X
		 *******************************************************************/
		virtual void WaitDrawDone(
			ATLICommandQueue* pCommandQueue,
			ATLISwapChain* pSwapChain
		) = 0;

		/****************************************************************//**
		 *  ���
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * �X���b�v�`�F�C���N���X
	 *******************************************************************/
	class ATLISwapChain
	{
	public:
		//----------------------------------------------------------------------
		// �v���[���g
		// [unsigned int] SyncInterval : �t���[���̒񎦂Ɛ��������̃u�����N�𓯊���������@
		// 0   : �O�ɒ񎦂��ꂽ�t���[���̎c�莞�Ԃ��L�����Z�����A���V�����t���[�����L���[�ɓ����Ă���ꍇ�͂��̃t���[����j������B
		// 1~4 : ���Ȃ��Ƃ�n�̐��������̃u�����N�ɑ΂��ăv���[���e�[�V�����𓯊�������B
		//----------------------------------------------------------------------

		/****************************************************************//**
		 *  �����_�����O�摜����ʂɕ`�悷��
		 * 
		 * \param SyncInterval [in] �t���[���̒񎦂Ɛ��������̃u�����N�𓯊���������@�B\n
		 *                           0   : �O�ɒ񎦂��ꂽ�t���[���̎c�莞�Ԃ��L�����Z�����A���V�����t���[�����L���[�ɓ����Ă���ꍇ�͂��̃t���[����j������B\n
		 *                           1~4 : ���Ȃ��Ƃ�n�̐��������̃u�����N�ɑ΂��ăv���[���e�[�V�����𓯊�������B
		 *******************************************************************/
		virtual void Present(
			unsigned int SyncInterval
		) = 0;

		/****************************************************************//**
		 *  ���
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * ���[�g�V�O�l�`���[�N���X
	 *******************************************************************/
	class ATLIRootSignature
	{
	public:
		/****************************************************************//**
		 *  ���
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * ���\�[�X�N���X
	 *******************************************************************/
	class ATLIResource
	{
	protected:
		ATL_RESOURCE_TYPE m_Type = ATL_RESOURCE_TYPE::UNKNOWN;
		ATL_RESOURCE_FLAG m_Flag = ATL_RESOURCE_FLAG::UNKNOWN;

	public:
		/****************************************************************//**
		 *  �T�u���\�[�X�����Z�b�g
		 * 
		 * \param pData [in] �Z�b�g����f�[�^
		 * \param SetByteSize [in] �Z�b�g����o�C�g�T�C�Y
		 * \return �Z�b�g����ID\n���s�����ꍇunsigned int�̍ő�l���Ԃ��Ă���
		 *******************************************************************/
		virtual unsigned int SetSubResource(
			const void* pData, 
			unsigned int SetByteSize
		) = 0;

		/****************************************************************//**
		 *  �T�u���\�[�X�X�V
		 * 
		 * \param SubResourceID [in] ATLIResource::SetSubResource()�̖߂�l
		 * \param MoveByte [in] �Z�b�g����f�[�^�̊J�n�ʒu�����炷�o�C�g�T�C�Y
		 * \param pData [in] �Z�b�g����f�[�^
		 * \param UpdateByteSize [in] �X�V����o�C�g�T�C�Y
		 * \return ���ʂ̐���
		 *******************************************************************/
		virtual bool UpdateSubResource(
			unsigned int SubResourceID,
			unsigned int MoveByte,
			const void* pData,
			unsigned int UpdateByteSize
		) = 0;

		/****************************************************************//**
		 *  ���
		 *******************************************************************/
		virtual void Release() = 0;

		/****************************************************************//**
		 *  �^�C�v���擾
		 * 
		 * \return ������ATL_RESOURCE_TYPE
		 *******************************************************************/
		ATL_RESOURCE_TYPE GetType()const { return m_Type; }

		/****************************************************************//**
		 *  �t���O���擾
		 * 
		 * \return ������ATL_RESOURCE_FLAG
		 *******************************************************************/
		ATL_RESOURCE_FLAG GetFlag()const { return m_Flag; }
	};

	/****************************************************************//**
	 * �����_�[�^�[�Q�b�g�r���[�N���X
	 *******************************************************************/
	class ATLIRenderTargetView
	{
	public:
		/****************************************************************//**
		 *  RTV�ɃZ�b�g���ꂽ���\�[�X���擾
		 * 
		 * �����Ŏ擾�������\�[�X�͎g�p���I�������Release���Ă����������������[�N�̌����ɂȂ�܂�
		 * 
		 * \param pFence [in] �t�F���X
		 * \return ���\�[�X�N���X
		 *******************************************************************/
		virtual ATLIResource* GetResource(
			ATLIFence* pFence
		) = 0;

		/****************************************************************//**
		 *  ���
		 *******************************************************************/
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * �f�v�X�X�e���V���r���[�N���X
	 *******************************************************************/
	class ATLIDepthStencilView
	{
	public:

		/****************************************************************//**
		 *  ���
		 *******************************************************************/
		virtual void Release() = 0;
	};
}