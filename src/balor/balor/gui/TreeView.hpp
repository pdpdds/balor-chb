#pragma once

#include <vector>

#include <balor/gui/Control.hpp>
#include <balor/ArrayRange.hpp>

struct _IMAGELIST;
struct _TREEITEM;
struct tagNMTVCUSTOMDRAW;

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
 * �c���[�r���[�B
 *
 * �}�E�X���{�^�������ڏ�ŉ������ꍇ�AonMouseDown �C�x���g�̓{�^���𗣂������ɔ������AonMouseUp �C�x���g�͔������Ȃ��B����� onClick �C�x���g���g�p�ł���B
 * �}�E�X�E�{�^�����������ꍇ�AonMouseDonw �C�x���g�̓{�^���𗣂������ɔ������AonMouseUp �C�x���g�͔������Ȃ��B����� onRightClick �C�x���g���g�p�ł���B
 * onDrag �C�x���g�͂��܂��E���Ȃ��B����� onItemDrag �C�x���g���g�p�ł���B
 * �w�i���u���V�œh����@�͔���Ȃ������BWM_ERASEBKGND �ł͍��ڂ̔w�i��h��Ȃ��B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"TreeView Sample");

	typedef TreeView::ItemInfo Info;
	Info subInfos0[] = {
		Info(L"�T�u����00"),
		Info(L"�T�u����01")
	};
	Info subInfos1[] = {
		Info(L"�T�u����10"),
		Info(L"�T�u����11"),
		Info(L"�T�u����12")
	};
	Info infos[] = {
		Info(L"����0", subInfos0),
		Info(L"����1", subInfos1),
		Info(L"����2")
	};
	TreeView tree(frame, 20, 10, 0, 0, infos);

	frame.runMessageLoop();
 * </code></pre>
 */
class TreeView : public Control {
public:
	typedef ::_IMAGELIST* HIMAGELIST;
	typedef ::_TREEITEM* HTREEITEM;
	typedef ::balor::graphics::ImageList ImageList;

	/// ���ڂ̕�����̏I�[�������܂߂��ő咷�B
	static const int maxTextLength = 260;


	/// �R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none       = 0      ,
			checkBoxes = 0x0100L, // ���ڂ��ƂɃ`�F�b�N�{�b�N�X��\������BstateImageList() �𑀍삵�ă`�F�b�N�摜��ύX�ł���B�摜��ǉ�����ƃ`�F�b�N��Ԃ�������B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


	class ItemInfo;
	class ItemDescendantsIterator;


	/// ���ځBTreeView::root �֐�������擾�ł���B
	class Item {
	public:
		Item(HWND ownerHandle, HTREEITEM item);
		/// ���ڏ��𔽉f�B
		Item& operator=(const ItemInfo& itemInfo);

		/// �q���ڂ𖖔��ɒǉ�����B
		Item add(const ItemInfo& itemInfo);
		/// �Ō�̎q���ځB�����ꍇ�̓k���̍��ڂ�Ԃ��B
		Item back();
		const Item back() const;
		/// ������̕ҏW���n�߂�B�����I�Ƀt�H�[�J�X���ڂ��B
		void beginEdit();
		/// �����񂪑������ǂ����B
		bool bold() const;
		void bold(bool value);
		/// �c��[�r���[���ł̍��ڂ̗̈�B
		Rectangle bounds() const;
		/// �c��[�r���[���ł̎q���ڂ��܂ލ��ڂ̗̈�B
		Rectangle boundsWithChildren() const;
		/// �`�F�b�N�{�b�N�X���`�F�b�N����Ă��邩�ǂ����B�`�F�b�N�̃I���ƃI�t�� state() �� 1 �� 0 �ɊY������B
		bool checked() const;
		void checked(bool value);
		/// �S�Ă̎q���ڂ��폜����B
		void clear();
		/// �؂��肳�ꂽ��Ԃ��ǂ����B�A�C�R���������\�������B
		bool cut() const;
		void cut(bool value);
		/// ���ڂ̎q����񋓂���C�e���[�^�B
		TreeView::ItemDescendantsIterator descendantsBegin();
		/// ������̕ҏW���I����B
		void endEdit(bool cancel = false);
		/// ���ڂ�������悤�ɃX�N���[������B
		void ensureVisible();
		/// �q���ڂ��폜����B
		void erase(Item& item);
		/// ���̍��ڂ̎q���ڂ��\������Ă��邩�ǂ����B
		bool expanded() const;
		void expanded(bool value);
		/// �S�Ă̎q�����ڂ�\���܂��͔�\���ɂ���B
		void expandAll(bool value);
		/// �ŏ��̎q���ځB�����ꍇ�̓k���̍��ڂ�Ԃ��B
		Item front();
		const Item front() const;
		/// �n�C���C�g�\�����ǂ����B�I����ԂƓ����\���B
		bool highlight() const;
		void highlight(bool value);
		/// �A�C�R���̉摜���X�g�iTreeView::imageList()�j�̃C���f�b�N�X�B
		int imageIndex() const;
		void imageIndex(int value);
		/// �w�肵���q���ڂ̑O�Ɏq���ڂ�ǉ�����B
		Item insert(Item& nextItem, const ItemInfo& itemInfo);
		/// �q���ڂ̏��z����ꊇ�Ŏ擾�A�ݒ肷��B
		std::vector<TreeView::ItemInfo> itemInfos() const;
		void itemInfos(ArrayRange<const ItemInfo> value);
		/// ���̌Z�퍀�ځB�����ꍇ�̓k���̍��ڂ�Ԃ��B
		Item next();
		const Item next() const;
		/// ���̕\������Ă��鍀�ځB�����ꍇ�̓k���̍��ڂ�Ԃ��B
		Item nextVisible();
		const Item nextVisible() const;
		/// �c���[�r���[�̃n���h��
		HWND ownerHandle() const;
		/// �e���ځB���[�g���ڂ��ǂ����� ListView::root() �� == ��r���Ĕ��f�ł���B
		Item parent();
		const Item parent() const;
		/// �O�̌Z�퍀�ځB�����ꍇ�̓k���̍��ڂ�Ԃ��B
		Item prev();
		const Item prev() const;
		/// �O�̕\������Ă��鍀�ځB�����ꍇ�̓k���̍��ڂ�Ԃ��B
		Item prevVisible();
		const Item prevVisible() const;
		/// �I����ԃA�C�R���̉摜���X�g�iTreeView::imageList()�j�̃C���f�b�N�X�B
		int selectedImageIndex() const;
		void selectedImageIndex(int value);
		/// ��ԁB��ԉ摜���X�g�iTreeView::stateImageList()�j�̃C���f�b�N�X - 1 �ŁA-1 �Ȃ�\�����Ȃ��B
		int state() const;
		void state(int value);
		/// ���ڂ̕�����B
		String text() const;
		void text(StringRange value);
		void textToBuffer(StringBuffer& buffer) const;
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

	public:
		/// �A�C�e���n���h���ւ̎����ϊ��A null �`�F�b�N�A�������ڂ��ǂ����� == ��r�p�B
		operator HTREEITEM() const { return _item; }

	private:
		void* _userData() const;

		HWND _ownerHandle;
		HTREEITEM _item;
	};


	/// ���ڏ��\���́B�����������Ńc��[�r���[�͈�ؑ��삵�Ȃ��BTreeView::Item::itemInfos �֐����Ŏg�p����B
	class ItemInfo {
	public:
		ItemInfo(ItemInfo&& value);
		/// ���ڏ��̎擾�B
		ItemInfo(const Item& item);
		/// ������ƃA�C�R���摜�C���f�b�N�X������쐬�B
		explicit ItemInfo(String text, int imageIndex = 0, int selectedImageIndex = -1, int state = -1);
		/// ������Ǝq���ڏ��z��Ɖ摜�C���f�b�N�X������쐬�B
		ItemInfo(String text, ArrayRange<const ItemInfo> itemInfos, int imageIndex = 0, int selectedImageIndex = -1, int state = -1);
		ItemInfo& operator=(ItemInfo&& value);

		/// �����񂪑������ǂ����B
		bool bold() const;
		void bold(bool value);
		/// �؂��肳�ꂽ��Ԃ��ǂ����B�A�C�R���������\�������B
		bool cut() const;
		void cut(bool value);
		/// �n�C���C�g�\�����ǂ����B�I����ԂƓ����\���B
		bool highlight() const;
		void highlight(bool value);
		/// �A�C�R���̉摜���X�g�iTreeView::imageList()�j�̃C���f�b�N�X�B
		int imageIndex() const;
		void imageIndex(int value);
		/// �q���ڂ̏��\���̔z��B
		std::vector<TreeView::ItemInfo>& itemInfos();
		const std::vector<TreeView::ItemInfo>& itemInfos() const;
		/// �I����ԃA�C�R���̉摜���X�g�iTreeView::imageList()�j�̃C���f�b�N�X�B-1 �Ȃ� imageIndex() �Ɠ����B
		int selectedImageIndex() const;
		void selectedImageIndex(int value);
		/// ��ԁB��ԉ摜���X�g�iTreeView::stateImageList()�j�̃C���f�b�N�X - 1 �ŁA-1 �Ȃ�\�����Ȃ��B
		int state() const;
		void state(int value);
		/// ���ڂ̕�����B
		const String& text() const;
		void text(String value);

	private:
		friend Item;

		String _text;
		std::vector<ItemInfo> _itemInfos;
		int _imageIndex;
		int _selectedImageIndex;
		int _itemDataState;
	};


	/// ���ڂ̎q����񋓂ł���C�e���[�^�B�q���ڂ��A�q�̎q���ڂ��S�čċA�I�ɗ񋓂���B
	class ItemDescendantsIterator {
	public:
		ItemDescendantsIterator(Item root);

		TreeView::ItemDescendantsIterator& operator++();
		TreeView::Item& operator*();
		TreeView::Item* operator->();
		operator bool() const;

	private:
		TreeView::Item _root;
		TreeView::Item _current;
	};



	/// �c��[�r���[�̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<TreeView, Control::Event> Event;

	typedef Event Click;
	typedef Event RightClick;


	/// ���ڂɊւ���C�x���g�B
	struct ItemEvent : public Event {
		ItemEvent(TreeView& sender, HTREEITEM item);

		/// ���ځB
		TreeView::Item item();

	private:
		HTREEITEM _item;
	};


	/// ���ڂ��}�E�X�E�{�^���܂��͍��{�^���Ńh���b�O�����C�x���g�B�h���b�O���J�n����͈͂͑I���ł���͈͂Ɠ����B
	struct ItemDrag : public ItemEvent {
		ItemDrag(TreeView& sender, HTREEITEM item, bool rButton);

		/// �E�{�^���h���b�O���ǂ����B
		bool rButton() const;

	private:
		bool _rButton;
	};


	/// ���ڂ̎q���ڂ��\������Ă��邩�ǂ������ω������C�x���g�B
	struct ItemExpand : public ItemEvent {
		ItemExpand(TreeView& sender, HTREEITEM item, bool expanded);

		/// ���ڂ̎q���ڂ��\������Ă��邩�ǂ����B
		bool expanded() const;

	private:
		bool _expanded;
	};


	/// ���ڂ̎q���ڂ��\������Ă��邩�ǂ������ω����悤�Ƃ��Ă���C�x���g�B
	struct ItemExpanding : public ItemExpand {
		ItemExpanding(TreeView& sender, HTREEITEM item, bool expanded);

		/// �ω����L�����Z�����邩�ǂ����B
		bool cancel() const;
		void cancel(bool value);

	private:
		bool _cancel;
	};


	/// ���ڂ�`�悷�钼�O�̃C�x���g�B
	struct ItemPrePaint : public Event {
		ItemPrePaint(TreeView& sender, ::tagNMTVCUSTOMDRAW* info);

		/// ���ڂ̔w�i�̐F�Bselected() �� true �̏ꍇ�͖����BTreeView::fullRowSelect() �Ŕ͈͂��ς��B
		Color backColor() const;
		void backColor(const Color& value);
		/// ���ڂ̃N���C�A���g���W�̈�B
		Rectangle bounds() const;
		/// �t�H�[�J�X������悤�ɕ`�悷�邩�ǂ����B
		bool focused() const;
		void focused(bool value);
		/// ���ڂ̕�����̃t�H���g�B
		Font font() const;
		void font(HFONT value);
		/// �C�x���g�̔����������ځB
		TreeView::Item item();
		/// ���ڂ̃c���[�K�w�̐[���B0 ����n�܂�B
		int level() const;
		/// �I�����Ă���悤�ɕ`�悷�邩�ǂ����B
		bool selected() const;
		void selected(bool value);
		/// ���ڂ̕�����̐F�B
		Color textColor() const;
		void textColor(const Color& value);

	private:
		friend TreeView;

		::tagNMTVCUSTOMDRAW* _info;
		bool _fontChanged;
	};


	/// �I�����ڂ��ω������C�x���g�B
	struct ItemSelect : public Event {
		ItemSelect(TreeView& sender, HTREEITEM oldSelectedItem, HTREEITEM newSelectedItem);

		/// �V�����I�����ځB
		TreeView::Item newSelectedItem() const;
		/// �Â��I�����ځB
		TreeView::Item oldSelectedItem() const;

	protected:
		HTREEITEM _oldSelectedItem;
		HTREEITEM _newSelectedItem;
	};


	/// �I�����ڂ��ω����悤�Ƃ��Ă���C�x���g�B
	struct ItemSelecting : public ItemSelect {
		ItemSelecting(TreeView& sender, HTREEITEM oldSelectedItem, HTREEITEM newSelectedItem);

		/// �ω����L�����Z�����邩�ǂ����B
		bool cancel() const;
		void cancel(bool value);

	private:
		bool _cancel;
	};


	/// ���ڂ̏�Ԃ��ω������C�x���g�B
	struct ItemStateChange : public ItemEvent {
		ItemStateChange(TreeView& sender, HTREEITEM item, int oldState, int newState);

		/// �V�������ڂ̏�ԁB
		int newState() const;
		/// �Â����ڂ̏�ԁB
		int oldState() const;

	protected:
		int _oldState;
		int _newState;
	};


	/// ���ڂ̏�Ԃ��ω����悤�Ƃ��Ă���C�x���g�B
	struct ItemStateChanging : public ItemStateChange {
		ItemStateChanging(TreeView& sender, HTREEITEM item, int oldState, int newState);

		/// �V�������ڂ̏�ԁB
		void newState(int value);
		using ItemStateChange::newState;
	};


	/// ���ڂ̃c�[���`�b�v���\�������C�x���g�B
	struct ItemTipPopup : public ItemEvent {
		ItemTipPopup(TreeView& sender, HTREEITEM item, wchar_t* buffer, int bufferSize);

		/// �\�����镶�����ݒ肷��B������̒����ɂ͏���������Đ؂�̂Ă���B
		void setText(StringRange value);

	private:
		wchar_t* _buffer;
		int _bufferSize;
	};


	/// ���ڂ̕������ҏW��������̃C�x���g�B
	struct TextEdit : public ItemEvent {
		TextEdit(TreeView& sender, HTREEITEM item, String itemText);

		/// �ҏW���J�n���Ȃ����A�܂��͕ҏW���ʂ𔽉f���Ȃ����ǂ����B
		bool cancel() const;
		void cancel(bool value);
		/// �ҏW�����A�܂��͕ҏW���ꂽ������B
		const String& itemText() const;
		void itemText(String value);

	private:
		String _itemText;
		bool _cancel;
	};


	/// ���ڂ̕������ҏW���钼�O�̃C�x���g�B
	struct TextEditing : public TextEdit {
		TextEditing(TreeView& sender, HTREEITEM item, String itemText);

		/// �ҏW������G�f�B�b�g�R���g���[���̎Q�ƁB�K�v�Ȑݒ���s������j�����Ă��ǂ����ꕔ�ݒ��C�x���g�͔j������Ɩ����ɂȂ�B
		/// ������x TreeView �����䂵�Ă���̂œ��삵�Ȃ��ݒ������B
		Edit edit();
	};


	/// �q�b�g�e�X�g�̌��ʁB
	struct HitTestInfo {
		HitTestInfo(HWND handle, HTREEITEM item, int flags);

		/// �������Ă��鍀�ځB�������ĂȂ��ꍇ�̓k�����ځB
		TreeView::Item item();
		/// �q���ڂ�\��/��\���ɂ���[+][-]�{�^���̏�B
		bool onButton() const;
		/// �A�C�R���摜�̏�B
		bool onImage() const;
		/// ���ڂ̃C���f���g�̏�B
		bool onIndent() const;
		/// ���ڂ̃A�C�R���摜�A��ԉ摜�A�܂��͕�����̏�B
		bool onItem() const;
		/// ���ڂ̕�������E�̕����B
		bool onItemRight() const;
		/// ��ԉ摜�̏�B
		bool onStateImage() const;
		/// ������̏�B
		bool onText() const;

	private:
		HWND _handle;
		HTREEITEM _item;
		int _flags;
	};


public:
	/// �k���n���h���ō쐬�B
	TreeView();
	TreeView(TreeView&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫������쐬�B
	TreeView(Control& parent, int x, int y, int width, int height, TreeView::Options options = Options::none);
	/// �e�A�ʒu�A�傫���A���ڏ��z�񂩂�쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	TreeView(Control& parent, int x, int y, int width, int height, ArrayRange<const ItemInfo> itemInfos, TreeView::Options options = Options::none);
	virtual ~TreeView();
	TreeView& operator=(TreeView&& value);

public:
	/// �t�H�[�J�X���O��Ă��I����Ԃ�\�����邩�ǂ����B�����l�� false�B
	bool alwaysSelected() const;
	void alwaysSelected(bool value);
	/// �w�i�F�B
	Color backColor() const;
	void backColor(const Color& value);
	/// �q���ڂ�\��/��\���ɂ���[+][-]�{�^����\�����邩�ǂ����B�����l�� true�B
	bool buttons() const;
	void buttons(bool value);
	/// ���ڐ��B
	int count() const;
	/// �c��[�r���[���ɕ\���ł��鍀�ڐ��B
	int countPerPage() const;
	/// �R���g���[���̋��E���̎�ށB�����l�� Control::Edge::client�B
	Control::Edge edge() const;
	void edge(Control::Edge value);
	/// ���̍s��S�đI����Ԃɂ��邩�ǂ����Blines() �� true �̏ꍇ�� true �ɐݒ�ł��Ȃ��B�����l�� false�B
	bool fullRowSelect() const;
	void fullRowSelect(bool value);
	/// �w�肵���N���C�A���g���W�̃q�b�g�e�X�g���s���ď����擾����B
	TreeView::HitTestInfo getHitTestInfo(const Point& point) const;
	TreeView::HitTestInfo getHitTestInfo(int x, int y) const;
	/// �w�肵���N���C�A���g���W�ɂ��鍀�ڂ��擾����B�����ꍇ�̓k�����ځB
	TreeView::Item getItemAt(const Point& point);
	TreeView::Item getItemAt(int x, int y);
	/// �K�؂ȃR���g���[���T�C�Y�Bfont(), count() ���̒l�ɂ���čœK�ȃT�C�Y��Ԃ��B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// ���ڂɃJ�[�\�������킹��ƃJ�[�\���� Cursor::hand() �ɂȂ��ĕ�����ɃA���_�[���C�����\������邩�ǂ����B�����l�� false�B
	bool hotTracking() const;
	void hotTracking(bool value);
	/// ���ڂ�\�����؂�Ȃ����ɐ����X�N���[���o�[��\�����邩�ǂ����B���ڂ��͂ݏo�Ă��Ȃ����ɐݒ肵�Ȃ��Ƃ��܂����삵�Ȃ��B�����l�� true�B
	bool hScrollable() const;
	void hScrollable(bool value);
	/// �A�C�R���̉摜���X�g�BTreeView �͉摜���X�g�̃n���h����j�����Ȃ��B
	ImageList imageList() const;
	void imageList(HIMAGELIST value);
	/// �q���ڂ̃C���f���g�s�N�Z�����B
	int indent() const;
	void indent(int value);
	/// ���ڂ̍����B
	int itemHeight() const;
	void itemHeight(int value);
	/// ���ڂ��Ƃɕ\������c�[���`�b�v�R���g���[���̎Q�ƁB�K�v�Ȑݒ���s������j�����Ă��ǂ����ꕔ�ݒ��C�x���g�͔j������Ɩ����ɂȂ�B������x TreeView �����䂵�Ă���̂œ��삵�Ȃ��ݒ������B
	ToolTip itemTip();
	/// ���ڂ��ƂɃc�[���`�b�v��\�����邩�ǂ����BonItemTipPopup �C�x���g�ŕ\�����镶������w�肷��B�����l�� false�B
	bool itemTipEnabled() const;
	void itemTipEnabled(bool value);
	/// �e�Ǝq���ڂ����Ԑ��̐F�B
	Color lineColor() const;
	void lineColor(const Color& value);
	/// �e�Ǝq���ڂ����Ԑ���\�����邩�ǂ����B�����l�� true�B
	bool lines() const;
	void lines(bool value);
	/// ���N���b�N�����C�x���g�B
	Listener<TreeView::Click&>& onClick();
	/// ���ڂ��}�E�X�E�{�^���܂��͍��{�^���Ńh���b�O�����C�x���g�B�h���b�O���J�n����͈͂͑I���ł���͈͂Ɠ����B
	Listener<TreeView::ItemDrag&>& onItemDrag();
	/// ���ڂ̎q���ڂ��\������Ă��邩�ǂ������ω������C�x���g�B
	Listener<TreeView::ItemExpand&>& onItemExpand();
	/// ���ڂ̎q���ڂ��\������Ă��邩�ǂ������ω����悤�Ƃ��Ă���C�x���g�B
	Listener<TreeView::ItemExpanding&>& onItemExpanding();
	/// ���ڂ�`�悷�钼�O�̃C�x���g�B
	Listener<TreeView::ItemPrePaint&>& onItemPrePaint();
	/// �I�����ڂ��ω������C�x���g�B
	Listener<TreeView::ItemSelect&>& onItemSelect();
	/// �I�����ڂ��ω����悤�Ƃ��Ă���C�x���g�B
	Listener<TreeView::ItemSelecting&>& onItemSelecting();
	/// ���ڂ̏�Ԃ��ω������C�x���g�B
	Listener<TreeView::ItemStateChange&>& onItemStateChange();
	/// ���ڂ̏�Ԃ��ω����悤�Ƃ��Ă���C�x���g�B
	Listener<TreeView::ItemStateChanging&>& onItemStateChanging();
	/// ���ڂ̃c�[���`�b�v��\������C�x���g�B
	Listener<TreeView::ItemTipPopup&>& onItemTipPopup();
	/// �E�N���b�N�����C�x���g�B���܂��E���Ȃ� onMouseUp �C�x���g�̑���Ɏg���B
	Listener<TreeView::RightClick&>& onRightClick();
	/// ���ڂ̕�����ҏW���I����Ĕ��f���钼�O�̃C�x���g�B
	Listener<TreeView::TextEdit&>& onTextEdit();
	/// ���ڂ̕�����ҏW���n�܂钼�O�̃C�x���g�B
	Listener<TreeView::TextEditing&>& onTextEditing();
	///	�R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B
	TreeView::Options options() const;
	/// ���z�I�ȃ��[�g���ڂ��擾����B���̍��ڂ͕\������Ȃ����q���ڂ̑���ȊO�͎󂯕t���Ȃ��B
	TreeView::Item root();
	const TreeView::Item root() const;
	/// ���[�g���ڂƎq���ڂ����Ԑ���\�����邩�ǂ����B�����l�� true�B
	bool rootLines() const;
	void rootLines(bool value);
	/// ���ڂ�\�����؂�Ȃ����ɃX�N���[���o�[��\�����邩�ǂ����B���ڂ��͂ݏo�Ă��Ȃ����ɐݒ肵�Ȃ��Ƃ��܂����삵�Ȃ��B�����l�� true�B
	bool scrollable() const;
	void scrollable(bool value);
	/// �I������Ă��鍀�ځB
	TreeView::Item selectedItem() const;
	void selectedItem(TreeView::Item value);
	/// ��ԃA�C�R���̉摜���X�g�B0 �Ԗڂ̉摜�͎g�p����Ȃ��BTreeView �͉摜���X�g�̃n���h����j�����Ȃ��B
	/// ���[�U�w��̉摜���X�g�̓`�F�b�N�{�b�N�X�Ƌ����ł��Ȃ��B�`�F�b�N�{�b�N�X�̕\����ς������ꍇ�� stateImageList() �֐��Ŏ擾�����摜���X�g�𑀍삷��B
	ImageList stateImageList() const;
	void stateImageList(HIMAGELIST value);
	/// �����F�B
	Color textColor() const;
	void textColor(const Color& value);
	/// �N���b�N�ō��ڂ̕������ҏW�ł��邩�ǂ����B�����l�� false�B
	bool textEditable() const;
	void textEditable(bool value);
	/// �ŏ��ɕ\������Ă��鍀�ځB
	TreeView::Item topItem() const;
	void topItem(TreeView::Item value);

protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	Listener<TreeView::Click&> _onClick;
	Listener<TreeView::ItemDrag&> _onItemDrag;
	Listener<TreeView::ItemExpand&> _onItemExpand;
	Listener<TreeView::ItemExpanding&> _onItemExpanding;
	Listener<TreeView::ItemPrePaint&> _onItemPrePaint;
	Listener<TreeView::ItemSelect&> _onItemSelect;
	Listener<TreeView::ItemSelecting&> _onItemSelecting;
	Listener<TreeView::ItemStateChange&> _onItemStateChange;
	Listener<TreeView::ItemStateChanging&> _onItemStateChanging;
	Listener<TreeView::ItemTipPopup&> _onItemTipPopup;
	Listener<TreeView::RightClick&> _onRightClick;
	Listener<TreeView::TextEdit&> _onTextEdit;
	Listener<TreeView::TextEditing&> _onTextEditing;
};



	}
}