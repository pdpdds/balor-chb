#pragma once

#include <balor/graphics/Color.hpp>
#include <balor/graphics/Graphics.hpp>
#include <balor/gui/Control.hpp>

namespace balor {
	namespace graphics {
		class Icon;
	}
}


namespace balor {
	namespace gui {



/**
 * �c�[���`�b�v�R���g���[���B
 *
 * set �֐��ŃR���g���[���Ƀc�[���`�b�v��ݒ肷��B
 * TTM_SETMARGIN �� Vista �Ńr�W���A���X�^�C�����g�p����Ɠ��삵�Ȃ��̂ŃT�|�[�g���Ȃ��B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"ToolTip Sample");

	Button button(frame, 20, 10, 0, 0, L"�{�^��");
	ToolTip toolTip(frame);
	toolTip.set(button, L"�{�^���̃c�[���`�b�v");
	toolTip.textColor(Color::blue());

	frame.runMessageLoop();
 * </code></pre>
 */
class ToolTip : protected Control {
public:
	typedef ::balor::graphics::Graphics Graphics;
	typedef ::balor::graphics::Icon Icon;


	/// �c�[���`�b�v�̕\���I�v�V�����B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none        = 0     , 
			center      = 0x0002, /// �R���g���[���̉������ɕ\������B
			track       = 0x0020, /// track �֐��ŕ\������B�����I�ɂ͕\������Ȃ��B
			absolute    = 0x0080, /// ��ʂ���͂ݏo�Ȃ��悤�Ɉʒu�𒲐������肵�Ȃ��Bshow �֐��ŕ\���������̂ݗL���B
			transparent = 0x0100, /// �c�[���`�b�v��ɃJ�[�\�����ړ����Ă��c�[���`�b�v�������Ȃ��B
			parseLinks  = 0x1000, /// �c�[���`�b�v������̃����N�^�O�i<a />�j�������N�Ƃ��ĕ\������B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


	/// �c�[���`�b�v�Ŕ�������C�x���g�B
	struct Event : public EventWithSender<ToolTip> {
		Event(ToolTip& sender, Control& owner, int id);

		/// �\���̈�����ʂ���ID�B�\���̈��ݒ肵�Ă��Ȃ��ꍇ�� 0 �ɂȂ�B
		int id() const;
		/// �c�[���`�b�v��\������I�[�i�[�R���g���[���B
		Control& owner();

	private:
		Control& _owner;
		int _id;
	};

	typedef Event LinkClick;
	typedef Event Pop;


	/// �c�[���`�b�v��\������O�ɕ������ݒ肷��C�x���g�B��������w�肹���Ƀc�[���`�b�v��ݒ肵���ꍇ�̂ݔ�������B
	struct GetText : public ToolTip::Event {
		GetText(ToolTip& sender, Control& owner, int id);

		/// �\�����镶����B�����l�͋󕶎���B
		String& text();
		void text(StringRange value);

	private:
		String _text;
	};


	/// �c�[���`�b�v��\�����钼�O�̃C�x���g�B
	struct Popup : public ToolTip::Event {
		Popup(ToolTip& sender, Control& owner, int id);

		/// �\������ʒu�B
		Point position() const;
		void position(const Point& value);
		void position(int x, int y);

	private:
		friend ToolTip;

		bool _positionChanged;
	};


public:
	/// �k���n���h���ō쐬�B
	ToolTip();
	ToolTip(ToolTip&& value, bool checkSlicing = true);
	/// �e�R���g���[������쐬�B�c�[���`�b�v��\������R���g���[���̑����� Frame �����w�肷��B
	explicit ToolTip(Control& parent);
	/// �n���h�����Q�Ƃ��č쐬�B�n���h���͔j�����Ȃ��B
	explicit ToolTip(HWND handle);
	~ToolTip();
	ToolTip& operator=(ToolTip&& value);

public:
	/// �c�[���`�b�v��L���܂��͖����ɂ���B�����l�� true�B
	void activate(bool value);
	/// �E�C���h�E����A�N�e�B�u�ł��c�[���`�b�v��\�����邩�ǂ����B�����l�� true�B
	bool alwaysPopup() const;
	void alwaysPopup(bool value);
	/// �c�[���`�b�v��\�����鎞�ɃX���C�h�A�j���[�V�������邩�ǂ����B�����l�� true�B�iTODO:���ʂ������悤���j
	bool animate() const;
	void animate(bool value);
	/// �����o���̌`�������c�[���`�b�v���ǂ����B�����l�� false�B
	bool balloon() const;
	void balloon(bool value);
	/// ������̈ʒu�Ƒ傫������c�[���`�b�v�̈ʒu�Ƒ傫�������߂�B
	Rectangle boundsFromTextBounds(const Rectangle& textBounds) const;
	Rectangle boundsFromTextBounds(int x, int y, int width, int height) const;
	/// set �֐��Őݒ肵���S�Ẵc�[���`�b�v���폜����B
	void clear();
	/// ����{�^����\�����邩�ǂ����Bbaloon() �� true �Ń^�C�g����ݒ肵���ꍇ�̂ݕ\�������B
	bool closeButton() const;
	void closeButton(bool value);
	/// �c�[���`�b�v�����ꂽ�������Ƃ��Ƀt�F�[�h�C���A�E�g���邩�ۂ��B�����l�� true�B
	bool fade() const;
	void fade(bool value);
	/// �t�H���g�BToolTip �̏����t�H���g�� Vista �ł́u���C���I�v�� height = 12�B
	using Control::font;
	/// �R���g���[���ɐݒ肳�ꂽ�c�[���`�b�v���擾����B�ݒ肳��Ă��Ȃ��ꍇ�͋󕶎��񂪕Ԃ�B������Ɋ܂܂�� & ����ꏈ��������̕����񂪕Ԃ�B
	/// �^�u�R�[�h���܂܂��Ƃ���ȍ~���Ԃ�Ȃ��͗l�B
	String get(Control& control, int id = -1) const;
	/// �c�[���`�b�v���\�������܂ł̎��ԁi�~���b�j�B�����l�� 500�B
	int initialDelay() const;
	void initialDelay(int value);
	/// �c�[���`�b�v�̍ő啶���񕝁B���̕��𒴂���ꍇ�͉��s����B�������Ȃ��ꍇ�� -1�B�������^�C�g��������ȉ��̕��ł͕\������Ȃ��B
	int maxTextWidth() const;
	void maxTextWidth(int value);
	/// �\�����镶����� & �̓��ꏈ���𖳌��ɂ��邩�ۂ��B�����l�� false�B
	bool noPrefix() const;
	void noPrefix(bool value);
	/// �\������O�ɕ������ݒ肷��C�x���g�B��������w�肹���Ƀc�[���`�b�v��ݒ肵���ꍇ�̂ݔ�������B
	Listener<ToolTip::GetText&>& onGetText();
	/// �c�[���`�b�v��̃����N���N���b�N�����C�x���g�B���̊֐��̎g�p�ɂ� EnableVisualStyle.hpp �̃C���N���[�h���K�v�B
	Listener<ToolTip::LinkClick&>& onLinkClick();
	/// �c�[���`�b�v�������鎞�̃C�x���g�B
	Listener<ToolTip::Pop&>& onPop();
	/// �c�[���`�b�v��\�����钼�O�̃C�x���g�B�ʒu��ύX�ł���B
	Listener<ToolTip::Popup&>& onPopup();
	/// ���݂̃c�[���`�b�v�̕\���������B
	void pop();
	/// ���݂̃}�E�X�ʒu�Ńc�[���`�b�v������Ε\������B���̊֐��̎g�p�ɂ� EnableVisualStyle.hpp �̃C���N���[�h���K�v�B
	void popup();
	/// �c�[���`�b�v���\������Ă��������܂ł̎��ԁi�~���b�j�B�����l�� 5000�B
	int popDelay() const;
	void popDelay(int value);
	/// �R���g���[������c�[���`�b�v���폜����B
	void reset(Control& control, int id = -1);
	/// �S�Ẵf�B���C�iinitialDelay�ApopDelay�AreshowDelay�j�������l�ɖ߂��B
	void resetDelay();
	/// �R���g���[���̊O�ɃJ�[�\�����ړ����Ă��\���������鎞�ԁi�~���b�j�B�����l�� 100�B
	/// �����������c�[���`�b�v�R���g���[����ݒ肵�Ă���R���g���[���ɃJ�[�\�����ړ�������Ƒ����ɏ�����B
	/// �����h���ɂ͈Ⴄ�c�[���`�b�v�R���g���[��������Đݒ肷�邵���Ȃ��B 
	int reshowDelay() const;
	void reshowDelay(int value);
	/// �R���g���[���Ƀc�[���`�b�v��\������悤�ɐݒ肷��B������� onGetText �C�x���g�Őݒ肷��K�v������Breset �֐��Ŗ����ɂł���B
	void set(Control& control, ToolTip::Options options = Options::transparent);
	/// �R���g���[���Ƀc�[���`�b�v��\������悤�ɐݒ肷��Breset �֐��Ŗ����ɂł���B
	void set(Control& control, StringRange toolTip, ToolTip::Options options = Options::transparent);
	/// �R���g���[���̃N���C�A���g���W�̈�Ƀc�[���`�b�v��\������悤�ɐݒ肷��Bid �͗̈�����ʂ���ԍ��B������� onGetText �C�x���g�Őݒ肷��K�v������Breset �֐��Ŗ����ɂł���B
	void set(Control& control, int id, const Rectangle& bounds, ToolTip::Options options = Options::transparent);
	void set(Control& control, int id, int x, int y, int width, int height, ToolTip::Options options = Options::transparent);
	/// �R���g���[���̃N���C�A���g���W�̈�Ƀc�[���`�b�v��\������悤�ɐݒ肷��Bid �͗̈�����ʂ���ԍ��Breset �֐��Ŗ����ɂł���B
	void set(Control& control, int id, const Rectangle& bounds, StringRange toolTip, ToolTip::Options options = Options::transparent);
	void set(Control& control, int id, int x, int y, int width, int height, StringRange toolTip, ToolTip::Options options = Options::transparent);
	/// �w�肵�� initialDelay ���� popDelay �� reshowDelay ���v�Z���đS�Đݒ肷��B
	void setDelay(int initialDelay);
	/// ������̐F�B�^�C�g���������ݒ肵���ꍇ�͖����B�����N�̕������Œ�F�B
	Color textColor() const;
	void textColor(const Color& value);
	/// ������̕\���t�H�[�}�b�g�B�c�[���`�b�v�R���g���[�����p�ӂ���t�H�[�}�b�g�ɒǉ�����t���O��ݒ肷��B�����l�� Graphics::TextFormat::none�B
	/// maxTextWidth() �� -1 �ȊO�ɐݒ肷�邱�Ƃ� Graphics::TextFormat::wordBreak �y�� Graphics::TextFormat::expandTabs �������I�ɒǉ������B
	Graphics::TextFormat textFormat() const;
	void textFormat(Graphics::TextFormat value);
	/// �^�C�g��������B�󕶎�����w�肷��Ə�����B�A�C�R���̂ݕ\���͂ł��Ȃ��B�^�C�g��������̎擾�� EnableVisualStyle.hpp �̃C���N���[�h���K�v�B
	String title() const;
	void title(StringRange value, HICON icon = nullptr);
	/// �w�肵���X�N���[�����W�Ƀc�[���`�b�v��\������Bset �֐��� options �� ToolTip::Options::track ���܂߂�K�v������Bpop �֐����ĂԂ܂ŕ\�����ꑱ����B
	void track(Control& control, const Point& position);
	void track(Control& control, int x, int y);
	void track(Control& control, int id, const Point& position);
	void track(Control& control, int id, int x, int y);
	/// track �֐��ŕ\�������c�[���`�b�v�̃X�N���[�����W�ʒu���X�V����B
	void trackPosition(const Point& value);
	void trackPosition(int x, int y);
	/// �ĕ`�悷��B
	void update();
	/// ���ݕ\������Ă��邩�ǂ����B
	bool visible() const;

public:
	/// HWND �ւ̎����ϊ� & null �`�F�b�N�p�B
	using Control::operator HWND;

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	bool _owned;
	/// onGetText �C�x���g�Őݒ肵�Ă���\������܂ł̈ꎞ�ۑ��ꏊ�B
	String _temporaryText;
	Color _textColor;
	Graphics::TextFormat _textFormat;
	Listener<ToolTip::GetText&> _onGetText;
	Listener<ToolTip::LinkClick&> _onLinkClick;
	Listener<ToolTip::Pop&> _onPop;
	Listener<ToolTip::Popup&> _onPopup;
};



	}
}