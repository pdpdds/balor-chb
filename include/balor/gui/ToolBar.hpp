#pragma once

#include <vector>

#include <balor/gui/Control.hpp>

struct _IMAGELIST;

namespace balor {
	namespace graphics {
class ImageList;
	}
}


namespace balor {
	namespace gui {

class ToolTip;



/**
 * �c�[���o�[�B
 *
 * �c�[���o�[��ɑ��̃R���g���[����u���ɂ̓c�[���o�[��e�R���g���[���Ƃ��č쐬���A
 * bounds() ��u�������Z�p���[�^�� ToolBar::Item::bounds() �ɐݒ肵�Ă��Ηǂ��B
 * 
 * TB_SETANCHORHIGHLIGHT �͌��ʂ��m�F�ł����B
 * TB_SETCOLORSCHEME �� Visual Style �L�����ɂ͖����Ȃ̂Ŏ��������B
 * TB_GETITEMDROPDOWNRECT �� MSDN �ł� XP �ȍ~�ƂȂ��Ă��邪�w�b�_�t�@�C�����ł� Vista �ȍ~�ƂȂ��Ă���B
 * TBSTATE_ELLIPSES �͎w�肵�Ă����Ȃ��Ă�������̏ȗ��L�����\�������ׁA���ʕs���B
 * TBSTYLE_TRANSPARENT �͓��삹���BVisual Style �����A�ォ��X�^�C���ύX�ł��_���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"ToolBar Sample");

	typedef PopupMenu::ItemInfo MenuInfo;
	MenuInfo menuInfos[] = {
		MenuInfo(L"�h���b�v�_�E��0"),
		MenuInfo(L"�h���b�v�_�E��1"),
		MenuInfo(L"�h���b�v�_�E��2"),
	};
	PopupMenu dropDown(menuInfos);

	typedef ToolBar::ItemInfo Info;
	Info infos[] = {
		Info(ImageList::StandardImage::cut, L"�؂���", [&] (ToolBar::Click& ) {
			MsgBox::show(L"�؂�����");
		}),
		Info(ImageList::StandardImage::copy, L"�R�s�[", [&] (ToolBar::Click& ) {
			MsgBox::show(L"�R�s�[����");
		}),
		Info(ImageList::StandardImage::paste, L"�\��t��", [&] (ToolBar::Click& ) {
			MsgBox::show(L"�\��t����");
		}),
		Info(ImageList::StandardImage::properties, L"�v���p�e�B", ToolBar::ItemStyle::dropDownButton, [&] (ToolBar::Click& e) {
			if (e.dropDown()) {
				dropDown.show(frame, e.item().bounds().bottomLeft());
			} else {
				MsgBox::show(L"�v���p�e�B");
			}
		})
	};
	ImageList imageList(ImageList::SystemResource::largeStandardImages);
	ToolBar tool(frame, 0, 0, 0, 0, imageList, infos);

	frame.runMessageLoop();
 * </code></pre>
 */
class ToolBar : public Control {
public:
	typedef ::_IMAGELIST* HIMAGELIST;
	typedef ::balor::graphics::ImageList ImageList;


	///	���ڂ̃X�^�C���B
	struct ItemStyle {
		enum _enum {
			button         = 0x0000, /// ���ʂ̃{�^���B
			separator      = 0x0001, /// �{�^�����m�̋�؂�B
			checkBox       = 0x0002, /// �g�O���{�^���B
			radioButton    = 0x0006, /// ���W�I�{�^���B
			dropDown       = 0x0088, /// �h���b�v�_�E���B
			dropDownButton = 0x0008, /// �{�^���ƃh���b�v�_�E���B���̃{�^����ǉ�����ƃc�[���o�[�̏c�����傫���Ȃ�B
		};
		BALOR_NAMED_ENUM_MEMBERS(ItemStyle);
	};


	class ItemInfo;
	struct ItemTipPopup;
	struct Click;


	/// ���ځBToolBar::operator[] �Ŏ擾�ł���B
	class Item {
	public:
		Item(HWND ownerHandle, int index);
		/// ���ڏ��𔽉f�B
		Item& operator=(const ItemInfo& itemInfo);

		/// ���ڂ̕��𕶎���̕��ɍ��킹�邩�ǂ����BToolTip::bottomText() �� true �̏ꍇ�̂ݗL���Bfalse �̏ꍇ�͍ő啝�œ��ꂳ���B
		bool autoSize() const;
		void autoSize(bool value);
		/// ���ڂ̃N���C�A���g���W�̈�B
		Rectangle bounds() const;
		/// �g�O���ŉ����ꂽ��Ԃ��ǂ����B
		bool checked() const;
		void checked(bool value);
		/// �������Ԃ��ǂ����B
		bool enabled() const;
		void enabled(bool value);
		/// �A�C�R���̉摜���X�g�iToolBar::imageList()�j�̃C���f�b�N�X�B-1 �Ȃ�\�����Ȃ��B
		/// style() �� ToolBar::ItemStyle::separator �̏ꍇ�̓Z�p���[�^�̃s�N�Z�����ɂȂ�B�ʖ��� separatorSize() �֐����g���Ɨǂ��B
		int imageIndex() const;
		void imageIndex(int value);
		/// ���ڂ̃C���f�b�N�X�B
		int index() const;
		/// ������� & ����ʏ������邩�ǂ����B��������c�[���`�b�v�ɕ\������ꍇ�͖����B
		bool noPrefix() const;
		void noPrefix(bool value);
		/// �{�^�����������C�x���g�B
		Listener<ToolBar::Click&>& onClick();
		/// ���ڂ̃c�[���`�b�v��\������C�x���g�B
		Listener<ToolBar::ItemTipPopup&>& onItemTipPopup();
		/// �c�[���o�[�̃n���h���B
		HWND ownerHandle() const;
		/// text() ���{�^���̉E�ɕ\�����邩�ǂ����Bfalse �̏ꍇ�� text() ���c�[���`�b�v������Ƃ���B
		/// ToolTip::bottomText() �� false �̏ꍇ�̂ݗL���B
		bool rightText() const;
		void rightText(bool value);
		/// �{�^������������Ԃ��ǂ����B
		bool pushed() const;
		/// �Z�p���[�^�̃s�N�Z�����Bwrap() �� true �̏ꍇ�͏c�����̑傫���B
		/// style() �� ToolBar::ItemStyle::separator �ȊO�̏ꍇ�̓A�C�R���̉摜���X�g�̃C���f�b�N�X�ɂȂ�B�ʖ��� imageIndex() �֐����g���Ɨǂ��B
		int separatorSize() const;
		void separatorSize(int value);
		/// ���ڂ̃X�^�C���B
		ToolBar::ItemStyle style() const;
		void style(ToolBar::ItemStyle value);
		/// ���ڂ̃c�[���`�b�v������BToolTip::bottomText() �� true �̏ꍇ�̓{�^�������ɕ\�������B�����ł͂Ȃ� rightText() �� true �̏ꍇ�̓{�^���̉E�ɕ\�������B
		/// ���ڕ\�����c�[���`�b�v��������\���������ꍇ�� onItemTipPopup() �C�x���g����������B
		String text() const;
		void text(StringRange value);
		/// �\�����邩�ǂ����B�B
		bool visible() const;
		void visible(bool value);
		/// ���ڂ̃s�N�Z�����B�����񂪕\������Ă���ꍇ�iToolBar::bottomText() �� true ���A�܂��� ToolBar::bottomText() �� false ���� rightText() �� true �̏ꍇ�j�̂ݕύX�ł���B
		/// �Z�p���[�^�̑傫����ύX����ꍇ�� separatorSize() ���g�p���Ȃ��Əc�����̑傫�����ς��Ȃ��B
		int width() const;
		void width(int value);
		/// ���̍��ڂ�����s���邩�ǂ����B
		bool wrap() const;
		void wrap(bool value);

	private:
		HWND _ownerHandle;
		int _index;
	};


	/// ���ڏ��\���́B�����������Ńc�[���o�[�͈�ؑ��삵�Ȃ��BToolBar::itemInfos �֐����Ŏg�p����B
	/// �f�t�H���g�R���X�g���N�^�ō쐬����ƃZ�p���[�^�ɂȂ�B
	class ItemInfo {
	public:
		/// �Z�p���[�^�Ƃ��č쐬�B
		ItemInfo();
		ItemInfo(ItemInfo&& value);
		/// ���ڏ��̎擾�B
		ItemInfo(const Item& item);
		/// �摜�C���f�b�N�X�A������A�N���b�N�C�x���g���畁�ʂ̃{�^���Ƃ��č쐬�B
		explicit ItemInfo(int imageIndex, String text = String(), Listener<ToolBar::Click&> onClick = Listener<ToolBar::Click&>());
		/// �摜�C���f�b�N�X�A������A���ڃX�^�C���A�N���b�N�C�x���g����쐬�B
		ItemInfo(int imageIndex, String text, ToolBar::ItemStyle style, Listener<ToolBar::Click&> onClick);
		ItemInfo& operator=(ItemInfo&& value);

		/// ���ڂ̕��𕶎���̕��ɍ��킹�邩�ǂ����BToolTip::bottomText() �� true �̏ꍇ�̂ݗL���Bfalse �̏ꍇ�͍ő啝�œ��ꂳ���B�����l�� false�B
		bool autoSize() const;
		void autoSize(bool value);
		/// �g�O���ŉ����ꂽ��Ԃ��ǂ����B
		bool checked() const;
		void checked(bool value);
		/// �������Ԃ��ǂ����B
		bool enabled() const;
		void enabled(bool value);
		/// �A�C�R���̉摜���X�g�iToolBar::imageList()�j�̃C���f�b�N�X�B-1 �Ȃ�\�����Ȃ��B
		/// style() �� ToolBar::ItemStyle::separator �̏ꍇ�̓Z�p���[�^�̃s�N�Z�����ɂȂ�B�ʖ��� separatorSize() �֐����g���Ɨǂ��B
		int imageIndex() const;
		void imageIndex(int value);
		/// ������� & ����ʏ������邩�ǂ����B��������c�[���`�b�v�ɕ\������ꍇ�͖����B�����l�� false�B
		bool noPrefix() const;
		void noPrefix(bool value);
		/// �{�^�����������C�x���g�B
		Listener<ToolBar::Click&>& onClick();
		const Listener<ToolBar::Click&>& onClick() const;
		/// ���ڂ̃c�[���`�b�v��\������C�x���g�B
		Listener<ToolBar::ItemTipPopup&>& onItemTipPopup();
		const Listener<ToolBar::ItemTipPopup&>& onItemTipPopup() const;
		/// text() ���{�^���̉E�ɕ\�����邩�ǂ����Bfalse �̏ꍇ�� text() ���c�[���`�b�v������Ƃ���B�����l�� false�B
		/// ToolTip::bottomText() �� false �̏ꍇ�̂ݗL���B
		bool rightText() const;
		void rightText(bool value);
		/// �Z�p���[�^�̃s�N�Z�����B0 �̏ꍇ�̓f�t�H���g�̑傫���Bwrap() �� true �̏ꍇ�͏c�����̑傫���B
		/// style() �� ToolBar::ItemStyle::separator �ȊO�̏ꍇ�̓A�C�R���̉摜���X�g�̃C���f�b�N�X�ɂȂ�B�ʖ��� imageIndex() �֐����g���Ɨǂ��B
		int separatorSize() const;
		void separatorSize(int value);
		/// ���ڂ̃X�^�C���B
		ToolBar::ItemStyle style() const;
		void style(ToolBar::ItemStyle value);
		/// ���ڂ̃c�[���`�b�v������BToolTip::bottomText() �� true �̏ꍇ�̓{�^�������ɕ\�������B�����ł͂Ȃ� rightText() �� true �̏ꍇ�̓{�^���̉E�ɕ\�������B
		/// ���ڕ\�����c�[���`�b�v��������\���������ꍇ�� onItemTipPopup() �C�x���g����������B
		const String& text() const;
		void text(String value);
		/// �\�����邩�ǂ����B�����l�� true�B
		bool visible() const;
		void visible(bool value);
		/// ���̍��ڂ�����s���邩�ǂ����B�����l�� false�B
		bool wrap() const;
		void wrap(bool value);

	private:
		friend ToolBar;
		friend Item;

		int _imageIndex;
		String _text;
		int _itemDataStyle;
		int _itemDataState;
		Listener<ToolBar::Click&> _onClick;
		Listener<ToolBar::ItemTipPopup&> _onItemTipPopup;
	};


	/// �c�[���o�[�̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<ToolBar, Control::Event> Event;


	/// ���ڂŔ�������C�x���g�B
	struct ItemEvent : public Event {
		ItemEvent(ToolBar& sender, int itemIndex);

		/// �C�x���g�̔����������ځB
		ToolBar::Item item() const;

	private:
		int _itemIndex;
	};


	/// �{�^�����N���b�N�����C�x���g�B
	struct Click : public ItemEvent {
		Click(ToolBar& sender, int itemIndex, bool dropDown);

		/// �h���b�v�_�E�����N���b�N�������ǂ����B
		bool dropDown() const;

	private:
		bool _dropDown;
	};


	/// ���ڂ̃c�[���`�b�v��\������C�x���g�B
	struct ItemTipPopup : public ItemEvent {
		ItemTipPopup(ToolBar& sender, int itemIndex, wchar_t* buffer, int bufferSize);

		/// �\�����镶�����ݒ肷��B������̒����ɂ͏���������Đ؂�̂Ă���B
		void setText(StringRange value);

	private:
		wchar_t* _buffer;
		int _bufferSize;
	};


public:
	/// �k���|�C���^�ō쐬�B
	ToolBar();
	ToolBar(ToolBar&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫������쐬�B
	ToolBar(Control& parent, int x, int y, int width, int height, HIMAGELIST imageList);
	/// �e�A�ʒu�A�傫���A���ڏ��z�񂩂�쐬�B
	ToolBar(Control& parent, int x, int y, int width, int height, HIMAGELIST imageList, ArrayRange<const ItemInfo> itemInfos);
	virtual ~ToolBar();
	ToolBar& operator=(ToolBar&& value);

public:
	/// ���ڂ�ǉ�����B
	void add(const ItemInfo& itemInfo);
	/// �{�^���̉����ɕ������\�����邩�ǂ����Btrue �̏ꍇ�� ToolTip::Item::text() ���{�^���̉����ɏ�ɕ\�������B
	/// �c�[���`�b�v��\������ꍇ�� ToolTip::Item::onItemTipPopup �C�x���g����������K�v������B
	/// false �̏ꍇ�̓{�^�������ɕ\�����ꂸ�A�c�[���`�b�v������Ƃ��ĕ\�������B������ ToolTip::Item::rightText() �� true �̏ꍇ�̓{�^���̉E���ɕ����񂪕\�������B
	/// �����l�� false�B
	bool bottomText() const;
	void bottomText(bool value);
	/// ���ڂ�S�č폜����B
	void clear();
	/// ���ڐ��B
	int count() const;
	/// ���͂��󂯕t���Ȃ����ڂ̉摜���X�g�B�ݒ肵�Ȃ��ꍇ�� imageList() �̉摜���O���C�X�P�[���ŕ\�������B�����l�� nullptr�BToolBar �͉摜���X�g�̃n���h����j�����Ȃ��B
	ImageList disabledImageList() const;
	void disabledImageList(HIMAGELIST value);
	/// �㕔��2�s�N�Z�����̃n�C���C�g�\�������邩�ǂ����B�����l�� false�B
	bool divider() const;
	void divider(bool value);
	/// �R���g���[���̋��E���̎�ށB�����l�� Control::Edge::none�B
	Control::Edge edge() const;
	void edge(Control::Edge value);
	/// ���ڂ��폜����B
	void erase(int index);
	/// �t�H�[�J�X����Ă��鍀�ڃC���f�b�N�X�B�����ꍇ�� -1�B
	int focusedIndex() const;
	void focusedIndex(int value);
	/// �w�肵���N���C�A���g���W�ɂ��鍀�ڂ̃C���f�b�N�X���擾����B�Z�p���[�^�̃C���f�b�N�X�͕Ԃ��Ȃ��B������Ȃ��ꍇ�͕�����Ԃ��B
	int getIndexAt(const Point& point) const;
	int getIndexAt(int x, int y) const;
	/// �K�؂ȃR���g���[���T�C�Y�B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// �����ł��\��������Ȃ����ڂ��B�����ǂ����B�����l�� false�B
	bool hideClippedItems() const;
	void hideClippedItems(bool value);
	/// �}�E�X�J�[�\���̉��̍��ڂ̉摜���X�g�B�ݒ肵�Ȃ��ꍇ�� imageList() �̉摜���\�������B�����l�� nullptr�BToolBar �͉摜���X�g�̃n���h����j�����Ȃ��B
	ImageList hotImageList() const;
	void hotImageList(HIMAGELIST value);
	/// ���ڂ̉摜���X�g�BToolBar �͉摜���X�g�̃n���h����j�����Ȃ��B
	ImageList imageList() const;
	void imageList(HIMAGELIST value);
	/// �ŏ��̍��ڂ̉������̃s�N�Z���ʒu�B�����l�͂����炭�O�B
	void indent(int value);
	/// ���ڂ�}������B
	void insert(int index, const ItemInfo& itemInfo);
	/// ���ڂ̏��z����ꊇ�Ŏ擾�A�ݒ肷��B
	std::vector<ToolBar::ItemInfo> itemInfos() const;
	void itemInfos(ArrayRange<const ToolBar::ItemInfo> value);
	/// ���ڑS�Ă��܂ޑ傫���B
	Size itemsSize() const;
	/// ���ڂɕ\������c�[���`�b�v�R���g���[���̎Q�ƁB�K�v�Ȑݒ���s������j�����Ă��ǂ����ꕔ�ݒ��C�x���g�͔j������Ɩ����ɂȂ�B������x ToolBar �����䂵�Ă���̂œ��삵�Ȃ��ݒ������B
	ToolTip itemTip();
	/// �N���C�A���g�̈�̑傫������R���g���[���̑傫�������߂�B
	virtual Size sizeFromClientSize(const Size& clientSize) const;
	/// �w�i�������邩�ǂ����B����ł͐e�� Rebar �ł���ꍇ�ɂ̂ݓ�����B�����l�� false�B
	bool transparent() const;
	void transparent(bool value);
	/// �c�[���o�[���c�\���ɂ��邩�ǂ����Btrue �̏ꍇ�A�Z�p���[�^�̕\�����c�����ɂȂ�S�Ă̍��ڂ� ToolBar::Item::wrap() �� true �ɐݒ肷��B
	bool vertical() const;
	void vertical(bool value);
	/// �c�[���o�[�̕��ō��ڂ�\��������Ȃ����ɉ��s���邩�ǂ����Bvertical() �Ɠ����� true �ɂ��邱�Ƃ͂ł��Ȃ��B�����l�� false�B
	/// ���s�̓���Z�p���[�^�͏c�\���ɂȂ�B���s�̈ʒu�̓V�X�e���Ōv�Z�����B
	/// bottomText() �� false �̏ꍇ�A���W�I�{�^������\��������Ȃ��Ă����s���Ȃ��ꍇ������B
	bool wrappable() const;
	void wrappable(bool value);

public:
	/// index �Ԗڂ̍��ځB
	ToolBar::Item operator[](int index);
	const ToolBar::Item operator[](int index) const;

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	struct ItemListener {
		ItemListener();
		ItemListener(const ItemInfo& info);

		Listener<ToolBar::Click&> onClick;
		Listener<ToolBar::ItemTipPopup&> onItemTipPopup;
	};
	std::vector<ItemListener> _itemListeners;
};



	}
}