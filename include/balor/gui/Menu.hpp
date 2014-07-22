#pragma once

#include <vector>

#include <balor/ArrayRange.hpp>
#include <balor/Event.hpp>
#include <balor/Listener.hpp>
#include <balor/NonCopyable.hpp>
#include <balor/Point.hpp>
#include <balor/String.hpp>
#include <balor/UniqueAny.hpp>

struct HBITMAP__;
struct HMENU__;

namespace balor {
	namespace graphics {
		class Bitmap;
		class Font;
	}
	class Rectangle;
	class Size;
}


namespace balor {
	namespace gui {

class Control;



/**
 * ���j���[�o�[��|�b�v�A�b�v���j���[�̊��N���X�B
 *
 * �f�t�H���g�A�C�e���̓T�|�[�g���Ȃ��B���ڂ̃_�u���N���b�N�Őe���ڂɑ΂��� WM_MENUCOMMAND ���b�Z�[�W����������̂ő����ڂ����ł��Ȃ��B
 * onDrag �C�x���g�Ńh���b�O���h���b�v���J�n���A�I�[�i�[�E�C���h�E�� DragDrop::Target::onDrop �C�x���g�Ń��b�Z�[�W�{�b�N�X��\�������
 * Vista �ł̓u���[�X�N���[���AXP�ł� PC �ċN�����Ă��܂����B���b�Z�[�W�{�b�N�X��\�����Ȃ���΋N���Ȃ��̂ŉ�������B���ӂ��K�v�B
 */
class Menu : private NonCopyable {
public:
	typedef ::HBITMAP__* HBITMAP;
	typedef ::HMENU__* HMENU;
	typedef ::balor::graphics::Bitmap Bitmap;
	typedef ::balor::graphics::Font Font;


	class Event;

	typedef Event Click;
	typedef Event PopupBegin;
	typedef Event PopupEnd;
	typedef Event RightClick;
	typedef Event Select;

	class Drag;
	class ItemInfo;
	class DescendantsIterator;

	/// ���j���[���ځBMenu::operator[] �܂��� Menu::Item::operator[] �Ŏ擾�ł���B
	class Item : private NonCopyable {
		friend Menu;

		Item();
		Item(Item&& value);
		~Item();
		Item& operator=(Item&& value);

	public:
		/// ���̔��f�B
		Item& operator=(const ItemInfo& itemInfo);

	public:
		/// �q���ڂ�ǉ�����B
		void add(const ItemInfo& itemInfo);
		/// �Ԃɐ��������ă��j���[�����s���邩�ǂ����B���j���[�o�[�̏ꍇ�͐��͈����Ȃ��B
		bool barBreak() const;
		void barBreak(bool value);
		/// �Ԃɐ����������Ƀ��j���[�����s���邩�ǂ����BbarBreak() �̂ق����D�悳���B
		bool lineBreak() const;
		void lineBreak(bool value);
		/// �`�F�b�N����Ă��邩�ǂ����B
		bool checked() const;
		void checked(bool value);
		/// �`�F�b�N���ꂽ��Ԃ̃r�b�g�}�b�v�摜�B�r�b�g�}�b�v�n���h���͎Q�Ƃ����̂Ŕj�����Ȃ����ƁB
		Bitmap checkedMark() const;
		void checkedMark(HBITMAP value);
		/// �q���ڂ�S�č폜����B
		void clear();
		/// �q���ڂ̐��B
		int count() const;
		/// �S�Ă̎q�����ڂ�񋓂���C�e���[�^�B
		Menu::DescendantsIterator descendantsBegin();
		/// �I���\���ǂ����B
		bool enabled() const;
		void enabled(bool value);
		/// �q���ڂ��폜����B
		void erase(int index);
		/// ���j���[�n���h�����獀�ڂ��擾����B������Ȃ��ꍇ�� nullptr ��Ԃ��B
		static Menu::Item* fromHandle(HMENU handle);
		/// �I�[�i�[�R���g���[����ł̍��ڂ̃X�N���[�����W�n�ł̕\���ʒu���擾����B�\������Ă��Ȃ��ꍇ�͑傫�����O�ɂȂ�B
		Rectangle getBounds(Control& owner) const;
		/// ���ڂ̃C���f�b�N�X�B
		int index() const;
		/// �q���ڂ�}������B
		void insert(int index, const ItemInfo& itemInfo);
		/// �q���ڂ̏��\���̔z����ꊇ�Ŏ擾�A�ݒ肷��B
		std::vector<Menu::ItemInfo> itemInfos() const;
		void itemInfos(ArrayRange<const Menu::ItemInfo> value);
		/// �N���b�N�������̃C�x���g�Bshortcut() ���ݒ肳��Ă���ꍇ�͔������Ȃ��B
		Listener<Menu::Click&>& onClick();
		/// ���̍��ڂ��h���b�O�������̃C�x���g�B
		Listener<Menu::Drag&>& onDrag();
		/// �|�b�v�A�b�v���j���[��\�����钼�O�̃C�x���g�B
		Listener<Menu::PopupBegin&>& onPopupBegin();
		/// �|�b�v�A�b�v���j���[��\�����I������C�x���g�B
		Listener<Menu::PopupEnd&>& onPopupEnd();
		/// �E�N���b�N�������C�x���g�B
		Listener<Menu::RightClick&>& onRightClick();
		/// �}�E�X�J�[�\������ɗ����C�x���g�B
		Listener<Menu::Select&>& onSelect();
		/// �e���ځB�Ȃ��ꍇ�� nullptr�B
		Menu::Item* parent();
		/// �e���ڂ̃n���h���B�Ȃ��ꍇ�� nullptr�B
		HMENU parentHandle() const;
		/// ���W�I�{�^���X�^�C���̃`�F�b�N�}�[�N��\�����邩�ǂ����B
		bool radioCheck() const;
		void radioCheck(bool value);
		/// �Z�p���[�^���ǂ����B
		bool separator() const;
		void separator(bool value);
		/// Key �� Key::Modifier ��g�ݍ��킹���V���[�g�J�b�g�R�}���h�B
		/// �ݒ肳��Ă���ꍇ�� onClick() �C�x���g�̑���ɃI�[�i�[�R���g���[���� onShortcutKey() �C�x���g����������B
		int shortcut() const;
		void shortcut(int value);
		/// ���j���[������B
		String text() const;
		void text(StringRange value);
		void textToBuffer(StringBuffer& buffer) const;
		/// �`�F�b�N����Ă��Ȃ���Ԃ̃r�b�g�}�b�v�摜�B�r�b�g�}�b�v�n���h���͎Q�Ƃ����̂Ŕj�����Ȃ����ƁB
		Bitmap uncheckedMark() const;
		void uncheckedMark(HBITMAP value);
		/// ���[�U�����R�Ɏg����C�ӂ̃f�[�^�B
		UniqueAny& userData();
		void userData(UniqueAny&& value);

	public:
		/// HMENU �ւ̎����ϊ� & null �`�F�b�N�B
		operator HMENU() const { return _handle; }
		/// �q���ڂ��擾����B
		Item& operator[](int index);
		const Item& operator[](int index) const;

	private:
		void _attachHandle();
		void _setIndex(int value);

		HMENU _parent;
		HMENU _handle;
		int _index;
		Item* _items; // vector ���� friend �錾����R�K�v�Ŗʓ|�B
		int _itemsCapacity;
		int _shortcut;
		UniqueAny _userData;
		Listener<Menu::Click&> _onClick;
		Listener<Menu::Drag&> _onDrag;
		Listener<Menu::PopupBegin&> _onPopupBegin;
		Listener<Menu::PopupEnd&> _onPopupEnd;
		Listener<Menu::RightClick&> _onRightClick;
		Listener<Menu::Select&> _onSelect;
	};


	/// ���j���[���ڏ��\���́B�����������Ń��j���[�͈�ؑ��삵�Ȃ��BMenu::itemInfos �֐��܂��� Menu::Item::itemInfos �֐����Ŏg�p����B
	class ItemInfo {
	public:
		/// �Z�p���[�^�Ƃ��č쐬�B
		ItemInfo();
		ItemInfo(ItemInfo&& value);
		/// ���̎擾�B
		ItemInfo(const Item& item);
		/// ���ڕ�����ƃV���[�g�J�b�g�R�}���h����쐬�B
		explicit ItemInfo(String text, int shortcut = 0);
		/// ���ڕ������ onClick �C�x���g����쐬�B
		ItemInfo(String text, Listener<Menu::Event&> onClick);
		/// ���ڕ�����Ǝq���ڂ̏��\���̔z�񂩂�쐬�B�� ArrayRange �� Listener �Ƃ����܂��Ȉ����ɂȂ�̂Ŏg�p�ł����B
		ItemInfo(String text, std::vector<Menu::ItemInfo> itemInfos);
		template<int Size> ItemInfo(String text, const std::tr1::array<Menu::ItemInfo, Size>& itemInfos) : _text(std::move(text)), _itemInfos(itemInfos.begin(), itemInfos.end()) { _initialize(); }
		template<int Size> ItemInfo(String text, const Menu::ItemInfo (&itemInfos)[Size]) : _text(std::move(text)), _itemInfos(itemInfos, itemInfos + Size) { _initialize(); }
		/// ���ڕ�����ƐF�X�ȏ�񂩂�쐬�B
		ItemInfo(String text, bool barBreak, bool lineBreak, bool radioCheck
			, bool checked = false, bool enabled = true, HBITMAP checkedMark = nullptr, HBITMAP uncheckedMark = nullptr
			, int shortcut = 0, Listener<Menu::Event&> onClick = [&] (Event& ) {});
		ItemInfo& operator=(ItemInfo&& value);

	public:
		/// �Ԃɐ��������ă��j���[�����s���邩�ǂ����B���j���[�o�[�̏ꍇ�͐��͈����Ȃ��B�����l�� false�B
		bool barBreak() const;
		void barBreak(bool value);
		/// �Ԃɐ����������Ƀ��j���[�����s���邩�ǂ����B�����l�� false�B
		bool lineBreak() const;
		void lineBreak(bool value);
		/// �`�F�b�N����Ă��邩�ǂ����B�����l�� false�B
		bool checked() const;
		void checked(bool value);
		/// �`�F�b�N���ꂽ��Ԃ̃r�b�g�}�b�v�摜�B�r�b�g�}�b�v�n���h���͎Q�Ƃ����̂Ŕj�����Ȃ����ƁB�����l�� nullptr�B
		Bitmap checkedMark() const;
		void checkedMark(HBITMAP value);
		/// �I���\���ǂ����B�����l�� true�B
		bool enabled() const;
		void enabled(bool value);
		/// �q���ڂ̏��\���̔z��B
		std::vector<Menu::ItemInfo>& itemInfos();
		const std::vector<Menu::ItemInfo>& itemInfos() const;
		void itemInfos(ArrayRange<const Menu::ItemInfo> value);
		/// �j�[���j�b�N�����B�����ꍇ�� L'\0' ���Ԃ�B
		wchar_t mnemonic() const;
		/// �N���b�N�������̃C�x���g�Bshortcut() ���ݒ肳��Ă���ꍇ�͔������Ȃ��B
		Listener<Menu::Click&>& onClick();
		const Listener<Menu::Click&>& onClick() const;
		/// ���̍��ڂ��h���b�O�������̃C�x���g�B�B
		Listener<Menu::Drag&>& onDrag();
		const Listener<Menu::Drag&>& onDrag() const;
		/// �|�b�v�A�b�v���j���[��\�����钼�O�̃C�x���g�B
		Listener<Menu::PopupBegin&>& onPopupBegin();
		const Listener<Menu::PopupBegin&>& onPopupBegin() const;
		/// �|�b�v�A�b�v���j���[��\�����I������C�x���g�B
		Listener<Menu::PopupEnd&>& onPopupEnd();
		const Listener<Menu::PopupEnd&>& onPopupEnd() const;
		/// �E�N���b�N�������C�x���g�B
		Listener<Menu::RightClick&>& onRightClick();
		const Listener<Menu::RightClick&>& onRightClick() const;
		/// �}�E�X�J�[�\������ɗ����C�x���g�B
		Listener<Menu::Select&>& onSelect();
		const Listener<Menu::Select&>& onSelect() const;
		/// ���W�I�{�^���X�^�C���̃`�F�b�N�}�[�N��\�����邩�ǂ����B�����l�� false�B
		bool radioCheck() const;
		void radioCheck(bool value);
		/// �Z�p���[�^���ǂ����B�f�t�H���g�R���X�g���N�^�ō쐬�����ꍇ�� true�B
		bool separator() const;
		void separator(bool value);
		/// Key �� Key::Modifier ��g�ݍ��킹���V���[�g�J�b�g�R�}���h�B
		/// �ݒ肳��Ă���ꍇ�� onClick() �C�x���g�̑���ɃI�[�i�[�R���g���[���� onShortcutKey() �C�x���g����������B�����l�� 0�B
		int shortcut() const;
		void shortcut(int value);
		/// ���j���[������B
		const String& text() const;
		void text(String value);
		/// �`�F�b�N����Ă��Ȃ���Ԃ̃r�b�g�}�b�v�摜�B�r�b�g�}�b�v�n���h���͎Q�Ƃ����̂Ŕj�����Ȃ����ƁB�����l�� nullptr�B
		Bitmap uncheckedMark() const;
		void uncheckedMark(HBITMAP value);

	private:
		friend Item;

		void _initialize();

		String _text;
		int _type;
		int _state;
		HBITMAP _checkedMark;
		HBITMAP _uncheckedMark;
		std::vector<ItemInfo> _itemInfos;
		int _shortcut;
		Listener<Menu::Click&> _onClick;
		Listener<Menu::Drag&> _onDrag;
		Listener<Menu::PopupBegin&> _onPopupBegin;
		Listener<Menu::PopupEnd&> _onPopupEnd;
		Listener<Menu::RightClick&> _onRightClick;
		Listener<Menu::Select&> _onSelect;
	};


	/// ���j���[���ڂŔ�������C�x���g�B
	class Event : public EventWithSender<Menu::Item> {
	public:
		Event(Item& sender, Control& owner);

		/// ���j���[��\�����Ă���I�[�i�[�R���g���[���B
		Control& owner();

	private:
		Control& _owner;
	};


	/// ���j���[���ڂŃh���b�O���J�n�����C�x���g�B
	class Drag : public Event {
	public:
		Drag(Item& sender, Control& owner);

		/// �h���b�O�C�x���g��Ƀ��j���[����邩�ǂ����B�������l�ɂ�����炸���j���[�̊O�Ń}�E�X�{�^���𗣂��ƃ��j���[�͕���B�����l�� false�B
		bool endMenu() const;
		void endMenu(bool value);

	private:
		bool _endMenu;
	};


	/// �S�Ă̎q����񋓂���C�e���[�^�B�񋓂��I����ƃk����Ԃ��悤�ɂȂ�A�ȍ~�͑���ł��Ȃ��B
	class DescendantsIterator {
	public:
		/// �e���ڂ���쐬�B
		DescendantsIterator(const Item& parent);

		/// ���̎q���ցB
		DescendantsIterator& operator ++();
		/// �񋓂��� Item �|�C���^�̎擾�B
		operator Menu::Item*() const;
		/// �񋓂��� Item �|�C���^�ւ̃A�N�Z�X�B
		Menu::Item* operator->();

	private:
		Item* _parent;
		Item* _current;
	};


protected:
	Menu();
	Menu(Menu&& value);
	virtual ~Menu() = 0;
	Menu& operator=(Menu&& value);

public:
	/// �q���ڂ�ǉ�����B
	virtual void add(const ItemInfo& itemInfo);
	/// ���ڂ��`�F�b�N���ꂽ��Ԃ̉摜�̑傫���B
	static Size checkedMarkSize();
	/// �q���ڂ�S�č폜����B
	void clear();
	/// ���݂̃X���b�h�̃A�N�e�B�u�ȃ��j���[�����B
	static void close();
	/// �q���ڂ̐��B
	int count() const;
	/// �S�Ă̎q�����ڂ�񋓂���C�e���[�^�B
	Menu::DescendantsIterator descendantsBegin();
	/// �q���ڂ��폜����B
	void erase(int index);
	/// ���j���[�Ŏg�p����t�H���g�B
	static Font font();
	/// �q���ڂ�}������B
	virtual void insert(int index, const ItemInfo& itemInfo);
	/// ���ڂ̍����B
	static int itemHeight();
	/// �q���ڂ̏��z����ꊇ�Ŏ擾�A�ݒ肷��B
	std::vector<Menu::ItemInfo> itemInfos() const;
	virtual void itemInfos(ArrayRange<const Menu::ItemInfo> value);

public:
	/// ���j���[�n���h���ւ̎����ϊ� & �k���`�F�b�N�p�B
	operator HMENU() { return _root._handle; }
	/// �q���ڂ��擾����B
	Menu::Item& operator[](int index);
	const Menu::Item& operator[](int index) const;


protected:
	void _attachHandle(HMENU handle);

	Item _root;
};



	}
}