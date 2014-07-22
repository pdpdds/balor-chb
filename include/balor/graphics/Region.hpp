#pragma once

#include <balor/ArrayRange.hpp>
#include <balor/Enum.hpp>
#include <balor/NonCopyable.hpp>

struct HRGN__;
struct HWND__;

namespace balor {
class Point;
class Rectangle;
class Size;
}


namespace balor {
	namespace graphics {

class GraphicsPath;



/**
 * GDI ���[�W������\���B
 *
 * ���[�W�����̃n���h�����k���̏ꍇ�͖�����̗̈��\���BGraphics �� �E�C���h�E�Ƀ��[�W�������ݒ肳��Ă��Ȃ��ꍇ�̓k���n���h����Ԃ��̂ł��̂ق����s�����ǂ��B
 * from�` �֐��ɂ���č쐬���ꂽ�̈�� Graphics::fill�` �֐��Ɣ͈͂����S�Ɉ�v����B
 * ��� GraphicsPath ����Đ}�`��������ꍇ�� Graphics �̂ǂ̐}�`�`��֐��Ƃ����ʂ���v���Ȃ��̂Œ��ӂ��邱�ƁB
 */
class Region : private NonCopyable {
public:
	typedef ::HRGN__* HRGN;
	typedef ::HWND__* HWND;

	/// ���[�W�����̍������Z�q�B
	struct Operation {
		enum _enum {
			and  = 1, /// AND �����B��̗̈�̋��ʕ����B
			or   = 2, /// OR �����B��̗̈�����킹�������B
			xor  = 3, /// XOR �����B��̗̈�����킹���������狤�ʕ����������������B
			diff = 4, /// ���ӗ̈悩��E�ӗ̈����菜���������B
		};
		BALOR_NAMED_ENUM_MEMBERS(Operation);
	};

public:
	/// ������̗̈�Ƃ��č쐬�B
	Region();
	Region(Region&& value);
	/// �n���h������쐬�Bowned �� true �Ȃ�΃f�X�g���N�^�Ńn���h����j������B
	explicit Region(HRGN handle, bool owned = false);
	/// �����`�̈悩��쐬�B
	explicit Region(const Rectangle& rect);
	Region(int x, int y, int width, int height);
	~Region();
	Region& operator=(Region&& value);

public:
	/// �̈�S�̂��܂ޒ����`�B
	Rectangle bounds() const;
	/// �������ĕԂ��B
	Region clone() const;
	static Region clone(HRGN handle);
	/// ��̗̈���w�肵�����Z�ō�������B���[�W�����̃n���h�����k���̏ꍇ�͖����̍L���̗̈�Ƃ��Ĉ�����B
	void combine(HRGN rhs, Region::Operation op);
	static Region combine(HRGN lhs, HRGN rhs, Region::Operation op);
	/// �̈�̖ʐς��O���ǂ����B�n���h�����k�����ǂ����ł͂Ȃ����Ƃɒ��ӁB
	bool empty() const;
	/// �̈悪���������ǂ����Boperator == �� operator HRGN() �ɂ���ăn���h���̔�r�ɂȂ�̂Œ��ӂ��邱�ƁB
	bool equals(HRGN rhs) const;
	/// �~�̗̈���쐬�B
	static Region fromCircle(const Point& point, int radius);
	static Region fromCircle(int x, int y, int radius);
	/// �ȉ~�̗̈���쐬�B
	static Region fromEllipse(const Rectangle& rect);
	static Region fromEllipse(int x, int y, int width, int height);
	/// GraphicsPath �Ɉ͂܂ꂽ�̈���쐬�B
	static Region fromGraphicsPath(const GraphicsPath& path);
	/// ���p�`�̗̈���쐬�Balternate �����͓h��Ԃ����[�h�� ALTERNATE ���ǂ�����\���Bfalse �̏ꍇ�� WINDING �ƂȂ�B
	static Region fromPolygon(ArrayRange<const Point> points, bool alternate = true);
	/// �����`�̗̈���쐬�B
	static Region fromRectangle(const Rectangle& rect);
	static Region fromRectangle(int x, int y, int width, int height);
	/// �p�̊ۂ������`�̗̈���쐬�B
	static Region fromRoundRectangle(const Rectangle& rect, const Size& ellipseSize);
	static Region fromRoundRectangle(int x, int y, int width, int height, int ellipseWidth, int ellipseHeight);
	/// �̈�̖ʐς��ɑ傩�ǂ����B�n���h�����k���̏ꍇ�� true�B
	bool infinite() const;
	/// �_���̈�Ɋ܂܂�邩�ǂ����B
	bool isVisible(const Point& point) const;
	bool isVisible(int x, int y) const;
	/// �����`�S�̂��̈�Ɋ܂܂�邩�ǂ����B
	bool isVisible(const Rectangle& rect) const;
	bool isVisible(int x, int y, int width, int height) const;
	/// �̈�̖ʐς��O�ɂ���B
	void makeEmpty();
	/// �̈�̖ʐς��ɑ�ɂ���B
	void makeInfinite();
	/// �f�X�g���N�^�Ńn���h����j�����邩�ǂ����B�ύX�͗v���ӁB
	bool owned() const;
	void owned(bool value);
	/// �̈�𕽍s�ړ�����B
	void translate(int dx, int dy);

public:
	/// HRGN �ւ̎����ϊ� �� null �`�F�b�N�p
	operator HRGN() const { return _handle; }

private:
	HRGN _handle;
	bool _owned;
};



	}
}