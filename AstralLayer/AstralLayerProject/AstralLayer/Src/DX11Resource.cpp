#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"
#include"../Include/ATL/AstralDirectX.h"

const unsigned long AstralLayerDirectX11::DX11Resource::CalcAlignment(unsigned long size)
{
	return size + DECREMENT_ALIGNMENT & NOT_DECREMENT_ALIGNMENT;
}

D3D11_BIND_FLAG AstralLayerDirectX11::DX11Resource::ConvBindFlag(ATL_RESOURCE_FLAG flag)
{
	switch (flag)
	{
	case ATL_RESOURCE_FLAG::CONSTANTBUFFER: return D3D11_BIND_CONSTANT_BUFFER;
	case ATL_RESOURCE_FLAG::VERTEXBUFFER: return D3D11_BIND_VERTEX_BUFFER;
	case ATL_RESOURCE_FLAG::INDEXBUFFER: return D3D11_BIND_INDEX_BUFFER;
	case ATL_RESOURCE_FLAG::TEXTURE2D: return D3D11_BIND_SHADER_RESOURCE;
	default: return D3D11_BIND_CONSTANT_BUFFER;
	}
}

AstralLayerDirectX11::DX11Resource::~DX11Resource()
{
	if (m_pBufferArray == nullptr)//�z�񂪑��݂��邩
	{
		if (m_pImmidiateContext != nullptr)
			m_pImmidiateContext->Release();
		return;
	}

	//Map���Ă���ꍇ
	if (m_Type == ATL_RESOURCE_TYPE::UPLOAD || m_Type == ATL_RESOURCE_TYPE::READBACK)
	{
		for (unsigned int i = 0; i < m_ObjectSize; i++)//���`�邭�`��
		{
			if (m_pBufferArray[i] != nullptr)//���\�[�X�����邩
				m_pImmidiateContext->Unmap(m_pBufferArray[i], 0);//�A���}�b�v
		}
	}

	//�������
	for (unsigned int i = 0; i < m_ObjectSize; i++)
	{
		if (m_pBufferArray[i] != nullptr)
			m_pBufferArray[i]->Release();
	}

	//�������
	if (m_pImmidiateContext != nullptr)
		m_pImmidiateContext->Release();

	delete[] m_pBufferArray;
}

unsigned int AstralLayerDirectX11::DX11Resource::SetSubResource(
	const void* pData, 
	unsigned int SetByteSize)
{
	//�}�b�v
	D3D11_MAPPED_SUBRESOURCE ms{};
	if (FAILED(m_pImmidiateContext->Map(m_pBufferArray[m_UseIndex], 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &ms)))
		return UINT_MAX;

	//�㏑��
	memcpy(ms.pData, pData, SetByteSize);

	//�A���}�b�v
	m_pImmidiateContext->Unmap(m_pBufferArray[m_UseIndex], 0);

	//�C���f�b�N�X�ێ�
	unsigned int index = m_UseIndex;

	//�C���f�b�N�X�ύX
	m_UseIndex = (m_UseIndex + 1) % m_ObjectSize;


	return index;
}

bool AstralLayerDirectX11::DX11Resource::UpdateSubResource(
	unsigned int SubResourceID, 
	unsigned int MoveByte, 
	const void* pData, 
	unsigned int UpdateByteSize)
{
	if (m_UseIndex >= m_ObjectSize)
		return false;

	//�}�b�v
	D3D11_MAPPED_SUBRESOURCE ms{};
	if (FAILED(m_pImmidiateContext->Map(m_pBufferArray[SubResourceID], 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &ms)))
		return false;

	//�|�C���^�󂯎��
	char* data = reinterpret_cast<char*>(ms.pData);

	//�㏑��
	memcpy(&data[MoveByte], pData, UpdateByteSize);

	//�A���}�b�v
	m_pImmidiateContext->Unmap(m_pBufferArray[SubResourceID], 0);

	return true;
}

void AstralLayerDirectX11::DX11Resource::GetHandle(
	void** ppOut,
	int Handle)
{
	if (Handle == RESOURCE_FORMAT)
	{
		*ppOut = &m_Format;
	}
	else if (Handle == RESOURCE_STRUCTURESIZE)
	{
		*ppOut = &m_StructureSize;//�\���̃T�C�Y
	}
	else if(Handle >= RESOURCE_BUFFER)
	{
		*ppOut = m_pBufferArray[Handle];//�擪�A�h���X
	}
}

void AstralLayerDirectX11::DX11Resource::Release()
{
	delete this;
}

bool AstralLayerDirectX11::DX11Resource::CreateResource(
	ID3D11Device* pDevice, 
	ATL_RESOURCE_DESC& Desc, 
	const void* pSrcData)
{
	ATLAssert(Desc.ByteStructure > 0);
	ATLAssert(Desc.Width > 0);
	ATLAssert(Desc.Height > 0);
	ATLAssert(Desc.NumObject > 0);
	ATLAssert(Desc.Type != ATL_RESOURCE_TYPE::UNKNOWN);
	if (Desc.ByteStructure <= 0 ||
		Desc.Width <= 0 ||
		Desc.Height <= 0 ||
		Desc.NumObject <= 0 ||
		Desc.Type == ATL_RESOURCE_TYPE::UNKNOWN )
		return false;

	//�ϐ������A���h�Z�b�g
	m_StructureSize = Desc.ByteStructure;
	m_Width = Desc.Width;
	m_ObjectSize = Desc.NumObject;
	m_pBufferArray = new ID3D11Buffer*[m_ObjectSize];
	m_Type = Desc.Type;
	m_Flag = Desc.Flag;
	m_Format = ConvDXGIFormat(Desc.Format);
	pDevice->GetImmediateContext(&m_pImmidiateContext);

	//�f�X�N����
	D3D11_BUFFER_DESC desc{};
	desc.BindFlags = ConvBindFlag(Desc.Flag);
	desc.MiscFlags = 0;
	desc.StructureByteStride = Desc.ByteStructure;

	if (Desc.Flag == ATL_RESOURCE_FLAG::CONSTANTBUFFER)//�萔�o�b�t�@�̓A���C�����g����
	{
		desc.ByteWidth = CalcAlignment(  // 0x10�ŃA���C�����g���ē����
			static_cast<unsigned int>(Desc.ByteStructure) *
			static_cast<unsigned int>(Desc.Width));
	}
	else//�萔�o�b�t�@�ȊO�̓A���C�����g���Ȃ�
	{
		desc.ByteWidth = Desc.ByteStructure * Desc.Width * Desc.Height;
	}

	//�^�C�v��UPLOAD�̍ۍX�V�ł���悤�ɂ���
	if (Desc.Type == ATL_RESOURCE_TYPE::UPLOAD)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
	}

	//�T�u���\�[�X�f�[�^�Z�b�g
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = pSrcData;

	//�o�b�t�@�[�쐬
	for (unsigned int i = 0; i < m_ObjectSize; i++)
	{
		HRESULT hr = pDevice->CreateBuffer(&desc, &sd, &m_pBufferArray[i]);
		ATLAssertMessage(SUCCEEDED(hr), "Resource�̍쐬�Ɏ��s���܂���");
		if (FAILED(hr))
		{
			this->~DX11Resource();
			return false;
		}
	}
	return true;
}
