#pragma once

#include <balor/gui/Control.hpp>
#include <balor/gui/Padding.hpp>


namespace balor {
	namespace gui {



/**
 * �R���g���[���𕪊����ăh���b�O�Őڂ���R���g���[���̑傫����ς��邱�Ƃ��ł���R���g���[���B
 *
 * �c���ō��Əc�����ɕ������A�����ō��Ɖ������ɕ�������B
 * �c���Ȃ�΍��E�A�����Ȃ�Ώ㉺�ɐڂ���R���g���[���̑傫�����h���b�O�ŕς��鎖���ł���B
 * margin() �ł��ꂼ��̕����ɐڂ���R���g���[���̍ŏ��̑傫�����w��ł���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Splitter sample", 1000, 800);

	Button left(frame, 0, 0, 100, 800, L"left");
	Splitter vertical(frame, 100, 0, 10, 800);
	Button bottom(frame, 110, 410, 890, 390, L"bottom");
	Splitter horizontal(frame, 110, 400, 890, 10);
	Button center(frame, 110, 0, 890, 400, L"center");

	vertical.margin(Padding(100));
	horizontal.margin(Padding(40));

	DockLayout dockLayout(frame);
	dockLayout.setStyle(left, DockLayout::Style::left);
	dockLayout.setStyle(vertical, DockLayout::Style::left);
	dockLayout.setStyle(bottom, DockLayout::Style::bottom);
	dockLayout.setStyle(horizontal, DockLayout::Style::bottom);
	dockLayout.setStyle(center, DockLayout::Style::fill);
	frame.onResized() = [&] (Frame::Resized& ) {
		dockLayout.perform();
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class Splitter : public Control {
public:
	/// Splitter �̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<Splitter, Control::Event> Event;

	typedef PaintEvent<Splitter, Event> Paint;


public:
	/// �k���n���h���ō쐬�B
	Splitter();
	Splitter(Splitter&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫������쐬�B���̑��̈����ɂ��Ă͓����̊֐����Q�ƁB
	Splitter(Control& parent, int x, int y, int width, int height, Control::Edge edge = Control::Edge::none);
	virtual ~Splitter();
	Splitter& operator=(Splitter&& value);

public:
	/// �e�̃N���C�A���g���W�n�ł̈ʒu�Ƒ傫���B
	using Control::bounds;
	virtual void bounds(const Rectangle& value);
	/// �R���g���[���̋��E���̎�ށB
	Control::Edge edge() const;
	void edge(Control::Edge value);
	/// �t�H�[�J�X�𓾂��邩�ǂ����B
	virtual bool focusable() const;
	/// ���ꂼ��̕����ɐڂ��Ă���R���g���[���̑傫���̍ŏ��l�B�����l�� Padding(0)�B
	Padding margin() const;
	void margin(const Padding& value);
	/// �N���C�A���g�̈��`�悷��C�x���g�B
	Listener<Splitter::Paint&>& onPaint();
	/// �e�R���g���[���̃N���C�A���g���W�n�ɂ����邱�̃R���g���[���̈ʒu�B
	using Control::position;
	virtual void position(const Point& value);
	/// �c�����ɕ������邩�ǂ����BSplitter �� size() ���c���Ȃ�� true�B
	bool vertical() const;
	/// �\���D��x�B�������قǎ�O�ɕ\�������B0 ���w�肷��ƍőO�ʂɁA-1 ���w�肷��ƍŌ�ʂɈړ�����B
	using Control::zOrder;
	virtual void zOrder(int value);

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	bool _movable;
	bool _zOrderable;
	Padding _margin;
	Listener<Splitter::Paint&> _onPaint;
};



	}
}