#pragma once

#include <balor/gui/Control.hpp>


namespace balor {
	namespace gui {



/**
 * �X�N���[���o�[�R���g���[���B
 *
 * Scroll �� pageSize, minimum, maximum �̕ύX�� value ���ω������ꍇ�ɂ͔������Ȃ��B
 * minimum �� maximum ���傫�����Ă� maximum = minimum �ɂȂ邾���ő����ʂ̕����͕ς��Ȃ��Bvalue �̍ő�l�� maximum() - pageSize() + 1 �ɂȂ�B
 * onMouseUp �C�x���g�͔������Ȃ��͗l�B����Ɋ֘A���Ă� onDrag �C�x���g�̔����^�C�~���O�����������Ȃ��Ă���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"ScrollBar Sample");

	ScrollBar scroll(frame, 20, 10, 0, 0, 0, 120, 21);
	Label label(frame, scroll.bounds().right() + 10, 10, 40, 0, String() + scroll.value());
	scroll.onScroll() = [&] (ScrollBar::Scroll& e) {
		label.text(String() + e.newValue());
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class ScrollBar : public Control {
public:
	/// �R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none     = 0      ,
			vertical = 0x0001L, /// �����X�N���[���o�[�ɂ���B�����͐����X�N���[���o�[�B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


public:
	/// �X�N���[���o�[�̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<ScrollBar, Control::Event> Event;


	/// �X�N���[���ʒu���ω������C�x���g�B
	struct Scroll : public Event {
		Scroll(ScrollBar& sender, int oldValue, int newValue, bool tracking);
		/// �V�����X�N���[���ʒu�B
		int newValue() const;
		/// �Â��X�N���[���ʒu�B
		int oldValue() const;
		/// �X�N���[���{�b�N�X�i�܂݁j���g���b�L���O�����ǂ����B
		bool tracking() const;

	private:
		int _newValue;
		int _oldValue;
		bool _tracking;
	};


public:
	/// �k���n���h���ō쐬�B
	ScrollBar();
	ScrollBar(ScrollBar&& value, bool checkSlicing = true);
	/// �e�R���g���[���A�ʒu�A�傫���A�ŏ��ʒu�A�ő�ʒu�A�X�N���[���{�b�N�X�i�܂݁j�̑傫������쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	ScrollBar(Control& parent, int x, int y, int width, int height, int minimum = 0, int maximum = 120, int pageSize = 21, ScrollBar::Options options = Options::none);
	virtual ~ScrollBar();
	ScrollBar& operator=(ScrollBar&& value);

public:
	/// �����X�N���[���o�[�̊���̍����B
	static int defaultHorizontalHeight();
	/// �����X�N���[���o�[�̊���̕��B
	static int defaultVerticalWidth();
	/// ���݂̏�Ԃ���œK�ȑ傫�������߂�B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// �����X�N���[���o�[�̖��{�^���̕��B
	static int horizontalArrowWidth();
	/// ���L�[�܂��̓X�N���[���{�^�����������Ƃ��܂��̓}�E�X�z�C�[���̃X�N���[���ʁB�����l�͂P�B
	int lineSize() const;
	void lineSize(int value);
	/// �X�N���[���̍ő�ʒu�B
	int maximum() const;
	void maximum(int value);
	/// �X�N���[���̍ŏ��ʒu�B
	int minimum() const;
	void minimum(int value);
	/// value ���ω������C�x���g�̃��X�i�[�B
	Listener<Scroll&>& onScroll();
	///	�R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B
	ScrollBar::Options options() const;
	/// �X�N���[���{�b�N�X�i�܂݁j�̑傫���B
	int pageSize() const;
	void pageSize(int value);
	/// ���݂̃X�N���[���ʒu�Bminimum() ���� maximum() - pageSize() + 1 �̊Ԃŕω�����B
	int value() const;
	void value(int value);
	/// �����X�N���[���o�[�̖��{�^���̍����B
	static int verticalArrowHeight();

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	int _lineSize;
	Listener<Scroll&> _onScroll;
};



	}
}