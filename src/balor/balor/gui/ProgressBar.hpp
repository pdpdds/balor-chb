#pragma once

#include <balor/gui/Control.hpp>


namespace balor {
	namespace gui {



/**
 * �v���O���X�o�[�B
 * 
 * �r�W���A���X�^�C�����L���ł���ꍇ�A�E�C���h�E�X�^�C���� PBS_SMOOTH �t���O�̎w��̗L���ɂ�����炸 XP �ł͐i���o�[�ɖڐ��肪�\������AVista �ł͖ڐ��肪�\������Ȃ��B
 * minimum �� maximum ���傫�����Ă� maximum = minimum �ɂȂ邾���ő����ʂ̕����͕ς��Ȃ��B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"ProgressBar Sample");

	ProgressBar bar(frame, 20, 10, 0, 0);
	Timer timer(frame, 500);
	Button button(frame, 20, 50, 0, 0, L"�������J�n����", [&] (Button::Click& e) {
		if (!timer.started()) {
			bar.value(0);
			timer.start();
			e.sender().text(L"�����𒆎~����");
			frame.onCursorChange() = [&] (Frame::CursorChange& e) {
				e.cursor(Cursor::wait());
			};
		} else {
			timer.stop();
			e.sender().text(L"�������J�n����");
			frame.onCursorChange().pop();
		}
		for (auto i = frame.descendantsBegin(); i; ++i) {
			i->onCursorChange() = frame.onCursorChange();
		}
	});
	timer.onRun() = [&] (Timer::Run& e) {
		bar.add(10);
		if (bar.maximum() <= bar.value()) {
			button.performClick();
			MsgBox::show(L"����");
		}
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class ProgressBar : public Control {
public:
	/// �k���n���h���ō쐬�B
	ProgressBar();
	ProgressBar(ProgressBar&& value, bool checkSlicing = true);
	/// �e�R���g���[���A�ʒu�A�傫���A�J�n�l�A�����l�ō쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	ProgressBar(Control& parent, int x, int y, int width, int height, int minimum = 0, int maximum = 100);
	virtual ~ProgressBar();
	ProgressBar& operator=(ProgressBar&& value);

public:
	/// ���݂̐i���l�ɉ��Z����B
	void add(int delta);
	/// �t�H�[�J�X�𓾂��邩�ǂ����B
	virtual bool focusable() const;
	/// ���݂̏�Ԃ���œK�ȑ傫�������߂�B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// �i�������I��邩�킩��Ȃ��\�����[�h�i�}�[�L�[�X�^�C���j�B�A�j���[�V�����X�s�[�h�̓~���b�P�ʁB�����l�� false�B
	/// ���̊֐��̎g�p�ɂ� EnableVisualStyle.hpp �̃C���N���[�h���K�v�B
	bool indeterminate() const;
	void indeterminate(bool value, int animationSpeed = 100);
	/// �i���̊����l�B
	int maximum() const;
	void maximum(int value);
	/// �i���̊J�n�l�B
	int minimum() const;
	void minimum(int value);
	/// ���݂̐i���l�B
	int value() const;
	void value(int value);
	/// �c�\�����ǂ����B
	bool vertical() const;
	void vertical(bool value);
};



	}
}