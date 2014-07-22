#pragma once

#include <balor/Enum.hpp>
#include <balor/NonCopyable.hpp>

struct HBITMAP__;
struct HBRUSH__;


namespace balor {
	namespace graphics {

class Bitmap;
class Color;


/**
 * GDI �u���V��\���B
 */
class Brush : private NonCopyable {
public:
	typedef ::HBITMAP__* HBITMAP;
	typedef ::HBRUSH__* HBRUSH;

	/// �n�b�`�u���V�̎�ށB
	struct Hatch {
		enum _enum {
			none             = -1, /// �P�F�u���V
			horizontal       =  0, /// ���Ȗ͗l�B
			vertical         =  1, /// �c�Ȗ͗l�B
			forwardDiagonal  =  2, /// �S�T�x�E�オ��Ȗ͗l�B
			backwardDiagonal =  3, /// �S�T�x�E������Ȗ͗l�B
			cross            =  4, /// �c���Ȗ͗l�B
			diagonalCross    =  5, /// �S�T�x�E�オ��E����������Ȗ͗l�B
		};
		BALOR_NAMED_ENUM_MEMBERS(Hatch);
	};

public:
	/// �k���n���h���ō쐬�B
	Brush();
	Brush(Brush&& value);
	/// �n���h������쐬�Bowned �� true �Ȃ�΃f�X�g���N�^�Ńn���h����j������B
	explicit Brush(HBRUSH handle, bool owned = false);
	/// �r�b�g�}�b�v����p�^�[���u���V���쐬����B�쐬��A�r�b�g�}�b�v�n���h���͎Q�Ƃ���Ȃ��B
	explicit Brush(HBITMAP bitmap);
	/// �F�ƃn�b�`�̎�ނ���P�F�u���V�܂��̓n�b�`�u���V���쐬����B
	explicit Brush(const Color& color, Brush::Hatch hatch = Hatch::none);
	~Brush();

	Brush& operator=(Brush&& value);

public:
	/// �p�^�[���u���V�̃r�b�g�}�b�v��Ԃ��B�p�^�[���u���V�łȂ��ꍇ�̓k���n���h���̃r�b�g�}�b�v���Ԃ�B
	Bitmap bitmap() const;
	/// �������ĕԂ��B
	Brush clone() const;
	static Brush clone(HBRUSH handle);
	/// �P�F�܂��̓n�b�`�u���V�̐F�B�p�^�[���u���V�̏ꍇ�͖��Ӗ��B
	Color color() const;
	/// �n�b�`�u���V�̎�ނ�Ԃ��B
	Brush::Hatch hatch() const;
	/// �f�X�g���N�^�Ńn���h����j�����邩�ǂ����B�ύX�͗v���ӁB
	bool owned() const;
	void owned(bool value);

public: // �V�X�e���u���V�ꗗ
	/// �����u���V�B
	static Brush white();
	/// ���邢�D�F�u���V�B
	static Brush lightGray();
	/// �Â��D�F�u���V�B
	static Brush darkGray();
	/// �����u���V�B
	static Brush black();
	/// �`�悵�Ȃ��u���V�B
	static Brush hollow();

	static Brush activeBorder();
	static Brush activeCaption();
	static Brush activeCaptionText();
	static Brush appWorkspace();
	static Brush control();
	static Brush controlShadow();
	static Brush controlDarkShadow();
	static Brush controlLight();
	static Brush controlHighlight();
	static Brush controlText();
	static Brush desktop();
	static Brush gradientActiveCaption();
	static Brush gradientInactiveCaption();
	static Brush grayText();
	static Brush hotTrack();
	static Brush inactiveBorder();
	static Brush inactiveCaption();
	static Brush inactiveCaptionText();
	static Brush menu();
	static Brush menuBar();
	static Brush menuHighlight();
	static Brush menuText();
	static Brush scrollbar();
	static Brush selectedControl();
	static Brush selectedControlText();
	static Brush toolTip();
	static Brush toolTipText();
	static Brush window();
	static Brush windowFrame();
	static Brush windowText();

public:
	/// HBRUSH �ւ̎����ϊ� �� null �`�F�b�N�p
	operator HBRUSH() const { return _handle; }

private:
	HBRUSH _handle;
	bool _owned;
};



	}
}