#pragma once

#include <balor/Event.hpp>
#include <balor/Listener.hpp>
#include <balor/Reference.hpp>

struct HWND__;


namespace balor {
	namespace gui {

class Control;


/**
 * �^�C�}�[��\���B
 *
 * start() �֐��Ń^�C�}�[���J�n����Ǝw�肵�����s�Ԋu�� onRun �C�x���g�𔭐�������B
 * onRun �C�x���g�����s�����̂� executor() �������郁�b�Z�[�W���[�v�Ɠ����X���b�h�ɂȂ�B
 * executor()  �����b�Z�[�W���[�v�ŏ�������Ă��Ȃ��ƃ^�C�}�[�͓����Ȃ��B
 * Timer �ւ̑���̓X���b�h�Z�[�t�ł͂Ȃ��̂ŁA�����̃X���b�h���� Timer �𑀍삷��ꍇ�͎����Ń��b�N���s�����ƁB
 * �^�C�}�[�̐��x�� 55 �~���b���x�ŁA���b�Z�[�W�����G���Ă��鎞�ɂ͏�������Ȃ��ꍇ������B
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
class Timer : private NonCopyable {
public:
	/// �^�C�}�[�̃C�x���g�N���X�B
	typedef EventWithSender<Timer> Run;

public:
	/// ��^�C�}�[���쐬�B
	Timer();
	Timer(Timer&& value);
	/// ���s���� Control�A���s�Ԋu�AonRun �C�x���g����쐬�B
	Timer(Control& executor, int interval, Listener<Timer::Run&> onRun = Listener<Timer::Run&>());
	~Timer();
	Timer& operator=(Timer&& value);

public:
	/// �^�C�}�[�����s���� Control�B
	Control* executor() const;
	/// onRun �̎��s�Ԋu�i�~���b�j�B
	int interval() const;
	void interval(int value);
	/// interval ���Ƃɔ�������C�x���g�B
	Listener<Timer::Run&>& onRun();
	/// �^�C�}�[���J�n����B
	void start();
	/// �J�n�ς݂��ǂ����B�����l�� false�B
	bool started() const;
	/// �^�C�}�[���~����B
	void stop();

private:
	typedef ::HWND__* HWND;

	Reference<Control> _executor;
	int _interval;
	Listener<Timer::Run&> _onRun;
	bool _started;
};



	}
}