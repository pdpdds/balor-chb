#pragma once

#include <balor/ArrayRange.hpp>
#include <balor/Convert.hpp>
#include <balor/Enum.hpp>
#include <balor/StringRange.hpp>
#include <balor/StringRangeArray.hpp>

namespace balor {
	namespace locale {
class Charset;
class Locale;
	}
}


namespace balor {

class StringBuffer;



/**
 * �������?���B
 *
 * Java �� .NET �� String �Ɠ��l�AUnicode �݂̂�����������?�C��?�̓��e�̕ύX�������Ȃ��B
 * std::wstring �Ƒ��݂ɕϊ���?�B������ basic_string �������Ɏ��e���v��?�g�֐��ɂ͓n���Ȃ����̂������̂ł��̏ꍇ�� begin�Aend �֐����g���B
 * �֐������� balor::locale::Locale ��n���Ȃ��ꍇ�͏�ɏ����������s���B�i�n�捷�𖳎����ĕ����R?�h�𐔒l�Ƃ��Ĕ�r����j
 * ���� operator < ���̉��Z�q�̏����ł� Locale ���w��ł��Ȃ��̂őS�ď��������ɂȂ邱�Ƃɒ��ӁB
 * ���������ł͑S�p�A���t?�x�b�g�ɑ΂��� ignoreCase �̓T??�g���Ȃ��B
 * Convert::to<String> �֐��ŕϊ���?��?�� String �� + ���Z�q�ŘA�����邱�Ƃ��ł���B
 *
 * Unicode ���K���ׂ̈� isNormalized, normalize �֐��� Vista ��?���AIE7 ��?�̃C���X�g?�����ꂽ XP ���A�܂��� normaliz.dll ���C���X�g?������ XP �ł̂݃T??�g����B
 *
 * Vista ��?�ł���� ::FindNLSString �֐����g����̂��� balor �� XP ��?�̃T??�g�Ȃ̂�
 * indexOf, lastIndexOf, startsWith �y�� endsWith �֐��͎��͎����ƂȂ��Ă���B
 * API ���Ή����Ă��Ȃ��̂ŃT���Q?�g�y�A�ł����������ł��镶���R?�h�����������Ɣ��f�ł��Ȃ��B
 *
 * ���e��ύX���Ȃ��Ƃ����d�l�𐶂����� refer, literal �֐����g���ĕ�����?�C��?���Q�Ƃ������邱�Ƃ��ł��邪�A?�C��?�Q�Ƃ̊댯����?���ɍl������K�v������B
 *
 * ������N���X�̎���͎ԗւ̍Ĕ����ł���A�ł���΂�肽���͂Ȃ���
 * std::wstring �y�� Boost.string algo �ł̓��P?���� Unicode �֘A�̏��������S�ɖ������Ă���̂őΉ�����������N���X���쐬�����B
 *
 * ���T���Q?�g�y�A�A���K���A���������� Unicode �̎d�l
 *
 * <h3>�E�T���v���R?�h</h3>
 * <pre><code>
	String s(L"abc");

	// std::wstring �Ƃ̑��ݕϊ�
	std::wstring ws = s;
	s = ws;

	// ���P?�����l��������r
	bool result = String::compare(s, L"������", Locale::current());

	// �����񓯎m�A�܂��͐��l�Ƃ̘A��
	s = s + L"def";
	s = String(L"(") + 128 + L", " + 256 + L")";
 * </code></pre>
 */
class String {
public:
	typedef std::basic_string<char, std::char_traits<char>, std::allocator<char> > string;
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > wstring;
	typedef ::balor::locale::Locale Locale;
#ifdef  _WIN64
	typedef unsigned __int64 SizeType;
#else
	typedef __w64 unsigned int SizeType;
#endif

	friend StringBuffer;

	/// �������r�̃I�v�V�����B�g�ݍ��킹�Ŏw�肷��B
	/// ���������������֐��iindexOf, lastIndexOf, startsWith, endsWith���j�ł� ignoreNonSpace, ignoreSymbols �͎w��ł��Ȃ��B
	struct CompareOptions {
		enum _enum {
			none           = 0         , 
			ignoreCase     = 0x00000001, /// �啶���Ə���������ʂ��Ȃ��B
			ignoreNonSpace = 0x00000002, /// �ꏊ�����Ȃ����������𖳎�����B�����������ʂ��������������������ʂ��������ꍇ�𓙂����Ƃ���B
			ignoreSymbols  = 0x00000004, /// �L���𖳎�����B
			ignoreKanaType = 0x00010000, /// �Ђ炪�ȂƃJ?�J�i����ʂ��Ȃ��B
			ignoreWidth    = 0x00020000, /// �S�p�Ɣ��p����ʂ��Ȃ��B
			stringSort     = 0x00001000, /// �u-�v��u'�v����ʈ������Ȃ��B�w�肵�Ȃ������ꍇ�͂���炪�������̂Ƃ��Ĕ�r�����B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(CompareOptions);
	};

	/// Unicode �̐��K��?���B
	struct NormalizationForm {
		enum _enum {
			c  = 0x1, /// ���K��?�� C
			d  = 0x2, /// ���K��?�� D
			kc = 0x5, /// ���K��?�� KC
			kd = 0x6, /// ���K��?�� KD
		};
		BALOR_NAMED_ENUM_MEMBERS(NormalizationForm);
	};

	/// normaliz.dll ��������Ȃ��ꍇ�ɓ�������B
	class NormalizeDllNotFoundException : public Exception {};

	/// �������T���Q?�g�y�A�Ȃǂ̐��K���s?�ȕ����𐳋K�����悤�Ƃ����Ƃ��ɓ�������B
	class NormalizeFailedException : public Exception {};

public:
	/// �󕶎���iL""�j�ŏ������B
	String();
	String(const String& value);
	String(String&& value);
	/// StringBuffer ����ϊ��B
	String(const StringBuffer& value);
	String(StringBuffer&& value);
	/// std::wstring �ŏ������B
	String(const wstring& value);
	/// ������?�C��?�ŏ������B
	String(const wchar_t* value);
	/// �L�����N??�ƌJ��Ԃ����ŏ������B
	String(wchar_t c, int count);
	/// ������?�C��?�ƕ�����̒����ŏ������B
	String(const wchar_t* value, int length);
	/// �o�C�g��������L�����N??�Z�b�g�Ńf�R?�h���ď������B
	String(ByteStringRange value, const ::balor::locale::Charset& charset);
	~String();

	String& operator=(const String& value);
	String& operator=(String&& value);
	/// StringBuffer ����ԁB
	String& operator=(const StringBuffer& value);
	String& operator=(StringBuffer&& value);
	/// std::wstring ����ԁB
	String& operator=(const wstring& value);
	/// ������?�C��?����ԁB
	String& operator=(const wchar_t* value);

public:
	/// ������ւ�?�C��?�B
	const wchar_t* begin() const { return _c_str; }
	/// ������ւ�?�C��?�B
	const wchar_t* c_str() const { return _c_str; }
	/// ������̔�r�B�߂�l�� C ����� strcmp �n�̊֐��Ɠ����B
	static int compare(StringRange lhs, StringRange rhs, bool ignoreCase = false);
	static int compare(StringRange lhs, StringRange rhs, const Locale& locale, String::CompareOptions options = CompareOptions::none);
	static int compare(StringRange lhs, int lindex, StringRange rhs, int rindex, int length, bool ignoreCase = false);
	static int compare(StringRange lhs, int lindex, StringRange rhs, int rindex, int length, const Locale& locale, String::CompareOptions options = CompareOptions::none);
	/// ������̔�r�B�߂�l�� C ����� strcmp �n�̊֐��Ɠ����B
	int compareTo(StringRange rhs) const;
	/// ��������� value �������邩�ǂ����B
	bool contains(StringRange value) const;
	/// �����z��� null�I?���܂ޕ�����S�̂��R�s?����B
	template<int Size> void copyTo(wchar_t (&array)[Size]) const { copyTo(array, Size); }
	void copyTo(wchar_t* array, int arraySize) const;
	/// �����z��ɕ�����������R�s?����B
	template<int Size> void copyTo(int beginIndex, wchar_t (&array)[Size], int arrayIndex, int length) const { copyTo(beginIndex, array, Size, arrayIndex, length); }
	void copyTo(int beginIndex, wchar_t* array, int arraySize, int arrayIndex, int length) const;
	/// �󕶎��񂩂ǂ����B�������O�ł͂Ȃ��Ă��󕶎���ɂȂ肦�邱�Ƃɒ��ӁB
	bool empty() const;
	/// ������I?�ւ�?�C��?�B
	const wchar_t* end() const { return _c_str + length(); }
	/// �w�肵��������ŏI��邩�ǂ����B
	bool endsWith(StringRange value, bool ignoreCase = false) const;
	bool endsWith(StringRange value, const Locale& locale, String::CompareOptions options = CompareOptions::none) const;
	/// �����񂪓��������ǂ����B
	static bool equals(ByteStringRange lhs, ByteStringRange rhs, bool ignoreCase = false);
	static bool equals(StringRange lhs, StringRange rhs, bool ignoreCase = false);
	static bool equals(StringRange lhs, StringRange rhs, const Locale& locale, String::CompareOptions options = CompareOptions::none);
	/// �����񂪓��������ǂ����B
	bool equalTo(StringRange rhs, bool ignoreCase = false) const;
	bool equalTo(StringRange rhs, const Locale& locale, String::CompareOptions options = CompareOptions::none) const;
	/// �w�肵���������폜�����������Ԃ��B
	String erase(int beginIndex) const;
	String erase(int beginIndex, int length) const;
	/// �o�C�g������?�C��?�̂���������̒�����Ԃ��B
	static int getLength(const char* value);
	/// ������?�C��?�̂���������̒�����Ԃ��B
	static int getLength(const wchar_t* value);
	/// ����������T���Q?�g�y�A���l������ beginIndex �̎��̕����̃C���f�b�N�X��Ԃ��B
	int getNextLetterIndex(int beginIndex = 0) const;
	/// ������̃n�b�V���l�B
	SizeType hashCode() const;
	/// �w�肵�������╶���񂪍ŏ��Ɍ��������ʒu��Ԃ��B
	int indexOf(StringRange value, bool ignoreCase = false) const;
	int indexOf(StringRange value, const Locale& locale, String::CompareOptions options = CompareOptions::none) const;
	int indexOf(wchar_t value, int beginIndex = 0) const;
	int indexOf(StringRange value, int beginIndex, bool ignoreCase = false) const;
	int indexOf(StringRange value, int beginIndex, const Locale& locale, String::CompareOptions options = CompareOptions::none) const;
	int indexOf(wchar_t value, int beginIndex, int length) const;
	int indexOf(StringRange value, int beginIndex, int length, bool ignoreCase = false) const;
	int indexOf(StringRange value, int beginIndex, int length, const Locale& locale, String::CompareOptions options = CompareOptions::none) const;
	/// �w�肵��������̒��̕����̂ǂꂩ���ŏ��Ɍ��������ʒu��Ԃ��B
	int indexOfAny(StringRange anyOf, int beginIndex = 0) const;
	int indexOfAny(StringRange anyOf, int beginIndex, int length) const;
	/// �������?�����ĕԂ��B
	String insert(int beginIndex, StringRange value) const;
	/// �w�肵�����K��?���Ő��K������Ă��邩�ǂ����B
	bool isNormalized(String::NormalizationForm frame = NormalizationForm::c) const;
	/// �󔒕��������܂܂�Ȃ����ǂ����B
	bool isWhiteSpace() const;
	/// �����̕������ separator �Ō������ĕԂ��B
	static String join(StringRange separator, StringRangeArray values);
	/// �w�肵�������╶���񂪍Ō�Ɍ��������ʒu��Ԃ��B
	int lastIndexOf(StringRange value, bool ignoreCase = false) const;
	int lastIndexOf(StringRange value, const Locale& locale, String::CompareOptions options = CompareOptions::none) const;
	int lastIndexOf(wchar_t value, int beginIndex = 0) const;
	int lastIndexOf(StringRange value, int beginIndex, bool ignoreCase = false) const;
	int lastIndexOf(StringRange  value, int beginIndex, const Locale& locale, String::CompareOptions options = CompareOptions::none) const;
	int lastIndexOf(wchar_t value, int beginIndex, int length) const;
	int lastIndexOf(StringRange value, int beginIndex, int length, bool ignoreCase = false) const;
	int lastIndexOf(StringRange  value, int beginIndex, int length, const Locale& locale, String::CompareOptions options = CompareOptions::none) const;
	/// �w�肵��������̒��̕����̂ǂꂩ���Ō�Ɍ��������ʒu��Ԃ��B
	int lastIndexOfAny(StringRange anyOf, int beginIndex = 0) const;
	int lastIndexOfAny(StringRange anyOf, int beginIndex, int length) const;
	/// ������̒����B
	int length() const;
	/// ����������T���Q?�g�y�A���l������?������镶����̒����B
	int lengthInLetter() const;
	/// �����񃊃e�������Q�Ƃ��� String ���쐬����B
	template<int Size> static String literal(const wchar_t (&string)[Size]) { return String(1 - Size, string); }
	/// �w�肵�����K��?���Ő��K�����ĕԂ��B
	String normalize(String::NormalizationForm frame = NormalizationForm::c) const;
	/// �w�肵�������ɂȂ�܂Ő擪�ɕ����𖄂ߍ���ŕԂ��B
	String padLeft(int length, wchar_t paddingChar = L' ') const;
	/// �w�肵�������ɂȂ�܂Ŗ����ɕ����𖄂ߍ���ŕԂ��B
	String padRight(int length, wchar_t paddingChar = L' ') const;
	/// ������?�C��?���Q�Ƃ��� String ���쐬����BString �͓��e�̕ύX�������Ȃ����A�Q�ƌ�����ɔj�󂳂��Ɗ댯�B
	static String refer(StringRange value);
	static String refer(const wchar_t* value, int length);
	/// ������?�C��?���Q�Ƃ��Ă��邩�ǂ����B
	bool referred() const { return _length <= 0; }
	/// �w�肵�������╶�����u�����ĕԂ��B
	String replace(wchar_t oldValue, wchar_t newValue) const;
	String replace(StringRange oldValue, StringRange newValue) const;
	/// �w�肵�������̋�؂蕶���ŕ�������������z���Ԃ��Bseparators ����̏ꍇ�͋�؂蕶���� whiteSpace �Ƃ݂Ȃ��B
	std::vector<String, std::allocator<String> > split(StringRange separators = L"") const;
	/// �w�肵�������̋�؂蕶����ŕ�������������z���Ԃ��B
	std::vector<String, std::allocator<String> > split(StringRangeArray separators) const;
	/// �w�肵��������Ŏn�܂邩�ǂ����B
	bool startsWith(StringRange value, bool ignoreCase = false) const;
	bool startsWith(StringRange value, const Locale& locale, String::CompareOptions options = CompareOptions::none) const;
	/// �����������Ԃ��B
	String substring(int beginIndex) const;
	String substring(int beginIndex, int length) const;
	/// �啶�����������ɂ��ĕԂ��B
	String toLower() const;
	String toLower(const Locale& locale) const;
	/// ��������啶���ɂ��ĕԂ��B
	String toUpper() const;
	String toUpper(const Locale& locale) const;
	/// �擪�Ɩ����� trimChars �Ɋ܂܂�镶����S�Ď�菜���ĕԂ��BtrimChars ���󕶎���̏ꍇ�� whiteSpace �Ƃ݂Ȃ��B
	String trim(StringRange trimChars = String()) const;

public:
	/// wstring �ւ̕ϊ��B
	operator wstring() const;
	/// StringRange �ւ̕ϊ��B
	operator StringRange() const { return StringRange(_c_str, length()); }
	/// �����v�f��Ԃ��B
	wchar_t operator[] (int index) const;
	/// ������̒ǉ��B
	String& operator+=(const String& rhs);
	String& operator+=(const wstring& rhs);
	String& operator+=(const wchar_t* rhs);
	String& operator+=(wchar_t* rhs);
	String& operator+=(wchar_t rhs);
	/// Convert::to<String> ����?��?�� += ���Z�B
	template<typename T> String& operator+=(const T& rhs) { return *this += Convert::to<String>(rhs); }
	/// ������̉��Z�B
	friend String operator+(const String& lhs, const String& rhs);
	friend String operator+(const String& lhs, const wstring& rhs);
	friend String operator+(const String& lhs, const wchar_t* rhs);
	friend String operator+(const String& lhs, wchar_t* rhs);
	friend String operator+(const String& lhs, wchar_t rhs);
	friend String operator+(const wstring& lhs, const String& rhs);
	friend String operator+(const wchar_t* lhs, const String& rhs);
	friend String operator+(wchar_t* lhs, const String& rhs);
	friend String operator+(wchar_t lhs, const String& rhs);
	/// Convert::to<String> ����?��?�Ƃ� + ���Z�B
	template<typename T> friend String operator+(const String& lhs, const T& rhs) { return lhs + Convert::to<String>(rhs); }
	template<typename T> friend String operator+(const T& lhs, const String& rhs) { return Convert::to<String>(lhs) + rhs; }
	/// ��r���Z�B
	friend bool operator==(StringRange lhs, StringRange rhs);
	friend bool operator!=(StringRange lhs, StringRange rhs);
	friend bool operator< (StringRange lhs, StringRange rhs);
	friend bool operator<=(StringRange lhs, StringRange rhs);
	friend bool operator> (StringRange lhs, StringRange rhs);
	friend bool operator>=(StringRange lhs, StringRange rhs);

private:
	String(int length, const wchar_t* value);

	const wchar_t* _c_str;
	int _length;
};



}


namespace stdext {
	inline ::balor::String::SizeType hash_value(const ::balor::String& string) {
		return string.hashCode();
	}
}