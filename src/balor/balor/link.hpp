#pragma once

/// include ���Ă����� balor ���C�u�����̃����N�������I�ɐݒ肵�Ă����B�S�Ă� all.hpp �� include �ς݁B
/// �����[�X�r���h�� NDEBUG ���`���Ȃ���Ԃ� beta �Ƃ��Ă���B

#if defined(_DEBUG)
#if defined(_DLL)
#pragma comment(lib, "balor_debug.lib")
#else
#pragma comment(lib, "balor_debug_static.lib")
#endif
#elif !defined(NDEBUG)
#if defined(_DLL)
#pragma comment(lib, "balor_beta.lib")
#else
#pragma comment(lib, "balor_beta_static.lib")
#endif
#else
#if defined(_DLL)
#pragma comment(lib, "balor.lib")
#else
#pragma comment(lib, "balor_static.lib")
#endif
#endif