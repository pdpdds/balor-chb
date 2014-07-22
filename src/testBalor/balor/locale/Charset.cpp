#include <balor/locale/Charset.hpp>

#include <boost/thread.hpp>
#include <MLang.h>

#include <balor/io/MemoryStream.hpp>
#include <balor/io/Resource.hpp>
#include <balor/system/Com.hpp>
#include <balor/system/ComPtr.hpp>
#include <balor/system/windows.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/String.hpp>


namespace balor {
	namespace locale {
		namespace testCharset {


using std::move;
using std::string;
using std::vector;
using boost::thread;
using namespace balor::io;
using namespace balor::system;


namespace {
const wchar_t testString[] = L"+-\\\\@~012abcABC����{�|���`���O�P�Q�������`�a�b�A�C�E����������";


string getResourceString(const wchar_t* name) {
	auto stream = Resource().getRawData(String::literal(L"balor::locale::charset::") + name);
	string result(static_cast<int>(stream.length()), '\0');
	stream.read(&result[0], 0, result.length());
	return move(result);
}
} // namespace



testCase(startup) { // �n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������i�ꌩ���[�N�Ɍ�����j�֐������炩���ߌĂ�ł���
	balor::test::UnitTest::ignoreHandleLeakCheck();

	Com::initialize(); // CoInitializeEx �֐��̓n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������
	{
		ComPtr<IMultiLanguage2> ptr(CLSID_CMultiLanguage); // CoCreateInstance �֐��̓n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������
	}
	Com::uninitialize();

	testAssert(SUCCEEDED(CoInitialize(nullptr))); // CoInitialize �֐��̓n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������
	CoUninitialize();

	IsValidCodePage(0); // IsValidCodePage �֐��̓n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������
}


testCase(ComInitialize) { // COM�������R�[�h�Ƃ̋����B���ɂ�₱�����A�ǂ��ɂ��Ȃ�Ȃ����̂�
	testAssert(!Com::initialized()); // ���������̂͂�

	{// Charset ���b�n�l���g�p���Ȃ��p�^�[��
		{
			Charset charset = Charset::default();
			testAssert(charset.encode(L"abc") == "abc");
			testAssert(charset.decode("abc") == L"abc");
		}
		testAssert(!Com::initialized());
	}
	{// Charset ���b�n�l������������
		{
			Charset charset(1200);
			testAssert(charset.name() == L"unicode");
		}
		testAssert(Com::initialized());
		Com::uninitialize();
	}
	{// �b�n�l���l�s�`�ŏ��������Ă�����Charset���g�p����
		Com::initialize(false);
		{
			Charset charset(1200);
			testAssert(charset.name() == L"unicode");
		}
		Com::uninitialize();
	}
	{// �b�n�l���r�s�`�ŏ��������Ă�����Charset���g�p����
		Com::initialize();
		{
			Charset charset(1200);
			testAssert(charset.name() == L"unicode");
		}
		Com::uninitialize();
	}
	{// �b�n�l���l�s�`�ŏ��������Ă����ĕʃX���b�h��Charset���g�p����
		Com::initialize(false);
		thread workor([] () {
			Charset charset(1200);
			testAssert(charset.name() == L"unicode");
		});
		workor.join();
		Com::uninitialize();
	}
	{// �b�n�l���r�s�`�ŏ��������Ă����ĕʃX���b�h�� STA �� Charset ���g�p����B
		Com::initialize();
		thread workor([] () {
			{
				testThrow(Charset charset(1200), Com::UninitializedException);
				Com::initialize();
				Charset charset(1200);
				testAssert(charset.name() == L"unicode");
			}
			Com::uninitialize();
		});
		workor.join();
		Com::uninitialize();
	}
	{// Charset ���ʃX���b�h��MTA �� �b�n�l������������B
		thread work([] () {
			Com::initialize(false);
			{
				Charset charset(1200);
				testAssert(charset.name() == L"unicode");
			}
			Com::uninitialize();
		});
		work.join();
		testNoThrow(Charset charset(1200));
		testAssert(Com::initialized());
		Com::uninitialize();
	}
}


testCase(secondStartup) { // �n���h�����[�N�`�F�b�N�Ɉ���������Ȃ��悤�ɂ��炩���߂b�n�l�̏����������܂��Ă���
	balor::test::UnitTest::ignoreHandleLeakCheck();
	Charset charset(932);
	Charset::charsets(); // IEnumCodePage->Next �֐��̓n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������
}


testCase(codePageAndIsWindowsCodePageConstruct) {
	// �����ȃp�����[�^
	testAssertionFailed(Charset(-1));
	testAssertionFailed(Charset(65536));

	{// isWindowsCodePage = true �ł���Ȃ��� windows �̃R�[�h�y�[�W�ł͂Ȃ�
		testAssertionFailed(Charset(51932, true));
		testNoThrow(Charset(932, true));
	}

	{// mlang �̃T�|�[�g�͈͊O�̃R�[�h�y�[�W
		testThrow(Charset(7777), Charset::NotFoundException);
		testThrow(Charset(1), Charset::NotFoundException);
		testNoThrow(Charset(51932));
	}

	{// ����P�[�X 1
		Charset shift_jis(932, true);
		testAssert(shift_jis.codePage() == 932);
		testAssert(shift_jis.name() == L"shift_jis");
		testAssert(shift_jis.fallbackChar() == L'?');
		testAssert(!shift_jis.throwable());
	}
	{// ����P�[�X 2
		Charset big5(950);
		testAssert(big5.codePage() == 950);
		testAssert(big5.name() == L"big5");
	}
}


testCase(nameConstruct) {
	{// �����ȃG���R�[�f�B���O��
		testThrow(Charset(L"unknowncode"), Charset::NotFoundException);
	}

	{// ����P�[�X
		Charset euc_jp(L"euc-jp");
		testAssert(euc_jp.codePage() == 51932);
		testAssert(euc_jp.name() == L"euc-jp");
		testAssert(euc_jp.fallbackChar() == L'?');
		testAssert(!euc_jp.throwable());
		Charset utf8(L"utf-8");
		testAssert(utf8.codePage() == 65001);
		testAssert(utf8.name() == L"utf-8");
	}
}


testCase(rvalueConstruct) {
	Charset source(20127);
	source.fallbackChar(L'*');
	source.throwable(true);
	Charset charset = move(source);
	testAssert(charset.codePage() == 20127);
	testAssert(charset.fallbackChar() == L'*');
	testAssert(charset.throwable());
	testAssert(charset.name() == L"us-ascii");
}


testCase(rvalueAssignment) {
	Charset source(1200);
	source.fallbackChar(L'*');
	source.throwable(true);
	Charset charset = Charset::default();
	charset = move(source);
	testAssert(charset.codePage() == 1200);
	testAssert(charset.fallbackChar() == L'*');
	testAssert(charset.throwable());
	testAssert(charset.name() == L"unicode");
}


testCase(ascii) {
	Charset charset = Charset::ascii();
	testAssert(charset.codePage() == 20127);
	testAssert(charset.displayName() == L"US-ASCII");
	testAssert(charset.fallbackChar() == L'?');
	testAssert(charset.throwable() == false);
	testAssert(charset.name() == L"us-ascii");

	String testString = L"abc012�`�a�b�O�P�Q����������";
	string bytes;
	testAssert((bytes = charset.encode(testString)) == "abc012ABC012?????");
	testAssert(charset.decode(bytes) == L"abc012ABC012?????");
	charset = Charset(charset.codePage(), true);
	testAssert((bytes = charset.encode(testString)) == "abc012???????????");
	testAssert(charset.decode(bytes) == L"abc012???????????");
}


testCase(bigEndianUnicode) {
	Charset charset = Charset::bigEndianUnicode();
	testAssert(charset.codePage() == 1201);
	testAssert(charset.displayName() == L"Unicode (�r�b�O �G���f�B�A��)" // .NET�� Unicode (Big-Endian)
			|| charset.displayName() == L"Unicode (Big-Endian)"); // �����XP�̕\�L
	testAssert(charset.fallbackChar() == L'?');
	testAssert(charset.throwable() == false);
	testAssert(charset.name() == L"unicodeFEFF" // .NET�� "utf-16BE"
			|| charset.name() == L"unicodeFFFE"); // �����XP�̕\�L

	string temp = charset.encode(ByteStringRange(reinterpret_cast<const char*>(testString), String::getLength(testString) * sizeof(wchar_t)), Charset::unicode());
	temp        = Charset::unicode().encode(temp, charset);
	String result(reinterpret_cast<const wchar_t*>(temp.c_str()), temp.length() / sizeof(wchar_t));
	testAssert(result == testString);
}


testCase(charsets) {
	vector<Charset> charsets;
	testNoThrow(charsets = Charset::charsets());
	testAssert(!charsets.empty());
	for (auto i = charsets.begin(), end = charsets.end(); i != end; ++i) {
		auto name = i->name();
		//i->encode(L"abc");
		i->decode("abc");
	}
}


//testCase(codePage) {} // �e�G���R�[�f�B���O�擾��static�֐��� testCase �Ńe�X�g�ς�


testCase(decode) {
	{// �����ȃp�����[�^
		Charset charset(932);
		testAssertionFailed(charset.decode("012", -1));
		testAssertionFailed(charset.decode("012",  4));
		testNoThrow        (charset.decode("012",  3));
		wchar_t buffer[4];
		testAssertionFailed(charset.decode("012", -1, buffer));
		testAssertionFailed(charset.decode("012",  4, buffer));
		testAssertionFailed(charset.decode("012",  3, ArrayRange<wchar_t>(buffer, 0)));
		//testAssertionFailed(Charset::bigEndianUnicode().decode("012",  3, buffer));
		//testAssertionFailed(Charset::unicode().decode("012",  3, buffer));
		testNoThrow        (charset.decode("012",  3, buffer));
	}
	{// �o�b�t�@�̒���������Ȃ��iWindowsCode�Łj
		Charset charset(932, true);
		wchar_t buffer[3];
		testThrow  (charset.decode("012", 3, buffer), Charset::InsufficientBufferExceptoin);
		testNoThrow(charset.decode("012", 2, buffer));
	}
	{// �o�b�t�@�̒���������Ȃ�
		Charset charset(932);
		wchar_t buffer[3];
		testThrow  (charset.decode("012", 3, buffer), Charset::InsufficientBufferExceptoin);
		testNoThrow(charset.decode("012", 2, buffer));
	}
	{// ����P�[�X 1�iWindowsCode�Łj
		Charset charset(932, true);
		string srcString = getResourceString(L"shift_jis.txt");
		testAssert(charset.decode(srcString) == testString);
	}
	{// ����P�[�X 1
		Charset charset(L"shift_jis");
		string srcBytes = getResourceString(L"shift_jis.txt");
		testAssert(charset.decode(srcBytes) == testString);
	}
	{// ����P�[�X 2�@�󕶎��iWindowsCode��)
		Charset charset(932, true);
		testAssert(charset.decode("") == L"");
		testAssert(charset.decode("", 0) == L"");
		wchar_t buffer[1];
		testAssert(charset.decode("", 0, buffer) == 0);
		testAssert(buffer == String());
	}
	{// ����P�[�X 2�@�󕶎�
		Charset charset(L"euc-jp");
		testAssert(charset.decode("") == L"");
		testAssert(charset.decode("", 0) == L"");
		wchar_t buffer[1];
		testAssert(charset.decode("", 0, buffer) == 0);
		testAssert(buffer == String());
	}
	{// ����P�[�X 3�iWindowsCode�Łj
		Charset charset(932, true);
		string srcBytes = getResourceString(L"shift_jis.txt");
		testAssert(charset.decode(srcBytes, 15) == String(testString, 15));
	}
	{// ����P�[�X 3
		Charset charset(L"us-ascii");
		string srcBytes = getResourceString(L"shift_jis.txt");
		testAssert(charset.decode(srcBytes, 15) == String(testString, 15));
	}
	{// ����P�[�X 4�iWindowsCode�Łj
		Charset charset(65001, true);
		string srcBytes = getResourceString(L"utf-8.txt");
		wchar_t buffer[41];
		testAssert(charset.decode(srcBytes, srcBytes.length(), buffer) == 40);
		testAssert(buffer == String(testString));
	}
	{// ����P�[�X 4
		Charset charset(L"utf-8");
		string srcBytes = getResourceString(L"utf-8.txt");
		wchar_t buffer[41];
		testAssert(charset.decode(srcBytes, srcBytes.length(), buffer) == 40);
		testAssert(buffer == String(testString));
	}
}


testCase(default) {
	Charset charset = Charset::default(); // Here is Japan!!
	testAssert(charset.codePage() == 932);
	testAssert(charset.displayName() == L"���{�� (�V�t�g JIS)");
	testAssert(charset.fallbackChar() == L'?');
	testAssert(charset.throwable() == false);
	testAssert(charset.name() == L"shift_jis");

	string bytes = getResourceString(L"shift_jis.txt");
	testAssert(charset.encode(testString) == bytes);
	testAssert(charset.decode(bytes) == testString);
	charset = Charset(charset.codePage(), true);
	testAssert(charset.encode(testString) == bytes);
	testAssert(charset.decode(bytes) == testString);
}


//testCase(displayName) {} // �e�G���R�[�f�B���O�擾��static�֐��� testCase �Ńe�X�g�ς�


testCase(encodeFromByteString) {
	{// �����ȃp�����[�^
		Charset src(932);
		Charset dst(51932);
		testAssertionFailed(dst.encode("012", -1, src));
		testAssertionFailed(dst.encode("012",  4, src));
		testNoThrow        (dst.encode("012",  3, src));
		char buffer[4];
		testAssertionFailed(dst.encode("012", -1, buffer, src));
		testAssertionFailed(dst.encode("012",  4, buffer, src));
		testAssertionFailed(dst.encode("012",  3, ArrayRange<char>(buffer, 0), src));
		testNoThrow        (dst.encode("012",  3, buffer, src));
	}
	{// �o�b�t�@�̒���������Ȃ�
		Charset src(932);
		Charset dst(51932);
		char buffer[3];
		testThrow  (dst.encode("012", 3, buffer, src), Charset::InsufficientBufferExceptoin);
		testNoThrow(dst.encode("012", 2, buffer, src));
	}
	{// �s���ȕ����̋�؂�i��؂ꂽ�����͖����j
		Charset src(L"shift_jis");
		Charset dst(L"euc-jp");
		char shift_jisBytes[] = "����";
		src.throwable(true);
		string temp = dst.encode(shift_jisBytes, 3, src);
		testAssert(temp.length() == 2);
		testAssert(src.encode(temp, dst) == "��");
	}
	{// ����P�[�X 1
		Charset src(L"shift_jis");
		Charset dst(L"utf-8");
		string srcBytes = getResourceString(L"shift_jis.txt");
		string dstBytes = getResourceString(L"utf-8.txt");
		testAssert(srcBytes != dstBytes);
		testAssert(dst.encode(srcBytes, src) == dstBytes);
	}
	{// ����P�[�X 2�@�󕶎�
		Charset src(L"shift_jis");
		Charset dst(L"euc-jp");
		testAssert(dst.encode("", src) == "");
		testAssert(dst.encode("", 0, src) == "");
		char buffer[1];
		testAssert(dst.encode("", 0, buffer, src) == 0);
		testAssert(buffer == string());
	}
	{// ����P�[�X 3�i���ڕϊ��̓T�|�[�g����Ȃ���unicode����ĕϊ��j
		Charset src(L"iso-2022-jp");
		Charset dst(L"euc-jp");
		string srcBytes = getResourceString(L"jis.txt");
		string dstBytes = getResourceString(L"euc-jp.txt");
		testAssert(srcBytes != dstBytes);
		testAssert(dst.encode(srcBytes, 10, src) == string(dstBytes.begin(), dstBytes.begin() + 10));
	}
	{// ����P�[�X 4�iunicode�����fallback�����j
		Charset src(L"shift_jis");
		Charset dst(L"us-ascii");
		char buffer[4];
		testAssert(dst.encode("a����", 5, buffer, src) == 3);
		testAssert(buffer == string("a??"));
	}
	{// ����P�[�X 5 Unicode�̍��������ϊ�
		Charset src(L"shift_jis");
		Charset dst = Charset::unicode();
		string temp = dst.encode("abc������", src);
		String result(reinterpret_cast<const wchar_t*>(temp.c_str()), temp.length() / sizeof(wchar_t));
		testAssert(result == L"abc������");
	}
	{// ����P�[�X 6 Unicode�̍��������ϊ�
		Charset src = Charset::unicode();
		Charset dst(L"shift_jis");
		String srcChars = L"abc������";
		testAssert(dst.encode(ByteStringRange(reinterpret_cast<const char*>(srcChars.c_str()), srcChars.length() * sizeof(wchar_t)), src) == "abc������");
	}
	{// ����P�[�X 7 Unicode�̍��������ϊ�
		Charset src = Charset::unicode();
		Charset dst = Charset::unicode();
		String srcChars = L"abc������";
		string temp = dst.encode(ByteStringRange(reinterpret_cast<const char*>(srcChars.c_str()), srcChars.length() * sizeof(wchar_t)), src);
		String result(reinterpret_cast<const wchar_t*>(temp.c_str()), temp.length() / sizeof(wchar_t));
		testAssert(result == srcChars);
	}
}


testCase(encode) {
	{// �����ȃp�����[�^
		Charset charset(932);
		testAssertionFailed(charset.encode(L"012", -1));
		testAssertionFailed(charset.encode(L"012",  4));
		testNoThrow        (charset.encode(L"012",  3));
		char buffer[4];
		testAssertionFailed(charset.encode(L"012", -1, buffer));
		testAssertionFailed(charset.encode(L"012",  4, buffer));
		testAssertionFailed(charset.encode(L"012",  3, ArrayRange<char>(buffer, 0)));
		//testAssertionFailed(Charset::bigEndianUnicode().encode(L"012",  3, buffer));
		//testAssertionFailed(Charset::unicode().encode(L"012",  3, buffer));
		testNoThrow        (charset.encode(L"012",  3, buffer));
	}
	{// �o�b�t�@�̒���������Ȃ��iWindowsCode�Łj
		Charset charset(932, true);
		char buffer[3];
		testThrow  (charset.encode(L"012", 3, buffer), Charset::InsufficientBufferExceptoin);
		testNoThrow(charset.encode(L"012", 2, buffer));
	}
	{// �o�b�t�@�̒���������Ȃ�
		Charset charset(932);
		char buffer[3];
		testThrow  (charset.encode(L"012", 3, buffer), Charset::InsufficientBufferExceptoin);
		testNoThrow(charset.encode(L"012", 2, buffer));
	}
	{// ����P�[�X 1�iWindowsCode�Łj
		Charset charset(932, true);
		string resultBytes = getResourceString(L"shift_jis.txt");
		testAssert(charset.encode(testString) == resultBytes);
	}
	{// ����P�[�X 1
		Charset charset(L"shift_jis");
		string resultBytes = getResourceString(L"shift_jis.txt");
		testAssert(charset.encode(testString) == resultBytes);
	}
	{// ����P�[�X 2�@�󕶎��iWindowsCode��)
		Charset charset(932, true);
		testAssert(charset.encode(L"") == "");
		testAssert(charset.encode(L"", 0) == "");
		char buffer[1];
		testAssert(charset.encode(L"", 0, buffer) == 0);
		testAssert(buffer == string());
	}
	{// ����P�[�X 2�@�󕶎�
		Charset charset(L"euc-jp");
		testAssert(charset.encode(L"") == "");
		testAssert(charset.encode(L"", 0) == "");
		char buffer[1];
		testAssert(charset.encode(L"", 0, buffer) == 0);
		testAssert(buffer == string());
	}
	{// ����P�[�X 3�iWindowsCode�Łj
		Charset charset(932, true);
		string resultBytes = getResourceString(L"shift_jis.txt");
		testAssert(charset.encode(testString, 15) == string(resultBytes.begin(), resultBytes.begin() + 15));
	}
	{// ����P�[�X 3
		Charset charset(L"us-ascii");
		string resultBytes = getResourceString(L"shift_jis.txt");
		testAssert(charset.encode(testString, 15) == string(resultBytes.begin(), resultBytes.begin() + 15));
	}
	{// ����P�[�X 4�iWindowsCode�Łj
		Charset charset(65001, true);
		string resultBytes = getResourceString(L"utf-8.txt");
		char buffer[91];
		testAssert(charset.encode(testString, String::getLength(testString), buffer) == 90);
		testAssert(buffer == resultBytes);
	}
	{// ����P�[�X 4
		Charset charset(L"utf-8");
		string resultBytes = getResourceString(L"utf-8.txt");
		char buffer[91];
		testAssert(charset.encode(testString, String::getLength(testString), buffer) == 90);
		testAssert(buffer == resultBytes);
	}
	{// ����P�[�X 5 fallback�iWindowsCode�Łj
		Charset charset(20127, true);
		String testString = L"abc012�`�a�b�O�P�Q����������";
		testAssert(charset.encode(testString) == "abc012???????????");
		charset.fallbackChar(L'+');
		testAssert(charset.fallbackChar() == L'+');
		testAssert(charset.encode(testString) == "abc012+++++++++++");
		charset.throwable(true);
		testAssert(charset.throwable() == true);
		testThrow(charset.encode(testString), Charset::ConversionFailedException);
		testNoThrow(charset.encode(testString, 6));
	}
	{// ����P�[�X 5 fallback
		Charset charset(L"us-ascii");
		String testString = L"abc012�`�a�b�O�P�Q����������";
		testAssert(charset.encode(testString) == "abc012ABC012?????"); // mlang�̂ق��������\�I
		charset.fallbackChar(L'+');
		testAssert(charset.fallbackChar() == L'+');
		testAssert(charset.encode(testString) == "abc012ABC012+++++");
		charset.throwable(true);
		testAssert(charset.throwable() == true);
		testThrow(charset.encode(testString), Charset::ConversionFailedException);
		testNoThrow(charset.encode(testString, 12));
	}
}


testCase(eucJp) {
	Charset charset(L"euc-jp");
	testAssert(charset.codePage() == 51932);
	testAssert(charset.displayName() == L"���{�� (EUC)");
	testAssert(charset.fallbackChar() == L'?');
	testAssert(charset.throwable() == false);
	testAssert(charset.name() == L"euc-jp");

	string bytes = getResourceString(L"euc-jp.txt");
	testAssert(charset.encode(testString) == bytes);
	testAssert(charset.decode(bytes) == testString);
	testAssertionFailed(Charset(charset.codePage(), true));
}


//testCase(fallbackChar) {} // testCase(encode) �Ńe�X�g�ς�


//testCase(name) {} // �e�G���R�[�f�B���O�擾��static�֐��� testCase �Ńe�X�g�ς�

//testCase(shiftJis) {} // testCase(default) �Ńe�X�g�ς�

//testCase(throwable) {} // testCase(encode) �Ńe�X�g�ς�


testCase(unicode) {
	Charset charset = Charset::unicode();
	testAssert(charset.codePage() == 1200);
	testAssert(charset.displayName() == L"Unicode"); // .NET�� Unicode
	testAssert(charset.fallbackChar() == L'?');
	testAssert(charset.throwable() == false);
	testAssert(charset.name() == L"unicode"); // .NET�� "utf-16"

	string temp = charset.encode(L"abc");
	testAssert(charset.decode(temp) == L"abc");
	testAssertionFailed(Charset(charset.codePage(), true)); // 1200��windowsCodePage�Ƃ��Ă͕s���Ȗ͗l
}


testCase(utf7) {
	Charset charset = Charset::utf7();
	testAssert(charset.codePage() == 65000);
	testAssert(charset.displayName() == L"Unicode (UTF-7)");
	testAssert(charset.fallbackChar() == L'?');
	testAssert(charset.throwable() == false);
	testAssert(charset.name() == L"utf-7");

	string bytes = getResourceString(L"utf-7.txt");
	testAssert(charset.encode(testString) == bytes);
	testAssert(charset.decode(bytes) == testString);
	charset = Charset(charset.codePage(), true);
	testAssert(charset.encode(testString) == bytes);
	testAssert(charset.decode(bytes) == testString);
}


testCase(utf8) {
	Charset charset = Charset::utf8();
	testAssert(charset.codePage() == 65001);
	testAssert(charset.displayName() == L"Unicode (UTF-8)");
	testAssert(charset.fallbackChar() == L'?');
	testAssert(charset.throwable() == false);
	testAssert(charset.name() == L"utf-8");

	string bytes = getResourceString(L"utf-8.txt");
	testAssert(charset.encode(testString) == bytes);
	testAssert(charset.decode(bytes) == testString);
	charset = Charset(charset.codePage(), true);
	testAssert(charset.encode(testString) == bytes);
	testAssert(charset.decode(bytes) == testString);
}


testCase(jis) { // �I�}�P�̃e�X�g�P�[�X
	Charset charset(L"csISO2022JP");
	//Charset charset(L"iso-2022-jp"); // ����������50220�̂ق��ɂȂ�
	testAssert(charset.codePage() == 50221);
	testAssert(charset.displayName() == L"���{�� (JIS 1 �o�C�g �J�^�J�i��)");
	testAssert(charset.fallbackChar() == L'?');
	testAssert(charset.throwable() == false);
	testAssert(charset.name() == L"csISO2022JP");

	string bytes = getResourceString(L"jis.txt");
	testAssert(charset.encode(testString) == bytes);
	testAssert(charset.decode(bytes) == testString);
	charset = Charset(charset.codePage(), true); // windowsCodePage �Ƃ��Ă͐������悤����
	testAssertionFailed(charset.encode(testString)); // �ϊ��ɂ͎��s����B�Ȃ���
	testAssert(charset.decode(bytes) != String(testString)); // �S�p�u�|�v�𔼊p�u-�v�ɕϊ����Ă���B�ǂ�������������
}


testCase(cleanup) { // �b�n�l�̊J��
	Com::uninitialize();
}



		}
	}
}