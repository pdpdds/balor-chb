#pragma once

#include <balor/gui/Control.hpp>


namespace balor {
	namespace gui {



/**
 * �X�N���[���@�\���������R���g���[���̊��N���X�B
 * 
 * Bitmap �N���X��\������E�C���h�E�� Bitmap ���X�N���[�����ĕ\���ł���悤�ɂ���ɂ͎��̂悤�ɐݒ肷��B�B
 * <pre><code>
 *	panel.scrollMinSize(bitmap.size());
 * </code></pre>
 * �q�R���g���[�����S�ĕ\���ł���悤�ɃX�N���[���͈͂�ݒ肷��ɂ͎��̂悤�ɐݒ肷��B
 * <pre><code>
 *	frame.scrollMinSize(frame.clientSizeFromSize(frame.preferredSize()));
 * </code></pre>
 */
class ScrollableControl : public Control {
public:
	/// ScrollableControl �̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<ScrollableControl, Control::Event> Event;


	/// �X�N���[���ʒu���ω������C�x���g�B
	struct Scroll : public ScrollableControl::Event {
		Scroll(ScrollableControl& sender, const Point& oldPosition, const Point& newPosition);

		/// �V�����X�N���[���ʒu�B
		const Point& newPosition() const;
		/// �Â��X�N���[���ʒu�B
		const Point& oldPosition() const;

	private:
		Point _oldPosition;
		Point _newPosition;
	};


protected: // �R���g���[���̐����Ɣj��
	ScrollableControl();
	ScrollableControl(ScrollableControl&& value);
	virtual ~ScrollableControl() = 0;

public:
	/// �N���C�A���g�̈�̑傫���B
	using Control::clientSize;
	virtual void clientSize(const Size& value);
	/// �X�N���[���ʒu��X�N���[���͈͂��l���������z�I�ȃR���g���[���̃N���C�A���g���W�Ƒ傫���B
	virtual Rectangle displayRectangle() const;
	/// �����X�N���[���o�[���\������Ă��邩�ǂ����B
	bool hScrollBar() const;
	/// �����X�N���[���o�[����ɕ\�����邩�ǂ����B�����l�� false�B���I�ɕύX����Ƌ��������������Ȃ邱�Ƃ�����̂ōŏ��Ɉ�x�����ݒ肷�邱�ƁB
	bool hScrollBarFixed() const;
	void hScrollBarFixed(bool value);
	/// �X�N���[���ʒu���ω������C�x���g�B
	Listener<ScrollableControl::Scroll&>& onScroll();
	/// Scaler ���g���ăR���g���[�����X�P�[�����O����B
	virtual void scale(const Scaler& scaler);
	/// control ���\�������悤�ɃX�N���[������Brecursive �� true �Ȃ�X�N���[���\�ȃR���g���[��������q�ɂȂ��Ă���ꍇ�ɂ��ׂĂ̊K�w�ŃX�N���[������B
	void scrollControlIntoView(Control& control, bool recursive = false);
	/// �R���g���[���̑傫��������ȉ��Ȃ�X�N���[���o�[��\������傫���B0 �Ȃ�΃X�N���[���o�[�͕\������Ȃ��B�����l�� Size(0, 0)�B
	Size scrollMinSize() const;
	void scrollMinSize(const Size& value);
	void scrollMinSize(int width, int height);
	/// �X�N���[���ʒu�B�X�N���[�����Ă���Ε����ɂȂ�B
	Point scrollPosition() const;
	void scrollPosition(const Point& value);
	void scrollPosition(int x, int y);
	/// ���݂̃X�N���[���͈͂̑傫���B
	Size scrollSize() const;
	/// �����X�N���[���o�[���\������Ă��邩�ǂ����B
	bool vScrollBar() const;
	/// �����X�N���[���o�[����ɕ\�����邩�ǂ����B�����l�� false�B���I�ɕύX����Ƌ��������������Ȃ邱�Ƃ�����̂ōŏ��Ɉ�x�����ݒ肷�邱�ƁB
	bool vScrollBarFixed() const;
	void vScrollBarFixed(bool value);

protected:
	/// �X�N���[���o�[�̏�Ԃ��X�V����B
	virtual void updateScrollBars();
	virtual void processMessage(Message& msg);

protected:
	Size _scrollMinSize;
	Size _scrollSize;
	bool _hScrollBarFixed;
	bool _vScrollBarFixed;
	bool _updating;
	Listener<ScrollableControl::Scroll&> _onScroll;
};



	}
}