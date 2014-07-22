#pragma once

#include <balor/test/noMacroAssert.hpp>
#include <balor/Exception.hpp>

struct _GUID;
struct IUnknown;

namespace balor {
	namespace system {



namespace detail {
	void coCreateInstance(const ::_GUID& rclsid, ::IUnknown* unknown, const ::_GUID& riid, void** pointer);
	void coCreateInstance(const ::_GUID& rclsid, ::IUnknown* unknown, const ::_GUID& riid, void** pointer, unsigned long context);
	void queryInterface(::IUnknown* from, const ::_GUID& riid, void** pointer);
}


/**
 * COM �C���^�[�t�F�[�X�̍쐬�A�J���̎x��������X�}�[�g�|�C���^�[�B
 */
#pragma warning (push)
#pragma warning (disable : 4189) //  'result' : ���[�J���ϐ�������������܂������A�Q�Ƃ���Ă��܂���
template<typename T>
class ComPtr {
public:
	/// �k���|�C���^�ŏ������B
	ComPtr() : _ptr(nullptr) {}
	ComPtr(const ComPtr& value) : _ptr(value._ptr) {
		_ptr->AddRef();
	}
	/// REFCLSID ���� COM �C���^�[�t�F�[�X���쐬�B
	/// COM �����������łȂ������C���X���b�h�ł���� Com::Initialize(true) �ŏ����������݂�B���C���X���b�h�łȂ���� Com::UninitializedException �𓊂���B
	/// COM �C���^�[�t�F�[�X�����o�^�܂��͖������̏ꍇ�� Com::InterfaceNotFoundException �𓊂���B
	explicit ComPtr(const ::_GUID& rclsid, ::IUnknown* unknown = nullptr) : _ptr(nullptr) {
		::balor::system::detail::coCreateInstance(rclsid, unknown, __uuidof(T), reinterpret_cast<void**>(&_ptr));
	}
	ComPtr(const ::_GUID& rclsid, ::IUnknown* unknown, unsigned long context) : _ptr(nullptr) {
		::balor::system::detail::coCreateInstance(rclsid, unknown, __uuidof(T), reinterpret_cast<void**>(&_ptr), context);
	}

	ComPtr(ComPtr&& value) : _ptr(value._ptr) {
		value._ptr = nullptr;
	}
	~ComPtr() {
		if (_ptr) {
			_ptr->Release();
			//_ptr = nullptr;
		}
	}

	ComPtr& operator=(ComPtr&& value) {
		if (&_ptr != &value._ptr) {
			auto backup = _ptr;
			_ptr = value._ptr;
			value._ptr = backup;
		}
		return *this;
	}
	ComPtr& operator=(const ComPtr& value) {
		if (this != &value) {
			if (_ptr) {
				_ptr->Release();
			}
			_ptr = value._ptr;
			_ptr->AddRef();
		}
		return *this;
	}

public:
	/// newPtr �̌^�� QueryInterface ���s���B
	/// COM �C���^�[�t�F�[�X�����o�^�܂��͖������̏ꍇ�� Com::InterfaceNotFoundException �𓊂���B
	template<typename T2>
	void queryInterface(ComPtr<T2>& newPtr) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(newPtr == nullptr);
#endif
		::balor::system::detail::queryInterface(*this, __uuidof(T2), reinterpret_cast<void**>(&newPtr));
	}

public:
	/// COM �C���^�[�t�F�[�X�|�C���^�̎擾�B
	operator T*() const { return _ptr; }
	/// COM �C���^�[�t�F�[�X�|�C���^�ւ̃A�h���X�̎擾�BCoCreateInstance �ł̎g�p��z�肵�Ă���̂Ń|�C���^�� nullptr �łȂ���΂Ȃ�Ȃ��B
	T** operator&() {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(_ptr == nullptr);
#endif
		return &_ptr;
	}
	/// COM �C���^�[�t�F�[�X�����o�ւ̃A�N�Z�X�B
	T* operator->() const { return _ptr; }

private:
	T* _ptr;
};
#pragma warning (pop)



	}
}