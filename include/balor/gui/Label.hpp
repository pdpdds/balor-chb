#pragma once

#include <balor/graphics/Color.hpp>
#include <balor/gui/Control.hpp>

namespace balor {
	namespace graphics {
		class Bitmap;
		class Icon;
	}
}


namespace balor {
	namespace gui {



/**
 * �X�^�e�B�b�N�R���g���[���B�R���g���[����ɕ������A�C�R���A�r�b�g�}�b�v��\������B
 * 
 * ���O�� Static �ɂ���ƕϐ����ɍ���̂� Label �ɕύX�����B�`��C�x���g�͖������A�I�[�i�[�h���[���邮�炢�Ȃ� Panel �N���X�� onPaint �C�x���g�����������ق����ǂ��B
 * ������A�r�b�g�}�b�v�A�A�C�R���̂R��ʂ̂ǂꂩ��\�����A�r�������ʂ�ύX���邱�Ƃ͂ł��Ȃ��B
 * �r�b�g�}�b�v��\���� DockLayout �Ŋg�k������̂͂��������������̂ł�߂��ق����悢�BPanel �� onPaint �C�x���g���������ׂ��B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Label Sample");

	Label textLabel(frame, 20, 10, 0, 0, L"�����񃉃x��:");
	Label iconLabel(frame, 20, 50, 0, 0, Icon::asterisk());

	frame.runMessageLoop();
 * </code></pre>
 */
class Label : public Control {
public:
	typedef ::balor::graphics::Bitmap Bitmap;
	typedef ::balor::graphics::Icon Icon;


	/// ������̔z�u�B
	struct TextAlign {
		enum _enum {
			left   = 0x00000000, /// �������B
			center = 0x00000001, /// ���������B
			right  = 0x00000002, /// �E�����B
		};
		BALOR_NAMED_ENUM_MEMBERS(TextAlign);
	};


	/// Label �̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<Label, Control::Event> Event;


public:
	/// �k���n���h���ō쐬�B
	Label();
	Label(Label&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫���A�����񂩂�쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	Label(Control& parent, int x, int y, int width, int height, StringRange text);
	/// �e�A�ʒu�A�傫���A�r�b�g�}�b�v����쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	Label(Control& parent, int x, int y, int width, int height, HBITMAP bitmap);
	/// �e�A�ʒu�A�傫���A�A�C�R������쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	Label(Control& parent, int x, int y, int width, int height, HICON icon);
	virtual ~Label();
	Label& operator=(Label&& value);

public:
	/// �\������r�b�g�}�b�v�B�����ꍇ�̓k���n���h���̃r�b�g�}�b�v���Ԃ�B
	Bitmap bitmap() const;
	void bitmap(HBITMAP value);
	/// �r�b�g�}�b�v��A�C�R�����g�k�����Ɍ����Œ����ɕ`�悷��B�����l�� false�B
	bool centerImage() const;
	void centerImage(bool value);
	/// �R���g���[���̋��E���̎�ށB�����l�� Control::Edge::none�B
	Control::Edge edge() const;
	void edge(Control::Edge value);
	/// �����s�G�f�B�b�g�R���g���[���̂悤�ɕ������\������B�Ⴆ�ΒP���؂����s�R�[�h���Ȃ��Ƃ��͂ݏo��Ή��s����B�����l�� true�B
	bool editLike() const;
	void editLike(bool value);
	/// �����񂪈�s�Ɏ��܂�Ȃ��ꍇ�ɕ����ɏȗ������u...�v��\�����邩�ǂ����Btrue �̏ꍇ���s���Ȃ��Ȃ�B�����l�� false�B
	bool endEllipsis() const;
	void endEllipsis(bool value);
	/// �t�H�[�J�X�𓾂��邩�ǂ����B
	virtual bool focusable() const;
	/// ���݂̕������t�H���g�A�摜������œK�ȑ傫�������߂�Bwidth ���Œ肷��ƍœK�� height �����܂�B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// �\������A�C�R���B�����ꍇ�̓k���n���h���̃A�C�R�����Ԃ�B
	Icon icon() const;
	void icon(HICON value);
	/// '&' ����ꕶ���Ƃ��ď������Ȃ����ǂ����B�����l�� false�B
	bool noPrefix() const;
	void noPrefix(bool value);
	/// �p�X�����񂪈�s�Ɏ��܂�Ȃ��ꍇ�Ƀt�@�C�����͕\�����r���ŏȗ������u...�v��\�����邩�ǂ����Btrue �̏ꍇ���s���Ȃ��Ȃ�B�����l�� false�B
	bool pathEllipsis() const;
	void pathEllipsis(bool value);
	/// ������̔z�u�B�����l�� Label::TextAlign::left�B
	Label::TextAlign textAlign() const;
	void textAlign(Label::TextAlign value);
	/// ������̐F�B
	Color textColor() const;
	void textColor(const Color& value);

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	Color _textColor;
};



	}
}