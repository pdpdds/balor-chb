#include <balor/test/Debug.hpp>

#include <utility>

#include <balor/io/File.hpp>
#include <balor/system/windows.hpp>
#include <balor/test/UnhandledException.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/scopeExit.hpp>
#include <balor/String.hpp>


namespace balor {
	namespace test {
		namespace testDebug {


using std::move;
using namespace balor::io;


namespace {
const wchar_t testDirectoryName[] = L"testBalor_system_diagnostics_Debug_ekhjiu879u0adfjalj0gjdftdsa";
File getTestDirectory() {
	File dir(File::getSpecial(File::Special::temporary), testDirectoryName);
	if (dir.exists()) {
		dir.remove(true);
	}
	dir.createDirectory();
	return dir;
}


void removeTestDirectory() {
	File(File::getSpecial(File::Special::temporary), testDirectoryName).remove(true);
}


bool raiseExceptionAndCreateDumpFile(const wchar_t* fileName) {
	bool result = false;
	__try {
		RaiseException(0, 0, 0, nullptr);
	} __except(result = Debug::createDumpFile(GetExceptionInformation(), fileName), EXCEPTION_EXECUTE_HANDLER) {
	}
	return result;
}
} // namespace



testCase(startup) { // �n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������i�ꌩ���[�N�Ɍ�����j�֐������炩���ߌĂ�ł���
	balor::test::UnitTest::ignoreHandleLeakCheck();

	scopeExit(&removeTestDirectory);
	File dir = getTestDirectory();
	Debug::createDumpFile(nullptr, File(dir, L"file.dmp")); // MiniDumpWriteDump �֐��͍ŏ��̌Ăяo���ł����n���h���𕡐��J���ĕێ�����
}


//testCase(crashDumpFilePath) { // testCase(enableCrashDumpHandler) �ɂăe�X�g
//}


testCase(createDumpFile) {
	scopeExit(&removeTestDirectory);
	File dir = getTestDirectory();

	{// �f�B���N�g�����݂��炸���s
		File file0(dir, L"not_exist_dir\\file0.dmp");
		testAssert(!Debug::createDumpFile(nullptr, file0.path()));
		testAssert(!file0.exists());
	}
	{// ��O�w�薳���ō쐬
		File file1(dir, L"file1.dmp");
		testAssert(Debug::createDumpFile(nullptr, file1.path()));
		testAssert(file1.exists());
		testAssert(0 < file1.openRead().length());
	}
	{// ��O�w�肠��ō쐬
		File file2(dir, L"file2.dmp");
		testAssert(raiseExceptionAndCreateDumpFile(file2.path()));
		testAssert(file2.exists());
		testAssert(0 < file2.openRead().length());
	}

	// Caution: �_���v�t�@�C����VC�Ő���ɊJ���邱�Ƃ�ڎ��Ŋm�F
}


testCase(enableCrashDumpHandler) {
	scopeExit(&removeTestDirectory);
	File dir = getTestDirectory();

	File file0(dir, L"not_exist_dir\\file0.dmp");
	Debug::enableCrashDumpHandler(file0.path(), false, L"message", L"failedMessage");

	if (IsDebuggerPresent() == 0) { // �f�o�b�K���g������n���h���͋N������Ȃ�
		{// �f�B���N�g�����݂��炸���s
			try {
				throw 0;
			} catch (UnhandledException& ) {
			}
			testAssert(!file0.exists());
		}
		{// �N���b�V���_���v�o�́i�b�{�{��O�j
			File file1(dir, L"file1.dmp");
			Debug::enableCrashDumpHandler(file1.path(), false, L"message", L"failedMessage");
			bool destructed = false;
			try {
				scopeExit([&] () {
					destructed = true;
				});
				throw 0;
			} catch (UnhandledException& ) {
			}
			testAssert(file1.exists());
			testAssert(0 < file1.openRead().length());
			testAssert(destructed);
		}
		{// �N���b�V���_���v�o�́i�\������O�j
			File file2(dir, L"file2.dmp");
			Debug::enableCrashDumpHandler(file2.path(), false, L"message", L"failedMessage");
			bool destructed = false;
			try {
				scopeExit([&] () {
					destructed = true;
				});
				RaiseException(0, 0, 0, nullptr);
			} catch (UnhandledException& ) {
			}
			testAssert(file2.exists());
			testAssert(0 < file2.openRead().length());
			testAssert(destructed);
		}
	} else { // �e�X�g�����͍��킹��
		testAssert(true);
		testAssert(true);
		testAssert(true);
		testAssert(true);
		testAssert(true);
		testAssert(true);
		testAssert(true);
	}

	Debug::enableCrashDumpHandler();

	// Caution: ���b�Z�[�W�{�b�N�X���\�������p�^�[���Ő����^���s���b�Z�[�W��ڎ��Ŋm�F
}


testCase(enableMemoryLeakCheck) {
	testNoThrow(Debug::enableMemoryLeakCheck());

	// Caution: ���ۂɃ��[�N���񍐂���邩�ۂ��ڎ��Ŋm�F
}


testCase(stackTrace) {
	String stackTrace = Debug::stackTrace();
	testAssert(0 < stackTrace.length());
	testAssert(stackTrace.startsWith(L"testBalor!balor::test::testDebug::stackTrace"));
	testAssert(stackTrace.contains(L"testBalor!balor::test::UnitTest::run"));
}


testCase(write) {
	testNoThrow(Debug::write(""));
	testNoThrow(Debug::write("test Debug::write"));
	testNoThrow(Debug::write(L""));
	testNoThrow(Debug::write(L"test Debug::write"));

	// Caution: ���ۂɃf�o�b�O�o�͂���邩�ۂ��ڎ��Ŋm�F
}


testCase(writeLine) {
	testNoThrow(Debug::writeLine(""));
	testNoThrow(Debug::writeLine("test Debug::writeLine"));
	testNoThrow(Debug::writeLine(L""));
	testNoThrow(Debug::writeLine(L"test Debug::writeLine"));

	// Caution: ���ۂɃf�o�b�O�o�͂���邩�ۂ��ڎ��Ŋm�F
}



		}
	}
}