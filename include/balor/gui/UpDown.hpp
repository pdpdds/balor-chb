#pragma once

#include <balor/gui/Control.hpp>


namespace balor {
	namespace gui {

class Edit;



/**
 * �A�b�v�_�E���R���g���[���B
 * 
 * ���_�R���g���[���̈ʒu��傫�����ω������ꍇ�A�����I�ɒǏ]�͂��Ȃ��̂ōēx buddy �֐��Őݒ肵�Ă��΂悢�B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"UpDown Sample");

	int number = 0;
	Edit edit(frame, 20, 10, 0, 25, 10);
	edit.text(String() + number);
	UpDown upDown(frame, edit);
	upDown.onUp() = [&] (UpDown::Up& ) {
		++number;
		edit.text(String() + number);
	};
	upDown.onDown() = [&] (UpDown::Down& ) {
		--number;
		edit.text(String() + number);
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class UpDown : public Control {
public:
	/// �R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none        = 0     , 
			noArrowKeys = 0x0020, /// buddy() ������L�[��}�E�X�z�C�[���̓��͂��󂯎��Ȃ��悤�ɂ���B
			horizontal  = 0x0040, /// ���E�{�^���̃A�b�v�_�E���R���g���[���ɂ���B
			leftAlign   = 0x0008, /// buddy() �̍��ɋz������B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


	/// �A�b�v�_�E���R���g���[���̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<UpDown, Control::Event> Event;

	typedef Event Down;
	typedef Event Up;


public:
	/// �k���n���h���ō쐬�B
	UpDown();
	UpDown(UpDown&& value, bool checkSlicing = true);
	/// �e�R���g���[���A�ʒu�A�傫���A�ŏ��ʒu�A�ő�ʒu����쐬�B���̑��̈����ɂ��Ă͓����̊֐����Q�ƁB
	UpDown(Control& parent, int x, int y, int width, int height, UpDown::Options options = Options::none);
	/// �e�R���g���[���A���_�R���g���[������쐬�B���_�R���g���[���ɋz������B���̑��̈����ɂ��Ă͓����̊֐����Q�ƁB
	UpDown(Control& parent, Control& buddy, UpDown::Options options = Options::none);
	virtual ~UpDown();
	UpDown& operator=(UpDown&& value);

public:
	/// ���_�R���g���[���B���̃R���g���[���ɋz�����A���L�[��}�E�X�z�C�[���̓��͂�������� onUp, onDown �C�x���g�𔭐�������B
	/// ���_�R���g���[���̈ʒu��傫�����ς���Ă��Ǐ]�͂��Ȃ����ēx�ݒ肵�Ȃ����Ƌz������B
	Control* buddy() const;
	void buddy(Control* value);
	/// �t�H�[�J�X�𓾂��邩�ǂ����B
	virtual bool focusable() const;
	/// ���{�^�����������C�x���g�̃��X�i�[�B
	Listener<UpDown::Down&>& onDown();
	/// ��{�^�����������C�x���g�̃��X�i�[�B
	Listener<UpDown::Up&>& onUp();
	///	�R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B
	UpDown::Options options() const;

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	Size _buddySize;
	Listener<UpDown::Down&> _onDown;
	Listener<UpDown::Up&> _onUp;
};



	}
}