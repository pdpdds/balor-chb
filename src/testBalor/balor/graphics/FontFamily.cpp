#include <balor/graphics/FontFamily.hpp>

#include <vector>

#include <balor/graphics/GdiplusInitializer.hpp>
#include <balor/ArgumentException.hpp>
#include <balor/scopeExit.hpp>
#include <balor/test/UnitTest.hpp>
#define ENABLE_WIN32_LEAN_AND_MEAN
#define ENABLE_MINMAX
#include <balor/system/windows.hpp> // gdiplus.h������min, max�}�N�����g���Ă���I
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")


namespace balor {
	namespace graphics {
		namespace testFontFamily {


using std::move;



testCase(startup) { // �n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������i�ꌩ���[�N�Ɍ�����j�֐������炩���ߌĂ�ł���
	balor::test::UnitTest::ignoreHandleLeakCheck();

	GdiplusInitializer::initialize(); // Gdiplus::GdiplusStartup�֐��͍ŏ��̌Ăяo���ł����n���h���𕡐��J���ĕێ�����

	{
		FontFamily family(L"Arial"); // EnumFontFamiliesExW �֐��͍ŏ��̌Ăяo���ł����n���h���𕡐��J���ĕێ�����
		Gdiplus::FontFamily gdiFamily(L"Arial"); // ���̊֐��͍ŏ��̌Ăяo���ł����n���h���𕡐��J���ĕێ�����
	}
}


testCase(defaultConstruct) {
	FontFamily family;
	testAssert(!family);
	testAssert(family.name() == L"");
}


testCase(rvalueConstruct) {
	FontFamily source(L"MS UI Gothic");
	FontFamily family = move(source);
	testAssert(!source);
	testAssert(family);
	testAssert(family.name() == L"MS UI Gothic");
}


testCase(nameConstruct) {
	// �����ȃp�����[�^
	testAssertionFailed(FontFamily(L""));

	// ������Ȃ��t�H���g��
	testThrow(FontFamily(L"���肦�Ȃ��t�H���g��"), ArgumentException);

	FontFamily family(L"MS UI Gothic");
	testAssert(family);
	testAssert(family.name() == L"MS UI Gothic");
}


testCase(rvalueAssignment) {
	FontFamily source(L"MS UI Gothic");
	FontFamily family;
	family = move(source);
	testAssert(!source);
	testAssert(family);
	testAssert(family.name() == L"MS UI Gothic");

	family = move(family);
	testAssert(family);
}


testCase(getMetrics) {
	// �v�Z���@�����Ă����ۂ��Ȃ̂łƂɂ����F�X��r���Ă݂�
	//auto families = FontFamily::families(); // �c�����p�ƁA.NET�ł͗񋓂���Ȃ��C�O�̃L�����N�^�[�Z�b�g�̃t�H���g�ƁA�l�r �o�q�Q�S�V�b�N�ȊO�ł͂��܂�������
	//for (auto i = families.begin(), end = families.end(); i != end; ++i) {
	//const wchar_t* names[] = {L"�l�r �o�q�Q�S�V�b�N"}; // ����͂Ȃ���regular�X�^�C�����T�|�[�g���Ȃ��ƌ딻�f�����B�����Gdiplus�̎擾�l���O�ɂȂ肤�܂������Ȃ�
	const wchar_t* names[] = {L"Arial", L"MS UI Gothic", L"�l�r �S�V�b�N", L"�l�r �o�S�V�b�N", L"�l�r ����", L"�l�r �o����", L"���C���I"};
	const int styles[] = {FontStyle::regular, FontStyle::bold, FontStyle::italic, FontStyle::bold | FontStyle::italic};
	for (int i = 0; i < sizeof(names) / sizeof(names[0]); ++i) {
		for (int j = 0; j < sizeof(styles) / sizeof(styles[0]); ++j) {
			FontFamily family(names[i]);
			//FontFamily& family = *i;
			Gdiplus::FontFamily gdiFamily(family.name().c_str());
			const int style = styles[j];
			if (gdiFamily.GetLastStatus() != Gdiplus::Ok) {
				balor::test::UnitTest::write(L"invalid family name:");
				balor::test::UnitTest::write(family.name().c_str());
				balor::test::UnitTest::write(L"\n");
			} else {
				testAssert(family.getCellAscent(style)  == gdiFamily.GetCellAscent(style));
				testAssert(family.getCellDescent(style) == gdiFamily.GetCellDescent(style));
				testAssert(family.getEmHeight(style)    == gdiFamily.GetEmHeight(style));
				testAssert(family.getLineSpacing(style) == gdiFamily.GetLineSpacing(style));

				//auto a = family.getCellAscent(style);
				//auto b = gdiFamily.GetCellAscent(style);
				//if (gdiFamily.IsStyleAvailable(style) && a != b) {
				//	a = a;
				//	balor::test::UnitTest::write(L"error family name:");
				//	balor::test::UnitTest::write(family.name().c_str());
				//	balor::test::UnitTest::write(L"\n");
				//}
			}
		}
	}
}


testCase(families) {
	auto families = FontFamily::families();
	testAssert(!families.empty());
}


testCase(genericFamilies) {
	testAssert(FontFamily::genericMonospace().name() == L"Courier New");
	testAssert(FontFamily::genericSansSerif().name() == L"Microsoft Sans Serif");
	testAssert(FontFamily::genericSerif().name() == L"Times New Roman");
}


//testCase(name) { // testCase(construct), testCase(nameConstruct) �Ńe�X�g�ς�
//}



		}
	}
}