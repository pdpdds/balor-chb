#pragma once

struct tagPOINT;


namespace balor {



/**
 * ���ʂ̍��W��\���\���́B
 * 
 * �e�퉉�Z�q���T�|�[�g���鑼�AWIN32 �� POINT �\���̂Ƒ��ݕϊ��ł���B
 */
class Point {
public:
	typedef ::tagPOINT POINT;

public:
	/// �����������ɍ쐬�B
	Point() {}
	Point(const Point& value);
	/// POINT �\���̂ŏ������B
	Point(const POINT& point);
	/// ���W�ŏ������B
	Point(int x, int y);

public:
	/// �v�f���Ƃɍő�l�����߂�B
	static Point maximize(const Point& lhs, const Point& rhs);
	/// �v�f���Ƃɍŏ��l�����߂�B
	static Point minimize(const Point& lhs, const Point& rhs);

public:
	/// POINT �\���̂ւ̕ϊ�
	operator POINT() const;
	Point operator-() const;
	Point& operator += (const Point& rhs);
	friend Point operator + (const Point& lhs, const Point& rhs);
	Point& operator -= (const Point& rhs);
	friend Point operator - (const Point& lhs, const Point& rhs);
	bool operator == (const Point& rhs) const;
	bool operator != (const Point& rhs) const;

public:
	int x;
	int y;
};



}