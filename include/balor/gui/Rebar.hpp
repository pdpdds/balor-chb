#pragma once

#include <vector>

#include <balor/gui/Control.hpp>

struct HBITMAP__;

namespace balor {
	namespace graphics {
		class Bitmap;
	}
}


namespace balor {
	namespace gui {



/**
 * ���o�[�R���g���[���B
 *
 * RB_MOVEBAND �͓��삹���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Rebar sample");

	ImageList imageList(ImageList::SystemResource::largeStandardImages);
	ToolBar::ButtonInfo toolItems[] = {
		ToolBar::ButtonInfo(ImageList::StandardImage::cut, L"�؂���", [&] (ToolBar::Click& ) {
			MsgBox::show(L"�؂�����");
		}),
		ToolBar::ButtonInfo(ImageList::StandardImage::copy, L"�R�s�[", [&] (ToolBar::Click& ) {
			MsgBox::show(L"�R�s�[����");
		}),
		ToolBar::ButtonInfo(ImageList::StandardImage::paste, L"�\��t��", [&] (ToolBar::Click& ) {
			MsgBox::show(L"�\��t����");
		}),
	};
	ToolBar tool(frame, 0, 0, 0, 0, imageList, toolItems);
	tool.size(tool.buttonsSize()); // �{�^���̑傫���ɍ��킹��
	tool.transparent(true);

	const wchar_t* comboItems[] = {
		L"�����S",
		L"������",
		L"�X�C�J",
	};
	ComboBox combo(frame, 0, 0, 0, 0, comboItems);
	combo.selectedIndex(0);

	Edit edit(frame, 0, 0, 0, 0, 10);
	edit.size(edit.size().width, tool.size().height);

	Rebar::ItemInfo rebarItems[] = {
		Rebar::ItemInfo(tool),
		Rebar::ItemInfo(combo, 0, L"�ʕ�"),
		Rebar::ItemInfo(edit),
		Rebar::ItemInfo(),
	};
	Rebar rebar(frame, rebarItems);
	frame.onResized() = [&] (Frame::Resized& ) {
		rebar.size(frame.clientSize().width, rebar.size().height);
		rebar.invalidate();
	};

	frame.runMessageLoop();
 * </code></pre>
 *
 * <h3>�E�V�F�u�����T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Rebar Chevron sample");

	std::vector<Menu::ItemInfo> menuItems;
	std::vector<Bitmap> menuBitmaps;
	std::vector<ToolBar::ButtonInfo> toolItems;
	ImageList imageList(ImageList::SystemResource::largeStandardImages);
	for (auto i = 0, end = imageList.count(); i < end; ++i) {
		String text = String(L"����") + i;
		menuBitmaps.push_back(imageList.getIcon(i).bitmap());
		Menu::ItemInfo menuItem(text);
		menuItem.uncheckedMark(menuBitmaps.back());
		menuItems.push_back(menuItem);
		toolItems.push_back(ToolBar::ButtonInfo(i, text));
	}
	ToolBar tool(frame, 0, 0, 0, 0, imageList, toolItems);
	tool.size(tool.buttonsSize());
	tool.transparent(true);
	tool.hideClippedButtons(true); // �{�^���������ł��B���Ȃ�\�����Ȃ��B

	Rebar rebar(frame);
	Rebar::ItemInfo rebarItem(tool);
	rebarItem.controlResizable(true); // �R���g���[�������T�C�Y�\�ɂ���B
	rebarItem.minControlSize(0, tool.size().height); // ���O�܂Ń��T�C�Y��������B
	rebarItem.displayWidth(tool.size().width); // �ŏ��̕��ȉ��Ȃ�V�F�u������\������B
	rebar.add(rebarItem);
	PopupMenu chevronMenu;
	rebar[0].onChevronClick() = [&] (Rebar::ChevronClick& e) {
		for (auto i = 0, end = tool.count(); i < end; ++i) {
			if (tool.bounds().width < tool[i].bounds().right()) {
				chevronMenu = PopupMenu(ArrayRange<const Menu::ItemInfo>(menuItems.data() + i, end - i));
				chevronMenu.show(frame, e.chevronBounds().bottomLeft());
				break;
			}
		}
	};

	frame.onResized() = [&] (Frame::Resized& ) {
		rebar.size(frame.clientSize().width, rebar.size().height);
		rebar.invalidate();
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class Rebar : public Control {
public:
	typedef ::_IMAGELIST* HIMAGELIST;
	typedef ::balor::graphics::Bitmap Bitmap;


	class ItemInfo;
	struct ItemEvent;
	struct ChevronClick;

	/// ���o�[�R���g���[����̃o���h���ځBRebar::operator[] �Ŏ擾�ł���B
	class Item {
	public:
		Item(HWND ownerHandle, int index);
		/// ���ڏ��𔽉f�B
		Item& operator=(const ItemInfo& itemInfo);

		/// ���ڂ̔w�i�r�b�g�}�b�v�B�^�C���\�������B
		Bitmap bitmap() const;
		void bitmap(HBITMAP value);
		/// ���ڂ̔w�i�r�b�g�}�b�v�̕\�����_�����ڂ̍��W�ɂ�炸�Œ肷�邩�ǂ����B
		bool bitmapOriginFixed() const;
		void bitmapOriginFixed(bool value);
		/// ���ڂ̃N���C�A���g���W�̈�B
		Rectangle bounds() const;
		/// ���ڂ����s���邩�ǂ����B���̍��ڂ��S�Ĉꏏ�ɉ��s�����̂� index() �͕ω����Ȃ��B
		bool lineBreak() const;
		void lineBreak(bool value);
		/// ���ڏ�ɒu���R���g���[���B�u���Ȃ��ꍇ�� nullptr�B�ύX����O�� minControlSize() �� control �̑傫���ɐݒ肵���ق����ǂ��B
		Control* control() const;
		void control(Control* value);
		/// ���ڏ�ɒu���R���g���[���̏㉺�ɋ󔒂�����ǂ����B
		bool controlEdge() const;
		void controlEdge(bool value);
		/// ���ڏ�ɒu���R���g���[�������ڂ̕��ɍ��킹�đ傫����ς��邩�ǂ����B
		bool controlResizable() const;
		void controlResizable(bool value);
		/// ���ڂ̕\���\�ȃs�N�Z�����Bwidth() �����̕������ł���ꍇ�A�V�F�u������\������B�����l�� 0�B
		int displayWidth() const;
		void displayWidth(int value);
		/// ���ڃC���f�b�N�X�B
		int index() const;
		/// ���ڂ��ő剻����B
		void maximize();
		/// ���[�U�����ڂ����T�C�Y����ꍇ�̍ŏ��̑傫���B
		Size minControlSize() const;
		void minControlSize(const Size& value);
		void minControlSize(int width, int height);
		/// ���ڂ��ŏ�������B
		void minimize();
		/// �V�F�u�������N���b�N�����C�x���g�B
		Listener<Rebar::ChevronClick&>& onChevronClick();
		/// ���o�[�R���g���[���̃n���h���B
		HWND ownerHandle() const;
		/// ���ڏ�̑傫����ύX�ł��邩�ǂ����Bfalse �̏ꍇ�̓O���b�v���\������Ȃ��B
		bool resizable() const;
		void resizable(bool value);
		/// ���ڂ̕�����B
		String text() const;
		void text(StringRange value);
		/// ���ڂ̃s�N�Z�����B
		int width() const;
		void width(int value);

	private:
		HWND _ownerHandle;
		int _index;
	};


	/// ���ڏ��\���́B�����������Ń��o�[�R���g���[���͈�ؑ��삵�Ȃ��BRebar::itemInfos �֐����Ŏg�p����B
	class ItemInfo {
	public:
		ItemInfo();
		ItemInfo(ItemInfo&& value);
		/// ���ڏ��̎擾�B
		ItemInfo(const Item& item);
		/// ���ڏ�ɒu���R���g���[������쐬�B
		explicit ItemInfo(Control& control, int width = 0, String text = L"");
		ItemInfo& operator=(ItemInfo&& value);

		/// ���ڂ̔w�i�r�b�g�}�b�v�B�^�C���\�������B�����l�̓k���n���h���� Bitmap�B
		Bitmap bitmap() const;
		void bitmap(HBITMAP value);
		/// ���ڂ̔w�i�r�b�g�}�b�v�̕\�����_�����ڂ̍��W�ɂ�炸�Œ肷�邩�ǂ����B�����l�� false�B
		bool bitmapOriginFixed() const;
		void bitmapOriginFixed(bool value);
		/// ���ڂ����s���邩�ǂ����B�����l�� false�B
		bool lineBreak() const;
		void lineBreak(bool value);
		/// ���ڏ�ɒu���R���g���[���B�u���Ȃ��ꍇ�� nullptr�B
		Control* control() const;
		void control(Control* value);
		/// ���ڏ�ɒu���R���g���[���̏㉺�ɋ󔒂�����ǂ����B�����l�� true�B
		bool controlEdge() const;
		void controlEdge(bool value);
		/// ���ڏ�ɒu���R���g���[�������ڂ̕��ɍ��킹�đ傫����ς��邩�ǂ����B�����l�� false�B
		bool controlResizable() const;
		void controlResizable(bool value);
		/// ���ڂ̕\���\�ȃs�N�Z�����Bwidth() �����̕������ł���ꍇ�A�V�F�u������\������B�����l�� 0�B
		int displayWidth() const;
		void displayWidth(int value);
		/// ���ڏ�̃R���g���[�������T�C�Y����ꍇ�̍ŏ��̑傫���B
		Size minControlSize() const;
		void minControlSize(const Size& value);
		void minControlSize(int width, int height);
		/// �V�F�u�������N���b�N�����C�x���g�B
		Listener<Rebar::ChevronClick&>& onChevronClick();
		const Listener<Rebar::ChevronClick&>& onChevronClick() const;
		/// ���ڏ�̑傫����ύX�ł��邩�ǂ����Bfalse �̏ꍇ�̓O���b�v���\������Ȃ��B�����l�� true�B
		bool resizable() const;
		void resizable(bool value);
		/// ���ڂ̕�����B�����l�͋󕶎���B
		const String& text() const;
		void text(String value);
		/// ���ڂ̃s�N�Z�����B0 �̏ꍇ�͍ŏ��̑傫���ɂȂ�B
		int width() const;
		void width(int value);

	private:
		friend Rebar;
		friend Item;

		HWND _control;
		bool _controlResizable;
		HBITMAP _bitmap;
		int _style;
		String _text;
		int _width;
		int _displayWidth;
		Size _minControlSize;
		Listener<Rebar::ChevronClick&> _onChevronClick;
	};



	/// ���o�[�R���g���[���̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<Rebar, Control::Event> Event;

	typedef Event Resize;


	/// ���ڂɊւ���C�x���g�B
	struct ItemEvent : public Event {
		ItemEvent(Rebar& sender, int itemIndex);

		/// �C�x���g�̔����������ځB
		Rebar::Item item();

	private:
		int _itemIndex;
	};


	/// �V�F�u�������������C�x���g�B
	struct ChevronClick : public ItemEvent {
		ChevronClick(Rebar& sender, int itemIndex, const Rectangle& bounds);

		/// �V�F�u�����̃N���C�A���g���W�̈�B
		const Rectangle& chevronBounds() const;

	private:
		Rectangle _chevronBounds;
	};


public:
	/// �k���|�C���^�ō쐬�B
	Rebar();
	Rebar(Rebar&& value, bool checkSlicing = true);
	/// �e����쐬�B�e�̏�[�ɐe�̕��ɂ��킹���傫���ō쐬����B
	Rebar(Control& parent);
	/// �e�ƍ��ڏ��z�񂩂�쐬�B�e�̏�[�ɐe�̕��ɂ��킹���傫���ō쐬����B
	Rebar(Control& parent, ArrayRange<const Rebar::ItemInfo> itemInfos);
	virtual ~Rebar();
	Rebar& operator=(Rebar&& value);

public:
	/// ���ڂ�ǉ�����B
	void add(const ItemInfo& itemInfo);
	/// ���ڂ�S�č폜����B
	void clear();
	/// ���ڐ��B
	int count() const;
	/// ���ڂ̋��E���_�u���N���b�N������ő剻/�ŏ������邩�ǂ����Bfalse �̏ꍇ�̓V���O���N���b�N�B�����l�� false�B
	bool doubleClickToggle() const;
	void doubleClickToggle(bool value);
	/// ���ڂ��폜����B
	void erase(int index);
	/// �w�肵���N���C�A���g���W�ɂ��鍀�ڂ̃C���f�b�N�X���擾����B�����ꍇ�� -1�B
	int getIndexAt(const Point& point) const;
	int getIndexAt(int x, int y) const;
	/// ���ڂ�}������B
	void insert(int index, const ItemInfo& itemInfo);
	/// ���ڂ̏��z����ꊇ�Ŏ擾�A�ݒ肷��B
	std::vector<Rebar::ItemInfo> itemInfos() const;
	void itemInfos(ArrayRange<const Rebar::ItemInfo> value);
	/// ���ړ��m�̋��E�ɐ����������ǂ����B�����l�� true�B
	bool itemBorderLines() const;
	void itemBorderLines(bool value);
	/// ���ڂ̏��Ԃ��Œ肳��邩�ǂ����B�����l�� false�B
	bool itemHeightVariable() const;
	void itemHeightVariable(bool value);
	/// ���ڂ̏��Ԃ��Œ肳��邩�ǂ����B�����l�� false�B
	bool itemOrderFixed() const;
	void itemOrderFixed(bool value);
	/// �R���g���[���̑傫�����ς�����C�x���g�B
	Listener<Rebar::Resize&>& onResize();
	/// ���ڂ̗񐔁B
	int rowCount() const;

public:
	/// index �Ԗڂ̍��ځB���Ԃ͒ǉ��������Ƃ͌��炸���[�U�̃h���b�O����ɂ���ĕω�����B
	Rebar::Item operator[](int index);

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	Listener<Rebar::Resize&> _onResize;
};



	}
}