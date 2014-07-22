#pragma once

#include <balor/test/noMacroAssert.hpp>


namespace std {
template<typename T> struct char_traits;
template<typename T> class allocator;
template<typename T, typename Traits, typename Allocator> class basic_string;
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
 * ������̃|�C���^�ƒ����������Abalor::String�Abalor::StringBuffer�Astd::wstring �ƕ�����|�C���^����ϊ��ł���B�l�X�ȕ�����\�������ʂ̊֐��C���^�[�t�F�[�X�Ŏ����ł���悤�ɂ���B
 * 
 * ���̃N���X�͊֐��̈����ɂ̂ݎg������z�肵�Ă���̂ŁA���[�J���ϐ���N���X�ϐ��Ŏg�p���Ȃ����ƁB
 * �Ⴆ�΃R���X�g���N�^�� wstring �̃e���|�����I�u�W�F�N�g��n���� StringRange �̃��[�J���ϐ����쐬����ƁA
 * StringRange �͊��ɔj�󂳂ꂽ���������e���Q�Ƃ��Ă���̂ŃA�N�Z�X����΃v���O�����̓N���b�V������B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	String s(L"abc");

	// String::compareTo �� StringRange �������Ɏ��̂ŕ�����|�C���^, String, StringBuffer, wstring ��n�����Ƃ��ł���B
	s.compareTo(L"abc");
	s.compareTo(String(L"abc"));
	s.compareTo(StringBuffer(L"abc"));
	s.compareTo(std::wstring(L"abc"));
 * </code></pre>
 */
template<typename T>
class BasicStringRange {
public:
	/// ������|�C���^�ŏ������B
	BasicStringRange(const T* string) : _c_str(string), _rawLength(-1) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(string != nullptr);
#endif
	}
	/// ������|�C���^�ƕ�����T�C�Y�ŏ������B
	/// �T�C�Y�����ɂ킩���Ă��ĕ�����̃T�C�Y�𒲂ׂ鏈�����Ȃ������ꍇ�ɂ��̃R���X�g���N�^���g���B
	/// StringRange �������Ɏ�鑽���̊֐��� length �ʒu�̕����� L'\0' �ł��邱�Ƃ����҂��Ă���̂ŕ�����������w�肵�Ȃ����ƁB
	BasicStringRange(const T* string, int length) : _c_str(string), _rawLength(length) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(string != nullptr);
		::balor::test::noMacroAssert(-1 <= length);
#endif
	}
	/// std::basic_string �ŏ������B
	template<typename Traits, typename Allocator> BasicStringRange(const std::basic_string<T, Traits, Allocator>& string) : _c_str(string.c_str()), _rawLength(string.length()) {}

public:
	/// �󕶎��񂩂ǂ����B�������O�ł͂Ȃ��Ă��󕶎���ɂȂ肦�邱�Ƃɒ��ӁB
	bool empty() const { return *_c_str == 0; }
	/// ������|�C���^�B
	const T* c_str() const { return _c_str; }
	/// ������̒����B
	int length() const {
		if (_rawLength == -1) {
			const_cast<BasicStringRange*>(this)->_rawLength = String::getLength(_c_str);
		}
		return _rawLength;
	}
	/// ������̒����B�������܂������Ă��Ȃ��Ƃ��� -1��Ԃ��B
	int rawLength() const { return _rawLength; }

private:
	const T* _c_str;
	int _rawLength;
};


/// �o�C�g������p�B
typedef BasicStringRange<char> ByteStringRange;


/// ���C�h������p�B
typedef BasicStringRange<wchar_t> StringRange;



}