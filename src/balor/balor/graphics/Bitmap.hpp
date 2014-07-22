#pragma once

#include <balor/ArrayRange.hpp>
#include <balor/Enum.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/OutOfMemoryException.hpp>
#include <balor/StringRange.hpp>

struct HBITMAP__;

namespace std {
template<typename T> class allocator;
template<typename T, typename A> class vector;
}

namespace balor {
	namespace io {
		class Stream;
	}
	class Point;
	class Rectangle;
	class Size;
}


namespace balor {
	namespace graphics {

class Color;



/**
 * GDI �r�b�g�}�b�v��\���B
 * 
 * �摜�̃R�s�[�ɂ� Graphics::copy �֐����A�F�̎擾�ɂ� Graphics::getPixel �֐����g�p�ł���B���邢�� pixels �֐��Ŏ��͂ŏ�������B
 * �t�@�C����X�g���[���ւ̓��o�͂ɂ� GDI+ ���g�p���Abmp, gif, jpeg, png, tiff �̃t�@�C���`���y�уA���t�@�`�����l���t���摜�`�����T�|�[�g����B
 * �R���X�g���N�^�ō쐬�����ꍇ�͏�� DIB �r�b�g�}�b�v���쐬����BDDB �r�b�g�}�b�v���쐬����ɂ� createDDB �܂��� toDDB �֐����g�p����B
 * DDB�͈��ȏ�̑傫���i�Ⴆ��4096 * 4096�j�ō쐬������A���ʈȏ�̗e�ʁi���������C���������ɂ͏\������j�𒴂����
 * OutOfMemoryException �𔭐�������B����͎�Ƀr�f�I�J�[�h�̐����ɂ��B�p���b�g���g�p���� DDB �̓T�|�[�g���Ȃ��B
 * ������ HBITMAP ��n���֐��� bottomUp, palette, save �֐����� HBITMAP �� Bitmap �� Graphics �N���X�ɎQ�Ƃ��ꂽ�܂܂��Ɗ֐������s����̂Œ��ӂ��邱�ƁB
 * 
 * �� DDB �Ƃ̓f�B�X�v���C�Ɠ����s�N�Z���t�H�[�}�b�g�������A�����ɉ�ʂɕ`�悪�ł��邪���e�̃������|�C���^�������Ȃ��r�b�g�}�b�v�ŁA
 *    DIB �̓I���W�i���̃t�H�[�}�b�g�����Ă锽�ʁA��ʂɕ`����s���Ɠ����ł͕ϊ����������邽�߂Ƀp�t�H�[�}���X���ቺ���鋰�ꂪ����r�b�g�}�b�v�B
 */
class Bitmap : private NonCopyable {
public:
	typedef ::HBITMAP__* HBITMAP;
	typedef ::balor::io::Stream Stream;


	/// ������������Ȃ������B
	struct OutOfMemoryException : public ::balor::OutOfMemoryException {};

	/// �t�@�C���t�H�[�}�b�g���s���B
	class FileFormatException : public Exception {};


	/// �t�@�C���ɕۑ�����`���BGDI+ �ŃT�|�[�g�����`���̂݁B
	struct FileFormat {
		enum _enum {
			bmp , /// �r�b�g�}�b�v�摜�t�@�C���`���B
			gif , /// GIF�摜�t�@�C���`���B
			jpeg, /// jpeg�摜�t�@�C���`���B
			png , /// PNG�摜�t�@�C���`���B
			tiff, /// TIFF�摜�t�@�C���`���B
		};
		BALOR_NAMED_ENUM_MEMBERS(FileFormat);
	};


	/// �r�b�g�}�b�v�̌`���B
	struct Format {
		Format();
		/// �P�s�N�Z��������̃r�b�g���� RGB �̃r�b�g�}�X�N����쐬�B
		explicit Format(int bitsPerPixel, int rMask = 0, int gMask = 0, int bMask = 0, int aMask = 0);

		/// ���m�N���p���b�g�r�b�g�}�b�v�B
		static const Format palette1bpp;
		/// �P�U�F�p���b�g�r�b�g�}�b�v�B
		static const Format palette4bpp;
		/// �Q�T�U�F�p���b�g�r�b�g�}�b�v�B
		static const Format palette8bpp;
		/// Format(16, 0x7C00, 0x03E0, 0x001F) �ł���P�U�r�b�g�摜�B
		static const Format rgb16bpp;
		/// Format(16, 0xF800, 0x07E0, 0x001F) �ł���P�U�r�b�g�摜�B
		static const Format rgb16bpp565;
		/// �o�C�g�z��̕��т� B, G, R �ł���Q�S�r�b�g�摜�B
		static const Format rgb24bpp;
		/// Format(32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000) �ł���R�Q�r�b�g�摜�B
		static const Format argb32bpp;

		bool operator==(const Format& value) const;
		bool operator!=(const Format& value) const;

		/// �P�s�N�Z��������̃r�b�g���B
		int bitsPerPixel;
		/// �P�s�N�Z���ŐԂ̐�߂�r�b�g�}�X�N�BbitsPerPixel �� 16 �܂��� 32 �̏ꍇ�̂ݗL���A����ȊO�ł� 0�B
		int rMask;
		/// �P�s�N�Z���ŗ΂̐�߂�r�b�g�}�X�N�BbitsPerPixel �� 16 �܂��� 32 �̏ꍇ�̂ݗL���A����ȊO�ł� 0�B
		int gMask;
		/// �P�s�N�Z���Ő̐�߂�r�b�g�}�X�N�BbitsPerPixel �� 16 �܂��� 32 �̏ꍇ�̂ݗL���A����ȊO�ł� 0�B
		int bMask;
		/// �P�s�N�Z���ŃA���t�@�`�����l���̐�߂�r�b�g�}�X�N�BbitsPerPixel �� 32 �̏ꍇ�̂ݗL���A����ȊO�ł� 0�B
		int aMask;
	};


public:
	/// �k���n���h���ō쐬�B
	Bitmap();
	Bitmap(Bitmap&& value);
	/// �n���h������쐬�Bowned �� true �Ȃ�΃f�X�g���N�^�Ńn���h����j������B
	explicit Bitmap(HBITMAP handle, bool owned = false);
	/// �X�g���[������쐬�B
	explicit Bitmap(Stream& stream, bool bottomUp = true, bool useIcm = false);
	explicit Bitmap(Stream&& stream, bool bottomUp = true, bool useIcm = false);
	/// �t�@�C������ǂݍ���ō쐬�B
	explicit Bitmap(StringRange filePath, bool bottomUp = true, bool useIcm = false);
	/// �r�b�g�}�b�v�̑傫���A�t�H�[�}�b�g�ύX���č쐬�B
	Bitmap(HBITMAP bitmap, const Size& size, Bitmap::Format format, bool bottomUp = true);
	Bitmap(HBITMAP bitmap, int width, int height, Bitmap::Format format, bool bottomUp = true);
	/// �傫���ƃt�H�[�}�b�g�A�s�N�Z���̃������f�[�^����쐬�BsrcStride �� srcPixels �̂P���C��������̃o�C�g���B
	explicit Bitmap(const Size& size, Bitmap::Format format = Format::argb32bpp, bool bottomUp = true, const void* srcPixels = nullptr, int srcStride = 0, bool srcBottomUp = true);
	Bitmap(int width, int height, Bitmap::Format format = Format::argb32bpp, bool bottomUp = true, const void* srcPixels = nullptr, int srcStride = 0, bool srcBottomUp = true);
	~Bitmap();
	Bitmap& operator=(Bitmap&& value);

public:
	/// �P�s�N�Z��������̃r�b�g���B
	int bitsPerPixel() const;
	/// �s�N�Z���f�[�^����������n�܂邩�ǂ����BDDB �̏ꍇ�͏�� true ��Ԃ��B
	bool bottomUp() const;
	/// DIB �Ȃ�� DIB�ADDB �Ȃ�� DDB �̂܂ܕ������ĕԂ��B
	Bitmap clone() const;
	static Bitmap clone(HBITMAP handle);
	/// DDB �r�b�g�}�b�v���쐬����
	static Bitmap createDDB(const Size& size);
	static Bitmap createDDB(int width, int height);
	/// �t�H�[�}�b�g�ƃs�N�Z���f�[�^����v���邩�ǂ�����Ԃ��B�t�H�[�}�b�g�����܂��ܓ����ł������Ƃ��Ă��ADDB �� DIB �̔�r�͏��false��Ԃ��B
	bool equalsBits(const Bitmap& rhs, bool exceptAlpha = false) const;
	static bool equalsBits(const Bitmap& lhs, const Bitmap& rhs, bool exceptAlpha = false);
	/// �r�b�g�}�b�v�̌`���B�A���t�@�}�X�N���擾�����i�������̂� DIB �̂R�Q�r�b�g�摜�͑S�ăA���t�@�}�X�N�t���Ƃ݂Ȃ����Ƃɒ��ӁB
	Bitmap::Format format() const;
	/// �摜�̍����B
	int height() const;
	/// DDB ���ǂ����B
	bool isDDB() const;
	/// �f�X�g���N�^�Ńn���h����j�����邩�ǂ����B�ύX�͗v���ӁB
	bool owned() const;
	void owned(bool value);
	/// �p���b�g�B�p���b�g�`���̃r�b�g�}�b�v�łȂ���Α���ł��Ȃ��B
	std::vector<Color, std::allocator<Color> > palette() const;
	void palette(ArrayRange<const Color> value);
	/// �s�N�Z���f�[�^�ւ̃|�C���^�B�������z�u�� bottomUp �֐��ŁA�P���C���̃o�C�g���� stride �֐��Œ��ׂ���BisDDB() �� true �̏ꍇ�� nullptr ��Ԃ��B
	/// GDI �̔񓯊��`��Ƃ̏Փ˂�����邽�߂Ƀ������ɃA�N�Z�X����O�� Graphics::flush �֐������s�����ق����悢�B
	unsigned char* pixels();
	const unsigned char* pixels() const;
	/// �A���t�@�`�����l����S�Ẵs�N�Z���ɏ�Z����BDIB �� 32�r�b�g�摜�̏ꍇ�̂ݗL���B
	/// Graphics::blend �֐��ŃA���t�@�`�����l�����g���ꍇ�͂��炩���߂��̊֐����Ă�ł����K�v������B
	void premultiplyAlpha();
	/// �X�g���[���ɕۑ�����Bquality �� jpeg �`���ŕۑ�����ꍇ�̕i���� 0 �` 100 �Őݒ肷��B
	void save(Stream& stream, Bitmap::FileFormat format, int quality = 75) const;
	void save(Stream&& stream, Bitmap::FileFormat format, int quality = 75) const;
	/// �t�@�C���ɕۑ�����B�t�@�C���`���͊g���q���画�ʂ���B���ʂł��Ȃ������ꍇ�� png �`���ŕۑ������Bquality �� jpeg �`���̕i���� 0 �` 100 �Őݒ肷��B
	void save(StringRange filePath, int quality = 75) const;
	/// �t�@�C���ɕۑ�����Bquality �� jpeg �`���̕i���� 0 �` 100 �Őݒ肷��B
	void save(StringRange filePath, Bitmap::FileFormat format, int quality = 75) const;
	/// �摜�̃T�C�Y�B
	Size size() const;
	/// �s�N�Z���f�[�^�̂P���C�������o�C�g���B
	int stride() const;
	/// DDB �r�b�g�}�b�v�Ƃ��ĕ�������B
	Bitmap toDDB() const;
	static Bitmap toDDB(HBITMAP handle);
	/// DIB �r�b�g�}�b�v�Ƃ��ĕ�������B
	Bitmap toDIB(bool bottomUp = true) const;
	static Bitmap toDIB(HBITMAP handle, bool bottomUp = true);
	/// �摜�̕��B
	int width() const;

public:
	/// HBITMAP �ւ̎����ϊ� �� null �`�F�b�N�p
	operator HBITMAP() const { return _handle; }

private:
	HBITMAP _handle;
	bool _owned;
};



	}
}