#pragma once

#include <balor/Listener.hpp>
#include <balor/StringRange.hpp>

struct _EXCEPTION_POINTERS;

namespace balor {
class String;
}


namespace balor {
	namespace test {



/**
 * �f�o�b�O�o�́A�������[���[�N���o�A�N���b�V���_���v�o�́A�X�^�b�N�g���[�X�Ƃ������f�o�b�O�Ɏg���֐����T�|�[�g����B
 */
class Debug {
public:
	typedef ::_EXCEPTION_POINTERS EXCEPTION_POINTERS;

public:
	/// �~�j�_���v�t�@�C�����쐬����B
	/// �t�@�C�����⃁�b�Z�[�W���w�肵�Ȃ������ꍇ�� enableCrashDumpHandler �֐��Őݒ肳�ꂽ�l���g�p�����B
	static bool createDumpFile(EXCEPTION_POINTERS* exceptions = nullptr, StringRange filePath = L"", bool showMessageBox = false, StringRange message = L"", StringRange failedMessage = L"");

	/// �f�o�b�K��Ŏ��s���Ă���ꍇ�͎��s�𒆒f���ăf�o�b�K�ɐ�����ڂ��B�f�o�b�K��ł͂Ȃ��ꍇ�͍\������O�𔭐�������B
	static void debugBreak();

	/// catch ����Ȃ� C++ ��O���邢�͍\������O�������������ɁA�����I������O�Ƀ~�j�_���v�t�@�C����f���o���悤�ɐݒ肷��B
	/// ���̐ݒ�̓X���b�h�ADLL�𒴂��ėL���B���������ɋN������Ă��鑼�X���b�h�ɂ͌��ʂ������B
	/// �f�o�b�K�Ŏ��s���Ă���ꍇ�͂��̋@�\�͗L���ɂȂ�Ȃ����A��O�������ɂ͂��̂܂܃f�o�b�K�Ō���ׂ��ł���B
	/// �_���v�t�@�C�����⃁�b�Z�[�W���w�肵�Ȃ������ꍇ�͎��s�t�@�C���Ɠ����f�B���N�g����ɍ쐬����悤�ɓK���ɐ��������B
	/// ���̎����������t�@�C�����ɂ͎��s�t�@�C���̃t�@�C���o�[�W�������܂܂��B<br><br>
	/// 
	/// C++ ��O�����������ꍇ�̓_���v��f������ ::balor::test::UnhandledException �𓊂���B
	/// ���̗�O�� catch ���鎖�ŃN���b�V���_���v��f���f�X�g���N�^���ĂԎ����ł���Bcatch ���Ȃ��ꍇ�f�X�g���N�^�͌Ă΂ꂸ�ɂ��̏�ŏI������B
	/// �\������O�����������ꍇ�A�_���v��f������A�v���P�[�V�����͂��̏�ŏI������B
	/// �\������O�����������ꍇ�ł��_���v��f���f�X�g���N�^���ĂԂɂ́A�܂��R���p�C���̃I�v�V���������L�̂悤�ɕύX����B<br>
	/// C/C++���R�[�h������C++�̗�O��L���ɂ��� = �͂� - SEH �̗�O����(/EHa)
	/// <br>���� _set_se_translator �֐����g���č\������O�� C++ ��O�ɕϊ�����B
	/// ���̊֐��̒��ŁA�����ɓn���Ă��� EXCEPTION_POINTERS ���g���� Debug::createDumpFile �֐��Ń_���v���o�͂���B
	/// �ϊ����ē�������O�� catch ����΃f�X�g���N�^���Ă΂��B�ȉ��͂��̃R�[�h��B
	/// <pre><code>
	///#include <windows.h>
	///#include <eh.h>
	///#include <balor/test/all.hpp>
	///
	///void se_translator(unsigned int /*code*/, struct _EXCEPTION_POINTERS* ep)
	///{
	///	balor::test::Debug::createDumpFile(ep);
	///	throw balor::test::UnhandledException(); // �W��C++�̗�O�𔭐�������
	///}
	///
	///int APIENTRY wWinMain(HINSTANCE ,HINSTANCE ,LPWSTR, int ) {
	///	balor::test::Debug::enableCrashDumpHandler();
	///	_set_se_translator(&se_translator);
	///
	///	try {
	///		runApplication(); // ���[�U�̏���
	///	} catch (balor::test::UnhandledException& ) { // ����Ńf�X�g���N�^���Ă�
	///	}
	///	return 0;
	///}
	////</code></pre>
	static void enableCrashDumpHandler(StringRange crashDumpFilePath = L"", bool showMessageBox = true, StringRange message = L"", StringRange failedMessage = L"");

	/// �f�o�b�O�r���h���̂݁A���������[�N�̃`�F�b�N��L���ɂ���B
	/// ���s�I�����Ƀf�o�b�O�o�͂Ƀ��[�N������������񍐂���B���̐ݒ�̓X���b�h�ADLL�𒴂��ėL���B<br><br>
	/// �E���������[�N�����\�[�X�R�[�h�ʒu�̓���<br>
	/// �܂��f�o�b�O�E�C���h�E�̃��������[�N���|�[�g���m�F���A�Ⴆ�Ή��L�̂悤�ɕ񍐂��ꂽ�Ƃ����<br>
	/// {1873} normal block at 0x00B64868, 4 bytes long.
	/// <br>{1873} �Ƃ����̂����������蓖�ĂɊ���U��ꂽ�ԍ��ɂȂ�ŁA�f�o�b�K���N�����ăv���O�����̍ŏ��Ŏ~�߂ăE�H�b�`�E�C���h�E�ɉ��L�̖��O��ǉ�����B<br>
	/// {,,msvcr100d.dll}_crtBreakAlloc
	/// <br>�� msvcr100d.dll �Ƃ��� DLL ���� Visual Studio 2010 �p�̂��̂Ȃ̂ŁA�g�p���Ă��� Visual Studio �ɂ����� DLL ���ɕύX���K�v�B<br>
	/// �������A�v���W�F�N�g�̐ݒ�i�\���v���p�e�B��C/C++���R�[�h�����������^�C�����C�u�����j���u�}���`�X���b�h�f�o�b�O(/MTd)�v�ɕύX���Ă���Ȃ�<br>
	/// _crtBreakAlloc
	/// <br>�Ƃ������O�ɂ���B�����Ēl�� 1873 �Ɠ��͂��Ď��s����ƁA���|�[�g���ꂽ�����������蓖�Ă����_�Ńu���C�N�i���s���f�j����B
	static void enableMemoryLeakCheck();

	/// ���݂̃v���Z�X���f�o�b�K��œ����Ă��邩�ǂ����B
	static bool isDebuggerPresent();

	/// �f�o�b�O�o�̓C�x���g�B�ݒ肵�Ȃ��ꍇ�͒P�Ƀf�o�b�O�o�͂��s���B���̊֐��̓X���b�h�Z�[�t�ł͂Ȃ��̂Œ��ӁB
	static Listener<ByteStringRange>& onWrite();

	/// �X�^�b�N�g���[�X��Ԃ��B
	/// �J�����ȊO�Ŏg�p����ꍇ�� exe �t�@�C���Ƌ��� pdf �t�@�C�����z�z����K�v������B
	/// �\�[�X�R�[�h������菜���� pdf �t�@�C���̔z�z����ʓI�B�i�����J�[���f�o�b�O���v���C�x�[�g�V���{���̍폜�j
	/// ���̊֐����g���ꍇ�ADbghelp.dll �� VS2010EE �ɕt���̂��̂ł͑� OS ���ł��܂����삵�Ȃ��̂Œ��ӁB�ŐV�ł��_�E�����[�h���ăA�v���P�[�V�����Ƃ�������ɔz�z����K�v������B
	/// �������ʓ|�Ȃ̂ŊJ�����ȊO�ł̓N���b�V���_���v���g���ق����ǂ��B
	static String stackTrace();

	/// �f�o�b�O�o�͂�����B
	static void write(ByteStringRange message);
	static void write(StringRange message);
	/// ���s��ǉ����ăf�o�b�O�o�͂�����B
	static void writeLine(ByteStringRange message);
	static void writeLine(StringRange message);
};



	}
}