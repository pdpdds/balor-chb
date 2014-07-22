#pragma once

#include <balor/StringRange.hpp>


namespace balor {
	namespace system {



/**
 * �R���\�[���E�C���h�E�̕\���╶���̏o�́B
 * 
 * �R���\�[���̓v���Z�X�ɂ���������ł���BWIN32 �A�v���P�[�V�����ׂ̈̂��̂ŁA�R���\�[���A�v���P�[�V�����ł͎g���Ȃ��B
 */
class Console {
public:
	/// �J���Ă����R���\�[�������B
	static void close();
	/// �R���\�[�����J���B
	static void open();
	/// ��������������ށB
	static void write(StringRange text);
	static void write(ByteStringRange text);
	/// ���������������ŉ��s����B
	static void writeLine(StringRange text);
	static void writeLine(ByteStringRange text);
};



	}
}