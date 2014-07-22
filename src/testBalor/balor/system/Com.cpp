#include <balor/system/Com.hpp>

#include <boost/thread.hpp>
#include <MLang.h>

#include <balor/gui/Frame.hpp>
#include <balor/system/ComBase.hpp>
#include <balor/system/ComPtr.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/test/verify.hpp>


namespace balor {
	namespace system {
		namespace testCom {

using boost::thread;
using namespace balor::gui;


namespace {
bool comCheck() {
	IMultiLanguage2* ptr;
	auto result = CoCreateInstance(CLSID_CMultiLanguage, nullptr, CLSCTX_ALL, __uuidof(IMultiLanguage2), reinterpret_cast<void**>(&ptr));
	if (result == CO_E_NOTINITIALIZED) {
		return false;
	}
	assert(SUCCEEDED(result));
	verify(SUCCEEDED(ptr->Release()));
	return true;
}

struct DropTarget : public IDropTarget {
	DropTarget() : count(1) {}
	virtual ~DropTarget() {}
	virtual ULONG STDMETHODCALLTYPE AddRef() { return ++count; }
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID id, void** ptr) {
		if (IsEqualIID(id, IID_IUnknown) || IsEqualIID(id, __uuidof(IDropTarget))) {
			*ptr = this;
			AddRef();
			return S_OK;
		} else {
			*ptr = NULL;
			return E_NOINTERFACE;
		}
	}
	virtual ULONG STDMETHODCALLTYPE Release() { return --count; }
	virtual HRESULT STDMETHODCALLTYPE DragEnter(IDataObject* , DWORD , POINTL , DWORD* ) { return S_OK; }
	virtual HRESULT STDMETHODCALLTYPE DragOver(DWORD , POINTL , DWORD* ) { return S_OK; }
	virtual HRESULT STDMETHODCALLTYPE DragLeave() { return S_OK; }
	virtual HRESULT STDMETHODCALLTYPE Drop(IDataObject* , DWORD , POINTL , DWORD* ) { return S_OK; }
	long count;
};

bool oleCheck() {
	DropTarget target;
	Frame frame(L"");
	auto result = RegisterDragDrop(frame, &target);
	if (result == CO_E_NOTINITIALIZED || result == E_OUTOFMEMORY) {
		return false;
	}
	assert(SUCCEEDED(result));
	verify(SUCCEEDED(RevokeDragDrop(frame)));
	return true;
}
} // namespace



testCase(startup) { // �n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������i�ꌩ���[�N�Ɍ�����j�֐������炩���ߌĂ�ł���
	test::UnitTest::ignoreHandleLeakCheck();
	Com::initialize();
	testAssert(comCheck()); // �������ς�

	Com::oleInitialize();
	testAssert(oleCheck()); // �������ς�
	Com::oleUninitialize();

	Com::uninitialize();
}


testCase(initializeAndInitializedAndUninitialize) {
	// STA �ŏ�����
	testAssert(!Com::initialized());
	testAssert(!comCheck()); // ��������
	testNoThrow(Com::initialize());
	testAssert(Com::initialized());
	testAssert(comCheck()); // �������ς�

	// MTA �ւ̕ύX�s��
	testAssertionFailed(Com::initialize(false));

	{// ���X���b�h�͖����������
		thread work([&] () {
			// initialized �Ăяo���s��
			testAssertionFailed(Com::initialized());
			testAssert(!comCheck()); // ��������

			// STA �ŏ�����
			testNoThrow(Com::initialize());
			testAssert(comCheck()); // �������ς�
			testNoThrow(Com::initialize());
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(!comCheck()); // ��������

			// MTA �ŏ�����
			testNoThrow(Com::initialize(false));
			testAssert(comCheck()); // �������ς�
			testNoThrow(Com::initialize(false));
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(!comCheck()); // ��������

		});
		work.join();
		testAssert(Com::initialized());
		testAssert(comCheck()); // �������ς�
	}

	// �������̏d��
	testNoThrow(Com::initialize());
	testAssert(Com::initialized());
	testAssert(comCheck()); // �������ς�

	// �i�K�I�ȏI������
	Com::uninitialize();
	testAssert(Com::initialized());
	testAssert(comCheck()); // �������ς�
	Com::uninitialize();
	testAssert(!Com::initialized());
	testAssert(!comCheck()); // ��������


	// MTA �ŏ�����
	testAssert(!Com::initialized());
	testAssert(!comCheck()); // ��������
	testNoThrow(Com::initialize(false));
	testAssert(Com::initialized());
	testAssert(comCheck()); // �������ς�

	// STA �ւ̕ύX�s��
	testAssertionFailed(Com::initialize(true));

	{// ���X���b�h�� MTA ���������
		thread work([&] () {
			// initialized �Ăяo���s��
			testAssertionFailed(Com::initialized());
			testAssert(comCheck()); // �������ς�

			// STA �ŏ�����
			testNoThrow(Com::initialize());
			testAssert(comCheck()); // �������ς�
			testNoThrow(Com::initialize());
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(comCheck()); // �������ς�

			// MTA �ŏ�����
			testNoThrow(Com::initialize(false));
			testAssert(comCheck()); // �������ς�
			testNoThrow(Com::initialize(false));
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(comCheck()); // �������ς�

		});
		work.join();
		testAssert(Com::initialized());
		testAssert(comCheck()); // �������ς�
	}

	// �������̏d��
	testNoThrow(Com::initialize(false));
	testAssert(Com::initialized());
	testAssert(comCheck()); // �������ς�

	// �i�K�I�ȏI������
	Com::uninitialize();
	testAssert(Com::initialized());
	testAssert(comCheck()); // �������ς�
	Com::uninitialize();
	testAssert(!Com::initialized());
	testAssert(!comCheck()); // ��������


	//// OLE �ŏ����ς�
	//testNoThrow(Com::oleInitialize());
	//testAssert(Com::initialized());
	//testAssert(comCheck()); // �������ς�

	//// �������̏d��
	//testNoThrow(Com::initialize());
	//testAssert(Com::initialized());
	//testAssert(comCheck()); // �������ς�

	//// �i�K�I�ȏI������
	//Com::uninitialize();
	//testAssert(Com::initialized());
	//testAssert(comCheck()); // �������ς�
	//Com::oleUninitialize();
	//testAssert(!Com::initialized());
	//testAssert(!comCheck()); // ��������



	{// ����������Ԃő��X���b�h
		thread work([&] () {
			// initialized �Ăяo���s��
			testAssertionFailed(Com::initialized());
			testAssert(!comCheck()); // ��������

			// STA �ŏ�����
			testNoThrow(Com::initialize());
			testAssert(comCheck()); // �������ς�
			testNoThrow(Com::initialize());
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(!comCheck()); // ��������

			// MTA �ŏ�����
			testNoThrow(Com::initialize(false));
			testAssert(comCheck()); // �������ς�
			testNoThrow(Com::initialize(false));
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(comCheck()); // �������ς�
			Com::uninitialize();
			testAssert(!comCheck()); // ��������

		});
		work.join();
		testAssert(!Com::initialized());
		testAssert(!comCheck()); // ��������
	}
}


testCase(isMainThread) {
	testAssert(Com::isMainThread());
	thread work([&] () {
		testAssert(!Com::isMainThread());
	});
	work.join();
}


testCase(oleInitializeAndOleInitializedAndOleUninitialize) {
	// COM STA ��������Ԃ���
	testNoThrow(Com::initialize());
	testAssert(!Com::oleInitialized());
	//testAssert(!oleCheck()); // �������� ����x�ł� OLE ������������Ƃ��Ƃ� COM ������������Ă��邩�ǂ��������Ŕ��f�����悤��
	testNoThrow(Com::oleInitialize());
	testAssert(Com::oleInitialized());
	testAssert(oleCheck()); // �������ς�

	// �i�K�I�ȏI������
	Com::oleUninitialize();
	testAssert(!Com::oleInitialized());
	//testAssert(!oleCheck()); // ��������
	testAssert(comCheck()); // COM �������ς�
	Com::uninitialize();
	testAssert(!Com::initialized());
	testAssert(!oleCheck()); // ��������
	testAssert(!comCheck()); // COM ��������


	// COM MTA ��������Ԃ���
	testNoThrow(Com::initialize(false));
	testAssert(!Com::oleInitialized());
	//testAssert(!oleCheck()); // ��������
	testAssertionFailed(Com::oleInitialize()); // MTA ����͏������ł��Ȃ�
	testAssert(!Com::oleInitialized());
	//testAssert(!oleCheck()); // ��������
	Com::uninitialize();
	testAssert(!oleCheck()); // ��������


	// COM ����������Ԃ���
	testAssert(!Com::oleInitialized());
	testAssert(!oleCheck()); // ��������
	testNoThrow(Com::oleInitialize());
	testAssert(Com::oleInitialized());
	testAssert(oleCheck()); // �������ς�

	// MTA �ւ̕ύX�s��
	testAssertionFailed(Com::initialize(false));

	{// ���X���b�h�͖����������
		thread work([&] () {
			// initialized �Ăяo���s��
			testAssertionFailed(Com::oleInitialized());
			testAssert(!oleCheck()); // ��������

			// OLE ������
			testNoThrow(Com::oleInitialize());
			testAssert(oleCheck()); // �������ς�
			testNoThrow(Com::oleInitialize());
			testAssert(oleCheck()); // �������ς�
			Com::oleUninitialize();
			testAssert(oleCheck()); // �������ς�
			Com::oleUninitialize();
			testAssert(!oleCheck()); // ��������
		});
		work.join();
		testAssert(Com::oleInitialized());
		testAssert(oleCheck()); // �������ς�
	}

	// �������̏d��
	testNoThrow(Com::oleInitialize());
	testAssert(Com::oleInitialized());
	testAssert(oleCheck()); // �������ς�

	// �i�K�I�ȏI������
	Com::oleUninitialize();
	testAssert(Com::oleInitialized());
	testAssert(oleCheck()); // �������ς�
	Com::oleUninitialize();
	testAssert(!Com::oleInitialized());
	testAssert(!oleCheck()); // ��������
}



		}
	}
}