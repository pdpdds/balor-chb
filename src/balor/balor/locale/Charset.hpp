#pragma once

#include <balor/system/ComPtr.hpp>
#include <balor/ArrayRange.hpp>
#include <balor/Exception.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/StringRange.hpp>

struct IMultiLanguage2;

namespace std {
template<typename T> struct char_traits;
template<typename T> class allocator;
template<typename T, typename Traits, typename Allocator> class basic_string;
}

namespace balor {
class String;
}


namespace balor {
	namespace locale {



/**
 * �����R�[�h��\���A�R�[�h�Ԃ̕�����ϊ���񋟂���B
 *
 * �ϊ��ɂ� mlang.dll �� COM �I�u�W�F�N�g���g�p���Ă��邪�A�R���X�g���N�^������ isWindowCodePage �� true �ɂ����ꍇ�Ɍ���
 * WIN32 API �� WideCharToMultiByte, MultiByteToWideChar �֐����g�p����B
 * ���̏ꍇ COM �I�u�W�F�N�g��K�v�Ƃ���֐����Ă΂Ȃ����� COM �I�u�W�F�N�g�͍쐬����Ȃ��̂ŁA�p�t�H�[�}���X�����シ��\��������B
 * ���������̐ݒ�� WIN32 API �ŃT�|�[�g�����R�[�h�y�[�W�ł����g���Ȃ��B�܂��A�ϊ��̌��ʂ� COM �̂��̂ƈقȂ�B
 * �Ⴆ�΁A�S�p�̃A���t�@�x�b�g�� ASCII �� encode �����ꍇ�� COM �͔��p�̃A���t�@�x�b�g�ɕϊ����邪 WIN32 API �ł͕ϊ����s�ɂȂ�B
 * COM �̏������́A���C���X���b�h�� COM �I�u�W�F�N�g�̏������Ɏ��s�����ꍇ�̂� ::balor::system::Com �� STA �� COM ���������s���Ă���B
 * �}���`�X���b�h�� Charset ���g�p����ꍇ�̓��C���X���b�h�� MTA �� COM ���������s�����A�V�����X���b�h���Ŗ����I�� COM �̏����������A�I���������s���K�v������B
 * �Ȃ� mlang.dll ��COM�I�u�W�F�N�g�� threadingModel �� both �ł���悤���B
 */
class Charset : private NonCopyable {
public:
	typedef std::basic_string<char, std::char_traits<char>, std::allocator<char> > string;

	/// �L�����N�^�[�Z�b�g��������Ȃ������B
	class NotFoundException : public Exception {};

	/// encode, decode, convert �����s���Athrowable ������ true �̏ꍇ�ɓ�������B
	class ConversionFailedException : public Exception {};

	/// �ϊ����ʂ��������ޔz��̒���������Ȃ������B
	class InsufficientBufferExceptoin : public Exception {};

public:
	/// �R�[�h�y�[�W����쐬�BisWindowsCodePage �ɂ��Ă̓N���X�̃h�L�������g���Q�ƁB
	explicit Charset(int codePage, bool isWindowsCodePage = false);
	/// �L�����N�^�[�Z�b�g������쐬�B
	explicit Charset(StringRange name);
	Charset(Charset&& value);
	~Charset();

	Charset& operator=(Charset&& value);

public:
	/// ASCII �����R�[�h�B
	static Charset ascii();
	/// �r�b�O�G���f�B�A�����j�R�[�h�B
	static Charset bigEndianUnicode();
	/// �g�p�\�ȃL�����N�^�[�Z�b�g�ꗗ�B
	static std::vector<Charset, std::allocator<Charset> > charsets();
	/// �R�[�h�y�[�W�B
	int codePage() const;
	/// Unicode �ւ̕ϊ��B
	String decode(ByteStringRange src) const;
	String decode(ByteStringRange src, int count) const;
	/// Unicode �ւ̕ϊ��Bdst �ɕϊ����ʂ��������݁A�ϊ�������������Ԃ��B
	int decode(ByteStringRange src, int count, ArrayRange<wchar_t> dst) const;
	/// �V�X�e���̃f�t�H���g�L�����N�^�[�Z�b�g�BisWindowsCodePage �� true �ō쐬����鎖�ɒ��ӁB
	static Charset default();
	/// �L�����N�^�[�Z�b�g�̕\�����B
	String displayName() const;
	/// srcCharset ����̕ϊ��B
	string encode(ByteStringRange src, const Charset& srcCharset) const;
	string encode(ByteStringRange src, int count, const Charset& srcCharset) const;
	/// srcCharset ����̕ϊ��Bdst �ɕϊ����ʂ��������݁A�ϊ�������������Ԃ��B
	int encode(ByteStringRange src, int count, ArrayRange<char> dst, const Charset& srcCharset) const;
	/// Unicode ����̕ϊ��B
	string encode(StringRange src) const;
	string encode(StringRange src, int count) const;
	/// Unicode ����̕ϊ��Bdst �ɕϊ����ʂ��������݁A�ϊ�������������Ԃ��B
	int encode(StringRange src, int count, ArrayRange<char> dst) const;
	/// EUC-JP �R�[�h�B
	static Charset eucJp();
	/// Unicode ����� encode �Ɏ��s����������u�����镶���B�����l�� L'?'�BUnicode �ȊO����� encode, decode �ł̓T�|�[�g����Ȃ��B
	wchar_t fallbackChar() const;
	void fallbackChar(wchar_t value);
	/// �L�����N�^�[�Z�b�g���B
	String name() const;
	/// ShiftJIS �R�[�h�B
	static Charset shiftJis();
	/// �ϊ��Ɏ��s�����ꍇ�� Charset::ConversionFailedException �𓊂��邩�ǂ����B�����l�� false�B
	bool throwable() const;
	void throwable(bool value);
	/// ���j�R�[�h�B
	static Charset unicode();
	/// UTF7�B
	static Charset utf7();
	/// UTF8�B
	static Charset utf8();

private:
	const ::balor::system::ComPtr<::IMultiLanguage2>& _getMultiLanguage() const;

	int _codePage;
	bool _isWindowsCodePage;
	bool _throwable;
	wchar_t _fallbackChar;
	char _fallbackBytes[6];
	::balor::system::ComPtr<::IMultiLanguage2> _multiLanguage;
};



	}
}