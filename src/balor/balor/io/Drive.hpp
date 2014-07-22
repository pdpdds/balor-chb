#pragma once

#include <balor/Enum.hpp>
#include <balor/Exception.hpp>
#include <balor/StringRange.hpp>


namespace balor {
	namespace io {



/**
 * �V�X�e���̃h���C�u��\���B
 */
class Drive {
public:
	/// �h���C�u�̎�ށB
	struct Type {
		enum _enum {
			unknown         = 0, /// ���ʕs�\�B
			noRootDirectory = 1, /// ���[�g�f�B���N�g�������݂��Ȃ������B
			removable       = 2, /// �����[�o�u���h���C�u�B
			fixed           = 3, /// ���o���Ȃ� HDD ���̃h���C�u�B
			remote          = 4, /// �����[�g�h���C�u�B
			cdRom           = 5, /// CD-ROM �h���C�u�B
			ramDisk         = 6, /// RAM�f�B�X�N�B
		};
		BALOR_NAMED_ENUM_MEMBERS(Type);
	};

	/// �_���h���C�u��񋓂���C�e���[�^�B
	struct DrivesIterator {
		DrivesIterator(bool begin);

		Drive operator*();
		Drive::DrivesIterator& operator++();
		Drive::DrivesIterator& operator--();
		bool operator<(const Drive::DrivesIterator& rhs);
	private:
		unsigned long mask;
		int current;
	};

	/// �A�N�Z�X�������Ȃ������B
	class AccessDeniedException : public Exception {};

	/// �h���C�u��������Ȃ������B
	class NotFoundException : public Exception {};

	/// �h���C�u�������ł��Ă��Ȃ������B
	class NotReadyException : public Exception {};

public:
	/// �h���C�u������쐬�B
	explicit Drive(wchar_t letter);
	explicit Drive(StringRange name);

public:
	/// ���݂̃��[�U���g�p�ł���󂫃o�C�g���B
	__int64 availableFreeBytes() const;
	/// �_���h���C�u���X�g�̃C�e���[�^�B
	static Drive::DrivesIterator drivesBegin();
	static Drive::DrivesIterator drivesEnd();
	/// �t�@�C���V�X�e����
	String fileSystem() const;
	void fileSystemToBuffer(StringBuffer& buffer) const;
	/// �h���C�u�����B
	wchar_t letter() const;
	/// �h���C�u���B
	const wchar_t* name() const;
	/// �������ł��Ă��邩�ǂ����B
	bool ready() const;
	/// �󂫃o�C�g���B
	__int64 totalFreeBytes() const;
	/// �h���C�u�̑��o�C�g���B
	__int64 totalBytes() const;
	/// �h���C�u�̃^�C�v�B
	Drive::Type type() const;
	/// �{�����[�����x���B
	String volumeLabel() const;
	void volumeLabel(StringRange value);
	void volumeLabelToBuffer(StringBuffer& buffer) const;

private:
	wchar_t _name[4];
};



	}
}