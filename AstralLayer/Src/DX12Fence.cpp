#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

AstralLayerDirectX12::DX12Fence::~DX12Fence()
{

}

void AstralLayerDirectX12::DX12Fence::GetHandle(
	void** ppOut, 
	int Handle)
{
	Handle;
	*ppOut = &m_BufferIndex;
}

void AstralLayerDirectX12::DX12Fence::WaitDrawDone(
	AstralLayer::ATLICommandQueue* pCommandQueue, 
	AstralLayer::ATLISwapChain* pSwapChain)
{
	//�R�}���h�L���[���擾
	ID3D12CommandQueue* cq = nullptr;
	reinterpret_cast<AstralRHI::RHICommandQueue*>(pCommandQueue)->
		GetHandle(reinterpret_cast<void**>(&cq), COMMANDQUEUE_QUEUE);

	//�X���b�v�`�F�C�����擾
	IDXGISwapChain3* swap = nullptr;
	reinterpret_cast<AstralRHI::RHISwapChain*>(pSwapChain)->
		GetHandle(reinterpret_cast<void**>(&swap), SWAPCHAIN_SWAPCHAIN);

	//���݂�Fence�l���R�}���h�I�����Fence�ɏ������܂��悤�ɂ���
	unsigned long long fvalue = m_fenceValue;
	cq->Signal(m_pFence.Get(), fvalue);
	m_fenceValue++;

	//�R�}���h�L���[���I�����Ă��Ȃ����Ƃ��m�F����
	if (m_pFence->GetCompletedValue() < fvalue)
	{
		m_pFence->SetEventOnCompletion(fvalue, m_fenceEvent);
		WaitForSingleObject(m_fenceEvent, INFINITE);
	}

	//�o�b�N�o�b�t�@�[�̃C���f�b�N�X�擾
	m_BufferIndex = swap->GetCurrentBackBufferIndex();
}

void AstralLayerDirectX12::DX12Fence::Release()
{
	delete this;
}

bool AstralLayerDirectX12::DX12Fence::Create(ID3D12Device* pDevice)
{
	//�t�F���X�쐬
	if (FAILED(
		pDevice->CreateFence(
			0,
			D3D12_FENCE_FLAG_NONE,
			IID_PPV_ARGS(&m_pFence))
	))
		return false;

	return true;
}
