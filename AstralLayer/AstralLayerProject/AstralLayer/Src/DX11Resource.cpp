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
	if (m_pBufferArray == nullptr)//配列が存在するか
	{
		if (m_pImmidiateContext != nullptr)
			m_pImmidiateContext->Release();
		return;
	}

	//Mapしている場合
	if (m_Type == ATL_RESOURCE_TYPE::UPLOAD || m_Type == ATL_RESOURCE_TYPE::READBACK)
	{
		for (unsigned int i = 0; i < m_ObjectSize; i++)//く～るく～る
		{
			if (m_pBufferArray[i] != nullptr)//リソースがあるか
				m_pImmidiateContext->Unmap(m_pBufferArray[i], 0);//アンマップ
		}
	}

	//解放処理
	for (unsigned int i = 0; i < m_ObjectSize; i++)
	{
		if (m_pBufferArray[i] != nullptr)
			m_pBufferArray[i]->Release();
	}

	//解放処理
	if (m_pImmidiateContext != nullptr)
		m_pImmidiateContext->Release();

	delete[] m_pBufferArray;
}

unsigned int AstralLayerDirectX11::DX11Resource::SetSubResource(
	const void* pData, 
	unsigned int SetByteSize)
{
	//マップ
	D3D11_MAPPED_SUBRESOURCE ms{};
	if (FAILED(m_pImmidiateContext->Map(m_pBufferArray[m_UseIndex], 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &ms)))
		return UINT_MAX;

	//上書き
	memcpy(ms.pData, pData, SetByteSize);

	//アンマップ
	m_pImmidiateContext->Unmap(m_pBufferArray[m_UseIndex], 0);

	//インデックス保持
	unsigned int index = m_UseIndex;

	//インデックス変更
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

	//マップ
	D3D11_MAPPED_SUBRESOURCE ms{};
	if (FAILED(m_pImmidiateContext->Map(m_pBufferArray[SubResourceID], 0, D3D11_MAP_WRITE_NO_OVERWRITE, 0, &ms)))
		return false;

	//ポインタ受け取る
	char* data = reinterpret_cast<char*>(ms.pData);

	//上書き
	memcpy(&data[MoveByte], pData, UpdateByteSize);

	//アンマップ
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
		*ppOut = &m_StructureSize;//構造体サイズ
	}
	else if(Handle >= RESOURCE_BUFFER)
	{
		*ppOut = m_pBufferArray[Handle];//先頭アドレス
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

	//変数準備アンドセット
	m_StructureSize = Desc.ByteStructure;
	m_Width = Desc.Width;
	m_ObjectSize = Desc.NumObject;
	m_pBufferArray = new ID3D11Buffer*[m_ObjectSize];
	m_Type = Desc.Type;
	m_Flag = Desc.Flag;
	m_Format = ConvDXGIFormat(Desc.Format);
	pDevice->GetImmediateContext(&m_pImmidiateContext);

	//デスク準備
	D3D11_BUFFER_DESC desc{};
	desc.BindFlags = ConvBindFlag(Desc.Flag);
	desc.MiscFlags = 0;
	desc.StructureByteStride = Desc.ByteStructure;

	if (Desc.Flag == ATL_RESOURCE_FLAG::CONSTANTBUFFER)//定数バッファはアライメントする
	{
		desc.ByteWidth = CalcAlignment(  // 0x10でアライメントして入れる
			static_cast<unsigned int>(Desc.ByteStructure) *
			static_cast<unsigned int>(Desc.Width));
	}
	else//定数バッファ以外はアライメントしない
	{
		desc.ByteWidth = Desc.ByteStructure * Desc.Width * Desc.Height;
	}

	//タイプがUPLOADの際更新できるようにする
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

	//サブリソースデータセット
	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = pSrcData;

	//バッファー作成
	for (unsigned int i = 0; i < m_ObjectSize; i++)
	{
		HRESULT hr = pDevice->CreateBuffer(&desc, &sd, &m_pBufferArray[i]);
		ATLAssertMessage(SUCCEEDED(hr), "Resourceの作成に失敗しました");
		if (FAILED(hr))
		{
			this->~DX11Resource();
			return false;
		}
	}
	return true;
}
