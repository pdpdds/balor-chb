#include <balor/Singleton.hpp>

#include <balor/testSingleton.hpp> // testBalorDll

#include <balor/io/File.hpp>
#include <balor/system/Module.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/String.hpp>


namespace balor {
	namespace testSingleton {


using namespace balor::io;
using namespace balor::system;


testCase(get) {
	// singleton dll�̑��݊m�F
	testAssert(File::exists(String::refer(Module::current().directory()) + L"\\balor_singleton.dll"));

	// ���c�O�Ȃ��� balor_singleton.dll �����̃P�[�X�̓e�X�g�ł��Ă��Ȃ��B�����̃v���Z�X���K�v���낤�B�ڎ��ł͊m�F�ς݁B

	
	int& exeInt = Singleton<int>::get();
	exeInt = 5;
	short& exeShort = Singleton<short>::get();
	exeShort = 6;
	testAssert(Singleton<int>::get() == 5);
	testAssert(Singleton<short>::get() == 6);

	Module module(L"testBalorDll.dll");
	auto getDllInt = module.getFunction<decltype(getSingletonInt)>("getSingletonInt");
	auto getDllShort = module.getFunction<decltype(getSingletonShort)>("getSingletonShort");

	int& dllInt = (*getDllInt)();
	short& dllShort = (*getDllShort)();
	testAssert(&exeInt == &dllInt);
	testAssert(&exeShort == &dllShort);
	testAssert(dllInt == 5);
	testAssert(dllShort == 6);
}



	}
}