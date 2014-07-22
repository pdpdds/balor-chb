#pragma once

#include <balor/ArrayRange.hpp>
#include <balor/Exception.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/Size.hpp>
#include <balor/StringRange.hpp>

struct HBITMAP__;
struct HICON__;

namespace balor {
	namespace io {
		class Stream;
	}
}


namespace balor {
	namespace graphics {

class Bitmap;
class Color;



/**
 * �A�C�R����\���B
 *
 * TODO: �A�C�R���̃X�g���[���ǂݍ��݁B
 * TODO: �V�X�e���A�C�R���͂ǂ�ȃT�C�Y���w�肵�Ă��W���T�C�Y�ɂȂ��Ă��܂��B
 */
class Icon : private NonCopyable {
public:
	typedef ::HBITMAP__* HBITMAP;
	typedef ::HICON__* HICON;
	typedef ::balor::io::Stream Stream;

	/// �t�@�C����������Ȃ������B
	class NotFoundException : public Exception {};

	/// ���[�h�Ɏ��s�����B
	class LoadFailedException : public Exception {};

public:
	/// �k���n���h���ō쐬�B
	Icon();
	Icon(Icon&& value);
	/// �n���h������쐬�Bowned �� true �Ȃ�΃f�X�g���N�^�Ńn���h����j������B
	explicit Icon(HICON handle, bool owned = false);
	/// �摜�ƃ}�X�N�摜����쐬�B�}�X�N�摜�̓��m�N���r�b�g�}�b�v�Ŕ��������𓧉߂���B�쐬��A�摜�n���h���͎Q�Ƃ���Ȃ��B
	/// bitmap �� 32 �r�b�g�摜�ł��P�h�b�g�ł��O�ł͂Ȃ��A���t�@�����Ȃ�}�X�N�摜�𖳎����ăA���t�@�`�����l���œ��߂���B
	Icon(HBITMAP bitmap, HBITMAP mask);
	/// �摜�ƃJ���[�L�[����쐬�B�J���[�L�[�̐F�̕����𓧉߂���B�쐬��A�摜�n���h���͎Q�Ƃ���Ȃ��B
	/// bitmap �� 32 �r�b�g�摜�ł��P�h�b�g�ł��O�ł͂Ȃ��A���t�@�����Ȃ�J���[�L�[�𖳎����ăA���t�@�`�����l���œ��߂���B
	Icon(HBITMAP bitmap, const Color& colorKey);
	/// �X�g���[���ƃT�C�Y���w�肵�č쐬�Bsize �� Size(0, 0) ���w�肷��ƍŏ��Ɍ��������A�C�R���̌����ō쐬�����B
	/*explicit Icon(Stream&& stream, const Size& size = Icon::largeSize());
	explicit Icon(Stream& stream, const Size& size = Icon::largeSize());
	Icon(Stream&& stream, int width, int height);
	Icon(Stream& stream, int width, int height); *//**/
	/// �t�@�C�����ƃT�C�Y���w�肵�č쐬�Bsize �� Size(0, 0) ���w�肷��ƍŏ��Ɍ��������A�C�R���̌����ō쐬�����B
	explicit Icon(StringRange filePath, const Size& size = Icon::largeSize());
	Icon(StringRange filePath, int width, int height);
	~Icon();

	Icon& operator=(Icon&& value);

public:
	/// �A�C�R���̉摜�B
	Bitmap bitmap() const;
	/// �A�C�R���̕�����Ԃ��B
	Icon clone() const;
	static Icon clone(HICON handle);
	/// �傫�ȃA�C�R���̕W���T�C�Y�B
	static Size largeSize();
	/// �A�C�R���̔w�i�𓧉߂��郂�m�N���r�b�g�}�b�v�B���������𓧉߂���B
	Bitmap mask() const;
	/// �f�X�g���N�^�Ńn���h����j�����邩�ǂ����B�ύX�͗v���ӁB
	bool owned() const;
	void owned(bool value);
	/// �X�g���[���ɕۑ�����B
	void save(Stream&& stream) const;
	void save(Stream& stream) const;
	/// �t�@�C���ɕۑ�����B
	void save(StringRange filePath) const;
	/// �����̃A�C�R������̃t�@�C���ɂ܂Ƃ߂ăX�g���[���ɕۑ�����B
	static void save(ArrayRange<const Icon> icons, Stream&& stream);
	static void save(ArrayRange<const Icon> icons, Stream& stream);
	/// �����̃A�C�R������̃t�@�C���ɂ܂Ƃ߂ăt�@�C���ɕۑ�����B
	static void save(ArrayRange<const Icon> icons, StringRange filePath);
	/// �A�C�R���̃T�C�Y�B
	Size size() const;
	/// �����ȃA�C�R���̕W���T�C�Y�B
	static Size smallSize();

public: // �V�X�e���A�C�R���ꗗ�B
	/// �A�v���P�[�V�����A�C�R���B
	static Icon application(const Size& size = Icon::largeSize());
	/// �A�X�^���X�N�A�C�R���B
	static Icon asterisk(const Size& size = Icon::largeSize());
	/// �G���[�A�C�R���B
	static Icon error(const Size& size = Icon::largeSize());
	/// ���Q���A�C�R���B
	static Icon exclamation(const Size& size = Icon::largeSize());
	/// ��̌`�̃A�C�R���B
	static Icon hand(const Size& size = Icon::largeSize());
	/// ���A�C�R���B
	static Icon information(const Size& size = Icon::largeSize());
	/// �^�╄�A�C�R���B
	static Icon question(const Size& size = Icon::largeSize());
	/// �x���A�C�R���B
	static Icon warning(const Size& size = Icon::largeSize());
	/// Windos ���S�A�C�R���B
	static Icon windowsLogo(const Size& size = Icon::largeSize());

public:
	/// HICON �ւ̎����ϊ� �� null �`�F�b�N�p
	operator HICON() const { return _handle; }

private:
	HICON _handle;
	bool _owned;
};



	}
}