#include <balor/system/Module.hpp>

#include <utility>
#include <balor/system/testModule.hpp> // testBalorDll

#include <balor/io/File.hpp>
#include <balor/test/HandleLeakChecker.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/String.hpp>


namespace balor {
	namespace system {
		namespace testModule {


using std::move;


testCase(construct) {
	// �����ȃp�����[�^
	testAssertionFailed(Module(L""));

	{// �f�t�H���g�R���X�g���N�g
		Module module;
		testAssert(!module);
	}

	{// ������Ȃ��t�@�C����
		Module module(L"balor_utility_testModule_390afjldagad09udfalohnfad.dll");
		testAssert(!module);
	}

	{// DLL�̃��[�h�ƃ��[�h����DLL�ւ̃A�N�Z�X�e�X�g
		Module module(L"testBalorDll.dll");
		testAssert(module);

		{// �֐��̎擾�ƌĂяo��
			auto function0 = module.getFunction<decltype(return100)>("return100");
			testAssert(function0 != nullptr);
			testAssert((*function0)() == 100);
			auto function1 = module.getFunction<decltype(return255)>("return255");
			testAssert(function1 != nullptr);
			testAssert((*function1)() == 255);
			auto function2 = module.getFunction<decltype(return255)>("return256");
			testAssert(function2 == nullptr);
		}
		{// find
			Module finded = Module::find(L"testBalorDll.dll");
			testAssert(finded);
			testAssert(finded.file() == module.file());
		}
		{// find �t���p�X��
			Module finded = Module::find(module.file());
			testAssert(finded);
			testAssert(finded.file() == module.file());
		}
		{// move
			Module moved = move(module);
			testAssert(moved);
			testAssert(!module);

			module = move(moved);
			testAssert(!moved);
			testAssert(module);
		}
	}

	{// �A�����[�h���ꂽDLL�̌���
		Module module = Module::find(L"testBalorDll.dll");
		testAssert(!module);
	}
}


//testCase(find) { // testCase(construct)�ɂăe�X�g�ς�
//}


testCase(getFunction) {
	// �����ȃp�����[�^
	testAssertionFailed(Module().getFunction<void*>("function"));

	// ���̑��̃P�[�X��testCase(construct)�ɂăe�X�g�ς�
}


testCase(path) {
	// ���̑��̃P�[�X��testCase(construct)�ɂăe�X�g�ς�
}



		}
	}
}