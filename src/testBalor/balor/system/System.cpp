#include <balor/system/System.hpp>

#include <balor/io/File.hpp>
#include <balor/system/Module.hpp>
#include <balor/system/Version.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/String.hpp>


namespace balor {
	namespace system {
		namespace testSystem {



testCase(startup) { // �n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������i�ꌩ���[�N�Ɍ�����j�֐������炩���ߌĂ�ł���
	balor::test::UnitTest::ignoreHandleLeakCheck();

	System::userName(); // GetUserNameW �֐��̓n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������
}


testCase(commandLineArgCount) {
	testAssert(System::commandLineArgCount() == 1);
}


testCase(computerName) {
	testAssert(0 < System::computerName().length());

	// Caution: �e�}�V���Ŗڎ��Ŋm�F���邱��
}


testCase(getCommandLineArg) {
	testAssert(System::getCommandLineArg(0) == Module::current().file());
}


testCase(is64BitOs) {
	testNoThrow(System::is64BitOs());

	// Caution: �e�n�r�Ŗڎ��Ŋm�F���邱��
}


testCase(is64BitProcess) {
	testNoThrow(System::is64BitProcess());

	// Caution: �e�n�r�Ŗڎ��Ŋm�F���邱��
}


testCase(osKind) {
	testAssert(System::osKind() != System::OsKind::unknown);

	// Caution: �e�n�r�Ŗڎ��Ŋm�F���邱��
}


testCase(osServicePack) {
	testAssert(0 < System::osServicePack().length());

	// Caution: �e�n�r�Ŗڎ��Ŋm�F���邱��
}


testCase(osVersion) {
	testAssert(Version(5, 1) <= System::osVersion()); // XP�ȍ~

	// Caution: �e�n�r�Ŗڎ��Ŋm�F���邱��
}


testCase(processorCount) {
	testAssert(0 < System::processorCount());

	// Caution: �e�}�V���Ŗڎ��Ŋm�F���邱��
}


testCase(userName) {
	testAssert(0 < System::userName().length());

	// Caution: �e�}�V���Ŗڎ��Ŋm�F���邱��
}



		}
	}
}