#pragma once

#include <balor/gui/Button.hpp>


namespace balor {
	namespace gui {



/**
 * ���W�I�{�^���B
 * 
 * �I�[�i�[�h���[�ɂ���ƃ`�F�b�N��ԓ��������ŊǗ����Ȃ���΂Ȃ�Ȃ��Ȃ�̂ŒP�� WM_PAINT ��������B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"GroupBox Sample");

	GroupBox group(frame, 20, 10, 0, 0, L"�w�i�F");
	Brush redBrush(Color::red());
	Brush greenBrush(Color::green());
	Brush blueBrush(Color::blue());
	RadioButton red(group, 20, 20, 0, 0, L"�Ԃ��w�i", [&] (RadioButton::Check& ) {
		frame.brush(redBrush);
		frame.invalidate(true);
	});
	RadioButton green(group, 20, 50, 0, 0, L"�΂̔w�i", [&] (RadioButton::Check& ) {
		frame.brush(greenBrush);
		frame.invalidate(true);
	});
	RadioButton blue(group, 20, 80, 0, 0, L"���w�i", [&] (RadioButton::Check& ) {
		frame.brush(blueBrush);
		frame.invalidate(true);
	});
	group.resize(); // �q�R���g���[���ɑ傫�������킹��B

	frame.runMessageLoop();
 * </code></pre>
 */
class RadioButton : public ButtonBase {
public:
	/// RadioButton �̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<RadioButton, Control::Event> Event;

	typedef Event Check;
	typedef PaintEvent<RadioButton, Event> Paint;


public:
	/// �k���n���h���ō쐬�B
	RadioButton();
	RadioButton(RadioButton&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫���A������AfirstOfGroup ����쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	RadioButton(Control& parent, int x, int y, int width, int height, StringRange text, bool firstOfGroup = false);
	/// �e�A�ʒu�A�傫���A������AonCheck �C�x���g�AfirstOfGroup ����쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	RadioButton(Control& parent, int x, int y, int width, int height, StringRange text, Listener<RadioButton::Check&> onCheck, bool firstOfGroup = false);
	virtual ~RadioButton();
	RadioButton& operator=(RadioButton&& value);

public:
	/// �`�F�b�N��Ԃ������I�ɍX�V���邩�ǂ����B�����l�� true�B
	bool autoCheck() const;
	void autoCheck(bool value);
	/// �`�F�b�N����Ă��邩�ǂ����B
	bool checked() const;
	void checked(bool value);
	/// ���݂̕������t�H���g������œK�ȑ傫�������߂�Bmultiline() �� true �̏ꍇ width ���Œ肷��ƍœK�� height �����܂�B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// �`�F�b�N��Ԃ��ω������A���邢�� autoCheck() �� false �̏ꍇ�͕ω����v�����ꂽ�C�x���g�B
	Listener<RadioButton::Check&>& onCheck();
	/// �`�悷��C�x���g�B
	Listener<RadioButton::Paint&>& onPaint();
	/// �g�O���{�^���̂悤�ȊO���������ǂ����B�����l�� false�B
	bool pushLike() const;
	void pushLike(bool value);
	/// �{�^����������̉E�ɕ\������邩�ǂ����B�����l�� false�B
	bool rightButton() const;
	void rightButton(bool value);
	/// ���W�I�{�^���O���[�v�̊J�n�R���g���[�����ǂ����B
	/// �O���[�v���̈���N���b�N����Ƃ���܂œ����O���[�v���Ń`�F�b�N����Ă������̂���`�F�b�N��Ԃ��ڂ�B
	/// ���̃��W�I�{�^���O���[�v���c��ɂ��Z��ɂ��q���ɂ������Ǘ����Ă���Ȃ�ݒ肷��K�v�͖����B
	/// �����ł͂Ȃ��ꍇ�̓O���[�v���ōŏ��ɒǉ������izOrder() ���ł������j���W�I�{�^�����J�n�R���g���[���ɐݒ肷��B
	bool firstOfGroup() const;
	void firstOfGroup(bool value);

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	bool _checkedChanging;
	Listener<RadioButton::Check&> _onCheck;
	Listener<RadioButton::Paint&> _onPaint;
};



	}
}