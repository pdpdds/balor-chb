#pragma once

#include <balor/Enum.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/StringRange.hpp>

struct HFONT__;
struct tagLOGFONTW;

namespace std {
template<typename T> class allocator;
template<typename T, typename A> class vector;
}

namespace balor {
class String;
}


namespace balor {
	namespace graphics {



/**
 * GDI �t�H���g��\���B
 * 
 * �t�H���g�T�C�Y�Ƀ|�C���g�P�ʂ��g�������ꍇ�� Graphics::pointToPixel �֐����g���B
 * �c�����w��� �R���X�g���N�^�Ńt�H���g���̐擪��@�����Aescapement �� orientation �� 2700 �Ɏw�肷��B
 * �c������p�t�H���g�łȂ��Ƃ� escapement �ňꉞ�c�����ɂ͂Ȃ邪�u�B�v���̏����ȕ����������Ɋ񂹂���̂Ŏg���ɂ����B
 * TODO:���ϕ������A�A�Z���g�A�f�B�Z���g�����̏��擾�B
 */
class Font : private NonCopyable {
public:
	typedef ::HFONT__* HFONT;
	typedef ::tagLOGFONTW LOGFONTW;

	/// �t�H���g�̕`��i���B
	/// XP�ł� nonantialiased �ȊO�� antialiased �Ɠ������悤���B
	/// Vista�ł� antialiased �� nonantialiased �͂w�o�Ɠ�����������ȊO�� ClearType �̂ڂ�����������B
	/// Vista�ɂ����āA�l�r �S�V�b�N�̓t�H���g�̃s�N�Z���T�C�Y���A���`�G�C���A�X�� 25 �����A ClearType �̂ڂ����� 23 �������Ƃ�����Ȃ��Ȃ邪�A
	/// ���C���I�� 23 �����ł�����������B
	struct Quality {
		enum _enum {
			default          = 0, /// �i�����d�����Ȃ��B
			draft            = 1, /// proof �̎��ɕi�����d������B
			proof            = 2, /// �ł��i�����d������B
			nonantialiased   = 3, /// �A���`�G�C���A�X�������Ȃ��B
			antialiased      = 4, /// �A���`�G�C���A�X��������B
			clearType        = 5, /// �N���A�^�C�v�̃A���`�G�C���A�X��������B
		};
		BALOR_NAMED_ENUM_MEMBERS(Quality);
	};

	/// �t�H���g�̃X�^�C���B�g�ݍ��킹�Ŏw�肷��B
	struct Style {
		enum _enum {
			regular   = 0x00, /// ���ʂ̎��́B
			bold      = 0x01, /// �����B
			italic    = 0x02, /// �ΆB
			strikeout = 0x04, /// ���������t���B
			underline = 0x08, /// �����t���B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Style);
	};

public:
	/// �k���n���h���ō쐬�B
	Font();
	Font(Font&& value);
	/// �n���h������쐬�Bowned �� true �Ȃ�΃f�X�g���N�^�Ńn���h����j������B
	explicit Font(HFONT handle, bool owned = false);
	/// �t�H���g��V�����傫���ƃX�^�C���ŕ�������B
	Font(const Font& font, int height, Font::Style style = Style::regular);
	/// �e���������Ƀt�H���g���쐬����Bheight �̓s�N�Z���T�C�Y�B
	Font(StringRange name, int height, Font::Style style = Style::regular, Font::Quality quality = Quality::proof, int escapement = 0, int orientation = 0);
	~Font();
	Font& operator=(Font&& value);

public:
	/// �����̕��ϕ��B
	int averageWidth() const;
	/// �������쐬���ĕԂ��B
	Font clone() const;
	static Font clone(HFONT handle);
	/// ������������̊p�x�B�i0�`3600�j
	int escapement() const;
	/// LOGFONTW �\���̂���쐬�B
	static Font fromLogFont(const LOGFONTW& logfont);
	/// �����̃s�N�Z���P�ʂ̍����B
	int height() const;
	/// �t�H���g���B�R���X�g���N�^�Ŏw�肵�����O�Ƃ͌���Ȃ��B�ŏI�I�ɑI�΂ꂽ���O�ɂȂ�B
	String name() const;
	/// �g�p�ł���t�H���g�����X�g�B
	static std::vector<String, std::allocator<String> > names();
	/// �����̃x�[�X���C���ɑ΂���\�������̊p�x�B�i0�`3600�j
	int orientation() const;
	/// �f�X�g���N�^�Ńn���h����j�����邩�ǂ����B�ύX�͗v���ӁB
	bool owned() const;
	void owned(bool value);
	/// �`��i��
	Font::Quality quality() const;
	/// �t�H���g�X�^�C���B
	Font::Style style() const;

public:// �V�X�e���t�H���g�ꗗ�B
	static Font ansiFixed();
	static Font ansiVar();
	static Font deviceDefault();
	/// Control �̃f�t�H���g�t�H���g�B
	static Font defaultGui();
	static Font oemFixed();
	static Font system();
	static Font systemFixed();

public:
	/// HFONT �ւ̎����ϊ� �� null �`�F�b�N�p
	operator HFONT() const { return _handle; }

private:
	HFONT _handle;
	bool _owned;
};



	}
}