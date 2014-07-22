#pragma once

#include <balor/OutOfMemoryException.hpp>
#include <balor/StringRange.hpp>
#include <balor/StringRangeArray.hpp>

struct HBITMAP__;

namespace std {
template<typename T> class allocator;
template<typename T, typename A> class vector;
}

namespace balor {
	namespace graphics {
		class Bitmap;
	}
	namespace io {
		class MemoryStream;
		class Stream;
	}
	class String;
}


namespace balor {
	namespace gui {



/**
 * �N���b�v�{�[�h�B
 *
 * �E�C���h�E�̃��b�Z�[�W���[�v�����s���Ă��Ȃ��Ɠ��삵�Ȃ��B
 * DIB �r�b�g�}�b�v�̓\��t���͂܂Ƃ��ɃT�|�[�g���Ă���\�t�g�͏��Ȃ���ADIB ���� DDB �̎����ϊ��͂��܂������Ȃ��ꍇ������悤�Ȃ̂�
 * �ʂ̃\�t�g�ɓ]�����l���Ă���ꍇ�� DDB �r�b�g�}�b�v�̂ݓ\��t����ق�������Ȃ悤���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Clipboard Sample");

	Edit edit(frame, 20, 100, 0, 0, 50, 10, Edit::Options::multiline);
	edit.hScrollBar(true);
	Button button0(frame, 20, 10, 0, 0, L"�N���b�v�{�[�h�̕�����\��t��", [&] (Button::Click& ) {
		edit.text(Clipboard::getText());
	});
	Button button1(frame, 20, 50, 0, 0, L"�N���b�v�{�[�h�ɃG�f�B�b�g�̕�����\��t��", [&] (Button::Click& ) {
		Clipboard::setText(edit.text());
	});

	frame.runMessageLoop();
 * </code></pre>
 */
class Clipboard {
public:
	typedef ::HBITMAP__* HBITMAP;
	typedef ::balor::graphics::Bitmap Bitmap;
	typedef ::balor::io::MemoryStream MemoryStream;
	typedef ::balor::io::Stream Stream;

	///// �N���b�v�{�[�h�ɃA�N�Z�X�ł��Ȃ������B
	//class AccessDeniedException : public Exception {};

	/// ������������Ȃ������B
	struct OutOfMemoryException : public ::balor::OutOfMemoryException {};


public:
	/// �\��t����ꂽ�S�Ă��폜����B
	static void clear();
	/// �r�b�g�}�b�v���\��t�����Ă��邩�ǂ����B
	static bool containsBitmap();
	/// DIB �r�b�g�}�b�v���\��t�����Ă��邩�ǂ����B������ DDB �� DIB �ɕϊ��\�Ȃ̂ŋ�ʂ��Ĕ��f�͂ł��Ȃ��B
	static bool containsDIB();
	/// �t�@�C���h���b�v���X�g���\��t�����Ă��邩�ǂ����B
	static bool containsFileDropList();
	/// ���[�U��`�̃������f�[�^���\��t�����Ă��邩�ǂ����B
	static bool containsMemory(int memoryFormat);
	/// �����񂪓\��t�����Ă��邩�ǂ����B
	static bool containsText();
	/// DDB �r�b�g�}�b�v���擾����B�����ꍇ�̓k���n���h���̃r�b�g�}�b�v��Ԃ��B
	static Bitmap getBitmap();
	/// DIB �r�b�g�}�b�v���擾����B�����ꍇ�̓k���n���h���̃r�b�g�}�b�v��Ԃ��B
	static Bitmap getDIB();
	/// �t�@�C���h���b�v���X�g���擾����B�����ꍇ�͋�̔z���Ԃ��B
	static std::vector<String, std::allocator<String> > getFileDropList();
	/// ���[�U��`�̃������f�[�^���擾����B�����ꍇ�͋�̃������X�g���[����Ԃ��B
	static MemoryStream getMemory(int memoryFormat);
	/// ��������擾����B�����ꍇ�͋󕶎����Ԃ��B
	static String getText();
	/// ���[�U��`�̃������t�H�[�}�b�g����o�^���A�������t�H�[�}�b�g��Ԃ��B�������t�H�[�}�b�g�������̃v���Z�X�Ŋ��ɓo�^����Ă����瓯���������t�H�[�}�b�g��Ԃ��B�啶���Ə������͋�ʂ��Ȃ��B
	static int registerMemoryFormat(StringRange memoryFormatName);
	/// DDB �r�b�g�}�b�v�Ƃ��ē\��t����B
	static void setBitmap(HBITMAP value);
	/// DIB �r�b�g�}�b�v�Ƃ��ē\��t����B
	static void setDIB(HBITMAP value);
	/// �t�@�C���h���b�v���X�g��\��t����B
	static void setFileDropList(StringRangeArray value);
	/// ���[�U��`�̃������f�[�^��ݒ肷��B
	static void setMemory(int memoryFormat, Stream& stream);
	/// �������\��t����B
	static void setText(StringRange value);


public: // �����g�p�֐�
	static void* _dibToHgrobal(HBITMAP bitmap);
	static void* _fileDropListToHglobal(StringRangeArray fileDropList);
	static std::vector<String, std::allocator<String> > _hdropToFileDropList(void* drop);
	static Bitmap _hgrobalToDIB(void* global);
};



	}
}