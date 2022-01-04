#include "../Include/ATL/AstralDirectX12.h"
#include "../Include/AstralDebug.h"

DXGI_SAMPLE_DESC AstralLayerDirectX12::GetMSAA(ID3D12Device* pDevice, unsigned int Count)
{
    DXGI_SAMPLE_DESC out = { 1,0 };

    D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS ms{};
    ms.Format = DXGI_FORMAT_D32_FLOAT;
    for (unsigned int i = 0; i <= Count; i++)
    {
        ms.SampleCount = i;
        HRESULT hr = pDevice->CheckFeatureSupport(
            D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &ms, sizeof(ms));
        if (SUCCEEDED(hr))
        {
            if (0 < ms.NumQualityLevels)
            {
                out.Count = i;
                out.Quality = ms.NumQualityLevels - 1;
            }
        }
    }

    return out;
}