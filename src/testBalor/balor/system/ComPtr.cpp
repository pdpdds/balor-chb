#include <balor/system/ComPtr.hpp>

#include <utility>
#include <boost/thread.hpp>
#include <MLang.h>

#include <balor/system/Com.hpp>
#include <balor/test/HandleLeakChecker.hpp>
#include <balor/test/UnitTest.hpp>


namespace balor {
	namespace system {
		namespace testComPtr {

using std::move;
using boost::thread;


testCase(construct) {
	balor::test::UnitTest::ignoreHandleLeakCheck(); // CLSID_CMLangConvertCharset �Ƃ����V���� CLSID �ɂ���ăn���h�����蓖�Ă��������Ă���
	{
		ComPtr<IMultiLanguage> ptr;
		testAssert(!ptr);
	}

	{// COM ����������
		testAssert(!Com::initialized());
		testNoThrow(ComPtr<IMultiLanguage2> ptr(CLSID_CMultiLanguage));
		testAssert(Com::initialized());
	}

	{// �񃁃C���X���b�h�� COM ����������
		thread work([&] () {
			testThrow(ComPtr<IMultiLanguage2> ptr(CLSID_CMultiLanguage), Com::UninitializedException);
		});
		work.join();
	}

	{// �N���X���o�^����Ă��Ȃ�
		testThrow(ComPtr<IMultiLanguage2> ptr(CLSID_CMLangConvertCharset), Com::InterfaceNotFoundException);
	}
	{// ����P�[�X
		ComPtr<IMultiLanguage2> ptr(CLSID_CMultiLanguage);
		testAssert(ptr != nullptr);
		MIMECPINFO info;
		testAssert(SUCCEEDED(ptr->GetCodePageInfo(932, GetUserDefaultUILanguage(), &info)));
		testAssert(info.uiCodePage == 932);
	}
}


testCase(copyConstruct) {
	ComPtr<IMultiLanguage2> source(CLSID_CMultiLanguage);
	ComPtr<IMultiLanguage2> ptr = source;
	testAssert(ptr != nullptr);
	testAssert(source == ptr);
}


testCase(rvalueConstruct) {
	ComPtr<IMultiLanguage2> source(CLSID_CMultiLanguage);
	ComPtr<IMultiLanguage2> ptr = move(source);
	testAssert(!source);
	testAssert(ptr != nullptr);
}


//testCase(destruct) { // �n���h���I�ȂȂɂ��Ń��[�N�����o�ł��ʂ��̂��H
//	ComPtr<IMultiLanguage2> ptr(CLSID_CMultiLanguage);
//	testAssert(ptr != nullptr);
//	ptr.~ComPtr<IMultiLanguage2>();
//	testAssert(!ptr);
//}


testCase(assignment) {
	ComPtr<IMultiLanguage2> source(CLSID_CMultiLanguage);
	ComPtr<IMultiLanguage2> ptr;
	ptr = source;
	testAssert(ptr != nullptr);
	testAssert(ptr == source);

	ptr = ptr;
	testAssert(ptr != nullptr);
}


testCase(rvalueAssignment) {
	ComPtr<IMultiLanguage2> source(CLSID_CMultiLanguage);
	ComPtr<IMultiLanguage2> ptr;
	ptr = move(source);
	testAssert(!source);
	testAssert(ptr != nullptr);

	ptr = move(ptr);
	testAssert(ptr != nullptr);
}


testCase(queryInterface) {
	ComPtr<IMultiLanguage> source(CLSID_CMultiLanguage);

	// ������Ȃ�
	ComPtr<IMLangConvertCharset> charset;
	testThrow(source.queryInterface(charset), Com::InterfaceNotFoundException);

	// ����P�[�X
	ComPtr<IMultiLanguage2> ptr;
	source.queryInterface(ptr);
	testAssert(ptr != nullptr);
}


testCase(operators) {
	{// operator T*
		ComPtr<IMultiLanguage2> ptr;
		IMultiLanguage2* rawPtr = ptr;
		testAssert(rawPtr == nullptr);
	}
	{
		ComPtr<IMultiLanguage2> ptr(CLSID_CMultiLanguage);
		IMultiLanguage2* rawPtr = ptr;
		testAssert(rawPtr != nullptr);
	}
	{// oprator&
		ComPtr<IMultiLanguage> source(CLSID_CMultiLanguage);
		ComPtr<IMultiLanguage2> ptr(CLSID_CMultiLanguage);
		testAssertionFailed(&ptr);
		ptr = ComPtr<IMultiLanguage2>();
		testAssert(SUCCEEDED(source->QueryInterface(__uuidof(IMultiLanguage2), reinterpret_cast<void**>(&ptr))));
		testAssert(ptr != nullptr);
	}
	{// operator-> ���Ɏg���Č�����
	}
}


testCase(cleanup) {
	Com::uninitialize();
}



		}
	}
}