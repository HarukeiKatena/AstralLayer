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
	class ATLIResource;
	class ATLIRenderTargetView;
	class ATLIDepthStencilView;
	/// @endcond
	
	/****************************************************************//**
	 * ���N���X
	 *******************************************************************/
	class ATLIUnknown
	{
	public:
		virtual void Release() = 0;
	};

	/****************************************************************//**
	 * �f�o�C�X�N���X
	 *******************************************************************/
	class ATLIDevice : public ATLIUnknown
	{
	protected:
		ATL_GRAPHIC_INTERFACE m_gi = {};


	public:
		/****************************************************************//**
		 *  ���\�[�X�N���X�쐬�֐�
		 * 
		 * \param [in] Desc		���\�[�X�N���X
		 * \param [in] pSrcData �������f�[�^\n
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
		 * \param [in] Desc �O���t�B�N�X�p�C�v���C���f�X�N
		 * \return �p�C�v���C���N���X
		 *******************************************************************/
		virtual ATLIPipeLine* CreatePipeLine(
			ATL_GRAPHICS_PIPELINE_STATE_DESC& Desc
		) = 0;

		/****************************************************************//**
		 *  �f�v�X�X�e���V���r���[�N���X�쐬�֐�
		 * 
		 * \param [in] Desc �f�v�X�X�e���V���r���[�f�X�N
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
		 * \param [in] Desc �X���b�v�`�F�C���f�X�N
		 * \param [in] pCommandQueue �R�}���h�L���[�N���X 
		 * \return �X���b�v�`�F�C���N���X
		 *******************************************************************/
		virtual ATLISwapChain* CreateSwapChain(
			ATL_SWAPCHAIN_DESC& Desc, 
			ATLICommandQueue* pCommandQueue
		) = 0;

		/****************************************************************//**
		 *  �t�F���X�N���X�쐬�֐�
		 * 
		 * \return �t�F���X�N���X
		 *******************************************************************/
		virtual ATLIFence* CreateFence() = 0;

		/****************************************************************//**
		 *  �����_�[�^�[�Q�b�g�r���[�N���X�쐬�֐�
		 * 
		 * \param [in] pSwapChain	�X���b�v�`�F�C���N���X\n
		 *							null�ł͂Ȃ��ꍇ�X���b�v�`�F�C������o�b�t�@���擾���č쐬����Anull�̏ꍇ�����Ńo�b�t�@���쐬���Ă���RTV���쐬����
		 * \param [in] ScreenWidth	��ʕ�
		 * \param [in] ScreenHeight ��ʍ���
		 * \return �����_�[�^�[�Q�b�g�r���[�N���X
		 *******************************************************************/
		virtual ATLIRenderTargetView* CreateRenderTargetView(
			ATLISwapChain* pSwapChain,
			unsigned int ScreenWidth,
			unsigned int ScreenHeight
		) = 0;

		/****************************************************************//**
		 * ���݂̃O���t�B�N�X�C���^�[�t�F�[�X���擾
		 *******************************************************************/
		ATL_GRAPHIC_INTERFACE GetGraphics_Interface()const {return m_gi;}
	};

	/****************************************************************//**
	 * �R�}���h���X�g�N���X
	 *******************************************************************/
	class ATLICommandList : public ATLIUnknown
	{
	public:
		/****************************************************************//**
		 *  �R�}���h���Z�b�g����֐�
		 * 
		 * \param [in] pPipeLine		�p�C�v���C���N���X
		 * \param [in] pFence			�t�F���X�N���X
		 * \return ���ʂ̐���
		 *******************************************************************/
		virtual bool Reset(
			ATLIPipeLine* pPipeLine, 
			ATLIFence* pFence
		) = 0;

		/****************************************************************//**
		 *  ���\�[�X���Z�b�g����֐�
		 * 
		 * \param [in] StartRootParametorIndex	���[�g�p�����[�^�[�Ŏw�肵���p�����[�^�[�̔ԍ�
		 * \param [in] pResource				�Z�b�g���郊�\�[�X�N���X
		 * \param [in] NumResourceIDs			���\�[�XID�̐�
		 * \param [in] pResourceIDs				ATLIResource::SetSubResource()�̖߂�l\n
		 *										pResource�Ŏw�肵�����\�[�X��ATL_RESOURCE_DESC��NumObject��1��Type��ATL_RESOURCE_TYPE::DEFAULT�̏ꍇ��null���w��
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
		 * \param [in] NumViewports �r���[�|�[�g�̐�
		 * \param [in] pViewports	�r���[�|�[�g
		 *******************************************************************/
		virtual void SetViewports(
			unsigned int NumViewports, 
			ATL_VIEWPORT* pViewports
		) = 0;

		/****************************************************************//**
		 *  ���N�g�Z�b�g����֐�
		 * 
		 * \param [in] NumRects ���N�g�̐�
		 * \param [in] pRects	���N�g
		 *******************************************************************/
		virtual void SetScissorRects(
			unsigned int NumRects, 
			ATL_RECT* pRects
		) = 0;

		/****************************************************************//**
		 *  �v���~�e�B�u�g�|���W�[���w��
		 * 
		 * \param [in] Topology ���p����g�|���W�[
		 *******************************************************************/
		virtual void SetPrimitiveTopology(
			ATL_PRIMITIVE_TOPOLOGY Topology
		) = 0;

		/****************************************************************//**
		 *  ���_�o�b�t�@�[���Z�b�g����֐�
		 * 
		 * \param [in] pVertexBuffer ���_�o�b�t�@�[
		 * \param [in] ResourceID ATLIResource::SetSubResource()�̖߂�l\n
		 *                        pVertexBuffer�Ŏw�肵�����\�[�X��ATL_RESOURCE_DESC��NumObject��1��Type��ATL_RESOURCE_TYPE::DEFAULT�̏ꍇ��0���w��
		 *******************************************************************/
		virtual void SetVertexBuffer(
			ATLIResource* pVertexBuffer, 
			unsigned int ResourceID
		) = 0;

		/****************************************************************//**
		 *  �C���f�b�N�X�o�b�t�@�[���Z�b�g����֐�
		 * 
		 * \param [in] pIndexBuffer ���_�o�b�t�@�[
		 * \param [in] ResourceID	ATLIResource::SetSubResource()�̖߂�l\n
		 *							pIndexBuffer�Ŏw�肵�����\�[�X��ATL_RESOURCE_DESC��NumObject��1��Type��ATL_RESOURCE_TYPE::DEFAULT�̏ꍇ��0���w��
		 *******************************************************************/
		virtual void SetIndexBuffer(
			ATLIResource* pIndexBuffer, 
			unsigned int ResourceID
		) = 0;

		/****************************************************************//**
		 *  ���\�[�X�o���A���Z�b�g����֐�
		 * 
		 * \param [in] Barrier �o���A�[
		 *******************************************************************/
		virtual void ResourceBarrier(
			ATL_RESOURCE_BARRIER& Barrier
		) = 0;

		/****************************************************************//**
		 *  �����_�[�^�[�Q�b�g�ƃf�v�X�X�e���V���r���[���Z�b�g����֐�
		 * 
		 * \param [in] pRenderTargetView �����_�[�^�[�Q�b�g�r���[�N���X
		 * \param [in] pDepthStencilView �f�v�X�X�e���V���r���[�N���X
		 *******************************************************************/
		virtual void SetRenderTargets(
			ATLIRenderTargetView* pRenderTargetView,
			ATLIDepthStencilView* pDepthStencilView
		) = 0;

		/****************************************************************//**
		 *  �N���A���郌���_�[�^�[�Q�b�g�r���[���w�肷��֐�
		 * 
		 * \param [in] pRenderTargetView	�����_�[�^�[�Q�b�g�r���[�N���X
		 * \param [in] ColorRGBA			��ʃN���A����F
		 *******************************************************************/
		virtual void ClearRenderTargetView(
			ATLIRenderTargetView* pRenderTargetView,
			const float ColorRGBA[4]
		) = 0;

		/****************************************************************//**
		 *  �N���A����f�v�X�X�e���V���r���[
		 * 
		 * \param [in] pDepthStencilView	�f�v�X�X�e���V���r���[�N���X
		 * \param [in] ClearFlags			�N���A�t���O
		 * \param [in] Depth				�[�x�o�b�t�@���N���A����B0�`1�̊ԂŃN�����v����܂�
		 * \param [in] Stencil				�N���A����X�e���V���o�b�t�@
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
		 * \param [in] VertexCountParInstance	�`�悷�钸�_��
		 * \param [in] InstanceCount			�`�悷��C���X�^���X�̐�
		 * \param [in] StartVertexLocation		�ŏ��̒��_�C���f�b�N�X�̈ʒu
		 * \param [in] StartInstanceLocation	���_�o�b�t�@����C���X�^���X�P�ʂ̃f�[�^��ǂݍ��ޑO�ɁA�e�C���f�b�N�X�ɒǉ������l
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
		 * \param [in] IndexCountParInstance	�`�悷��C���f�b�N�X��
		 * \param [in] InstanceCount			�`�悷��C���X�^���X�̐�
		 * \param [in] StartIndexLocation		�ŏ��̃C���f�b�N�X�̈ʒu
		 * \param [in] BaceVertexLocation		���_�o�b�t�@���璸�_��ǂݍ��ޑO�Ɋe�C���f�b�N�X�ɒǉ������l
		 * \param [in] StartInstanceLocation	���_�o�b�t�@����C���X�^���X�P�ʂ̃f�[�^��ǂݍ��ޑO�ɁA�e�C���f�b�N�X�ɒǉ������l
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
	};

	/****************************************************************//**
	 * �p�C�v���C���N���X
	 *******************************************************************/
	class ATLIPipeLine : public ATLIUnknown
	{
	};

	/****************************************************************//**
	 * �R�}���h�L���[�N���X
	 *******************************************************************/
	class ATLICommandQueue : public ATLIUnknown
	{
	public:
		/****************************************************************//**
		 *  �R�}���h���������񂾃R�}���h���X�g�����s����
		 * 
		 * \param [in] NumCommandLists	�R�}���h�̐�
		 * \param [in] ppCommandLists	�R�}���h���X�g
		 * \return ���ʂ̐���
		 *******************************************************************/
		virtual bool ExecuteCommandLists(
			unsigned int NumCommandLists,
			AstralLayer::ATLICommandList* const* ppCommandLists
		) = 0;

	};

	/****************************************************************//**
	 * �t�F���X�N���X
	 *******************************************************************/
	class ATLIFence : public ATLIUnknown
	{
	public:
		/****************************************************************//**
		 *  �`�抮����҂�
		 * 
		 * \param [in] pCommandQueue	�R�}���h�L���[�N���X
		 * \param [in] pSwapChain		�X���b�v�`�F�C���N���X
		 *******************************************************************/
		virtual void WaitDrawDone(
			ATLICommandQueue* pCommandQueue,
			ATLISwapChain* pSwapChain
		) = 0;
	};

	/****************************************************************//**
	 * �X���b�v�`�F�C���N���X
	 *******************************************************************/
	class ATLISwapChain : public ATLIUnknown
	{
	public:
		/****************************************************************//**
		 *  �����_�����O�摜����ʂɕ`�悷��
		 * 
		 * \param [in] SyncInterval	�t���[���̒񎦂Ɛ��������̃u�����N�𓯊���������@�B\n
		 *                          0   : �O�ɒ񎦂��ꂽ�t���[���̎c�莞�Ԃ��L�����Z�����A���V�����t���[�����L���[�ɓ����Ă���ꍇ�͂��̃t���[����j������B\n
		 *                          1~4 : ���Ȃ��Ƃ�n�̐��������̃u�����N�ɑ΂��ăv���[���e�[�V�����𓯊�������B
		 *******************************************************************/
		virtual void Present(
			unsigned int SyncInterval
		) = 0;
	};

	/****************************************************************//**
	 * ���\�[�X�N���X
	 *******************************************************************/
	class ATLIResource : public ATLIUnknown
	{
	protected:
		ATL_RESOURCE_TYPE m_Type = ATL_RESOURCE_TYPE::UNKNOWN;
		ATL_RESOURCE_FLAG m_Flag = ATL_RESOURCE_FLAG::UNKNOWN;

	public:
		/****************************************************************//**
		 *  �T�u���\�[�X�����Z�b�g
		 * 
		 * \param [in] pData		�Z�b�g����f�[�^
		 * \param [in] SetByteSize	�Z�b�g����o�C�g�T�C�Y
		 * \return �Z�b�g����ID\n���s�����ꍇunsigned int�̍ő�l���Ԃ��Ă���
		 *******************************************************************/
		virtual unsigned int SetSubResource(
			const void* pData, 
			unsigned int SetByteSize
		) = 0;

		/****************************************************************//**
		 *  �T�u���\�[�X�X�V
		 * 
		 * \param [in] SubResourceID	ATLIResource::SetSubResource()�̖߂�l
		 * \param [in] MoveByte			�Z�b�g����f�[�^�̊J�n�ʒu�����炷�o�C�g�T�C�Y
		 * \param [in] pData			�Z�b�g����f�[�^
		 * \param [in] UpdateByteSize	�X�V����o�C�g�T�C�Y
		 * \return ���ʂ̐���
		 *******************************************************************/
		virtual bool UpdateSubResource(
			unsigned int SubResourceID,
			unsigned int MoveByte,
			const void* pData,
			unsigned int UpdateByteSize
		) = 0;

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
	class ATLIRenderTargetView : public ATLIUnknown
	{
	public:
		/****************************************************************//**
		 *  RTV�ɃZ�b�g���ꂽ���\�[�X���擾
		 * 
		 * �����Ŏ擾�������\�[�X��Release����delete���Ȃ��ł�������
		 * 
		 * \param [in] pFence �t�F���X
		 * \return ���\�[�X�N���X
		 *******************************************************************/
		virtual ATLIResource* GetResource(
			ATLIFence* pFence
		) = 0;
	};

	/****************************************************************//**
	 * �f�v�X�X�e���V���r���[�N���X
	 *******************************************************************/
	class ATLIDepthStencilView : public ATLIUnknown
	{

	};
}