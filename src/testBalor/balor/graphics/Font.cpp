#include <balor/graphics/Font.hpp>

#include <vector>

#include <balor/graphics/Bitmap.hpp>
#include <balor/graphics/Brush.hpp>
#include <balor/graphics/Color.hpp>
#include <balor/graphics/Graphics.hpp>
#include <balor/graphics/Pen.hpp>
#include <balor/io/File.hpp>
#include <balor/io/MemoryStream.hpp>
#include <balor/io/Resource.hpp>
#include <balor/system/Module.hpp>
#include <balor/system/windows.hpp>
#include <balor/test/HandleLeakChecker.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/Point.hpp>
#include <balor/Rectangle.hpp>
#include <balor/String.hpp>

#include "../../tools/floatEquals.hpp"


namespace balor {
	namespace graphics {
		namespace testFont {


using std::move;
using namespace balor::io;
using namespace balor::system;
using tools::floatEquals;


namespace {
String getSavePath() {
	return File(Module::current().directory(), L"..\\testBalor\\balor\\graphics\\font\\").path();
}


Bitmap getTestBitmap(const String& name) {
	auto stream = Resource().getRawData(L"balor::graphics::font::" + name);
	return Bitmap(stream);
}


bool makeTestData = false; // �e�X�g�f�[�^�쐬�p�B���ӁI�쐬���ɂ͂��Ȃ炸�摜��ڎ��Ŋm�F���邱�ƁI


bool testFontDraw(const Font& font, int width, int height, const String& text, const String& sourceName, int x = 0, int y = 0) {
	Bitmap bitmap(width, height, Bitmap::Format::argb32bpp);
	{
		Graphics graphics(bitmap);
		graphics.brush(Brush::white());
		graphics.pen(Pen::white());
		graphics.drawRectangle(0, 0, width, height);
		graphics.font(font);
		graphics.textColor(Color::black());
		graphics.drawText(text, x, y);
	}
	if (makeTestData) {
		bitmap.save(getSavePath() + L"\\" + sourceName);
		return false;
	}
	return bitmap.equalsBits(getTestBitmap(sourceName), true);
}
} // namespace



testCase(startup) { // �n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������i�ꌩ���[�N�Ɍ�����j�֐������炩���ߌĂ�ł���
	balor::test::UnitTest::ignoreHandleLeakCheck();

	getTestBitmap(L"test00.png"); // GdiplusStartup �֐��͍ŏ��̌Ăяo���ł����n���h���𕡐��J���ĕێ�����

	//Font::names(); // EnumFontFamiliesW �֐��͍ŏ��̌Ăяo���ł����n���h���𕡐��J���ĕێ�����

	Bitmap bitmap = Bitmap::createDDB(100, 100);
	Font font(L"�l�r �S�V�b�N", 16);
	Graphics graphics(bitmap);
	graphics.font(font);
	graphics.textColor(Color::black());
	graphics.drawText(L"����", 0, 0); // TextOutW �֐��͍ŏ��̌Ăяo���ł����n���h���𕡐��J���ĕێ�����
}


testCase(defaultConstruct) {
	Font font;
	testAssert(!font);
}


testCase(rvalueConstruct) {
	Font source(L"MS UI Gothic", 24);
	Font font = move(source);
	testAssert(!source);
	testAssert(font);
	testAssert(font.name() == L"MS UI Gothic");
}


testCase(fontAndHeightAndStyleConstruct) {
	Font source(L"MS UI Gothic", 24, Font::Style::regular);
	{
		Font font(source, 16, Font::Style::bold);
		testAssert(font);
		testAssert(font.name() == L"MS UI Gothic");
		testAssert(font.height() == 16);
		testAssert(font.style() == Font::Style::bold);
	}
	{
		Font font(source, 24, Font::Style::italic);
		testAssert(font.style() == Font::Style::italic);
	}
	{
		Font font(source, 24, Font::Style::strikeout);
		testAssert(font.style() == Font::Style::strikeout);
	}
	{
		Font font(source, 24, Font::Style::underline);
		testAssert(font.style() == Font::Style::underline);
	}
}


testCase(fontFamilyNameConstruct) {
	// �����ȃp�����[�^
	testAssertionFailed(Font(L"", 1));
	testAssertionFailed(Font(L"�l�r �S�V�b�N", 0));
	testAssertionFailed(Font(L"�l�r �S�V�b�N", 1, Font::Style::_enum(-1)));
	testAssertionFailed(Font(L"�l�r �S�V�b�N", 1, Font::Style::regular, Font::Quality::_enum(-1)));
	testAssertionFailed(Font(L"�l�r �S�V�b�N", 1, Font::Style::regular, Font::Quality::proof, -3601));
	testAssertionFailed(Font(L"�l�r �S�V�b�N", 1, Font::Style::regular, Font::Quality::proof,  3601));
	testAssertionFailed(Font(L"�l�r �S�V�b�N", 1, Font::Style::regular, Font::Quality::proof,  3600, -3601));
	testAssertionFailed(Font(L"�l�r �S�V�b�N", 1, Font::Style::regular, Font::Quality::proof,  3600,  3601));
	testNoThrow        (Font(L"�l�r �S�V�b�N", 1, Font::Style::regular, Font::Quality::proof,  3600,  3600));
	testNoThrow        (Font(L"�l�r �S�V�b�N", 1, Font::Style::regular, Font::Quality::proof, -3600, -3600));

	{// ���肦�Ȃ��t�H���g�����w�肵�Ă��V�X�e��������ɂȂ�Ƃ����Ă����
		Font font(L"���肦�Ȃ��t�H���g��", 160);
		testAssert(font);
		testAssert(font.name() != L"���肦�Ȃ��t�H���g��");
	}

	// name �̔��f
	testAssert(testFontDraw(Font(L"�l�r �S�V�b�N", 160, Font::Style::regular, Font::Quality::antialiased), 400, 200, L"����", L"test00.png"));
	testAssert(testFontDraw(Font(L"�l�r �o����", 160, Font::Style::regular, Font::Quality::antialiased), 400, 200, L"����", L"test01.png"));

	// height �̔��f
	testAssert(testFontDraw(Font(L"�l�r �S�V�b�N", 16, Font::Style::regular, Font::Quality::antialiased), 40, 20, L"����", L"test02.png"));
	testAssert(testFontDraw(Font(L"�l�r �S�V�b�N", 96, Font::Style::regular, Font::Quality::antialiased), 200, 100, L"����", L"test03.png"));

	// style �̔��f
	testAssert(testFontDraw(Font(L"�l�r �S�V�b�N", 160, Font::Style::bold, Font::Quality::antialiased), 400, 200, L"����", L"test04.png"));
	testAssert(testFontDraw(Font(L"�l�r �S�V�b�N", 160, Font::Style::italic, Font::Quality::antialiased), 400, 200, L"����", L"test05.png"));
	testAssert(testFontDraw(Font(L"�l�r �S�V�b�N", 160, Font::Style::strikeout, Font::Quality::antialiased), 400, 200, L"����", L"test06.png"));
	testAssert(testFontDraw(Font(L"�l�r �S�V�b�N", 160, Font::Style::underline, Font::Quality::antialiased), 400, 200, L"����", L"test07.png"));
	testAssert(testFontDraw(Font(L"�l�r �S�V�b�N", 160, Font::Style::_enum(0x0F), Font::Quality::antialiased), 400, 200, L"����", L"test08.png"));

	// quality �̔��f�iCaution: antialiased �� nonantialiased�ȊO�͂n�r�ɂ���ċ������Ⴄ�̂Ŗڎ��Ŋm�F�j
	testAssert(testFontDraw(Font(L"�l�r �S�V�b�N", 160, Font::Style::regular, Font::Quality::antialiased), 400, 200, L"����", L"test09.png"));
	testAssert(testFontDraw(Font(L"�l�r �S�V�b�N", 160, Font::Style::regular, Font::Quality::nonantialiased), 400, 200, L"����", L"test10.png"));

	// �c�����̃e�X�g
	testAssert(testFontDraw(Font(L"@�l�r �S�V�b�N", 160, Font::Style::regular, Font::Quality::antialiased, 2700, 2700), 200, 600, L"�����B", L"test11.png", 160));
}


testCase(destruct) {
	balor::test::HandleLeakChecker checker;
	{// ���L�������ꍇ
		Font font(L"�l�r �S�V�b�N", 16);
		testAssert(checker.getGdiHandleChange() == 1);
	}
	testAssert(checker.getGdiHandleChange() == 0);
	{// ���L���������Ȃ��ꍇ
		Font font = Font::defaultGui();
		testAssert(checker.getGdiHandleChange() == 0);
	}
	testAssert(checker.getGdiHandleChange() == 0);
}


testCase(rvalueAssignment) {
	{// ���L�������ꍇ
		Font source(L"MS UI Gothic", 24);
		Font font;
		font = move(source);
		testAssert(!source);
		testAssert(font);
		testAssert(font.name() == L"MS UI Gothic");

		font = move(font);
		testAssert(font);
	}
	{// ���L���������Ȃ��ꍇ
		Font source(L"MS UI Gothic", 24);
		Font source2 = Font((HFONT)source);
		Font font;
		font = move(source2);
		testAssert(!source2);
		testAssert(font);
		testAssert(font.name() == L"MS UI Gothic");
		testAssert((HFONT)font == (HFONT)source);

		font = move(font);
		testAssert(font);
	}
}


testCase(clone) {
	{// ��̃t�H���g
		Font source;
		Font font = source.clone();
		testAssert(!font);
	}
	{// ���L�����������n���h��
		Font source(L"MS UI Gothic", 24);
		Font font = source.clone();
		testAssert(font);
		testAssert((HFONT)font != (HFONT)source);
		testAssert(source.name() == L"MS UI Gothic");
		testAssert(font.name() == source.name());
	}
	{// ���L���������Ȃ��n���h��
		Font source(L"MS UI Gothic", 24);
		Font source2 = Font((HFONT)source);
		Font font = source2.clone();
		testAssert(font);
		testAssert((HFONT)font != (HFONT)source2);
		testAssert(source.name() == L"MS UI Gothic");
		testAssert(font.name() == source.name());
	}
}


testCase(cloneWithHFONT) {
	// �����ȃp�����[�^
	testAssertionFailed(Font::clone(nullptr));

	Font source(L"MS UI Gothic", 24);
	Font font = Font::clone(source);
	testAssert(font);
	testAssert(source.name() == L"MS UI Gothic");
	testAssert(font.escapement()  == source.escapement());
	testAssert(font.height()      == source.height());
	testAssert(font.name()        == source.name());
	testAssert(font.orientation() == source.orientation());
	testAssert(font.quality()     == source.quality());
	testAssert(font.style()       == source.style());
}


testCase(escapement) {
	// �����ȃp�����[�^
	testAssertionFailed(Font().escapement());

	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::proof).escapement() == 0);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::proof, 2700).escapement() == 2700);
}
//
//
//testCase(fromHdc) {
//	// �����ȃp�����[�^
//	testAssertionFailed(Font::fromHdc(nullptr));
//
//	Bitmap bitmap(200, 200, Bitmap::PixelFormat::argb32bpp);
//	Graphics graphics(bitmap);
//	Font source(L"MS UI Gothic", 24);
//	testAssert(SelectObject(graphics, source) != nullptr);
//	Font font = Font::fromHdc(graphics);
//	testAssert(font);
//	testAssert(font.name() == L"MS UI Gothic");
//	testAssert((HFONT)font == (HFONT)source);
//}


testCase(fromHandle) {
	Font source(L"MS UI Gothic", 24);
	Font font = Font((HFONT)source);
	testAssert(font);
	testAssert(font.name() == L"MS UI Gothic");
	testAssert((HFONT)font == (HFONT)source);
}


testCase(fromLogFont) {
	Font source(L"MS UI Gothic", 24);
	LOGFONTW logfont;
	memset(&logfont, 0, sizeof(logfont));
	//testThrow(Font::fromLogFont(logfont), Win32Exception); // �������Ă��܂���

	testAssert(GetObjectW(source, sizeof(logfont), &logfont) != 0);
	Font font = Font::fromLogFont(logfont);
	testAssert(font);
	testAssert(font.name() == L"MS UI Gothic");
	testAssert(font.height() == 24);
}


testCase(height) {
	// �����ȃp�����[�^
	testAssertionFailed(Font().height());

	testAssert(Font(L"�l�r �S�V�b�N", 16).height() == 16);
	testAssert(Font(L"�l�r �S�V�b�N", 160).height() == 160);
}


testCase(name) {
	// �����ȃp�����[�^
	testAssertionFailed(Font().name());

	testAssert(Font(L"�l�r �S�V�b�N", 16).name() == L"�l�r �S�V�b�N");
	testAssert(Font(L"�l�r �o����", 16).name() == L"�l�r �o����");
}


testCase(names) {
	auto names = Font::names();
	testAssert(!names.empty());
}


testCase(orientation) {
	// �����ȃp�����[�^
	testAssertionFailed(Font().orientation());

	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::proof).orientation() == 0);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::proof, 0, 2700).orientation() == 2700);
}


testCase(quality) {
	// �����ȃp�����[�^
	testAssertionFailed(Font().quality());

	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular).quality() == Font::Quality::proof);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::default         ).quality() == Font::Quality::default);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::draft           ).quality() == Font::Quality::draft);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::proof           ).quality() == Font::Quality::proof);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::nonantialiased  ).quality() == Font::Quality::nonantialiased);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::antialiased     ).quality() == Font::Quality::antialiased);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::clearType       ).quality() == Font::Quality::clearType);
	//testAssert(Font(L"MS UI Gothic", 24, Font::Style::regular, Font::Quality::clearTypeNatural).quality() == Font::Quality::clearTypeNatural);
}


testCase(style) {
	// �����ȃp�����[�^
	testAssertionFailed(Font().style());

	testAssert(Font(L"MS UI Gothic", 24).style() == Font::Style::regular);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::bold     ).style() == Font::Style::bold);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::italic   ).style() == Font::Style::italic);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::strikeout).style() == Font::Style::strikeout);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::underline).style() == Font::Style::underline);
	testAssert(Font(L"MS UI Gothic", 24, Font::Style::_enum(0x0F)).style() == 0x0F);
}



		}
	}
}