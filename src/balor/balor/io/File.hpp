#pragma once

#include <balor/io/FileStream.hpp>
#include <balor/Enum.hpp>
#include <balor/Exception.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/StringRange.hpp>

namespace std {
template<typename T> class allocator;
template<typename T, typename A> class vector;
}

namespace balor {
	namespace graphics {
		class Icon;
	}
}


namespace balor {
	namespace io {



/**
 * �t�@�C���܂��̓f�B���N�g����\���B�p�X��ێ����A�p�X�ɑ΂��鑀����T�|�[�g����B
 */
class File {
public:
	typedef ::balor::graphics::Icon Icon;

	/// �t�@�C�������B�g�ݍ��킹�Ŏw�肷��B
	struct Attributes {
		enum _enum {
			none              = 0         , 
			readOnly          = 0x00000001, /// �ǂݎ���p�B
			hidden            = 0x00000002, /// �B���t�@�C���܂��̓f�B���N�g���B
			system            = 0x00000004, /// �V�X�e���t�@�C���܂��̓f�B���N�g���B
			directory         = 0x00000010, /// �f�B���N�g���ł���B
			archive           = 0x00000020, /// �A�[�J�C�u�t�@�C���܂��̓f�B���N�g���B
			normal            = 0x00000080, /// ���ɑ����������B
			temporary         = 0x00000100, /// �ꎞ�t�@�C���B
			sparseFile        = 0x00000200, /// �X�p�[�X�t�@�C���B
			reparsePoint      = 0x00000400, /// �ĉ�̓|�C���g���֘A�t�����Ă���B
			compressed        = 0x00000800, /// ���k����Ă���B
			offline           = 0x00001000, /// �t�@�C���̑��݂��郊���[�g�L���悪�I�t���C���B
			notContentIndexed = 0x00002000, /// �C���f�b�N�X�T�[�r�X�̑ΏۂɂȂ��Ă��Ȃ��B
			encrypted         = 0x00004000, /// �Í�������Ă���B
			virtualFile       = 0x00010000, /// UAC �ɂ���ăt�@�C�������z������Ă���B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Attributes);
	};

	/// �V�X�e���̓��ʂȃf�B���N�g���̎�ށB
	struct Special {
		enum _enum {
			adminTools             = 0x0030, /// �Ǘ��c�[���B
			appData                = 0x001a, /// ���[�~���O����̃A�v���P�[�V�����f�[�^�B
			CDBurnArea             = 0x003b, /// CD �ւ̏������݂�ҋ@���Ă���t�@�C���̗̈�B
			commonAdminTools       = 0x002f, /// �S���[�U�̊Ǘ��c�[���B
			commonAppData          = 0x0023, /// �S���[�U�̃A�v���P�[�V�����f�[�^�B
			commonDesktopDirectory = 0x0019, /// �S���[�U�̃f�X�N�g�b�v�B
			commonDocuments        = 0x002e, /// �S���[�U�̃h�L�������g�B
			commonMusic            = 0x0035, /// �S���[�U�̃~���[�W�b�N�B
			commonOemLinks         = 0x003a, /// common OEM link�B
			commonPictures         = 0x0036, /// �S���[�U�̃s�N�`���B
			commonPrograms         = 0X0017, /// �S���[�U�̃X�^�[�g���j���[�̑S�Ẵv���O�����B
			commonStartMenu        = 0x0016, /// �S���[�U�̃X�^�[�g���j���[�B
			commonStartup          = 0x0018, /// �S���[�U�̃X�^�[�g�A�b�v�B
			commonTemplates        = 0x002d, /// �S���[�U�̃h�L�������g�e���v���[�g�B
			commonVideos           = 0x0037, /// �S���[�U�̃r�f�I�B
			cookies                = 0x0021, /// Cookie�B
			desktop                = 0x0000, /// �f�X�N�g�b�v�B
			desktopDirectory       = 0x0010, /// �f�X�N�g�b�v�B
			favorites              = 0x0006, /// ���C�ɓ���B
			fonts                  = 0x0014, /// �t�H���g�B
			history                = 0x0022, /// �����B
			internetCache          = 0x0020, /// IE�L���b�V���B
			localAppData           = 0x001c, /// �A�v���P�[�V�����f�[�^�B
			localizedResources     = 0x0039, /// ���[�J���C�Y���ꂽ���\�[�X�f�[�^�B
			myComputer             = 0x0011, /// �}�C�R���s���[�^�B
			myDocuments            = 0x0005, /// �}�C�h�L�������g�B
			myMusic                = 0x000d, /// �}�C�~���[�W�b�N�B
			myPictures             = 0x0027, /// �}�C�s�N�`���B
			myVideos               = 0x000e, /// �}�C�r�f�I�B
			netHood                = 0x0013, /// NetHood�B
			personal               = 0x0005, /// �}�C�h�L�������g�B
			printHood              = 0x001b, /// PrintHood�B
			programFiles           = 0x0026, /// Program Files�B
			programFilesX86        = 0x002a, /// Program Files�B�i�U�S�r�b�g�j
			programFilesCommon     = 0x002b, /// Program Files/common�B
			programFilesCommonX86  = 0x002c, /// Program Files/common�B�i�U�S�r�b�g�j
			programs               = 0x0002, /// �X�^�[�g���j���[�̑S�Ẵv���O�����B
			recent                 = 0x0008, /// �ŋߎg�����t�@�C���B
			resources              = 0x0038, /// ���\�[�X�f�[�^�B
			sendTo                 = 0x0009, /// ����B
			startMenu              = 0x000b, /// �X�^�[�g���j���[�B
			startup                = 0x0007, /// �X�^�[�g�A�b�v�B
			system                 = 0x0025, /// �n�r�̃V�X�e���f�B���N�g���B
			systemX86              = 0x0029, /// �n�r�̃V�X�e���f�B���N�g���B
			templates              = 0x0015, /// �h�L�������g�e���v���[�g�B
			userProfile            = 0x0028, /// �v���t�@�C���B
			windows                = 0x0024, /// �n�r�̃f�B���N�g���B
			temporary              = 0xffff, /// �e���|�����t�@�C���̒u����B(�I���W�i���j
		};
		BALOR_NAMED_ENUM_MEMBERS(Special);
	};

	/// �V�X�e���̓���ȃf�B���N�g���̎擾�I�v�V�����B
	struct SpecialOption {
		enum _enum {
			none        = 0     , /// ���݂��Ȃ��ꍇ�͋󕶎����Ԃ��B
			create      = 0x8000, /// ���݂��Ȃ��ꍇ�͍쐬����B
			doNotVerify = 0x4000, /// ���݂��邩�ǂ������m�F�����ɕԂ��B
		};
		BALOR_NAMED_ENUM_MEMBERS(SpecialOption);
	};


	/// �t�@�C����񋓂���C�e���[�^�B�ċA�����̓T�|�[�g���Ȃ��B�ċA����������ɂ̓X�^�b�N�Ȃǂ̏������K�v�ɂȂ�̂ł���Ȃ�� getFiles �Ŕz��ɓ��ꂽ�ق����������낤�B
	struct FilesIterator;


	/// �A�N�Z�X�������Ȃ������B���邢�͈قȂ�{�����[���Ɉړ����悤�Ƃ����B
	class AccessDeniedException : public Exception {};

	/// �ړ��擙�Ƀt�@�C����f�B���N�g�������ɑ��݂��Ă����B
	class AlreadyExistsException : public Exception {};

	/// �f�B���N�g���̃p�X���s���������B
	class InvalidPathException : public Exception {};

	/// �f�B���N�g������ł͂Ȃ��č폜�ł��Ȃ������B
	class NotEmptyException : public Exception {};

	/// �f�B���N�g����������Ȃ������B
	class NotFoundException : public Exception {};

	/// �p�X�����������B
	class PathTooLongException : public Exception {};

	/// ���X���b�h�Ƃ� Share �A�N�Z�X�������������B���邢�͈ړ��悪�����̃T�u�f�B���N�g���������B
	class SharingViolationException : public Exception {};

	/// �p�X������̍ő咷�B
	static const int maxPath = 260;

public:
	/// �󕶎���̃p�X����쐬�B
	File();
	File(const File& value);
	/// �t�@�C���p�X����쐬�B
	File(StringRange path);
	/// �f�B���N�g�����ƃt�@�C��������쐬�B
	File(StringRange direcotryName, StringRange fileName);
	File& operator=(const File& value);

public:
	/// �t�@�C�������B
	File::Attributes attributes() const;
	void attributes(File::Attributes value);
	/// �t�@�C�����R�s�[����B
	void copyTo(StringRange destPath, bool overwrite = false) const;
	/// �t�@�C�����쐬���A�t�@�C���X�g���[����Ԃ��B
	FileStream create();
	/// �f�B���N�g�����쐬����B
	void createDirectory();
	/// �e���|�����t�@�C�����쐬����B
	static File createTempFile();
	/// �J�����g�f�B���N�g��
	static File current();
	static void current(StringRange path);
	/// �t�@�C���p�X���󕶎���ł��邩�ǂ����B
	bool empty() const;
	/// ���݂��邩�ǂ����B
	bool exists() const;
	static bool exists(StringRange path);
	/// �g���q�B�����ꍇ�͋󕶎��񂪕Ԃ�B
	String extension() const;
	void extensionToBuffer(StringBuffer& buffer) const;
	/// �t���t�@�C���p�X�̃t�@�C���B
	File fullPathFile() const;
	/// ���݂̃f�B���N�g���̉��̃t�@�C���ꗗ��Ԃ��B���C���h�J�[�h�w��\�B
	/// ���C���h�J�[�h�̓t�@�C�����܂��͍Ō�̃f�B���N�g�����ɂ̂ݎg�p�ł���B
	std::vector<File, std::allocator<File> > getFiles(StringRange searchPettern = L"?*", bool recursive = false) const;
	File::FilesIterator getFilesIterator(StringRange searchPettern = L"?*") const;
	/// �V�X�e���̓���ȃf�B���N�g����Ԃ��B�����ɂ���Ă͋�̃p�X�⑶�݂��Ȃ��p�X���Ԃ鎖������B
	static File getSpecial(File::Special special, File::SpecialOption option = SpecialOption::create);
	/// �G�N�X�v���[����ł��̃t�@�C�����\������鎞�̃A�C�R���B
	Icon icon() const;
	/// �f�B���N�g�����ǂ����B���݂��Ȃ��ꍇ�� false ��Ԃ��B
	bool isDirectory() const;
	/// �t�@�C���܂��̓f�B���N�g�����ړ�����B�f�B���N�g���̃{�����[�����܂������ړ��͂ł��Ȃ��B
	void moveTo(StringRange destPath);
	/// �t�@�C���܂��̓f�B���N�g�����B
	String name() const;
	void nameToBuffer(StringBuffer& buffer) const;
	/// �g���q�����̃t�@�C�����B
	String nameWithoutExtension() const;
	void nameWithoutExtensionToBuffer(StringBuffer& buffer) const;
	/// �t�@�C����ǉ��������݃��[�h�ŃI�[�v������B
	FileStream openAppend();
	/// �t�@�C����ǂݎ�胂�[�h�ŃI�[�v������B
	FileStream openRead() const;
	/// �t�@�C�����������݃��[�h�ŃI�[�v������B
	FileStream openWrite();
	/// �t�@�C���p�X�B
	const wchar_t* path() const { return _path; }
	void path(StringRange value);
	void path(StringRange directoryName, StringRange fileName);
	/// �t�@�C���p�X�̒����B
	int pathLength() const;
	/// �e�f�B���N�g���B�����ꍇ�͋�̃p�X�������� File ���Ԃ�B
	File parent() const;
	/// �t�@�C�����폜����B
	void remove(bool recursive = false);
	/// �o�b�N�A�b�v���쐬���Ȃ��ꍇ�� destinationBackupFileName �ɒ����O�̕������n��
	void replace(StringRange destFilePath, StringRange backupFilePath);
	/// �t�@�C���p�X�̒�����ݒ肵�����B
	void resetPathLength();
	/// ���[�g�f�B���N�g���B
	File root() const;

public:
	/// �p�X��\�� StringRange �ւ̕ϊ��B
	operator StringRange() const { return StringRange(_path, _pathLength); }

private:
	wchar_t _path[maxPath];
	int _pathLength;
};



/// �t�@�C����񋓂���C�e���[�^�B�ċA�����̓T�|�[�g���Ȃ��B�ċA����������ɂ̓X�^�b�N�Ȃǂ̏������K�v�ɂȂ�̂ł���Ȃ�� getFiles �Ŕz��ɓ��ꂽ�ق����������낤�B
struct File::FilesIterator : private NonCopyable {
	FilesIterator(FilesIterator&& value);
	FilesIterator(const File& file, StringRange searchPettern = L"?*");
	~FilesIterator();
	File::FilesIterator& operator=(FilesIterator&& value);

public:
	/// �񋓂����t�@�C���ւ̃A�N�Z�X�B
	File& operator*();
	File* operator->();
	/// ���̃t�@�C���ֈړ��B
	File::FilesIterator& operator++();
	/// �񋓒����ǂ����B
	operator bool() const;

private:
	File current;
	int nameIndex;
	void* handle;
};



	}
}