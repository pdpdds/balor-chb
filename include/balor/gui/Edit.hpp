#pragma once

#include <balor/graphics/Color.hpp>
#include <balor/gui/Control.hpp>
#include <balor/gui/Padding.hpp>
#include <balor/Enum.hpp>
#include <balor/StringBuffer.hpp>

struct HBITMAP__;


namespace balor {
	namespace gui {


/**
 * �G�f�B�b�g�R���g���[���B
 * 
 * options() �� Edit::Options::multiline ��ݒ肵���ꍇ�̂ݗL���ȋ@�\�����邪�A
 * options() �� Edit::Options::multiline | Edit::Options::noVScroll ��ݒ肷��Έ�s�G�f�B�b�g�ł���Ȃ��畡���s�̏ꍇ�̋@�\���g����B
 * �I�[�g�R���v���[�g�@�\���g�������ꍇ�� AutoComplete �N���X���g�p����B
 * Tab �L�[�� Enter �L�[�ɂ��Ă� onShortcutKey �C�x���g�ŋ�����ύX�ł���BControl::ShortcutKey �N���X�̃h�L�������g���Q�ƁB
 * onTextChange �C�x���g���������邱�Ƃœ��͐�����u���ɑΉ��ł���B�ionKeyPress �C�x���g�ł͓\��t����؂���ɑΉ��ł��Ȃ��j
 * �ȉ��͂Ђ炪�Ȃ��J�^�J�i�ɋ����ϊ������B
 *<pre><code>
 *	Edit edit(frame, 10, 10, 100, 20);
 *	edit.onTextChange() = [&] (Edit::TextChange& e) {
 *		StringBuffer buffer(e.newText());
 *		for (auto i = buffer.begin(), end = buffer.end(); i != end; ++i) {
 *			if (L'��' <= *i && *i <= L'��') {
 *				*i += L'�@' - L'��';
 *			}
 *		}
 *		e.newText(buffer);
 *	};
 *</code></pre>
 * ��L�̗�̂悤�ɏ�ɕ������ݒ肵�����ƃI�[�g�R���v���[�g�@�\���g���ꍇ�ɕs����o��̂�
 * ���ł���� onKeyPress �C�x���g�� onPaste �C�x���g�𕹗p����̂��ǂ��B
 * 
 * IME �֘A�͓��{����̏ꍇ�̂ݓ��삷��B����ȊO�ł͉���ݒ肵�Ă���������B
 * ����̎����ł� imeFixed() �� true �̏ꍇ�ł��A�}�E�X�� IME ����o�[�𑀍삷��Ǝ��̂P�����̓��͂͌Œ肳�ꂽ�ݒ�ɖ߂�O�̓��͂ɂȂ�B
 * �@������ďC�����������ǂ̓��y�[�X�g���ɑΉ�����ׂɕʂ̓��͐����͕K�{�B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Edit Sample");

	Edit edit(frame, 20, 10, 0, 0, 10);
	Button button(frame, 20, 50, 0, 0, L"���l����", [&] (Button::Click& ) {
		MsgBox::show(L"���͂������l��\n\n" + edit.text());
	});
	frame.acceptButton(&button); // �G�f�B�b�g�R���g���[����� Enter �L�[�������Ɣ�������悤�ɂ���B

	// �����_���܂ސ��l�̂ݓ��͂ł���悤�ɂ���BC++ �W�����K�\�����C�u������ #include <regex>
	std::wregex editRegex(L"-?[0-9]*\\.?[0-9]*");
	edit.onTextChange() = [&] (Edit::TextChange& e) {
		auto text = e.newText();
		if (!std::regex_match(text.begin(), text.end(), editRegex)) {
			e.cancel(true);
		}
	};
	edit.imeMode(Edit::ImeMode::alphaHalf);
 
	frame.runMessageLoop();
 * </code></pre>
 */
class Edit : public Control {
public:
	typedef ::HBITMAP__* HBITMAP;

	/// �ҏW������̔z�u�B
	struct Align {
		enum _enum {
			left   = 0x0000, /// �������B
			center = 0x0001, /// ���������B
			right  = 0x0002, /// �E�����B
		};
		BALOR_NAMED_ENUM_MEMBERS(Align);
	};


	/// IME �̕ϊ����[�h�B
	struct ImeConvert {
		enum _enum {
			default            = 0xFFFF, /// OS �ɔC����B
			general            = 0x0008, /// ��ʁB
			personAndPlaceName = 0x0001, /// �l��/�n���B
			informal           = 0x0010, /// �b�����t�B
			none               = 0x0000, /// ���ϊ��B
		};
		BALOR_NAMED_ENUM_MEMBERS(ImeConvert);
	};


	/// IME �̓���B
	struct ImeMode {
		enum _enum {
			default      = 0x1000, /// OS �ɔC����B
			on           = 0x2000, /// IME��L���ɂ���B
			off          = 0x3000, /// IME�𖳌��ɂ���B
			disabled     = 0x4000, /// IME�𖳌��ɂ��ă��[�U���L�����ł��Ȃ�����B
			hiragana     = 0x0009, /// �Ђ炪�ȁB
			katakana     = 0x000b, /// �S�p�J�^�J�i�B
			katakanaHalf = 0x0003, /// ���p�J�^�J�i�B
			alpha        = 0x0008, /// �S�p�p���B
			alphaHalf    = 0x0000, /// ���p�p���B
		};
		BALOR_NAMED_ENUM_MEMBERS(ImeMode);
	};


	/// IME �̋�����\���t���O�B�g�ݍ��킹�Ŏw�肷��B
	struct ImeStatus {
		enum _enum {
			none                = 0     ,
			noKeyPress          = 0x0001, /// IME�̓��͌��ʂɂ��� onKeyPress �C�x���g�iWM_CHAR ���b�Z�[�W�j�𔭐������Ȃ��B
			cancelOnGotFocus    = 0x0002, /// �t�H�[�J�X�𓾂��Ƃ� IME �̓��͓r���̓��e��j������B
			completeOnLostFocus = 0x0004, /// �t�H�[�J�X�������Ƃ� IME �̓��͓r���̓��e����͊�������B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(ImeStatus);
	};


	/// �R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none           = 0      ,
			multiline      = 0x0004L, /// �����s���͂ł���悤�ɂ���BTab �L�[�AEnter�L�[�AEsc �L�[���_�C�A���O�L�[�Ƃ݂Ȃ���Ȃ��Ȃ�B
			noHScroll      = 0x0080L, /// ���͕������E�ɂ͂ݏo��ꍇ�ɉE�ɃX�N���[�������Ɏ������s����B
			noVScroll      = 0x0040L, /// ���͕��������ɂ͂ݏo��ꍇ�ɉ��ɃX�N���[�������ɂ���ȏ���͂ł��Ȃ��Ȃ�B
			alwaysSelected = 0x0100L, /// �t�H�[�J�X���������ł�������̑I����Ԃ�\������B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


	/// ������̑I����ԁB
	struct Selection {
		Selection() {}
		Selection(int index, int length) : index(index), length(length) {}

		/// �I�����J�n���镶���C���f�b�N�X�B
		int index;
		/// �I�����Ă��镶�����B
		int length;
	};


	/// Label �̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<Edit, Control::Event> Event;


	/// �N���b�v�{�[�h�̕������\��t����C�x���g�B
	struct Paste : public Edit::Event {
		Paste(Edit& sender);

		/// �\��t�����L�����Z�����邩�ǂ����B�����l�� false�B
		bool cancel() const;
		void cancel(bool value);
		/// �\��t���镶����B
		String text() const;

	private:
		bool _cancel;
	};


	/// �������ύX���ĕ\���ɔ��f���钼�O�̃C�x���g�B
	struct TextChange : public Edit::Event {
		TextChange(Edit& sender);

		/// �ύX���L�����Z�����邩�ǂ����B�����l�� false�B
		bool cancel() const;
		void cancel(bool value);
		/// �ύX��̑I����ԁB
		Edit::Selection newSelection() const;
		void newSelection(const Edit::Selection& value);
		/// �ύX��̕�����B
		String newText() const;
		void newText(StringRange value);
		/// �ύX�O�̑I����ԁB
		Edit::Selection oldSelection() const;
		/// �ύX�O�̕�����B
		String oldText() const;

	private:
		bool _cancel;
	};


public:
	/// �k���n���h���ō쐬�B
	Edit();
	Edit(Edit&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫������쐬�B
	Edit(Control& parent, int x, int y, int width, int height, Edit::Options options = Options::none);
	/// �e�A�ʒu�A�傫���A��s�̕������A�s������쐬�B�傫�����O�ɂ���ƈ�s�̕������ƍs������傫�������߂�B
	Edit(Control& parent, int x, int y, int width, int height, int lineLength, int lineCount = 1, Edit::Options options = Options::none);
	/// �n���h�����Q�Ƃ��č쐬�B�n���h���͔j�����Ȃ��B
	explicit Edit(HWND handle);
	~Edit();
	Edit& operator=(Edit&& value);


public:
	/// �ҏW������̔z�u�B�����l�� Edit::Align::left�B
	Edit::Align align() const;
	void align(Edit::Align value);
	/// ��蒼����񂪂��邩�ǂ����B
	bool canUndo() const;
	/// �L�����b�g�̓_�Ŏ��ԁi�~���b�j�B
	static int caretBlinkTime();
	/// �L�����b�g�̂��镶���C���f�b�N�X�B
	int caretIndex() const;
	void caretIndex(int value);
	/// �L�����b�g��\�����邩�ǂ����B
	bool caretVisible() const;
	void caretVisible(bool value);
	/// �L�����b�g�̑傫����A�D�F�ɂ��邩�ǂ�����ݒ肷��B�Ⴆ�Δ��p������������͂���ꍇ�Ɏl�p���L�����b�g�ɂ���ɂ͉��L�̂悤�ȃR�[�h�������B
	/// <pre><code>
	/// Graphics graphics(edit);
	/// graphics.font(edit.font());
	/// edit.changeCaret(graphics.measureText(L"0"));
	/// </code></pre>
	void changeCaret(const Size& size, bool grayed = false);
	void changeCaret(int width, int height, bool grayed = false);
	/// �L�����b�g�̉摜��ύX����B�摜�͕����ɑ΂��� XOR ���Z���s���B�L�����b�g�̑傫����ύX����Ɩ����ɂȂ�B
	void changeCaret(HBITMAP caret);
	/// ��蒼�����������B
	void clearUndo();
	/// �I�����Ă��镶������N���b�v�{�[�h�ɃR�s�[����B�����񂪑I������Ă��Ȃ��ꍇ�͉������Ȃ��B
	void copy() const;
	/// ���[�U�����߂ē��͂���܂ŕ\������K�C�h������Boptins() �� Edit::Options::multiline ��ݒ肵�Ă��Ȃ��ꍇ�̂ݗL���B���̊֐��̎g�p�ɂ� EnableVisualStyle.hpp �̃C���N���[�h���K�v�B
	String cueBanner() const;
	void cueBanner(StringRange value);
	/// �I�����Ă��镶�����؂����ăN���b�v�{�[�h�ɓ\��t����B�����񂪑I������Ă��Ȃ��ꍇ�͂Ȃɂ����Ȃ��B
	void cut();
	/// �V�X�e���f�t�H���g�̃L�����b�g�̕��B
	static int defaultCaretWidth();
	/// �R���g���[���̋��E���̎�ށB�����l�� Control::Edge::client�B
	Control::Edge edge() const;
	void edge(Control::Edge value);
	/// �ŏ��ɕ\������Ă���s�B
	int firstVisibleLine() const;
	/// �N���C�A���g���W����ł��߂������C���f�b�N�X�����߂�B�N���C�A���g�̈��ł͂Ȃ��ꍇ�� -1 ��Ԃ��B
	int getIndexAt(const Point& position) const;
	int getIndexAt(int x, int y) const;
	/// �s�̐擪�̕����C���f�b�N�X�����߂�B
	int getIndexFromLine(int line) const;
	/// �����C���f�b�N�X����s�����߂�B
	int getLineFromIndex(int index) const;
	/// �s�̕������B
	int getLineLength(int line) const;
	/// �s�̕������Ԃ��B
	String getLineText(int line) const;
	/// �����C���f�b�N�X����N���C�A���g���W�����߂�B�L�����b�g���ړ��ł��镶���͂Ȃ����ʒu���擾�ł��Ȃ��̂Œ��ӁB
	Point getPositionFromIndex(int index) const;
	/// ������ 0 ���w�肵�������̂݌��݂̏�ԂɍœK�ȑ傫�������߂�B0 �ȊO���w�肵�������͂��̂܂ܕԂ�B
	/// Edit �͑f�̂܂܂ł͍œK�ȑ傫���������ł��Ȃ��̂� preferredCharCount() �̈�s�̕������A�s������œK�ȑ傫�������߂�B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// �����X�N���[���o�[��\�����邩�ǂ����Boptins() �� Edit::Options::multiline ��ݒ肵���ꍇ�̂ݗL���B�����l�� false�B
	bool hScrollBar() const;
	void hScrollBar(bool value);
	/// IME �̕ϊ����[�h�B�����l�� Edit::ImeConvert::default�B
	Edit::ImeConvert imeConvert() const;
	void imeConvert(Edit::ImeConvert value);
	/// imeMode() �� imeConvert() �����݂̏�Ԃ��烆�[�U���ύX�ł��Ȃ����邩�ǂ����B�����l�� false�B
	bool imeFixed() const;
	void imeFixed(bool value);
	/// IME �̓���B�����l�� Edit::ImeConvert::default�B
	Edit::ImeMode imeMode() const;
	void imeMode(Edit::ImeMode value);
	/// IME �̋�����\���t���O�B�����l�� Edit::ImeStatus::none�B
	Edit::ImeStatus imeStatus() const;
	void imeStatus(Edit::ImeStatus value);
	/// �ҏW������̒����B
	int length() const;
	/// �ҏW������̍s���B
	int lineCount() const;
	/// �啶����S�ď������Ƃ��ē��͂���ǂ����B�����l�� false�B
	bool lowercaseOnly() const;
	void lowercaseOnly(bool value);
	/// ������ƃR���g���[���̊Ԃ̗]���Bmultiline() �� false �̏ꍇ�� left �� right �����w��ł��Ȃ��B�����l�� Padding(2, 0, 2, 0)�B
	/// �����s�ł͂Ȃ����㉺�̗]�����~�����ꍇ�� options() �� Edit::Options::mutiline | Edit::Options::noVScroll ��ݒ肷��Ɨǂ��B
	/// �����s�ł͂Ȃ� options() �� Edit::Options::noHScroll ��ݒ肵���ꍇ�A�]���̕����ɂ͂ݏo���������\������Ă��܂��̂ŏ�L�̂悤�ɕ����s�ɂ���Ɨǂ��B
	Padding margin() const;
	void margin(const Padding& value);
	void margin(int left, int top, int right, int bottom);
	/// ���͂ł���ő啶�����B
	int maxLength() const;
	void maxLength(int value);
	/// �����񂪕ҏW���ꂽ���ǂ����B
	bool modified() const;
	void modified(bool value);
	/// �����s���͂ł��邩�ǂ����B�R���X�g���N�^�� options ������ Edit::Options::multiline ��ݒ肵�����ǂ����B
	bool multiline() const;
	/// �����̂݋����邩�ǂ����B�������\��t������������̓`�F�b�N����Ȃ��B�����l�� false�B
	bool numberOnly() const;
	void numberOnly(bool value);
	/// �N���b�v�{�[�h�̕������\��t����C�x���g�B
	Listener<Edit::Paste&>& onPaste();
	/// �������ύX���ĕ\���ɔ��f���钼�O�̃C�x���g�B
	Listener<Edit::TextChange&>& onTextChange();
	///	�R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B
	Edit::Options options() const;
	/// �p�X���[�h���͂Ńp�X���[�h���B�������B0 �Ȃ�B���Ȃ��B�����l�� 0�B
	wchar_t passwordChar() const;
	void passwordChar(wchar_t value);
	/// �N���b�v�{�[�h�̕������\��t����B
	void paste();
	/// ���� Edit �őz�肳����s�̕������ƍs���Bwidth �͈�s�̕������Aheight �͍s����\���BgetPreferredSize �֐��� 0 ���w�肵�����A���̐��l����傫�������߂�B�����l�� Size(10, 1)�B
	Size preferredCharCount() const;
	void preferredCharCount(const Size& value);
	void preferredCharCount(int lineLength, int lineCount);
	/// �ǂݎ���p���ǂ����B�����l�� false�B
	bool readOnly() const;
	void readOnly(bool value);
	/// Scaler ���g���ăR���g���[�����X�P�[�����O����B
	virtual void scale(const Scaler& scaler);
	/// ���������� x ���������A���������� y �s���X�N���[������Bx �͎��ۂ̕������ł͂Ȃ����p�����̕��ϕ������̃X�N���[���ʁB
	void scroll(int x, int y);
	/// y�s�� x �����ڂɃX�N���[������Bx �͎��ۂ̕������ł͂Ȃ����p�����̕��ϕ������̃X�N���[���ʁB
	void scrollInto(int x, int y);
	/// ��s���ɃX�N���[������B
	void scrollLineDown();
	/// ��s��ɃX�N���[������B
	void scrollLineUp();
	/// �P�y�[�W���ɃX�N���[������B
	void scrollPageDown();
	/// �P�y�[�W��ɃX�N���[������B
	void scrollPageUp();
	/// �L�����b�g��������ʒu�ɃX�N���[������B
	void scrollToCaret();
	/// �I������Ă��镶����B�����ꍇ�͋󕶎����Ԃ��B
	String selectedText() const;
	void selectedText(StringRange value);
	/// ������̑I����ԁB
	Edit::Selection selection() const;
	void selection(const Edit::Selection& value);
	void selection(int index, int length);
	/// �N���C�A���g�̈�̑傫������R���g���[���̑傫�������߂�B
	virtual Size sizeFromClientSize(const Size& clientSize) const;
	/// tab ���B�����l�͎擾�ł��Ȃ��������炭 8�B
	void tabWidth(int value);
	/// �ҏW������B
	using Control::text;
	virtual void text(StringRange value);
	/// ������̐F�B
	Color textColor() const;
	void textColor(const Color& value);
	/// ���O�̕ҏW����蒼���B
	void undo();
	/// ��������S�đ啶���Ƃ��ē��͂��邩�ǂ����B�����l�� false�B
	bool uppercaseOnly() const;
	void uppercaseOnly(bool value);
	/// �����X�N���[���o�[��\�����邩�ǂ����Bmultiline() �� true �̏ꍇ�̂ݗL���B�����l�� false�B
	bool vScrollBar() const;
	void vScrollBar(bool value);

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	void _initialize();

	bool _owned;
	HBITMAP _caret;
	Size _caretSize;
	int _caretIndex;
	bool _caretVisible;
	ImeMode _imeMode;
	ImeMode _imeModeBackup;
	bool _imeModeChanging;
	ImeConvert _imeConvert;
	ImeConvert _imeConvertBackup;
	bool _imeFixed;
	Padding _margin;
	Size _preferredCharCount;
	bool _textChanging;
	Color _textColor;
	StringBuffer _oldText;
	Selection _oldSelection;
	Listener<Edit::Paste&> _onPaste;
	Listener<Edit::TextChange&> _onTextChange;
};



	}
}