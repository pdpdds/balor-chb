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
 * �^�u�R���g���[���B
 *
 * �}�E�X�C�x���g�̓N���b�N�ł���^�u�����ł̂ݔ�������B
 *
 * TCS_BUTTONS�ATCS_FLATBUTTONS�ATCS_VERTICAL�ATCS_RIGHT �� Visual Style �������ɂȂ�̂ŃT�|�[�g���Ȃ��B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Tab Sample");

	Panel page0(frame, 0, 0, 0, 0);
	Button button0(page0, 20, 10, 0, 0, L"button0", [&] (Button::Click& ) {
		MsgBox::show(L"button0");
	});
	Button button1(page0, 20, 50, 0, 0, L"button1", [&] (Button::Click& ) {
		MsgBox::show(L"button1");
	});
	Panel page1(frame, 0, 0, 0, 0);
	CheckBox check(page1, 20, 10, 0, 0, L"check");

	typedef Tab::ItemInfo Info;
	Info infos[] = {
		Info(L"�^�u0", page0),
		Info(L"�^�u1", page1),
		Info(L"�^�u2"),
	};
	Tab tab(frame, 20, 10, 400, 300, infos);

	frame.runMessageLoop();
 * </code></pre>
 */
class Tab : public Control {
public:
	typedef ::_IMAGELIST* HIMAGELIST;
	typedef ::balor::graphics::ImageList ImageList;


	/// �^�u�̃X�^�C���B
	struct Style {
		enum _enum {
			singleline      = 0x0000, /// �^�u�͈��ŕ\�������B�͂ݏo��ꍇ�̓X�N���[���ł���B
			multiline       = 0x0200, /// �^�u���͂ݏo��ꍇ�͕�����ŕ\�������B���̏ꍇ�^�u�̕��̓R���g���[���̕��ɍ��킹����B
			multilineScroll = 0x0201, /// �^�u���͂ݏo��ꍇ�͕�����ŕ\������A�I������Ă��Ȃ��񂪉��Ɉړ�����B
		};
		BALOR_NAMED_ENUM_MEMBERS(Style);
	};


	/// ���ڂ̕�����̔z�u�B
	struct TextAlign {
		enum _enum {
			center    = 0x0000, /// ���������B
			iconLeft  = 0x0010, /// �A�C�R�������������A������͒��������B
			left      = 0x0020, /// �������B
		};
		BALOR_NAMED_ENUM_MEMBERS(TextAlign);
	};


	class ItemInfo;

	/// ���ځBTab::operator[] �Ŏ擾�ł���B
	class Item {
	public:
		Item(HWND ownerHandle, int index);
		/// ���ڏ��𔽉f�B
		Item& operator=(const ItemInfo& itemInfo);

		/// ���ڂ̃N���C�A���g���W�̈�B
		Rectangle bounds() const;
		/// �A�C�R���̉摜���X�g�iTab::imageList()�j�̃C���f�b�N�X�B
		int imageIndex() const;
		void imageIndex(int value);
		/// �^�u�C���f�b�N�X�B
		int index() const;
		/// �^�u�R���g���[���̃n���h���B
		HWND ownerHandle() const;
		/// �^�u���N���b�N�������ɕ\������R���g���[���BTab �̎q�E�C���h�E�ɂ���B�w�肵�Ȃ��ꍇ�� nullptr�B
		Control* page() const;
		void page(Control* value);
		/// ���ڂ̕�����B
		String text() const;
		void text(StringRange value);

	private:
		HWND _ownerHandle;
		int _index;
	};


	/// ���ڏ��\���́B�����������Ń^�u�R���g���[���͈�ؑ��삵�Ȃ��BTab::itemInfos �֐����Ŏg�p����B
	class ItemInfo {
	public:
		ItemInfo();
		ItemInfo(ItemInfo&& value);
		/// ���ڏ��̎擾�B
		ItemInfo(const Item& item);
		/// ������ƃA�C�R���摜�C���f�b�N�X����쐬�B
		explicit ItemInfo(String text, int imageIndex = -1);
		/// ������ƃy�[�W�R���g���[���ƃA�C�R���摜�C���f�b�N�X����쐬�B
		ItemInfo(String text, const Control& page, int imageIndex = -1);
		ItemInfo& operator=(ItemInfo&& value);

		/// �A�C�R���̉摜���X�g�iTab::imageList()�j�̃C���f�b�N�X�B
		int imageIndex() const;
		void imageIndex(int value);
		/// �^�u���N���b�N�������ɕ\������R���g���[���B�w�肵�Ȃ��ꍇ�� nullptr�B
		Control* page() const;
		void page(Control* value);
		/// ���ڂ̕�����B
		const String& text() const;
		void text(String value);

	private:
		String _text;
		int _imageIndex;
		HWND _page;
	};



	/// �^�u�R���g���[���̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<Tab, Control::Event> Event;


	/// ���ڂɊւ���C�x���g�B
	struct ItemEvent : public Event {
		ItemEvent(Tab& sender, int itemIndex);

		/// �C�x���g�̔����������ځB
		Tab::Item item();

	private:
		int _itemIndex;
	};


	typedef Event ItemSelect;


	/// ���ڂ�I������C�x���g�B
	struct ItemSelecting : public Event {
		ItemSelecting(Tab& sender);

		/// �I�����L�����Z�����邩�ǂ����B�����l�� false�B
		bool cancel() const;
		void cancel(bool value);

	private:
		bool _cancel;
	};


	/// ���ڂ̃c�[���`�b�v��\������C�x���g�B
	struct ItemTipPopup : public ItemEvent {
		ItemTipPopup(Tab& sender, int itemIndex, String& text);

		/// �C�x���g�̔����������ځB
		void setText(String value);

	private:
		String& _text;
	};


public:
	/// �k���|�C���^�ō쐬�B
	Tab();
	Tab(Tab&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫������쐬�B
	Tab(Control& parent, int x, int y, int width, int height, Tab::Style style = Tab::Style::singleline);
	/// �e�A�ʒu�A�傫���A���ڏ��z�񂩂�쐬�B
	Tab(Control& parent, int x, int y, int width, int height, ArrayRange<const Tab::ItemInfo> itemInfos, Tab::Style style = Tab::Style::singleline);
	virtual ~Tab();
	Tab& operator=(Tab&& value);

public:
	/// ���ڂ�ǉ�����B
	void add(const ItemInfo& itemInfo);
	/// �^�u���R���g���[���̉����ɕ\�����邩�ǂ����B�����l�� false�B
	bool bottomItems() const;
	void bottomItems(bool value);
	/// ���ڂ�S�č폜����B
	void clear();
	/// ���ڐ��B
	int count() const;
	/// Tab::Item::page() �̕\���͈͂̃N���C�A���g���W�̈�B�^�u�R���g���[���̋��E�ƌ����ɂ͈�v���Ȃ��悤�����e�[�}�ɂ���ė̈悪�ω�����ׂ�������Ȃ��B
	virtual Rectangle displayRectangle() const;
	/// ���ڂ��폜����B
	void erase(int index);
	/// �w�肵���N���C�A���g���W�ɂ��鍀�ڂ̃C���f�b�N�X���擾����B�����ꍇ�� -1�B
	int getIndexAt(const Point& point) const;
	int getIndexAt(int x, int y) const;
	/// �A�C�R���̉摜���X�g�BTab �͉摜���X�g�̃n���h����j�����Ȃ��B�����l�̓k���n���h���̉摜���X�g�B
	ImageList imageList() const;
	void imageList(HIMAGELIST value);
	/// ���ڂ�}������B
	void insert(int index, const ItemInfo& itemInfo);
	/// ���ڂ̏��z����ꊇ�Ŏ擾�A�ݒ肷��B
	std::vector<Tab::ItemInfo> itemInfos() const;
	void itemInfos(ArrayRange<const Tab::ItemInfo> value);
	/// ���ڂ̕�����ƊO�g�̗]���s�N�Z�����B
	void itemPadding(const Size& value);
	/// ���ڂ̃s�N�Z���T�C�Y��ύX����BitemWidthFixed() �� false �̏ꍇ�͍����̂ݕύX����B
	void itemSize(const Size& value);
	void itemSize(int width, int height);
	/// ���ڂ��Ƃɕ\������c�[���`�b�v�R���g���[���̎Q�ƁB�K�v�Ȑݒ���s������j�����Ă��ǂ����ꕔ�ݒ��C�x���g�͔j������Ɩ����ɂȂ�B������x Tab �����䂵�Ă���̂œ��삵�Ȃ��ݒ������B
	ToolTip itemTip();
	/// ���ڂ̕����Œ�ɂ��邩�ǂ����Bfalse �̏ꍇ�͕�����̒����ɍ��킹��BitemSize() �֐��ŌŒ蕝���w��ł���B�����l�� false�B
	bool itemWidthFixed() const;
	void itemWidthFixed(bool value);
	/// ���ڂ̍ŏ��s�N�Z�����B-1 ���w�肷��ƃf�t�H���g�̕��ɖ߂��B
	void minItemWidth(int value);
	/// ���ڂ�I�������C�x���g�B
	Listener<Tab::ItemSelect&>& onItemSelect();
	/// ���ڂ�I������C�x���g�B
	Listener<Tab::ItemSelecting&>& onItemSelecting();
	/// ���ڂ̃c�[���`�b�v��\������C�x���g�B
	Listener<Tab::ItemTipPopup&>& onItemTipPopup();
	/// Tab::Item::page() �����ڂ̑傫���ɍ��킹�ă��T�C�Y����B
	void resizeItemPages();
	/// �^�u�̗񐔁B
	int rowCount() const;
	/// �I������Ă��鍀�ڃC���f�b�N�X�B�����ꍇ�� -1�B
	/// �^�u�y�[�W��\�������܂ܑ��̃R���g���[�����t�H�[�J�X�𓾂���̂őI������Ă��Ă��t�H�[�J�X�𓾂Ă���Ƃ͌���Ȃ��B
	int selectedIndex() const;
	void selectedIndex(int value);
	/// �^�u�̃X�^�C���B
	Tab::Style style() const;
	/// ���ڂ̕�����̔z�u�BitemWidthFixed() �� true �̏ꍇ�̂ݕύX�ł���B�����l�� Tab::TextAlign::center�B
	Tab::TextAlign textAlign() const;
	void textAlign(Tab::TextAlign value);

public:
	/// index �Ԗڂ̍��ځB
	Tab::Item operator[](int index);

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	String _temporaryText;
	Listener<Tab::ItemSelect&> _onItemSelect;
	Listener<Tab::ItemSelecting&> _onItemSelecting;
	Listener<Tab::ItemTipPopup&> _onItemTipPopup;
};



	}
}