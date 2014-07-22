#pragma once

#include <balor/Exception.hpp>
#include <balor/StringRange.hpp>


namespace std {
template<typename T> struct char_traits;
template<typename T> class allocator;
template<typename T, typename Traits, typename Allocator> class basic_string;
}


namespace balor {

class String;
class StringBuffer;



/**
 * ��{�f�[�^�^�� String �𑊌݂ɕϊ�����e���v���[�g�֐��Q�B
 *
 * ���Aprintf �Ɠ��l�̏������w�肵���ϊ����T�|�[�g����B���P�[���w��̕ϊ��͖������B�S��"C"���P�[���ŏ��������B
 * ��{�f�[�^�^���m�̕ϊ��̓T�|�[�g���Ȃ��Bboost::numeric_cast�ASafeInt �܂��� static_cast �𗘗p����Ηǂ��B
 * ������\�������񂩂� unsigned �^�ɕϊ������ꍇ�Asigned �^�̃o�C�i���\���ɂȂ邩 OverflowException �𔭐������邩�͌^�ɂ���ĕs��B
 * 1.#INF �� 1.#QNAN �͕����񉻂͂ł��邪���l�����悤�Ƃ���ƂP�ɂȂ�_�ɒ��ӁB
 * Convert �͖��O��ԂƂ��Ď������Ă���̂ŁA�C�ӂ̌^�ɂ��Ċ֐���ǉ�������AConvet::�ƃ^�C�v����̂��ʓ|�ȏꍇ�� using ���邱�Ƃ��ł���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	// ���l�ƕ�����̕ϊ�
	String s0 = Convert::to<String>(128);
	String s1 = Convert::to<String>(3.1415);
	int i0 = Convert::to<int>(L"128");
	double i1 = Convert::to<double>(L"3.1415");

	// ��⏑���w��������ϊ�
	String s2 = Convert::to<String>(0xff, 16); // s2 == L"ff"
	String s3 = Convert::to<String>(128, L"05"); // s3 == L"00128"
 * </code></pre>
 */
namespace Convert {
	/// �^�ϊ��ŃI�[�o�[�t���[�����������ꍇ�ɓ��������O�B
	class OverflowException : public Exception {};

	/// �������ϊ��ł��Ȃ������ꍇ�ɓ��������O�B
	class StringFormatException : public Exception {};


	/// �C�ӌ^����C�ӌ^�ւ̕ϊ��e���v���[�g�֐��B�T�|�[�g����ϊ��̂ݓ��ꉻ���Ď�������B������̏����l�� 10 �ɐݒ肷��B
	template<typename Dst, typename Src> Dst to(const Src& value, int base = 10) { static_assert(false, "Convert type unsupported"); }

	/// �l�X�Ȍ^�̕���������� StringRange �����ɕϊ�����e���v���[�g�֐��B
	template<typename Dst> Dst to(wchar_t* value, int base = 10) { return to<Dst>(StringRange(value), base); }
	template<typename Dst> Dst to(const wchar_t* value, int base = 10) { return to<Dst>(StringRange(value), base); }
	template<typename Dst> Dst to(const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >& value, int base = 10) { return to<Dst>(StringRange(value), base); }
	template<typename Dst> Dst to(const String& value, int base = 10) { return to<Dst>(StringRange(value), base); }
	template<typename Dst> Dst to(const StringBuffer& value, int base = 10) { return to<Dst>(StringRange(value), base); }

	/// �����񂩂琔�l�ւ̕ϊ��B
	/// base �Ɋ�Ƃ��Ďw��ł���̂� float �� double �̏ꍇ�� 10 �݂̂ŁA����ȊO�� 2, 8, 10, 16�B
	template<> __int64 to<__int64>(const StringRange& value, int base);
	template<> char to<char>(const StringRange& value, int base);
	template<> double to<double>(const StringRange& value, int base);
	template<> float to<float>(const StringRange& value, int base);
	template<> int to<int>(const StringRange& value, int base);
	template<> long to<long>(const StringRange& value, int base);
	template<> short to<short>(const StringRange& value, int base);
	template<> unsigned __int64 to<unsigned __int64>(const StringRange& value, int base);
	template<> unsigned char to<unsigned char>(const StringRange& value, int base);
	template<> unsigned int to<unsigned int>(const StringRange& value, int base);
	template<> unsigned long to<unsigned long>(const StringRange& value, int base);
	template<> unsigned short to<unsigned short>(const StringRange& value, int base);
	/// ���l���� String �ւ̕ϊ��B
	/// base �Ɋ�Ƃ��Ďw��ł���̂� float �� double �̏ꍇ�� 10 �݂̂ŁA����ȊO�� 2, 8, 10, 16�B
	template<> String to<String>(const __int64& value, int base);
	template<> String to<String>(const char& value, int base);
	template<> String to<String>(const double& value, int base);
	template<> String to<String>(const float& value, int base);
	template<> String to<String>(const int& value, int base);
	template<> String to<String>(const long& value, int base);
	template<> String to<String>(const short& value, int base);
	template<> String to<String>(const unsigned __int64& value, int base);
	template<> String to<String>(const unsigned char& value, int base);
	template<> String to<String>(const unsigned int& value, int base);
	template<> String to<String>(const unsigned long& value, int base);
	template<> String to<String>(const unsigned short& value, int base);
	template<> String to<String>(const bool& value, int base);

	/// ���l�𕶎��񉻂��� StringBuffer �֒ǉ�����B
	/// base �Ɋ�Ƃ��Ďw��ł���̂� float �� double �̏ꍇ�� 10 �݂̂ŁA����ȊO�� 2, 8, 10, 16�B
	template<typename Dst, typename Src> void to(StringBuffer& stringBuffer, const Src& value, int base = 10)  { static_assert(false, "Convert type unsupported"); }
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const __int64& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const char& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const double& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const float& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const int& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const long& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const short& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const unsigned __int64& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const unsigned char& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const unsigned int& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const unsigned long& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const unsigned short& value, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const bool& value, int base);

	/// ���l���珑���w�肵�� String �ւ̕ϊ��B
	/// base �Ɋ�Ƃ��Ďw��ł���̂� float �� double �̏ꍇ�� 10 �݂̂ŁA����ȊO�� 8, 10, 16�B
	/// ������ printf �̏�������ŏ��� % �� �Ō�̌^�t�B�[���h���������������́B
	/// �������ASrc �� float �� double �̏ꍇ�͖����Ɍ^�t�B�[���h�����ie, E, f, g, G�j���w��ł���B�w�肵�Ȃ������ꍇ�� g �ƂȂ�B
	/// �Ⴆ�Ή��L�� printf �� "%08x" �Ə����w�肷��̂ɓ������B
	/// <pre><code>
	/// String s = Convert::to<String>(65535, L"08", 16);
	/// </code></pre>
	template<typename Dst, typename Src> Dst to(const Src& value, StringRange format, int base = 10)  { static_assert(false, "Convert type unsupported"); }
	template<> String to<String>(const __int64& value, StringRange format, int base);
	template<> String to<String>(const char& value, StringRange format, int base);
	template<> String to<String>(const double& value, StringRange format, int base);
	template<> String to<String>(const float& value, StringRange format, int base);
	template<> String to<String>(const int& value, StringRange format, int base);
	template<> String to<String>(const long& value, StringRange format, int base);
	template<> String to<String>(const short& value, StringRange format, int base);
	template<> String to<String>(const unsigned __int64& value, StringRange format, int base);
	template<> String to<String>(const unsigned char& value, StringRange format, int base);
	template<> String to<String>(const unsigned int& value, StringRange format, int base);
	template<> String to<String>(const unsigned long& value, StringRange format, int base);
	template<> String to<String>(const unsigned short& value, StringRange format, int base);

	/// ���l���珑���w�肵��������֕ϊ����� StringBuffer �ɒǉ�����B
	/// base �Ɋ�Ƃ��Ďw��ł���̂� float �� double �̏ꍇ�� 10 �݂̂ŁA����ȊO�� 8, 10, 16�B
	/// ������ printf �̏�������ŏ��� % �� �Ō�̌^�t�B�[���h���������������́B
	/// �������ASrc �� float �� double �̏ꍇ�͖����Ɍ^�t�B�[���h�����ie, E, f, g, G�j���w��ł���B�w�肵�Ȃ������ꍇ�� g �ƂȂ�B
	template<typename Dst, typename Src> void to(StringBuffer& stringBuffer, const Src& value, StringRange format, int base = 10)  { static_assert(false, "Convert type unsupported"); }
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const __int64& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const char& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const double& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const float& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const int& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const long& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const short& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const unsigned __int64& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const unsigned char& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const unsigned int& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const unsigned long& value, StringRange format, int base);
	template<> void to<StringBuffer>(StringBuffer& stringBuffer, const unsigned short& value, StringRange format, int base);
}



}