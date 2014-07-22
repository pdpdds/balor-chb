#pragma once

#include <balor/gui/ScrollableControl.hpp>


namespace balor {
	namespace gui {



/**
 * �R���g���[�����悹�ăO���[�v������e�R���g���[���B
 *
 * fromParentHandle() �֐����g���� Control �̔h���N���X�ł͂Ȃ��C�ӂ̃E�C���h�E�n���h���̎q�ɂȂ邱�Ƃ��ł���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Panel Sample");

	Label label(frame, 20, 10, 0, 0, L"�{�^���� Panel �ɏ悹�ď�ɃE�C���h�E�̉E���ɕ\������");
	Panel bottom(frame, 0, 0, 0, 50);
	Panel right(bottom, 0, 0, 60, 50);
	Button ok(right, 20, 10, 0, 0, L"OK");

	DockLayout layout(frame);
	layout.setStyle(bottom, DockLayout::Style::bottom);
	DockLayout subLayout(bottom);
	subLayout.setStyle(right, DockLayout::Style::right);
	layout.perform();
	subLayout.perform();
	frame.onResized() = [&] (Frame::Resized& ) {
		layout.perform();
		subLayout.perform();
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class Panel : public ScrollableControl {
public:
	/// �R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none        = 0      ,
			transparent = 0x0020L, /// �����Őe�R���g���[���������Č�����悤�ɂ���B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


	/// Panel �̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<Panel, ScrollableControl::Event> Event;

	typedef PaintEvent<Panel, Event> Paint;


public:
	/// �k���n���h���ō쐬�B
	Panel();
	Panel(Panel&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫������쐬�B���̑��̈����ɂ��Ă͓����̊֐����Q�ƁB
	Panel(Control& parent, int x, int y, int width, int height, Control::Edge edge = Control::Edge::none, Panel::Options options = Options::none);
	virtual ~Panel();
	Panel& operator=(Panel&& value);

public:
	/// �R���g���[���̋��E���̎�ށB
	Control::Edge edge() const;
	void edge(Control::Edge value);
	/// �t�H�[�J�X�𓾂��邩�ǂ����B
	virtual bool focusable() const;
	/// �e�E�C���h�E�n���h���A�ʒu�A�傫������R���g���[�����쐬�B���̑��̈����ɂ��Ă͓����̊֐����Q�ƁB
	/// Control �N���X�̔h���N���X�ł͂Ȃ��C�ӂ̃E�C���h�E�n���h���̎q�ɂȂ邱�Ƃ��ł���B
	static Panel fromParentHandle(HWND parent, int x, int y, int width, int height, Control::Edge edge = Control::Edge::none, Panel::Options options = Options::none);
	/// �N���C�A���g�̈��`�悷��C�x���g�B
	Listener<Panel::Paint&>& onPaint();
	///	�R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B
	Panel::Options options() const;

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	Listener<Panel::Paint&> _onPaint;
};



	}
}