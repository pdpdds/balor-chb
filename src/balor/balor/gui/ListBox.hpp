#pragma once

#include <balor/graphics/Color.hpp>
#include <balor/gui/Control.hpp>
#include <balor/StringRangeArray.hpp>
#include <balor/UniqueAny.hpp>


namespace balor {
	namespace gui {



/**
 * ���X�g�{�b�N�X�R���g���[���B
 * 
 * �����X�N���[���o�[�͎����I�ɂ͕\������Ȃ��̂ŁAscrollWidth() �� maxItemWidth() ����ݒ肷��K�v������B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"ListBox Sample");

	Label label(frame, 20, 10, 0, 0, L"�E�C���h�E�̃A�C�R����I��");
	Icon icons[] = {
		Icon::application(),
		Icon::exclamation(),
		Icon::question()
	};
	const wchar_t* items[] = {
		L"�A�v���P�[�V�����A�C�R��",
		L"�G�N�X�N�����[�V�����A�C�R��",
		L"�N�G�X�`�����A�C�R��"
	};
	ListBox list(frame, 20, 50, 0, 0, items);
	list.onSelect() = [&] (ListBox::Select& e) {
		frame.icon(icons[list.selectedIndex()]);
	};
 
	frame.runMessageLoop();
 * </code></pre>
 */
class ListBox : public Control {
public:
	/// ���ڂ̑I����@�B
	struct SelectMode {
		enum _enum {
			none             = 0x4000L, /// �I���ł��Ȃ�
			one              = 0x0000L, /// ������I���ł���
			multiple         = 0x0008L, /// �����I���ł���
			multipleExtended = 0x0800L, /// CTRL �L�[�������Ȃ���ŕ����I���AShift �L�[�������Ȃ���Ŕ͈͑I���ł���B
		};
		BALOR_NAMED_ENUM_MEMBERS(SelectMode);
	};


	/// �R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B�g�ݍ��킹�Ŏw�肷��B
	struct Options {
		enum _enum {
			none             = 0          , 
			noHScroll        = 0x00100000L, /// �����X�N���[�������Ȃ��B
			noVScroll        = 0x00200000L, /// �����X�N���[�������Ȃ��B
			scrollBarFixed   = 0x1000L    , /// noHScroll �� noVScroll ���ݒ肳��Ă��Ȃ��X�N���[���o�[����ɕ\������B
			multiColumn      = 0x0200L    , /// �c�̍s�𕡐��s�ɂ���B
			noIntegralHeight = 0x0100L    , /// �R���g���[���̍����������I�ɍ��ڂ̍����̔{���ɒ��߂��Ȃ��B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Options);
	};


	/// ���X�g�{�b�N�X�̃C�x���g�̐e�N���X�B
	typedef EventWithSubclassSender<ListBox, Control::Event> Event;

	typedef Event Select;


public:
	/// �k���n���h���ō쐬�B
	ListBox();
	ListBox(ListBox&& value, bool checkSlicing = true);
	/// �e�A�ʒu�A�傫������쐬�B
	ListBox(Control& parent, int x, int y, int width, int height, ListBox::SelectMode select = SelectMode::one, ListBox::Options options = Options::none);
	/// �e�A�ʒu�A�傫���A���ڔz�񂩂�쐬�B�傫�����O�ɂ���� getPreferredSize �֐��ŋ��߂�B
	ListBox(Control& parent, int x, int y, int width, int height, StringRangeArray items, ListBox::SelectMode select = SelectMode::one, ListBox::Options options = Options::none);
	virtual ~ListBox();
	ListBox& operator=(ListBox&& value);

public:
	/// ���ڂ�ǉ�����B
	void add(StringRange item);
	/// �͈͑I���̊J�n�_�ɂȂ鍀�ڃC���f�b�N�X�B�ݒ肳��Ă��Ȃ��ꍇ�� -1�B
	int anchorIndex() const;
	void anchorIndex(int value);
	/// �S�Ă̍��ڂ��폜����B
	void clear();
	/// �S�Ă̍��ڂ𖢑I���ɂ���B
	void clearSelected();
	/// ��s�̕��Boptions() �� ListBox::Options::multiColumn ��ݒ肵���ꍇ�̂ݗL���B
	void columnWidth(int value);
	/// ���ڐ��B
	int count() const;
	/// �P��ɕ\���ł��鍀�ڐ��H�B
	int countPerPage() const;
	/// �R���g���[���̋��E���̎�ށB
	Control::Edge edge() const;
	void edge(Control::Edge value);
	/// ���ڂ��폜����B
	void erase(int index);
	/// �ŏ��ɕ\������Ă��鍀�ڂ̃C���f�b�N�X�B�X�N���[���𐧌�ł���B
	int firstVisibleIndex() const;
	void firstVisibleIndex(int value);
	/// �t�H�[�J�X����Ă��鍀�ڃC���f�b�N�X�B
	int focusedIndex() const;
	void focusedIndex(int value);
	/// �N���C�A���g���W����ł��߂����ڂ̃C���f�b�N�X�����߂�B������Ȃ��ꍇ�� -1 ��Ԃ��B
	int getIndexAt(const Point& point) const;
	int getIndexAt(int x, int y) const;
	/// �w�肵���C���f�b�N�X�̍��ځB
	String getItem(int index) const;
	void getItemToBuffer(StringBuffer& buffer, int index) const;
	/// ���ڂ̃N���C�A���g���W�Ƒ傫���B���͌��݂̃X�N���[���ʒu�ŕ\������Ă���傫���B
	Rectangle getItemBounds(int index) const;
	/// ���ڂɕR�����f�[�^�B�擾����ꍇ�� UniqueAny �̒��g�̌^���w�肷��B
	template<typename T> T getItemData(int index) {
		auto data = _getItemData(index);
		return any_cast<T>(*reinterpret_cast<UniqueAny*>(&data));
	}
	template<typename T> T getItemData(int index) const {
		auto data = _getItemData(index);
		return any_cast<T>(*reinterpret_cast<const UniqueAny*>(&data));
	}
	/// ���ڂɕR�����f�[�^�����邩�ǂ����B
	bool getItemDataIsEmpty(int index) const;
	/// font(), items() �̒l�ɂ���čœK�ȑ傫�������߂�B
	virtual Size getPreferredSize(int width = 0, int height = 0) const;
	/// ���ڂ�}������B
	void insert(int index, StringRange item);
	/// ���ڂ̑I����Ԃ̎擾�Ɛݒ�B
	bool isSelected(int index) const;
	void isSelected(int index, bool selected);
	/// ���ڂ̍����B�X�N���[�������������Ȃ�̂ō��ڂ�ǉ�����O�ɐݒ肷��ׂ��B
	int itemHeight() const;
	void itemHeight(int value);
	/// ���ڂ��ꊇ�Ŏ擾�A�ݒ肷��B
	std::vector<String, std::allocator<String> > items() const;
	void items(StringRangeArray value);
	/// ���݂̍��ڂ̕\���ɕK�v�ȍő啝�B
	int maxItemWidth() const;
	/// �I�����ڂ��ύX���ꂽ�C�x���g�B
	Listener<ListBox::Select&>& onSelect();
	///	�R���g���[���쐬��ɕύX�ł��Ȃ��ݒ�B
	ListBox::Options options() const;
	/// first �Ԗڂ��� last �Ԗڂ܂ł̍��ڂ�I������Bselecting �� false �Ȃ�I������������B�����I���\�ȏꍇ�̂ݗL���B
	void select(int first, int last, bool selecting = true);
	/// �I������Ă��鍀�ڂ̐��B
	int selectedCount() const;
	/// �I������Ă��鍀�ڂ̃C���f�b�N�X�B�I������Ă��Ȃ��ꍇ�� -1 ���Ԃ�BselectMode() �� ListBox::SelectMode::one �̏ꍇ�̂ݗL���B
	int selectedIndex() const;
	void selectedIndex(int value);
	/// �I������Ă��鍀�ڂ̃C���f�b�N�X�z��B
	std::vector<int, std::allocator<int> > selectedIndices() const;
	void selectedIndices(ArrayRange<int> value);
	/// ���ڂɃf�[�^��R����B
	void setItemData(int index, UniqueAny&& value);
	/// �����X�N���[���ł��镝�B
	int scrollWidth() const;
	void scrollWidth(int value);
	/// ���ڂ̑I����@�B
	ListBox::SelectMode selectMode() const;
	/// tab ���B�����l�� 8�B�P�ʂ̓t�H���g�̕��ϕ��B
	int tabWidth() const;
	void tabWidth(int value);
	/// ������̐F�B
	Color textColor() const;
	void textColor(const Color& value);

public:
	/// ���ڂ��擾����B
	String operator[](int index) const;


protected:
	/// ���b�Z�[�W����������B������E�C���h�E�v���V�[�W���B
	virtual void processMessage(Message& msg);

protected:
	void* _getItemData(int index) const;

	int _tabWidth;
	Color _textColor;
	Listener<ListBox::Select&> _onSelect;
};



	}
}