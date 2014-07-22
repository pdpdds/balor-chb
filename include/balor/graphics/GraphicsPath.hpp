#pragma once

#include <vector>

#include <balor/graphics/Graphics.hpp>
#include <balor/ArrayRange.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/StringRange.hpp>

struct HDC__;
struct HFONT__;
struct HPEN__;

namespace balor {
class Point;
class Rectangle;
class Size;
}


namespace balor {
	namespace graphics {



/**
 * �`�悵����A�̐��̏W����\���B
 *
 * GraphicsPath �� Graphics �N���X�̊֐��Ɛ}�`�̕`�挋�ʂ������ɈقȂ�̂łP�h�b�g�̈Ⴂ�������Ȃ��ꍇ�ɂ͎g�p���ׂ��ł͂Ȃ��B
 * Graphics::drawPath �����ꍇ�� Graphics::draw�`�n�֐��ƌ��ʂ�����������v���邪�AGraphics::fillPath �����ꍇ��
 * �}�`�̉E���s�N�Z�����������`�ɂȂ邩�A�}�`�ɂ���Ă͗֊s�������������`�ɂȂ�B
 * �܂� GraphicsPath ���� Region ���쐬�����ꍇ�͎�� fillPath �����ꍇ�̗̈悪�쐬�����B
 */
class GraphicsPath : private NonCopyable {
public:
	typedef ::HDC__* HDC;
	typedef ::HFONT__* HFONT;
	typedef ::HPEN__* HPEN;

	/// �`�悵�����̃f�[�^�B
	class Data {
	public:
		Data() {}
		Data(Data&& value);

		Data& operator=(Data&& value);

	public:
		std::vector<Point> points;
		std::vector<unsigned char> types;
	};


public:
	/// �܂�����ȕ`���Ԃō쐬�B
	GraphicsPath();
	GraphicsPath(GraphicsPath&& value);
	/// �}�`�f�[�^����쐬�B
	explicit GraphicsPath(const Data& data);
	~GraphicsPath();

	GraphicsPath& operator=(GraphicsPath&& value);

public:
	/// �~�ʂ�ǉ�����B
	void addArc(const Rectangle& rect, float startAngle, float sweepAngle);
	void addArc(int x, int y, int width, int height, float startAngle, float sweepAngle);
	/// �x�W�F�Ȑ���ǉ�����B�I�_�̃s�N�Z���͕`�悳��Ȃ��B
	void addBezier(const Point& p0, const Point& p1, const Point& p2, const Point& p3);
	void addBezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
	/// �x�W�F�Ȑ���A���Œǉ�����B�I�_�̃s�N�Z���͕`�悳��Ȃ��B
	void addBeziers(ArrayRange<const Point> points);
	/// �~��ǉ�����B
	void addCircle(const Point& point, int radius);
	void addCircle(int x, int y, int radius);
	/// �ȉ~��ǉ�����B
	void addEllipse(const Rectangle& rect);
	void addEllipse(int x, int y, int width, int height);
	/// ������ǉ�����B�I�_�̃s�N�Z���͕`�悳��Ȃ��B
	void addLine(const Point& p0, const Point& p1);
	void addLine(int x0, int y0, int x1, int y1);
	/// ������A���Œǉ�����B�I�_�̃s�N�Z���͕`�悳��Ȃ��B
	void addLines(ArrayRange<const Point> points);
	/// �p�X��ǉ�����B
	void addPath(const GraphicsPath& path);
	/// ��`��ǉ�����B
	void addPie(const Rectangle& rectangle, float startAngle, float sweepAngle);
	void addPie(int x, int y, int width, int height, float startAngle, float sweepAngle);
	/// ���p�`��ǉ�����B
	void addPolygon(ArrayRange<const Point> points);
	/// �����`��ǉ�����B
	void addRectangle(const Rectangle& rect);
	void addRectangle(int x, int y, int width, int height);
	/// �����`��A���Œǉ�����B
	void addRectangles(ArrayRange<const Rectangle> rects);
	/// �������ǉ�����B
	void addText(StringRange s, const Point& point);
	void addText(StringRange s, int x, int y);
	void addText(StringRange s, const Rectangle& rect, Graphics::TextFormat format = Graphics::TextFormat::default);
	/// �}�`���܂ދ�`�B
	Rectangle bounds() const;
	/// ������Ԃ��B
	GraphicsPath clone() const;
	/// ���O�ɕ`�����}�`�����B
	void closeFigure();
	/// �}�`�f�[�^�B
	Data data() const;
	/// �Ȑ��f�[�^�𒼐��ɕ�������B
	void flatten();
	/// ������`�悷��t�H���g�B
	Font font() const;
	Font font(HFONT value);
	/// HDC ��Ԃ��B
	HDC hdc() const { return _handle; }
	/// �_���}�`�Ɋ܂܂�邩�ǂ����B
	bool isVisible(const Point& point) const;
	bool isVisible(int x, int y) const;
	/// �Ō�̐}�`�������I������_�B
	Point lastPoint() const;
	/// �}�`��S�ď����B
	void reset();
	/// �}�`�̐����w�肵���y���̑����ɂ���B�������������̂��}�`�ɂȂ�B
	void widen(HPEN pen);

private:
	HDC _handle;
	bool _closed;
};



	}
}