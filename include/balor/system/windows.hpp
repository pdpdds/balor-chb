#pragma once

// windows.h �� include �p�B


#ifndef WINVER
#define WINVER 0x0501 // Windows XP �ȍ~
#endif

#ifndef _WIN32_WINNT                   
#define _WIN32_WINNT 0x0501 // Windows XP �ȍ~
#endif						

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410 // Windows 98 �ȍ~
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0600 // IE 6.0 �ȍ~
#endif

#if !defined(ENABLE_WIN32_LEAN_AND_MEAN)
#if !defined(WIN32_LEAN_AND_MEAN)
#	define WIN32_LEAN_AND_MEAN // windows.h �w�b�_�[����g�p����Ă��Ȃ����������O����
#endif
#endif
#if !defined(ENABLE_MINMAX)
#if !defined(NOMINMAX)
#	define NOMINMAX // min,max�}�N���𖳌��ɂ���
#endif
#endif
#if !defined(OEMRESOURCE)
#	define OEMRESOURCE // OCR�J�[�\�����\�[�X��L���ɂ���
#endif
#include <windows.h>

#if defined(MessageBox) // �N���X���Ƃ��Ԃ�̂�
#undef MessageBox
#endif