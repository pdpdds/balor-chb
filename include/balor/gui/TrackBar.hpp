#pragma once

#include <balor/gui/Control.hpp>
#include <balor/Enum.hpp>


namespace balor {
	namespace gui {

class ToolTip;



/**
 * �g���b�N�o�[�B
 * 
 * ValueChange �� pageSize, minimum, maximum �̕ύX�� value ���ω������ꍇ�ɂ͔������Ȃ��B
 * minimum �� maximum ���傫�����Ă� maximum = minimum �ɂȂ邾���ő����ʂ̕����͕ς��Ȃ��B
 * �ȉ��� CTRL �L�[�������Ȃ���h���b�O�Ŕ͈͑I�����s���R�[�h�̗�B
 * <pre><code>
 *	trackBar.thick(true);
 *	int start = 0;
 *	trackBar.onMouseDown() = [&] (Control::MouseDown& e) {
 *		if (e.lButton() && e.ctrl()) {
 *			start = trackBar.value();
 *			trackBar.selectionBegin(start);
 *			trackBar.selectionEnd(start);
 *		}
 *	};
 *	trackBar.onMouseMove() = [&] (Control::MouseMove& e) {
 *		if (e.lButton() && e.ctrl()) {
 *			auto value = trackBar.value();
 *			if (value <= start) {
 *				trackBar.selectionBegin(value);
 *				trackBar.selectionEnd(start);
 *			} else {
 *				trackBar.selectionBegin(start);
 *				trackBar.selectionEnd(value);
 *			}
 *		}
 *	};
 * </code></pre>
 *
 * TBM_SETTOOLTIPS �ɂ��Ă͐ݒ肵���c�[���`�b�v���\������Ȃ������B�v�����B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"TrackBar Sample");

	TrackBar track(frame, 20, 10, 0, 0, 0, 100, TrackBar::Options::valueTip);
	Edit edit(frame, track.bounds().right() + 10, 10, 0, 0, 4);
	edit.readOnly(true);
	edit.text(String() + track.value());
	track.onValueChange() = [&] (TrackBar::ValueChange& e) {
		edit.text(String() + e.newValue());
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class TrackBar : public Control {
public:
	/// �R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none     = 0      ,
			valueTip = 0x0100L, /// �X���C�_�[���ړ����ɒl���c�[���`�b�v�ŕ\������B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


	/// �ڐ�����ǂ��ɕ\�����邩�B�X���C�_�[�͖ڐ���̂�����������B
	struct TickStyle {
		enum _enum {
			left   = 0x0004, /// ���ɖڐ����\������B���c�\���̏ꍇ�B
			top    = 0x0004, /// ��ɖڐ����\������B�����\���̏ꍇ�B
			right  = 0x0000, /// �E�ɖڐ����\������B���c�\���̏ꍇ�B
			bottom = 0x0000, /// ���ɖڐ����\������B�����\���̏ꍇ�B
			both   = 0x0008, /// �㉺�܂��͍��E�ɖڐ����\������B�X���C�_�[�͒����`�ɂȂ�B
		};
		BALOR_NAMED_ENUM_MEMBERS(TickStyle);
	};

	/// �X���C�_�[�ړ����ɕ\������c�[���`�b�v�̈ʒu�B
	struct ValueTipSide {
		enum _enum {
			top    = 0, /// ��ɕ\������B�����\���̏ꍇ�B
			left   = 1, /// ���ɕ\������B���c�\���̏ꍇ�B
			bottom = 2, /// ���ɕ\������B�����\���̏ꍇ�B
			right  = 3, /// �E�ɕ\������B���c�\���̏ꍇ�B
		};
		BALOR_NAMED_ENUM_MEMBERS(ValueTipSide);
	};


	/// �g���b�N�o�[�̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<TrackBar, Control::Event> Event;


	/// value ���ω������C�x���g�B
	struct ValueChange : public Event {
		ValueChange(TrackBar& sender, int oldValue, int newValue, bool tracking);
		/// �V���� value�B
		int newValue() const;
		/// �Â� value�B
		int oldValue() const;
		/// �X���C�_�[���g���b�L���O�����ǂ����B
		bool tracking() const;

	private:
		int _newValue;
		int _oldValue;
		bool _tracking;
	};


public:
	/// �k���n���h���ō쐬�B
	TrackBar();
	TrackBar(TrackBar&& value, bool checkSlicing = true);
	/// �e�R���g���[���A�ʒu�A�傫���A�ŏ��ʒu�A�ő�ʒu����쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B���̑��̈����͓����̊֐����Q�ƁB
	TrackBar(Control& parent, int x, int y, int width, int height, int minimum = 0, int maximum = 100, TrackBar::Options options = Options::none);
	virtual ~TrackBar();
	TrackBar& operator=(TrackBar&& value);

public:
	/// �I��͈͂��N���A����B
	void clearSelection();
	/// �ڐ��������������B�ŏ��ƍŌ�̖ڐ��肾���c��B
	void clearTick();
	/// �����L�[�����������ɍ��Ɉړ����邩�ǂ����B�����l�� false�B
	bool downIsLeft() const;
	void downIsLeft(bool value);
	void endSelect();
	/// ���݂̏�Ԃ���œK�ȑ傫�������߂�B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// ���L�[���������Ƃ��܂��̓}�E�X�z�C�[���̃X���C�_�[�̈ړ��ʁB�����l�͂P�B
	int lineSize() const;
	void lineSize(int value);
	/// �X���C�_�[�ړ��ł���ő�l�B
	int maximum() const;
	void maximum(int value);
	/// �X���C�_�[�ړ��ł���ŏ��l�B
	int minimum() const;
	void minimum(int value);
	/// value ���ω������C�x���g�̃��X�i�[�B
	Listener<ValueChange&>& onValueChange();
	///	�R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B
	TrackBar::Options options() const;
	/// �y�[�W�ړ��̑傫���B�i�X���C�_�[�̖��������N���b�N������APageUp�APageDown �L�[�����������j
	int pageSize() const;
	void pageSize(int value);
	/// Scaler ���g���ăR���g���[�����X�P�[�����O����B
	virtual void scale(const Scaler& scaler);
	/// �͈͑I���̊J�n�_�Bthick() �� true �ł���ꍇ�̂ݗL���B
	int selectionBegin() const;
	void selectionBegin(int value);
	/// �͈͑I���̏I���_�Bthick() �� true �ł���ꍇ�̂ݗL���B
	int selectionEnd() const;
	void selectionEnd(int value);
	/// �w�肵���l�̈ʒu�ɖڐ����ǉ�����B
	void setTick(int value);
	/// �X���C�_�[�̈ړ��͈͂̐����������ǂ����B�܂��͔͈͑I����L���ɂ��邩�ǂ����B�����l�� false�B
	bool thick() const;
	void thick(bool value);
	/// �܂݂̑傫���B�ڐ���ƌ�����������̃s�N�Z���T�C�Y�BtickStyle() �� TrackBar::TickStyle::both �̏ꍇ�̂ݗL���B
	int thumbSize() const;
	void thumbSize(int value);
	/// �܂݂�\�����邩�ǂ����B�����l�� true�B
	bool thumbVisible() const;
	void thumbVisible(bool value);
	/// �ڐ���̐��B
	int tickCount() const;
	/// �ڐ���̕\���Ԋu�B
	void tickFrequency(int value);
	/// �ڐ�����ǂ��ɕ\�����邩�B�X���C�_�[�̌`�ɂ��e������B�����l�� TrackBar::TickStyle::both�B
	TrackBar::TickStyle tickStyle() const;
	void tickStyle(TrackBar::TickStyle value);
	/// �ڐ����\�����邩�ǂ����B�����l�� false�B
	bool tickVisible() const;
	void tickVisible(bool value);
	/// ���݂̃X���C�_�[�ʒu�̒l�B
	int value() const;
	void value(int value);
	/// �X���C�_�[���ړ����ɒl��\������c�[���`�b�v�R���g���[���̎Q�ƁBoptions() �� TrackBar::Options::valueTip ��ݒ肵�Ă���ꍇ�̂ݗL���B
	/// �K�v�Ȑݒ���s������j�����Ă��ǂ����ꕔ�ݒ��C�x���g�͔j������Ɩ����ɂȂ�B������x TrackBar �����䂵�Ă���̂œ��삵�Ȃ��ݒ������B
	ToolTip valueTip();
	/// valueTip ���\�������ʒu�B
	void valueTipSide(TrackBar::ValueTipSide value);
	/// �����g���b�N�o�[���ǂ����B
	bool vertical() const;
	void vertical(bool value);

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	int _value;
	Listener<ValueChange&> _onValueChange;
};



	}
}