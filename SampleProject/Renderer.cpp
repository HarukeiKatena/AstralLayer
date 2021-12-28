#include "Renderer.h"

#include<AstralLayerFactory.h>
#include<AstralSupport.h>

void Renderer::Init(HWND hwnd)
{
	//�t�@�N�g���[
	AstralLayerFactory::ATLIFactory* factory = 
		AstralLayerFactory::CreateAstralFactory(ATL_GRAPHIC_INTERFACE::DirectX12);

	//�f�o�C�X
	m_pDevice = factory->CreateDevice();

	//�t�@�N�g���[���
	factory->Release();
	factory = nullptr;

	//�R�}���h�L���[
	m_pCommandQueue = m_pDevice->CreateCommandQueue();

	//�X���b�v�`�F�C��
	ATL_SWAPCHAIN_DESC swapdesc{};
	swapdesc.Width = SCREEN_WIDHT;
	swapdesc.Height = SCREEN_HEIGHT;
	swapdesc.hWnd = hwnd;
	swapdesc.Sample.Count = 1;
	swapdesc.Sample.Quality = 0;
	swapdesc.Windowed = true;
	m_pSwapChain = m_pDevice->CreateSwapChain(swapdesc, m_pCommandQueue);

	//�����_�[�^�[�Q�b�g�r���[
	m_pRenderTargetView = m_pDevice->CreateRenderTargetView(m_pSwapChain, SCREEN_WIDHT, SCREEN_HEIGHT);

	//ATLIRenderTargetView* test = m_pDevice->CreateRenderTargetView(nullptr, SCREEN_WIDHT, SCREEN_HEIGHT);

	//�R�}���h���X�g
	m_pCommandList = m_pDevice->CreateCommandList();
	m_pClearCommandList = m_pDevice->CreateCommandList();

	//�t�F���X
	m_pFence = m_pDevice->CreateFence();

	//�f�v�X�X�e���V���r���[
	{
		ATL_DEPTH_STENCIL_VIEW_DESC desc;
		desc.Width = SCREEN_WIDHT;
		desc.Height = SCREEN_HEIGHT;
		desc.SampleDesc = swapdesc.Sample;
		desc.Dimension = ATL_DSV_DIMENSION::TEXTURE2DMS;
		m_pDepthStencilView = m_pDevice->CreateDepthStencilView(desc);
	}


	//���[�g�V�O�l�`���[
	ATL_ROOT_PARAMETER atlrootpara[4] = {
		{ATL_DESCRIPTOR_TYPE::CBV,ATL_SHADER_VISIBILITY::VERTEX,0},
		{ATL_DESCRIPTOR_TYPE::CBV,ATL_SHADER_VISIBILITY::VERTEX,1},
		{ATL_DESCRIPTOR_TYPE::CBV,ATL_SHADER_VISIBILITY::VERTEX,2},
		{ATL_DESCRIPTOR_TYPE::SRV,ATL_SHADER_VISIBILITY::PIXEL,0},
	};

	ATL_SAMPLER_DESC atlsamp = ATLSCreateSamplerDesc(
		ATL_FILTER::MIN_MAG_MIP_LINEAR,
		ATL_ADDRESS_MODE::WRAP
	);

	ATL_ROOT_SIGNATURE_DESC atlroot{};
	atlroot.NumRootParameters = 4;
	atlroot.pRootParameters = atlrootpara;
	atlroot.NumSamplers = 1;
	atlroot.pSamplers = &atlsamp;

	m_pRootSignature = m_pDevice->CreateRootSignature(atlroot);

	//���_�V�F�[�_�[
	ATLSShaderBinary vs;
	vs.LoadShaderBinary("Shader//unlitVS.cso");

	//�s�N�Z���V�F�[�_�[
	ATLSShaderBinary ps;
	ps.LoadShaderBinary("Shader//unlit_intexPS.cso");

	ATL_INPUT_ELEMENT_DESC atlelement[] = {
		{"POSITION", ATL_FORMAT::R32G32B32_FLOAT,0},
		{"NORMAL", ATL_FORMAT::R32G32B32_FLOAT,4 * 3},
		{"COLOR", ATL_FORMAT::R32G32B32A32_FLOAT,4 * 6},
		{"TEXCOORD", ATL_FORMAT::R32G32_FLOAT,4 * 10}
	};

	ATL_BLEND_DESC Blend = ATLSCreateBlendDesc();

	ATL_RASTERIZER_DESC Rasterizer = ATLSCreateRasterizerDesc(ATL_FILL_MODE::SOLID, ATL_CULL_MODE::BACK);

	ATL_GRAPHICS_PIPELINE_STATE_DESC PipeLineState =
		ATLSCreatePipeLineStateDesc(
			vs.GetShaderByteCode(),
			ps.GetShaderByteCode(),
			Blend,
			Rasterizer,
			true,
			false,
			{ atlelement,4 },
			8,0
	);

	m_pPipeLine = m_pDevice->CreatePipeLine(m_pRootSignature, PipeLineState);

	//�s�񃊃\�[�X
	{
		ATL_RESOURCE_DESC desc = ATLSCreateConstantBufferResourceDesc(
			sizeof(Matrix),
			1,
			1,
			ATL_RESOURCE_TYPE::UPLOAD
		);

		Matrix matrix = Matrix::Identity;

		//���[���h
		m_pWorldBuffer = m_pDevice->CreateResource(desc, &matrix);

		//�r���[�v���W�F�N�V����
		desc.NumObject = 2;
		m_pViewProjection = m_pDevice->CreateResource(desc, &matrix);
		
		//�f�[�^�Z�b�g
		{
			//�r���[
			Vector3 eye(0.0f, 2.0f, -3.0f), at(0.0f, 0.0f, 0.0f), up(0.0f, 1.0f, 0.0f);
			matrix = XMMatrixLookAtLH(eye, at, up);
			matrix = XMMatrixTranspose(matrix);
			m_ViewID = m_pViewProjection->SetSubResource(&matrix, sizeof(matrix));

			//�v���W�F�N�V����
			matrix = XMMatrixPerspectiveFovLH(
				1.0f,
				static_cast<float>(SCREEN_WIDHT) / static_cast<float>(SCREEN_HEIGHT),
				1.0f, 1000.0f);
			matrix = XMMatrixTranspose(matrix);
			m_ProjectionID = m_pViewProjection->SetSubResource(&matrix, sizeof(matrix));
		}
	}

	//���_
	{
		ATL_VERTEX_3D vertex[] =
		{
			{Vector3(-0.5f,0.5f,0.5f),  Vector3(0.0f,1.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,0.0f)},//���
			{Vector3(0.5f ,0.5f,0.5f),  Vector3(0.0f,1.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,0.0f)},
			{Vector3(-0.5f,0.5f,-0.5f), Vector3(0.0f,1.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,1.0f)},
			{Vector3(0.5f ,0.5f,-0.5f), Vector3(0.0f,1.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,1.0f)},

			{Vector3(0.5f ,-0.5f,0.5f),  Vector3(0.0f,-1.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,0.0f)},//����
			{Vector3(-0.5f,-0.5f,0.5f),  Vector3(0.0f,-1.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,0.0f)},
			{Vector3(0.5f ,-0.5f,-0.5f), Vector3(0.0f,-1.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,1.0f)},
			{Vector3(-0.5f,-0.5f,-0.5f), Vector3(0.0f,-1.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,1.0f)},
			 							 						   							   
			{Vector3(-0.5f,0.5f,-0.5f),  Vector3(0.0f,0.0f,-1.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,0.0f)},//����
			{Vector3(0.5f ,0.5f,-0.5f),  Vector3(0.0f,0.0f,-1.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,0.0f)},
			{Vector3(-0.5f,-0.5f,-0.5f), Vector3(0.0f,0.0f,-1.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,1.0f)},
			{Vector3(0.5f ,-0.5f,-0.5f), Vector3(0.0f,0.0f,-1.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,1.0f)},
			 							 
			{Vector3(0.5f ,0.5f,-0.5f),  Vector3(1.0f,0.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,0.0f)},//�E��
			{Vector3(0.5f ,0.5f,0.5f),   Vector3(1.0f,0.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,0.0f)},
			{Vector3(0.5f ,-0.5f,-0.5f), Vector3(1.0f,0.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,1.0f)},
			{Vector3(0.5f ,-0.5f,0.5f),  Vector3(1.0f,0.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,1.0f)},
			 							 						  							  
			{Vector3(0.5f,0.5f,0.5f),    Vector3(0.0f,0.0f,1.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,0.0f)},//����
			{Vector3(-0.5f,0.5f,0.5f),   Vector3(0.0f,0.0f,1.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,0.0f)},
			{Vector3(0.5f,-0.5f,0.5f),   Vector3(0.0f,0.0f,1.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,1.0f)},
			{Vector3(-0.5f,-0.5f,0.5f),  Vector3(0.0f,0.0f,1.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,1.0f)},
			 							 						  							  
			{Vector3(-0.5f,0.5f,0.5f),   Vector3(0.0f,0.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,0.0f)},//����
			{Vector3(-0.5f,0.5f,-0.5f),  Vector3(0.0f,0.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,0.0f)},
			{Vector3(-0.5f,-0.5f,0.5f),  Vector3(0.0f,0.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(0.0f,1.0f)},
			{Vector3(-0.5f,-0.5f,-0.5f), Vector3(0.0f,0.0f,0.0f), Color(1.0f,1.0f,1.0f,1.0f), Vector2(1.0f,1.0f)},
		};

		ATL_RESOURCE_DESC desc = ATLSCreateVertexBufferResourceDesc(
			sizeof(ATL_VERTEX_3D),
			24,
			1,
			ATL_RESOURCE_TYPE::DEFAULT
		);

		m_pVertexBuffer = m_pDevice->CreateResource(desc, vertex);
	}

	//�C���f�b�N�X�o�b�t�@�[
	{
		unsigned int index[]{
		0,1,2,2,1,3,
		4,5,6,6,5,7,
		8,9,10,10,9,11,
		12,13,14,14,13,15,
		16,17,18,18,17,19,
		20,21,22,22,21,23
		};

		ATL_RESOURCE_DESC desc = ATLSCreateIndexBufferResourceDesc(
			sizeof(unsigned int),
			36,
			1,
			ATL_RESOURCE_TYPE::DEFAULT
		);

		m_pIndexBuffer = m_pDevice->CreateResource(desc, index);
	}

	//�e�N�X�`��
	{
		const unsigned int texw = 64;
		const unsigned int texh = 64;
		Vector4 texdata[texh][texw];
		for (int h = 0; h < texh; h++)
		{
			for (int w = 0; w < texw; w++)
			{
				texdata[h][w] = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}

		for (int h = 0; h < texh / 2; h++)
		{
			for (int w = 0; w < texw / 2; w++)
			{
				texdata[h][w] = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
				texdata[h][w + (texw / 2)] = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
				texdata[h + (texh / 2)][w] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
				texdata[h + (texh / 2)][w + (texw / 2)] = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
			}
		}

		ATL_RESOURCE_DESC desc = ATLSCreateTexture2DBufferResourceDesc(
			sizeof(Vector4),
			texw,
			texh,
			1,
			ATL_FORMAT::R32G32B32A32_FLOAT,
			{ 1,0 },
			ATL_RESOURCE_TYPE::DEFAULT
		);

		m_pTexture = m_pDevice->CreateResource(desc, texdata);
	}

	m_Viewport = ATLSCreateViewport(SCREEN_WIDHT, SCREEN_HEIGHT);
	m_Rect = ATLSCreateRect(SCREEN_WIDHT, SCREEN_HEIGHT);
}

void Renderer::Update(void)
{
}

void Renderer::Draw(void)
{

	//�`�揈�����I����ĂȂ��ꍇ�͑҂�
	m_pFence->WaitDrawDone(m_pCommandQueue, m_pSwapChain);

	//rtv�̃��\�[�X�擾
	ATLIResource* pRTV = m_pRenderTargetView->GetResource(m_pFence);

	{
		//�R�}���h���Z�b�g
		m_pClearCommandList->Reset(m_pPipeLine, m_pFence);

		//�o���A
		ATL_RESOURCE_BARRIER barrier{};
		barrier.Type = ATL_BARRIER_TYPE::RENDER_TARGET;
		barrier.pResource = pRTV;
		barrier.StateBefore = ATL_RESOURCE_STATE::PRESENT;
		barrier.StateAfter = ATL_RESOURCE_STATE::RENDER_TARGET;
		m_pClearCommandList->ResourceBarrier(barrier);

		//��ʃN���A
		float color[4] = { 0.0f,0.0f,0.5f,1.0f };
		m_pClearCommandList->ClearRenderTargetView(m_pRenderTargetView, color);

		//�f�v�X�X�e���V���r���[
		m_pClearCommandList->ClearDepthStencilView(m_pDepthStencilView, ATL_CLEAR_FLAG::DEPTH, 1.0f, 0);

		//�o���A
		barrier.StateBefore = ATL_RESOURCE_STATE::RENDER_TARGET;
		barrier.StateAfter = ATL_RESOURCE_STATE::PRESENT;
		m_pClearCommandList->ResourceBarrier(barrier);

		//�R�}���h����
		m_pClearCommandList->Close();
	}

	//�R�}���h���Z�b�g
	m_pCommandList->Reset(m_pPipeLine, m_pFence);

	//���[�g�V�O�l�`���[�Z�b�g
	m_pCommandList->SetGraphicsRootSignature(m_pRootSignature);

	//�o���A
	ATL_RESOURCE_BARRIER barrier{};
	barrier.Type = ATL_BARRIER_TYPE::RENDER_TARGET;
	barrier.pResource = pRTV;
	barrier.StateBefore = ATL_RESOURCE_STATE::PRESENT;
	barrier.StateAfter = ATL_RESOURCE_STATE::RENDER_TARGET;
	m_pCommandList->ResourceBarrier(barrier);

	//�����_�[�^�[�Q�b�g�r���[
	m_pCommandList->SetRenderTargets(m_pRenderTargetView, m_pDepthStencilView);

	//���\��
	{
		//���[���h�f�[�^�Z�b�g
		static float yrotate = 0.0f;
		yrotate += 0.4f;
		Matrix matrix, rota;
		rota = XMMatrixRotationY(XMConvertToRadians(yrotate));
		matrix = rota;
		m_WorldID = m_pWorldBuffer->SetSubResource(&matrix, sizeof(Matrix));

		//�R�}���h�Z�b�g
		m_pCommandList->SetResource(0, m_pWorldBuffer, 1, &m_WorldID);

		unsigned int id[2] = { m_ViewID, m_ProjectionID };
		m_pCommandList->SetResource(1, m_pViewProjection, 2, id);

		m_pCommandList->SetResource(3, m_pTexture, 1, nullptr);

		//�r���[�|�[�g�A���N�g
		m_pCommandList->SetViewports(1, &m_Viewport);
		m_pCommandList->SetScissorRects(1, &m_Rect);

		//�g�|���W�[
		m_pCommandList->SetPrimitiveTopology(ATL_PRIMITIVE_TOPOLOGY::TRIANGLELIST);
		
		//���_�A�C���f�b�N�X
		m_pCommandList->SetVertexBuffer(m_pVertexBuffer, 0);
		m_pCommandList->SetIndexBuffer(m_pIndexBuffer, 0);
		
	}

	//�h���[�R�[��
	m_pCommandList->DrawIndexedInstanced(36, 1, 0, 0, 0);

	//�o���A
	barrier.StateBefore = ATL_RESOURCE_STATE::RENDER_TARGET;
	barrier.StateAfter = ATL_RESOURCE_STATE::PRESENT;
	m_pCommandList->ResourceBarrier(barrier);

	//�R�}���h����
	m_pCommandList->Close();

	//�R�}���h���s
	ATLICommandList* command[2] = { m_pClearCommandList, m_pCommandList };
	m_pCommandQueue->ExecuteCommandLists(2, command);

	//�`��
	m_pSwapChain->Present(1);

	//RTV�g���I������̂ŉ��
	pRTV->Release();
}

void Renderer::Uninit(void)
{
	//�`�悪�I���܂ő҂�
	m_pFence->WaitDrawDone(m_pCommandQueue, m_pSwapChain);

	m_pTexture->Release();
	m_pWorldBuffer->Release();
	m_pViewProjection->Release();
	m_pVertexBuffer->Release();
	m_pIndexBuffer->Release();
	m_pFence->Release();
	m_pPipeLine->Release();
	m_pCommandList->Release();
	m_pCommandQueue->Release();
	m_pRenderTargetView->Release();
	m_pSwapChain->Release();
	m_pDevice->Release();
}
