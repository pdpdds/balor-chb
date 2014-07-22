#include <balor/StringRange.hpp>

#include <string>

#include <balor/String.hpp>
#include <balor/test/UnitTest.hpp>


namespace balor {
	namespace testStringRange {


using std::wstring;


namespace {
wstring rangeToString(StringRange range) {
	return range.c_str();
}
} // namespace



testCase(constructAndAccess) {
	{ // asset�e�X�g
		testAssertionFailed(const StringRange range(nullptr));
		testNoThrow        (const StringRange range(L""));
		testAssertionFailed(const StringRange range(nullptr, -1));
		testAssertionFailed(const StringRange range(L"", -2));
		testNoThrow        (const StringRange range(L"", -1));
	}
	{ // �|�C���^��o�[�W����
		const wchar_t* string = L"abc";
		const StringRange range = string;
		testAssert(range == string);
		testAssert(range.rawLength() == -1);
		testAssert(range.length() == 3);
	}
	{ // �T�C�Y�w��o�[�W����
		const wchar_t* string = L"abc";
		const StringRange range(string, 3);
		testAssert(range.c_str() == string);
		testAssert(range.rawLength() == 3);
		testAssert(range.length() == 3);
	}
	{ // �z��o�[�W����
		wchar_t string[5] = L"abc";
		const StringRange range = string;
		testAssert(range.c_str() == string);
		testAssert(range.rawLength() == -1);
		testAssert(range.length() == 3);
	}
	{ // �����񃊃e�����o�[�W����
		const wchar_t string[] = L"abc";
		const StringRange range = string;
		testAssert(range.c_str() == string);
		testAssert(range.rawLength() == -1);
		testAssert(range.length() == 3);
	}
	{ // wstring�o�[�W����
		const wstring string = L"abc";
		const StringRange range = string;
		testAssert(range.c_str() == string.c_str());
		testAssert(range.rawLength() == static_cast<int>(string.length()));
		testAssert(range.length() == static_cast<int>(string.length()));
	}
	{ // String�o�[�W����
		const String string = L"abc";
		const StringRange range = string;
		testAssert(range.c_str() == string.c_str());
		testAssert(range.rawLength() == static_cast<int>(string.length()));
		testAssert(range.length() == static_cast<int>(string.length()));
	}
}


testCase(empty) {
	{ // ��ł͂Ȃ����e����
		const wchar_t* string = L"abc";
		const StringRange range = string;
		testAssert(!range.empty());
	}
	{ // �󃊃e����
		const wchar_t* string = L"";
		const StringRange range = string;
		testAssert(range.empty());
	}
	{ // \0�Ŏn�܂郊�e����
		const wchar_t* string = L"\0abc";
		const StringRange range(string);
		testAssert(range.empty());
	}
	{ // \0�Ŏn�܂郊�e�������T�C�Y�w��ŏ�����
		const wchar_t* string = L"\0abc";
		const StringRange range(string, 4);
		testAssert(range.empty());
	}
	{ // ��wstring
		const wstring string;
		const StringRange range = string;
		testAssert(range.empty());
	}
	{ // \0�Ŏn�܂��ł͂Ȃ�wstring
		const wstring string(L"\0abc", 4);
		const StringRange range = string;
		testAssert(range.empty());
	}
	{ // ��String
		const String string;
		const StringRange range = string;
		testAssert(range.empty());
	}
	{ // \0�Ŏn�܂��ł͂Ȃ�String
		const String string(L"\0abc", 4);
		const StringRange range = string;
		testAssert(range.empty());
	}
}


testCase(length) {
	{ // ��ł͂Ȃ����e����
		const wchar_t* string = L"abc";
		const StringRange range = string;
		testAssert(range.length() == 3);
	}
	{ // �󃊃e����
		const wchar_t* string = L"";
		const StringRange range = string;
		testAssert(range.length() == 0);
	}
	{ // \0�Ŏn�܂郊�e����
		const wchar_t* string = L"\0abc";
		const StringRange range(string);
		testAssert(range.length() == 0);
	}
	{ // \0�Ŏn�܂郊�e�������|�C���^��ŏ�����
		const wchar_t* string = L"\0abc";
		const StringRange range(string, 4);
		testAssert(range.length() == 4);
	}
	{ // ��wstring
		const wstring string;
		const StringRange range = string;
		testAssert(range.length() == 0);
	}
	{ // \0�Ŏn�܂��ł͂Ȃ�wstring
		const wstring string(L"\0abc", 4);
		const StringRange range = string;
		testAssert(range.length() == 4);
	}
	{ // ��String
		const String string;
		const StringRange range = string;
		testAssert(range.length() == 0);
	}
	{ // \0�Ŏn�܂��ł͂Ȃ�String
		const String string(L"\0abc", 4);
		const StringRange range = string;
		testAssert(range.length() == 4);
	}
}


//testCase(rawLength) { // constructAndAccess �Ńe�X�g�ς�
//}


testCase(functionArgument) {
	testAssert(rangeToString(L"abc") == L"abc");
	testAssert(rangeToString(wstring(L"a") + L"bc") == L"abc");
}



	}
}