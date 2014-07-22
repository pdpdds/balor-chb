#pragma once

#include <balor/graphics/Graphics.hpp>
#include <balor/gui/Key.hpp>
#include <balor/gui/Mouse.hpp>
#include <balor/gui/Message.hpp>
#include <balor/Enum.hpp>
#include <balor/Event.hpp>
#include <balor/Listener.hpp>
#include <balor/Point.hpp>
#include <balor/Rectangle.hpp>
#include <balor/Reference.hpp>
#include <balor/Size.hpp>
#include <balor/String.hpp>
#include <balor/UniqueAny.hpp>

struct HWND__;

namespace std {
	namespace tr1 {
template<typename T> class function;
	}
}

namespace balor {
	namespace graphics {
		class Brush;
		class Color;
		class Font;
		class Region;
	}
}


namespace balor {
	namespace gui {

class Frame;
class Scaler;



/**
 * �R���g���[���̊��N���X�B
 *
 * �S�ẴR���g���[���N���X�͂��̃N���X����h������B
 * �J�[�\����ݒ肷��ɂ� onCursorChange �C�x���g����������B
 * �|�b�v�A�b�v���j���[��\������ɂ� onPopupMenu �C�x���g����������B
 * �R���g���[���̃j�[���j�b�N�⃁�j���[�̃V���[�g�J�b�g�L�[�ׂ̈� onShortcutKey �C�x���g�𗘗p�ł���B
 * �h���b�O���h���b�v����������̂� DragDrop �N���X�𗘗p�ł���B
 * ���C�A�E�g��ݒ肷��̂� DockLayout �N���X�� LineLayout �N���X���𗘗p�ł���B
 *
 * <h3>�E�g���̃K�C�h���C��</h3>
 *
 * Control �N���X���p�������h���N���X�̓E�C���h�E�n���h�����쐬���� attachHandle �֐��� Control �ɕR���AprocessMessage �֐����I�[�o�[���C�h���ăE�C���h�E�v���V�[�W�����g������B
 * �ł��邾���f�X�g���N�^�� destoryHandle �֐����ĂԁB�����Ȃ��� Control �N���X�̃f�X�g���N�^����Ă΂�邪�A���̎��_�Ŕh���N���X�̃f�X�g���N�^�͊��ɌĂ΂�Ă���̂�
 * Control �N���X�� processMessage �֐����Ă΂�Ă��܂��B���邢�͔h���N���X�Ɍ��J����Ă��� _handle, _defaultProcedure �����o�ϐ��𑀍삵�ď������A�I���������s���B
 * Control �̓R�s�[�֎~�N���X�Ȃ̂ňꎞ�I�u�W�F�N�g����������A�֐��̖߂�l�Ƃ�����ASTL �R���e�i�Ɋi�[���邽�߂ɂ͉E�Ӓl�R�s�[�R���X�g���N�^�A�E�Ӓl������Z�q���`����B
 * ���̒�`�� Control ���ʂ̌��ߎ��ɂ��������Ď�������K�v������B�ȉ��� Button �N���X���p�������R�[�h�̗�B
 * <pre><code>
 * class MyButton : public Button {
 * public:
 *	MyButton() {}
 *	MyButton(MyButton&& value, bool checkSlicing = true)
 *		: Button(std::move(value), false) // Button �N���X�̔h���N���X����`�F�b�N�ɕK���Ђ�������̂� false ���w�肷��B
 *		, myMember(std::move(value.myMember)) {
 *		if (checkSlicing) { // MyButton �̔h���N���X�̑�����`�F�b�N
 *			assert("Object sliced" && typeid(*this) == typeid(value));
 *		}
 *	}
 *	MyButton(Control& parent, int x, int y) : Button(parent, x, y, 200, 100, L"myButton") {}
 *	MyButton& operator=(MyButton&& value) {
 *		if (this != &value) {
 *			this->~MyButton(); // �����o�̈ړ���h���N���X�̑���`�F�b�N���R���X�g���N�^�ɂ܂Ƃ߂�ׂɃf�X�g���N�^�� new ���g��
 *			new (this) MyButton(std::move(value));
 *		}
 *		return *this;
 *	}
 *	std::vector<String> myMember;
 * };
 * </code></pre>
 * 
 * <h3>�E���b�Z�[�W���t���N�V����</h3>
 *
 * WM_NOTIFY�AWM_COMMAND�AWM_CTLCOLORBTN ���̃��b�Z�[�W�͐e�R���g���[���ɒʒm����Đe�R���g���[���ŏ������邱�ƂɂȂ��Ă��邪
 * �����ʒm���̎q�R���g���[���ɑ���Ԃ��Ďq�R���g���[���ŏ������Ă���B�����MFC �� WIN32 API �v���O���~���O�ł̓��b�Z�[�W���t���N�V�����ƌĂ΂��B
 * �������邱�ƂŐe�R���g���[���͎q�R���g���[���ɉ������݂��邩�m��Ȃ��Ă��ǂ����q�R���g���[���͎����̂��Ƃ͑S�Ď����ŏ����ł���B
 * ���̎�����Ԃ���郁�b�Z�[�W�ԍ��� Control::wmReflect + ���̃��b�Z�[�W�ԍ� �ƂȂ�B
 *
 * <h3>�E���c�o�h���ւ̑Ή�</h3>
 *
 * ���c�o�h���ł̓E�C���h�E���������㏬�����A�V�X�e���t�H���g�͑傫���Ȃ��Ă���̂Ń��C�A�E�g�������B
 * �ꕔ���ł̓f�t�H���g�ō��c�o�h�ݒ�̏ꍇ�����鑼�A�R���g���[���p�l��������c�o�h�ݒ��ύX�ł���B
 * ����ɑΉ�����ɂ͂܂��v���W�F�N�g�̐ݒ���ȉ��̂悤�ɕύX����K�v������悤���B<br>
 * �\���v���p�e�B���}�j�t�F�X�g�c�[�������o�́�DPI �F���̗L���� = �͂�
 * <br>���ɃR�[�f�B���O�łǂ̂悤�ɑΉ����ׂ����̓A�v���P�[�V�����ɂ���ĈقȂ邪�ȉ��̂悤�ȑ΍􂪍l������B
 *
 * <h6>�P�D�t�H���g���Œ肷��B</h6>
 *
 * �t�H���g�ɌŒ�̑傫�����w�肵�č쐬���A�S�ẴR���g���[���ɐݒ肷��B���������c�o�h���ł͏�����������B
 *
 * <h6>�Q�DScaler �N���X�� scale �֐��𗘗p���ăR���g���[�����X�P�[�����O����B</h6>
 *
 * Scaler �N���X��n���� Frame �N���X�� scale �֐����ĂׂΎq�R���g���[�����܂߂ăX�P�[�����O����B
 * ������ getPreferredSize �֐��ő傫�������߂Ă���ꍇ�A���̊֐����t�H���g�̑傫�������l������̂ł�����X�P�[������Ƒ傫���Ȃ肷����B
 * ���̏ꍇ scalable �֐��ő傫�����X�P�[�����Ȃ��悤�ɂ���΂悢�B����͑����̃R���g���[���̃R���X�g���N�^�����̑傫���ɂO���w�肵���ꍇ�������B
 * �܂����c�o�h�𗘗p���Đ����ȉ摜���������Ƃ����悤�ȏꍇ�ɉ摜�܂ŃX�P�[������ƍ��c�o�h�̈Ӗ��������Ȃ�̂�
 * �X�P�[������Ώۂ̓P�[�X�o�C�P�[�X�ƂȂ�B�ȉ��� Frame �N���X�Ƃ��̎q���R���g���[�����c�o�h��ŃX�P�[������R�[�h�̗�B
 * <pre><code>
 *	frame.scale(Scaler());
 * </code></pre>
 *
 */
class Control : public Referenceable {
public:
	typedef ::HWND__* HWND;
	typedef Message::LRESULT (__stdcall *Procedure)(HWND handle, unsigned int message, Message::WPARAM wparam, Message::LPARAM lparam);
	typedef ::balor::graphics::Brush Brush;
	typedef ::balor::graphics::Color Color;
	typedef ::balor::graphics::Font Font;
	typedef ::balor::graphics::Graphics Graphics;
	typedef ::balor::graphics::Region Region;
	typedef Graphics::HBITMAP HBITMAP;
	typedef Graphics::HBRUSH HBRUSH;
	typedef Graphics::HDC HDC;
	typedef Graphics::HFONT HFONT;
	typedef Graphics::HICON HICON;
	typedef Graphics::HICON HCURSOR;
	typedef Graphics::HRGN HRGN;


	/// �R���g���[���̋��E���̎�ށB
	struct Edge {
		enum _enum {
			none  , /// ���E���͂Ȃ��B
			line  , /// ��d���B
			sunken, /// �ւ��񂾋��E�B�X�^�e�B�b�N�R���g���[���̋��E�B
			client, /// ���̓I�ȋ��E�B
		};
		BALOR_NAMED_ENUM_MEMBERS(Edge);
	};


	/// �E�C���h�E�n���h����\���B�n���h���ɑ΂��鑀����܂Ƃ߂� Control �̃C���e���Z���X���g���₷������B
	class Handle : private ::balor::NonCopyable {
	public:
		/// �n���h������쐬�Bowned �� true �Ȃ�΃f�X�g���N�^�Ńn���h����j������B
		Handle(HWND handle = nullptr);
		Handle(Handle&& value);
		~Handle();
		Handle& operator=(Handle&& value);

	public:
		/// �e�̃N���C�A���g���W�n�ł̈ʒu�Ƒ傫���B
		Rectangle bounds() const;
		void bounds(const Rectangle& value);
		void bounds(int x, int y, int width, int height);
		/// parent ��e�Ɏ������ł��邩�ǂ����B
		bool checkParentingCycle(HWND parent) const;
		/// �R����ꂽ�R���g���[���B
		Control* control() const;
		void control(Control* value);
		/// �Ⴄ�v���Z�X�̃n���h�����ǂ����B
		bool differentProcess() const;
		/// �Ⴄ�X���b�h�̃n���h�����ǂ����B
		bool differentThread() const;
		/// ���E���̎�ށB
		Control::Edge edge() const;
		void edge(Control::Edge value);
		/// �g���E�C���h�E�X�^�C���B
		int exStyle() const;
		void exStyle(int value);
		/// �w�肵���X�^�C���r�b�g���S�ėL�����ǂ����B
		bool hasStyle(int bitFlags) const;
		/// �w�肵���g���X�^�C���r�b�g���S�ėL�����ǂ����B
		bool hasExStyle(int bitFlags) const;
		/// �e�E�C���h�E�n���h���B
		Control::Handle parent() const;
		/// �E�C���h�E�v���V�[�W���B
		Procedure procedure() const;
		Procedure procedure(Procedure value);
		/// �w�肵���X�^�C���r�b�g��L���܂��͖����ɂ���B
		void setStyle(int bitFlags, bool on);
		/// �w�肵���g���X�^�C���r�b�g��L���܂��͖����ɂ���B
		void setExStyle(int bitFlags, bool on);
		/// Control �� processMessage ���ĂԕW���I�ȃv���V�[�W���֐��B
		static Message::LRESULT __stdcall standardProcedure(HWND handle, unsigned int message, Message::WPARAM wparam, Message::LPARAM lparam);
		/// �E�C���h�E�X�^�C���B
		int style() const;
		void style(int value);
		/// �ύX���ꂽ style, exStyle ��\���ɔ��f����B
		void updateStyle();

	public:
		/// HWND �ւ̎����ϊ��B
		operator HWND() const { return _handle; }

	private:
		HWND _handle;
	};


	/// �q�R���g���[����񋓂���C�e���[�^�B�\���D��x�̍������i���ǉ��������j�ɗ񋓂���B�񋓂��I����ƃk����Ԃ��A�ȍ~�͑���ł��Ȃ��B
	class ControlsIterator {
	public:
		/// �\���D��x�̍ł������q����C�e���[�g�B
		ControlsIterator(const Control& parent);
		ControlsIterator(Control* current);

		/// �\���D��x�̒Ⴂ�q�ցB
		ControlsIterator& operator ++();
		/// �\���D��x�̍����q�ցB
		ControlsIterator& operator --();
		/// �񋓂��� Control �|�C���^�̎擾�B
		operator Control*() const;
		/// �񋓂��� Control �|�C���^�ւ̃A�N�Z�X�B
		Control* operator->();

		/// �\���D��x�̍ł��Ⴂ�q�̃C�e���[�^�B
		static ControlsIterator getLast(const Control& parent);

	private:
		Control* _current;
	};


	/// �S�Ă̎q����񋓂���C�e���[�^�B�񋓂��I����ƃk����Ԃ��悤�ɂȂ�A�ȍ~�͑���ł��Ȃ��B
	class DescendantsIterator {
	public:
		/// �e�N���X����쐬�B
		DescendantsIterator(const Control& parent);

		/// ���̎q���ցB
		DescendantsIterator& operator ++();
		/// �񋓂��� Control �|�C���^�̎擾�B
		operator Control*() const;
		/// �񋓂��� Control �|�C���^�ւ̃A�N�Z�X�B
		Control* operator->();

	private:
		Control* _parent;
		Control* _current;
	};



	/// Control �̃C�x���g�̐e�N���X�B
	typedef EventWithSender<Control> Event;

	typedef Event Activate;
	typedef Event Deactivate;
	typedef Event MouseEnter;
	typedef Event MouseHover;
	typedef Event MouseLeave;


	/// �J�[�\����ݒ肷��C�x���g�B�ݒ肵�Ȃ���΃R���g���[���̃f�t�H���g�ɂȂ�B
	struct CursorChange : public Control::Event {
		CursorChange(Control& control);

		/// �ݒ肷��J�[�\���B�����l�� nullptr�B
		HCURSOR cursor() const;
		void cursor(HCURSOR value);

	private:
		HCURSOR _cursor;
	};


	/// �t�H�[�J�X���������C�x���g�BComboBox �̂悤�ɃR���g���[���ɂ���Ă͎��܂��͑O�̃R���g���[�����擾�ł��Ȃ����Ƃ�����B
	/// �����̃A�v���P�[�V�����ł� onDeactivate �C�x���g�̂ق����g���₷���B
	struct Defocus : public Control::Event {
		Defocus(Control& sender, HWND nextFocusedHandle);

		/// �t�H�[�J�X�𓾂��R���g���[���B�k���̏ꍇ������B
		Control* nextFocused() const;
		/// �t�H�[�J�X�𓾂��R���g���[���̃E�C���h�E�n���h���B�k���̏ꍇ������B
		Control::Handle nextFocusedHandle() const;

	private:
		HWND _nextFocusedHandle;
	};


	/// �t�H�[�J�X�𓾂��C�x���g�BComboBox �̂悤�ɃR���g���[���ɂ���Ă͎��܂��͑O�̃R���g���[�����擾�ł��Ȃ����Ƃ�����B
	/// �����̃A�v���P�[�V�����ł� onActivate �C�x���g�̂ق����g���₷���B
	struct Focus : public Control::Event {
		Focus(Control& sender, HWND prevFocusedHandle);

		/// �t�H�[�J�X���������R���g���[���B�k���̏ꍇ������B
		Control* prevFocused() const;
		/// �t�H�[�J�X���������R���g���[���̃E�C���h�E�n���h���B�k���̏ꍇ������B
		Control::Handle prevFocusedHandle() const;

	private:
		HWND _prevFocusedHandle;
	};


	/// �w���v����v�����ꂽ�C�x���g�B�H�{�^���������ăR���g���[�����N���b�N�������AF1�L�[���������ꍇ�ɔ�������B
	/// �H�{�^�����������ꍇ�A�H�{�^���̂��� Frame ���N���b�N���Ă����������q�R���g���[���ł̂ݔ�������B���j���[�̃w���v�͖��Ή��B
	struct HelpRequest : public Control::Event {
		HelpRequest(Control& sender, Control& target, const Point& position);

		/// �������L�����Z�����Đe�R���g���[���ɂ܂����邩�ǂ����B�����l�� false�B
		bool cancel() const;
		void cancel(bool value);
		/// �}�E�X�J�[�\���̃N���C�A���g���W�B
		const Point& position() const;
		/// �w���v����v������Ă���R���g���[���B
		Control& target();

	private:
		Control& _target;
		Point _position;
		bool _cancel;
	};


	/// �L�[�����������������C�x���g�B
	struct KeyEvent : public Control::Event {
		KeyEvent(Control& sender, Key key, int flags);

		/// ALT�L�[�������ɉ�����Ă��邩�ǂ����B
		bool alt() const;
		/// ���̌�R���g���[���̏������ĂԕK�v�������ꍇ�� true �ɐݒ肷��B�����l�� false�B
		bool handled() const;
		void handled(bool value);
		/// ���������������L�[�B
		Key key() const;
		/// ���b�Z�[�W��������O�ɃL�[��������Ă������ǂ����B
		bool previousDown() const;
		/// �L�[�̃��s�[�g�񐔁B
		int repeatCount() const;

	private:
		Key _key;
		int _flags;
		bool _handled;
	};

	typedef KeyEvent KeyDown;
	typedef KeyEvent KeyUp;


	/// �L�[���͂ňꕶ�����͂��������C�x���g�B�J�b�g���y�[�X�g�͕߂炦�鎖���ł��Ȃ��B
	struct KeyPress : public Control::Event {
		KeyPress(Control& sender, wchar_t charCode);

		/// ���͂��ꂽ�����B�ύX���邱�Ƃ��ł���B
		wchar_t charCode() const;
		void charCode(wchar_t value);
		/// ���̌�R���g���[���̏������ĂԕK�v�������ꍇ�� true �ɐݒ肷��B�����l�� false�B
		bool handled() const;
		void handled(bool value);

	private:
		wchar_t _charCode;
		bool _handled;
	};


	/// �}�E�X�̃{�^�����h���b�O�����A�_�u���N���b�N�����A�J�[�\�����ړ������A�{�^���𗣂����C�x���g�B
	struct MouseEvent : public Control::Event {
		MouseEvent(Control& sender, Mouse button, Message& message);

		/// �C�x���g�̑ΏۂƂȂ�{�^���B
		Mouse button() const;
		/// CTRL �L�[��������Ă��邩�ǂ����B
		bool ctrl() const;
		/// �}�E�X�̍��{�^����������Ă��邩�ǂ����B
		bool lButton() const;
		/// �}�E�X�̒����{�^����������Ă��邩�ǂ����B
		bool mButton() const;
		/// �}�E�X�̉E�{�^����������Ă��邩�ǂ����B
		bool rButton() const;
		/// �}�E�X�̂w�P�{�^����������Ă��邩�ǂ����B
		bool xButton1() const;
		/// �}�E�X�̂w�Q�{�^����������Ă��邩�ǂ����B
		bool xButton2() const;
		/// �}�E�X�J�[�\���̃N���C�A���g���W�B
		Point position() const;
		/// Shift �L�[��������Ă��邩�ǂ����B
		bool shift() const;

	protected:
		Mouse _button;
		Message& _message;
	};
	typedef MouseEvent Drag;
	typedef MouseEvent MouseDoubleClick;
	typedef MouseEvent MouseMove;
	typedef MouseEvent MouseUp;


	/// �}�E�X�̃{�^�����������C�x���g�B
	struct MouseDown : public MouseEvent {
		MouseDown(Control& sender, Mouse button, Message& message, Rectangle& dragBox);

		///	���S�_���}�E�X�ʒu�Ƃ��� onDrag �C�x���g�𔭐�������}�E�X�̈ړ��͈́B�����l�� DragDrop::defaultDragSize() ���̑傫���B
		/// �����l�̓V�X�e�������j�^�𑜓x�iDPI�j�ɍ��킹�Ē������Ă���邪�Ǝ��ɐݒ肷��ꍇ�͎����ŃX�P�[�����O���s���� DragDrop::defaultDragSize() �̔{���Őݒ肷��Ɨǂ��B
		Rectangle dragBox() const;
		void dragBox(const Rectangle& value);
		void dragBox(int x, int y, int width, int height);

	private:
		Rectangle& _dragBox;
	};


	/// �}�E�X�z�C�[���𓮂������C�x���g�B
	struct MouseWheel : public MouseEvent {
		MouseWheel(Control& sender, Message& _message);

		/// �}�E�X�J�[�\���̃N���C�A���g���W�B
		Point position() const;
		/// �}�E�X�z�C�[���̈ړ��ʁB��O�ɓ]�����ƕ��A���ɓ]�����Ɛ��̐��ŗʂ� Mouse::wheelScrollDelta() �Ŏ擾�ł���B
		int wheelDelta() const;
	};


	/// �|�b�v�A�b�v���j���[��\������C�x���g�B
	struct PopupMenu : public Control::Event {
		PopupMenu(Control& sender, const Point& position, bool clicked);

		/// �\�����L�����Z�����ăR���g���[���̃f�t�H���g�|�b�v�A�b�v���j���[��\�����邩�A������ΐe�R���g���[���ɂ܂����邩�ǂ����B�����l�� false�B
		bool cancel() const;
		void cancel(bool value);
		/// �}�E�X�E�N���b�N���������ǂ����BShift + F10 �L�[���������ꍇ�� false�B
		bool clicked() const;
		/// �N���b�N���ꂽ�N���C�A���g���W�BShift + F10 �L�[���������ꍇ�̓N���C�A���g�̈�̌��_�ɂȂ�B
		const Point& position() const;

	private:
		Point _position;
		bool _clicked;
		bool _cancel;
	};


	/// �L�[�������ꂽ�Ƃ��ɃV���[�g�J�b�g�L�[����������C�x���g�B
	/// �L�[�������ꂽ���̏����̏��Ԃ́A�V���[�g�J�b�g�L�[�̏������������� Frame �̃V���[�g�J�b�g�L�[�̏������_�C�A���O�L�[�̏������R���g���[���̃��b�Z�[�W�̏����ƂȂ�B
	/// handled �� true �ɐݒ肷��Ə����ł����Ɣ��f���Ĉȍ~�̏������΂��� isInputKey �� true �Ȃ�΃R���g���[���̃��b�Z�[�W�������s���B
	/// handled �� false �̏ꍇ�� isInputKey �Ń_�C�A���O�L�[�̏��������Ȃ����ǂ������f����B
	/// isInputKey �̏����l�ŃR���g���[�����L�[���͂̃��b�Z�[�W������K�v�Ƃ��Ă��邩�ǂ��������f�ł���B
	/// <br><br>
	/// �� �����܂��ȏ������j<br><br>
	/// �P�D�V���[�g�J�b�g�L�[�����������ꍇ�@�@�E�E�E handled �� true �ɁAisInputKey �� false �ɐݒ肷��B<br>
	/// �Q�D�_�C�A���O�L�[�𖳌��ɂ���ꍇ�@�@�@�E�E�E isInputKey �� true �ɐݒ肷��B<br>
	/// �Q�D�_�C�A���O�L�[�ɂ���ꍇ�@�@�@�@�@�@�E�E�E isInputKey �� false �ɐݒ肷��B<br>
	/// �R�D�_�C�A���O�L�[�̏������㏑������ꍇ�E�E�E handled �� true �ɁA�����ł����ꍇ�� isInputKey �� false �ɐݒ肷��B<br>
	/// �S�D�_�C�A���O�L�[�̏��������ւ���ꍇ�E�E�E shortcut ������������B<br>
	struct ShortcutKey : public Control::Event {
		ShortcutKey(Control& sender, int shortcut, bool isInputKey);

		/// ���̌�̃V���[�g�J�b�g�L�[������_�C�A���O�L�[�̏������΂��Ȃ� true�B�����l�� false�B
		bool handled() const;
		void handled(bool value);
		/// handled �� false �Ȃ�΃_�C�A���O�L�[�̏������΂����ǂ����Bhandled �� true �Ȃ�΃R���g���[���̃��b�Z�[�W�������΂����ǂ����B
		/// �����l�̓R���g���[�������̃L�[���͂�K�v�Ƃ��Ă��邩�ǂ����B
		bool isInputKey() const;
		void isInputKey(bool value);
		/// Key �� Key::Modifier ��g�ݍ��킹���V���[�g�J�b�g�R�}���h�B�ύX���ł���B
		int shortcut() const;
		void shortcut(int value);

	private:
		int _shortcut;
		bool _isInputKey;
		bool _handled;
	};


protected:
	/// �`�悷��C�x���g�̃e���v���[�g�B�h���N���X�Ŏg�p����B
	template<typename T, typename Base>
	struct PaintEvent : public Base {
		PaintEvent(T& sender, HDC hdc) : Base(sender), _hdc(hdc) {}

		/// �`��Ɏg���O���t�B�N�X�B
		Graphics graphics() const { return Graphics(_hdc); }

	private:
		HDC _hdc;
	};


protected:
	/// �k���n���h���ō쐬�B
	Control();
	Control(Control&& value);
	virtual ~Control() = 0;

public:
	/// �e�̃N���C�A���g���W�n�ł̈ʒu�Ƒ傫���B
	virtual Rectangle bounds() const;
	virtual void bounds(const Rectangle& value);
	void bounds(int x, int y, int width, int height);
	/// �w�i�u���V�B�u���V�n���h���͎Q�Ƃ����̂Ŕj�����Ȃ��悤���ӁB
	/// ���W�I�{�^���A�`�F�b�N�{�b�N�X�A�O���[�v�{�b�N�X�A�{�^�����̂悤�ɐe�R���g���[���ƒn�����Ȏq�R���g���[���ׂ̈ɁA�e�R���g���[���͔w�i�u���V�����J����`��������B
	virtual Brush brush() const;
	virtual void brush(HBRUSH value);
	/// �w�i�u���V�̌��_�B
	virtual Point brushOrigin() const;
	virtual void brushOrigin(const Point& value);
	void brushOrigin(int x, int y);
	/// �}�E�X���L���v�`�����Ă��邩�ǂ����B
	bool captured() const;
	void captured(bool value);
	/// �R���g���[�����_���猩���N���C�A���g�̈�̈ʒu�B
	Point clientOrigin() const;
	/// �N���C�A���g�̈�̋�`�B�ʒu�͏�� Point(0, 0)�B
	Rectangle clientRectangle() const;
	/// �N���C�A���g�̈�̑傫���B
	Size clientSize() const;
	virtual void clientSize(const Size& value);
	void clientSize(int width, int height);
	/// �R���g���[���̑傫������N���C�A���g�̈�̑傫�������߂�B
	virtual Size clientSizeFromSize(const Size& size) const;
	/// �N���C�A���g���W�n����X�N���[�����W�n�ɕϊ�����B
	Point clientToScreen(const Point& point) const;
	Rectangle clientToScreen(const Rectangle& rect) const;
	/// control ���q���Ɋ܂܂�邩�ǂ����B
	bool contains(HWND control) const;
	/// �����܂��͎q�����t�H�[�J�X�𓾂Ă��邩�ǂ����B
	bool containsFocus() const;
	/// �őO�ʂ̎q�R���g���[������i�ǉ��������j�񋓂���C�e���[�^�B
	Control::ControlsIterator controlsBegin() const;
	/// �Ō�ʂ̎q�R���g���[������i�ǉ������t���j�񋓂���C�e���[�^�B
	Control::ControlsIterator controlsLast() const;
	/// ����̃t�H���g�B
	static Font defaultFont();
	/// �S�Ă̎q����񋓂���C�e���[�^�B
	Control::DescendantsIterator descendantsBegin() const;
	/// �X�N���[���ʒu��X�N���[���͈͂��l���������z�I�ȃN���C�A���g���W�Ƒ傫���B
	virtual Rectangle displayRectangle() const;
	/// �r�b�g�}�b�v�ɃR���g���[����`�悷��B
	void drawTo(HBITMAP bitmap) const;
	/// ���͂��󂯕t���邩�ǂ����B
	virtual bool enabled() const;
	virtual void enabled(bool value);
	/// �R���g���[���̑����� Frame ��������B������Ȃ��ꍇ�� nullptr ��Ԃ��B
	virtual Frame* findFrame();
	/// controlsBegin() �œ�����ŏ��̎q�R���g���[���� bounds()�B
	Rectangle firstBounds() const;
	/// �t�H�[�J�X�𓾂�B
	void focus();
	/// �t�H�[�J�X�𓾂��邩�ǂ����BTAB �L�[������L�[�ňړ�����Ώۂɂ������Ȃ��ꍇ�� false ��Ԃ��悤�ɏ㏑������BtabStop �����ł͕����L�[�Ńt�H�[�J�X�𓾂�B
	virtual bool focusable() const;
	/// �t�H�[�J�X�𓾂Ă��邩�ǂ����B
	virtual bool focused() const;
	/// �\���Ɏg���t�H���g�B�����l�� defaultFont()�B�t�H���g�n���h���͎Q�Ƃ����̂Ŕj�����Ȃ��悤�ɒ��ӁB
	virtual Font font() const;
	virtual void font(HFONT value);
	/// �E�C���h�E�n���h������R���g���[�����擾����B�R���g���[�����R���Ă��Ȃ��ꍇ�� nullptr ��Ԃ��B
	static Control* fromHandle(HWND handle);
	/// �w�肵���N���C�A���g���W�Ɏq�R���g���[��������ΕԂ��B������� nullptr ��Ԃ��B
	Control* getChildAt(const Point& clientPoint, bool skipInvisible = false, bool skipDisabled = false, bool skipTransparent = false) const;
	/// �^�u�I�[�_�[���� start �̎��̎q�R���g���[����Ԃ��Bforward �� false �Ȃ�ΑO�̃R���g���[����Ԃ��B�����ꍇ�� nullptr ��Ԃ��B
	/// start �͎q�R���g���[�����������g�łȂ���΂Ȃ�Ȃ��Bstart ���������g�Ȃ�� forward �ɂ���ă^�u�I�[�_�[���ŏ��܂��͍Ō�̎q�R���g���[����Ԃ��B
	Control* getNextControl(Control& start, bool forward) const;
	Control* getNextControl(Control& start, bool forward, bool tabStopOnly, bool nested, bool wrap);
	/// ������ 0 ���w�肵�������̂݌��݂̏�ԂɍœK�ȑ傫�������߂�B0 �ȊO���w�肵�������͂��̂܂ܕԂ�B�R���g���[���̎�ނɂ���ċ��ߕ����Ⴄ�B
	/// �R���g���[���ɂ���Ă� width �� 0 �ȊO��n���� height �� 0 ���w�肷�邱�Ƃ� width ���Œ肵���ꍇ�̍œK�� height �������߂���B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// �E�C���h�E�n���h���B������n���h���͕K���쐬�ς݂ŁA���݂̃X���b�h�Ŏg�p�ł���B�����łȂ���� assert �Ōx�����o���B
	HWND handle() const;
	/// �}�E�X�J�[�\�����R���g���[���̏�ɂ��邩�ǂ����B
	bool hot() const;
	/// �R���g���[�� ID�Bbalor ���C�u�����ł̓C�x���g�� Listener ���g���̂Ŏg���Ȃ��B�A�v���P�[�V�����ŗL�̔ԍ���t�������ꍇ�Ɏg���B
	int id() const;
	void id(int value);
	/// controlsLast() �œ�����ŏ��̎q�R���g���[���� bounds()�B
	Rectangle lastBounds() const;
	/// �S�̂܂��͎w�肵���̈�𖳌��ɂ��čĕ`�悳���悤�ɂ���B
	void invalidate(bool invalidateChildren = false);
	void invalidate(const Rectangle& rect, bool invalidateChildren = false);
	void invalidate(HRGN region, bool invalidateChildren = false);
	/// �R���g���[���������郁�b�Z�[�W���[�v�̃X���b�h�� function �����s����B���̃X���b�h����R���g���[���𑀍삷��ꍇ�Ɏg���B
	/// synchronous �� function �̎��s���I���܂ő҂��ǂ����B������߂�l�̓����_�����g���Ď󂯓n������Ηǂ��B
	void invoke(const std::tr1::function<void ()>& function, bool synchronous = true);
	/// �R���g���[�������݂̃X���b�h���瑀�삷�ׂ��ł͂Ȃ����ǂ����Btrue �̏ꍇ�� invoke() �֐����g���K�v������B
	bool invokeRequired() const;
	/// onMouseHover �C�x���g����������܂ł̃}�E�X�Î~�̎��ԁi�~���b�j�B�����l�� 100�B
	int mouseHoverTime() const;
	void mouseHoverTime(int value);
	/// �C���X�^���X�����ʂ��閼�O�B
	const String& name() const;
	void name(String value);
	/// ������������ Frame �� activeControl �ɂȂ����C�x���g�BonFocus �Ƃ̈Ⴂ�� activeControl �� Frame ��̃t�H�[�J�X�J�ڂ�����ǐՂ���̂�
	/// �|�b�v�A�b�v���j���[��_�C�A���O�\�����ł��������C�x���g���������Ȃ����ƁB�������������g�b�v���x���� Frame �ł���ꍇ�̓A�N�e�B�u�E�C���h�E�ɂȂ������̃C�x���g�ɂȂ�B
	Listener<Control::Activate&>& onActivate();
	/// �J�[�\����ݒ肷��C�x���g�B
	Listener<Control::CursorChange&>& onCursorChange();
	/// ������������ Frame �� activeControl �ł͂Ȃ��Ȃ����C�x���g�BonDefocus �Ƃ̈Ⴂ�� activeControl �� Frame ��̃t�H�[�J�X�J�ڂ�����ǐՂ���̂�
	/// �|�b�v�A�b�v���j���[��_�C�A���\���O���ł��������C�x���g���������Ȃ����ƁB�������������g�b�v���x���� Frame �ł���ꍇ�̓A�N�e�B�u�E�C���h�E�ł͂Ȃ��Ȃ������̃C�x���g�ɂȂ�B
	Listener<Control::Deactivate&>& onDeactivate();
	/// �t�H�[�J�X���������C�x���g�B
	Listener<Control::Defocus&>& onDefocus();
	/// ���܂��͒����܂��͉E�}�E�X�{�^���Ńh���b�O���n�߂��C�x���g�BonMouseDown �C�x���g�Ńh���b�O���J�n����ړ��͈͂��w��ł���B
	Listener<Control::Drag&>& onDrag();
	/// �t�H�[�J�X�𓾂��C�x���g�B
	Listener<Control::Focus&>& onFocus();
	/// �w���v����v�����ꂽ�C�x���g�B
	Listener<Control::HelpRequest&>& onHelpRequest();
	/// �L�[���������C�x���g�B
	Listener<Control::KeyDown&>& onKeyDown();
	/// �L�[���͂ňꕶ�����͂����C�x���g�B�iWM_CHAR ���b�Z�[�W�j
	Listener<Control::KeyPress&>& onKeyPress();
	/// �L�[�𗣂����C�x���g�B
	Listener<Control::KeyUp&>& onKeyUp();
	/// �}�E�X�{�^�����_�u���N���b�N�����C�x���g�B
	Listener<Control::MouseDoubleClick&>& onMouseDoubleClick();
	/// �}�E�X�{�^�����������C�x���g�B
	Listener<Control::MouseDown&>& onMouseDown();
	/// �}�E�X�J�[�\�����R���g���[����ɓ������C�x���g�B
	Listener<Control::MouseEnter&>& onMouseEnter();
	/// �}�E�X�J�[�\���� mouseHoverTime() ���Î~�����C�x���g�B
	Listener<Control::MouseHover&>& onMouseHover();
	/// �}�E�X�J�[�\�����R���g���[���ォ��o���C�x���g�B
	Listener<Control::MouseLeave&>& onMouseLeave();
	/// �}�E�X�J�[�\���𓮂������C�x���g�B
	Listener<Control::MouseMove&>& onMouseMove();
	/// �}�E�X�{�^���𗣂����C�x���g�B
	Listener<Control::MouseUp&>& onMouseUp();
	/// �}�E�X�z�C�[���𓮂������C�x���g�B
	Listener<Control::MouseWheel&>& onMouseWheel();
	/// �|�b�v�A�b�v���j���[��\������C�x���g�B�������Ȃ������ꍇ�͐e�E�C���h�E�ŏ�������B
	Listener<Control::PopupMenu&>& onPopupMenu();
	/// �L�[�������ꂽ�Ƃ��ɃV���[�g�J�b�g�L�[����������C�x���g�B
	Listener<Control::ShortcutKey&>& onShortcutKey();
	/// �e�R���g���[���B
	virtual Control* parent() const;
	virtual void parent(Control* value);
	/// �e�R���g���[���̃N���C�A���g���W�n�ɂ����邱�̃R���g���[���̈ʒu�B
	Point position() const;
	virtual void position(const Point& value);
	void position(int x, int y);
	/// �R���g���[���̕\���̈�B���w��̏ꍇ�̓k���̗̈悪�Ԃ�B�ݒ��A�̈�n���h���͎Q�Ƃ���Ȃ��B�C�ӂ̌`�̃R���g���[��������B
	Region region() const;
	void region(HRGN value);
	/// �傫���� getPreferredSize(0, 0) �ŋ��߂čX�V����B
	void resize();
	/// scale �֐��ő傫�����X�P�[�����O���邩�ǂ����B�����l�� true�B�X�P�[�����O���K�v�Ȃ����A�Ǝ��ɍs���ꍇ�� false�ɐݒ肷��B
	bool scalable() const;
	void scalable(bool value);
	/// Scaler ���g���ăR���g���[�����X�P�[�����O����B
	virtual void scale(const Scaler& scaler);
	/// �X�N���[�����W�n����N���C�A���g���W�n�ɕϊ�����B
	Point screenToClient(const Point& point) const;
	Rectangle screenToClient(const Rectangle& rect) const;
	/// �傫���B
	Size size() const;
	void size(const Size& value);
	void size(int width, int height);
	/// �N���C�A���g�̈�̑傫������R���g���[���̑傫�������߂�B
	virtual Size sizeFromClientSize(const Size& clientSize) const;
	/// �^�u�L�[���������Ƃ��Ƀt�H�[�J�X�̈ڂ鏇�ԁB�����l�� 0�B
	int tabIndex() const;
	void tabIndex(int value);
	/// �^�u�L�[���������Ƃ��ɂ��̃R���g���[���Ƀt�H�[�J�X���ڂ��邩�ǂ����B
	bool tabStop() const;
	void tabStop(bool value);
	/// ������B�R���g���[���ɂ���ă^�C�g���������胉�x����������G�f�B�b�g���e��������l�X�B
	String text() const;
	virtual void text(StringRange value);
	void textToBuffer(StringBuffer& buffer) const;
	/// �`��X�V�ł��邩�ǂ����B�`��ŕ\����������ꍇ�ɕ`��O�� false �ɐݒ肵�ĕ`���� true �ɐݒ肵�A���̌� update �֐������ĂԁB
	void updatable(bool value);
	/// �����ȗ̈�����̏�ŕ`�悷��B
	void update();
	/// ���[�U�����R�Ɏg����C�ӂ̃f�[�^�B
	UniqueAny& userData();
	void userData(UniqueAny&& value);
	/// �\�����Ă��邩�ǂ����B
	bool visible() const;
	virtual void visible(bool value);
	/// �e�̉e�����ʂ��ɂ��ĕ\������邩�ǂ����B
	bool visibleExceptParent() const;
	/// ���̃R���g���[���ʂŃr�W���A���X�^�C�����L�����ǂ����B�V�X�e���S�̂ŗL�����ǂ����� System::visualStyleEnabled() �֐��Œ��ׂ���B
	/// Frame �̊O�ς͕ς��Ȃ��͗l�B
	bool visualStyle() const;
	void visualStyle(bool value);
	/// �\���D��x�B�������قǎ�O�ɕ\�������B0 ���w�肷��ƍőO�ʂɁA-1 ���w�肷��ƍŌ�ʂɈړ�����B
	int zOrder() const;
	virtual void zOrder(int value);

public:
	/// HWND �ւ̎����ϊ� & null �`�F�b�N�p�B
	operator HWND() const;


protected:
	/// �쐬���ꂽ�E�C���h�E�n���h�����R���g���[���Ɋ��蓖�Ă�B�t�H���g���ݒ肳��ĂȂ���� defaultFont() �ɐݒ肷��B
	void attachHandle(HWND handle);
	//// �}�E�X�g���b�L���O���łȂ���΃}�E�X�g���b�L���O���J�n���� onMouseEnter �C�x���g�𔭐�������B
	void beginMouseTracking(int mouseHoverTime);
	/// �E�C���h�E�n���h����j������B
	void destroyHandle();
	//// �}�E�X�g���b�L���O���Ȃ�΃}�E�X�g���b�L���O���I������ onMouseLeave �C�x���g�𔭐�������B
	void endMouseTracking();
	//// �L�[���͂��_�C�A���O�L�[�ł͂Ȃ��R���g���[���ŏ�������K�v�����邩�ǂ����B
	virtual bool isInputKey(int shortcut) const;
	/// ���b�Z�[�W���[�v���� TranslateMessage �֐��̑O�ɌĂ�ŃL�[���͂𒲂ׁA�V���[�g�J�b�g�L�[��_�C�A���O�L�[�Ȃ�Ώ������� true ��Ԃ��B
	/// �������Ȃ������� false ��Ԃ��Btrue ���Ԃ����ꍇ�̓��b�Z�[�W�͏����ς݂Ȃ̂�TranslateMessage �֐��� DispatchMessageW �֐����ĂԕK�v�͖����B
	static bool preTranslateMessage(Message& msg);
	/// �_�C�A���O�L�[���������ď����ł������ǂ�����Ԃ��B
	virtual bool processDialogKey(int shortcut);
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);
	/// ���̃R���g���[���̃��b�Z�[�W����������B
	static void processMessage(Control& control, Message& msg);
	/// �f�t�H���g�E�C���h�E�v���V�[�W���Ń��b�Z�[�W����������B
	void processMessageByDefault(Message& msg);
	/// �}�E�X�{�^�����������Ƃ��̋��ʏ����B
	void processMouseDown(MouseDown&& event);
	/// �}�E�X�{�^���𗣂����Ƃ��̋��ʏ����B
	void processMouseUp(MouseUp&& event);
	/// �w�肵���E�C���h�E�n���h���Ƀ��b�Z�[�W��]������B���b�Z�[�W���������ꂽ���ǂ�����Ԃ��B
	static bool reflectMessage(HWND handle, Message& msg);
	//// �}�E�X�g���b�L���O���Ȃ�� onMouseHover �C�x���g�̔��������� mouseHoverTime �~���b�قǉ��΂��B
	void resetMouseTracking(int mouseHoverTime);
	/// Frame �� Panel ���ŋ��ʂ��Ďg���E�C���h�E�N���X���B
	static const wchar_t* userClassName();


protected: // processMessage ���I�[�o�[���C�h���āu�����I�Ɂv�������������Ǝv�����Ƃ��ɂ���炪 private ���Ə�Q�ɂȂ肦��B
		   // �u�����I�Ɂv���������ł���悤�ɏ������א؂�ɂ��� protected �̊֐��ɂ���������S�Ȃ̂͊ԈႢ�Ȃ����V���v���ł͂Ȃ��B

	/// ���b�Z�[�W���t���N�V�����p�̃��b�Z�[�W�ԍ��B
	static const int wmReflect = 0x2000;

	/// �E�C���h�E�n���h���B
	Handle _handle;
	/// �f�t�H���g�E�C���h�E�v���V�[�W���BprocessMessageByDefault �֐�����Ă΂��B
	Procedure _defaultProcedure;
	/// �}�E�X�g���b�L���O�����ǂ����B
	bool _mouseTracked;
	/// �}�E�X�����͈̔͂���o���� onDrag �C�x���g�𔭐�������B
	Rectangle _dragBox;
	HBRUSH _brush;
	Point _brushOrigin;
	int _mouseHoverTime;
	String _name;
	int _tabIndex;
	bool _scalable;
	UniqueAny _userData;
	Listener<Control::Activate&> _onActivate;
	Listener<Control::CursorChange&> _onCursorChange;
	Listener<Control::Deactivate&> _onDeactivate;
	Listener<Control::Defocus&> _onDefocus;
	Listener<Control::Drag&> _onDrag;
	Listener<Control::Focus&> _onFocus;
	Listener<Control::HelpRequest&> _onHelpRequest;
	Listener<Control::KeyDown&> _onKeyDown;
	Listener<Control::KeyPress&> _onKeyPress;
	Listener<Control::KeyUp&> _onKeyUp;
	Listener<Control::MouseDoubleClick&> _onMouseDoubleClick;
	Listener<Control::MouseDown&> _onMouseDown;
	Listener<Control::MouseEnter&> _onMouseEnter;
	Listener<Control::MouseHover&> _onMouseHover;
	Listener<Control::MouseLeave&> _onMouseLeave;
	Listener<Control::MouseMove&> _onMouseMove;
	Listener<Control::MouseUp&> _onMouseUp;
	Listener<Control::MouseWheel&> _onMouseWheel;
	Listener<Control::PopupMenu&> _onPopupMenu;
	Listener<Control::ShortcutKey&> _onShortcutKey;
};



	}
}