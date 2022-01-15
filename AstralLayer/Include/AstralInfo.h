/**********************************************************//**
 * @file Astralinfo.h
 *************************************************************/
#pragma once
#include"AstralRendererInterface.h"



/// @cond
/// �O���錾
namespace AstralLayer
{
    class ATLIUnknown;
    class ATLICommandList;
    class ATLIPipeLine;
    class ATLIFence;
    class ATLICommandQueue;
    class ATLISwapChain;
    class ATLIResource;
    class ATLIRenderTargetView;
    class ATLIDepthStencilView;
}
/// @endcond


/****************************************************************//**
 * �f�t�H���g�l
 *******************************************************************/
#define ATL_DEFAULT_DEPTH_BIAS              (0)     //!< ATL_RASTRIZER_DESC�ɂ���DepthBias�̃f�t�H���g�l
#define ATL_DEFAULT_DEPTH_BIAS_CLAMP        (0.0f)  //!< ATL_RASTRIZER_DESC�ɂ���DepthBiasClamp�̃f�t�H���g�l
#define ATL_DEFAULT_SLOPE_SCALED_DEPTH_BIAS (0.0f)  //!< ATL_RASTRIZER_DESC�ɂ���DepthBias�̃f�t�H���g�l
#define ATL_DEFAULT_STENCIL_READ_MASK       (0xff)  //!< ATL_DEPTH_STENCIL_DESC�ɂ���StencilReadMask�̃f�t�H���g�l
#define ATL_DEFAULT_STENCIL_WRITE_MASK      (0xff)  //!< ATL_DEPTH_STENCIL_DESC�ɂ���StencilWriteMask�̃f�t�H���g�l

/****************************************************************//**
 * ���\�[�X�t���O
 *******************************************************************/
enum class ATL_RESOURCE_FLAG : unsigned int
{
    UNKNOWN,        //!< �g���Ă͂����Ȃ�
    CONSTANTBUFFER, //!< CBV
    VERTEXBUFFER,   //!< ���_�o�b�t�@�[
    INDEXBUFFER,    //!< �C���f�b�N�X�o�b�t�@�[
    TEXTURE1D,      //!< �e�N�X�`��1D�@���Ή�
    TEXTURE2D,      //!< �e�N�X�`��2D
    TEXTURE3D,      //!< �e�N�X�`��3D�@���Ή�
};

/****************************************************************//**
 * ���\�[�X�^�C�v
 *******************************************************************/
enum class ATL_RESOURCE_TYPE : unsigned int
{
    UNKNOWN,    //!< �g���Ă͂����Ȃ�
    DEFAULT,    //!< �ʏ���
    UPLOAD,     //!< �X�V
    READBACK,   //!< �ǂݍ���
};

/****************************************************************//**
 * �r���[�f�B�����W����
 *******************************************************************/
enum class ATL_VIEW_DIMENSION : unsigned int
{
    UNKNOWN,        //!< �g���Ă͂����Ȃ�
    //TEXTURE1D,    //!< �e�N�X�`��1D
    TEXTURE2D,      //!< �e�N�X�`��2D
    //TEXTURE3D,    //!< �e�N�X�`��3D
};

/****************************************************************//**
 * �t�H�[�}�b�g
 *******************************************************************/
enum class ATL_FORMAT : unsigned int
{
    UNKNOWN,                //!< ���ݒ�

    R32G32B32A32_TYPELESS,  //!< 4����128�r�b�g�Ńf�[�^�^����`����Ă��Ȃ�
    R32G32B32A32_FLOAT,     //!< 4����128�r�b�g��float
    R32G32B32A32_UINT,      //!< 4����128�r�b�g��unsigned int
    R32G32B32A32_SINT,      //!< 4����128�r�b�g��signed int

    R32G32B32_TYPELESS,     //!< 3����96�r�b�g�Ńf�[�^�^����`����Ă��Ȃ�
    R32G32B32_FLOAT,        //!< 3����96�r�b�g��float
    R32G32B32_UINT,         //!< 3����96�r�b�g��unsigned int
    R32G32B32_SINT,         //!< 4����96�r�b�g��signed int

    R16G16B16A16_TYPELESS,  //!< 4����64�r�b�g�Ńf�[�^�^����`����Ă��Ȃ�
    R16G16B16A16_UINT,      //!< 4����64�r�b�g��unsigned int
    R16G16B16A16_SINT,      //!< 4����64�r�b�g��signed int

    R32G32_TYPELESS,        //!< 2����64�r�b�g�Ńf�[�^�^����`����Ă��Ȃ�
    R32G32_FLOAT,           //!< 2����64�r�b�g��float
    R32G32_UINT,            //!< 2����64�r�b�g��unsigned int
    R32G32_SINT,            //!< 2����64�r�b�g��signed int

    R8G8B8A8_TYPELESS,      //!< 4����32�r�b�g�Ńf�[�^�^����`����Ă��Ȃ�
    R8G8B8A8_UINT,          //!< 4����32�r�b�g��unsigned int
    R8G8B8A8_SINT,          //!< 4����32�r�b�g��signed int

    R16G16_TYPELESS,        //!< 2����32�r�b�g�Ńf�[�^�^����`����Ă��Ȃ�
    R16G16_UINT,            //!< 2����32�r�b�g��unsigned int
    R16G16_SINT,            //!< 2����32�r�b�g��signed int

    R32_TYPELESS,           //!< 1����32�r�b�g�Ńf�[�^�^����`����Ă��Ȃ�
    R32_FLOAT,              //!< 1����32�r�b�g��float
    R32_UINT,               //!< 1����32�r�b�g��unsigned int
    R32_SINT,               //!< 1����32�r�b�g��signed int

    R8G8_TYPELESS,          //!< 2����16�r�b�g�Ńf�[�^�^����`����Ă��Ȃ�
    R8G8_UINT,              //!< 2����16�r�b�g��unsigned int
    R8G8_SINT,              //!< 2����16�r�b�g��signed int

    R16_TYPELESS,           //!< 1����16�r�b�g�Ńf�[�^�^����`����Ă��Ȃ�
    R16_UINT,               //!< 1����16�r�b�g��unsigned int
    R16_SINT,               //!< 1����16�r�b�g��signed int

    R8_TYPELESS,            //!< 1����8�r�b�g�Ńf�[�^�^����`����Ă��Ȃ�
    R8_UINT,                //!< 1����8�r�b�g��unsigned int
    R8_SINT,                //!< 1����8�r�b�g��signed int
};

/****************************************************************//**
 * �Z�}���e�B�N�X�t���O
 *******************************************************************/
enum class ATL_SEMANTICS_FLAG : unsigned int
{
    POSITION,   //!< ���W
    NORMAL,     //!< �@��
    COLOR,      //!< �J���[
    TEXCOORD,   //!< UV(�e�N�X�`���[�R�[�h)
};

/****************************************************************//**
 * �V�F�[�_�[�r�W�r���e�B
 *******************************************************************/
enum class ATL_SHADER_VISIBILITY : unsigned int
{
    ALL,    //!< ���ׂ�
    VERTEX, //!< ���_�V�F�[�_�[
    PIXEL,  //!< �s�N�Z���V�F�[�_�[
    MAX     //!< �g���Ă͂����Ȃ�
};

/****************************************************************//**
 * �t�B���^�[
 *******************************************************************/
enum class ATL_FILTER : unsigned int
{
    MIN_MAG_MIP_POINT,                          //!< �ŏ����A�g��A�~�b�v���x���T���v�����O�ɂ̓|�C���g�T���v�����O�𗘗p���܂�
    MIN_MAG_POINT_MIP_LINEAR,                   //!< �ŏ����E�g�傩�ɂ̓|�C���g�T���v�����O�A�~�b�v���x���T���v�����O�ɂ͐��`�⊮�𗘗p���܂�
    MIN_POINT_MAG_LINEAR_MIP_POINT,             //!< �ŏ����ɂ̓|�C���g�T���v�����O�A�g��ɂ͐��`�⊮�A�~�b�v���x���T���v�����O�ɂ̓|�C���g�T���v�����O�𗘗p���܂�
    MIN_POINT_MAG_MIP_LINEAR,                   //!< �ŏ����ɂ̓|�C���g�T���v�����O�A�g���~�b�v���x���T���v�����O�ɂ͐��`��Ԃ��g�p���܂�
    MIN_LINEAR_MAG_MIP_POINT,                   //!< �ŏ����ɂ͐��`��Ԃ��A�g��E�~�b�v���x���T���v�����O�ɂ̓|�C���g�T���v�����O���g�p���܂�
    MIN_LINEAR_MAG_POINT_MIP_LINEAR,            //!< �ŏ����ɂ͐��`��Ԃ��A�g��ɂ̓|�C���g�T���v�����O���A�~�b�v���x���T���v�����O�ɂ͐��`��Ԃ��g�p���܂�
    MIN_MAG_LINEAR_MIP_POINT,                   //!< �ŏ����E�g�剻�ɂ͐��`��ԁA�~�b�v���x���T���v�����O�ɂ̓|�C���g�T���v�����O���g�p���܂�
    MIN_MAG_MIP_LINEAR,                         //!< �ŏ����A�g��A�~�b�v���x���T���v�����O�ɂ́A���`��Ԃ��g�p���܂�
    ANISOTROPIC,                                //!< �ŏ����A�g��A�~�b�v���x���T���v�����O�Ɉٕ�����Ԃ��g�p���܂�
    COMPARISON_MIN_MAG_MIP_POINT,               //!< �ŏ����A�g��A�~�b�v���x���T���v�����O�ɂ́A�|�C���g�T���v�����O���g�p���܂��B���ʂ��r�l�Ɣ�r����
    COMPARISON_MIN_MAG_POINT_MIP_LINEAR,        //!< �ŏ����E�g�剻�ɂ̓|�C���g�T���v�����O�A�~�b�v���x���T���v�����O�ɂ͐��`��Ԃ��g�p���܂��B���ʂ��r�l�Ɣ�r����
    COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT,  //!< �ŏ����ɂ̓|�C���g�T���v�����O�A�g��ɂ͐��`��ԁA�~�b�v���x���T���v�����O�ɂ̓|�C���g�T���v�����O���g�p���܂��B���ʂ��r�l�Ɣ�r����
    COMPARISON_MIN_POINT_MAG_MIP_LINEAR,        //!< �ŏ����ɂ̓|�C���g�T���v�����O�A�g��E�~�b�v���x���T���v�����O�ɂ͐��`��Ԃ��g�p���܂��B���ʂ��r�l�Ɣ�r����
    COMPARISON_MIN_LINEAR_MAG_MIP_POINT,        //!< �ŏ����ɂ͐��`��Ԃ��A�g��ɂ̓|�C���g�T���v�����O���A�~�b�v���x���T���v�����O�ɂ̓~�b�v���x���T���v�����O���g�p���܂��B���ʂ��r�l�Ɣ�r����
    COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR, //!< �ŏ����ɂ͐��`��Ԃ��A�g��ɂ̓|�C���g�T���v�����O���A�~�b�v���x���T���v�����O�ɂ͐��`��Ԃ��g�p���܂��B���ʂ��r�l�Ɣ�r����
    COMPARISON_MIN_MAG_LINEAR_MIP_POINT,        //!< �ŏ����E�g�剻�ɂ͐��`��ԁA�~�b�v���x���T���v�����O�ɂ̓|�C���g�T���v�����O���g�p���܂��B���ʂ��r�l�Ɣ�r����
    COMPARISON_MIN_MAG_MIP_LINEAR,              //!< �ŏ����A�g��A�~�b�v���x���T���v�����O�ɂ́A���`��Ԃ��g�p���܂��B���ʂ��r�l�Ɣ�r����
    COMPARISON_ANISOTROPIC,                     //!< �ŏ����A�g��A�~�b�v���x���T���v�����O�Ɉٕ�����Ԃ��g�p���܂��B���ʂ��r�l�Ɣ�r����
};

/****************************************************************//**
 * �A�h���b�V���O���[�h
 *******************************************************************/
enum class ATL_ADDRESS_MODE : unsigned int
{
    WRAP,           //!< �͈�[0,1]�ȊO�̒l�ł��J��Ԃ��\�������
    MIRROR,         //!< 0�܂���1�����E�ɔ��]������
    CLAMP,          //!< �͈�[0,1]�ŃN�����v���܂��@��̍ŏ㕔�ƍs�ɂ���J���[���͈͊O�̃J���[�ɂȂ�܂�
    BORDER,         //!< �͈�[0,1]�����E�ɔC�ӂ̃J���[��͈͊O�ɓK�����܂�
};

/****************************************************************//**
 * ��r�I�v�V����
 *******************************************************************/
enum class ATL_COMPARISON_FUNC : unsigned int
{
    NEVER,          //!< ��r�Ώۂ͐�΂Ƀp�X
    LESS,           //!< ��r���f�[�^����r��f�[�^��菬�����ꍇ�A��r�̓p�X����
    EQUAL,          //!< ��r���f�[�^�Ɣ�r��f�[�^���������ꍇ�A��r�͐�������
    LESS_EQUAL,     //!< ��r���f�[�^����r��f�[�^��菬�������������ꍇ�A��r�̓p�X����
    GREATER,        //!< ��r���f�[�^����r��f�[�^���傫���ꍇ�A��r�͐�������
    NOT_EQUAL,      //!< ��r���f�[�^�Ɣ�r��f�[�^���������Ȃ��ꍇ�A��r�̓p�X����
    GREATER_EQUAL,  //!< ��r���f�[�^����r��f�[�^���傫�����������ꍇ�A��r�͐�������
    ALWAYS,         //!< �K����r���p�X����
};

/****************************************************************//**
 * �f�X�N���v�^�[�q�[�v�̃^�C�v
 *******************************************************************/
enum class ATL_DESCRIPTOR_HEAP_TYPE : unsigned int
{
    CBV_SRV_UAV,    //!< �萔�o�b�t�@�[�A�V�F�[�_�[���\�[�X�r���[�A�A���I�[�_�[�h�A�N�Z�X�r���[
    SAMPLER,        //!< �T���v���[
    RTV,            //!< �����_�[�^�[�Q�b�g�r���[
    DSV,            //!< �f�v�X�X�e���V���r���[
};

/****************************************************************//**
 * �f�X�N���v�^�[�̃^�C�v
 *******************************************************************/
enum class ATL_DESCRIPTOR_TYPE : unsigned int
{
    CBV,    //!< �萔�o�b�t�@�[
    SRV,    //!< �V�F�[�_�[���\�[�X�r���[
    UAV,    //!< �A���I�[�_�[�h�A�N�Z�X�r���[
};

/****************************************************************//**
 * �{�[�_�[�J���[
 *******************************************************************/
enum class ATL_BORDER_COLOR : unsigned int
{
    TRANSPARENT_BLACK,  //!< �J���[�� �A���t�@[0]
    OPAQUE_BLACK,       //!< �J���[�� �A���t�@[255]
    OPAQUE_WHITE,       //!< �J���[�� �A���t�@[255]
};

/****************************************************************//**
 * �O�p�`�̕`��Ɏg�p����h��Ԃ����[�h
 *******************************************************************/
enum class ATL_FILL_MODE : unsigned int
{
    WIREFRAME,  //!< ���_�ƒ��_�����Ԑ�
    SOLID,      //!< �O�p�`��h��Ԃ�
};

/****************************************************************//**
 * �J�����O���[�h
 *******************************************************************/
enum class ATL_CULL_MODE : unsigned int
{
    NONE,   //!< ���ׂĂ̎O�p�`��`��
    FRONT,  //!< ���ʂ��������O�p�`��`�悵�Ȃ�
    BACK    //!< �������̎O�p�`��`�悵�Ȃ�
};

/****************************************************************//**
 * �u�����h���[�h
 *******************************************************************/
enum class ATL_BLEND : unsigned int
{
    ZERO,               //!< �u�����h�t�@�N�^�[��(0,0,0,0) �A�v���u�����h����͍s��Ȃ�
    ONE,                //!< �u�����h�t�@�N�^�[��(1,1,1,1) �A�v���u�����h����͍s��Ȃ�
    SRC_COLOR,          //!< �u�����h�t�@�N�^�[��(R,G,B,A) �A�v���u�����h����͍s��Ȃ�
    INV_SRC_COLOR,      //!< �u�����h�t�@�N�^�[��(1-R,1-G,1-B,1-A)�A�v���u�����h�����ɂ���ăf�[�^�����]����A1-RGB�����������
    SRC_ALPHA,          //!< �u�����h�t�@�N�^�[��(A,A,A,A)�A�v���u�����h����͍s��Ȃ�
    INV_SRC_ALPHA,      //!< �u�����h�t�@�N�^�[��(1-A,1-A,1-A,1-A)�A�v���u�����h���Z�̓f�[�^�𔽓]�����A1-A�𐶐�����
    DEST_ALPHA,         //!< �u�����h�t�@�N�^�[��(A,A,A,A)�A�u�����h�O�̑���͂���܂���
    INV_DEST_ALPHA,     //!< �u�����h�t�@�N�^�[��(1-A,1-A,1-A,1-A)�A�v���u�����h����ɂ���ăf�[�^�����]����A1 - A�����������
    DEST_COLOR,         //!< �u�����h�t�@�N�^�[��(Rd,Gd,Bd,Ad)�A�v���u�����h����͍s��Ȃ�
    INV_DEST_COLOR,     //!< �u�����h�t�@�N�^�[��(1-Rd,1-Gd,1-Bd,1-Ad)�A�v���u�����h����ɂ���ăf�[�^�����]����A1-RGB�����������
    SRC_ALPHA_SAT,      //!< �u�����h�t�@�N�^�[��(f, f, f, 1)�ł���Af = min(A, 1)�A�v���u�����h����ɂ��A�f�[�^��1�ȉ��ɂȂ�悤�ɃN�����v�����
    SRC1_COLOR,         //!< �u�����h�t�@�N�^�[�̓s�N�Z���V�F�[�_���o�͂���J���[�f�[�^�Ƃ��Ẵf�[�^�\�[�X�̗����ł��B�u�����h�O�̑���͂���܂���B���̃u�����h�t�@�N�^�[�̓f���A���\�[�X�J���[�u�����f�B���O���T�|�[�g���܂�
    INV_SRC1_COLOR,     //!< �u�����h�t�@�N�^�[�̓s�N�Z���V�F�[�_�[���o�͂���J���[�f�[�^�Ƃ��Ă̗����̃f�[�^�\�[�X�ł��B�v���u�����h����ɂ��f�[�^�����]����A1-RGB����������܂��B���̃u�����h�t�@�N�^�[�̓f���A���\�[�X�J���[�u�����f�B���O���T�|�[�g���܂�
    SRC1_ALPHA,         //!< �u�����h�t�@�N�^�[�̓s�N�Z���V�F�[�_�[���o�͂���A���t�@�f�[�^�Ƃ��Ẵf�[�^�\�[�X�ł��B�v���u�����h�̑���͂���܂���B���̃u�����h�t�@�N�^�[�̓f���A���\�[�X�J���[�u�����f�B���O���T�|�[�g���܂�
    INV_SRC1_ALPHA,     //!< �u�����h�t�@�N�^�[�̓s�N�Z���V�F�[�_�[����o�͂����A���t�@�f�[�^�Ƃ��Ẵf�[�^�\�[�X�ł��B�v���u�����h����ɂ���ăf�[�^�����]����A1 - A �����������B���̃u�����h�t�@�N�^�[�̓f���A���\�[�X�J���[�u�����f�B���O���T�|�[�g����
};

/****************************************************************//**
 * RGB�܂��̓A���t�@�u�����f�B���O�̑���
 *******************************************************************/
enum class ATL_BLEND_OP : unsigned int
{
    ADD,            //!< �\�[�X1�A�\�[�X2�����Z���܂�
    SUBTRACT,       //!< �\�[�X2����\�[�X1�����Z���܂�
    REV_SUBTRACT,   //!< �\�[�X1����\�[�X2�����Z���܂�
    MIN,            //!< �\�[�X1�ƃ\�[�X2�̍ŏ��l�����߂�
    MAX,            //!< �\�[�X1�ƃ\�[�X2�̍ő�l�����߂�
};

/****************************************************************//**
 * �f�v�X�f�[�^���������ޕ�������肷��
 *******************************************************************/
enum class ATL_DEPTH_WRITE_MASK
{
    ZERO,   //!< �f�v�X�X�e���V���o�b�t�@�ւ̏������݂��I�t�ɂ��܂�
    ALL,    //!< �f�v�X�X�e���V���o�b�t�@�ւ̏������݂��I���ɂ��܂�
};

/****************************************************************//**
 * �f�v�X�X�e���V���̃e�X�g���Ɏ��s�\�ȃX�e���V������̂���
 *******************************************************************/
enum class ATL_STENCIL_OP
{
    KEEP,       //!< �����̃X�e���V���f�[�^��ێ����܂�
    ZERO,       //!< �X�e���V���f�[�^��0�ɂ���
    INCR_SAT,   //!< �X�e���V���l��1�������������A���̌��ʂ��N�����v����
    DECR_SAT,   //!< �X�e���V���l��1���炵�A���̌��ʂ��N�����v����
    INVERT,     //!< �X�e���V���f�[�^�𔽓]������
    INCR,       //!< �X�e���V���l��1���������A�K�v�ɉ����Č��ʂ����b�v����
    DECR,       //!< �X�e���V���l��1���炵�A�K�v�Ȃ猋�ʂ����b�v����
};

/****************************************************************//**
 * �o���A�[�^�C�v
 *******************************************************************/
enum class ATL_BARRIER_TYPE
{
    RENDER_TARGET,  //!< RTV
    UAV,            //!< UAV
};

/****************************************************************//**
 * ��\�[�X�X�e�[�^�X
 *******************************************************************/
enum class ATL_RESOURCE_STATE
{
    PRESENT,        //!< Present
    RENDER_TARGET,  //!< �����_�[�^�[�Q�b�g
};

/****************************************************************//**
 * �v���~�e�B�u�g�|���W�[
 *******************************************************************/
enum class ATL_PRIMITIVE_TOPOLOGY
{
    POINTLIST,      //!< �|�C���g���X�g
    LINELIST,       //!< ���C�����X�g
    LINESTRIP,      //!< ���C���X�g���b�v
    TRIANGLELIST,   //!< �g���C�A���O�����X�g
    TRIANGLESTRIP,  //!< �g���C�A���O���X�g���b�v
};

/****************************************************************//**
 * �����_�����O�^�[�Q�b�g�̊e�s�N�Z���̂����A�u�����f�B���O���ɏ������݉\�ȃR���|�[�l���g����肷��B
 *******************************************************************/
enum class ATL_COLOR_WRITE_ENABLE : unsigned char
{
    RED     = 1 << 0,   //!< �ԐF�R���|�[�l���g���f�[�^���i�[�ł���悤�ɂ���
    GREEN   = 1 << 1,   //!< �ΐF�F�R���|�[�l���g���f�[�^���i�[�ł���悤�ɂ���
    BLUE    = 1 << 2,   //!< �F�R���|�[�l���g���f�[�^���i�[�ł���悤�ɂ���
    ALPHA   = 1 << 3,   //!< �A���t�@�R���|�[�l���g���f�[�^���i�[�ł���悤�ɂ���
    ALL     = RED | GREEN | BLUE | ALPHA,   //!< ���ׂăR���|�[�l���g���f�[�^���i�[�ł���悤�ɂ���
};
constexpr ATL_COLOR_WRITE_ENABLE operator|(ATL_COLOR_WRITE_ENABLE a, ATL_COLOR_WRITE_ENABLE b)
{
    return static_cast<ATL_COLOR_WRITE_ENABLE>(static_cast<unsigned char>(a) | static_cast<unsigned char>(b));
}

/****************************************************************//**
 * ATLICommandList::ClearDepthStencilView()�Ŏw�肷�鐔�l
 *******************************************************************/
enum class ATL_CLEAR_FLAG : unsigned int
{
    DEPTH   = 1 << 0,   //!< �f�v�X
    STENCIL = 1 << 1,   //!< �X�e���V��
};
constexpr ATL_CLEAR_FLAG operator|(ATL_CLEAR_FLAG a, ATL_CLEAR_FLAG b)
{
    return static_cast<ATL_CLEAR_FLAG>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

/****************************************************************//**
 * DSV�f�B�����V����
 *******************************************************************/
enum class ATL_DSV_DIMENSION
{
    TEXTURE1D,      //!< 1�����̃e�N�X�`���Ƃ��ăA�N�Z�X�����
    TEXTURE2D,      //!< 2�����̃e�N�X�`���Ƃ��ăA�N�Z�X�����
    TEXTURE2DMS,    //!< �}���`�T���v�����O��2�����e�N�X�`���Ƃ��A�N�Z�X�����
};

/****************************************************************//**
 * �T���v���[�f�X�N
 *******************************************************************/
struct ATL_SAMPLE_DESC
{
    unsigned int Count;     //!< 1��f������̃}���`�T���v����
    unsigned int Quality;   //!< �掿���x��
};

/****************************************************************//**
 * ���\�[�X�f�X�N
 *******************************************************************/
struct ATL_RESOURCE_DESC
{
    unsigned int ByteStructure; //!< �\���̃T�C�Y
    unsigned int Width;         //!< ����
    unsigned int Height;        //!< �c��
    unsigned int NumObject;     //!< �I�u�W�F�N�g��
    unsigned int MipLevel;      //!< �~�b�v���x��
    ATL_FORMAT Format;          //!< �t�H�[�}�b�g
    ATL_SAMPLE_DESC SampleDesc; //!< �T���v���f�X�N
    ATL_RESOURCE_TYPE Type;     //!< �^�C�v
    ATL_RESOURCE_FLAG Flag;     //!< �t���O
};

/****************************************************************//**
 * �V�F�[�_�[���\�[�X�r���[�f�X�N
 *******************************************************************/
struct ATL_SHADER_RESOURCE_VIEW_DESC
{
    ATL_VIEW_DIMENSION Dimension;   //!< �f�B�����W����
    ATL_FORMAT Format;              //!< �t�H�[�}�b�g
    unsigned int MipLevels;         //!< �~�b�v���x��
};

/****************************************************************//**
 * �f�v�X�X�e���V���r���[�f�X�N
 *******************************************************************/
struct ATL_DEPTH_STENCIL_VIEW_DESC
{
    unsigned int Width;         //!< ��
    unsigned int Height;        //!< ����
    ATL_SAMPLE_DESC SampleDesc; //!< �T���v���f�X�N
    ATL_DSV_DIMENSION Dimension;//!< �f�B�����W����
};

/****************************************************************//**
 * �r���[�|�[�g
 *******************************************************************/
struct ATL_VIEWPORT
{
    float TopLeftX; //!< ������X
    float TopLeftY; //!< �㕔��Y
    float Width;    //!< ���@�@0�ȏ�
    float Height;   //!< �����@0�ȏ�
    float MinDepth; //!< �ŏ��[�x�@0�`1�͈̔͂Ŏw��
    float MaxDepth; //!< �ő�[�x�@0�`1�͈̔͂Ŏw��
};

/****************************************************************//**
 * ���N�g
 *******************************************************************/
struct ATL_RECT
{
    unsigned int left;  //!< ����X
    unsigned int top;   //!< �㕔Y
    unsigned int right; //!< �E��X
    unsigned int bottom;//!< ����Y
};

#if defined(ASTRAL_WINDOWS)
/****************************************************************//**
 * �X���b�v�`�F�C���@(Windows�p)
 *******************************************************************/
struct ATL_SWAPCHAIN_DESC
{
    unsigned int Width;         //!< �o�b�t�@�[�J�E���g
    unsigned int Height;        //!< ��
    ATL_SAMPLE_DESC Sample;     //!< �}���`�T���v�����O
    bool Windowed;              //!< �E�B���h�E���[�h�ŕ\�����邩���Ȃ����@true�̓E�B���h�E���[�h false�̓t���X�N���[��
    HWND hWnd;                  //!< �E�B���h�E�n���h��
};
#elif defined(ASTRAL_MAC)

#endif

/****************************************************************//**
 * ���[�g�p�����[�^�[
 *******************************************************************/
struct ATL_ROOT_PARAMETER
{
    ATL_DESCRIPTOR_TYPE Type;               //!< �f�X�N���v�^�[�̃^�C�v
    ATL_SHADER_VISIBILITY ShaderVisibirity; //!< �V�F�[�_�[�r�W�r���e�B
    unsigned int ShaderRegister;            //!< ���W�X�^�[�̐擪�ԍ�
};

/****************************************************************//**
 * �T���v���[�f�X�N
 *******************************************************************/
struct ATL_SAMPLER_DESC
{
    ATL_FILTER Filter;                      //!< �T���v�����O����ۂ̕⊮�̕��@
    ATL_ADDRESS_MODE AddressU;              //!< UV�̒l��0�`1�ȊO�̏ꍇ�̏������@
    ATL_ADDRESS_MODE AddressV;              //!< UV�̒l��0�`1�ȊO�̏ꍇ�̏������@
    ATL_ADDRESS_MODE AddressW;              //!< UV�̒l��0�`1�ȊO�̏ꍇ�̏������@
    float MipLODBias;                       //!< �v�Z���ꂽ�~�b�v�}�b�v���x���̃I�t�Z�b�g
    unsigned int MaxAnisotropy;             //!< Filter��ANISOTROPIC,COMPARISON_ANISOTROPIC���w�肳��Ă���ꍇ�̃N�����v�l�@�͈� 1�`16
    ATL_COMPARISON_FUNC ComparisionFunc;    //!< �����̃T���v�����O�f�[�^�ɑ΂��ăf�[�^���r����֐�
    ATL_BORDER_COLOR BorderColor;           //!< AddressU,V,W��BORDER���w�肳��Ă���ꍇ�Ɏg�p����鋫�E�̐F
    float MinLOD;                           //!< �N�����v����~�b�v�}�b�v�͈͂̉���
    float MaxLOD;                           //!< �N�����v����~�b�v�}�b�v�͈͂̏��
    unsigned int ShaderRegister;            //!< ���W�X�^�[�̔ԍ�
    ATL_SHADER_VISIBILITY Visibility;       //!< �V�F�[�_�[�r�W�r���e�B
};

/****************************************************************//**
 * ���[�g�V�O�l�`���[
 *******************************************************************/
struct ATL_ROOT_SIGNATURE_DESC
{
    ATL_ROOT_PARAMETER* pRootParameters;//!< ���[�g�p�����[�^�[
    unsigned int NumRootParameters;     //!< ���[�g�p�����[�^�[�̐�
    ATL_SAMPLER_DESC* pSamplers;        //!< �T���v���[
    unsigned int NumSamplers;           //!< �T���v���[�̐�
};

/****************************************************************//**
 * �C���v�b�g�G�������g
 *******************************************************************/
struct ATL_INPUT_ELEMENT_DESC
{
    const char* SemanticsName;      //!< �Z�}���e�B�N�X�̖��O
    ATL_FORMAT Format;              //!< �t�H�[�}�b�g
    unsigned int AlignedByteOffset; //!< ���_�̊J�n�_���炱�̗v�f�܂ł̃I�t�Z�b�g���o�C�g�P�ʂŎw�肷��
};

/****************************************************************//**
 * �C���v�b�g���C�A�E�g�f�X�N
 *******************************************************************/
struct ATL_INPUT_LAYOUT_DESC
{
    const ATL_INPUT_ELEMENT_DESC* pInputElementDescs;   //!< �C���v�b�g�G�������g
    unsigned int NumElements;                           //!< �C���v�b�g�G�������g�̐�
};

/****************************************************************//**
 * ���W�X�^�[�f�X�N
 *******************************************************************/
struct ATL_RASTERIZER_DESC
{
    ATL_FILL_MODE FillMode;     //!< �t�B�����[�h
    ATL_CULL_MODE CullMode;     //!< �J�����O���[�h
    bool FrontCounterClockwise; //!< �O�p�`�����ʂ��w�ʌ����������߂�@true�����v���@false���v���
    int DepthBias;              //!< �s�N�Z���ɒǉ������[�x�o�C�A�X
    float DepthBiasClamp;       //!< �s�N�Z���̍ő�[�x�o�C�A�X
    float SlopeScaledDepthBias; //!< �s�N�Z���̌X���̃X�J���[
    bool DepthClipEnable;       //!< �����ɂ��N���b�s���O��L���ɂ��邩
    bool MultisampleEnable;     //!< �}���`�T���v���E�A���`�G�C���A�V���O�Ŏl�ӌ`���C���ƃA���t�@���C���̂ǂ�����g���� true�l�ӌ`���C���@false�A���t�@���C��
    bool AntialiasedLineEnable; //!< ���C���A���`�G�C���A�V���O��L���ɂ��邩 MultisampleEnable��false�̎��ɓK�p�����
};

/****************************************************************//**
 * @brief �����_�[�^�[�Q�b�g
 * 
 * - �f�t�H���g�l\n
 * BlendEnable           = false\n
 * SrcBlend              = ATL_BLEND::ONE\n
 * DestBlend             = ATL_BLEND::ZERO\n
 * BlendOp               = ATL_BLEND_OP::ADD\n
 * SrcBlendAlpha         = ATL_BLEND::ONE\n
 * DestBlendAlpha        = ATL_BLEND::ZERO\n
 * BlendOpAlpha          = ATL_BLEND_OP::ADD\n
 * RenderTargetWriteMask = ATL_COLOR_WRITE_ENABLE::ALL\n
 *******************************************************************/
struct ATL_RENDER_TARGET_BLEND_DESC
{
    bool BlendEnable;                               //!< �u�����h��L���ɂ���ۂ�true
    ATL_BLEND SrcBlend;                             //!< �s�N�Z���V�F�[�_�[���o�͂���RGB�l�ɑ΂��čs��������w�肷��
    ATL_BLEND DestBlend;                            //!< �����_�[�^�[�Q�b�g�̌��݂�RGB�l�ɑ΂��Ď��s���鑀����w�肷��
    ATL_BLEND_OP BlendOp;                           //!< SrcBlend��DestBlend�̑g�ݍ��킹�����`����
    ATL_BLEND SrcBlendAlpha;                        //!< �s�N�Z���V�F�[�_�[���o�͂���A���t�@�l�ɑ΂��čs��������w�肷��
    ATL_BLEND DestBlendAlpha;                       //!< �����_�����O�^�[�Q�b�g�̌��݂̃A���t�@�l�ɑ΂��Ď��s���鑀����w�肷��
    ATL_BLEND_OP BlendOpAlpha;                      //!< SrcBlendAlpha��DestBlendAlpha�̍������@���`����
    ATL_COLOR_WRITE_ENABLE RenderTargetWriteMask;   //!< �������݃}�X�N���w�肷��@ATL_COLOR_WRITE_ENABLE�̒l���r�b�g�P�ʂ�OR���Z�őg�ݍ��킹������
};


/****************************************************************//**
 * �u�����h�f�X�N
 *******************************************************************/
struct ATL_BLEND_DESC
{
    bool AlphaToCoverageEnable;                     //!< AlphaToCoverage���g�p����ꍇ��true
    bool IndependentBlendEnable;                    //!< ���������_�����O�^�[�Q�b�g�œƗ������L���ɂ��邩�ǂ������w�肷�� false��RenderTarget[0]�̂ݎg��
    ATL_RENDER_TARGET_BLEND_DESC RenderTarget[8];   //!< �����_�[�^�[�Q�b�g�u�����h�f�X�N
};

/****************************************************************//**
 * �V�F�[�_�[�̃o�C�i�����
 *******************************************************************/
struct ATL_SHADER_BYTECODE
{
    const void* pShaderBytecode;    //!< �V�F�[�_�[�̃o�C�i���f�[�^�̐擪�|�C���^
    unsigned int BytecodeLength;    //!< �V�F�[�_�[�̃o�C�i���f�[�^�̒���
};

/****************************************************************//**
 * �f�v�X�X�e���V���I�y���[�V�����f�X�N
 *******************************************************************/
struct ATL_DEPTH_STENCILOP_DESC
{
    ATL_STENCIL_OP StencilFailOp;       //!< �X�e���V���e�X�g�Ɏ��s�����Ƃ��Ɏ��s����X�e���V������
    ATL_STENCIL_OP StencilDepthFailOp;  //!< �X�e���V���e�X�g�����i�A�f�v�X�e�X�g���s���i�̏ꍇ�Ɏ��s����X�e���V������
    ATL_STENCIL_OP StencilPassOp;       //!< �X�e���V���e�X�g�Ɛ[�x�e�X�g�̗��������i�����Ƃ��Ɏ��s����X�e���V������
    ATL_COMPARISON_FUNC StencilFunc;    //!< �X�e���V���f�[�^�Ɗ����̃X�e���V���f�[�^���r����@�\�����ʂ���
};

/****************************************************************//**
 * �f�v�X�X�e���V���f�X�N
 * 
 * - �f�t�H���g�l
 * DepthEnable                  : true
 * DepthWriteMask               : ATL_DEPTH_WRITE_MASK::ALL
 * DepthFunc                    : ATL_COMPARISON_FUNC::LESS
 * StencilEnable                : false
 * StencilReadMask              : ATL_DEFAULT_STENCIL_READ_MASK
 * StencilWriteMask             : ATL_DEFAULT_STENCIL_WRITE_MASK
 * 
 * FrontFace.StencilFailOp      : ATL_STENCIL_OP::KEEP
 * FrontFace.StencilDepthFailOp : ATL_STENCIL_OP::KEEP
 * FrontFace.StencilPassOp      : ATL_STENCIL_OP::KEEP
 * FrontFace.StencilFunc        : ATL_COMPARISON_FUNC::ALWAYS
 * 
 * BackFace.StencilFailOp       : ATL_STENCIL_OP::KEEP
 * BackFace.StencilDepthFailOp  : ATL_STENCIL_OP::KEEP
 * BackFace.StencilPassOp       : ATL_STENCIL_OP::KEEP
 * BackFace.StencilFunc         : ATL_COMPARISON_FUNC::ALWAYS
 *******************************************************************/
struct ATL_DEPTH_STENCIL_DESC
{
    bool DepthEnable;                       //!< �[�x�𗘗p���邩���Ȃ���
    ATL_DEPTH_WRITE_MASK DepthWriteMask;    //!< �ύX�\�Ȑ[�x�X�e���V���o�b�t�@�̕������w�肷��
    ATL_COMPARISON_FUNC DepthFunc;          //!< �[�x�f�[�^�Ɗ����̐[�x�f�[�^���r����֐����w��
    bool StencilEnable;                     //!< �X�e���V���𗘗p���邩���Ȃ���
    unsigned char StencilReadMask;          //!< �X�e���V���f�[�^��ǂݍ��ނ��߂̃X�e���V���o�b�t�@���w�肷��
    unsigned char StencilWriteMask;         //!< �X�e���V���f�[�^���������ޕ������w�肷��
    ATL_DEPTH_STENCILOP_DESC FrontFace;     //!< �\�ʖ@�����J�����̕��������Ă���s�N�Z���[�x�e�X�g�ƃX�e���V���e�X�g�̌��ʂ̎g�p���@���w�肷��
    ATL_DEPTH_STENCILOP_DESC BackFace;      //!< �\�ʖ@�����J�����̔��Α��������Ă���s�N�Z���ɑ΂���[�x�e�X�g�ƃX�e���V���e�X�g�̌��ʂ��g�p������@���w�肷��
};

/****************************************************************//**
 * �O���t�B�N�X�p�C�v���C�����
 *******************************************************************/
struct ATL_GRAPHICS_PIPELINE_STATE_DESC
{
    ATL_SHADER_BYTECODE VS;                     //!< ���_�V�F�[�_�[
    ATL_SHADER_BYTECODE PS;                     //!< �s�N�Z���V�F�[�_�[
    ATL_BLEND_DESC BlendState;                  //!< �u�����h�X�e�[�g
    ATL_RASTERIZER_DESC RasterizerState;        //!< ���X�^���C�U�[�X�e�[�g
    ATL_DEPTH_STENCIL_DESC DepthStencilState;   //!< �f�v�X�X�e���V���X�e�[�g
    ATL_INPUT_LAYOUT_DESC InputLayout;          //!< �C���v�b�g���C�A�E�g 
    ATL_SAMPLE_DESC Sample;                     //!< �T���v���f�X�N
    ATL_ROOT_SIGNATURE_DESC RootSignature;      //!< ���[�g�V�O�l�`���[�f�X�N
};

/****************************************************************//**
 * ���\�[�X�o���A
 *******************************************************************/
struct ATL_RESOURCE_BARRIER
{
    ATL_BARRIER_TYPE Type;                  //!< �^�C�v
    ATL_RESOURCE_STATE StateBefore;         //!< �X�e�[�^�X�g�p�O
    ATL_RESOURCE_STATE StateAfter;          //!< �X�e�[�^�X�g�p��

    union
    {
        AstralLayer::ATLIResource* pResource;   //!< ���\�[�X
        AstralLayer::ATLIRenderTargetView* pRenderTargetView; //!< RTV
    };
};