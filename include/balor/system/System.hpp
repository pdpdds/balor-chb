#pragma once

#include <balor/Enum.hpp>
#include <balor/StringRange.hpp>


namespace balor {
	namespace system {

class Version;



/**
 * �V�X�e���S�̂ɂ��Ă̊֐������B�i�����ނƂ�������j
 */
class System {
public:
	/// �V�X�e���̋N�����[�h
	struct BootMode {
		enum _enum {
			normal              = 0, /// �ʏ탂�[�h�B
			failSafe            = 1, /// �Z�[�t���[�h�B
			failSafeWithNetwork = 2, /// �l�b�g���[�N�ڑ�����Z�[�t���[�h�B
		};
		BALOR_NAMED_ENUM_MEMBERS(BootMode);
	};

	/// �n�r�̎�ށB
	struct OsKind {
		enum _enum {
			unknown,
			windows95,
			windows98,
			windowsME,
			windowsNT4,
			windows2000,
			windowsXP,
			windowsHomeServer,
			windowsServer2003,
			windowsServer2003R2,
			windowsVista,
			windowsServer2008,
			windowsServer2008R2,
			windows7,
		};
		BALOR_NAMED_ENUM_MEMBERS(OsKind);
	};


public:
	/// �V�X�e���̋N�����[�h�B
	static System::BootMode bootMode();
	/// �R�}���h���C�������̐��B
	static int commandLineArgCount();
	/// �R���s���[�^���B�iNetBIOS���j
	static String computerName();
	/// �n�r���}���`�o�C�g�������T�|�[�g���邩�ǂ����B
	static bool dbcsEnabled();
	/// �f�o�b�O�łn�r���L�����ǂ����B
	static bool debugOS();
	/// �E�C���h�E���e��\�������܂܃h���b�O�ł��邩�ǂ����B
	static bool dragFullWindows();
	/// �R�}���h���C�������B
	static String getCommandLineArg(int index);
	/// 64�r�b�g�n�r���ǂ����B
	static bool is64BitOs();
	/// ���݂̃v���Z�X��64�r�b�g�v���Z�X���ǂ����B
	static bool is64BitProcess();
	/// �l�b�g���[�N�ڑ����L�����ǂ����B
	static bool network();
	/// �n�r�̎�ށB
	static System::OsKind osKind();
	/// �T�[�r�X�p�b�N���B
	static String osServicePack();
	/// �n�r�̃o�[�W�����B
	static Version osVersion();
	/// �v���Z�b�T�̐��B
	static int processorCount();
	/// �V�X�e���𒆒f�܂��͋x�~��Ԃɂ���B�����Ɩ߂�l�� ::SetSuspendState �֐��Ɠ����B
	static bool suspend(bool hibernate, bool force, bool disableWakeEvent);
	/// ���[�U���BVista�ɂ����ăC���X�g�[�����Ŏg�p����ƌ������i�̊֌W�ŕs�������炵���B
	static String userName();
	/// �r�W���A���X�^�C�����g�p�ł��邩�ǂ����B�� Comctl32.dll �̃o�[�W�������U�ȏ�ł��邩�ǂ����B
	/// balor/gui/EnableVisualStyle.hpp ���Q�Ƃ̂��ƁB
	static bool visualStyleEnabled();
};



	}
}