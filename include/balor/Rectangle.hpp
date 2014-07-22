#pragma once


struct tagRECT;


namespace balor {

class Size;
class Point;



/**
 * ���ʏ�̈ʒu�Ƒ傫�������̈��\���\���́B
 *
 * WIN32 �� RECT �\���̂Ƒ��ݕϊ��ł���B
 * WIN32 �� Rectangle �֐��Ɩ��O�����Ԃ�̂� windows.h �ƈꏏ�Ɏg���ꍇ�͕ʖ��� Rect ���g���Ɨǂ��B
 */
class Rectangle {
public:
	typedef ::tagRECT RECT;

public:
	/// �����������ɍ쐬�B
	Rectangle() {}
	Rectangle(const Rectangle& rectangle);
	/// RECT �\���̂ŏ������B
	Rectangle(const RECT& rect);
	/// �ʒu�Ƒ傫���̍\���̂ŏ������B
	Rectangle(const Point& position, const Size& size);
	/// �ʒu�Ƒ傫���ŏ������B
	Rectangle(int x, int y, int width, int height);

public:
	/// �̈�̉��[���W�B
	int bottom() const { return y + height; }
	/// �̈�̍������W�B
	Point bottomLeft() const;
	/// �̈�̉E�����W�B
	Point bottomRight() const;
	/// �_�����̗̈�Ɋ܂܂�邩�ǂ����B
	bool contains(const Point& point) const;
	bool contains(int x, int y) const;
	/// rect �S�̂����̗̈�Ɋ܂܂�邩�ǂ����B
	bool contains(const Rectangle& rect) const;
	/// left, top, right, bottom ���W�n����쐬����B
	static Rectangle fromLTRB(int left, int top, int right, int bottom);
	/// �w�肵���傫�����A�㉺���E�Ɋg�傷��B
	void grow(const Size& size);
	void grow(int width, int height);
	/// ��̗̈�̌���������Ԃ��B
	static Rectangle intersection(const Rectangle& lhs, const Rectangle& rhs);
	/// �̈悪�������邩�ǂ����B
	bool intersects(const Rectangle& rhs) const;
	/// �̈�̍��[���W�B
	int left() const { return x; }
	/// ��̗̈�̌���������Ԃ��B
	static Rectangle or(const Rectangle& lhs, const Rectangle& rhs);
	/// �̈�̍�����W�B
	Point position() const;
	void position(const Point& value);
	void position(int x, int y);
	/// �̈�̉E�[���W�B
	int right() const { return x + width; }
	/// �̈�̑傫���B
	Size size() const;
	void size(const Size& value);
	void size(int width, int height);
	/// �̈�̏�[���W�B
	int top() const { return y; }
	/// �̈�̍�����W�B
	Point topLeft() const;
	/// �̈�̉E����W�B
	Point topRight() const;
	/// ���W�̐��l���ړ�����B
	void translate(const Point& point);
	void translate(int x, int y);

public:
	/// RECT �\���̂ւ̕ϊ��B
	operator RECT() const;
	bool operator == (const Rectangle& rhs) const;
	bool operator != (const Rectangle& rhs) const;

public:
	int x;
	int y;
	int width;
	int height;
};


/// Rectangle �� WIN32 �̊֐����Ƃ��Ԃ�̂� windows.h �ƈꏏ�Ɏg���ꍇ�͂��̖��O��
typedef Rectangle Rect;



}