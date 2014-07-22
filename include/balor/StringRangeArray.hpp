#pragma once

#include <balor/test/noMacroAssert.hpp>
#include <balor/StringRange.hpp>

namespace std {
	namespace tr1 {
#ifdef  _WIN64
		template<typename T, unsigned __int64> class array;
#else
		template<typename T, __w64 unsigned int> class array;
#endif
	}
	template<typename T> class allocator;
	template<typename T> struct char_traits;
	template<typename T, typename Traits, typename Allocator> class basic_string;
	template<typename T, typename A> class vector;
}

namespace balor {
	namespace io {
class File;
	}
}


namespace balor {

class String;
class StringBuffer;



/**
 * �������� StringRange �̔z��Ɍ�����N���X�B
 * 
 * balor::String �܂��� balor::StringBuffer�Abalor::io::File�Astd::wstring�A������|�C���^��v�f�Ƃ���Œ蒷�z��܂��̓|�C���^�[�Astd::vector�Astd::array �����ʂ̃C���^�[�t�F�[�X�ň�����悤�ɂ���B
 * ���܂�����I�ł͂Ȃ��̂ŋ���z��Ȃ畉�ׂɒ��ӂ���B
 * ������Ɣz��܂��̃J�I�X���ɍ��������ɂȂ邪�ł��邾���P�������Ă��������B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	String s(L"abc");

	// String::split �� StringRangeArray �������Ɏ��̂� ������|�C���^�AString�Awstring ���̌Œ蒷�z��Avector ����n�����Ƃ��ł���B
	const wchar_t* pointers[] = {L"abc", L"def"};
	s.split(pointers);

	std::vector<String> strings;
	strings.push_back(L"abc");
	strings.push_back(L"def");
	s.split(strings);

	std::wstring wstrings[] = {L"abc", L"def"};
	s.split(wstrings);
 * </code></pre>
 */
class StringRangeArray {
	typedef ::balor::io::File File;

public:
	/// ������|�C���^�̌Œ蒷�z��ŏ������B
	template<int Size> StringRangeArray(wchar_t* (&array)[Size]) : _begin(array), _length(Size), _accessor(_charPointerAccessor) {}
	template<int Size> StringRangeArray(const wchar_t* (&array)[Size]) : _begin(array), _length(Size), _accessor(_charPointerAccessor) {}
	/// ������|�C���^�̃|�C���^�ƒ����ŏ������B
	StringRangeArray(const wchar_t* const * begin, int length) : _begin(begin), _length(length), _accessor(_charPointerAccessor) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(0 <= length);
#endif
	}
	/// ������|�C���^�� vector �ŏ������B
	template<typename Allocator> StringRangeArray(const std::vector<wchar_t*, Allocator>& array) : _begin(array.data()), _length(array.size()), _accessor(_charPointerAccessor) {}
	template<typename Allocator> StringRangeArray(const std::vector<const wchar_t*, Allocator>& array) : _begin(array.data()), _length(array.size()), _accessor(_charPointerAccessor) {}
	/// ������|�C���^�� array �ŏ������B
	template<int Size> StringRangeArray(const std::tr1::array<wchar_t*, Size >& array) : _begin(array.data()), _length(Size), _accessor(_charPointerAccessor) {}
	template<int Size> StringRangeArray(const std::tr1::array<const wchar_t*, Size >& array) : _begin(array.data()), _length(Size), _accessor(_charPointerAccessor) {}


	/// File �̌Œ蒷�z��ŏ������B
	template<int Size> StringRangeArray(const File (&array)[Size]) : _begin(array), _length(Size), _accessor(_fileAccessor) {}
	/// File �̃|�C���^�ƒ����ŏ������B
	StringRangeArray(const File* begin, int length) : _begin(begin), _length(length), _accessor(_fileAccessor) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(0 <= length);
#endif
	}
	/// File �� vector �ŏ������B
	template<typename Allocator> StringRangeArray(const std::vector<File, Allocator>& array) : _begin(array.data()), _length(array.size()), _accessor(_fileAccessor) {}
	template<typename Allocator> StringRangeArray(const std::vector<const File, Allocator>& array) : _begin(array.data()), _length(array.size()), _accessor(_fileAccessor) {}
	/// File �� array �ŏ������B
	template<int Size> StringRangeArray(const std::tr1::array<File, Size >& array) : _begin(array.data()), _length(Size), _accessor(_fileAccessor) {}
	template<int Size> StringRangeArray(const std::tr1::array<const File, Size >& array) : _begin(array.data()), _length(Size), _accessor(_fileAccessor) {}


	/// String �̌Œ蒷�z��ŏ������B
	template<int Size> StringRangeArray(const String (&array)[Size]) : _begin(array), _length(Size), _accessor(_stringAccessor) {}
	/// String �̃|�C���^�ƒ����ŏ������B
	StringRangeArray(const String* begin, int length) : _begin(begin), _length(length), _accessor(_stringAccessor) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(0 <= length);
#endif
	}
	/// String �� vector �ŏ������B
	template<typename Allocator> StringRangeArray(const std::vector<String, Allocator>& array) : _begin(array.data()), _length(array.size()), _accessor(_stringAccessor) {}
	template<typename Allocator> StringRangeArray(const std::vector<const String, Allocator>& array) : _begin(array.data()), _length(array.size()), _accessor(_stringAccessor) {}
	/// String �� array �ŏ������B
	template<int Size> StringRangeArray(const std::tr1::array<String, Size >& array) : _begin(array.data()), _length(Size), _accessor(_stringAccessor) {}
	template<int Size> StringRangeArray(const std::tr1::array<const String, Size >& array) : _begin(array.data()), _length(Size), _accessor(_stringAccessor) {}


	/// StringBuffer �̌Œ蒷�z��ŏ������B
	template<int Size> StringRangeArray(const StringBuffer (&array)[Size]) : _begin(array), _length(Size), _accessor(_stringBufferAccessor) {}
	/// StringBuffer �̃|�C���^�ƒ����ŏ������B
	StringRangeArray(const StringBuffer* begin, int length) : _begin(begin), _length(length), _accessor(_stringBufferAccessor) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(0 <= length);
#endif
	}
	/// StringBuffer �� vector �ŏ������B
	template<typename Allocator> StringRangeArray(const std::vector<StringBuffer, Allocator>& array) : _begin(array.data()), _length(array.size()), _accessor(_stringBufferAccessor) {}
	template<typename Allocator> StringRangeArray(const std::vector<const StringBuffer, Allocator>& array) : _begin(array.data()), _length(array.size()), _accessor(_stringBufferAccessor) {}
	/// StringBuffer �� array �ŏ������B
	template<int Size> StringRangeArray(const std::tr1::array<StringBuffer, Size >& array) : _begin(array.data()), _length(Size), _accessor(_stringBufferAccessor) {}
	template<int Size> StringRangeArray(const std::tr1::array<const StringBuffer, Size >& array) : _begin(array.data()), _length(Size), _accessor(_stringBufferAccessor) {}


	/// wstring �̌Œ蒷�z��ŏ������B
	template<typename Traits, typename Allocator, int Size> StringRangeArray(const std::basic_string<wchar_t, Traits, Allocator> (&array)[Size]) : _begin(array), _length(Size), _accessor(_stdStringAccessor) {}
	/// wstring �̃|�C���^�ƒ����ŏ������B
	template<typename Traits, typename Allocator> StringRangeArray(const std::basic_string<wchar_t, Traits, Allocator>* begin, int length) : _begin(begin), _length(length), _accessor(_stdStringAccessor) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(0 <= length);
#endif
	}
	/// wstring �� vector �ŏ������B
	template<typename Traits, typename Allocator, typename VectorAllocator> StringRangeArray(const std::vector<std::basic_string<wchar_t, Traits, Allocator>, VectorAllocator>& array) : _begin(array.data()), _length(array.size()), _accessor(_stdStringAccessor) {}
	template<typename Traits, typename Allocator, typename VectorAllocator> StringRangeArray(const std::vector<const std::basic_string<wchar_t, Traits, VectorAllocator>, Allocator>& array) : _begin(array.data()), _length(array.size()), _accessor(_stdStringAccessor) {}
	/// wstring �� array �ŏ������B
	template<typename Traits, typename Allocator, int Size> StringRangeArray(const std::tr1::array<std::basic_string<wchar_t, Traits, Allocator>, Size >& array) : _begin(array.data()), _length(Size), _accessor(_stdStringAccessor) {}
	template<typename Traits, typename Allocator, int Size> StringRangeArray(const std::tr1::array<const std::basic_string<wchar_t, Traits, Allocator>, Size >& array) : _begin(array.data()), _length(Size), _accessor(_stdStringAccessor) {}

public:
	/// �z�񂪋󂩂ǂ����B
	bool empty() const {
		return !_length;
	}
	/// �z��̒����B
	int length() const {
		return _length;
	}

public:
	/// �z��v�f�ւ̃A�N�Z�X
	StringRange operator[](int index) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(0 <= index);
		::balor::test::noMacroAssert(index < length());
#endif
		return (*_accessor)(_begin, index);
	}

private:
	static StringRange _charPointerAccessor(const void* begin, int index);
	static StringRange _fileAccessor(const void* begin, int index);
	static StringRange _stringAccessor(const void* begin, int index);
	static StringRange _stringBufferAccessor(const void* begin, int index);
	static StringRange _stdStringAccessor(const void* begin, int index);

	const void* _begin;
	StringRange (*_accessor)(const void* , int);
	int _length;
};



}