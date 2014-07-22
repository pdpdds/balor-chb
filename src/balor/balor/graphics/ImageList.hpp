#pragma once

#include <balor/Enum.hpp>
#include <balor/NonCopyable.hpp>

struct _IMAGELIST;
struct HBITMAP__;
struct HICON__;

namespace balor {
	class Size;
}


namespace balor {
	namespace graphics {

class Bitmap;
class Color;
class Icon;



/**
 * �摜���X�g�B
 *
 * �����傫���A�t�H�[�}�b�g�̉摜���܂Ƃ߂ĊǗ����A���߃J���[�L�[��A���t�@�`�����l���ɂ�锼�����������T�|�[�g����B
 */
class ImageList : private NonCopyable {
public:
	typedef ::_IMAGELIST* HIMAGELIST;
	typedef ::HBITMAP__* HBITMAP;
	typedef ::HICON__* HICON;

	/// �摜���X�g�̃t�H�[�}�b�g�B
	struct Format {
		enum _enum {
			palette4bpp = 0x00000004, /// �P�U�F�p���b�g�B
			palette8bpp = 0x00000008, /// �Q�T�U�F�p���b�g�B
			rgb16bpp    = 0x00000010, /// �P�U�r�b�g�J���[�摜�B
			rgb24bpp    = 0x00000018, /// �Q�S�r�b�g�J���[�摜�B
			argb32bpp   = 0x00000020, /// �A���t�@�`�����l���t���R�Q�r�b�g�J���[�摜�B
		};
		BALOR_NAMED_ENUM_MEMBERS(Format);
	};

	/// �摜�̕`���ԁBGraphics::drawImageList �֐��̈����Ɏg���B
	struct State {
		enum _enum {
			normal    = 0x00000000, /// �}�X�N���g���ĕ`��B
			drawMask  = 0x00000010, /// �}�X�N�摜��`��B
			unmasked  = 0x00000020, /// �}�X�N���g�킸�ɕ`��B�������}�X�N�������Ȃ��A���t�@�`�����l���摜�ɂ͖����B
			focused   = 0x00000002, /// �t�H�[�J�X��Ԃŕ`��B
			selected  = 0x00000004, /// �I����Ԃŕ`��B
		};
		BALOR_NAMED_ENUM_MEMBERS(State);
	};

	/// �V�X�e�����\�[�X�̉摜���X�g�̎�ށBfromSystemResource �֐��̈����Ɏg���B
	struct SystemResource {
		enum _enum {
			smallStandardImages = 0, /// �W���I�ȃA�v���P�[�V�����Ŏg�p����鏬���ȃA�C�R���̉摜���X�g�B
			largeStandardImages = 1, /// �W���I�ȃA�v���P�[�V�����Ŏg�p�����傫�ȃA�C�R���̉摜���X�g�B
			smallViewImages     = 4, /// ���X�g�r���[�̑����\�������ȃA�C�R���̉摜���X�g�B
			largeViewImages     = 5, /// ���X�g�r���[�̑����\���傫�ȃA�C�R���̉摜���X�g�B
			smallExplorerImages = 8, /// �E�C���h�E�Y�G�N�X�v���[���Ŏg�p����鏬���ȃA�C�R���̉摜���X�g�B
			largeExplorerImages = 9, /// �E�C���h�E�Y�G�N�X�v���[���Ŏg�p����鏬���ȃA�C�R���̉摜���X�g�B
		};
		BALOR_NAMED_ENUM_MEMBERS(SystemResource);
	};

	/// �V�X�e�����\�[�X�̉摜���X�g�ismallStandardImages�AlargeStandardImages�j�̉摜�C���f�b�N�X�B
	struct StandardImage {
		enum _enum {
			cut          =  0, /// �؂���B
			copy         =  1, /// �R�s�[�B
			paste        =  2, /// �\��t���B
			undo         =  3, /// ���ɖ߂��B
			redo         =  4, /// ��蒼���B
			remove       =  5, /// �폜�B
			fileNew      =  6, /// �t�@�C���̐V�K�쐬�B
			fileOpen     =  7, /// �t�@�C�����J���B
			fileSave     =  8, /// �t�@�C���̕ۑ��B
			printPreview =  9, /// ����v���r���[�B
			properties   = 10, /// �v���p�e�B�B
			help         = 11, /// �w���v�B
			find         = 12, /// �����B
			replace      = 13, /// �u���B
			print        = 14, /// ����B
		};
		BALOR_NAMED_ENUM_MEMBERS(StandardImage);
	};

	/// �V�X�e�����\�[�X�̉摜���X�g�ismallViewImages�AlargeViewImages�j�̉摜�C���f�b�N�X�B
	struct ViewImage {
		enum _enum {
			largeIcons    =  0, /// �傫�ȃA�C�R���B
			smallIcons    =  1, /// �����ȃA�C�R���B
			list          =  2, /// �ꗗ�B
			details       =  3, /// �ڍׁB
			sortName      =  4, /// ���O���Ń\�[�g�B
			sortSize      =  5, /// �傫�����Ń\�[�g�B
			sortDate      =  6, /// ���t���Ń\�[�g�B
			sortType      =  7, /// ��ނŃ\�[�g�B
			parentFolder  =  8, /// �e�t�H���_�ֈړ��B
			netConnect    =  9, /// �l�b�g���[�N�h���C�u�ɐڑ��B
			netDisconnect = 10, /// �l�b�g���[�N�h���C�u����ؒf�B
			newFolder     = 11, /// �V�����t�H���_�B
			viewMenu      = 12, /// ���j���[�B
		};
		BALOR_NAMED_ENUM_MEMBERS(ViewImage);
	};

	/// �V�X�e�����\�[�X�̉摜���X�g�ismallExplorerImages�AlargeExplorerImages�j�̉摜�C���f�b�N�X�B
	struct ExplorerImage {
		enum _enum {
			back           =  0, /// �߂�B
			forward        =  1, /// �i�ށB
			favorites      =  2, /// ���C�ɓ���B
			addToFavorites =  3, /// ���C�ɓ���ɒǉ��B
			viewTree       =  4, /// �c���[�\���B
		};
		BALOR_NAMED_ENUM_MEMBERS(ExplorerImage);
	};

public:
	/// �k���n���h���ō쐬�B
	ImageList();
	ImageList(ImageList&& value);
	/// �n���h������쐬�Bowned �� true �Ȃ�΃f�X�g���N�^�Ńn���h����j������B
	explicit ImageList(HIMAGELIST handle, bool owned = false);
	/// �傫���Ɖ摜�t�H�[�}�b�g����쐬�Bmasked �̓��m�N���̃}�X�N�摜���g�����ǂ����B
	explicit ImageList(const Size& imageSize, ImageList::Format format = Format::argb32bpp, bool masked = true);
	ImageList(int width, int height, ImageList::Format format = Format::argb32bpp, bool masked = true);
	/// �V�X�e�����\�[�X����摜���X�g���쐬����B
	explicit ImageList(ImageList::SystemResource systemResource);
	~ImageList();
	ImageList& operator=(ImageList&& value);

public:
	/// �摜�����X�g�̖����ɒǉ�����B�摜�̕��� imageSize().width �ȏ�łȂ���΂Ȃ�Ȃ��B�摜�̕��� imageSize().width �� n �{�ł���ꍇ�� n �̉摜��ǉ�����B
	/// �}�X�N�摜�̓��m�N���r�b�g�}�b�v�ŁA�������������߂���B�J���[�L�[���w�肵���ꍇ�̓J���[�L�[�̐F�̕����𓧉߂���B
	/// �r�b�g�}�b�v���R�Q�r�b�g�摜�łȂ����P�h�b�g�ł��O�ł͂Ȃ��A���t�@�����ꍇ�A�}�X�N�摜���J���[�L�[����������ăA���t�@�`�����l���œ��߂����B
	/// �ǉ���Ƀr�b�g�}�b�v�n���h���͎Q�Ƃ���Ȃ��B
	void add(HBITMAP bitmap, HBITMAP mask = nullptr);
	void add(HBITMAP bitmap, const Color& colorKey);
	/// �A�C�R�������X�g�̖����ɒǉ�����B
	/// ���\�[�X�A�C�R���ł������ꍇ�A���[�h���ꂽ���̃T�C�Y���Ȃ�ł��낤�ƁAimageSize() �ɍ����T�C�Y�̃A�C�R�����I�������B�����łȂ��ꍇ�� imageSize() �ɍ��킹�Ċg��k�������B
	/// �ǉ���ɃA�C�R���n���h���͎Q�Ƃ���Ȃ��B
	void add(HICON icon);
	/// �摜���X�g����ɂ���B
	void clear();
	/// �摜���X�g�𕡐�����B
	ImageList clone() const;
	static ImageList clone(HIMAGELIST handle);
	/// �摜�̐��B
	int count() const;
	/// �摜�����X�g����폜����B
	void erase(int index);
	/// �摜�t�H�[�}�b�g�B
	ImageList::Format format();
	/*/// �V�X�e���A�C�R���̉摜���X�g�B�ҏW������n���h�����폜����Ƒ�ςȎ��ɂȂ�̂Œ��ӁB
	//static ImageList fromSystemIcons();*//**/
	/// �P�s�N�Z��������̃r�b�g������摜���X�g�̃t�H�[�}�b�g�ɕϊ�����B
	static ImageList::Format getFormatFromBitsPerPixel(int bitsPerPixel);
	/// �摜���A�C�R���ɂ��Ď擾����B
	Icon getIcon(int index) const;
	/// ���X�g���̉摜�̃T�C�Y�B
	Size imageSize() const;
	/// �f�X�g���N�^�Ńn���h����j�����邩�ǂ����B�ύX�͗v���ӁB
	bool owned() const;
	void owned(bool value);
	/// �w�肵���C���f�b�N�X�̉摜��u��������B�C���f�b�N�X�ȊO�̈����� add �֐��Ɠ����B�u��������Ɉ����̃r�b�g�}�b�v�n���h���A�A�C�R���n���h���͎Q�Ƃ���Ȃ��B
	void replace(int index, HBITMAP bitmap, HBITMAP mask = nullptr);
	void replace(int index, HBITMAP bitmap, const Color& colorKey);
	void replace(int index, HICON icon);

public:
	/// HIMAGELIST �ւ̎����ϊ� �� null �`�F�b�N�p
	operator HIMAGELIST() const { return _handle; }

private:
	HIMAGELIST _handle;
	bool _owned;
};



	}
}