#pragma once

#include <balor/Exception.hpp>


namespace balor {
	namespace system {



/**
 * COM �̏������ƏI���̎�������񋟂���B
 * 
 * ���C���X���b�h�� initialize �܂��� oleInitialize �֐����Ă񂾏�́A�v���Z�X�I�����Ɏ����I�� uninitialize �܂��� oleUninitialize �֐����ĂԁB
 * ���C���X���b�h�ł͂Ȃ��X���b�h����Ăԏꍇ�͎����I�ȏI�������͍s���Ȃ����Ƃɒ��ӁB
 * �v���Z�X�I�����ɏ����������ƏI�������̌Ăяo���񐔂��������Ȃ���� assert �Ōx������B
 */
class Com {
public:
	/// COM �����������������ꍇ�B
	class UninitializedException : public Exception {};

	/// COM �C���^�[�t�F�[�X�����W�X�g���ɖ��o�^�������薢�����������ꍇ�B
	class InterfaceNotFoundException : public Exception {};

public:
	/// COM ������������BisSTA �� true �Ȃ�� STA�Afalse �Ȃ�� MTA �ŏ���������B
	static void initialize(bool isSTA = true);
	/// ���C���X���b�h�ɂ����� COM �������ς݂��ۂ���Ԃ��B
	static bool initialized();
	/// ���C���X���b�h���ǂ����B
	static bool isMainThread();
	/// OLE ������������BCOM �����������ł������ꍇ�͓����� COM �� STA �ŏ���������B
	static void oleInitialize();
	/// ���C���X���b�h�ɂ����� OLE �������ς݂��ǂ����B
	static bool oleInitialized();
	/// OLE �̏I���������s���B
	static void oleUninitialize();
	/// COM �̏I���������s���B
	static void uninitialize();
};



	}
}