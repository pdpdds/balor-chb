#pragma once

#include <balor/StringRange.hpp>

namespace balor {
	namespace io {
		class Registry;
	}
}


namespace balor {
	namespace system {



/**
 * ���ϐ��Ɋւ��鑀��B
 */
class EnvironmentVariable {
public:
	typedef ::balor::io::Registry Registry;

	/// ���݂̃v���Z�X�̑S�Ă̊��ϐ���񋓂���C�e���[�^�B�񋓒��Ɋ��ϐ����폜�����肷��Ɨ\�����ʓ�����N�����\��������B
	/// ���O��l�ւ̃A�N�Z�X�̓X���b�h�Z�[�t�ł͂Ȃ��B
	struct VariablesIterator {
		VariablesIterator();

		/// ���ϐ����B
		String name() const;
		void nameToBuffer(StringBuffer& buffer) const;
		/// ���ϐ��̒l�B
		String value() const;
		void valueToBuffer(StringBuffer& buffer) const;
		/// ���̊��ϐ��ցB
		VariablesIterator& operator++();
		/// �񋓒����ǂ����B
		operator bool() const;

	private:
		int _current;
	};

public:
	/// ������Ɋ܂܂�� % �ň͂܂ꂽ���ϐ�����W�J���ĕԂ��B
	static String expandStrings(StringRange string);
	static void expandStringsToBuffer(StringBuffer& buffer, StringRange string);
	/// ���݂̃v���Z�X�̊��ϐ������݂��邩�ǂ����B
	static bool find(StringRange valueName);
	/// ���݂̃v���Z�X�̊��ϐ���Ԃ��B������Ȃ������ꍇ�͋󕶎����Ԃ��B
	static String get(StringRange valueName);
	static void getToBuffer(StringBuffer& buffer, StringRange valueName);
	/// ���݂̃v���Z�X�̊��ϐ����폜����B
	static void remove(StringRange valueName);
	/// ���݂̃v���Z�X�̊��ϐ���ύX����B
	static void set(StringRange valueName, StringRange value);
	/// �V�X�e���̊��ϐ����ݒ肳��Ă��郌�W�X�g����Ԃ��B
	static Registry systemRegistry();
	/// ���ϐ��̃��W�X�g���̕ύX��S�Ẵv���Z�X�ɔ��f������BWM_SETTINGCHANGE ���b�Z�[�W���������Ȃ��v���Z�X�ɂ͌��ʂ��Ȃ��B
	/// TODO:�R�}���h�v�����v�g�ɔ��f����Ȃ��悤���B����̃A�v���ł����f����Ȃ��B�ǂ��Ȃ��Ă���̂��E�E
	static void updateAllProcess();
	/// ���O�C�����̃��[�U�̊��ϐ����ݒ肳��Ă��郌�W�X�g����Ԃ��B
	static Registry userRegistry();
	/// ���݂̃v���Z�X�̑S�Ă̊��ϐ���񋓂���C�e���[�^�B
	static EnvironmentVariable::VariablesIterator variablesBegin();
};



	}
}