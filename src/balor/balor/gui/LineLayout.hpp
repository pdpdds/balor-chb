#pragma once

#include <balor/gui/Control.hpp>


namespace balor {
	namespace gui {



/**
 * �q�R���g���[����ǉ��������ɍ��ォ��E�i�܂��͍��ォ�牺�j�ɕ��ׂĂ����A�͂ݏo�����ɂȂ�������s���郌�C�A�E�g�B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"LineLayout Sample");

	Label label(frame, 0, 0, 0, 0, L"�E�C���h�E�̑傫����ς���ƃR���g���[���̔z�u���ω�����");
	Button button0(frame, 0, 0, 0, 0, L"�{�^��0");
	Button button1(frame, 0, 0, 0, 0, L"�{�^��1");
	Button button2(frame, 0, 0, 0, 0, L"�{�^��2");
	Edit edit(frame, 0, 0, 0, 0, 100, 20);
	CheckBox check0(frame, 0, 0, 0, 0, L"�`�F�b�N0");
	CheckBox check1(frame, 0, 0, 0, 0, L"�`�F�b�N1");

	LineLayout layout(frame);
	layout.perform();
	frame.onResized() = [&] (Frame::Resized& ) {
		layout.perform();
	};
 
	frame.runMessageLoop();
 * </code></pre>
 */
class LineLayout : private NonCopyable {
public:
	/// �������Ȃ����C�A�E�g���쐬�B
	LineLayout();
	LineLayout(LineLayout&& value);
	/// ���C�A�E�g�ΏۂƏc�z�u���ǂ�������쐬�B
	LineLayout(Control& target, bool vertical = false);
	~LineLayout();
	LineLayout& operator=(LineLayout&& value);

public:
	/// �q�R���g���[�����m�̉��Əc�̌��ԁB�����l�� Size(10, 20)�B
	Size margin() const;
	void margin(const Size& value);
	void margin(int width, int height);
	/// ���C�A�E�g���X�V����B
	void perform();
	/// Scaler ���g���ă��C�A�E�g�ݒ���X�P�[�����O����B�R���g���[���͕ʓr�X�P�[�����O���K�v�B
	void scale(const Scaler& scaler);
	/// �ŏ��̎q�R���g���[�����ǂ��ɔz�u���邩�B�����l�� Size(10, 10)�B
	Point startPosition() const;
	void startPosition(const Point& value);
	void startPosition(int x, int y);
	/// ���C�A�E�g�Ώۂ̃R���g���[���B
	Control* target();
	/// �c�z�u���ǂ����B
	bool vertical() const;
	void vertical(bool value);

private:
	Reference<Control> _target;
	bool _vertical;
	Point _startPosition;
	Size _margin;
};



	}
}