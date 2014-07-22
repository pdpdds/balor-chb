#pragma once

#include <balor/Enum.hpp>

struct HICON__;

namespace balor {
	namespace graphics {
		class Cursor;
	}
class Point;
class Rectangle;
class Size;
}


namespace balor {
	namespace gui {


/**
 * �}�E�X�Ɋւ�����⑀��������B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"MessageBox Sample");

	Label position(frame, 20, 10, 200, 0, L"���݂̃J�[�\���ʒu�F");
	frame.onMouseMove() = [&] (Frame::MouseMove& ) {
		position.text(String(L"���݂̃J�[�\���ʒu�F") + Mouse::position().x + L", " + Mouse::position().y);
	};
	Label change(frame, 20, 50, 200, 100, L"�J�[�\���̕ύX");
	change.edge(Label::Edge::client);
	change.onCursorChange() = [&] (Label::CursorChange& e) {
		e.cursor(Cursor::hand());
	};
	Label hide(frame, 20, 180, 200, 100, L"�J�[�\�����\��");
	hide.edge(Label::Edge::client);
	hide.onMouseEnter() = [&] (Label::MouseEnter& ) {
		Mouse::hide();
	};
	hide.onMouseLeave() = [&] (Label::MouseLeave& ) {
		Mouse::show();
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class Mouse {
public:
	typedef ::HICON__* HCURSOR;
	typedef ::balor::graphics::Cursor Cursor;

	/// �}�E�X�̃{�^���̎�ށB
	enum _enum {
		none               = 0x00, /// �ǂ̃{�^���ł��Ȃ��B
		lButton            = 0x01, /// ���{�^���B
		mButton            = 0x04, /// �����{�^���B
		rButton            = 0x02, /// �E�{�^���B
		xButton1           = 0x05, /// X1�{�^���B
		xButton2           = 0x06, /// X2�{�^���B
	};
	BALOR_NAMED_ENUM_MEMBERS(Mouse);

public:
	/// �{�^���̐��B
	static int buttonCount();
	/// ���E�̃{�^���@�\���������Ă��邩�ǂ����B
	static bool buttonSwapped();
	/// �}�E�X�J�[�\�����ړ��\�ȃX�N���[�����W�̈�B
	static Rectangle clip();
	static void clip(const Rectangle& value);
	/// �}�E�X�J�[�\���B
	static Cursor cursor();
	static void cursor(HCURSOR value);
	/// ���̃N���b�N���_�u���N���b�N�Ƃ݂Ȃ����s�N�Z���͈́B
	static Size doubleClickSize();
	/// �_�u���N���b�N�Ƃ݂Ȃ����N���b�N�Ԋu�i�~���b�j�B
	static int doubleClickTime();
	/// �}�E�X�J�[�\�����\���ɂ���B�\����\���̓J�E���g�����B
	static void hide();
	/// �}�E�X�z�o�[�łƂǂ܂��Ă��Ȃ���΂Ȃ�Ȃ��͈̓s�N�Z���B
	static Size hoverSize();
	/// �}�E�X�z�o�[�̃f�t�H���g�ҋ@���ԁi�~���b�j�B
	static int hoverTime();
	/// �{�^����������Ă��邩�ǂ����B�E�C���h�E���b�Z�[�W���[�v�ŏ�Ԃ��X�V�����B
	static bool isPushed(Mouse button);
	/// �{�^����������Ă��邩�ǂ����B�E�C���h�E���b�Z�[�W���[�v�ɂ�炸�Ɍ��݂̏�Ԃ��擾����B
	static bool isPushedAsync(Mouse button);
	/// �}�E�X�J�[�\���̌��݂̃X�N���[�����W�B
	static Point position();
	static void position(const Point& value);
	/// �Ō�Ƀ��b�Z�[�W�������ꂽ�}�E�X�J�[�\���̃X�N���[�����W�B
	static Point positionAtLastMessage();
	/// �}�E�X���ڑ�����Ă��邩�ǂ����B
	static bool present();
	/// �}�E�X�J�[�\����\������B�\����\���̓J�E���g�����B
	static void show();
	/// �}�E�X�J�[�\���̈ړ����x�B�P�i�x���j�`�Q�O�i�����j��Ԃ��B
	static int speed();
	/// �}�E�X�z�C�[�����ڑ�����Ă��邩�ǂ����B
	static bool wheelPresent();
	/// �}�E�X�z�C�[���ň�x�ɃX�N���[������s�N�Z�����B
	static int wheelScrollDelta();
	/// �}�E�X�z�C�[���ň�x�ɃX�N���[������s���B
	static int wheelScrollLines();
};



	}
}