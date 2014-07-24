#pragma once


namespace balor {

class Point;



/**
 * ���ƍ����ɂ�鐡?��?��?���́B
 */
class Size {
public:
	/// �����������ɍ쐬�B
	Size() {}
	Size(const Size& size);
	/// Point ?���̂ŏ������B
	Size(const Point& point);
	/// ���ƍ����ŏ������B
	Size(int width, int height);

public:
	/// �v�f���Ƃɍŏ��l�����߂�B
	static Size minimize(const Size& lhs, const Size& rhs);
	/// �v�f���Ƃɍő�l�����߂�B
	static Size maximize(const Size& lhs, const Size& rhs);
	/// �v�f�ɕ������܂܂�邩�ǂ���
	bool negative() const;

public:
	/// Point ?���̂ւ̕ϊ��B
	operator Point() const;
	Size& operator += (const Size& rhs);
	friend Size operator + (const Size& lhs, const Size& rhs);
	Size& operator -= (const Size& rhs);
	friend Size operator - (const Size& lhs, const Size& rhs);
	Size& operator *= (int rhs);
	friend Size operator * (const Size& lhs, int rhs);
	Size& operator /= (int rhs);
	friend Size operator / (const Size& lhs, int rhs);
	bool operator == (const Size& rhs) const;
	bool operator != (const Size& rhs) const;

public:
	int width;
	int height;
};



}