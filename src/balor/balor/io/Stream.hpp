#pragma once

#include <balor/NonCopyable.hpp>


namespace balor {
	namespace io {



/**
 * �o�C�i���X�g���[����\�����ۃN���X�B
 */
class Stream : private NonCopyable {
protected:
	Stream();
	virtual ~Stream();

public:
	/// �X�g���[���̃o�b�t�@���t���b�V���i�����j����B
	virtual void flush() = 0;
	/// �X�g���[���̒����B
	virtual __int64 length() const = 0;
	/// ���݈ʒu�B
	virtual __int64 position() const = 0;
	virtual void position(__int64 value) = 0;
	/// �P�o�C�g�ǂݏo���ĕԂ��B�t�@�C���̏I���ɒB���Ă����� -1 ��Ԃ��B
	virtual int read();
	/// �w�肵���o�C�g���̓ǂݏo�������݂āA���ۂɓǂݏo�����o�C�g����Ԃ��B
	virtual int read(void* buffer, int offset, int count) = 0;
	/// �ǂݏo���\���ǂ����B
	virtual bool readable() const = 0;
	/// ���݈ʒu����w�肵���o�C�g�����ړ�����B
	virtual __int64 skip(__int64 offset) = 0;
	/// �P�o�C�g�������ށB
	virtual void write(unsigned char value);
	/// �w�肵���o�C�g���������ށB
	virtual void write(const void* buffer, int offset, int count) = 0;
	/// �������݉\���ǂ����B
	virtual bool writable() const = 0;
};



	}
}