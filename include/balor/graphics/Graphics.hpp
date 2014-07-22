#pragma once

#include <balor/graphics/ImageList.hpp>
#include <balor/graphics/Region.hpp>
#include <balor/ArrayRange.hpp>
#include <balor/Enum.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/StringRange.hpp>

struct _IMAGELIST;
struct HBITMAP__;
struct HBRUSH__;
struct HDC__;
struct HFONT__;
struct HICON__;
struct HPEN__;
struct HRGN__;
struct HWND__;

namespace balor {
class Point;
class Rectangle;
class Size;
}


namespace balor {
	namespace graphics {

class Brush;
class Color;
class Font;
class GraphicsPath;
class Pen;



/**
 * GDI �ɂ��`�揈���������B
 * 
 * �}�`��h��Ԃ������ɗ֊s�����`�������ꍇ�� brush() �� Brush::hollow() ��ݒ肷��B
 * �}�`��h��Ԃ������������ꍇ�� pen() �� Pen::hollow() ��ݒ肷��B���̏ꍇ�}�`�̉E�������͕`�悳��Ȃ��B
 * drawText �֐����g���ꍇ�� backTransparent() �ɒ��ӂ���B
 * �r�b�g�}�b�v��`�悷��ɂ� Bitmap ���� Graphics ���쐬���� copy �֐����g���B
 * �g��k���𔺂��� copy �֐����g���ꍇ�� copyMode() �ɒ��ӂ���B
 * �������`���A�A���t�@�`�����l���ɂ�锼��������������ɂ� Bitmap::premultiplyAlpha �֐��� blend �֐����g���B
 * �J���[�L�[�ɂ��F����������ɂ� ImageList �� drawImageList �֐����g��
 * �ݒ��ύX����֐��ł͋��ݒ��Ԃ��悤�ɂȂ��Ă���B�ݒ���܂Ƃ߂ĕۑ��A��������ɂ� state �֐����g���B
 */
class Graphics : private NonCopyable {
public:
	typedef ::_IMAGELIST* HIMAGELIST;
	typedef ::HBITMAP__* HBITMAP;
	typedef ::HBRUSH__* HBRUSH;
	typedef ::HDC__* HDC;
	typedef ::HFONT__* HFONT;
	typedef ::HICON__* HICON;
	typedef ::HPEN__* HPEN;
	typedef ::HRGN__* HRGN;
	typedef ::HWND__* HWND;


	/// �R�s�[�������[�h�B
	struct CopyMode {
		enum _enum {
			andScans    = 1, /// �k���ŏ�����s�N�Z�����c�����s�N�Z���� AND ���Z����B
			orScans     = 2, /// �k���ŏ�����s�N�Z�����c�����s�N�Z���� OR ���Z����B
			deleteScans = 3, /// �k���ŏ�����s�N�Z�������̂܂܏����B
			halftone    = 4, /// �k���ŏ�����s�N�Z�����c�����s�N�Z���ƍ��F����B
		};
		BALOR_NAMED_ENUM_MEMBERS(CopyMode);
	};

	/// �R�s�[�̉��Z���@�B�g�ݍ��킹�Ŏw�肷��B
	struct CopyOperation {
		enum _enum {
			captureBlt        = 0x40000000, /// �R�s�[�����������ȃE�C���h�E�ł����Ă��s�N�Z�����R�s�[����B
			destinationInvert = 0x00550009, /// �R�s�[��̐F�𔽓]����B
			mergeCopy         = 0x00C000CA, /// �R�s�[���ƃR�s�[��̃u���V�� AND ���Z����B
			mergePaint        = 0x00BB0226, /// �R�s�[���̐F�𔽓]���ăR�s�[��� OR ���Z����B
			notSourceCopy     = 0x00330008, /// �R�s�[���̐F�𔽓]���ăR�s�[����B
			notSourceErase    = 0x001100A6, /// �R�s�[���ƃR�s�[��� OR ���Z�����㔽�]����B
			patCopy           = 0x00F00021, /// �R�s�[��̃u���V�œh��B
			patInvert         = 0x005A0049, /// �R�s�[��̃u���V�ƃR�s�[��� XOR ���Z����B
			patPaint          = 0x00FB0A09, /// �R�s�[���𔽓]�����F�ƃR�s�[��̃u���V�� OR ���Z���A���ʂƃR�s�[��� OR ���Z����B
			sourceAnd         = 0x008800C6, /// �R�s�[���ƃR�s�[��� AND ���Z����B
			sourceCopy        = 0x00CC0020, /// �R�s�[�����R�s�[����B
			sourceErase       = 0x00440328, /// �R�s�[���ƃR�s�[��𔽓]�����F�� AND ���Z����B
			sourceInvert      = 0x00660046, /// �R�s�[���ƃR�s�[��� XOR ���Z����B
			sourcePaint       = 0x00EE0086, /// �R�s�[���ƃR�s�[��� OR ���Z����B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(CopyOperation);
	};

	/// ������`��̃t���O�B�g�ݍ��킹�Ŏw�肷��B
	struct TextFormat {
		enum _enum {
			none                      = 0         , 
			bottom                    = 0x00000028, /// ��`�̉��[�ɕ�����𑵂���BsingleLine ���܂߂�B
			default                   = 0x00000810, /// noPrefix ���� wordBreak�B
			editControl               = 0x00002000, /// �����s�G�f�B�b�g�R���g���[���Ɠ����悤�ɕ`�悷��B
			endEllipsis               = 0x00008000, /// ��������`����͂ݏo���ꍇ�Ɂu...�v��\������B
			expandTabs                = 0x00000040, /// �^�u��W�J����B
			externalLeading           = 0x00000200, /// �s�̍����ɁA�O�����f�B���O�̍�����ǉ�����B
			hidePrefix                = 0x00100000, /// L'&' �ɂ���ĉ�����\�����Ȃ��B
			horizontalCenter          = 0x00000001, /// ��`�̐��������̒����ɕ�����𑵂���B
			noClipping                = 0x00000100, /// ��`����͂ݏo�Ă��`�悷��B
			noFullWidthCharacterBreak = 0x00080000, /// ��̕����𕡐��̕����R�[�h�̘A���ŕ\�����ɓr���ŉ��s����Ȃ��悤�ɂ���B
			noPrefix                  = 0x00000800, /// L'&' ����ꕶ���Ƃ݂Ȃ��Ȃ��悤�ɂ���B
			pathEllipsis              = 0x00004000, /// �t�@�C���p�X��\�����؂�Ȃ��ꍇ�ɓK�؂ɒZ�k����B
			prefixOnly                = 0x00200000, /// L'&' �ɂ���ĕ\������鉺�������`�悷��B
			right                     = 0x00000002, /// ��`�̉E�[�ɕ�����𑵂���B
			rightToLeft               = 0x00020000, /// �t�H���g���w�u���C�ꂩ�A���r�A��̏ꍇ�ɉE���獶�ɕ�����`�悷��B
			singleLine                = 0x00000020, /// ���s�����ɕ`�悷��B
			verticalCenter            = 0x00000024, /// ��`�̐��������̒����ɕ�����𑵂���BsingleLine ���܂߂�B
			wordBreak                 = 0x00000010, /// �P��̓r���ŉ��s���Ȃ��悤�ɂ���B
			wordEllipsis              = 0x00040000, /// ��`����P��̓r���ł͂ݏo���ꍇ�Ɂu...�v��\������B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(TextFormat);
	};


	/// �y����u���V���̐ݒ��ۑ������I�u�W�F�N�g�B
	class State {
	public:
		State();
		State(HDC handle);

	public:
		HDC handle() const;
		int id() const;

	private:
		HDC _handle;
		int _id;
	};


public:
	/// �k���n���h���ō쐬�B
	Graphics();
	Graphics(Graphics&& value);
	/// �n���h������쐬�Bowned �� true �Ȃ�΃f�X�g���N�^�Ńn���h����j������B
	explicit Graphics(HDC handle, bool owned = false);
	/// �r�b�g�}�b�v�̃f�o�C�X���쐬�B�r�b�g�}�b�v���ɔj�����悤�Ƃ���Ǝ��s����̂ŁA�K�� Graphics �̂ق����ɔj�����邱�ƁB
	explicit Graphics(HBITMAP bitmap);
	/// �E�C���h�E�n���h������쐬�B
	explicit Graphics(HWND control);
	~Graphics();

	Graphics& operator=(Graphics&& value);

public:
	/// �w�i�F�B
	Color backColor() const;
	Color backColor(Color value);
	/// �e�L�X�g�A�n�b�`�u���V�A�y���ŕ`�悷�鎞�ɔw�i���u���V�œh��Ȃ����ǂ����B
	bool backTransparent() const;
	bool backTransparent(bool value) const;
	/// �������������s���Balpha �ɕs�����x�O�`�P���w�肷��BcopyMode() �̉e���͎󂯂��A��� Graphics::CopyMode::deleteScans �Ɠ��������ɂȂ�B
	/// src ���A���t�@�`�����l���������� 32�r�b�g�̃r�b�g�}�b�v�iDDB �ł��ǂ��j�ł���ꍇ�Ɍ���AsrcAlphaChannel ������ true �ɂ���ƃA���t�@�`�����l���ɂ�锼�����������s���B
	/// ���̏ꍇ src �̉摜�� Bitmap::premultiplyAlpha �֐��ł��炩���߃A���t�@����Z���Ă����K�v������B�܂� alpha �����������Ɏw��ł���B
	/// copy �֐��̂悤�Ȕ��]�R�s�[�̓T�|�[�g���ꂸ�A�\�[�X�͈̔͊O���R�s�[���悤�Ƃ���ƃG���[�ɂȂ�B
	void blend(const Point& dstPos, HDC src, float alpha, bool srcAlphaChannel = false);
	void blend(int dstX, int dstY, HDC src, float alpha, bool srcAlphaChannel = false);
	void blend(const Point& dstPos, HDC src, const Point& srcPos, const Size& size, float alpha, bool srcAlphaChannel = false);
	void blend(int dstX, int dstY, HDC src, int srcX, int srcY, int width, int height, float alpha, bool srcAlphaChannel = false);
	void blend(const Rectangle& dstRect, HDC src, float alpha, bool srcAlphaChannel = false);
	void blend(int dstX, int dstY, int dstWidth, int dstHeight, HDC src, float alpha, bool srcAlphaChannel = false);
	void blend(const Rectangle& dstRect, HDC src, const Rectangle& srcRect, float alpha, bool srcAlphaChannel = false);
	void blend(int dstX, int dstY, int dstWidth, int dstHeight, HDC src, int srcX, int srcY, int srcWidth, int srcHeight, float alpha, bool srcAlphaChannel = false);
	/// �}�`��h��Ԃ��u���V�B�F�𒼐ڐݒ�ł���B�h��Ȃ��ꍇ�� Brush::hollow() ��ݒ肷��B
	Brush brush() const;
	Brush brush(HBRUSH value);
	Brush brush(Color value);
	/// �u���V�̌��_�BcopyMode �� Graphics::CopyMode::halftone �ɐݒ肵���ꍇ�͍Đݒ肷��K�v������B
	Point brushOrigin() const;
	Point brushOrigin(const Point& value);
	/// ���݂̃u���V�őS�̂�h��Ԃ��B
	void clear();
	/// �N���b�v�̈�B
	Region clip() const;;
	void clip(HRGN region);
	/// �N���b�v�̈����������B
	void combineClip(HRGN region, Region::Operation operation);
	void combineClip(const Rectangle rect, Region::Operation operation);
	/// �s�N�Z���̃R�s�[���s���B�傫���ɕ������w�肷��Ɣ��]�R�s�[�ɂȂ�B
	/// �k����g��R�s�[����ꍇ�AcopyMode �� Graphics::CopyMode::halftone �ɂ��Ă����Ȃ��ƂƂĂ������Ȃ�B������ Graphics::CopyMode::halftone ���ƃA���t�@�`�����l����񂪂��������Ȃ�B
	/// �Y��ɂ���K�v�������Ă����Ȃ��Ƃ� Graphics::CopyMode::deleteScans �ɂ��Ă����Ȃ��Ǝv�����悤�Ȍ��ʂɂ͂Ȃ�Ȃ��B
	void copy(const Point& dstPos, HDC src, Graphics::CopyOperation operation = CopyOperation::sourceCopy);
	void copy(int dstX, int dstY, HDC src, Graphics::CopyOperation operation = CopyOperation::sourceCopy);
	void copy(const Point& dstPos, HDC src, const Point& srcPos, const Size& size, Graphics::CopyOperation operation = CopyOperation::sourceCopy);
	void copy(int dstX, int dstY, HDC src, int srcX, int srcY, int width, int height, Graphics::CopyOperation operation = CopyOperation::sourceCopy);
	void copy(const Rectangle& dstRect, HDC src, Graphics::CopyOperation operation = CopyOperation::sourceCopy);
	void copy(int dstX, int dstY, int dstWidth, int dstHeight, HDC src, Graphics::CopyOperation operation = CopyOperation::sourceCopy);
	void copy(const Rectangle& dstRect, HDC src, const Rectangle& srcRect, Graphics::CopyOperation operation = CopyOperation::sourceCopy);
	void copy(int dstX, int dstY, int dstWidth, int dstHeight, HDC src, int srcX, int srcY, int srcWidth, int srcHeight, Graphics::CopyOperation operation = CopyOperation::sourceCopy);
	/// �R�s�[�����̃��[�h�BGraphics::CopyMode::halftone �ɐݒ肵���ꍇ�� brushOrigin ���Đݒ肷��K�v������B
	Graphics::CopyMode copyMode() const;
	Graphics::CopyMode copyMode(Graphics::CopyMode value);
	/// �����̃h�b�g���x�B
	int dpiX() const;
	/// �����̃h�b�g���x�B
	int dpiY() const;
	/// �~�ʂ�`���B�p�x�� 0 �` 360 �Ŕ����v����B
	void drawArc(const Rectangle& rect, float startAngle, float sweepAngle);
	void drawArc(int x, int y, int width, int height, float startAngle, float sweepAngle);
	/// �_ p0 ���� �_ p3 �Ƀx�W�F�Ȑ���`���B
	void drawBezier(const Point& p0, const Point& p1, const Point& p2, const Point& p3);
	void drawBezier(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
	/// �A�������x�W�F�Ȑ���`���B�S�_�w��ŘA������n�_�ƏI�_�����ʉ������_�̔z��ŁA�R�Ŋ���ƂP�]�钷���łȂ���΂Ȃ�Ȃ��B
	void drawBeziers(ArrayRange<const Point> points);
	/// �~��`���B
	void drawCircle(const Point& point, int radius);
	void drawCircle(int x, int y, int radius);
	/// �ȉ~��`���B
	void drawEllipse(const Rectangle& rect);
	void drawEllipse(int x, int y, int width, int height);
	/// �A�C�R����`���Bmasked �� false �ɂ���Ɣw�i�𓧉߂��Ȃ��B
	void drawIcon(HICON icon, const Point& point, bool masked = true);
	void drawIcon(HICON icon, int x, int y, bool masked = true);
	void drawIcon(HICON icon, const Rectangle& rect, bool masked = true);
	void drawIcon(HICON icon, int x, int y, int width, int height, bool masked = true);
	/// �C���[�W���X�g�̒��̉摜��`���B�傫�����O�ɂ���ƌ����ŕ`�悷��Balpha �� 1 �����̏ꍇ�͔�������������B�������O���C�X�P�[���Ɠ����ɂ͗L���ɂȂ�Ȃ��B
	void drawImageList(HIMAGELIST imageList, int index, const Rectangle& rect, ImageList::State state = ImageList::State::normal, float alpha = 1.0f, bool grayscale = false);
	void drawImageList(HIMAGELIST imageList, int index, int x, int y, int width = 0, int height = 0, ImageList::State state = ImageList::State::normal, float alpha = 1.0f, bool grayscale = false);
	/// ������`���B�I�_�̃s�N�Z���͕`����Ȃ��B
	void drawLine(const Point& p0, const Point& p1);
	void drawLine(int x0, int y0, int x1, int y1);
	/// ������A���ŕ`���B
	void drawLines(ArrayRange<const Point> points);
	/// GraphicsPath �ŕ`���ꂽ����`���B�y���Ő��̂ݕ`���B�u���V�œh��ꍇ�� fillPath �֐����g���B
	void drawPath(GraphicsPath& path);
	/// ��^��`���B�p�x�� 0 �` 360 �Ŕ����v����B
	void drawPie(const Rectangle& rect, float startAngle, float sweepAngle);
	void drawPie(int x, int y, int width, int height, float startAngle, float sweepAngle);
	/// ���p�`��`���B�h��Ԃ����@�� fillAlternate �֐��Őݒ肷��B
	void drawPolygon(ArrayRange<const Point> points);
	/// �����`��`���B
	void drawRectangle(const Rectangle& rect);
	void drawRectangle(int x, int y, int width, int height);
	/// �����`��A���ŕ`���B
	void drawRectangles(ArrayRange<const Rectangle> rects);
	/// �̈�̗֊s��`���B�����ꂾ���֊s�`��Ɏg���u���V�������Ŏw�肷��B
	void drawRegion(HRGN region, HBRUSH brush, int lineWidth, int lineHeight);
	/// �p�̊ۂ������`��`���B
	void drawRoundRectangle(const Rectangle& rect, const Size ellipseSize);
	void drawRoundRectangle(int x, int y, int width, int height, int ellipseWidth, int ellipseHeight);
	/// ������������B�����̔w�i��h��Ȃ��悤�ɂ���ɂ� backTransparent �� true �ɐݒ肷��B
	void drawText(StringRange s, const Point& point);
	void drawText(StringRange s, int x, int y);
	/// ��`�͈͓̔��ŕ�����������Bescapement �y�� orientation �� 0 �̃t�H���g�����T�|�[�g���Ȃ��B�i���c�����͕s�j
	void drawText(StringRange s, const Rectangle& rect, Graphics::TextFormat format = TextFormat::default, int tabWidth = 8);
	void drawText(StringRange s, int x, int y, int width, int height, Graphics::TextFormat format = TextFormat::default, int tabWidth = 8);
	/// drawPolygon �֐��Ō������鑽�p�`�����݂ɓh��Ԃ����ǂ����Bfalse �̏ꍇ�͑S�ēh��Ԃ��B
	bool fillAlternate() const;
	bool fillAlternate(bool value);
	/// GraphicsPath �ŕ`���ꂽ�̈���u���V�œh��B
	void fillPath(GraphicsPath& path);
	/// �̈���u���V�œh��B
	void fillRegion(HRGN region);
	/// ���E�F�Ɉ͂܂ꂽ�̈�̓h��Ԃ����s���B�f�o�C�X���X�V�̈�ŃN���b�s���O����Ă���Ǝv�����悤�Ȍ��ʂɂȂ�Ȃ����ɒ��ӁB
	void floodFillBorder(const Point& point, const Color& borderColor);
	void floodFillBorder(int x, int y, const Color& borderColor);
	/// �w�肵���\�ʐF�̗̈�̓h��Ԃ����s���B�f�o�C�X���X�V�̈�ŃN���b�s���O����Ă���Ǝv�����悤�Ȍ��ʂɂȂ�Ȃ����ɒ��ӁB
	void floodFillSurface(const Point& point, const Color& surfaceColor);
	void floodFillSurface(int x, int y, const Color& surfaceColor);
	/// �n�[�h���`����I����܂ő҂B
	static void flush();
	/// ������`�悷��t�H���g�B
	Font font() const;
	Font font(HFONT value);
	/// �E�C���h�E�̔�N���C�A���g�̈���܂߂� Graphics ���쐬�B
	static Graphics fromControlWithNonClientArea(HWND control);
	/// �w�肵�� graphics �ƌ݊����̂��郁�����f�o�C�X���쐬�Bgraphics �� nullptr ���w�肷��ƃf�B�X�v���C�ƌ݊����̂��郁�����f�o�C�X���쐬����B
	static Graphics fromGraphics(HDC graphics);
	/// �f�B�X�v���C��\�� Graphics ���쐬�B
	static Graphics fromScreen();
	/// ���̃f�o�C�X�Ŏw�肵���F�ɍł��߂��F��Ԃ��B
	Color getNearestColor(const Color& color) const;
	/// �s�N�Z���̐F���擾����B�摜���A���t�@�`�����l���������Ă����Ƃ��Ă��A���t�@���͎擾�ł��Ȃ��B
	Color getPixel(const Point& point) const;
	Color getPixel(int x, int y) const;
	/// �_���`��ł��邩�ǂ����B
	bool isVisible(const Point& point) const;
	bool isVisible(int x, int y) const;
	/// �̈悪�ꕔ�ł��`��ł��邩�ǂ����B
	bool isVisible(const Rectangle& rect) const;
	bool isVisible(int x, int y, int width, int height) const;
	/// ������̕`��T�C�Y�����߂�B���ʂ̉��`���t�H���g�̂ݗL���B
	Size measureText(StringRange s);
	/// �w�肵�����ŕ\���ł��镶���܂łŐ؂�̂Ă��ꍇ�̕`��T�C�Y�����߂�B���ʂ̉��`���t�H���g�̂ݗL���B
	Size measureText(StringRange s, int width);
	/// ������̕`��T�C�Y�����߂�B���ʂ̉��`���t�H���g�̂ݗL���B
	Size measureText(StringRange s, const Size& layoutArea, Graphics::TextFormat format = TextFormat::default, int tabWidth = 8);
	Size measureText(StringRange s, int width, int height, Graphics::TextFormat format = TextFormat::default, int tabWidth = 8);
	/// �y���̃}�C�^�[�ڍ��̒����B
	float miterLimit() const;
	float miterLimit(float value);
	/// �f�X�g���N�^�Ńn���h����j�����邩�ǂ����B�ύX�͗v���ӁB
	bool owned() const;
	void owned(bool value);
	/// �}�`�̗֊s��`���y���B�F�𒼐ڐݒ�ł���B�֊s��`���Ȃ��ꍇ�� Pen::hollow() ��ݒ肷��B
	Pen pen() const;
	Pen pen(HPEN value);
	Pen pen(Color value);
	/// dpiY() �����Ƀs�N�Z�����|�C���g�ϊ����s���B
	float pixelToPoint(int pixel);
	/// dpiY() �����Ƀ|�C���g���s�N�Z���ϊ����s���B
	int pointToPixel(float point);
	/// �s�N�Z���̐F��ݒ肷��B
	void setPixel(const Point& point, const Color& color);
	void setPixel(int x, int y, const Color& color);
	/// ���݂̐ݒ�̕ۑ��ƕ����B
	Graphics::State state() const;
	void state(Graphics::State value);
	/// ������̕����Ԋu�B��s�`��� drawText �֐��Ńv���|�[�V���i���ł͂Ȃ��t�H���g���g�����ꍇ�̂ݗL���B
	/// �v���|�[�V���i���t�H���g�ŕ`�悷��ꍇ�ɂ��̐ݒ肪�O�i�K��l�j�ȊO���Ƃ��܂��`�悳��Ȃ��̂Œ��ӁB
	int textCharExtra() const;
	int textCharExtra(int value);
	/// �e�L�X�g�̐F�B
	Color textColor() const;
	Color textColor(Color value);
	/// �N���b�v�̈�𕽍s�ړ�����B
	void translateClip(int dx, int dy);
	/// ���ۂɕ`��\�ȗ̈���܂ދ�`�B�摜����쐬���Ă���ꍇ�͉摜�̑傫���B
	Rectangle visibleClipBounds() const;

public:
	/// HDC �ւ̎����ϊ� �� null �`�F�b�N�p
	operator HDC() const { return _handle; }

private:
	HDC _handle;
	bool _owned;
};



	}
}