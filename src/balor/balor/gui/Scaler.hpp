#pragma once

#include <balor/Size.hpp>

struct HFONT__;

namespace balor {
	class Point;
	class Rectangle;
}


namespace balor {
	namespace gui {

class Padding;



/**
 * ���l�̃X�P�[�����O���s���B
 *
 * ��ʉ𑜓x�i�c�o�h�j�������ɃR���g���[�����X�P�[�����O����̂Ɏg���B
 */
class Scaler {
public:
	typedef ::HFONT__* HFONT;

public:
	/// defaultDpi() ���猻�݂̉�ʂ� DPI �ւ̃X�P�[�����O���s���悤�ɍ쐬�B
	Scaler();
	/// from ���� to �ւ̃X�P�[�����O���s���悤�ɍ쐬�BSize �� width, height �͂��ꂼ�ꐅ�������Ɛ��������̃X�P�[�����O�ɂ������B
	/// �Ⴆ�Ή��L�̂悤�ɍ쐬����Əc�������ɂQ�{�̃X�P�[�����O���s���B<br><br>
	///  Scale(Size(100, 100), Size(200, 200))
	Scaler(const Size& from, const Size& to);
	/// �c���䗦�𓙂������̂Ƃ��� from ���� to �ւ̃X�P�[�����O���쐬�B
	Scaler(int from, int to);
	/// �t�H���g�̕��ϕ������ƍ�������X�P�[�����O���s���悤�ɍ쐬�B
	Scaler(HFONT from, HFONT to);

public:
	/// �f�t�H���g�R���X�g���N�^�� from �Ɏg�p���� DPI�B�����l�� Size(96, 96)�B���̒l�� Control �₻�̔h���N���X�̓����ł��g���Ă���̂�
	/// ���ɊJ������ DPI �� 96 �ł͂Ȃ��ꍇ�̓R���g���[�����쐬����O�ɊJ������ DPI ��ݒ肷��K�v������B
	static Size defaultDpi();
	static void defaultDpi(const Size& value);
	/// ���������̔{���ŃX�P�[�����O����B
	int scale(int value) const;
	double scale(double value) const;
	/// ���������̔{���ŃX�P�[�����O����B
	int scaleH(int value) const;
	double scaleH(double value) const;
	/// ���������̔{���ŃX�P�[�����O����B
	int scaleV(int value) const;
	double scaleV(double value) const;
	/// �X�P�[�����O����B
	Padding scale(const Padding& value) const;
	Point scale(const Point& value) const;
	Rectangle scale(const Rectangle& value) const;
	Size scale(const Size& value) const;

private:
	Size _from;
	Size _to;
};



	}
}