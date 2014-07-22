#pragma once

#include <balor/ArrayRange.hpp>
#include <balor/Enum.hpp>
#include <balor/NonCopyable.hpp>

struct HBRUSH__;
struct HPEN__;


namespace balor {
	namespace graphics {

class Brush;
class Color;



/**
 * GDI �y����\���B
 */
class Pen : private NonCopyable {
public:
	typedef ::HBRUSH__* HBRUSH;
	typedef ::HPEN__* HPEN;

	/// ���̎n�_�ƏI�_�̌`�B
	struct LineCap {
		enum _enum {
			round  = 0x00000000, /// ���̒[�_���ۂ�����B
			square = 0x00000100, /// ���̒[�_���l�p������B
			flat   = 0x00000200, /// ���̒[�_�𕽂�ɂ���Bsquare ���[�_�Ɏl�p�̔�����ǉ�����̂ɑ΂� flat �͒[�_�ŃJ�b�g����B
		};
		BALOR_NAMED_ENUM_MEMBERS(LineCap);
	};


	/// ���̐ڑ������̌`�B
	struct LineJoin {
		enum _enum {
			round  = 0x00000000, /// �ڑ��������ۂ�����B
			bevel  = 0x00001000, /// �ڑ������𕽂�ɂ���B
			mitter = 0x00002000, /// ���Ɛ��̋����� Graphics::mitterLimit() �ȉ��Ȃ�ΐڑ��������点��B�����łȂ���� bevel �Ɠ����B
		};
		BALOR_NAMED_ENUM_MEMBERS(LineJoin);
	};

	/// �y���̐��̃X�^�C���B
	struct Style {
		enum _enum {
			solid       = 0, /// �����B
			dash        = 1, /// �j���B
			dot         = 2, /// �_���B
			dashDot     = 3, /// ��_�����B
			dashDotDot  = 4, /// ��_�����B
			null        = 5, /// ����`�悵�Ȃ��B
			insideFrame = 6, /// �����ŁA�}�`��`���ꍇ�ɐ������}�`���Ɋ��S�Ɏ��܂�悤�ɏ����B
			custom      = 7, /// ���̃p�^�[�������[�U���ݒ肷��B
		};
		BALOR_NAMED_ENUM_MEMBERS(Style);
	};

public:
	/// �k���n���h���ō쐬�B
	Pen();
	Pen(Pen&& value);
	/// �n���h������쐬�Bowned �� true �Ȃ�΃f�X�g���N�^�Ńn���h����j������B
	explicit Pen(HPEN handle, bool owned = false);
	/// �u���V�ƕ��ƃX�^�C��������쐬�B�쐬��A�u���V�n���h���͎Q�Ƃ���Ȃ��B
	explicit Pen(HBRUSH brush, int width = 1, Pen::Style style = Style::solid, LineCap lineCap = LineCap::square, LineJoin lineJoin = LineJoin::mitter);
	/// �u���V�ƕ��Ɠ_���̃p�^�[��������쐬�B�쐬��A�u���V�n���h���͎Q�Ƃ���Ȃ��B
	Pen(HBRUSH brush, int width, ArrayRange<const int> patten, LineCap lineCap = LineCap::square, LineJoin lineJoin = LineJoin::mitter);
	/// �F�ƕ��ƃX�^�C��������쐬�B
	explicit Pen(const Color& color, int width = 1, Pen::Style style = Style::solid, LineCap lineCap = LineCap::square, LineJoin lineJoin = LineJoin::mitter);
	/// �F�ƕ��Ɠ_���̃p�^�[��������쐬�B
	Pen(const Color& color, int width, ArrayRange<const int> patten, LineCap lineCap = LineCap::square, LineJoin lineJoin = LineJoin::mitter);
	~Pen();

	Pen& operator=(Pen&& value);

public:
	/// �`��Ɏg���u���V�B�u���V���g��Ȃ��ꍇ�̓k���n���h���̃u���V���Ԃ�B
	Brush brush() const;
	/// ������Ԃ��B
	Pen clone() const;
	static Pen clone(HPEN handle);
	/// ���̐F�B�u���V���g���ꍇ�͈Ӗ��������Ȃ��B
	Color color() const;
	/// ���̎n�_�ƏI�_�̌`�B
	Pen::LineCap lineCap() const;
	/// ���̐ڑ��_�̌`�B
	Pen::LineJoin lineJoin() const;
	/// �f�X�g���N�^�Ńn���h����j�����邩�ǂ����B�ύX�͗v���ӁB
	bool owned() const;
	void owned(bool value);
	/// �_���̃p�^�[���B�R���X�g���N�^�Ŏw�肵�Ȃ������ꍇ�͋�̔z��B
	std::vector<int, std::allocator<int> > pattern() const;
	/// �_���̃X�^�C���B
	Pen::Style style() const;
	/// ���̕��B
	int width() const;

public: // �V�X�e���y���ꗗ
	/// ���������̃y���B
	static Pen white();
	/// ���������̃y���B
	static Pen black();
	/// �`�悵�Ȃ��y���B
	static Pen hollow();

public:
	/// HPEN �ւ̎����ϊ� �� null �`�F�b�N�p
	operator HPEN() const { return _handle; }

private:
	HPEN _handle;
	bool _owned;
};



	}
}