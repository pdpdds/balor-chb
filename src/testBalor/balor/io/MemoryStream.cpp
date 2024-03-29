﻿#include <balor/io/MemoryStream.hpp>

#include <limits>
#include <utility>

#include <balor/test/UnitTest.hpp>
#include <balor/String.hpp>


namespace balor {
	namespace io {
		namespace testMemoryStream {


using std::move;
using namespace balor::io;



testCase(construct) {
	{// 기본 생성자
		MemoryStream stream;
		testAssert(stream.capacity() == 256);
		testAssert(stream.length() == 0);
		testAssert(stream.position() == 0);
		testAssert(stream.readable());
		testAssert(stream.writable());
		stream.length(512);
		testAssert(stream.length() == 512);
		testAssert(stream.buffer() != nullptr);
	}
	{// 캐파시티 설정
		// 무효한 파라미터
		testAssertionFailed(MemoryStream(0));
		testNoThrow        (MemoryStream(1));

		MemoryStream stream(16);
		testAssert(stream.capacity() == 16);
		testAssert(stream.length() == 0);
		testAssert(stream.position() == 0);
		testAssert(stream.readable());
		testAssert(stream.writable());
		stream.length(512);
		testAssert(stream.length() == 512);
		testAssert(stream.buffer() != nullptr);
	}
	{// 메모리 배열 지정
		wchar_t buffer[5] = L"0123";

		{
			MemoryStream stream(buffer);
			testAssert(stream.capacity() == 10);
			testAssert(stream.length() == 10);
			testAssert(stream.position() == 0);
			testAssert(stream.readable());
			testAssert(stream.writable());
			testAssertionFailed(stream.length(11));
			testAssert(stream.buffer() == buffer);
		}
		{
			MemoryStream stream(buffer, false);
			testAssert(stream.capacity() == 10);
			testAssert(stream.length() == 10);
			testAssert(stream.position() == 0);
			testAssert(stream.readable());
			testAssert(!stream.writable());
			testAssertionFailed(stream.length(11));
			testAssert(stream.buffer() == buffer);
		}
	}
	{// 메모리 포인터 지정 
		char buffer[5] = "0123";

		// 무효한 파라미터
		testAssertionFailed(MemoryStream(nullptr, 0, 4));
		testAssertionFailed(MemoryStream(buffer, -1, 4));
		testAssertionFailed(MemoryStream(buffer, 0, -1));
		testAssertionFailed(MemoryStream("0123", 0, 4));
		testNoThrow        (MemoryStream(buffer, 0, 0));
		{
			MemoryStream stream(buffer, 0, 4);
			testAssert(stream.capacity() == 4);
			testAssert(stream.length() == 4);
			testAssert(stream.position() == 0);
			testAssert(stream.readable());
			testAssert(stream.writable());
			testAssertionFailed(stream.length(5));
			testAssert(stream.buffer() == buffer);
		}
		{
			MemoryStream stream(buffer, 1, 2, false);
			testAssert(stream.capacity() == 2);
			testAssert(stream.length() == 2);
			testAssert(stream.position() == 0);
			testAssert(stream.readable());
			testAssert(!stream.writable());
			testAssertionFailed(stream.length(5));
			testAssert(stream.buffer() == (buffer + 1));
		}
	}
}


testCase(moveConstructAndAssignment) {
	char buffer[] = "0123";

	MemoryStream stream0(buffer, 0, 4);
	stream0.length(3);
	stream0.position(1);
	
	// move construct
	MemoryStream stream1 = move(stream0);
	testAssert(stream0.buffer() == nullptr);
	testAssert(stream1.buffer() == buffer);
	testAssert(stream0.capacity() == 0);
	testAssert(stream1.capacity() == 4);
	testAssert(stream0.length() == 0);
	testAssert(stream1.length() == 3);
	testAssert(stream0.position() == 0);
	testAssert(stream1.position() == 1);
	testAssert(stream1.writable());
	testAssertionFailed(stream1.length(5));

	MemoryStream stream2(buffer, 0, 4, false);
	MemoryStream stream3 = move(stream2);
	testAssert(!stream3.writable());

	// move assignment
	MemoryStream stream4(buffer, 0, 4);
	stream4.position(1);
	MemoryStream stream5;
	void* stream5Buffer = stream5.buffer();
	MemoryStream& result = stream5 = move(stream4);
	testAssert(&result == &stream5);
	testAssert(stream4.buffer() == stream5Buffer);
	testAssert(stream5.buffer() == buffer);
	testAssert(stream4.capacity() == 256);
	testAssert(stream5.capacity() == 4);
	testAssert(stream4.length() == 0);
	testAssert(stream5.length() == 4);
	testAssert(stream4.position() == 0);
	testAssert(stream5.position() == 1);
	testAssert(stream4.writable());
	testAssert(stream5.writable());
	testAssertionFailed(stream5.length(5));
	
	MemoryStream stream6(buffer, 0, 4, false);
	MemoryStream stream7;
	stream7 = move(stream6);
	testAssert(stream6.writable());
	testAssert(!stream7.writable());
}


testCase(buffer) {
	char buffer[4] = {0};
	MemoryStream stream(buffer, 0, 4);
	const MemoryStream& constStream = stream;
	testAssert(constStream.buffer() == buffer);

	// 나머지 케이스는 testCase(construct) 에서 완료
}


//testCase(capacity) { // testCase(length) 에서 테스트 완료
//}


testCase(flush) {
	testNoThrow(MemoryStream().flush());
}


testCase(length) {
	char source[5] = "0123";
	MemoryStream stream0(source, 0, 4);
	MemoryStream stream1 = move(stream0);
	MemoryStream stream2(source, 0, 4, false);
	MemoryStream stream3(4);

	// 무효한 파라미터
	testAssertionFailed(stream0.length(0));
	testAssertionFailed(stream1.length(-1));
	testNoThrow        (stream1.length(0));
	testAssertionFailed(stream2.length(0));

	// 사이즈 변경
	testAssert(stream1.length() == 0);
	stream1.length(2);
	testAssert(stream1.length() == 2);
	stream1.length(4);
	testAssert(stream1.length() == 4);
	testAssertionFailed(stream1.length(5));

	// 캐파시티 변경을 따르는 사이즈 변경
	testAssert(stream3.capacity() == 4);
	testAssert(stream3.length() == 0);
	stream3.write("0123", 0, 4);
	testAssert(stream3.position() == 4);
	stream3.length(16);
	testAssert(stream3.capacity() == 16);
	testAssert(stream3.length() == 16);
	testAssert(stream3.position() == 4);
	stream3.position(0);
	char buffer[5] = {0};
	stream3.read(buffer, 0, 4);
	testAssert(String::equals(buffer, "0123"));
}


testCase(position) {
	char source[5] = "0123";
	MemoryStream stream0(source, 0, 4);
	MemoryStream stream1 = move(stream0);

	// 무효한 파라미터
	testAssertionFailed(stream0.position(1));
	testAssertionFailed(stream1.position(-1));
	testAssertionFailed(stream1.position(std::numeric_limits<int>::max() + static_cast<__int64>(1)));
	testNoThrow        (stream1.position(std::numeric_limits<int>::max()));

	// seek 테스트
	char buffer[2] = {0};
	stream1.position(1);
	testAssert(stream1.position() == 1);
	stream1.read(buffer, 0, 1);
	testAssert(buffer[0] == L'1');
	testAssert(stream1.position() == 2);

	// 범위 외에 seek
	stream1.position(5);
	testAssert(stream1.position() == 5);
	testAssert(stream1.length() == 4);
	stream1.position(4);
	testAssert(stream1.read(buffer, 0, 1) == 0);
}


testCase(read) {
	char source[5] = "0123";
	MemoryStream stream0(source, 0, 4);
	MemoryStream stream1 = move(stream0);

	// 무효한 파라미터
	char buffer[5] = {0};
	testAssertionFailed(stream0.read(buffer, 0, 4));
	testAssertionFailed(stream1.read(nullptr, 0, 4));
	testAssertionFailed(stream1.read(buffer, -1, 4));
	testAssertionFailed(stream1.read(buffer, 0, -1));
	testAssertionFailed(stream1.read("abcd", 0, 4));
	testNoThrow        (stream1.read(buffer, 0, 0));

	// 읽기
	testAssert(stream1.read(buffer, 0, 4) == 4);
	testAssert(stream1.position() == 4);
	testAssert(String::equals(buffer, "0123"));
	stream1.position(0);
	testAssert(stream1.read(buffer, 0, 0) == 0);
	testAssert(stream1.position() == 0);
	testAssert(String::equals(buffer, "0123"));
	stream1.position(0);
	testAssert(stream1.read(buffer, 1, 2) == 2);
	testAssert(stream1.position() == 2);
	testAssert(String::equals(buffer, "0013"));
	testAssert(stream1.read(buffer, 1, 0) == 0);
	testAssert(stream1.position() == 2);
	testAssert(String::equals(buffer, "0013"));

	// 범위 외 읽기
	testAssert(stream1.read(buffer, 0, 4) == 2);
	testAssert(stream1.position() == 4);
	testAssert(String::equals(buffer, "2313"));

	testAssert(stream1.read(buffer, 0, 1) == 0);
	testAssert(stream1.position() == 4);
	testAssert(String::equals(buffer, "2313"));
}


//testCase(readable) { // testCase(construct) 에서 테스트 완료
//}


testCase(skip) {
	char source[5] = "0123";
	MemoryStream stream0(source, 0, 4);
	MemoryStream stream1 = move(stream0);

	// 무효한 파라미터
	testAssertionFailed(stream0.skip(1));
	testAssertionFailed(stream1.skip(std::numeric_limits<int>::max() + static_cast<__int64>(1)));
	testNoThrow        (stream1.skip(std::numeric_limits<int>::max()));

	// seek 테스트 
	char buffer[2] = {0};
	stream1.position(0);
	testAssert(stream1.skip(1) == 1);
	stream1.read(buffer, 0, 1);
	testAssert(stream1.skip(-2) == -2);
	testAssert(buffer[0] == L'1');
	testAssert(stream1.skip(0) == 0);
	testAssert(stream1.skip(-2) == 0);

	// 범위 외 seek
	testAssert(stream1.skip(5) == 5);
	testAssert(stream1.length() == 4);
	stream1.position(4);
	testAssert(stream1.read(buffer, 0, 1) == 0);
}


testCase(write) {
	char source[5] = "0123";
	MemoryStream stream0(source, 0, 4);
	MemoryStream stream1 = move(stream0);
	MemoryStream stream2(source, 0, 4, false);
	MemoryStream stream3(4);

	// 무효한 파라미터
	testAssertionFailed(stream0.write("0123", 0, 4));
	testAssertionFailed(stream1.write(nullptr, 0, 4));
	testAssertionFailed(stream1.write("0123", -1, 4));
	testAssertionFailed(stream1.write("0123", 0, -1));
	testNoThrow        (stream1.write("0123", 0, 0));
	testAssertionFailed(stream2.write("0123", 0, 4));

	// 쓰기 
	char buffer[10] = {0};
	stream1.write("abcd", 0, 4);
	testAssert(stream1.length() == 4);
	testAssert(stream1.position() == 4);
	stream1.position(0);
	stream1.read(buffer, 0, 4);
	testAssert(String::equals(buffer, "abcd"));
	stream1.write("abcd", 0, 0);
	testAssert(stream1.length() == 4);
	testAssert(stream1.position() == 4);
	stream1.position(0);
	stream1.read(buffer, 0, 4);
	testAssert(String::equals(buffer, "abcd"));
	stream1.position(2);
	stream1.write("0123", 1, 2);
	testAssert(stream1.length() == 4);
	testAssert(stream1.position() == 4);
	stream1.position(0);
	stream1.read(buffer, 0, 4);
	testAssert(String::equals(buffer, "ab12"));
	testThrow(stream1.write("3", 0, 1), MemoryStream::BufferOverrunException);

	// 범위 외 쓰기
	testAssert(stream3.length() == 0);
	stream3.write("0123", 0, 4);
	testAssert(stream3.length() == 4);
	stream3.write("ab", 0, 2);
	testAssert(stream3.length() == 6);
	testAssert(stream3.position() == 6);
	testAssert(stream3.capacity() == 8);
	stream3.position(0);
	stream3.read(buffer, 0, 6);
	testAssert(String::equals(buffer, "0123ab"));
}


//testCase(writable) {
//}



		}
	}
}