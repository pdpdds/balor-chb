#include <balor/system/FileVersionInfo.hpp>

#include <vector>

#include "../../Revision.h"
#include <balor/locale/Locale.hpp>
#include <balor/io/File.hpp>
#include <balor/system/Module.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/scopeExit.hpp>
#include <balor/String.hpp>


namespace balor {
	namespace system {
		namespace testFileVersionInfo {


using std::move;
using namespace balor::locale;
using namespace balor::io;
using namespace balor::system;



testCase(startup) { // �n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������i�ꌩ���[�N�Ɍ�����j�֐������炩���ߌĂ�ł���
	balor::test::UnitTest::ignoreHandleLeakCheck();

	Locale::locales(); // EnumSystemLocalesW �֐��͍ŏ��̌Ăяo���ł����n���h���𕡐��J���ĕێ�����
}


testCase(constructAndProperties) {
	// �����ȃp�����[�^
	testAssertionFailed(FileVersionInfo(L""));

	// ������Ȃ��t�@�C����
	testThrow(FileVersionInfo(File(Module::current().directory(), L"eliajlfre098faljeoijalfjalheiothjali")), File::NotFoundException);

	{// �o�[�W�������̑��݂��Ȃ��t�@�C��
		FileVersionInfo info(File(Module::current().directory(), L"balor_singleton.dll"));
		testAssertionFailed(info.comments());
		testAssertionFailed(info.companyName());
		testAssertionFailed(info.fileDescription());
		testAssertionFailed(info.fileVersion());
		testAssertionFailed(info.fileVersionText());
		testAssertionFailed(info.internalName());
		testAssertionFailed(info.isDebug());
		testAssertionFailed(info.isPatched());
		testAssertionFailed(info.isPreRelease());
		testAssertionFailed(info.isSpecialBuild());
		testAssertionFailed(info.languageCode());
		testAssertionFailed(info.legalCopyright());
		testAssertionFailed(info.legalTrademarks());
		testAssertionFailed(info.originalFileName());
		testAssertionFailed(info.privateBuild());
		testAssertionFailed(info.productName());
		testAssertionFailed(info.productVersion());
		testAssertionFailed(info.productVersionText());
		testAssertionFailed(info.specialBuild());
	}

	{// ���{��
		Locale backup = Locale::current();
		Locale current(L"ja-JP");
		Locale::current(current);
		scopeExit([&] () {
			Locale::current(backup);
		});
		FileVersionInfo info(Module::current().file());
		testAssert(info.comments() == L"�R�����g");
		testAssert(info.companyName() == L"�J���p�j�[�l�[��");
		testAssert(info.fileDescription() == L"�t�@�C���f�X�N���v�V����");
		testAssert(info.fileVersion() == Version(1, 2, 3, REVISION));
		testAssert(info.fileVersionText() == L"�t�@�C���o�[�W����");
		testAssert(info.internalName() == L"�C���^�[�i���l�[��");
#ifdef _DEBUG
		testAssert(info.isDebug() == true);
		testAssert(info.isPatched() == true);
		testAssert(info.isPreRelease() == false);
		testAssert(info.isSpecialBuild() == false);
#else
		testAssert(info.isDebug() == false);
		testAssert(info.isPatched() == false);
		testAssert(info.isPreRelease() == true);
		testAssert(info.isSpecialBuild() == true);
#endif
		testAssert(info.languageCode() == 0x411);
		testAssert(info.legalCopyright() == L"���[�K���R�s�[���C�g");
		testAssert(info.legalTrademarks() == L"���[�K���g���[�h�}�[�N");
		testAssert(info.originalFileName() == L"�I���W�i���t�@�C���l�[��");
		testAssert(info.privateBuild() == L"�v���C�x�[�g�r���h");
		testAssert(info.productName() == L"�v���_�N�g�l�[��");
		testAssert(info.productVersion() == Version(5, 6, 7, 8));
		testAssert(info.productVersionText() == L"�v���_�N�g�o�[�W����");
		testAssert(info.specialBuild() == L"�X�y�V�����r���h");
	}

	{// �p��
		Locale backup = Locale::current();
		Locale::current(Locale(L"en-US"));
		scopeExit([&] () {
			Locale::current(backup);
		});
		FileVersionInfo info(Module::current().file());
		testAssert(info.comments() == L"comments");
		testAssert(info.companyName() == L"companyName");
		testAssert(info.fileDescription() == L"fileDescription");
		testAssert(info.fileVersion() == Version(1, 2, 3, REVISION));
		testAssert(info.fileVersionText() == L"fileVersion");
		testAssert(info.internalName() == L"internalName");
#ifdef _DEBUG
		testAssert(info.isDebug() == true);
		testAssert(info.isPatched() == true);
		testAssert(info.isPreRelease() == false);
		testAssert(info.isSpecialBuild() == false);
#else
		testAssert(info.isDebug() == false);
		testAssert(info.isPatched() == false);
		testAssert(info.isPreRelease() == true);
		testAssert(info.isSpecialBuild() == true);
#endif
		testAssert(info.languageCode() == 0x409);
		testAssert(info.legalCopyright() == L"legalCopyright");
		testAssert(info.legalTrademarks() == L"legalTrademarks");
		testAssert(info.originalFileName() == L"originalFilename");
		testAssert(info.privateBuild() == L"privateBuild");
		testAssert(info.productName() == L"productName");
		testAssert(info.productVersion() == Version(5, 6, 7, 8));
		testAssert(info.productVersionText() == L"productVersion");
		testAssert(info.specialBuild() == L"specialBuild");
	}

	{// �p�ӂ���Ă��Ȃ��J���`���i�f�t�H���g�J���`���ɂȂ�j
		Locale backup = Locale::current();
		Locale::current(Locale(L"it-CH"));
		scopeExit([&] () {
			Locale::current(backup);
		});
		FileVersionInfo info(Module::current().file());
		testAssert(info.comments() == L"default comments");
		testAssert(info.languageCode() == 0x800);
	}
}


testCase(rvalueConstruct) {
	FileVersionInfo source(Module::current().file());
	testAssert(source);
	FileVersionInfo info = move(source);
	testAssert(!source);
	testAssert(info);
	testAssertionFailed(source.comments());
	testAssert(info.comments() == L"�R�����g");
}


testCase(rvalueAssignment) {
	FileVersionInfo source(Module::current().file());
	testAssert(source);
	FileVersionInfo info(File(Module::current().directory(), L"balor_singleton.dll"));
	testAssert(!info);
	info = move(source);
	testAssert(!source);
	testAssert(info);
	testAssertionFailed(source.comments());
	testAssert(info.comments() == L"�R�����g");

	info = move(info);
	testAssert(info);
	testAssert(info.comments() == L"�R�����g");
}



		}
	}
}