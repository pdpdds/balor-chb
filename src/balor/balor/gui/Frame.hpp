#pragma once

#include <balor/gui/ScrollableControl.hpp>

struct tagMINMAXINFO;

namespace balor {
	namespace graphics {
		class Icon;
	}
}


namespace balor {
	namespace gui {

class Button;
class MenuBar;



/**
 * �g�b�v���x���ő��̃R���g���[���̃t���[���ƂȂ�E�C���h�E�B
 *
 * TODO: parent �ɑ��̃R���g���[�����w�肵�Ďq�t���[���ɂȂ�� WS_CAPTION �X�^�C����������t���[����̃G�f�B�b�g�R���g���[�����}�E�X�ɔ������Ȃ��Ȃ�B�����s���B.NET �ł��������ۂ��N����̂� WIN32 �̎d�l��������Ȃ��B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Frame Sample");

	Edit edit(frame, 20, 10, 0, 0, 20);
	Button accept(frame, 20, 40, 0, 0, L"����", [&] (Button::Click& ) {
		MsgBox::show(L"���肵�܂����B");
	});
	Button cancel(frame, 20, 70, 0, 0, L"�L�����Z��", [&] (Button::Click& ) {
		MsgBox::show(L"�L�����Z�����܂����B");
	});
	frame.acceptButton(&accept); // Enter �L�[�Ŕ����B
	frame.cancelButton(&cancel); // ESC �L�[�Ŕ����B
	frame.onClosing() = [&] (Frame::Closing& e) {
		if (MsgBox::show(frame, L"���܂����H", L"�I��", MsgBox::Buttons::okCancel) != MsgBox::Result::ok) {
			e.cancel(true);
		}
	};
	frame.icon(Icon::question());

 	frame.runMessageLoop();
* </code></pre>
 */
class Frame : public ScrollableControl {
public:
	typedef ::balor::graphics::Icon Icon;


	/// �E�C���h�E����闝�R�B
	struct CloseReason {
		enum _enum {
			none              ,
			taskManagerClosing, /// �^�X�N�}�l�[�W���[��������B
			userClosing       , /// close() ���\�b�h������{�^���ŕ����B
			windowShutDown    , /// �E�C���h�E�Y�̃V���b�g�_�E���B
		};
		BALOR_NAMED_ENUM_MEMBERS(CloseReason);
	};


	/// �E�C���h�E�̃X�^�C���B
	struct Style {
		enum _enum {
			none             , /// �^�C�g���o�[���g�������E�C���h�E�B
			singleLine       , /// ��d���̘g�����E�C���h�E�B
			threeDimensional , /// ���̓I�Șg�����E�C���h�E�B
			dialog           , /// �_�C�A���O���B
			sizable          , /// ���T�C�Y�ł���E�C���h�E�B
			toolWindow       , /// �c�[���E�C���h�E�B�A�C�R���A�ő剻�{�^���A�ŏ����{�^���A�w���v�{�^�����\������Ȃ��B
			sizableToolWindow, /// ���T�C�Y�ł���c�[���E�C���h�E�B�A�C�R���A�ő剻�{�^���A�ŏ����{�^���A�w���v�{�^�����\������Ȃ��B
		};
		BALOR_NAMED_ENUM_MEMBERS(Style);
	};


	/// Frame �̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<Frame, ScrollableControl::Event> Event;

	typedef Event DisplayChange;
	typedef Event MenuLoopBegin;
	typedef Event MenuLoopEnd;
	typedef Event ResizeMoveBegin;
	typedef Event ResizeMoveEnd;
	typedef PaintEvent<Frame, Event> Paint;


	/// �E�C���h�E������C�x���g�B
	struct Close : public Frame::Event {
		Close(Frame& sender, CloseReason reason);

		/// �������R�B
		CloseReason closeReason() const;

	private:
		CloseReason _closeReason;
	};


	/// �E�C���h�E�����C�x���g�B
	struct Closing : public Close {
		Closing(Frame& sender, CloseReason reason);

		/// ����̂��L�����Z�����邩�ǂ����B�����l�� false�B
		bool cancel() const;
		void cancel(bool value);

	private:
		bool _cancel;
	};


	///	�w���v�{�^�����������C�x���g�B
	struct HelpButtonClick : public Frame::Event {
		HelpButtonClick(Frame& sender);

		/// �f�t�H���g�̏������L�����Z�����邩�ǂ����B�����l�� false�B
		bool cancel() const;
		void cancel(bool value);

	private:
		bool _cancel;
	};


	///	�ړ������C�x���g�B
	struct Move : public Frame::Event {
		Move(Frame& sender, const Point& position);

		/// �ړ������X�N���[���ʒu�B
		const Point& position() const;

	protected:
		Point _position;
	};


	///	�ړ�����C�x���g�B
	struct Moving : public Move {
		Moving(Frame& sender, const Point& position);

		/// �ړ�����X�N���[���ʒu�B
		using Move::position;
		void position(const Point& value);
		void position(int x, int y);
	};


	///	�傫����ύX����C�x���g�B
	struct Resizing : public Frame::Event {
		Resizing(Frame& sender, ::tagMINMAXINFO* info);

		/// �ő剻�������̃X�N���[���ʒu�B���C�x���g���̃~�X�}�b�`�I
		Point maximizedPosition() const;
		void maximizedPosition(const Point& value);
		void maximizedPosition(int x, int y);
		/// �ő剻�������̑傫���B
		Size maximizedSize() const;
		void maximizedSize(const Size& value);
		void maximizedSize(int width, int height);
		/// �E�C���h�E���h���b�O���đ傫���ύX���鎞�̍ő�̑傫���B
		Size maxTrackSize() const;
		void maxTrackSize(const Size& value);
		void maxTrackSize(int width, int height);
		/// �E�C���h�E���h���b�O���đ傫���ύX���鎞�̍ŏ��̑傫���B
		Size minTrackSize() const;
		void minTrackSize(const Size& value);
		void minTrackSize(int width, int height);

	private:
		::tagMINMAXINFO* _info;
	};


	///	�傫����ύX�����C�x���g�B
	struct Resize : public Frame::Event {
		Resize(Frame& sender, int flag);

		/// �ő剻���ꂽ���ǂ����B
		bool maximized() const;
		/// �ŏ������ꂽ���ǂ����B
		bool minimized() const;

	private:
		int _flag;
	};


public:
	/// �k���n���h���ō쐬�B
	Frame();
	/// �^�C�g��������A�N���C�A���g�T�C�Y�A�X�^�C������쐬�B�N���C�A���g�T�C�Y���O�ɂ���Ɗ���̑傫���ō쐬����B
	Frame(StringRange text, int clientWidth = 0, int clientHeight = 0, Frame::Style style = Style::sizable);
	Frame(Frame&& value, bool checkSlicing = true);
	virtual ~Frame();
	Frame& operator=(Frame&& value);

public:
	/// �{�^���ȊO�Ƀt�H�[�J�X�����鎞�� Enter �L�[�������Ɖ��������ɂȂ�{�^���B
	Button* acceptButton() const;
	void acceptButton(Button* value);
	/// �A�N�e�B�u�ɂ���B
	void activate();
	/// �E�C���h�E��Ńt�H�[�J�X�𓾂Ă���R���g���[���B�E�C���h�E���A�N�e�B�u�łȂ��Ȃ��Ă��ۑ�����A�E�C���h�E���ĂуA�N�e�B�u�ɂȂ������Ƀt�H�[�J�X�����������B
	virtual Control* activeControl() const;
	virtual void activeControl(Control* value);
	/// ���݃A�N�e�B�u�ȃE�C���h�E�B
	static Frame* activeFrame();
	/// ESC �L�[�����������ɉ��������ɂȂ�{�^���B
	Button* cancelButton() const;
	void cancelButton(Button* value);
	/// �^�C�g���o�[�̕�����̃t�H���g�B
	static Font captionFont();
	/// �I�[�i�[�E�C���h�E�̒��S�Ɉړ�����B
	void centerToOwner();
	/// �X�N���[���̒��S�Ɉړ�����B
	void centerToScreen();
	/// �E�C���h�E�����B�E�C���h�E�͔�\���ɂȂ邪�j��͂���Ȃ��B
	void close();
	/// �f�X�N�g�b�v��ł̍��W�B
	Point desktopPosition() const;
	void desktopPosition(const Point& value);
	void desktopPosition(int x, int y);
	/// ���b�Z�[�W���[�v���甲����B
	static void exitMessageLoop();
	/// �t�H�[�J�X�𓾂��邩�ǂ����B
	virtual bool focusable() const;
	/// �H�{�^����L���ɂ��邩�ǂ����B�L���ɂ����ꍇ�A�ő剻�{�^���ƍŏ����{�^���͏�����B�����l�� false�B
	bool helpButton() const;
	void helpButton(bool value);
	/// �^�C�g���o�[�ɕ\������A�C�R���B�傫���A�C�R�����w�肷��B�����l�� nullptr�B
	Icon icon() const;
	void icon(HICON value);
	/*bool keyPreview() const;  onShortcutKey �C�x���g����΂���Ȃ��H *//**/
	/*void keyPreview(bool value); *//**/
	/// �ő剻�{�^����L���ɂ��邩�ǂ����B�����l�� true�B
	bool maximizeButton() const;
	void maximizeButton(bool value);
	/// �ő剻���Ă��邩�ǂ����Bvisible �� true �̏ꍇ�̂ݕύX�ł���B�����l�� false�B
	bool maximized() const;
	void maximized(bool value);
	/// ���j���[�o�[��ݒ肷��B
	void menuBar(MenuBar* value);
	/// ���j���[�o�[�̐�߂�̈�B�����ꍇ�� Rectangle(0, 0, 0, 0) ��Ԃ��B
	Rectangle menuBarBounds() const;
	/// ���j���[�o�[���t�H�[�J�X�𓾂Ă��邩�ǂ����B
	bool menuBarFocused() const;
	/// �ŏ����{�^����L���ɂ��邩�ǂ����B�����l�� true�B
	bool minimizeButton() const;
	void minimizeButton(bool value);
	/// �ŏ������Ă��邩�ǂ����B�����l�� false�B
	bool minimized() const;
	void minimized(bool value);
	/// �E�C���h�E������C�x���g�B
	Listener<Frame::Close&>& onClose();
	/// �E�C���h�E�����C�x���g�B
	Listener<Frame::Closing&>& onClosing();
	/// ���j�^�̉𑜓x�܂��͐F�����ύX���ꂽ�C�x���g�B
	Listener<Frame::DisplayChange&>& onDisplayChange();
	/// �w���v�{�^�����������C�x���g�B
	Listener<Frame::HelpButtonClick&>& onHelpButtonClick();
	/// ���j���[�̕\�����J�n�����C�x���g�B
	Listener<Frame::MenuLoopBegin&>& onMenuLoopBegin();
	/// ���j���[�̕\�����I�������C�x���g�B
	Listener<Frame::MenuLoopEnd&>& onMenuLoopEnd();
	/// �ړ������C�x���g�B
	Listener<Frame::Move&>& onMove();
	/// �ړ�����C�x���g�B
	Listener<Frame::Moving&>& onMoving();
	/// �N���C�A���g�̈��`�悷��C�x���g�B
	Listener<Frame::Paint&>& onPaint();
	/// �傫�����ύX���ꂽ�C�x���g�B
	Listener<Frame::Resize&>& onResize();
	/// �傫�����ύX�����C�x���g�B
	Listener<Frame::Resizing&>& onResizing();
	/// �T�C�Y�ύX��ړ����J�n�����C�x���g�B
	Listener<Frame::ResizeMoveBegin&>& onResizeMoveBegin();
	/// �T�C�Y�ύX��ړ����I�������C�x���g�B
	Listener<Frame::ResizeMoveEnd&>& onResizeMoveEnd();
	/// �I�[�i�[�B�I�[�i�[�����E�C���h�E�͏�ɃI�[�i�[���O�ɕ\������ăI�[�i�[���ŏ���������肷��ƒǏ]����B
	Frame* owner() const;
	void owner(Frame* value);
	/// �I�[�i�[�E�C���h�E�n���h���B�I�[�i�[�����E�C���h�E�͏�ɃI�[�i�[���O�ɕ\������ăI�[�i�[���ŏ���������肷��ƒǏ]����B
	HWND ownerHandle() const;
	void ownerHandle(HWND value);
	/// �e�R���g���[���B
	using ScrollableControl::parent;
	virtual void parent(Control* value);
	/// setLayer �֐��Őݒ肵�����C���[�𖳌��ɂ���B
	void resetLayer();
	/// �ő剻���ŏ��������Ă��Ȃ���Ԃ� bounds�B
	Rectangle restoreBounds() const;
	/// ���b�Z�[�W���[�v�����s����BexitMessageLoop �֐����ĂԂ��A���̊֐����Ă񂾃E�C���h�E��������΃��[�v�𔲂���B
	void runMessageLoop();
	/// �����X���b�h�̑��̃E�C���h�E���g�p�s�ɂ��ă��b�Z�[�W���[�v�����s����B������_�C�A���O�̕\���B�I�[�i�[��ݒ肵�Ă����K�v������B
	void runModalMessageLoop();
	/// ���܂��Ă��郁�b�Z�[�W���������ă��b�Z�[�W���[�v���I�����ׂ����ǂ�����Ԃ��B
	bool runPostedMessages();
	/// �E�C���h�E�𔼓����ɂ���Balpha �͕s�����x(0�`1) �� 1 �ŕs�����BresetLayer �֐��Ŗ������ł���B
	void setLayer(float alpha);
	/// �E�C���h�E��� colorKey �Ɠ����F�̕����𓧖��ɂ���BresetLayer �֐��Ŗ������ł���B
	void setLayer(const Color& colorKey);
	/// graphicsWithAlphaChannel �Ŏw�肵���A���t�@�`�����l�����������R�Q�r�b�g�摜�ŃE�C���h�E�Ɣw�i�𔼓�����������B�摜�͂��炩���� Bitmap::premultiplyAlpha �֐������s���Ă����K�v������B
	/// alpha �����ł���ɑS�̂ɔ������������邱�Ƃ��ł���Bstyle() �������I�� Frame::Style::none �ɐݒ肷��BresetLayer �֐��Ŗ������ł���B���� setLayer �֐������ɓK�p����Ă���ꍇ�A���̊֐��͎��s����B
	/// WM_PAINT ����������Ȃ��Ȃ�A�摜�̂ݕ\�������̂ł��� Frame �̏�ɃR���g���[����\���������ꍇ�͂��� Frame ���I�[�i�[�Ɏ����AcolorKey �œ��߂��� Frame ����ɏ悹�Ĉʒu��Ǐ]������Ɨǂ��B
	void setLayer(HDC graphicsWithAlphaChannel, float alpha = 1.0f);
	/// �N���C�A���g�̈�̑傫������R���g���[���̑傫�������߂�B
	virtual Size sizeFromClientSize(const Size& clientSize) const;
	/// �^�X�N�o�[�ɕ\�����邩�ǂ����B�\����������̂� style() �� Frame::Style::toolWindow �� Frame::Style::sizableToolWindow �̎����I�[�i�[�����E�C���h�E�����B
	/// ��L�� style() �ȊO�ŕ\���������ɂ͏�L�� style() ����������\���̃I�[�i�[�����ĂΗǂ��B�����l�� true�B
	bool showInTaskbar() const;
	void showInTaskbar(bool value);
	/// �E�C���h�E�̃X�^�C���B�����l�� Frame::Style::sizable�B
	Frame::Style style() const;
	void style(Frame::Style value);
	/// ����A�ő剻�A�ŏ����{�^���ƃV�X�e�����j���[��L���ɂ��邩�ǂ����B�����l�� true�B
	bool systemMenu() const;
	void systemMenu(bool value);
	/// �^�C�g��������B
	using ScrollableControl::text;
	virtual void text(StringRange value);
	/// ��ɍőO�ʂɕ\������邩�ǂ����B�����l�� false�B
	bool topMost() const;
	void topMost(bool value);
	/// ���j���[�o�[�̕\�����X�V����B�|�b�v�A�b�v�ł͂Ȃ����j���[���ڂ�ύX������X�V����K�v������B
	void updateMenubar();
	/// �\������邩�ǂ����B�����l�� false�B
	using ScrollableControl::visible;
	virtual void visible(bool value);


public: // �{���� protected �ɂ������� Control �Ƃ��̔h���N���X����ĂԕK�v������̂Ō��J�B
	/// �q���R���g���[�����q���ł͂Ȃ��Ȃ�Ƃ��̏����B�B
	virtual void processDescendantErased(Control& descendant);
	///	�q���R���g���[�����t�H�[�J�X�𓾂��Ƃ��̏����B
	virtual void processDescendantFocused(Control& descendant);

protected:
	/// �_�C�A���O�L�[���������ď����ł������ǂ�����Ԃ��B
	virtual bool processDialogKey(int shortcut);
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);
	/// �E�C���h�E�n���h���̃X�^�C�����X�V����B
	void updateHandleStyle(int style, int exStyle, HICON icon);


protected:
	bool _canPostQuitMessage;
	CloseReason _closeReason;
	Reference<Button> _acceptButton;
	Reference<Control> _activeControl;
	Reference<Button> _cancelButton;
	Style _style;
	Listener<Frame::Close&> _onClose;
	Listener<Frame::Closing&> _onClosing;
	Listener<Frame::DisplayChange&> _onDisplayChange;
	Listener<Frame::HelpButtonClick&> _onHelpButtonClick;
	Listener<Frame::MenuLoopBegin&> _onMenuLoopBegin;
	Listener<Frame::MenuLoopEnd&> _onMenuLoopEnd;
	Listener<Frame::Move&> _onMove;
	Listener<Frame::Moving&> _onMoving;
	Listener<Frame::Paint&> _onPaint;
	Listener<Frame::Resize&> _onResize;
	Listener<Frame::Resizing&> _onResizing;
	Listener<Frame::ResizeMoveBegin&> _onResizeMoveBegin;
	Listener<Frame::ResizeMoveEnd&> _onResizeMoveEnd;
};



	}
}