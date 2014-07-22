#include <balor/locale/Locale.hpp>

#include <vector>

#include <balor/test/UnitTest.hpp>
#include <balor/String.hpp>


namespace balor {
	namespace locale {
		namespace testLocale {



testCase(startup) { // �n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������i�ꌩ���[�N�Ɍ�����j�֐������炩���ߌĂ�ł���
	balor::test::UnitTest::ignoreHandleLeakCheck();
	Locale locale(1041);
	locale.displayName(); // GetLocaleInfoW �֐��� LOCALE_SLOCALIZEDDISPLAYNAME �ŌĂяo���Ɠ����Ńn���h����ێ���������
	Locale::locales(); // EnumSystemLocalesW �֐��̓n���h�����ŏ��̌Ăяo���Ŋm�ۂ��A�����ŕێ���������
}


testCase(constructWithLcid) {
	// ������LCID
	testThrow(Locale(-1), Locale::NotFoundException);

	{// ja-JP
		Locale locale(1041);
		testAssert(locale.displayName() == L"���{�� (���{)" || locale.displayName() == L"���{��");
		testAssert(locale.englishCountryName() == L"Japan");
		testAssert(locale.englishLanguageName() == L"Japanese");
		testAssert(locale.id() == 1041);
		testAssert(locale.cLocaleName() == L"Japanese_Japan");
		testAssert(locale.name() == L"ja-JP");
		testAssert(locale.languageName() == L"ja");
		testAssert(locale.countryName() == L"JP");
	}

	{// en-US
		Locale locale(1033);
		testAssert(locale.displayName() == L"�p�� (�č�)");
		testAssert(locale.englishCountryName() == L"United States");
		testAssert(locale.englishLanguageName() == L"English");
		testAssert(locale.id() == 1033);
		testAssert(locale.cLocaleName() == L"English_United States");
		testAssert(locale.name() == L"en-US");
		testAssert(locale.languageName() == L"en");
		testAssert(locale.countryName() == L"US");
	}

	{// invaliant
		Locale locale(127);
		testAssert(locale.displayName() == L"���P�[���Ɉˑ����Ȃ����� (���P�[���Ɉˑ����Ȃ���)" || locale.displayName() == L"Invariant Language (Invariant Country)");
		testAssert(locale.englishCountryName() == L"Invariant Country");
		testAssert(locale.englishLanguageName() == L"Invariant Language");
		testAssert(locale.id() == 127);
		testAssert(locale.name() == L"iv-IV");
		testAssert(locale.cLocaleName() == L"");
		testAssert(locale.languageName() == L"iv");
		testAssert(locale.countryName() == L"IV");
	}
}


testCase(constructWithName) {
	// �����ȃJ���`����
	testThrow(Locale(L"invalid culture name"), Locale::NotFoundException);

	{// ja-JP
		Locale locale(L"ja-JP");
		testAssert(locale.id() == 1041);
		testAssert(locale.name() == L"ja-JP");
	}

	{// en-US
		Locale locale(L"en-US");
		testAssert(locale.id() == 1033);
		testAssert(locale.name() == L"en-US");
	}
}


testCase(current) {
	Locale locale = Locale::current();
	testAssert(locale.id() == 1041); // here is JAPAN!
}


testCase(invariant) {
	Locale locale = Locale::invariant();
	testAssert(locale.id() == 127);
}


testCase(locales) {
	auto locales = Locale::locales();
	testAssert(!locales.empty());
	bool ok = true;
	for (auto i = locales.begin(), end = locales.end(); i != end; ++i) {
		try {
			i->name();
		} catch (Exception& ) {
			ok = false;
		}
	}
	testAssert(ok);
}


//testCase(cLocaleName) {} // testCase(lcidConstruct) �ɂăe�X�g�ς�
//testCase(countryName) {}
//testCase(displayName) {}
//testCase(englishCountryName) {}
//testCase(englishLanguageName) {}
//testCase(id) {}
//testCase(languageName) {}
//testCase(name) {}



		}
	}
}