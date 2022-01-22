/****************************************************************//**
 * @file AstralSupport.h
 * @brief AstralLayer�ŗ��p�ł���ƃ|�[�g�֐���N���X��
 *******************************************************************/
#pragma once
#include"AstralInfo.h"

namespace AstralLayer
{
	/****************************************************************//**
	 * @brief �V�F�[�_�[�o�C�i���ǂݍ��݃N���X
	 * �V�F�[�_�[�̃o�C�i���t�@�C����ǂݍ��݊Ǘ�����N���X
	 *******************************************************************/
	class ATLSShaderBinary
	{
	public:
		unsigned long m_Size = 0;			//!< �o�b�t�@�T�C�Y
		unsigned char* m_Buffer = nullptr;	//!< �o�b�t�@�[

		/****************************************************************//**
		 * �f�X�g���N�^
		 *******************************************************************/
		~ATLSShaderBinary();

		/****************************************************************//**
		 * �V�F�[�_�[�o�C�i���f�[�^�ǂݍ��݊֐�
		 *
		 * \param [in] FilePath	�o�C�i���t�@�C���܂ł̃p�X(�t�@�C��������)
		 * \return				���ʂ̐���
		 *******************************************************************/
		bool LoadShaderBinary(const char* FilePath);

		/****************************************************************//**
		 * �o�b�t�@�[�폜�֐�
		 *******************************************************************/
		void DeleteBuffer();

		/****************************************************************//**
		 * �o�b�t�@�[�T�C�Y�擾�֐�
		 * \return �o�b�t�@�[�T�C�Y
		 *******************************************************************/
		unsigned long GetSize()const { return m_Size; }

		/****************************************************************//**
		 * �o�b�t�@�[�擾�֐�
		 * \return �o�b�t�@�̐擪�|�C���^
		 *******************************************************************/
		unsigned char* GetBuffer()const { return m_Buffer; }

		/****************************************************************//**
		 * ATL_SHADER_BYTECODE�Ŏ擾
		 * \return ATL_SHADER_BYTECODE�Ŏ擾����
		 *******************************************************************/
		ATL_SHADER_BYTECODE GetShaderByteCode() { return ATL_SHADER_BYTECODE{ m_Buffer, m_Size }; }
	};

	/****************************************************************//**
	 * @brief AstralLayer�Ŏg����X�}�[�g�|�C���^
	 *******************************************************************/
	template<class ATLClass>
	class ATLS_Ptr
	{
	private:
		ATLClass* m_pATL = nullptr;//�N���X
		int* m_pCounter = nullptr;//�J�E���^�[

	public:
		ATLS_Ptr() {}
		ATLS_Ptr(decltype(nullptr)) {}
		ATLS_Ptr(const ATLS_Ptr& atls)
		{
			copy(atls);
		}

		ATLS_Ptr(ATLClass* atl)
		{
			reset(atl);
		}

		virtual ~ATLS_Ptr()
		{
			release();
		}

		/****************************************************************//**
		 * ���
		 *******************************************************************/
		int release()
		{
			if (m_pCounter != nullptr)
			{
				(*m_pCounter)--;

				if ((*m_pCounter) <= 0)//�J�E���^�[��0�ȉ��̏ꍇ
				{
					delete m_pCounter;
					m_pCounter = nullptr;

					if (m_pATL != nullptr)
						m_pATL->Release();
					m_pATL = nullptr;

					return 0;
				}

				return (*m_pCounter);
			}

			return 0;
		}

		/****************************************************************//**
		 * �w�肳�ꂽ�N���X���Z�b�g����
		 * ���g�����łɂ���ꍇRelease���Ă�������
		 *******************************************************************/
		void reset(ATLClass* atl)
		{
			release();

			m_pATL = atl;
			m_pCounter = new int;
			(*m_pCounter) = 0;

			(*m_pCounter)++;
		}
		void reset()
		{
			release();
		}

		/****************************************************************//**
		 * �f�[�^���R�s�[���ĎQ�ƃJ�E���^�C���N�������g
		 *******************************************************************/
		void copy(const ATLS_Ptr& atls)
		{
			release();

			m_pATL = atls.m_pATL;
			m_pCounter = atls.m_pCounter;

			(*m_pCounter)++;
		}

		/****************************************************************//**
		 * �f�[�^�������Ă��邩�`�F�b�N
		 *******************************************************************/
		bool empty()noexcept { return m_pATL == nullptr; }

		/****************************************************************//**
		 * �f�[�^����������
		 * �J�E���^�[�͑����Ȃ�
		 *******************************************************************/
		void swap(ATLS_Ptr& atls)
		{
			ATLClass* atlswap = m_pATL;
			int* counterswap = m_pCounter;

			m_pATL = atls.m_pATL;
			m_pCounter = atls.m_pCounter;

			atls.m_pATL = atlswap;
			atls.m_pCounter = counterswap;
		}

		/****************************************************************//**
		 * �����̃f�[�^�������ɓn��(���L�����󂯎��)
		 * ���������łɎ����Ă����ꍇ��Release�����
		 * �J�E���^�[�͑����Ȃ�
		 *******************************************************************/
		void move(ATLS_Ptr& atls)
		{
			release();

			m_pATL = atls.m_pATL;
			m_pCounter = atls.m_pCounter;

			atls.release();
		}

		/****************************************************************//**
		 * �|�C���^���󂯎��
		 *******************************************************************/
		ATLClass* get() const { return m_pATL; }
		ATLClass** get_doubleptr() { return &m_pATL; }

		/********************************************************************
		 * ���Z�q�̃I�[�o�[���[�h�֌W
		 *******************************************************************/
		ATLClass* operator&() const { return m_pATL; }
		ATLClass* operator->() const { return m_pATL; }
		operator bool() const noexcept { return empty(); }
		bool operator!() const { return !static_cast<bool>(this); }

		ATLS_Ptr& operator= (ATLClass* atl) { reset(atl); return *this; }
		ATLS_Ptr& operator= (decltype(nullptr)) { release(); return *this; }
		ATLS_Ptr& operator= (const ATLS_Ptr& atls) { copy(atls); return *this; }

		bool operator==(ATLS_Ptr* atls)const		{ return this->m_pATL == atls->m_pATL; }
		bool operator==(ATLS_Ptr& atls)const		{ return this->m_pATL == atls.m_pATL; }
		bool operator==(ATLS_Ptr atls)const			{ return this->m_pATL == atls.m_pATL; }
		bool operator==(decltype(nullptr) atl)const { return this->m_pATL == nullptr; }

		bool operator!=(ATLS_Ptr* atls)const		{ return this->m_pATL != atls->m_pATL; }
		bool operator!=(ATLS_Ptr& atls)const		{ return this->m_pATL != atls.m_pATL; }
		bool operator!=(ATLS_Ptr atls)const			{ return this->m_pATL != atls.m_pATL; }
		bool operator!=(decltype(nullptr) atl)const { return this->m_pATL != nullptr; }
	};
}

/****************************************************************//**
 * @brief �萔�o�b�t�@�[�̃��\�[�X�f�X�N�쐬�֐�
 * 
 * @param [in] ByteStructure	�\���̃T�C�Y
 * @param [in] Width			��
 * @param [in] ObjectNum		�I�u�W�F�N�g��
 * @param [in] Type				���\�[�X�^�C�v
 * @return						���\�[�X�f�X�N
 *******************************************************************/
ATL_RESOURCE_DESC ATLSCreateConstantBufferResourceDesc(
	unsigned int ByteStructure,
	unsigned int Width,
	unsigned int ObjectNum,
	ATL_RESOURCE_TYPE Type
);

/****************************************************************//**
 * @brief ���_�o�b�t�@�̃��\�[�X�f�X�N�쐬�֐�
 * 
 * @param [in] ByteStructure	�\���̃T�C�Y
 * @param [in] Width			��
 * @param [in] ObjectNum		�I�u�W�F�N�g��
 * @param [in] Type				���\�[�X�^�C�v
 * @return						���\�[�X�f�X�N
 *******************************************************************/
ATL_RESOURCE_DESC ATLSCreateVertexBufferResourceDesc(
	unsigned int ByteStructure,
	unsigned int Width,
	unsigned int ObjectNum,
	ATL_RESOURCE_TYPE Type
);

/****************************************************************//**
 * @brief �C���f�b�N�X�o�b�t�@�̃��\�[�X�f�X�N�쐬�֐�
 * 
 * @datails Format��ATL_FORMAT::R32_UINT�ō쐬
 * 
 * @param [in] ByteStructure	�\���̃T�C�Y
 * @param [in] Width			��
 * @param [in] ObjectNum		�I�u�W�F�N�g��
 * @param [in] Type				���\�[�X�^�C�v
 * @return						���\�[�X�f�X�N
 *******************************************************************/
ATL_RESOURCE_DESC ATLSCreateIndexBufferResourceDesc(
	unsigned int ByteStructure,
	unsigned int Width,
	unsigned int ObjectNum,
	ATL_RESOURCE_TYPE Type
);

/****************************************************************//**
 * @brief
 * 
 * @param [in] ByteStructure	�\���̃T�C�Y
 * @param [in] Width			��
 * @param [in] Height			����
 * @param [in] MipLevel			�~�b�v���x��
 * @param [in] Format			�t�H�[�}�b�g
 * @param [in] SamplerDesc		�T���v���[�f�X�N
 * @param [in] Type				���\�[�X�^�C�v
 * @return						���\�[�X�f�X�N
 *******************************************************************/
ATL_RESOURCE_DESC ATLSCreateTexture2DBufferResourceDesc(
	unsigned int ByteStructure,
	unsigned int Width,
	unsigned int Height,
	unsigned int MipLevel,
	ATL_FORMAT Format,
	ATL_SAMPLE_DESC SamplerDesc,
	ATL_RESOURCE_TYPE Type
);

/****************************************************************//**
 * @brief �T���v���[�f�X�N�쐬�֐�
 * 
 * @param [in] Filter			�t�B���^�[
 * @param [in] AddressUVW		�A�h���X���[�h�AUVW�܂Ƃ߂�
 * @param [in] ShadeerRegister	�V�F�[�_�[���W�X�^�[�A������0
 * @param [in] Visibility		�r�W�r���e�B�[�A������ATL_SHADER_VISIBILITY::PIXEL
 * @return						�T���v���[�f�X�N
 *******************************************************************/
ATL_SAMPLER_DESC ATLSCreateSamplerDesc(
	ATL_FILTER Filter,
	ATL_ADDRESS_MODE AddressUVW,
	unsigned int ShadeerRegister = 0,
	ATL_SHADER_VISIBILITY Visibility = ATL_SHADER_VISIBILITY::PIXEL
);

/****************************************************************//**
 * @brief �f�t�H���g�ݒ�̃u�����h�f�X�N�쐬�֐�
 * @return �u�����h�f�X�N
 *******************************************************************/
ATL_BLEND_DESC ATLSCreateBlendDesc();

/****************************************************************//**
 * @brief ���X�^���C�U�[�f�X�N
 * 
 * @param [in] FillMode	�O�p�`�̕`��Ɏg�p����h��Ԃ����[�h
 * @param [in] CullMode �J�����O���[�h
 * @return ���X�^���C�U�[�f�X�N
 *******************************************************************/
ATL_RASTERIZER_DESC ATLSCreateRasterizerDesc(
	ATL_FILL_MODE FillMode,
	ATL_CULL_MODE CullMode
);

/****************************************************************//**
 * @brief �O���t�B�N�X�p�C�v���C���f�X�N�쐬�֐�
 * 
 * @param [in] VS				���_�V�F�[�_�[���
 * @param [in] PS				�s�N�Z���V�F�[�_�[���
 * @param [in] BlendState		�u�����h�X�e�[�g
 * @param [in] RasterizerState	���X�^���C�U�[�X�e�[�g
 * @param [in] DepthEnable		�f�v�X���g�����g��Ȃ���
 * @param [in] StencilEnable	�X�e���V�����g�����g��Ȃ���
 * @param [in] InputLayout		�C���v�b�g���C�A�E�g
 * @param [in] SampleCount		1��f������̃}���`�T���v�����A������1
 * @param [in] SampleQuality	�掿���x���A������0
 * @return
 *******************************************************************/
ATL_GRAPHICS_PIPELINE_STATE_DESC ATLSCreatePipeLineStateDesc(
	ATL_SHADER_BYTECODE VS,
	ATL_SHADER_BYTECODE PS,
	ATL_BLEND_DESC BlendState,
	ATL_RASTERIZER_DESC RasterizerState,
	bool DepthEnable,
	bool StencilEnable,
	ATL_INPUT_LAYOUT_DESC InputLayout,
	unsigned int SampleCount = 1,
	unsigned int SampleQuality = 0
);

/****************************************************************//**
 * @brief �r���[�|�[�g�쐬�֐�
 * 
 * @param [in] ScreenWidth	��ʕ�
 * @param [in] ScreenHeight	��ʍ���
 * @return					�r���[�|�[�g
 *******************************************************************/
ATL_VIEWPORT ATLSCreateViewport(
	float ScreenWidth,
	float ScreenHeight
);

/****************************************************************//**
 * @brief ���N�g�쐬�֐�
 * 
 * @param [in] ScreenWidth  ��ʕ�
 * @param [in] ScreenHeight ��ʍ���
 * @return					���N�g
 *******************************************************************/
ATL_RECT ATLSCreateRect(
	unsigned int ScreenWidth,
	unsigned int ScreenHeight
);