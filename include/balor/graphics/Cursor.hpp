#pragma once

#include <balor/ArrayRange.hpp>
#include <balor/Exception.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/StringRange.hpp>

struct HBITMAP__;
struct HICON__;

namespace balor {
	namespace io {
		class Stream;
	}
	class Point;
	class Size;
}


namespace balor {
	namespace graphics {

class Bitmap;
class Color;



/**
 * �J�[�\���̉摜��\���B
 */
class Cursor : private NonCopyable {
public:
	typedef ::HBITMAP__* HBITMAP;
	typedef ::HICON__* HCURSOR;
	typedef ::balor::io::Stream Stream;

	/// �t�@�C����������Ȃ������B
	class NotFoundException : public Exception {};

	/// ���[�h�Ɏ��s�����B
	class LoadFailedException : public Exception {};

public:
	/// �k���n���h���ō쐬�B
	Cursor();
	Cursor(Cursor&& value);
	/// �n���h������쐬�Bowned �� true �Ȃ�΃f�X�g���N�^�Ńn���h����j������B
	explicit Cursor(HCURSOR handle, bool owned = false);
	/// �摜�ƃ}�X�N�摜�ƃz�b�g�X�|�b�g����쐬�B�}�X�N�摜�̓��m�N���r�b�g�}�b�v�Ŕ��������𓧉߂���B
	/// bitmap �� 32 �r�b�g�摜�ł��P�h�b�g�ł��O�ł͂Ȃ��A���t�@�����Ȃ�}�X�N�摜�𖳎����ăA���t�@�`�����l���œ��߂���B
	Cursor(HBITMAP bitmap, HBITMAP mask, int xHotSpot, int yHotSpot);
	/// �摜�ƃJ���[�L�[�ƃz�b�g�X�|�b�g����쐬�B�J���[�L�[�̐F�̕����𓧉߂���B
	/// bitmap �� 32 �r�b�g�摜�ł��P�h�b�g�ł��O�ł͂Ȃ��A���t�@�����Ȃ�J���[�L�[�𖳎����ăA���t�@�`�����l���œ��߂���B
	Cursor(HBITMAP bitmap, const Color& colorKey, int xHotSpot, int yHotSpot);
	/// �t�@�C������쐬�B.cur�A .ani �t�@�C���ɑΉ��B
	explicit Cursor(StringRange filePath);
	~Cursor();
	Cursor& operator=(Cursor&& value);

public:
	/// �J�[�\���̉摜�B
	Bitmap bitmap() const;
	/// ������Ԃ��B
	Cursor clone() const;
	static Cursor clone(HCURSOR handle);
	/// �W���̃T�C�Y�B
	static Size defaultSize();
	/// �J�[�\�����|�C���g����_�B�摜�̍�������_�Ƃ���s�N�Z���ʒu�B
	Point hotSpot();
	/// �J�[�\���̔w�i�𓧉߂��郂�m�N���r�b�g�}�b�v�B���������𓧉߂���B
	Bitmap mask() const;
	/// �f�X�g���N�^�Ńn���h����j�����邩�ǂ����B�ύX�͗v���ӁB
	bool owned() const;
	void owned(bool value);
	/// �X�g���[���ɕۑ�����B
	void save(Stream&& stream) const;
	void save(Stream& stream) const;
	/// �t�@�C���ɕۑ�����B
	void save(StringRange filePath) const;
	/// �����̃J�[�\������̃t�@�C���ɂ܂Ƃ߂ăX�g���[���ɕۑ�����B
	static void save(ArrayRange<const Cursor> cursors, Stream&& stream);
	static void save(ArrayRange<const Cursor> cursors, Stream& stream);
	/// �����̃J�[�\������̃t�@�C���ɂ܂Ƃ߂ăt�@�C���ɕۑ�����B
	static void save(ArrayRange<const Cursor> cursors, StringRange filePath);
	/// �J�[�\���̑傫���B
	Size size();

public: // �V�X�e���J�[�\���ꗗ�B
	/// ���J�[�\���ƍ����v�B
	static Cursor appStarting();
	/// ���J�[�\���B
	static Cursor default();
	/// �\���J�[�\���B
	static Cursor cross();
	/// �n���h�J�[�\���B
	static Cursor hand();
	/// ���J�[�\���Ƌ^�╄�B
	static Cursor help();
	/// �c���J�[�\���B
	static Cursor iBeam();
	/// �֎~�J�[�\���B
	static Cursor no();
	/// �S�����̖��J�[�\���B
	static Cursor sizeAll();
	/// �E��ƍ��������̖��J�[�\���B
	static Cursor sizeNESW();
	/// �㉺�����̖��J�[�\���B
	static Cursor sizeNS();
	/// ����ƉE�������̖��J�[�\���B
	static Cursor sizeNWSE();
	/// ���E�����̖��J�[�\���B
	static Cursor sizeWE();
	/// ������̖��J�[�\���B
	static Cursor upAllow();
	/// �����v�J�[�\���B
	static Cursor wait();

public:
	/// HCURSOR �ւ̎����ϊ� �� null �`�F�b�N�p
	operator HCURSOR() const { return _handle; }

private:
	HCURSOR _handle;
	bool _owned;
};



	}
}