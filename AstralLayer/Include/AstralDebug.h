/****************************************************************//**
 * @file AstralDebug.h
 * 
 * @brief OFF_ATLDEBUGをdefineするか_DEBUGをdefineしていない状態の場合AstralLayerのデバッグ機能をOFFにすることが出来ます
 *******************************************************************/
#pragma once
#include<assert.h>

//デバッグモードチェック
#if defined(_DEBUG) && !defined(OFF_ATLDEBUG)
#define ATL_DEBUG (1)
#endif

//デバッグ分岐
#if defined(ATL_DEBUG)
#define ATLAssertMessage(State, Message) (State != true ? _wassert(_CRT_WIDE(#Message), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)) : (void)0)
#define ATLAssert(State) (assert(State))
#else
#define ATLAssertMessage(State, Message) ((void)0)
#define ATLAssert(State) (assert(State))
#endif