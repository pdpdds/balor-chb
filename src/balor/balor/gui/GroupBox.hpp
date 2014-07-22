#pragma once

#include <balor/gui/Control.hpp>


namespace balor {
	namespace gui {



/**
 * �O���[�v�{�b�N�X�B
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
class GroupBox : public Control {
public:
	/// �k���n���h���ō쐬�B
	GroupBox();
	GroupBox(GroupBox&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫���A�����񂩂�쐬�B
	GroupBox(Control& parent, int x, int y, int width, int height, StringRange text);
	virtual ~GroupBox();
	GroupBox& operator=(GroupBox&& value);

public:
	/// �w�i�u���V�B�ݒ肵�Ȃ���ΐe�R���g���[���̃u���V���g�p����B
	virtual Brush brush() const;
	using Control::brush;
	/// �w�i�u���V�̌��_�B
	virtual Point brushOrigin() const;
	using Control::brushOrigin;
	/// ���z�I�ȃR���g���[���̃N���C�A���g���W�Ƒ傫���B
	virtual Rectangle displayRectangle() const;
	/// �t�H�[�J�X�𓾂��邩�ǂ����B
	virtual bool focusable() const;
	/// �q�R���g���[�������܂�œK�ȑ傫�������߂�B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);
};



	}
}