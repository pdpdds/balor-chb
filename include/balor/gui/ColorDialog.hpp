#pragma once

#include <balor/graphics/Color.hpp>
#include <balor/Event.hpp>
#include <balor/Listener.hpp>
#include <balor/Point.hpp>
#include <balor/Size.hpp>

struct HWND__;


namespace balor {
	namespace gui {



/**
 * �F�I���_�C�A���O�B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"ColorDialog sample");

	Brush frameBrush;
	ColorDialog dialog;
	Button selectColor(frame, 20, 10, 0, 0, L"�w�i�F�I��", [&] (Button::Click& ) {
		if (dialog.show(frame)) {
			frameBrush = Brush(dialog.color());
			frame.brush(frameBrush);
		}
	});

	frame.runMessageLoop();
 * </code></pre>
 */
class ColorDialog {
public:
	typedef ::HWND__* HWND;
	typedef ::balor::graphics::Color Color;


	/// ColorDialog �̃C�x���g�̐e�N���X�B
	struct Event : public balor::Event {
		Event(HWND sender);

		/// �_�C�A���O�̃E�C���h�E�n���h���B
		HWND sender() const;

	private:
		HWND _sender;
	};


	/// �_�C�A���O������������C�x���g�B
	struct Init : public Event {
		Init(HWND sender);

		/// �_�C�A���O�̃X�N���[�����W�ʒu�B
		/// ����ł̓A�v���P�[�V�����̃v���Z�X���N�����Ă���ŏ��̈�񂵂��ύX�ł��Ȃ��͗l�B���񂩂�͑O��̈ʒu����������Ă���B
		Point position() const;
		void position(const Point& value);
		void position(int x, int y);
		/// �_�C�A���O�̃N���C�A���g�̈�̑傫���B
		Size clientSize() const;
		void clientSize(int width, int height);
		void clientSize(const Size& value);
	};


public:
	ColorDialog();
	ColorDialog(ColorDialog&& value);
	~ColorDialog();

	/// �����F�܂��͍쐬�����F�B�����l�� Color::black()�B
	Color color() const;
	void color(const Color& value);
	/// �F�쐬�t�h��\�����邩�ǂ����Bfalse �̏ꍇ�ł��F�쐬�{�^���������Ε\�������B�����l�� true�B
	bool createColorUI() const;
	void createColorUI(bool value);
	/// �P�U�F�̍쐬�ς݂̐F�����擾����B�����l�͑S�� Color::black()�B
	Color getCustomColor(int index) const;
	/// �_�C�A���O������������C�x���g�B
	Listener<ColorDialog::Init&>& onInit();
	/// �P�U�F�̍쐬�ς݂̐F����ݒ肷��B
	void setCustomColor(int index, const Color& value);
	/// �_�C�A���O�{�b�N�X��\������B�F��I���������ǂ�����Ԃ��B
	bool show(HWND owner);

protected:
	Color _color;
	Color _customColors[16];
	int _flags;
	Listener<ColorDialog::Init&> _onInit;
};



	}
}