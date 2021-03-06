/****************************************************************//**
 * @file AstralDirectX.h
 *******************************************************************/
#pragma once
#include"../AstralRendererInterface.h"
#include"../AstralInfo.h"
#include"AstralRHI.h"

/****************************************************************//**
 * ATL_FORMATをDXGIに変換するやつ
 *******************************************************************/
DXGI_FORMAT ConvDXGIFormat(ATL_FORMAT Format);
