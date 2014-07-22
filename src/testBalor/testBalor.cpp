#include <functional>

#include <balor/gui/MessageBox.hpp>
#include <balor/io/File.hpp>
#include <balor/io/FileStream.hpp>
#include <balor/system/Console.hpp>
#include <balor/system/Module.hpp>
#include <balor/test/Debug.hpp>
#include <balor/test/UnhandledException.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/String.hpp>

#include <tchar.h>
#include <windows.h>


using namespace balor::io;
using namespace balor::system;
using namespace balor::test;
using namespace balor;


void se_translator_function(unsigned int /*code*/, struct _EXCEPTION_POINTERS* ep)
{
	Debug::createDumpFile(ep);
	throw UnhandledException(); //�W��C++�̗�O�𔭐�������
}


int debugReportHook(int /*reportType*/, char* message, int* /*returnValue*/) {
	// ���������[�N���񍐂���Ă����ɗ���Ƃ��ɂ̓O���[�o���ϐ��͊��Ƀf�X�g���N�g����Ă���\���������̂ŃO���[�o���ϐ��͎g���Ȃ��B
	File(Module::current().directory(), L"testBalorLog.txt").openAppend().write(message, 0, String::getLength(message));
	return FALSE;
}


int APIENTRY _tWinMain(HINSTANCE //instance
					  ,HINSTANCE //prevInstance
					  ,LPTSTR    //commandLine
					  ,int       //showState
					  ) {
	Debug::enableMemoryLeakCheck();
	Debug::enableCrashDumpHandler(L"", false);
	_set_se_translator(&se_translator_function); // �\������O�� C++ ��O�ɕϊ����ăf�X�g���N�^���N������B
	_CrtSetReportHook(debugReportHook); // enableMemoryLeakCheck �̌��ʂ��E����悤�Ƀ��|�[�g�֐����t�b�N����B

	Console::open();

	try {
		auto stream = File(Module::current().directory(), L"testBalorLog.txt").create();
		Debug::onWrite() = [&] (ByteStringRange message) {
			stream.write(message.c_str(), 0, message.length());
			Console::write(message);
		};

		UnitTest::run();
		//UnitTest::run("listener");
	} catch (UnhandledException& ) {
	}

	gui::MsgBox::show(L"�e�X�g�I��");

	return 0;
}
