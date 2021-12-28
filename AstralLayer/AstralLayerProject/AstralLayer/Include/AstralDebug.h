/****************************************************************//**
 * @file AstralDebug.h
 * 
 * @brief OFF_ATLDEBUG��define���邩_DEBUG��define���Ă��Ȃ���Ԃ̏ꍇAstralLayer�̃f�o�b�O�@�\��OFF�ɂ��邱�Ƃ��o���܂�
 *******************************************************************/
#pragma once
#include<assert.h>

//�f�o�b�O���[�h�`�F�b�N
#if defined(_DEBUG) && !defined(OFF_ATLDEBUG)
#define ATL_DEBUG (1)
#endif

//�f�o�b�O����
#if defined(ATL_DEBUG)
#define ATLAssertMessage(State, Message) (State != true ? _wassert(_CRT_WIDE(#Message), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)) : (void)0)
#define ATLAssert(State) (assert(State))
#else
#define ATLAssertMessage(State, Message) ((void)0)
#define ATLAssert(State) (assert(State))
#endif