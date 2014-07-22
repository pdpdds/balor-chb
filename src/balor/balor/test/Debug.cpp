#include "Debug.hpp"

#include <ctime>
#define BOOST_DATE_TIME_NO_LIB
#define BOOST_THREAD_NO_LIB
#include <boost/thread/mutex.hpp>

#include <balor/io/File.hpp>
#include <balor/locale/Charset.hpp>
#include <balor/system/FileVersionInfo.hpp>
#include <balor/system/Module.hpp>
#include <balor/system/windows.hpp>
#include <balor/test/UnhandledException.hpp>
#include <balor/test/verify.hpp>
#include <balor/scopeExit.hpp>
#include <balor/Singleton.hpp>
#include <balor/String.hpp>
#include <balor/StringBuffer.hpp>

#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")
#include <tlhelp32.h>


namespace balor {
	namespace test {


using std::move;
using boost::mutex;
using namespace balor::io;
using namespace balor::locale;
using namespace balor::system;


namespace {
class Global {
	friend Singleton<Global>;

	Global() {
		filePath[0] = L'\0';
		message[0] = L'\0';
		failedMessage[0] = L'\0';
		showMessageBox = false;
	}
	~Global() {
	}

public:
	wchar_t filePath[MAX_PATH];
	wchar_t message[384];
	wchar_t failedMessage[128];
	bool showMessageBox;
	Listener<ByteStringRange> onWrite;
};


bool createMiniDump(StringRange filePath, EXCEPTION_POINTERS* exceptions) { // ��O�������Ȃ̂Ń��C���^�C�����C�u�����͋ɗ͌Ă΂Ȃ��悤��
	HANDLE file = CreateFileW(filePath.c_str(), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (file != INVALID_HANDLE_VALUE) {
		MINIDUMP_EXCEPTION_INFORMATION info;
		if (exceptions) {
			info.ExceptionPointers = exceptions;
			info.ThreadId = GetCurrentThreadId();
			info.ClientPointers = TRUE;
		}

		// ���̊֐��̓X���b�h�Z�[�t�ł͂Ȃ��̂Ŗ{���̓��b�N���������ً}���ɗ]�v�ȏ����͂ł��邾���������Ȃ�
		BOOL result = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), file
			, static_cast<MINIDUMP_TYPE>(MiniDumpWithDataSegs | MiniDumpWithHandleData | MiniDumpWithIndirectlyReferencedMemory)
			, exceptions ? &info : nullptr
			, 0, 0);

		BOOL result2 = CloseHandle(file);

		if (result && result2) {
			return true;
		}
	}
	return false;
}


LONG WINAPI createMiniDumpExceptionHandler(EXCEPTION_POINTERS* exceptions) { // ��O�������Ȃ̂Ń��C���^�C�����C�u�����͋ɗ͌Ă΂Ȃ��悤��
	__try {
		//if (exceptions != nullptr
		// && exceptions->ExceptionRecord != nullptr
		// && exceptions->ExceptionRecord->ExceptionCode == EXCEPTION_STACK_OVERFLOW) {
		//	// �X�^�b�N�I�[�o�[�t���[�������̓_���v���������܂��������ǂ����킩��Ȃ��̂Ńf�o�b�O�o�͂ł����Ă������f�o�b�K�g���Ă�Ƃ��͂����ɗ��Ȃ��������ς肢��Ȃ�
		//	OutputDebugStringA("EXCEPTION_STACK_OVERFLOW occurred\n");
		//}

		// setCrashDumpHandler���Ă΂�Ȃ���΂����ɂ͗��Ȃ��̂�Singleton<Global>�͂����ł̓q�[�v���蓖�Ă͍s��Ȃ�
		Global& global = Singleton<Global>::get();

		bool dumpCreated = false;
		if (global.filePath[0] != L'\0') {
			dumpCreated = createMiniDump(global.filePath, exceptions);
		}

		if (global.showMessageBox) {
			MessageBoxExW(nullptr, dumpCreated ? global.message : global.failedMessage
				, L"Error", MB_OK | MB_TASKMODAL, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT));
		}
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		// �_���v�o�͏������̍\������O�͈���ׂ�
	}

	if (exceptions
	 && exceptions->ExceptionRecord
	 && exceptions->ExceptionRecord->ExceptionCode == 0xE06D7363) {
		 // ���������̂� C++ ��O�ł���Ȃ�� UnhandledException �� throw ���A�L���b�`���邱�ƂŃf�X�g���N�^���Ăяo����
		 // ����  C++ ��O���L���b�`���Ȃ��ꍇ�A�f�X�g���N�^�͌Ă΂�邱�Ƃ�����
		 throw UnhandledException();
	}

	return EXCEPTION_CONTINUE_SEARCH; // ��������w�肷��ƃf�o�b�O���邩�ǂ����I���ł���
	//return EXCEPTION_EXECUTE_HANDLER;
}
} // namespace



bool Debug::createDumpFile(EXCEPTION_POINTERS* exceptions, StringRange filePath, bool showMessageBox, StringRange message, StringRange failedMessage) {
	if (filePath.empty()) {
		filePath = Singleton<Global>::get().filePath;
		assert(!filePath.empty());
	}
	bool result = false;
	if (exceptions) {
		result = createMiniDump(filePath, exceptions);
	} else {
		__try {
			RaiseException(0, 0, 0, nullptr);
		} __except(result = createMiniDump(filePath, GetExceptionInformation()), EXCEPTION_EXECUTE_HANDLER) {
		}
	}
	if (showMessageBox) {
		if (message.empty()) {
			message = Singleton<Global>::get().message;
		}
		if (failedMessage.empty()) {
			failedMessage = Singleton<Global>::get().failedMessage;
		}
		MessageBoxExW(nullptr, result ? message.c_str() : failedMessage.c_str()
			, L"Error", MB_OK | MB_TASKMODAL, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT));
	}
	return result;
}


void Debug::debugBreak() {
	DebugBreak();
}


void Debug::enableCrashDumpHandler(StringRange crashDumpFilePath, bool showMessageBox, StringRange message, StringRange failedMessage) {
	Global& global = Singleton<Global>::get();

	if (crashDumpFilePath.empty()) {
		StringBuffer buffer(global.filePath);
		buffer += String::refer(Module::current().file());

		{// �t�@�C���o�[�W����������̎擾
			FileVersionInfo info(buffer);
			if (info) {
				auto fileVersion = info.fileVersion();
				buffer += L"_";
				buffer += fileVersion.major();
				buffer += L".";
				buffer += fileVersion.minor();
				buffer += L".";
				buffer += fileVersion.build();
				buffer += L".";
				buffer += fileVersion.revision();
			}
		}

		{// ���t������̍쐬
			wchar_t date[64];
			date[0] = 0;
			time_t global;
			time(&global);

			tm local;
			if (!localtime_s(&local, &global)) {
				wcsftime(date, sizeof(date) / sizeof(date[0]), L"_%Y%m%d_%H%M%S", &local);
			}
			buffer += date;
		}

		buffer += L".dmp";
	} else {
		String::refer(crashDumpFilePath).copyTo(global.filePath);
	}

	if (message.empty()) {
		StringBuffer buffer(global.message);
		buffer += L"Application crashed!\n\nOutput dumpfile at ";
		buffer += global.filePath;
	} else {
		String::refer(message).copyTo(global.message);
	}

	if (failedMessage.empty()) {
		String::literal(L"Application crashed!\n\nFaild to create dumpfile.").copyTo(global.failedMessage);
	} else {
		String::refer(failedMessage).copyTo(global.failedMessage);
	}

	global.showMessageBox = showMessageBox;

	SetUnhandledExceptionFilter(createMiniDumpExceptionHandler);
}


void Debug::enableMemoryLeakCheck() {
#if defined(_DEBUG)

	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif
}


bool Debug::isDebuggerPresent() {
	return IsDebuggerPresent() != FALSE;
}


Listener<ByteStringRange>& Debug::onWrite() {
	return Singleton<Global>::get().onWrite;
}


#pragma warning(push)
#pragma warning(disable : 4740) // �C�����C�� asm �R�[�h�̓����܂��͊O���̃t���[�́A�O���[�o���ȍœK����}�����܂�
#pragma warning(disable : 4748) // /GS �֐��ł̍œK���������ɂ���Ă��邽�߁A�p�����[�^�[����у��[�J���ϐ������[�J���̃o�b�t�@�[ �I�[�o�[��������ی�ł��܂���B
String Debug::stackTrace() {
	struct StackTraceMutex {
		mutex mutex;
	};
	mutex::scoped_lock lock(Singleton<StackTraceMutex>::get().mutex); // Dbghelp���C�u�����̊֐��̓X���b�h�Z�[�t�ł͂Ȃ��̂Ń��b�N����

	// �Q�lURL http://wiki.encom.bz/index.php/%E3%82%B9%E3%82%BF%E3%83%83%E3%82%AF%E3%83%88%E3%83%AC%E3%83%BC%E3%82%B9%E3%82%92%E8%A1%A8%E7%A4%BA%E3%81%99%E3%82%8B
	// �V���{���n���h���̏�����
	const HANDLE process = GetCurrentProcess();
	verify(SymInitialize(process, nullptr, TRUE));
	scopeExit([&] () {
		verify(SymCleanup(process));
	});

	{// ���W���[���̓ǂݍ���
		const DWORD processId = GetCurrentProcessId();
		const HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);
		assert(snapshot != INVALID_HANDLE_VALUE);
		scopeExit([&] () {
			verify(CloseHandle(snapshot));
		});

		MODULEENTRY32W entry;
		ZeroMemory(&entry, sizeof(entry));
		entry.dwSize = sizeof(entry);

		if (Module32FirstW(snapshot, &entry)) {
			do {
				// pdb�t�@�C����������Ȃ���Ύ��s���邱�Ƃ͕��ʂɂ���̂ŃG���[�`�F�b�N���Ȃ��Ƃ��ǂ�
				SymLoadModuleExW(process, nullptr, entry.szExePath, entry.szModule, reinterpret_cast<DWORD64>(entry.modBaseAddr), entry.modBaseSize, nullptr, 0);
			} while (Module32NextW(snapshot, &entry));
		}
	}

    // ���X���b�h�̃R���e�L�X�g�̎擾
	const HANDLE thread = GetCurrentThread();
	CONTEXT context;
	ZeroMemory(&context, sizeof(context));
	context.ContextFlags = CONTEXT_FULL;

#if defined(_M_IX86)
	__asm    call(x);
	__asm x: pop eax;
	__asm    mov context.Eip, eax;
	__asm    mov context.Ebp, ebp;
	__asm    mov context.Esp, esp;
#else // for Windows 64-bit editions
	RtlCaptureContext(&context);
#endif


	// �X�^�b�N�t���[���\���̂̏�����
	STACKFRAME64 stackFrame;
	ZeroMemory(&stackFrame, sizeof(stackFrame));
#if defined(_M_IX86)
	stackFrame.AddrPC.Offset    = context.Eip;
	stackFrame.AddrPC.Mode      = AddrModeFlat;
	stackFrame.AddrFrame.Offset = context.Ebp;
	stackFrame.AddrFrame.Mode   = AddrModeFlat;
	stackFrame.AddrStack.Offset = context.Esp;
	stackFrame.AddrStack.Mode   = AddrModeFlat;
	DWORD machineType = IMAGE_FILE_MACHINE_I386;
#elif defined(_M_AMD64)
	stackFrame.AddrPC.Offset    = context.Rip;
	stackFrame.AddrPC.Mode      = AddrModeFlat;
	stackFrame.AddrFrame.Offset = context.Rbp;
	stackFrame.AddrFrame.Mode   = AddrModeFlat;
	stackFrame.AddrStack.Offset = context.Rsp;
	stackFrame.AddrStack.Mode   = AddrModeFlat;
	DWORD machineType = IMAGE_FILE_MACHINE_AMD64;
#elif defined(_M_IA64)
	stackFrame.AddrPC.Offset     = context.StIIP;
	stackFrame.AddrPC.Mode       = AddrModeFlat;
	stackFrame.AddrStack.Offset  = context.IntSp;
	stackFrame.AddrStack.Mode    = AddrModeFlat;
	stackFrame.AddrBStore.Offset = context.RsBSP;
	stackFrame.AddrBStore.Mode   = AddrModeFlat;
	DWORD machineType = IMAGE_FILE_MACHINE_IA64;
#else
#error "Not Supported."
#endif


	// �X�^�b�N�g���[�X�̍쐬
	if (!StackWalk64(machineType, process, thread, &stackFrame, &context, nullptr, nullptr, nullptr, nullptr)) { // ���̊֐��istackTrace�j�̃X�^�b�N�����΂�
		return String();
	}
	StringBuffer result(512);
	for (;;) {
		if (!StackWalk64(machineType, process, thread, &stackFrame, &context, nullptr, nullptr, nullptr, nullptr)) {
			break;
		}

		if ((stackFrame.AddrPC.Offset == stackFrame.AddrReturn.Offset) // �G���h���X�ɂȂ�̂ŏI��
		 || (stackFrame.AddrPC.Offset == 0)) { // �s���ȃX�^�b�N�t���[��
			break;
		}

		{// ���W���[�����̎擾
			IMAGEHLP_MODULEW64 module;
			ZeroMemory(&module, sizeof(module));
			module.SizeOfStruct = sizeof(module);
			if (SymGetModuleInfoW64(process, stackFrame.AddrPC.Offset, &module)) {
				result += module.ModuleName;
				result += L"!";
			}
		}

		// �֐����̎擾
		BYTE buffer[sizeof(SYMBOL_INFOW) + sizeof(wchar_t) * MAX_SYM_NAME];
		ZeroMemory(buffer, sizeof(buffer));
		SYMBOL_INFOW* symbol = reinterpret_cast<SYMBOL_INFOW*>(buffer);
		symbol->SizeOfStruct = sizeof(SYMBOL_INFOW);
		symbol->MaxNameLen = MAX_SYM_NAME;
		DWORD64 displacement = 0;
		if (SymFromAddrW(process, stackFrame.AddrPC.Offset, &displacement, symbol)) {
			result += symbol->Name;

			DWORD displacement = 0;
			IMAGEHLP_LINEW64 line;
			ZeroMemory(&line, sizeof(line));
			line.SizeOfStruct = sizeof(line);
			if (SymGetLineFromAddrW64(process, stackFrame.AddrReturn.Offset, &displacement, &line)) {
				result += L" at ";
				result += line.FileName;
				result += L"(";
				result += line.LineNumber;
				result += L")";
			}
		} else {
			result += L"<nosymbols>";
		}

		result += L"\n";

		if (stackFrame.AddrReturn.Offset == 0) { // �Ō�̃X�^�b�N�t���[��
			break;
		}
	}

	return result;
}
#pragma warning(pop)


void Debug::write(ByteStringRange message) {
	OutputDebugStringA(message.c_str());
	Global& global = Singleton<Global>::get();
	if (global.onWrite) {
		global.onWrite(message);
	}
}


void Debug::write(StringRange message) {
	OutputDebugStringW(message.c_str());
	Global& global = Singleton<Global>::get();
	if (global.onWrite) {
		global.onWrite(Charset::default().encode(message));
	}
}


void Debug::writeLine(ByteStringRange message) {
	write(message);
	write("\n");
}


void Debug::writeLine(StringRange message) {
	write(message);
	write(L"\n");
}



	}
}