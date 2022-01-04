#include "..\Include\ATL\AstralDirectX.h"

DXGI_FORMAT ConvDXGIFormat(ATL_FORMAT Format)
{
    switch (Format)
    {
    case ATL_FORMAT::UNKNOWN:                    return DXGI_FORMAT_UNKNOWN;
    case ATL_FORMAT::R32G32B32A32_TYPELESS:      return DXGI_FORMAT_R32G32B32A32_TYPELESS;
    case ATL_FORMAT::R32G32B32A32_FLOAT:         return DXGI_FORMAT_R32G32B32A32_FLOAT;
    case ATL_FORMAT::R32G32B32A32_UINT:          return DXGI_FORMAT_R32G32B32A32_UINT;
    case ATL_FORMAT::R32G32B32A32_SINT:          return DXGI_FORMAT_R32G32B32A32_SINT;
    case ATL_FORMAT::R32G32B32_TYPELESS:         return DXGI_FORMAT_R32G32B32_TYPELESS;
    case ATL_FORMAT::R32G32B32_FLOAT:            return DXGI_FORMAT_R32G32B32_FLOAT;
    case ATL_FORMAT::R32G32B32_UINT:             return DXGI_FORMAT_R32G32B32_UINT;
    case ATL_FORMAT::R32G32B32_SINT:             return DXGI_FORMAT_R32G32B32_SINT;
    case ATL_FORMAT::R16G16B16A16_TYPELESS:      return DXGI_FORMAT_R16G16B16A16_TYPELESS;
    case ATL_FORMAT::R16G16B16A16_UINT:          return DXGI_FORMAT_R16G16B16A16_UINT;
    case ATL_FORMAT::R16G16B16A16_SINT:          return DXGI_FORMAT_R16G16B16A16_SINT;
    case ATL_FORMAT::R32G32_TYPELESS:            return DXGI_FORMAT_R32G32_TYPELESS;
    case ATL_FORMAT::R32G32_FLOAT:               return DXGI_FORMAT_R32G32_FLOAT;
    case ATL_FORMAT::R32G32_UINT:                return DXGI_FORMAT_R32G32_UINT;
    case ATL_FORMAT::R32G32_SINT:                return DXGI_FORMAT_R32G32_SINT;
    case ATL_FORMAT::R8G8B8A8_TYPELESS:          return DXGI_FORMAT_R8G8B8A8_TYPELESS;
    case ATL_FORMAT::R8G8B8A8_UINT:              return DXGI_FORMAT_R8G8B8A8_UINT;
    case ATL_FORMAT::R8G8B8A8_SINT:              return DXGI_FORMAT_R8G8B8A8_SINT;
    case ATL_FORMAT::R16G16_TYPELESS:            return DXGI_FORMAT_R16G16_TYPELESS;
    case ATL_FORMAT::R16G16_UINT:                return DXGI_FORMAT_R16G16_UINT;
    case ATL_FORMAT::R16G16_SINT:                return DXGI_FORMAT_R16G16_SINT;
    case ATL_FORMAT::R32_TYPELESS:               return DXGI_FORMAT_R32_TYPELESS;
    case ATL_FORMAT::R32_FLOAT:                  return DXGI_FORMAT_R32_FLOAT;
    case ATL_FORMAT::R32_UINT:                   return DXGI_FORMAT_R32_UINT;
    case ATL_FORMAT::R32_SINT:                   return DXGI_FORMAT_R32_SINT;
    case ATL_FORMAT::R8G8_TYPELESS:              return DXGI_FORMAT_R8G8_TYPELESS;
    case ATL_FORMAT::R8G8_UINT:                  return DXGI_FORMAT_R8G8_UINT;
    case ATL_FORMAT::R8G8_SINT:                  return DXGI_FORMAT_R8G8_SINT;
    case ATL_FORMAT::R16_TYPELESS:               return DXGI_FORMAT_R16_TYPELESS;
    case ATL_FORMAT::R16_UINT:                   return DXGI_FORMAT_R16_UINT;
    case ATL_FORMAT::R16_SINT:                   return DXGI_FORMAT_R16_SINT;
    case ATL_FORMAT::R8_TYPELESS:                return DXGI_FORMAT_R8_TYPELESS;
    case ATL_FORMAT::R8_UINT:                    return DXGI_FORMAT_R8_UINT;
    case ATL_FORMAT::R8_SINT:                    return DXGI_FORMAT_R8_SINT;
    default:                                     return DXGI_FORMAT_UNKNOWN;
    }
}
