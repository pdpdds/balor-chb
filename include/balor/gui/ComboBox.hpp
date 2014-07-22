#pragma once

#include <balor/gui/Control.hpp>
#include <balor/gui/Edit.hpp>
#include <balor/gui/ListBox.hpp>
#include <balor/StringRangeArray.hpp>


namespace balor {
	namespace gui {



/**
 * �R���{�{�b�N�X�B
 *
 * �R���{�{�b�N�X�̓G�f�B�b�g�R���g���[���ƃ��X�g�{�b�N�X���܂�ł���A���ꂼ�� edit�Alist �֐��ŃR���g���[�����擾�ł���B
 * ComboBox �N���X�łł��Ȃ�����͂��̊֐��œ���ꂽ�R���g���[���ɑ΂��čs���B�R���{�{�b�N�X�̓h���b�v�_�E���\��������{�^���̕����ɂȂ�B
 * ���邢�� style() �� ComboBox::Style::dropDownList �̏ꍇ�̓G�f�B�b�g�R���g���[�����Ȃ��A���̕����̓R���{�{�b�N�X�ɂȂ�B
 * onFocus �y�� onDefocus �C�x���g�ł͑O�̃t�H�[�J�X�A���̃t�H�[�J�X�R���g���[���𓾂��Ȃ��B
 * edit() �� list() �� tabWidth() �͐ݒ�ł��Ȃ��͗l�B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"ComboBox Sample");

	const wchar_t* items[] = {
		L"���",
		L"�o�i�i",
		L"�p�C�i�b�v��",
		L"�X�C�J"
	};
	ComboBox combo(frame, 20, 10, 0, 0, items);
	combo.edit().textColor(Color::red());

	frame.runMessageLoop();
 * </code></pre>
 */
class ComboBox : public Control {
public:
	/// �R���{�{�b�N�X�̃X�^�C���B
	struct Style {
		enum _enum {
			simple       = 0x0001L, /// �G�f�B�b�g�̉��Ƀ��X�g�{�b�N�X����ɕ\������B
			dropDown     = 0x0002L, /// �G�f�B�b�g�ׂ̗̃{�^���������ƃ��X�g�{�b�N�X���\�������B
			dropDownList = 0x0003L, /// �G�f�B�b�g�͓��͕s�\�ŗׂ̃{�^���������ƃ��X�g�{�b�N�X���\�������B
		};
		BALOR_NAMED_ENUM_MEMBERS(Style);
	};


	/// �R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none             = 0      ,
			noHScroll        = 0x0040L, /// ���͕����񂪉E�ɂ͂ݏo��ꍇ�ɃX�N���[�������A����ȏ���͂ł��Ȃ�����B
			noIntegralHeight = 0x0400L, /// ���X�g�{�b�N�X�̍����������I�ɍ��ڂ̍����̔{���ɒ��߂���̂���߂�Bstyle() �� ComboBox::Style::simple �Ń��X�g�{�b�N�X�̔w�i�̐F��ς���ꍇ�ɉe������B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


	/// �R���{�{�b�N�X��̃G�f�B�b�g�R���g���[���B
	class Edit : public ::balor::gui::Edit {
		friend ComboBox;

		Edit();
		Edit(Edit&& value);
		Edit(HWND handle);
		~Edit();
		Edit& operator=(Edit&& value);

	private:
		/// �t�H�[�J�X�C�x���g�� ComboBox �ŁB
		Listener<Control::Defocus&>& onDefocus();
		/// �t�H�[�J�X�C�x���g�� ComboBox �ŁB
		Listener<Control::Focus&>& onFocus();

	public:
		/// �e�ύX���֎~�B
		using Control::parent;
		virtual void parent(Control* );

	protected:
		//// �L�[���͂��_�C�A���O�L�[�ł͂Ȃ��R���g���[���ŏ�������K�v�����邩�ǂ����B
		virtual bool isInputKey(int shortcut) const;
		/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
		virtual void processMessage(Message& msg);
	};


	/// �R���{�{�b�N�X��̃��X�g�{�b�N�X�B
	class List : public ::balor::gui::ListBox {
		friend ComboBox;

		List();
		List(List&& value);
		List(HWND handle);
		~List();
		List& operator=(List&& value);

	private:
		/// �t�H�[�J�X�C�x���g�� ComboBox �ŁB
		Listener<Control::Defocus&>& onDefocus();
		/// �t�H�[�J�X�C�x���g�� ComboBox �ŁB
		Listener<Control::Focus&>& onFocus();

	public:
		/// �e�ύX���֎~�B
		using Control::parent;
		virtual void parent(Control* );
	};


	/// �R���{�{�b�N�X�̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<ComboBox, Control::Event> Event;

	typedef Event CloseUp;
	typedef Event DropDown;
	typedef Event Select;
	typedef Event SelectCancel;
	typedef Event SelectEnd;


public:
	/// �k���n���h���ō쐬�B
	ComboBox();
	ComboBox(ComboBox&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫���A�X�^�C������쐬�B
	ComboBox(Control& parent, int x, int y, int width, int height, ComboBox::Style style = Style::dropDown, ComboBox::Options options = Options::none);
	/// �e�A�ʒu�A�傫���A���ڔz��A�X�^�C������쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	ComboBox(Control& parent, int x, int y, int width, int height, StringRangeArray items, ComboBox::Style style = Style::dropDown, ComboBox::Options options = Options::none);
	virtual ~ComboBox();
	ComboBox& operator=(ComboBox&& value);

public:
	/// �h���b�v�_�E����\���������̈ʒu�Ƒ傫���B
	Rectangle boundsWithDropDown() const;
	/// �h���b�v�_�E�����J�n����{�^���̋�`�B
	Rectangle dropDownButtonBounds() const;
	/// �h���b�v�_�E�����J�n����{�^����������Ă��邩�ǂ����B
	bool dropDownButtonIsPushed() const;
	/// �h���b�v�_�E�����\������Ă��邩�ǂ����B
	bool dropDowned() const;
	void dropDowned(bool value);
	/// �h���b�v�_�E���̃X�N���[���\�ȕ��B
	int dropDownScrollWidth() const;
	void dropDownScrollWidth(int value);
	/// �h���b�v�_�E���̕��B�R���{�{�b�N�X�̕���菬�����͂Ȃ�Ȃ��Bstyle() �� ComboBox::Style::simple �̏ꍇ�͏�ɃR���{�{�b�N�X�̕��Ɠ����B
	int dropDownWidth() const;
	void dropDownWidth(int value);
	/// �R���{�{�b�N�X��̃G�f�B�b�g�R���g���[���Bstyle() �� ComboBox::Style::DropDownList �̏ꍇ�͍쐬����Ȃ��B
	ComboBox::Edit& edit();
	const ComboBox::Edit& edit() const;
	/// �G�f�B�b�g�̕����̍����Bstyle() �� ComboBox::Style::simple �ł��� options() �� ComboBox::Options::noIntegralHeight ��ݒ肵�Ȃ������ꍇ�͂��܂��ύX�ł��Ȃ��B
	int editHeight() const;
	void editHeight(int value);
	/// �����L�[�Ńh���b�v�_�E���J�����ǂ����Btrue �̏ꍇ�̓}�E�X�z�C�[���őI���ł��Ȃ��Ȃ�Bfalse �̏ꍇ�� F4 �L�[�ŊJ���B�����l�� false�B
	bool extendedUI() const;
	void extendedUI(bool value);
	/// �t�H�[�J�X�𓾂��邩�ǂ����B
	virtual bool focused() const;
	/// �K�؂ȃR���g���[���T�C�Y�Bfont, style, items �̒l�ɂ���čœK�ȑ傫����Ԃ��B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// �R���{�{�b�N�X��̃��X�g�{�b�N�X�B
	ComboBox::List& list();
	const ComboBox::List& list() const;
	/// �h���b�v�_�E�����X�g�����ڂ����܂ŕ\���ł��邩�B���݂̍��ڐ���菬�����ꍇ�̓X�N���[���o�[���\�������B
	/// options() �� ComboBox::Options::noIntegralHeight ��ݒ肵�����Astyle() �� ComboBox::Style::simple �̏ꍇ�͖����B
	/// �����l�� 30�B���̊֐��̎g�p�ɂ� EnableVisualStyle.hpp �̃C���N���[�h���K�v�B
	int maxVisibleItemCount() const;
	void maxVisibleItemCount(int value);
	/// �h���b�v�_�E����������̃C�x���g�B
	Listener<ComboBox::CloseUp&>& onCloseUp();
	/// �h���b�v�_�E����\���������̃C�x���g�B
	Listener<ComboBox::DropDown&>& onDropDown();
	/// �I�����ڂ�ύX�������̃C�x���g�B�h���b�v�_�E���\�����ɖ��L�[�����������͋N���邪�}�E�X�ړ��ł͋N���Ȃ��B
	Listener<ComboBox::Select&>& onSelect();
	/// ���ڂ�I�������Ƀh���b�v�_�E����������̃C�x���g�BESC �L�[�⑼�̃R���g���[���Ƀt�H�[�J�X���ڂ����ꍇ�B
	Listener<ComboBox::SelectCancel&>& onSelectCancel();
	/// ���ڂ�I�����ăh���b�v�_�E����������̃C�x���g�B
	Listener<ComboBox::SelectEnd&>& onSelectEnd();
	///	�R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B
	ComboBox::Options options() const;
	/// ���ݑI�����Ă��鍀�ڂ̃C���f�b�N�X�B�I�����Ă��Ȃ����A�I����Ɉ�x�ł�������ҏW������ -1 ���Ԃ�B
	int selectedIndex() const;
	void selectedIndex(int value);
	/// �R���{�{�b�N�X�̃X�^�C���B
	ComboBox::Style style() const;

protected:
	//// �L�[���͂��_�C�A���O�L�[�ł͂Ȃ��R���g���[���ŏ�������K�v�����邩�ǂ����B
	virtual bool isInputKey(int shortcut) const;
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

	Edit _edit;
	List _list;
	Listener<ComboBox::CloseUp&> _onCloseUp;
	Listener<ComboBox::DropDown&> _onDropDown;
	Listener<ComboBox::Select&> _onSelect;
	Listener<ComboBox::SelectCancel&> _onSelectCancel;
	Listener<ComboBox::SelectEnd&> _onSelectEnd;
};



	}
}