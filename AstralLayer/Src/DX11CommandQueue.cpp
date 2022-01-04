#include"../Include/ATL/AstralDirectX11.h"
#include"../Include/AstralDebug.h"

AstralLayerDirectX11::DX11CommandQueue::~DX11CommandQueue()
{
	//�C�~�f�B�G�C�g�R���e�L�X�g�����[�X
	if (m_pImmidiateContext != nullptr)
		m_pImmidiateContext->Release();
}

void AstralLayerDirectX11::DX11CommandQueue::GetHandle(
	void** ppResource, 
	int Handle)
{
	Handle;
	*ppResource = m_pImmidiateContext;
}

bool AstralLayerDirectX11::DX11CommandQueue::ExecuteCommandLists(
	unsigned int NumCommandLists, 
	AstralLayer::ATLICommandList* const* ppCommandLists)
{
	for (unsigned int i = 0; i < NumCommandLists; i++)
	{
		if(ppCommandLists[i] == nullptr)
			continue;

		//�R�}���h���X�g�擾
		ID3D11CommandList* commandlist = nullptr;
		reinterpret_cast<AstralRHI::RHICommandList*>(ppCommandLists[i])->
			GetHandle(reinterpret_cast<void**>(&commandlist), COMMANDLIST_COMMAND);

		//�R�}���h���s
		m_pImmidiateContext->ExecuteCommandList(commandlist, true);
	}

	return true;
}

void AstralLayerDirectX11::DX11CommandQueue::Release()
{
	delete this;
}

bool AstralLayerDirectX11::DX11CommandQueue::Create(
	ID3D11Device* pDevice)
{
	//�C�~�f�B�G�C�g�R���e�L�X�g�擾
	ID3D11DeviceContext* dcon = nullptr;
	pDevice->GetImmediateContext(&dcon);
	if (dcon == nullptr)//�ꉞnull�������玸�s
		return false;

	//DeviceContext4�ɃL���X�g
	m_pImmidiateContext = reinterpret_cast<ID3D11DeviceContext4*>(dcon);

	return true;
}
