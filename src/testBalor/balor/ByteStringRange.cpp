#include <balor/StringRange.hpp>

#include <string>

#include <balor/String.hpp>
#include <balor/test/UnitTest.hpp>


namespace balor {
	namespace testByteStringRange {


using std::string;


namespace {
string rangeToString(ByteStringRange range) {
	return range.c_str();
}
} // namespace



testCase(constructAndAccess) {
	{ // asset�e�X�g
		testAssertionFailed(const ByteStringRange range(nullptr));
		testNoThrow        (const ByteStringRange range(""));
		testAssertionFailed(const ByteStringRange range(nullptr, -1));
		testAssertionFailed(const ByteStringRange range("", -2));
		testNoThrow        (const ByteStringRange range("", -1));
	}
	{ // �|�C���^��o�[�W����
		const char* string = "abc";
		const ByteStringRange range = string;
		testAssert(range.c_str() == string);
		testAssert(range.rawLength() == -1);
		testAssert(range.length() == 3);
	}
	{ // �T�C�Y�w��o�[�W����
		const char* string = "abc";
		const ByteStringRange range(string, 3);
		testAssert(range.c_str() == string);
		testAssert(range.rawLength() == 3);
		testAssert(range.length() == 3);
	}
	{ // �z��o�[�W����
		char string[5] = "abc";
		const ByteStringRange range = string;
		testAssert(range.c_str() == string);
		testAssert(range.rawLength() == -1);
		testAssert(range.length() == 3);
	}
	{ // �����񃊃e�����o�[�W����
		const char string[] = "abc";
		const ByteStringRange range = string;
		testAssert(range.c_str() == string);
		testAssert(range.rawLength() == -1);
		testAssert(range.length() == 3);
	}
	{ // string�o�[�W����
		const string string = "abc";
		const ByteStringRange range = string;
		testAssert(range.c_str() == string.c_str());
		testAssert(range.rawLength() == static_cast<int>(string.length()));
		testAssert(range.length() == static_cast<int>(string.length()));
	}
}


testCase(empty) {
	{ // ��ł͂Ȃ����e����
		const char* string = "abc";
		const ByteStringRange range = string;
		testAssert(!range.empty());
	}
	{ // �󃊃e����
		const char* string = "";
		const ByteStringRange range = string;
		testAssert(range.empty());
	}
	{ // \0�Ŏn�܂郊�e����
		const char* string = "\0abc";
		const ByteStringRange range(string);
		testAssert(range.empty());
	}
	{ // \0�Ŏn�܂郊�e�������T�C�Y�w��ŏ�����
		const char* string = "\0abc";
		const ByteStringRange range(string, 4);
		testAssert(range.empty());
	}
	{ // ��string
		const string string;
		const ByteStringRange range = string;
		testAssert(range.empty());
	}
	{ // \0�Ŏn�܂��ł͂Ȃ�string
		const string string("\0abc", 4);
		const ByteStringRange range = string;
		testAssert(range.empty());
	}
}


testCase(length) {
	{ // ��ł͂Ȃ����e����
		const char* string = "abc";
		const ByteStringRange range = string;
		testAssert(range.length() == 3);
	}
	{ // �󃊃e����
		const char* string = "";
		const ByteStringRange range = string;
		testAssert(range.length() == 0);
	}
	{ // \0�Ŏn�܂郊�e����
		const char* string = "\0abc";
		const ByteStringRange range(string);
		testAssert(range.length() == 0);
	}
	{ // \0�Ŏn�܂郊�e�������T�C�Y�w��ŏ�����
		const char* string = "\0abc";
		const ByteStringRange range(string, 4);
		testAssert(range.length() == 4);
	}
	{ // ��string
		const string string;
		const ByteStringRange range = string;
		testAssert(range.length() == 0);
	}
	{ // \0�Ŏn�܂��ł͂Ȃ�string
		const string string("\0abc", 4);
		const ByteStringRange range = string;
		testAssert(range.length() == 4);
	}
}


//testCase(rawLength) { // constructAndAccess �Ńe�X�g�ς�
//}


testCase(functionArgument) {
	testAssert(rangeToString("abc") == "abc");
	testAssert(rangeToString(string("a") + "bc") == "abc");
}



	}
}