#pragma once

#include <balor/Enum.hpp>
#include <balor/StringRange.hpp>

struct HWND__;

namespace balor {
	namespace graphics {
		class Font;
	}
}


namespace balor {
	namespace gui {



/**
 * ���b�Z�[�W�{�b�N�X�̕\�����s���B
 *
 * windows.h �� MessageBox �Ƃ����}�N������`����Ă���̂ŃN���X���� MsgBox �Ƃ��Ă��邪�A
 * typedef �� MessageBox �Ƃ������O���g����悤�ɂ��Ă���̂� windows.h �ƈꏏ�Ɏg��Ȃ��ꍇ��MessageBox �̂ق��̖��O���g�p�ł���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"MessageBox Sample");

	Button warning(frame, 20, 10, 0, 0, L"�x��", [&] (Button::Click& ) {
		MsgBox::show(frame, L"�x���I");
	});
	Button close(frame, 20, 50, 0, 0, L"����", [&] (Button::Click& ) {
		if (MsgBox::show(frame, L"�E�C���h�E����܂����H", L"�I��", MsgBox::Buttons::yesNo) == MsgBox::Result::yes) {
			frame.close();
		}
	});
 
	frame.runMessageLoop();
 * </code></pre>
 */
class MsgBox {
public:
	typedef ::HWND__* HWND;
	typedef ::balor::graphics::Font Font;


	/// �\������{�^���̑g�ݍ��킹�B
	struct Buttons {
		enum _enum {
			ok                = 0x00000000L, /// OK�B
			okCancel          = 0x00000001L, /// OK�A�L�����Z���B
			abortRetryIgnore  = 0x00000002L, /// ���~�A�Ď��s�A�����B
			yesNoCancel       = 0x00000003L, /// �͂��A�������A�L�����Z���B
			yesNo             = 0x00000004L, /// �͂��A�������B
			retryCancel       = 0x00000005L, /// �Ď��s�A�L�����Z���B
			cancelTryContinue = 0x00000006L, /// �L�����Z���A�Ď��s�A���s�B
		};
		BALOR_NAMED_ENUM_MEMBERS(Buttons);
	};


	/// �\������A�C�R���B
	struct Icon {
		enum _enum {
			none        = 0          , /// �A�C�R����\���B
			hand        = 0x00000010L, /// ��~�A�C�R���B
			question    = 0x00000020L, /// �^�╄�A�C�R���B
			exclamation = 0x00000030L, /// ���Q���A�C�R���B
			asterisk    = 0x00000040L, ///�ui]�}�[�N�A�C�R���B
			stop        = 0x00000010L, /// ��~�A�C�R���B
			error       = 0x00000010L, /// ��~�A�C�R���B
			warning     = 0x00000030L, /// ���Q���A�C�R���B
			information = 0x00000040L, ///�ui]�}�[�N�A�C�R���B
		};
		BALOR_NAMED_ENUM_MEMBERS(Icon);
	};


	/// ����̃{�^���B
	struct Default {
		enum _enum {
			button1 = 0x00000000L, /// ��Ԗڂ̃{�^���B
			button2 = 0x00000100L, /// ��Ԗڂ̃{�^���B
			button3 = 0x00000200L, /// �O�Ԗڂ̃{�^���B
		};
		BALOR_NAMED_ENUM_MEMBERS(Default);
	};


	/// �\���I�v�V�����B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none                = 0          , 
			topMost             = 0x00040000L, /// �őO�ʃE�C���h�E�ɂ���B
			serviceNotification = 0x00200000L, /// �T�[�r�X����\������B
			defaultDesktopOnly  = 0x00020000L, /// �T�[�r�X����\������ꍇ�Ɋ���̃f�X�N�g�b�v�ł̂ݕ\������B
			rightAlign          = 0x00080000L, /// �e�L�X�g���E�񂹂���B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


	/// �{�^���̑I�����ʁB
	struct Result {
		enum _enum {
			ok        =  1, /// OK�B
			cancel    =  2, /// �L�����Z���B
			abort     =  3, /// ���~�B
			retry     =  4, /// �Ď��s�B
			ignore    =  5, /// �����B
			yes       =  6, /// �͂��B
			no        =  7, /// �������B
			tryAgain  = 10, /// �Ď��s�B
			continues = 11, /// ���s�B
		};
		BALOR_NAMED_ENUM_MEMBERS(Result);
	};

public:
	/// ���b�Z�[�W�{�b�N�X���g�p����t�H���g�B
	static Font font();
	/// �����X���b�h�̑S�ẴE�C���h�E���g�p�s�ɂ��ă��b�Z�[�W�{�b�N�X��\������B
	static MsgBox::Result show(StringRange text, StringRange caption = L"", MsgBox::Buttons buttons = Buttons::ok, MsgBox::Icon icon = Icon::none, MsgBox::Default defaultButton = Default::button1, MsgBox::Options options = Options::none);
	/// �w�肵���E�C���h�E�̂ݎg�p�s�ɂ��ă��b�Z�[�W�{�b�N�X��\������B
	static MsgBox::Result show(HWND owner, StringRange text, StringRange caption = L"", MsgBox::Buttons buttons = Buttons::ok, MsgBox::Icon icon = Icon::none, MsgBox::Default defaultButton = Default::button1, MsgBox::Options options = Options::none);
};


typedef MsgBox MessageBox; // MessageBox�}�N���΍�



	}
}