#pragma once

#include <cassert>



/// �f�o�b�O���� assert ���������[�X���������������͎c��}�N���B
///
/// BOOST_VERIFY �Ɠ����B�i�I���W�i���� assert �����܂��Ă���j
/// verify �Ƃ����P��͏d������\���������̂Ō����ă��C�u�����̃w�b�_�t�@�C���Ŏg�p���Ă͂Ȃ�Ȃ��B
#if defined(verify)
#	error ERROR: verify macro is already defined!
#endif

#if defined(NDEBUG)
#	define verify(expression) ((void)(expression))
#else
#	define verify(expression) assert(expression)
#endif