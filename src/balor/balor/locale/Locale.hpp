#pragma once

#include <balor/Exception.hpp>
#include <balor/StringRange.hpp>


namespace std {
template<typename T> class allocator;
template<typename T, typename A> class vector;
}

namespace balor {
class String;
}


namespace balor {
	namespace locale {



/**
 * ����A�����񏈗��Ɋւ�郍�P�[����\���B
 * 
 * ���P�[���� ISO ���Ƃ͓��{�Ȃ� "ja-JP" �ŁA�č��Ȃ�� "en-US" �Ƃ������`���B
 * .NET �̃T�|�[�g���郍�P�[���Ɗ��S�Ɉ�v����킯�ł͂Ȃ����啔���͓����B http://msdn.microsoft.com/ja-jp/library/system.globalization.cultureinfo(v=vs.80).aspx
 */
class Locale {
public:
	/// ���P�[����������Ȃ������B
	class NotFoundException : public Exception {};

public:
	/// �n��Ɉˑ����Ȃ����P�[���ō쐬�B
	Locale();
	/// ���P�[���h�c����쐬�B
	explicit Locale(int lcid);
	/// ���P�[���� ISO ������쐬�B
	explicit Locale(StringRange name);

public:
	/// C/C++ �̕W�����C�u�����Ŏg�p�ł��郍�P�[�����B
	String cLocaleName() const;
	/// ISO �����B
	String countryName() const;
	/// ���݂̃X���b�h�̃��P�[���B
	static Locale current();
	static void current(const Locale& value);
	/// ���݂̃��P�[���ł̕\���ɓK�������P�[�����B
	String displayName() const;
	/// �p��̍����B
	String englishCountryName() const;
	/// �p��̌��ꖼ�B
	String englishLanguageName() const;
	/// ���P�[���h�c�B
	int id() const;
	/// �n��Ɉˑ����Ȃ����P�[���B
	static Locale invariant();
	/// ����R�[�h�B
	int languageCode() const;
	/// ISO ���ꖼ�B
	String languageName() const;
	/// �C���X�g�[������Ă���S�Ẵ��P�[���B
	static std::vector<Locale, std::allocator<Locale> > locales();
	/// ���P�[���� ISO ���B
	String name() const;
	void nameToBuffer(StringBuffer& buffer) const;

public:
	bool operator==(const Locale& rhs) const;
	bool operator!=(const Locale& rhs) const;

private:
	unsigned int _id;
};



	}
}