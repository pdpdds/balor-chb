#pragma once

#include <hash_map>

#include <balor/locale/Locale.hpp>
#include <balor/OutOfMemoryException.hpp>
#include <balor/String.hpp>

struct HINSTANCE__;

namespace balor {
	namespace graphics {
		class Bitmap;
		class Cursor;
		class Icon;
	}
	class Size;
}


namespace balor {
	namespace io {

class MemoryStream;



/**
 * ���\�[�X��\���B
 *
 * ���P�[�����w�肵���ꍇ�A���\�[�X���̖����Ƀs���I�h�{���P�[���� ISO ���iLocale::name() �֐��̌��ʁj�����ă��\�[�X����������B
 * ������Ȃ������ꍇ�͖����ɂȂɂ������ɍēx��������B���������\�[�X ID ���g�p����ꍇ�̓��P�[���ɂ��ĉ������Ȃ��B
 * �����񃊃\�[�X�ɂ��Ă͓��ʂŁA���\�[�X ID ���g�p����ꍇ�͏]���ǂ��� STRINGTABLE ���\�[�X���g�������\�[�X�����g�p����ꍇ��
 * namedStringTable �Ƃ������O�� RCDATA ���\�[�X��T���B���̖��O�ɂ����P�[�����̏C�����t���B
 * RCDATA ���\�[�X�̓��e�Ƃ��ĕ����񖼂ƕ�����̓�̃J�����������j�R�[�h�� CSV �e�L�X�g�t�@�C����p�ӂ���K�v������B
 */
class Resource {
public:
	typedef ::HINSTANCE__* HMODULE;
	typedef ::balor::graphics::Bitmap Bitmap;
	typedef ::balor::graphics::Cursor Cursor;
	typedef ::balor::graphics::Icon Icon;
	typedef ::balor::locale::Locale Locale;

	/// ���\�[�X��������Ȃ�����
	class NotFoundException : public Exception {};

	/// ������������Ȃ�����
	struct OutOfMemoryException : public ::balor::OutOfMemoryException {};

public:
	/// ���W���[������쐬�B
	explicit Resource(HMODULE module = nullptr);
	/// ���P�[���ƃ��W���[������쐬�B
	explicit Resource(const Locale& locale, HMODULE module = nullptr);

public:
	/// BITMAP ���\�[�X�܂��� RCDATA ���\�[�X���� Bitmap ���쐬���ĕԂ��BBitmap �N���X�̑Ή����Ă���摜�`����ǂݍ��߂�B
	Bitmap getBitmap(int id);
	Bitmap getBitmap(StringRange name);
	/// CURSOR ���\�[�X���� Cursor ���쐬���ĕԂ��B
	Cursor getCursor(int id);
	Cursor getCursor(StringRange name);
	/// ICON ���\�[�X���� Icon ���쐬���ĕԂ��Bsize �� Size(0, 0) ���w�肷��ƍŏ��Ɍ��������A�C�R���̌����ō쐬�����B
	Icon getIcon(int id);
	Icon getIcon(int id, const Size& size);
	Icon getIcon(int id, int width, int height);
	Icon getIcon(StringRange name);
	Icon getIcon(StringRange name, const Size& size);
	Icon getIcon(StringRange name, int width, int height);
	/// RCDATA ���\�[�X���������X�g���[���Ƃ��Ď擾����B�������̓��\�[�X�̓��������W���[�����A�����[�h�����܂ŗL���B
	MemoryStream getRawData(int id);
	MemoryStream getRawData(StringRange name);
	/// �����񃊃\�[�X���擾����B���O���w�肷�镶���񃊃\�[�X�̍����ɂ��Ă̓N���X�h�L�������g���Q�ƁB
	String getString(int id);
	String getString(StringRange name);
	void getStringToBuffer(StringBuffer& buffer, int id);
	void getStringToBuffer(StringBuffer& buffer, StringRange name);
	/// ���\�[�X�̃��P�[���B
	Locale locale() const;

private:
	HMODULE _module;
	Locale _locale;
	wchar_t _localeName[32];
	std::hash_map<String, String> _namedStringTable;
};



	}
}