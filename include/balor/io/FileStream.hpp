#pragma once

#include <balor/io/Stream.hpp>
#include <balor/Enum.hpp>
#include <balor/Exception.hpp>
#include <balor/StringRange.hpp>


namespace balor {
	namespace io {



/**
 * Win32 API �̃t�@�C���A�N�Z�X�@�\���T�|�[�g����X�g���[���B
 */
class FileStream : public Stream {
public:
	typedef void* HANDLE;

	/// �t�@�C���̃I�[�v�����[�h�B
	struct Mode {
		enum _enum {
			create       = 1, /// �t�@�C���̐V�K�쐬�B���ɑ��݂��Ă����ꍇ�� AlreadyExistsException �𓊂���B
			createAlways = 2, /// �t�@�C���̐V�K�쐬�B���ɑ��݂��Ă����ꍇ�͏����Ă���쐬�B
			open         = 3, /// �t�@�C�����J���B���݂��Ȃ��ꍇ�� NotFoundException �𓊂���B
			openAlways   = 4, /// �t�@�C�����J���B���݂��Ȃ��ꍇ�͐V�K�쐬����B
			truncate     = 5, /// �t�@�C�����J���A�T�C�Y���O�ɂ���B���݂��Ȃ��ꍇ�� NotFoundException �𓊂���B
			append       = 6, /// openAlways �ŊJ���ăt�@�C���ʒu���I�[�Ɉړ�����B
		};
		BALOR_NAMED_ENUM_MEMBERS(Mode);
	};

	/// �t�@�C���ւ̃A�N�Z�X���B
	struct Access {
		enum _enum {
			read      = 0x80000000L, /// �ǂݎ��A�N�Z�X�B
			write     = 0x40000000L, /// �������݃A�N�Z�X�B
			readWrite = 0xc0000000L, /// �ǂݏ����A�N�Z�X�B
		};
		BALOR_NAMED_ENUM_MEMBERS(Access);
	};

	/// �t�@�C���ւ̋��L�����B�g�ݍ��킹�Ŏw�肷��B
	struct Share {
		enum _enum {
			none      = 0x00000000, /// ���X���b�h�A�v���Z�X�̈�؂̃A�N�Z�X���ւ���B
			read      = 0x00000001, /// �ǂݎ��̋��L�B
			write     = 0x00000002, /// �������݂̋��L�B
			remove    = 0x00000004, /// �폜�̋��L�B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Share);
	};

	/// �t�@�C���I�[�v���̃I�v�V�����B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none           = 0         , 
			writeThrough   = 0x80000000, /// �L���b�V�������ɒ��ڃf�B�X�N�ɏ������ށB
			randomAccess   = 0x10000000, /// �����_���A�N�Z�X���邱�Ƃ��V�X�e���Ɏw������B
			removeOnClose  = 0x04000000, /// �t�@�C����������ɍ폜����B
			sequentialScan = 0x08000000, /// �V�[�P���V�����ɃA�N�Z�X���邱�Ƃ��V�X�e���Ɏw������B
			encrypted      = 0x00004000, /// �t�@�C�����Í�������B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};

	/// �A�N�Z�X�����Ȃ������B
	class AccessDeniedException : public Exception {};

	/// �t�@�C�������ɑ��݂��Ă����B
	class AlreadyExistsException : public Exception {};

	/// ���b�N����Ă��ēǂݏ����ł��Ȃ������B
	class LockViolationException : public Exception {};

	/// �t�@�C����������Ȃ������B
	class NotFoundException : public Exception {};

	/// ���L�����ɔ����鋣�����������B
	class SharingViolationException : public Exception {};

	// �I�[�o�[���[�h�֐��̃I�[�o�[���C�h�p
	using Stream::read;
	using Stream::write;

public:
	/// �t�@�C���̎������b�N�����p�I�u�W�F�N�g�B
	/// MSDN�ɂ��΃t�@�C���̃��b�N������ position �� length �����b�N�����ƌ�����v�����čs���K�v������A
	/// ���b�N�������s�킸�Ƀt�@�C���n���h���������v���Z�X���I�������肷��Ɩ���`�̓���Ƃ���̂Ńf�X�g���N�^�Ŋm���ɏ����������B
	class Lock {
		friend FileStream;

		Lock(HANDLE handle, __int64 position, __int64 length);

	public:
		Lock(Lock&& lock);
		~Lock();

	private:
		Lock(const Lock& );
		Lock& operator=(const Lock& );

		HANDLE handle;
		__int64 position;
		__int64 length;
	};

public:
	/// �k���n���h���ō쐬����B
	FileStream();
	/// �w�肵���p�����[�^�Ńt�@�C�����I�[�v������B
	FileStream(StringRange path, FileStream::Mode mode, FileStream::Access access = Access::readWrite, FileStream::Share share = Share::read, FileStream::Options options = Options::none);
	FileStream(FileStream&& value);
	/// �t�@�C�����N���[�Y����B
	virtual ~FileStream();

	FileStream& operator=(FileStream&& value);

public:
	virtual void flush();
	virtual __int64 length() const;
	/// �w�肵���̈�̑��̃n���h���̓ǂݏ������֎~����B�߂�l�� Lock �I�u�W�F�N�g�����݂��Ă���Ԃ����L���B
	Lock lock(__int64 position, __int64 length);
	virtual __int64 position() const;
	virtual void position(__int64 value);
	virtual int read(void* buffer, int offset, int count);
	virtual bool readable() const;
	virtual __int64 skip(__int64 offset);
	/// �t�@�C���̏I�[�Ɉړ�����B
	virtual __int64 skipToEnd();
	virtual void write(const void* buffer, int offset, int count);
	virtual bool writable() const;

public:
	/// HANDLE �ւ̎����ϊ� �� null �`�F�b�N�p
	operator HANDLE() const { return _handle; }

private:
	HANDLE _handle;
	Access _access;
};



	}
}