#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

void AstralLayerDirectX11::DX11CommandList::SetCBV(
	ATL_ROOT_PARAMETER* para, 
	ID3D11Buffer* buffer)
{
	switch (para->ShaderVisibirity)
	{
	case ATL_SHADER_VISIBILITY::ALL:
		m_pDeferredContext->PSSetConstantBuffers(para->BaceShaderRegister, 1, &buffer);
		m_pDeferredContext->VSSetConstantBuffers(para->BaceShaderRegister, 1, &buffer);
		break;
	case ATL_SHADER_VISIBILITY::PIXEL:
		m_pDeferredContext->PSSetConstantBuffers(para->BaceShaderRegister, 1, &buffer);
		break;
	case ATL_SHADER_VISIBILITY::VERTEX:
		m_pDeferredContext->VSSetConstantBuffers(para->BaceShaderRegister, 1, &buffer);
		break;
	default:
		break;
	}
}

void AstralLayerDirectX11::DX11CommandList::SetSRV(
	ATL_ROOT_PARAMETER* para, 
	ID3D11ShaderResourceView* srv)
{
	switch (para->ShaderVisibirity)
	{
	case ATL_SHADER_VISIBILITY::ALL:
		m_pDeferredContext->VSSetShaderResources(para->BaceShaderRegister, 1, &srv);
		m_pDeferredContext->PSSetShaderResources(para->BaceShaderRegister, 1, &srv);
		break;
	case ATL_SHADER_VISIBILITY::PIXEL:
		m_pDeferredContext->PSSetShaderResources(para->BaceShaderRegister, 1, &srv);
		break;
	case ATL_SHADER_VISIBILITY::VERTEX:
		m_pDeferredContext->VSSetShaderResources(para->BaceShaderRegister, 1, &srv);
		break;
	default:
		break;
	}
}

D3D11_PRIMITIVE_TOPOLOGY AstralLayerDirectX11::DX11CommandList::ConvToporogy(
	ATL_PRIMITIVE_TOPOLOGY toporogy)
{
	switch (toporogy)
	{
	case ATL_PRIMITIVE_TOPOLOGY::POINTLIST:		return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
	case ATL_PRIMITIVE_TOPOLOGY::LINELIST:		return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	case ATL_PRIMITIVE_TOPOLOGY::LINESTRIP:		return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
	case ATL_PRIMITIVE_TOPOLOGY::TRIANGLELIST:  return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	case ATL_PRIMITIVE_TOPOLOGY::TRIANGLESTRIP: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	default:									return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	}
}

AstralLayerDirectX11::DX11CommandList::~DX11CommandList()
{
	//�f�t�@�[�h�R���e�L�X�g�����[�X
	if (m_pDeferredContext != nullptr)
		m_pDeferredContext->Release();

	//�R�}���h���X�g�����[�X
	if (m_pCommandList != nullptr)
		m_pCommandList->Release();
}

bool AstralLayerDirectX11::DX11CommandList::Create(
	ID3D11Device* pDevice)
{
	//�f�t�@�[�h�R���e�L�X�g�쐬
	if (FAILED(pDevice->CreateDeferredContext(0, &m_pDeferredContext)))
		return false;

	return true;
}

bool AstralLayerDirectX11::DX11CommandList::Reset(
	AstralLayer::ATLIPipeLine* pPipeLine, 
	AstralLayer::ATLIFence* pFence)
{
	pFence;//�g��Ȃ�

	//�R�}���h���X�g��null�ł͂Ȃ��ꍇ�����[�X
	if (m_pCommandList != nullptr)
	{
		m_pCommandList->Release();
		m_pCommandList = nullptr;
	}

	//�p�C�v���C�����󂯎��
	DX11PipeLineState* pipeline = nullptr;
	reinterpret_cast<AstralRHI::RHIPipeLine*>(pPipeLine)->
		GetHandle(reinterpret_cast<void**>(&pipeline), PIPELINE_PIPELINE);

	//�V�F�[�_�[
	m_pDeferredContext->IASetInputLayout(pipeline->InputLayout);
	m_pDeferredContext->VSSetShader(pipeline->VertexShader, nullptr, 0);
	m_pDeferredContext->PSSetShader(pipeline->PixelShader, nullptr, 0);

	//�u�����h�X�e�[�g
	float BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_pDeferredContext->OMSetBlendState(pipeline->BlendState, BlendFactor, 0xffffffff);

	//���X�^���C�U�[
	m_pDeferredContext->RSSetState(pipeline->Rasterizer);

	//�f�v�X�X�e���V���X�e�[�g
	m_pDeferredContext->OMSetDepthStencilState(pipeline->DepthStencil, 0);

	return true;
}

void AstralLayerDirectX11::DX11CommandList::SetGraphicsRootSignature(
	AstralLayer::ATLIRootSignature* pRootSignature)
{
	//���[�g�V�O�l�`���[RHI���󂯎��
	AstralRHI::RHIRootSignature* root = 
		reinterpret_cast<AstralRHI::RHIRootSignature*>(pRootSignature);

	//���[�g�p�����[�^�[�󂯎��
	root->GetHandle(reinterpret_cast<void**>(&m_pRootDesc), ROOTSIGNATURE_PARAMETOR);

	//�T���v���[�󂯎��
	DX11SamplerDesc* samplerdesc = nullptr;
	root->GetHandle(reinterpret_cast<void**>(&samplerdesc), ROOTSIGNATURE_SAMPLER);

	//�T���v���[�Z�b�g
	for (unsigned int i = 0; i < samplerdesc->NumSampler; i++)
	{
		DX11Sampler* sampler = &samplerdesc->pSampler[i];

		switch (sampler->SamplerVisibility)
		{
		case ATL_SHADER_VISIBILITY::ALL:
			m_pDeferredContext->VSSetSamplers(sampler->SamplerRegister, 1, &sampler->pSamplerState);
			m_pDeferredContext->PSSetSamplers(sampler->SamplerRegister, 1, &sampler->pSamplerState);
			break;
		case ATL_SHADER_VISIBILITY::VERTEX:
			m_pDeferredContext->VSSetSamplers(sampler->SamplerRegister, 1, &sampler->pSamplerState);
			break;
		case ATL_SHADER_VISIBILITY::PIXEL:
			m_pDeferredContext->PSSetSamplers(sampler->SamplerRegister, 1, &sampler->pSamplerState);
			break;
		default:
			break;
		}
	}
}

void AstralLayerDirectX11::DX11CommandList::SetResource(
	unsigned int StartRootParametorIndex,
	AstralLayer::ATLIResource* pResource,
	unsigned int NumResourceIDs,
	unsigned int* pResourceIDs)
{
	for (unsigned int i = 0; i < NumResourceIDs; i++)
	{
		ATL_ROOT_PARAMETER parametor = m_pRootDesc->pParameters[StartRootParametorIndex + i];

		unsigned int id = 0;
		if (pResourceIDs != nullptr)
			id = pResourceIDs[i];

		switch (parametor.Type)
		{
		case ATL_DESCRIPTOR_TYPE::CBV:
		{
			//�o�b�t�@�[�󂯎��
			ID3D11Buffer* buffer = nullptr;
			reinterpret_cast<AstralRHI::RHIResource*>(pResource)->
				GetHandle(reinterpret_cast<void**>(&buffer), id);

			//�Z�b�g
			SetCBV(&parametor, buffer);
		}
			break;
		case ATL_DESCRIPTOR_TYPE::SRV:
		{
			//SRV�󂯎��
			ID3D11ShaderResourceView* srv = nullptr;
			reinterpret_cast<AstralRHI::RHIResource*>(pResource)->
				GetHandle(reinterpret_cast<void**>(&srv), id);

			//�Z�b�g
			SetSRV(&parametor, srv);
		}
			break;
		case ATL_DESCRIPTOR_TYPE::UAV:
			break;
		default:
			break;
		}
	}
}

void AstralLayerDirectX11::DX11CommandList::SetViewports(
	unsigned int NumViewports, 
	ATL_VIEWPORT* pViewports)
{
	//�Z�b�g�r���[�|�[�g
	m_pDeferredContext->RSSetViewports(
		NumViewports,
		reinterpret_cast<D3D11_VIEWPORT*>(pViewports));
}

void AstralLayerDirectX11::DX11CommandList::SetScissorRects(
	unsigned int NumRects, 
	ATL_RECT* pRects)
{
	//�Z�b�g���N�g
	m_pDeferredContext->RSSetScissorRects(
		NumRects,
		reinterpret_cast<D3D11_RECT*>(pRects));
}

void AstralLayerDirectX11::DX11CommandList::SetPrimitiveTopology(
	ATL_PRIMITIVE_TOPOLOGY Topology)
{
	//�Z�b�g�g�|���W�[
	m_pDeferredContext->IASetPrimitiveTopology(ConvToporogy(Topology));
}

void AstralLayerDirectX11::DX11CommandList::SetVertexBuffer(
	AstralLayer::ATLIResource* pVertex, 
	unsigned int ResourceID)
{
	//���_�o�b�t�@�[�łȂ��ꍇ�������Ȃ�
	if (pVertex->GetFlag() != ATL_RESOURCE_FLAG::VERTEXBUFFER)
		return;

	//���\�[�X�擾
	AstralRHI::RHIResource* resource = reinterpret_cast<AstralRHI::RHIResource*>(pVertex);

	//���_�󂯎��
	ID3D11Buffer* vertex = nullptr;
	resource->GetHandle(reinterpret_cast<void**> (&vertex), ResourceID);

	//stride�󂯎��
	unsigned int* stride = 0;
	resource->GetHandle(reinterpret_cast<void**>(&stride), RESOURCE_STRUCTURESIZE);

	//�Z�b�g
	unsigned int offset = 0;
	m_pDeferredContext->IASetVertexBuffers(0, 1, &vertex, stride, &offset);
}

void AstralLayerDirectX11::DX11CommandList::SetIndexBuffer(
	AstralLayer::ATLIResource* pIndexBuffer, 
	unsigned int ResourceID)
{
	//�C���f�b�N�X�o�b�t�@�[�łȂ��ꍇ�������Ȃ�
	if (pIndexBuffer->GetFlag() != ATL_RESOURCE_FLAG::INDEXBUFFER)
		return;

	//���\�[�X�擾
	AstralRHI::RHIResource* resource = 
		reinterpret_cast<AstralRHI::RHIResource*>(pIndexBuffer);

	//���_�󂯎��
	ID3D11Buffer* index = nullptr;
	resource->GetHandle(reinterpret_cast<void**> (&index), ResourceID);

	//�t�H�[�}�b�g�擾
	DXGI_FORMAT* format = nullptr;
	resource->GetHandle(reinterpret_cast<void**>(&format), RESOURCE_FORMAT);

	//�Z�b�g
	m_pDeferredContext->IASetIndexBuffer(index, *format, 0);
}

void AstralLayerDirectX11::DX11CommandList::ResourceBarrier(
	ATL_RESOURCE_BARRIER& Barrier)
{
	//11�ł̓o���A�͎g��Ȃ�
	Barrier;
}

void AstralLayerDirectX11::DX11CommandList::SetRenderTargets(
	AstralLayer::ATLIRenderTargetView* pRenderTargetView, 
	AstralLayer::ATLIDepthStencilView* pDepthStencilView)
{
	//RTV���󂯎��
	ID3D11RenderTargetView* rtv = nullptr;
	reinterpret_cast<AstralRHI::RHIRenderTargetView*>(pRenderTargetView)->
		GetHandle(reinterpret_cast<void**>(&rtv), RTV_RTV);

	//DSV���󂯎��@NULL�̏ꍇ�͎󂯎��Ȃ�
	ID3D11DepthStencilView* dsv = nullptr;
	if (pDepthStencilView != nullptr)
	{
		reinterpret_cast<AstralRHI::RHIDepthStencilView*>(pDepthStencilView)->
			GetHandle(reinterpret_cast<void**>(&dsv), DSV_DSV);
	}

	//�Z�b�g
	m_pDeferredContext->OMSetRenderTargets(1, &rtv, dsv);
}

void AstralLayerDirectX11::DX11CommandList::ClearRenderTargetView(
	AstralLayer::ATLIRenderTargetView* pRenderTargetView, 
	const float ColorRGBA[4])
{
	//RTV���󂯎��
	ID3D11RenderTargetView* rtv = nullptr;
	reinterpret_cast<AstralRHI::RHIRenderTargetView*>(pRenderTargetView)->
		GetHandle(reinterpret_cast<void**>(&rtv), RTV_RTV);

	//�Z�b�g
	m_pDeferredContext->ClearRenderTargetView(rtv, ColorRGBA);
}

void AstralLayerDirectX11::DX11CommandList::ClearDepthStencilView(
	AstralLayer::ATLIDepthStencilView* pDepthStencilView, 
	ATL_CLEAR_FLAG ClearFlags,
	float Depth, 
	unsigned char Stencil)
{
	//DSV���󂯎��
	ID3D11DepthStencilView* dsv = nullptr;
	reinterpret_cast<AstralRHI::RHIDepthStencilView*>(pDepthStencilView)->
		GetHandle(reinterpret_cast<void**>(&dsv), DSV_DSV);

	//�Z�b�g
	m_pDeferredContext->ClearDepthStencilView(dsv, static_cast<unsigned int>(ClearFlags), Depth, Stencil);
}

void AstralLayerDirectX11::DX11CommandList::DrawInstanced(
	unsigned int VertexCountParInstance, 
	unsigned int InstanceCount, 
	unsigned int StartVertexLocation, 
	unsigned int StartInstanceLocation)
{
	//�Z�b�g
	m_pDeferredContext->DrawInstanced(
		VertexCountParInstance,
		InstanceCount,
		StartVertexLocation,
		StartInstanceLocation
	);
}

void AstralLayerDirectX11::DX11CommandList::DrawIndexedInstanced(
	unsigned int IndexCountParInstance, 
	unsigned int InstanceCount, 
	unsigned int StartIndexLocation, 
	unsigned int BaceVertexLocation, 
	unsigned int StartInstanceLocation)
{
	//�Z�b�g
	m_pDeferredContext->DrawIndexedInstanced(
		IndexCountParInstance,
		InstanceCount,
		StartIndexLocation,
		BaceVertexLocation,
		StartInstanceLocation);
}

bool AstralLayerDirectX11::DX11CommandList::Close()
{
	//����
	return FAILED(m_pDeferredContext->FinishCommandList(true, &m_pCommandList));
}

void AstralLayerDirectX11::DX11CommandList::Release()
{
	delete this;
}

void AstralLayerDirectX11::DX11CommandList::GetHandle(
	void** pResource, 
	int Handle)
{
	//�f�[�^��n��
	switch (Handle)
	{
	case COMMANDLIST_CONTEXT:
		*pResource = m_pDeferredContext;
		break;
	case COMMANDLIST_COMMAND:
		*pResource = m_pCommandList;
		break;
	default:
		break;
	}
}
