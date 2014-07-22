#include "Singleton.hpp"

#include <typeinfo>
#define BOOST_DATE_TIME_NO_LIB
#define BOOST_THREAD_NO_LIB
#include <boost/thread/recursive_mutex.hpp>

#include <balor/system/Module.hpp>
#include <balor/test/verify.hpp>
#include <../balor_singleton/balor/singleton/getSingletonInstance.hpp>


namespace balor {
	namespace detail {


using boost::recursive_mutex;
using namespace balor::system;


namespace {
class BalorSingletonModule {
public:
	BalorSingletonModule() : module(L"balor_singleton.dll") {
		if (module) {
			function = module.getFunction<decltype(balor::singleton::getSingletonInstance)>("getSingletonInstance");
			assert(function);
		}
	}

	bool empty() const { return !module; }
	void* getSingletonInstance(const std::type_info& info, void* (*createInstanceFunction)()) {
		return (*function)(info, createInstanceFunction);
	}

	Module module;
	decltype(balor::singleton::getSingletonInstance)* function;
};


recursive_mutex& getSingletonMutex() { // mutex ���O���[�o���ϐ�����������������g����悤�Ɋ֐�����擾����悤�ɂ��Ă���
	static recursive_mutex singletonMutex; // ���̃C���X�^���X�� DLL ���Ƃɍ쐬�����B�����������̒��ł���ɑ��̌^�� Singleton ���쐬�ł���悤�� recursive_mutex �ɂ��Ă����B
	return singletonMutex;
}


recursive_mutex& singletonMutex = getSingletonMutex(); // ���̃O���[�o���ϐ��Ń}���`�X���b�h�ŃA�N�Z�X�������� mutex �̏��������ۏ؂����B�i�O���[�o���ϐ��̏����������Ń}���`�X���b�h�ɂȂ�����͂��܂��j
} // namespace



void* getSingletonInstance(const type_info& info, void* (*createInstanceFunction)()) {
	recursive_mutex::scoped_lock lock(getSingletonMutex()); // mutex �̃C���X�^���X�� DLL ���Ƃɍ쐬�����̂ŗB��ł͂Ȃ� DLL ���ƂɃ��b�N����Ă��܂��B
	static BalorSingletonModule module; // ���̃C���X�^���X�� DLL ���Ƃɍ쐬�����̂� DLL ���Ƃ̃��b�N�Ŗ��Ȃ��BLoadLibrary �͒P�� DLL ���ƂɃJ�E���^�𑝂₷�����B
	if (module.empty()) {
		return (*createInstanceFunction)(); // balor_singletone.dll �������ꍇ�� DLL ���g��Ȃ��Ƃ݂Ȃ��B����ă��b�N�͗B��ł���A���̊֐��𒴂��ă������œK���͋N���Ȃ��̂ŌĂяo�����Ń������o���A�͕K�v�Ȃ��B
	} else {
		return module.getSingletonInstance(info, createInstanceFunction); // ���̊֐������͌Ăяo����� DLL ���ł��炽�߂ă��b�N�����B
	}
}



	}
}