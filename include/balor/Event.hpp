#pragma once


namespace balor {



/**
 * ���ׂẴC�x���g�N���X�̐e�N���X�B
 *
 * Event �̎Q�Ƃ������ɂƂ�֐��I�u�W�F�N�g�� Event �N���X�̔h���N���X�̎Q�Ƃ������ɂƂ邠����C�x���g���X�i�[�ɓo�^���邱�Ƃ��o����B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Event Sample");

	Button button(frame, 20, 10, 0, 0, L"�{�^��");
	CheckBox check(frame, 20, 50, 0, 0, L"�`�F�b�N");

	// Event& �������Ɏ��֐��I�u�W�F�N�g�͂�����C�x���g�ɑ���ł���B
	auto onAny = [&] (Event& ) {
		MsgBox::show(L"something event");
	};
	button.onClick() = onAny;
	check.onStateChange() = onAny;

	frame.runMessageLoop();
 * </code></pre>
 */
class Event {
};


/// �C�x���g�������𔺂��C�x���g�N���X�B
template<typename Sender>
class EventWithSender : public Event {
public:
	/// �C�x���g���������w�肵�č쐬�B
	EventWithSender(Sender& sender) : _sender(sender) {}

private: // �����̋֎~�B
	EventWithSender(const EventWithSender& );
	EventWithSender& operator=(const EventWithSender& );

public:
	/// �C�x���g�������B
	Sender& sender() { return _sender; }
	const Sender& sender() const { return _sender; }

private:
	Sender& _sender;
};


/// sender �֐���h���N���X�ŏ㏑������C�x���g�N���X�B
template<typename SubclassSender, typename BaseEvent>
class EventWithSubclassSender : public BaseEvent {
public:
	/// �C�x���g���������w�肵�č쐬�B
	EventWithSubclassSender(SubclassSender& sender) : BaseEvent(sender) {}

public:
	/// �C�x���g�������B
	SubclassSender& sender() { return static_cast<SubclassSender&>(BaseEvent::sender()); }
	const SubclassSender& sender() const { return static_cast<const SubclassSender&>(BaseEvent::sender()); }
};


}