#pragma once

#include <balor/gui/Button.hpp>


namespace balor {
	namespace gui {



/**
 * �`�F�b�N�{�b�N�X�B
 *
 * �I�[�i�[�h���[�ɂ���ƃ`�F�b�N��ԓ��������ŊǗ����Ȃ���΂Ȃ�Ȃ��Ȃ�̂ŒP�� WM_PAINT ��������B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"CheckBox Sample");

	auto onStateChange = [&] (CheckBox::StateChange& ) {
		frame.invalidate();
	};
	CheckBox check0(frame, 20, 10, 0, 0, L"�F�𔒂ɕς���", onStateChange);
	CheckBox check1(frame, 20, 40, 0, 0, L"�`���l�p�ɕς���", onStateChange);

	frame.onPaint() = [&] (Frame::Paint& e) {
		auto g = e.graphics();
		g.brush(Color::control());
		g.clear();
		g.brush(check0.checked() ? Color::white() : Color::yellow());
		if (check1.checked()) {
			g.drawRectangle(10, 80, 200, 200);
		} else {
			g.drawEllipse(10, 80, 200, 200);
		}
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class CheckBox : public ButtonBase {
public:
	/// �`�F�b�N��ԁB
	struct State {
		enum _enum {
			unchecked     = 0x0000, /// �`�F�b�N����Ă��Ȃ��B
			checked       = 0x0001, /// �`�F�b�N����Ă���B
			indeterminate = 0x0002, /// �s�m���ԁB
		};
		BALOR_NAMED_ENUM_MEMBERS(State);
	};


	/// CheckBox �̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<CheckBox, Control::Event> Event;

	typedef Event StateChange;
	typedef PaintEvent<CheckBox, Event> Paint;


public:
	/// �k���n���h���ō쐬�B
	CheckBox();
	CheckBox(CheckBox&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫���A�����񂩂�쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	CheckBox(Control& parent, int x, int y, int width, int height, StringRange text, Listener<CheckBox::StateChange&> onStateChange = Listener<CheckBox::StateChange&>());
	virtual ~CheckBox();
	CheckBox& operator=(CheckBox&& value);

public:
	/// �`�F�b�N��Ԃ������I�ɍX�V���邩�ǂ����B�����l�� true�B
	bool autoCheck() const;
	void autoCheck(bool value);
	/// �`�F�b�N����Ă��邩�ǂ����B
	bool checked() const;
	void checked(bool value);
	/// ���݂̕������t�H���g������œK�ȑ傫�������߂�Bmultiline() �� true �̏ꍇ width ���Œ肷��ƍœK�� height �����܂�BTODO:������ɉ��s���܂܂��ꍇ�Ƀt�H���g��ύX����Ɛ��m�ɋ��߂��Ȃ��͗l�B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// �`�悷��C�x���g�B
	Listener<CheckBox::Paint&>& onPaint();
	/// �`�F�b�N��Ԃ��ω������A���邢�� autoCheck() �� false �̏ꍇ�͕ω����v�����ꂽ�C�x���g�B
	Listener<CheckBox::StateChange&>& onStateChange();
	/// �g�O���{�^���̂悤�ȊO���������ǂ����B�����l�� false�B
	bool pushLike() const;
	void pushLike(bool value);
	/// �{�^����������̉E�ɕ\������邩�ǂ����B�����l�� false�B
	bool rightButton() const;
	void rightButton(bool value);
	/// �`�F�b�N��ԁB
	CheckBox::State state() const;
	void state(CheckBox::State value);
	/// �R�̃`�F�b�N��Ԃ������ǂ����Bfalse �̏ꍇ�͂Q�̃`�F�b�N��Ԃ����B�����l�� false�B
	bool threeState() const;
	void threeState(bool value);

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	bool _stateChanging;
	Listener<CheckBox::Paint&> _onPaint;
	Listener<CheckBox::StateChange&> _onStateChange;
};



	}
}