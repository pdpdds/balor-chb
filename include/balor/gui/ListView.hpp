#pragma once

#include <vector>

#include <balor/graphics/Color.hpp>
#include <balor/gui/Control.hpp>
#include <balor/StringRangeArray.hpp>

struct _IMAGELIST;
struct tagNMLVCUSTOMDRAW;

namespace std {
	namespace tr1 {
template<typename T> class function;
	}
}

namespace balor {
	namespace graphics {
class ImageList;
	}
}


namespace balor {
	namespace gui {

class Edit;
class ToolTip;



/**
 * ���X�g�r���[�B
 * 
 * �}�E�X���{�^�����E�{�^�����������ꍇ�AonMouseDown �C�x���g�̓{�^���𗣂������ɔ������AonMouseUp �C�x���g�͔������Ȃ��B
 * ����� onItemClick �C�x���g�� onItemRightClick �C�x���g���g�p�ł���B
 * onDrag �C�x���g�͂��܂��E���Ȃ��BonDrag �̑���� onItemDrag �C�x���g���g�p�ł���B
 * �O���[�v�͖������B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"ListView Sample");

	typedef ListView::ColumnInfo Column;
	Column columns[] = {
		Column(L"�ʕ���"),
		Column(L"�F"),
		Column(L"�傫��")
	};
	typedef ListView::ItemInfo Item;
	const wchar_t* item0Texts[] = {L"�u�h�E", L"��", L"��"};
	const wchar_t* item1Texts[] = {L"������", L"��", L"��"};
	const wchar_t* item2Texts[] = {L"�X�C�J", L"��", L"��"};
	Item items[] = {
		Item(item0Texts),
		Item(item1Texts),
		Item(item2Texts)
	};
	ListView list(frame, 20, 10, 0, 0, columns, items);
	list.fullRowSelect(true);
 
	frame.runMessageLoop();
 * </code></pre>
 */
class ListView : public Control {
public:
	typedef ::_IMAGELIST* HIMAGELIST;
	typedef ::balor::graphics::ImageList ImageList;

	/// ���ڂ̕�����̏I�[�������܂߂��ő咷�B
	static const int maxTextLength = 512;


	/// ���ڂ̕�����̔z�u�B
	struct Align {
		enum _enum {
			left   = 0x0000, /// �������B
			right  = 0x0001, /// �E�����B
			center = 0x0002, /// ���������B
		};
		BALOR_NAMED_ENUM_MEMBERS(Align);
	};


	/// ���ڂ̕����B
	struct ItemPortion {
		enum _enum {
			whole        = 0x0000, /// ���ڑS�́B
			icon         = 0x0001, /// �A�C�R�������B
			text         = 0x0002, /// �����񕔕��B
			selectBounds = 0x0003, /// �I���\�����BfullRowSelect() �ɂ���Ĕ͈͂��ς��B
		};
		BALOR_NAMED_ENUM_MEMBERS(ItemPortion);
	};


	/// �R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none          = 0     , 
			checkBoxes    = 0x0004, /// ���ڂ��ƂɃ`�F�b�N�{�b�N�X��\������BstateImageList() �𑀍삵�ă`�F�b�N�摜��ύX�ł���B�摜��ǉ�����ƃ`�F�b�N��Ԃ�������B
			noHeaderClick = 0x8000, /// �w�b�_���{�^���̂悤�ɃN���b�N�ł��Ȃ��悤�ɂ���B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


	/// �\���X�^�C���B
	struct Style {
		enum _enum {
			largeIcon = 0x0000, /// �傫�ȃA�C�R���\���B
			details   = 0x0001, /// �ڍו\���B
			smallIcon = 0x0002, /// �����ȃA�C�R���\���B
			list      = 0x0003, /// �ꗗ�\���B
			tile      = 0x0004, /// ���ׂĕ\���BEnableVisualStyle.hpp �̃C���N���[�h���K�v�B
		};
		BALOR_NAMED_ENUM_MEMBERS(Style);
	};



	class ColumnInfo;

	/// �c�̍s�BListView::getColumn �֐��Ŏ擾�ł���B
	class Column {
	public:
		Column(HWND ownerHandle, int index);
		/// �c�̍s�̏�񔽉f�B
		Column& operator=(const ColumnInfo& columnInfo);

		/// �c�̍s�̕�����z�u�B�ŏ��̍s�� ListView::Align::left �ŌŒ肳���B
		ListView::Align align() const;
		void align(ListView::Align value);
		/// �����w�b�_�[�̕����񕝂ɍ��킹��B���ڂ̕����񕝈ȉ��ɂ͂Ȃ�Ȃ��B
		void fitWidthToHeader();
		/// �������ڂ̕����񕝂ɍ��킹��B
		void fitWidthToItem();
		/// �w�b�_�̉摜���X�g�iListView::smallImageList()�j�̃C���f�b�N�X�B-1 �Ȃ�\�����Ȃ��B
		int imageIndex() const;
		void imageIndex(int value);
		/// �c�̍s�̃C���f�b�N�X�B
		int index() const;
		/// �\�������B
		int order() const;
		void order(int value);
		/// ���X�g�r���[�̃n���h���B
		HWND ownerHandle() const;
		/// �摜�𕶎���̉E�ɕ\�����邩�ǂ����B�ŏ��̍s�� false �ŌŒ肳���B
		bool rightImage() const;
		void rightImage(bool value);
		/// �I������Ă���悤�ɕ\�����邩�ǂ����B���̊֐��̎g�p�ɂ� EnableVisualStyle.hpp �̃C���N���[�h���K�v�B
		bool selected() const;
		void selected(bool value);
		/// �w�b�_�̕�����B
		String text() const;
		void text(StringRange value);
		/// �c�̍s�̕��B
		int width() const;
		void width(int value);

	private:
		HWND _ownerHandle;
		int _index;
	};


	/// �c�̍s�̏��\���́B�����������Ń��X�g�r���[�͈�ؑ��삵�Ȃ��BListView::columnInfos �֐����Ŏg�p����B
	class ColumnInfo {
	public:
		ColumnInfo(ColumnInfo&& value);
		/// �c�̍s�̏��擾�B
		ColumnInfo(const Column& column);
		/// �S�v�f����쐬�B�����͓����̊֐����Q�ƁB
		explicit ColumnInfo(String text = L"", int width = 0, ListView::Align align = Align::left, int imageIndex = -1, bool rightImage = false, int order = -1);
		ColumnInfo& operator=(ColumnInfo&& value);

		/// �c�̍s�̕�����z�u�B�ŏ��̍s�� ListView::Align::left �ŌŒ肳���B
		ListView::Align align() const;
		void align(ListView::Align value);
		/// �w�b�_�̉摜���X�g�iListView::smallImageList�j�̃C���f�b�N�X�B-1 �Ȃ�\�����Ȃ��B
		int imageIndex() const;
		void imageIndex(int value);
		/// �\�������B-1 �Ȃ�ǉ��������B
		int order() const;
		void order(int value);
		/// �摜�𕶎���̉E�ɕ\�����邩�ǂ����B�ŏ��̍s�� false �ŌŒ肳���B
		bool rightImage() const;
		void rightImage(bool value);
		/// �w�b�_�̕�����B
		const String& text() const;
		void text(String value);
		/// �c�̍s�̕��B
		int width() const;
		void width(int value);

	private:
		String _text;
		int _width;
		ListView::Align _align;
		int _imageIndex;
		bool _rightImage;
		int _order;
	};


	class ItemInfo;

	/// ���ځBListView::operator[] �Ŏ擾�ł���B
	class Item {
	public:
		Item(HWND ownerHandle, int index);
		/// ���ڏ��𔽉f�B
		Item& operator=(const ItemInfo& itemInfo);

		/// �`�F�b�N�{�b�N�X���`�F�b�N����Ă��邩�ǂ����B�`�F�b�N�̃I���ƃI�t�� state() �� 1 �� 0 �ɊY������B
		bool checked() const;
		void checked(bool value);
		/// �؂��肳�ꂽ��Ԃ��ǂ����B�A�C�R���������\�������B
		bool cut() const;
		void cut(bool value);
		/// ���ڂ�������悤�ɃX�N���[������B
		void ensureVisible();
		/// ���X�g�r���[���ł̍��ڂ̑S�̂܂��͕����̈�B
		Rectangle getBounds(ListView::ItemPortion portion = ListView::ItemPortion::whole) const;
		/// ���X�g�r���[���ł̃T�u���ڂ̗̈�BcolumnIndex �� 0 �̏ꍇ�͍��ڑS�̗̂̈�B
		Rectangle getSubBounds(int columnIndex) const;
		/// ��������擾����B
		String getText(int columnIndex) const;
		void getTextToBuffer(StringBuffer& buffer, int columnIndex) const;
		/// �n�C���C�g�\�����ǂ����B�I����ԂƓ����\���B
		bool highlight() const;
		void highlight(bool value);
		/// �A�C�R���̉摜���X�g�iListView::smallImageList() �܂��� ListView::largeImageList()�j�̃C���f�b�N�X�B
		int imageIndex() const;
		void imageIndex(int value);
		/// �C���f���g�B1 �ɂ���ԃA�C�R���̕��قǃC���f���g����B
		int indent() const;
		void indent(int value);
		/// ���ڂ̃C���f�b�N�X�B
		int index() const;
		/// ���X�g�r���[�̃n���h���B
		HWND ownerHandle() const;
		/// ���ڂ̈ʒu�B
		Point position() const;
		void position(const Point& value);
		void position(int x, int y);
		/// �I������Ă��邩�ǂ����B
		bool selected() const;
		void selected(bool value);
		/// �������ݒ肷��BListView::maxTextLength �����ȏ�͐ݒ�ł��Ȃ��B
		void setText(int columnIndex, StringRange text);
		/// ��ԁB��ԉ摜���X�g�iListView::stateImageList()�j�̃C���f�b�N�X�ŁA-1 �Ȃ�\�����Ȃ��B
		int state() const;
		void state(int value);
		/// �O�Ԗڂ̕�����B
		String text() const;
		void text(StringRange value);
		/// ������z��B
		std::vector<String> texts() const;
		void texts(StringRangeArray value);
		/// ���[�U��`�̃f�[�^�B�擾����ꍇ�� UniqueAny �̒��g�̌^���w�肷��B
		template<typename T> T userData() {
			auto data = _userData();
			return any_cast<T>(*reinterpret_cast<UniqueAny*>(&data));
		}
		template<typename T> T userData() const {
			auto data = _userData();
			return any_cast<T>(*reinterpret_cast<const UniqueAny*>(&data));
		}
		void userData(UniqueAny&& value);
		bool userDataIsEmpty() const;

	private:
		void* _userData() const;

		HWND _ownerHandle;
		int _index;
	};


	/// ���ڏ��\���́B�����������Ń��X�g�r���[�͈�ؑ��삵�Ȃ��BListView::itemInfos �֐����Ŏg�p����B
	class ItemInfo {
	public:
		ItemInfo(ItemInfo&& value);
		/// ���ڏ��̎擾�B
		ItemInfo(const Item& item);
		/// ������ƃA�C�R���摜�C���f�b�N�X������쐬�B
		explicit ItemInfo(String text = L"", int imageIndex = 0, int state = -1, int indent = 0);
		/// ������z��ƃA�C�R���摜�C���f�b�N�X������쐬�B
		explicit ItemInfo(StringRangeArray texts, int imageIndex = 0, int state = -1, int indent = 0);
		ItemInfo& operator=(ItemInfo&& value);

		/// �؂��肳�ꂽ��Ԃ��ǂ����B�A�C�R���������\�������B�����l�� false�B
		bool cut() const;
		void cut(bool value);
		/// �n�C���C�g�\�����ǂ����B�I����ԂƓ����\���B�����l�� false�B
		bool highlight() const;
		void highlight(bool value);
		/// �A�C�R���̉摜���X�g�iListView::smallImageList() �܂��� ListView::largeImageList()�j�̃C���f�b�N�X�B
		int imageIndex() const;
		void imageIndex(int value);
		/// �C���f���g�B1 �ɂ���ԃA�C�R���̕��قǃC���f���g����B
		int indent() const;
		void indent(int value);
		/// �I������Ă��邩�ǂ����B
		bool selected() const;
		void selected(bool value);
		/// ��ԁB��ԉ摜���X�g�iListView::stateImageList()�j�̃C���f�b�N�X�ŁA-1 �Ȃ�\�����Ȃ��B
		int state() const;
		void state(int value);
		/// ���ڂ̕�����B
		String text() const;
		void text(String value);
		/// ���ڂ̕�����z��B
		std::vector<String>& texts();
		const std::vector<String>& texts() const;
		void texts(StringRangeArray value);

	private:
		friend ListView;
		friend Item;

		std::vector<String> _texts;
		int _imageIndex;
		int _itemDataState;
		int _indent;
	};



	/// ���X�g�r���[�̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<ListView, Control::Event> Event;


	/// �w�b�_���N���b�N�����C�x���g�B
	struct HeaderClick : public Event {
		HeaderClick(ListView& sender, int columnIndex);

		/// �N���b�N���ꂽ�c�̍s�C���f�b�N�X�B
		int columnIndex() const;

	private:
		int _columnIndex;
	};


	/// ���ڂɊւ���C�x���g�B
	struct ItemEvent : public Event {
		ItemEvent(ListView& sender, int itemIndex);

		/// �C�x���g�̔����������ځB
		ListView::Item item();

	private:
		int _itemIndex;
	};


	/// ���ڂ��N���b�N�����C�x���g�B
	struct ItemClick : public ItemEvent {
		ItemClick(ListView& sender, int itemIndex, int columnIndex, const Point& occurredPoint);

		/// �c�̍s�̃C���f�b�N�X�B
		int columnIndex() const;
		/// �C�x���g�̔����������W�B
		const Point& occurredPoint() const;

	private:
		int _columnIndex;
		Point _occurredPoint;
	};

	typedef ItemClick ItemDoubleClick;
	typedef ItemClick ItemRightClick;


	/// ���ڂ��ω������C�x���g�B
	struct ItemChange : public ItemEvent {
		ItemChange(ListView& sender, int itemIndex, int oldStates, int newStates);

		/// �V�����t�H�[�J�X��ԁB
		bool newFocused() const;
		/// �V�����I����ԁB
		bool newSelected() const;
		/// �V������ԁB
		int newState() const;
		/// �Â��t�H�[�J�X��ԁB
		bool oldFocused() const;
		/// �Â��I����ԁB
		bool oldSelected() const;
		/// �Â���ԁB
		int oldState() const;

	private:
		int _oldStates;
		int _newStates;
	};


	/// ���ڂ��ω����悤�Ƃ��Ă���C�x���g�B
	struct ItemChanging : public ItemChange {
		ItemChanging(ListView& sender, int itemIndex, int oldStates, int newStates);

		/// �ω����L�����Z�����邩�ǂ����B
		bool cancel() const;
		void cancel(bool value);

	private:
		bool _cancel;
	};


	/// ���ڂ��}�E�X�E�{�^���܂��͍��{�^���Ńh���b�O�����C�x���g�B�h���b�O���J�n����͈͂͑I���ł���͈͂Ɠ����B
	struct ItemDrag : public ItemEvent {
		ItemDrag(ListView& sender, int itemIndex, bool rButton);

		/// �E�{�^���h���b�O���ǂ����B
		bool rButton() const;

	private:
		bool _rButton;
	};


	/// ���ڂ�`�悷�钼�O�̃C�x���g�B�I���s�̐F��ς���ɂ� selected() �� false �ɐݒ肷��B
	struct ItemPrePaint : public Event {
		ItemPrePaint(ListView& sender, ::tagNMLVCUSTOMDRAW* info);

		/// ���ڂ̔w�i�̐F�BListView::brush �֐��ŉ摜�u���V���w�肵���ꍇ�͖����Bselected() �� true �̏ꍇ�������B
		Color backColor() const;
		void backColor(const Color& value);
		/// ���ڂ̃N���C�A���g���W�̈�B
		Rectangle bounds() const;
		/// �c�̍s�̃C���f�b�N�X�B
		int columnIndex() const;
		/// �t�H�[�J�X������悤�ɕ`�悷�邩�ǂ����B
		bool focused() const;
		void focused(bool value);
		/// ���ڂ̕�����̃t�H���g�B
		Font font() const;
		void font(HFONT value);
		/// �C�x���g�̔����������ځB
		ListView::Item item();
		/// �I�����Ă���悤�ɕ`�悷�邩�ǂ����B�I�����ڂ̐F��ς���ɂ͂���� false �ɂ��Ȃ���΂Ȃ�Ȃ��B
		bool selected() const;
		void selected(bool value);
		/// ���ڂ̕�����̐F�B
		Color textColor() const;
		void textColor(const Color& value);

	private:
		friend ListView;

		::tagNMLVCUSTOMDRAW* _info;
		bool _fontChanged;
	};


	/// ���ڂ̃c�[���`�b�v���\�������C�x���g�B
	struct ItemTipPopup : public ItemEvent {
		ItemTipPopup(ListView& sender, int itemIndex, wchar_t* buffer, int bufferSize);

		/// �\�����镶�����ݒ肷��B������̒����ɂ͏���������Đ؂�̂Ă���B
		void setText(StringRange value);

	private:
		wchar_t* _buffer;
		int _bufferSize;
	};


	/// ���ڂ̕�����ҏW���I����Ĕ��f���钼�O�̃C�x���g�B
	struct TextEdit : public ItemEvent {
		TextEdit(ListView& sender, int itemIndex, String itemText);

		/// �ҏW���ʂ𔽉f���Ȃ����ǂ����B
		bool cancel() const;
		void cancel(bool value);
		/// �ҏW�e�L�X�g�B
		const String& itemText() const;
		void itemText(String value);

	private:
		String _itemText;
		bool _cancel;
	};


	/// ���ڂ̕�����ҏW���n�܂钼�O�̃C�x���g�B
	struct TextEditing : public TextEdit {
		TextEditing(ListView& sender, int itemIndex, String itemText);

		/// �ҏW������G�f�B�b�g�R���g���[���̎Q�ƁB�K�v�Ȑݒ���s������j�����Ă��ǂ����ꕔ�ݒ��C�x���g�͔j������Ɩ����ɂȂ�B
		/// ������x ListView �����䂵�Ă���̂œ��삵�Ȃ��ݒ������B
		Edit edit();
	};


	/// �q�b�g�e�X�g�̌��ʁB
	struct HitTestInfo {
		HitTestInfo(int itemIndex, int columnIndex, int flags);

		/// �c�̍s�̃C���f�b�N�X�B�������ĂȂ��ꍇ�� -1�B
		int columnIndex() const;
		/// ���ڃC���f�b�N�X�B�������ĂȂ��ꍇ�� -1�B
		int itemIndex() const;
		/// �A�C�R���摜�̏�B
		bool onImage() const;
		/// ��ԉ摜�̏�B
		bool onStateImage() const;
		/// ������̏�B
		bool onText() const;

	private:
		int _itemIndex;
		int _columnIndex;
		int _flags;
	};


public:
	/// �k���|�C���^�ō쐬�B
	ListView();
	ListView(ListView&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫������쐬�B
	ListView(Control& parent, int x, int y, int width, int height, ListView::Style style = Style::details, ListView::Options options = Options::none);
	/// �e�A�ʒu�A�傫���A���ڏ��z�񂩂�쐬�B
	ListView(Control& parent, int x, int y, int width, int height, ArrayRange<const ItemInfo> itemInfos, ListView::Style style = Style::details, ListView::Options options = Options::none);
	/// �e�A�ʒu�A�傫���A�c�̍s���z��A���ڏ��z�񂩂�쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	ListView(Control& parent, int x, int y, int width, int height, ArrayRange<const ColumnInfo> columnInfos, ArrayRange<const ItemInfo> itemInfos, ListView::Style style = Style::details, ListView::Options options = Options::none);
	virtual ~ListView();
	ListView& operator=(ListView&& value);

public:
	/// ���ڂ�ǉ�����B
	void add(const ItemInfo& itemInfo);
	/// �t�H�[�J�X���O��Ă��I����Ԃ�\�����邩�ǂ����B�����l�� false�B
	bool alwaysSelected() const;
	void alwaysSelected(bool value);
	/// �A�C�R���𐮗񂷂�Bstyle() �� ListView::Style::largeIcon, smallIcon, tile �̏ꍇ�̂ݗL���BsnapToGrid �� true �̏ꍇ�͍��ڂ���ԋ߂����Ԋu�̏��ڂ̒��Ɉړ�����B
	void arrange(bool snapToGrid = false);
	/// �A�C�R�����������񂷂邩�ǂ����B�����l�� true�B
	bool autoArrange() const;
	void autoArrange(bool value);
	/// ���ڂ̕�����̕ҏW���n�߂�B�����I�Ƀt�H�[�J�X�𓾂�B
	void beginEdit(int index);
	/// �w�i�u���V�B�u���V�n���h���͎Q�Ƃ����̂Ŕj�����Ȃ��悤���ӁB�n�b�`�u���V�͎g���Ȃ��BMSDN �ɂ� COM �̏��������K�v�Ƃ��邪���������Ȃ��Ƃ������Ă���B
	using Control::brush;
	virtual void brush(HBRUSH value);
	/// �w�i�u���V�̌��_�B�ݒ�ɂ� EnableVisualStyle.hpp �̃C���N���[�h���K�v�B
	using Control::brushOrigin;
	virtual void brushOrigin(const Point& value);
	/// ���ڂ�S�č폜����B
	void clear();
	/// �c�̍s�̐��B
	int columnCount() const;
	/// �c�̍s�̏��z����ꊇ�Ŏ擾�A�ݒ肷��BColumnInfo::width() �� 0 �̏ꍇ�� Column::fitWidthToHeader �֐��ŕ������߂�B
	std::vector<ListView::ColumnInfo> columnInfos() const;
	void columnInfos(ArrayRange<const ListView::ColumnInfo> value);
	/// ���ڐ��B
	int count() const;
	/// ���X�g�r���[���ɕ\���ł��鍀�ڐ��Bstyle() �� ListView::Style::details �� list �̏ꍇ�̂ݗL���B
	int countPerPage() const;
	/// �R���g���[���̋��E���̎�ށB�����l�� Control::Edge::client�B
	Control::Edge edge() const;
	void edge(Control::Edge value);
	/// ���ڂ̕�����̕ҏW���I������B
	void endEdit();
	/// ���ڂ��폜����B
	void erase(int index);
	/// �w�肵���C���f�b�N�X�ȍ~�Ŏw�肵��������������ڂ�������B�T�u���ڂ̕�����͌�������Ȃ��B������Ȃ��ꍇ�� -1�B
	int findIndex(StringRange text, int startIndex = 0, bool prefixSearch = false) const;
	/// �t�H�[�J�X����Ă��鍀�ڃC���f�b�N�X�B�����ꍇ�� -1�B
	int focusedIndex() const;
	void focusedIndex(int value);
	/// ���̍s��S�đI����Ԃɂ��邩�ǂ����B�����l�� false�B
	bool fullRowSelect() const;
	void fullRowSelect(bool value);
	/// �c�̍s���擾����B
	ListView::Column getColumn(int index);
	/// �w�肵���N���C�A���g���W�̃q�b�g�e�X�g���s���ď����擾����B
	ListView::HitTestInfo getHitTestInfo(const Point& point) const;
	ListView::HitTestInfo getHitTestInfo(int x, int y) const;
	/// �w�肵���N���C�A���g���W�ɂ��鍀�ڂ̃C���f�b�N�X���擾����B�����ꍇ�� -1�B
	int getIndexAt(const Point& point) const;
	int getIndexAt(int x, int y) const;
	/// �K�؂ȃR���g���[���T�C�Y�Bfont(), count() ���̒l�ɂ���čœK�ȃT�C�Y��Ԃ��Bstyle() �� ListView::Style::details �̏ꍇ�̂ݐ��m�ȃT�C�Y���v�Z�ł���B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// �w�肵���C���f�b�N�X�ȍ~�őI������Ă��鍀�ڂ̃C���f�b�N�X���擾����B
	/// �����ɑO��擾�����C���f�b�N�X + 1 ���w�肷��Ύ��̃C���f�b�N�X����������B������Ȃ��ꍇ�� -1 ��Ԃ��B
	int getSelectedIndex(int startIndex = 0) const;
	/// ���ڋ��E����\�����邩�ǂ����B�����l�� false�B
	bool gridLines() const;
	void gridLines(bool value);
	/// �w�b�_���h���b�O���h���b�v�ňړ��ł��邩�ǂ����B�����l�� false�B
	bool headerDragDrop() const;
	void headerDragDrop(bool value);
	/// �w�b�_��\�����邩�ǂ����B�����l�� true�B
	bool headerVisible() const;
	void headerVisible(bool value);
	/// ���ڂɃJ�[�\�������킹��ƃJ�[�\���� Cursor::hand() �ɂȂ��ĕ�����ɃA���_�[���C�����\������邩�ǂ����B�����l�� false�B
	bool hotTracking() const;
	void hotTracking(bool value);
	/// ���ڂɃJ�[�\�������킹�Ă��΂炭����ƍ��ڂ��I������邩�ǂ����B�����l�� false�B
	bool hotTrackSelection() const;
	void hotTrackSelection(bool value);
	/// ���ړ��m�̋����BSize(-1, -1) ���w�肷��ƃf�t�H���g�ɖ߂�Bstyle() �� ListView::Style::largeIcon �̏ꍇ�̂ݗL���B�c�����ς��Ȃ��͗l�B
	Size iconSpacing() const;
	void iconSpacing(const Size& value);
	/// ���ڂ�}������B
	void insert(int index, const ItemInfo& itemInfo);
	/// ���ڂ̏��z����ꊇ�Ŏ擾�A�ݒ肷��B
	std::vector<ListView::ItemInfo> itemInfos() const;
	void itemInfos(ArrayRange<const ListView::ItemInfo> value);
	/// ���ڂ��Ƃɕ\������c�[���`�b�v�R���g���[���̎Q�ƁB�K�v�Ȑݒ���s������j�����Ă��ǂ����ꕔ�ݒ��C�x���g�͔j������Ɩ����ɂȂ�B������x ListView �����䂵�Ă���̂œ��삵�Ȃ��ݒ������B
	ToolTip itemTip();
	/// ���ڂ��ƂɃc�[���`�b�v��\�����邩�ǂ����BonItemTipPopup() �C�x���g�ŕ\�����镶������w�肷��B�����l�� false�B
	bool itemTipEnabled() const;
	void itemTipEnabled(bool value);
	/// �傫���A�C�R���̉摜���X�g�BListView �͉摜���X�g�̃n���h����j�����Ȃ��B
	ImageList largeImageList() const;
	void largeImageList(HIMAGELIST value);
	/// �A�C�R�������ォ�牺�ɐ��񂷂邩�ǂ����Bfalse �̏ꍇ�͍��ォ��E�ɐ��񂷂�B�����l�� false�B
	bool leftArrange() const;
	void leftArrange(bool value);
	/// �A�C�e���𕡐��I���ł��邩�ǂ����B�����l�� true�B
	bool multiselect() const;
	void multiselect(bool value);
	/// �w�b�_���N���b�N�����C�x���g�B
	Listener<ListView::HeaderClick&>& onHeaderClick();
	/// ���ڂ��ω������C�x���g�B
	Listener<ListView::ItemChange&>& onItemChange();
	/// ���ڂ��ω����悤�Ƃ��Ă���C�x���g�B
	Listener<ListView::ItemChanging&>& onItemChanging();
	/// ���ڂ��N���b�N�����C�x���g�B
	Listener<ListView::ItemClick&>& onItemClick();
	/// ���ڂ��_�u���N���b�N�����C�x���g�B
	Listener<ListView::ItemDoubleClick&>& onItemDoubleClick();
	/// ���ڂ��}�E�X���{�^���܂��͉E�{�^���Ńh���b�O�����C�x���g�B
	Listener<ListView::ItemDrag&>& onItemDrag();
	/// ���ڂ�`�悷�钼�O�̃C�x���g�B
	Listener<ListView::ItemPrePaint&>& onItemPrePaint();
	/// ���ڂ��E�N���b�N�����C�x���g�B
	Listener<ListView::ItemRightClick&>& onItemRightClick();
	/// ���ڂ̃c�[���`�b�v��\������C�x���g�B
	Listener<ListView::ItemTipPopup&>& onItemTipPopup();
	/// ���ڂ̕�����ҏW���I����Ĕ��f���钼�O�̃C�x���g�B
	Listener<ListView::TextEdit&>& onTextEdit();
	/// ���ڂ̕�����ҏW���n�܂钼�O�̃C�x���g�B
	Listener<ListView::TextEditing&>& onTextEditing();
	///	�R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B
	ListView::Options options() const;
	/// ���ڂ�\�����؂�Ȃ����ɃX�N���[���o�[��\�����邩�ǂ����B�����l�� true�B
	/// ���ځA�ʒu�A�T�C�Y�� style ��ݒ肷��O�ɐݒ肵�Ȃ��Ƃ��܂����삵�Ȃ��B
	bool scrollable() const;
	void scrollable(bool value);
	/// �I������Ă��鍀�ڂ̐��B
	int selectedCount() const;
	/// �������A�C�R���̉摜���X�g�BListView �͉摜���X�g�̃n���h����j�����Ȃ��B
	ImageList smallImageList() const;
	void smallImageList(HIMAGELIST value);
	/// ���ڂ𕶎��񏇂Ƀ\�[�g����B
	void sort(bool ascending = true, int columnIndex = 0);
	/// ��r�֐��Ń\�[�g����B��r�֐��̖߂�l�� String::compare �Ɠ��l�ŁA�����͔�r�����̍��ڃC���f�b�N�X�B
	void sort(const std::tr1::function<int (int, int)>& compareFunction);
	/// ��r�֐��Ń\�[�g����B��r�֐��̖߂�l�� String::compare �Ɠ��l�ŁA�����͔�r�����̍��ڕ�����B
	void sort(const std::tr1::function<int (const String&, const String&)>& compareFunction, int columnIndex);
	/// ��ԃA�C�R���̉摜���X�g�BListView �͉摜���X�g�̃n���h����j�����Ȃ��B
	/// ���[�U�w��̉摜���X�g�̓`�F�b�N�{�b�N�X�Ƌ����ł��Ȃ��B�`�F�b�N�{�b�N�X�̕\����ς������ꍇ�� checkBoxes() �� true �ɂ�����Ԃ� stateImageList() �֐��Ŏ擾�����摜���X�g�𑀍삷��B
	ImageList stateImageList() const;
	void stateImageList(HIMAGELIST value);
	/// �\���X�^�C���B���̊֐��̎g�p�ɂ� EnableVisualStyle.hpp �̃C���N���[�h���K�v�B�����l�� ListView::Style::details�B
	ListView::Style style() const;
	void style(ListView::Style value);
	/// �����F�B
	Color textColor() const;
	void textColor(const Color& value);
	/// �N���b�N�ō��ڂ̕������ҏW�ł��邩�ǂ����B�ҏW�ł���͍̂��ڂ̍ŏ��̕�����̂݁B�����l�� false�B
	bool textEditable() const;
	void textEditable(bool value);
	/// ���ڕ������\�����邩�ǂ����B��\���ɂȂ�̂� style() �� ListView::Style::largeIcon �܂��� smallIcon �̏ꍇ�̂݁B���̊֐��̎g�p�ɂ� EnableVisualStyle.hpp �̃C���N���[�h���K�v�B�����l�� true�B
	bool textVisible() const;
	void textVisible(bool value);
	/// �A�C�R���\���̍��ڂ̕����񂪒����ꍇ�ɉ��s���邩�ǂ����B�����l�� true�B
	bool textWrap() const;
	void textWrap(bool value);
	/// �ŏ��ɕ\������Ă��鍀�ڂ̃C���f�b�N�X�Bstyle() �� ListView::Style::details �� ListView::Style::list �̏ꍇ�̂ݗL���B
	int topIndex() const;
	void topIndex(int value);

public:
	/// index �Ԗڂ̍��ځB
	ListView::Item operator[](int index);

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	Listener<ListView::HeaderClick&> _onHeaderClick;
	Listener<ListView::ItemChange&> _onItemChange;
	Listener<ListView::ItemChanging&> _onItemChanging;
	Listener<ListView::ItemClick&> _onItemClick;
	Listener<ListView::ItemDoubleClick&> _onItemDoubleClick;
	Listener<ListView::ItemDrag&> _onItemDrag;
	Listener<ListView::ItemPrePaint&> _onItemPrePaint;
	Listener<ListView::ItemRightClick&> _onItemRightClick;
	Listener<ListView::ItemTipPopup&> _onItemTipPopup;
	Listener<ListView::TextEdit&> _onTextEdit;
	Listener<ListView::TextEditing&> _onTextEditing;
};



	}
}