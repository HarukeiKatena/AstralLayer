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
	//デファードコンテキストリリース
	if (m_pDeferredContext != nullptr)
		m_pDeferredContext->Release();

	//コマンドリストリリース
	if (m_pCommandList != nullptr)
		m_pCommandList->Release();
}

bool AstralLayerDirectX11::DX11CommandList::Create(
	ID3D11Device* pDevice)
{
	//デファードコンテキスト作成
	if (FAILED(pDevice->CreateDeferredContext(0, &m_pDeferredContext)))
		return false;

	return true;
}

bool AstralLayerDirectX11::DX11CommandList::Reset(
	AstralLayer::ATLIPipeLine* pPipeLine, 
	AstralLayer::ATLIFence* pFence)
{
	pFence;//使わない

	//コマンドリストがnullではない場合リリース
	if (m_pCommandList != nullptr)
	{
		m_pCommandList->Release();
		m_pCommandList = nullptr;
	}

	//パイプラインを受け取る
	DX11PipeLineState* pipeline = nullptr;
	reinterpret_cast<AstralRHI::RHIPipeLine*>(pPipeLine)->
		GetHandle(reinterpret_cast<void**>(&pipeline), PIPELINE_PIPELINE);

	//シェーダー
	m_pDeferredContext->IASetInputLayout(pipeline->InputLayout);
	m_pDeferredContext->VSSetShader(pipeline->VertexShader, nullptr, 0);
	m_pDeferredContext->PSSetShader(pipeline->PixelShader, nullptr, 0);

	//ブレンドステート
	float BlendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_pDeferredContext->OMSetBlendState(pipeline->BlendState, BlendFactor, 0xffffffff);

	//ラスタライザー
	m_pDeferredContext->RSSetState(pipeline->Rasterizer);

	//デプスステンシルステート
	m_pDeferredContext->OMSetDepthStencilState(pipeline->DepthStencil, 0);

	return true;
}

void AstralLayerDirectX11::DX11CommandList::SetGraphicsRootSignature(
	AstralLayer::ATLIRootSignature* pRootSignature)
{
	//ルートシグネチャーRHIを受け取る
	AstralRHI::RHIRootSignature* root = 
		reinterpret_cast<AstralRHI::RHIRootSignature*>(pRootSignature);

	//ルートパラメーター受け取る
	root->GetHandle(reinterpret_cast<void**>(&m_pRootDesc), ROOTSIGNATURE_PARAMETOR);

	//サンプラー受け取る
	DX11SamplerDesc* samplerdesc = nullptr;
	root->GetHandle(reinterpret_cast<void**>(&samplerdesc), ROOTSIGNATURE_SAMPLER);

	//サンプラーセット
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
			//バッファー受け取る
			ID3D11Buffer* buffer = nullptr;
			reinterpret_cast<AstralRHI::RHIResource*>(pResource)->
				GetHandle(reinterpret_cast<void**>(&buffer), id);

			//セット
			SetCBV(&parametor, buffer);
		}
			break;
		case ATL_DESCRIPTOR_TYPE::SRV:
		{
			//SRV受け取る
			ID3D11ShaderResourceView* srv = nullptr;
			reinterpret_cast<AstralRHI::RHIResource*>(pResource)->
				GetHandle(reinterpret_cast<void**>(&srv), id);

			//セット
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
	//セットビューポート
	m_pDeferredContext->RSSetViewports(
		NumViewports,
		reinterpret_cast<D3D11_VIEWPORT*>(pViewports));
}

void AstralLayerDirectX11::DX11CommandList::SetScissorRects(
	unsigned int NumRects, 
	ATL_RECT* pRects)
{
	//セットレクト
	m_pDeferredContext->RSSetScissorRects(
		NumRects,
		reinterpret_cast<D3D11_RECT*>(pRects));
}

void AstralLayerDirectX11::DX11CommandList::SetPrimitiveTopology(
	ATL_PRIMITIVE_TOPOLOGY Topology)
{
	//セットトポロジー
	m_pDeferredContext->IASetPrimitiveTopology(ConvToporogy(Topology));
}

void AstralLayerDirectX11::DX11CommandList::SetVertexBuffer(
	AstralLayer::ATLIResource* pVertex, 
	unsigned int ResourceID)
{
	//頂点バッファーでない場合処理しない
	if (pVertex->GetFlag() != ATL_RESOURCE_FLAG::VERTEXBUFFER)
		return;

	//リソース取得
	AstralRHI::RHIResource* resource = reinterpret_cast<AstralRHI::RHIResource*>(pVertex);

	//頂点受け取る
	ID3D11Buffer* vertex = nullptr;
	resource->GetHandle(reinterpret_cast<void**> (&vertex), ResourceID);

	//stride受け取る
	unsigned int* stride = 0;
	resource->GetHandle(reinterpret_cast<void**>(&stride), RESOURCE_STRUCTURESIZE);

	//セット
	unsigned int offset = 0;
	m_pDeferredContext->IASetVertexBuffers(0, 1, &vertex, stride, &offset);
}

void AstralLayerDirectX11::DX11CommandList::SetIndexBuffer(
	AstralLayer::ATLIResource* pIndexBuffer, 
	unsigned int ResourceID)
{
	//インデックスバッファーでない場合処理しない
	if (pIndexBuffer->GetFlag() != ATL_RESOURCE_FLAG::INDEXBUFFER)
		return;

	//リソース取得
	AstralRHI::RHIResource* resource = 
		reinterpret_cast<AstralRHI::RHIResource*>(pIndexBuffer);

	//頂点受け取る
	ID3D11Buffer* index = nullptr;
	resource->GetHandle(reinterpret_cast<void**> (&index), ResourceID);

	//フォーマット取得
	DXGI_FORMAT* format = nullptr;
	resource->GetHandle(reinterpret_cast<void**>(&format), RESOURCE_FORMAT);

	//セット
	m_pDeferredContext->IASetIndexBuffer(index, *format, 0);
}

void AstralLayerDirectX11::DX11CommandList::ResourceBarrier(
	ATL_RESOURCE_BARRIER& Barrier)
{
	//11ではバリアは使わない
	Barrier;
}

void AstralLayerDirectX11::DX11CommandList::SetRenderTargets(
	AstralLayer::ATLIRenderTargetView* pRenderTargetView, 
	AstralLayer::ATLIDepthStencilView* pDepthStencilView)
{
	//RTVを受け取る
	ID3D11RenderTargetView* rtv = nullptr;
	reinterpret_cast<AstralRHI::RHIRenderTargetView*>(pRenderTargetView)->
		GetHandle(reinterpret_cast<void**>(&rtv), RTV_RTV);

	//DSVを受け取る　NULLの場合は受け取らない
	ID3D11DepthStencilView* dsv = nullptr;
	if (pDepthStencilView != nullptr)
	{
		reinterpret_cast<AstralRHI::RHIDepthStencilView*>(pDepthStencilView)->
			GetHandle(reinterpret_cast<void**>(&dsv), DSV_DSV);
	}

	//セット
	m_pDeferredContext->OMSetRenderTargets(1, &rtv, dsv);
}

void AstralLayerDirectX11::DX11CommandList::ClearRenderTargetView(
	AstralLayer::ATLIRenderTargetView* pRenderTargetView, 
	const float ColorRGBA[4])
{
	//RTVを受け取る
	ID3D11RenderTargetView* rtv = nullptr;
	reinterpret_cast<AstralRHI::RHIRenderTargetView*>(pRenderTargetView)->
		GetHandle(reinterpret_cast<void**>(&rtv), RTV_RTV);

	//セット
	m_pDeferredContext->ClearRenderTargetView(rtv, ColorRGBA);
}

void AstralLayerDirectX11::DX11CommandList::ClearDepthStencilView(
	AstralLayer::ATLIDepthStencilView* pDepthStencilView, 
	ATL_CLEAR_FLAG ClearFlags,
	float Depth, 
	unsigned char Stencil)
{
	//DSVを受け取る
	ID3D11DepthStencilView* dsv = nullptr;
	reinterpret_cast<AstralRHI::RHIDepthStencilView*>(pDepthStencilView)->
		GetHandle(reinterpret_cast<void**>(&dsv), DSV_DSV);

	//セット
	m_pDeferredContext->ClearDepthStencilView(dsv, static_cast<unsigned int>(ClearFlags), Depth, Stencil);
}

void AstralLayerDirectX11::DX11CommandList::DrawInstanced(
	unsigned int VertexCountParInstance, 
	unsigned int InstanceCount, 
	unsigned int StartVertexLocation, 
	unsigned int StartInstanceLocation)
{
	//セット
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
	//セット
	m_pDeferredContext->DrawIndexedInstanced(
		IndexCountParInstance,
		InstanceCount,
		StartIndexLocation,
		BaceVertexLocation,
		StartInstanceLocation);
}

bool AstralLayerDirectX11::DX11CommandList::Close()
{
	//閉じる
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
	//データを渡す
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
