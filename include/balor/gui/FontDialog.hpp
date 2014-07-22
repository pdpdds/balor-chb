#pragma once

#include <balor/graphics/Color.hpp>
#include <balor/graphics/Font.hpp>
#include <balor/Event.hpp>
#include <balor/Listener.hpp>
#include <balor/Point.hpp>
#include <balor/Size.hpp>

struct HWND__;


namespace balor {
	namespace gui {



/**
 * �t�H���g�I���_�C�A���O�B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"FontDialog sample");

	FontDialog dialog;
	dialog.font(Font::defaultGui());
	Button selectFont(frame, 20, 10, 0, 0, L"�t�H���g�I��", [&] (Button::Click& ) {
		if (dialog.show(frame)) {
			frame.invalidate();
		}
	});
	frame.onPaint() = [&] (Frame::Paint& e) {
		auto g = e.graphics();
		g.brush(Color::control());
		g.clear();
		g.font(dialog.font());
		g.textColor(dialog.color());
		g.backTransparent(true);
		g.drawText(L"aBc���a����������������", 10, 100);
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class FontDialog {
public:
	typedef ::HWND__* HWND;
	typedef ::balor::graphics::Color Color;
	typedef ::balor::graphics::Font Font;
	typedef ::balor::graphics::Font::HFONT HFONT;


	/// FontDialog �̃C�x���g�̐e�N���X�B
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
	FontDialog();
	FontDialog(FontDialog&& value);
	virtual ~FontDialog();

	/// �����Z�b�g��I������t�h��L���ɂ��邩�ǂ����B�����l�� true�B
	bool charsetUI() const;
	void charsetUI(bool value);
	/// �t�H���g�̏����F�܂��͑I�������t�H���g�̐F�B�����l�� Color::black()�B
	Color color() const;
	void color(const Color& value);
	/// ���������A�����A�F��I������t�h��\�����邩�ǂ����B�����l�� true�B
	bool effectsUI() const;
	void effectsUI(bool value);
	/// �Œ�s�b�`�t�H���g�̂ݑI���ł��邩�ǂ����B�����l�� false�B
	bool fixedPitchOnly() const;
	void fixedPitchOnly(bool value);
	/// �����t�H���g�܂��͑I�������t�H���g�B�����l�̓k���n���h���� Font�B
	const Font& font() const;
	void font(HFONT value);
	/// �_�C�A���O������������C�x���g�B
	Listener<FontDialog::Init&>& onInit();
	/// �� OEM�A�V���{���AANSI �����Z�b�g��I���ł��邩�ǂ����B�����l�� false�B
	bool scriptsOnly() const;
	void scriptsOnly(bool value);
	/// �_�C�A���O�{�b�N�X��\������B�F��I���������ǂ�����Ԃ��B
	bool show(HWND owner);
	/// �c�����t�H���g��I���ł��邩�ǂ����B�����l�� true�B
	bool verticalFonts() const;
	void verticalFonts(bool value);

protected:
	Font _font;
	Color _color;
	int _flags;
	Listener<FontDialog::Init&> _onInit;
};



	}
}