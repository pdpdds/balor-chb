#include <balor/io/Resource.hpp>

#include <utility>

#include <balor/graphics/Bitmap.hpp>
#include <balor/graphics/Brush.hpp>
#include <balor/graphics/Color.hpp>
#include <balor/graphics/Cursor.hpp>
#include <balor/graphics/Graphics.hpp>
#include <balor/graphics/Icon.hpp>
#include <balor/graphics/Pen.hpp>
#include <balor/io/File.hpp>
#include <balor/io/MemoryStream.hpp>
#include <balor/system/Module.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/Rectangle.hpp>


namespace balor {
	namespace io {
		namespace testResource {

using std::move;
using namespace balor::graphics;
using namespace balor::io;
using namespace balor::locale;
using namespace balor::system;


namespace {
Bitmap getTestBitmap(Bitmap&& bitmap) { // ���F���₷���A���E�Ɣ��]�̃`�F�b�N���ł���悤�ȉ摜�𐶐�����B�ڎ��Ńe�X�g�ς�
	if (bitmap.bitsPerPixel() <= 8) {
		Color colors[] = {Color::red(), Color::blue(), Color::green(), Color::white(), Color::black(), Color::yellow(), Color::aqua()};
		bitmap.palette(colors);
	}
	Graphics graphics(bitmap);
	Rectangle rect(0, 0, bitmap.width(), bitmap.height());
	graphics.brush(Brush::hollow());
	graphics.pen(Color::red());
	graphics.drawRectangle(rect);
	rect.grow(-1, -1);
	graphics.pen(Color::blue());
	graphics.drawRectangle( rect);
	rect.grow(-1, -1);
	graphics.brush(Color::green());
	graphics.pen(Color::green());
	graphics.drawRectangle(rect);
	graphics.setPixel(0, 0, Color::green());
	graphics.setPixel(bitmap.width() - 1, 0, Color::black());
	graphics.setPixel(0, bitmap.height() - 1, Color::yellow());
	graphics.setPixel(bitmap.width() - 1, bitmap.height() - 1, Color::aqua());
	Graphics::flush();
	return move(bitmap);
}
} // namespace



testCase(startup) {
	balor::test::UnitTest::ignoreHandleLeakCheck();
	Resource resource(Locale(L"en-US"));
	auto stream = resource.getRawData(L"balor::io::resource::test00.png");
	Bitmap bitmap(stream); // XP�ɂ����Ă�����̏�������x�ʂ��Ă����Ȃ��ƃn���h�����[�N�����o�����
}


testCase(construct) {
	{// �f�t�H���g�R���X�g���N�^
		testNoThrow(Resource resource);
	}
}


testCase(getBitmap) {
	Resource resource;

	// ������Ȃ����\�[�X
	testThrow(resource.getBitmap(L"balor::io::resource::lajeoiajfo0830203"), Resource::NotFoundException);

	{// RCDATA���\�[�X
		Bitmap bitmap = resource.getBitmap(L"balor::io::resource::test00.png");
		testAssert(!bitmap.isDDB());
		testAssert(bitmap.equalsBits(getTestBitmap(Bitmap(30, 40, Bitmap::Format::rgb24bpp))));
	}
	{// BITMAP���\�[�X
		Bitmap bitmap = resource.getBitmap(L"balor::io::resource::test01.bmp");
		testAssert(!bitmap.isDDB());
		testAssert(bitmap.equalsBits(getTestBitmap(Bitmap(30, 40, Bitmap::Format::palette8bpp))));
	}
	resource = Resource(Locale(L"en-US"));
	{// ���[�J���C�Y���\�[�X
		Bitmap bitmap = resource.getBitmap(L"balor::io::resource::test02.bmp");
		testAssert(bitmap.equalsBits(getTestBitmap(Bitmap(40, 50, Bitmap::Format::palette4bpp))));
	}
	{// ���[�J���C�Y���\�[�X��������Ȃ�
		Bitmap bitmap = resource.getBitmap(L"balor::io::resource::test03.bmp");
		testAssert(bitmap.equalsBits(getTestBitmap(Bitmap(40, 50, Bitmap::Format::argb32bpp)), true));
	}
	{// ���[�J���C�Y���\�[�X�iRCDATA�j
		Bitmap bitmap = resource.getBitmap(L"balor::io::resource::test04.png");
		testAssert(bitmap.equalsBits(getTestBitmap(Bitmap(40, 50, Bitmap::Format::palette4bpp))));
	}
	{// ���[�J���C�Y���\�[�X��������Ȃ��iRCDATA�j
		Bitmap bitmap = resource.getBitmap(L"balor::io::resource::test05.png");
		testAssert(bitmap.equalsBits(getTestBitmap(Bitmap(40, 50, Bitmap::Format::argb32bpp))));
	}

	// TODO: DLL���\�[�X�ɂ��Ă͖��e�X�g
}


testCase(getCursor) {
	balor::test::UnitTest::ignoreHandleLeakCheck(); // �J�[�\�����\�[�X�͂������񃍁[�h���ꂽ�炽�Ƃ��J�����Ă��v���Z�X�Ɏc�葱����悤���B�d�l�H
	Resource resource;

	// ������Ȃ����\�[�X
	testThrow(resource.getCursor(L"balor::io::resource::la0r9840avfjoasdjifao0"), Resource::NotFoundException);

	{// ���[�J���C�Y�Ȃ�
		Cursor cursor = resource.getCursor(L"balor::io::resource::test08.ico");
		testAssert(cursor.bitmap().toDIB().equalsBits(getTestBitmap(Bitmap(32, 32, Bitmap::Format::argb32bpp))));
	}

	resource = Resource(Locale(L"en-US"));
	{// ���[�J���C�Y���\�[�X
		Cursor cursor = resource.getCursor(L"balor::io::resource::test09.ico");
		testAssert(cursor.bitmap().toDIB().equalsBits(getTestBitmap(Bitmap(32, 32, Bitmap::Format::argb32bpp))));
	}
	{// ���[�J���C�Y���\�[�X��������Ȃ�
		Cursor cursor = resource.getCursor(L"balor::io::resource::test08.ico");
		testAssert(cursor.bitmap().toDIB().equalsBits(getTestBitmap(Bitmap(32, 32, Bitmap::Format::argb32bpp))));
	}
}


testCase(getIcon) {
	balor::test::UnitTest::ignoreHandleLeakCheck(); // �A�C�R�����\�[�X�͂������񃍁[�h���ꂽ�炽�Ƃ��J�����Ă��v���Z�X�Ɏc�葱����悤���B�d�l�H
	Resource resource;

	// ������Ȃ����\�[�X
	testThrow(resource.getIcon(L"balor::io::resource::la0r9840avfjoasdjifao0"), Resource::NotFoundException);

	{// ���[�J���C�Y�Ȃ�
		Icon icon = resource.getIcon(L"balor::io::resource::test06.ico");
		testAssert(icon.bitmap().toDIB().equalsBits(getTestBitmap(Bitmap(32, 32, Bitmap::Format::argb32bpp))));
	}

	resource = Resource(Locale(L"en-US"));
	{// ���[�J���C�Y���\�[�X
		Icon icon = resource.getIcon(L"balor::io::resource::test07.ico", 16, 16);
		testAssert(icon.bitmap().toDIB().equalsBits(getTestBitmap(Bitmap(16, 16, Bitmap::Format::argb32bpp))));
	}
	{// ���[�J���C�Y���\�[�X��������Ȃ�
		Icon icon = resource.getIcon(L"balor::io::resource::test06.ico");
		testAssert(icon.bitmap().toDIB().equalsBits(getTestBitmap(Bitmap(32, 32, Bitmap::Format::argb32bpp))));
	}
}


testCase(getRawData) {
	Resource resource;

	// ������Ȃ����\�[�X
	testThrow(resource.getRawData(L"balor::io::resource::la0r9840avfjoasdjifao0"), Resource::NotFoundException);

	{// getBitmap����f�[�^��q��
		auto stream = resource.getRawData(L"balor::io::resource::test00.png");
		Bitmap bitmap(stream);
		testAssert(bitmap.equalsBits(getTestBitmap(Bitmap(30, 40, Bitmap::Format::rgb24bpp))));
	}

	resource = Resource(Locale(L"en-US"));
	{// ���[�J���C�Y���\�[�X
		auto stream = resource.getRawData(L"balor::io::resource::test04.png");
		Bitmap bitmap(stream);
		testAssert(bitmap.equalsBits(getTestBitmap(Bitmap(40, 50, Bitmap::Format::palette4bpp))));
	}
	{// ���[�J���C�Y���\�[�X��������Ȃ�
		auto stream = resource.getRawData(L"balor::io::resource::test05.png");
		Bitmap bitmap(stream);
		testAssert(bitmap.equalsBits(getTestBitmap(Bitmap(40, 50, Bitmap::Format::argb32bpp))));
	}
}



		}
	}
}