#pragma once

#include <balor/io/Stream.hpp>
#include <balor/Exception.hpp>


namespace balor {
	namespace io {



/**
 * �Œ蒷�������܂��͓��I�Ɋ��蓖�Ă��������̃X�g���[���B
 *
 * std::iostream �ɂ͕W���ł͑��݂��Ȃ��̂Ŏ��삷��B
 */
class MemoryStream : public Stream {
public:
	// �������݂��Œ蒷�o�b�t�@���I�[�o�[����
	class BufferOverrunException : public Exception {};

	// �I�[�o�[���[�h�֐��̃I�[�o�[���C�h�p
	using Stream::read;
	using Stream::write;

public:
	/// �����̃o�b�t�@�T�C�Y���w�肵�ĕK�v�ɉ����ăo�b�t�@���g�����Ă����������X�g���[�����쐬�B
	MemoryStream(int capacity = 256);
	/// �Œ蒷�z��̃������o�b�t�@����쐬�B
	template<typename T, int Size> MemoryStream(T (&buffer)[Size], bool writable = true)
		: _first(reinterpret_cast<unsigned char*>(buffer)), _last(_first + sizeof(buffer)), _end(_last), _current(_first), _allocatable(false), _writable(writable) {}
	/// �Œ蒷�̃������o�b�t�@����쐬�B
	MemoryStream(void* buffer, int offset, int bufferSize, bool writable = true);
	MemoryStream(MemoryStream&& stream);
	virtual ~MemoryStream();

	MemoryStream& operator=(MemoryStream&& stream);

public:
	/// �������o�b�t�@�̐擪�̃|�C���^�B
	void* buffer();
	const void* buffer() const;
	/// �o�b�t�@�̑傫���B�傫���Ȃ邱�Ƃ͂����Ă��������Ȃ邱�Ƃ͂Ȃ��B
	int capacity() const;
	virtual void flush();
	virtual __int64 length() const;
	void length(int value);
	virtual __int64 position() const;
	virtual void position(__int64 value);
	virtual int read(void* buffer, int offset, int count);
	virtual bool readable() const;
	virtual __int64 skip(__int64 offset);
	virtual void write(const void* buffer, int offset, int count);
	virtual bool writable() const;

private:
	unsigned char* _first;
	unsigned char* _last;
	unsigned char* _end;
	unsigned char* _current;
	bool _allocatable;
	bool _writable;
};



	}
}