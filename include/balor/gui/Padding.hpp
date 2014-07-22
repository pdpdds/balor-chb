#pragma once


namespace balor {
class Size;
}

		
namespace balor {
	namespace gui {



/**
 * �㉺���E�̗]����\���B
 */
class Padding {
public:
	/// �����������ɍ쐬�B
	Padding() {}
	Padding(const Padding& value);
	/// �S�ē������l�ŏ������B
	Padding(int all);
	/// ���ꂼ��̐��l�ŏ������B
	Padding(int left, int top, int right, int bottom);

public:
	/// ���������̗]���̍��v�B
	int horizontal() const;
	/// �]���̍��v�̑傫���B
	Size size() const;
	/// ���������̗]���̍��v�B
	int vertical() const;

public:
	Padding& operator += (const Padding& rhs);
	friend Padding operator + (const Padding& lhs, const Padding& rhs);
	Padding& operator -= (const Padding& rhs);
	friend Padding operator - (const Padding& lhs, const Padding& rhs);
	bool operator == (const Padding& rhs) const;
	bool operator != (const Padding& rhs) const;

public:
	int left; // ���̗]��
	int top; // ��̗]��
	int right; // �E�̗]��
	int bottom; // ���̗]��
};



	}
}