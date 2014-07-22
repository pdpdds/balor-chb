#pragma once

#include <balor/system/Version.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/StringRange.hpp>

namespace balor {
	namespace io {
		class File;
		class Registry;
	}
}


namespace balor {
	namespace system {



/**
 * �t�@�C���̃o�[�W�������B
 * 
 * ���݂̃��P�[�����猾��R�[�h���擾���Ĉ�v����o�[�W��������T���B
 * �݂���Ȃ��ꍇ�̓V�X�e���f�t�H���g���P�[�����j���[�g�����Ɏw�肳�ꂽ�o�[�W��������T���A
 * ����ł�������Ȃ������ꍇ�͍ŏ��̃o�[�W��������ǂݎ��B
 * �o�[�W������񂪖��������ꍇ�� operator SafeBool �� false ��Ԃ��B
 * �t�@�C�����̂�������Ȃ������ꍇ�� ::balor::io::File::NotFoundException �𓊂���B
 */
class FileVersionInfo : private NonCopyable {
public:
	typedef ::balor::io::File File;
	typedef ::balor::io::Registry Registry;

public:
	/// �w�肵���t�@�C���̃o�[�W���������쐬����B
	FileVersionInfo(StringRange filePath);
	FileVersionInfo(FileVersionInfo&& value);
	~FileVersionInfo();

	FileVersionInfo& operator=(FileVersionInfo&& value);

public: // ���ꂼ��t�@�C���o�[�W�������\�[�X�̖��O�ɑΉ����Ă���
	/// ���̃o�[�W�����������A�v���P�[�V�����̃��[�U�f�[�^�̃f�B���N�g���B
	File appDataDirectory(bool useProductVersion = true) const;
	/// ���̃o�[�W�����������A�v���P�[�V�����̃��[�U�f�[�^�̃��W�X�g���B
	Registry appDataRegistry(bool useProductVersion = true) const;
	String comments() const;
	/// ���̃o�[�W�����������A�v���P�[�V�����̋��ʃf�[�^�̃f�B���N�g���B
	File commonAppDataDirectory(bool useProductVersion = true) const;
	/// ���̃o�[�W�����������A�v���P�[�V�����̋��ʃf�[�^�̃��W�X�g���B
	Registry commonAppDataRegistry(bool useProductVersion = true) const;
	String companyName() const;
	String fileDescription() const;
	Version fileVersion() const;
	String fileVersionText() const;
	String internalName() const;
	bool isDebug() const;
	bool isPatched() const;
	bool isPreRelease() const;
	bool isSpecialBuild() const;
	/// �t�@�C���o�[�W�����̌���R�[�h�i���̂܂� Locale �R���X�g���N�^�����Ɏg����j
	int languageCode() const;
	String legalCopyright() const;
	String legalTrademarks() const;
	/// ���̃o�[�W�����������A�v���P�[�V�����̃��[�U�f�[�^�i���[�~���O����j�̃f�B���N�g���B
	File localAppDataDirectory(bool useProductVersion = true) const;
	String originalFileName() const;
	String privateBuild() const;
	String productName() const;
	Version productVersion() const;
	String productVersionText() const;
	String specialBuild() const;

public:
	/// �t�@�C���o�[�W������񂪌����������ǂ����B
	operator bool() const;

private:
	unsigned char* _buffer;
	int _languageCode;
	wchar_t _queryHeader[32];
};



	}
}