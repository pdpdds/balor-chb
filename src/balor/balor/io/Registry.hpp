#pragma once

#include <balor/ArrayRange.hpp>
#include <balor/Enum.hpp>
#include <balor/Exception.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/StringRange.hpp>

struct HKEY__;

namespace std {
template<typename T> class allocator;
template<typename T, typename A> class vector;
}


namespace balor {
	namespace io {



/**
 * ���W�X�g���ɃA�N�Z�X����N���X�B
 */
class Registry : private NonCopyable {
public:
	typedef ::HKEY__* HKEY;

	/// ���W�X�g���̒l�̎��
	struct ValueKind {
		enum _enum {
			string       = 1 , /// ������l�B
			expandString = 2 , /// %PATH% �̂悤�Ȋ��ϐ�������B
			binary       = 3 , /// �o�C�i���f�[�^�B
			dword        = 4 , /// �R�Q�r�b�g���l�B
			multiString  = 7 , /// �k�������ŋ�؂�ꂽ�����̕�����l�B��A���̃k���������I�[��\���B
			qword        = 11, /// �U�S�r�b�g���l�B
			unknown      = -1, /// �T�|�[�g���Ȃ��l�̎�ށB
			notFound     = -2, /// �l��������Ȃ������B
		};
		BALOR_NAMED_ENUM_MEMBERS(ValueKind);
	};

	/// �L�[����l����񋓂���C�e���[�^�B
	struct NamesIterator {
		NamesIterator(HKEY handle, bool isKeyName);

		/// ���݈ʒu�̖��O��񋓂��Ȃ����B�񋓂��Ȃ���L�[��l���폜����ꍇ�� ++ �ł͂Ȃ����������g���B
		void refresh();
		/// �񋓂������O�B
		const wchar_t* operator*() const;
		/// ���̖��O�Ɉړ��B
		Registry::NamesIterator& operator++();
		/// �񋓂��I��������ǂ����B
		operator bool() const;

	private:
		HKEY handle;
		bool isKeyName;
		unsigned long count;
		wchar_t name[256];
	};

	/// �L�[��l�ɃA�N�Z�X�������������B���邢�̓T�u�L�[�������W�X�g�����폜���悤�Ƃ����B
	class AccessDeniedException : public Exception {};

	/// HKEY_LOCAL_MACHINE �����ɃL�[���쐬���悤�Ƃ����ꍇ���B
	class InvalidParameterException : public Exception {};

	/// ���삵�悤�Ƃ����L�[�����ɍ폜����Ă����B
	class KeyDeletedException : public Exception {};

	/// �l��������Ȃ������B
	class ValueNotFoundException : public Exception {};

	/// �l�̎�ނƕϐ��̌^�������ĂȂ��B
	class ValueKindMismatchException : public Exception {};

public:
	/// ����������ԁB
	Registry();
	Registry(Registry&& value);
	/// HKEY_�`�Ŏn�܂郌�W�X�g���L�[������쐬�B
	Registry(StringRange path, bool writable = false);
	~Registry();
	Registry& operator=(Registry&& value);

public:
	/// HKEY_CLASSES_ROOT �ō쐬�B
	static Registry classesRoot();
	/// �T�u�L�[���쐬���ĕԂ��B
	Registry createKey(StringRange keyName, bool writable = false);
	/// HKEY_CURRENT_CONFIG �ō쐬�B
	static Registry currentConfig();
	/// HKEY_CURRENT_USER �ō쐬�B
	static Registry currentUser();
	/// �L���b�V������Ă��錻�݂̃L�[�̕ύX���f�B�X�N�ɔ��f������B
	void flush();
	/// �������ނ̒l���o�C�i���`���ŕԂ��B
	std::vector<unsigned char, std::allocator<unsigned char> > getBinary(StringRange valueName) const;
	/// DWORD �^�̒l��Ԃ��B
	unsigned long getDword(StringRange valueName) const;
	/// QWORD �^�̒l��Ԃ��B
	unsigned __int64 getQword(StringRange valueName) const;
	/// String �^�Ŏ󂯎���l��Ԃ��B
	String getString(StringRange valueName) const;
	void getStringToBuffer(StringBuffer& buffer, StringRange valueName) const;
	/// �l�̎�ނ�Ԃ��B�l��������Ȃ���� Registry::ValueKind::notFound ��Ԃ��B
	Registry::ValueKind getValueKind(StringRange valueName) const;
	/// HKEY_LOCAL_MACHINE �ō쐬�B
	static Registry localMachine();
	/// �T�u�L�[�̐��B
	int keyCount() const;
	/// �T�u�L�[����񋓂���C�e���[�^�B
	Registry::NamesIterator keyNamesIterator() const;
	/// �T�u�L�[���J���B���݂��Ȃ������ꍇ�͋�� Registry ��Ԃ��B
	Registry openKey(StringRange subKeyName, bool writable = false) const;
	/// �T�u�L�[���폜����B
	void removeKey(StringRange keyName, bool recursive = false);
	/// �l���폜����B
	void removeValue(StringRange valueName);
	/// �C�ӂ̌^�̒l��ݒ肷��B
	void setBinary(StringRange valueName, ArrayRange<const unsigned char> value, Registry::ValueKind kind = ValueKind::binary);
	/// Registry::ValueKind::dword �̒l��ݒ肷��B
	void setDword(StringRange valueName, unsigned long value);
	/// Registry::ValueKind::qword �̒l��ݒ肷��B
	void setQword(StringRange valueName, unsigned __int64 value);
	/// String �^ �̒l��ݒ肷��B
	void setString(StringRange valueName, StringRange value, Registry::ValueKind kind = ValueKind::string);
	/// HKEY_USERS �ō쐬�B
	static Registry users();
	/// �l�̐��B
	int valueCount() const;
	/// �l����񋓂���C�e���[�^�B
	Registry::NamesIterator valueNamesIterator() const;

public:
	/// HKEY �ւ̎����ϊ� �� null �`�F�b�N�p�B
	operator HKEY() const { return _handle; }

private:
	HKEY _handle;
};



	}
}