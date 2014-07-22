#pragma once

#include <balor/Convert.hpp>
#include <balor/StringRange.hpp>


namespace balor {



/**
 * ������̘A���A�}���A�폜��u�����s���镶����o�b�t�@�B
 * 
 * String ���A���A�}���A�폜�A�u���������s�����тɐV���Ƀ��������蓖�Ă��s���̂ɑ΂��AStringBuffer �̓o�b�t�@�T�C�Y���������胁�������蓖�Ă��s��Ȃ��B
 * �o�b�t�@�ɊO���̌Œ蒷�z����w�肷�邱�Ƃ��ł��A���̏ꍇ�͌Œ蒷�𒴂��ĕ������������߂Ȃ��B
 * String::refer �� String::literal �Ƒg�ݍ��킹�邱�ƂŃ��������蓖�Ă����S�ɔr���ł���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	wchar_t buffer[256];
	StringBuffer s(buffer);
	s += L"abc";
	s += L"def";
	assert(String::equals(buffer, L"abcdef"));
 * </code></pre>
 */
class StringBuffer {
public:
	typedef std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> > wstring;
	friend String;

public:
	/// �L���p�V�e�B = 1 �ŏ������B
	StringBuffer();
	StringBuffer(const StringBuffer& value);
	StringBuffer(StringBuffer&& value);
	/// String �̒��� + 1 �̃L���p�V�e�B�ŕ�������R�s�[���ď������B
	explicit StringBuffer(const String& value);
	explicit StringBuffer(String&& value);
	/// �w�肵���L���p�V�e�B�ŏ������B
	explicit StringBuffer(int capacity);
	/// �Œ蒷�z����o�b�t�@�Ƃ��ď������B
	template<int Capacity> explicit StringBuffer(wchar_t (&buffer)[Capacity], int length = 0) : _begin(buffer), _length(length), _capacity(Capacity), _allocatable(false) {
#if !defined(NDEBUG)
		::balor::test::noMacroAssert(0 <= length);
		::balor::test::noMacroAssert(length < Capacity);
#endif
		_begin[length] = L'\0';
	}
	/// �������|�C���^�ŏ������B
	StringBuffer(wchar_t* buffer, int capacity, int length = 0);
	~StringBuffer();

	StringBuffer& operator=(const StringBuffer& value);
	StringBuffer& operator=(StringBuffer&& value);

public:
	/// �o�b�t�@���g���ł��邩�ǂ����B
	bool allocatable() const;
	/// ������̐擪�B
	wchar_t* begin() { return _begin; }
	const wchar_t* begin() const { return _begin; }
	/// �I�[�������܂񂾃o�b�t�@�̃T�C�Y�B
	int capacity() const;
	void capacity(int value);
	/// ������̒������O�ɂ���B
	void clear() { length(0); }
	/// �󕶎��񂩂ǂ����B
	bool empty() const;
	/// ������̏I�[�B
	wchar_t* end() { return _begin + _length; }
	const wchar_t* end() const { return _begin + _length; }
	/// �w�肵���������폜����B
	void erase(int beginIndex);
	void erase(int beginIndex, int length);
	/// end() ����I�[�������������ĐV����������ݒ肵�����B
	void expandLength();
	/// �������w�肵���������傫������B�I�[�����͏������܂Ȃ��B
	void expandLength(int delta);
	/// �������}������B
	void insert(int beginIndex, wchar_t value, int count);
	void insert(int beginIndex, StringRange value);
	/// ������̒����B
	int length() const { return _length; }
	void length(int value);
	/// �w�肵�������╶�����u������B
	void replace(wchar_t oldValue, wchar_t newValue);
	void replace(StringRange oldValue, StringRange newValue);
	void replace(int beginIndex, int length, StringRange value);
	/// capacity ���w�肵�������ȏ�ɂ���B
	void reserve(int maxLength);
	/// capacity �����݂̒��� + �ǉ��̒����ȏ�ɂ���B
	void reserveAdditionally(int additionalLength);
	/// �擪�Ɩ����� trimChars �Ɋ܂܂�镶������菜���BtrimChars ���󕶎���̏ꍇ�� whiteSpace �Ƃ݂Ȃ��B
	void trim(StringRange trimChars = L"");

public:
	/// wstring �ւ̕ϊ��B
	operator wstring() const;
	/// StringRange �ւ̕ϊ��B
	operator StringRange() const { return StringRange(_begin, _length); }
	/// �����v�f��Ԃ��B
	wchar_t& operator[] (int index);
	const wchar_t& operator[] (int index) const;
	/// ������̒ǉ����Z�q�B
	StringBuffer& operator+=(const StringBuffer& rhs);
	StringBuffer& operator+=(const String& rhs);
	StringBuffer& operator+=(const wstring& rhs);
	StringBuffer& operator+=(const wchar_t* rhs);
	StringBuffer& operator+=(wchar_t* rhs);
	StringBuffer& operator+=(wchar_t rhs);
	/// Convert::to<StringBuffer> ���\�Ȍ^�� += ���Z�B
	template<typename T> StringBuffer& operator+=(const T& rhs) {
		Convert::to<StringBuffer>(*this, rhs);
		return *this;
	}

private:
	int _getNewCapacity(int newLength) const;

	wchar_t* _begin;
	int _length;
	int _capacity;
	bool _allocatable;
};



}