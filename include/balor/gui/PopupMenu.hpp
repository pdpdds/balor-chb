#pragma once

#include <balor/gui/Menu.hpp>

namespace balor {
class Point;
}


namespace balor {
	namespace gui {


/**
 * �|�b�v�A�b�v���j���[�B
 *
 * TODO: �|�b�v�A�b�v�̕\�����l�X�g����Ă���̂��������o�ł��Ȃ����̂��B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"PopupMenu Sample");

	Label label(frame, 20, 10, 0, 0, L"�E�N���b�N�Ń|�b�v�A�b�v���j���[�\��");

	typedef Menu::ItemInfo Item;
	Item items[] = {
		Item(L"�`�F�b�N(&C)", [&] (Menu::Click& e) {
			auto& menuItem = e.sender();
			menuItem.checked(!menuItem.checked());
		}),
		Item(L"�x������(&W)", [&] (Menu::Click& ) {
			MsgBox::show(frame, L"�x��");
		}),
		Item(),
		Item(L"�I��(&X)", [&] (Menu::Click& ) {
			frame.close();
		})
	};
	PopupMenu menu(items);
	frame.onPopupMenu() = [&] (Frame::PopupMenu& e) {
		menu.show(frame, e.position());
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class PopupMenu : public Menu {
public:
	/// �\���𐧌䂷��t���O�B�g�ݍ��킹�Ŏw�肷��B
	struct Flags {
		enum _enum {
			recursive  = 0x0001L, /// onRightClick() �C�x���g�ōċA�I�Ƀ|�b�v�A�b�v���j���[��\�����鎞�Ɏw�肵�Ȃ���΂Ȃ�Ȃ��B
			bothButton = 0x0002L, /// onRightClick() �C�x���g�̑���� onClick() �C�x���g�𔭐�������B
			hCentor    = 0x0004L, /// ���������̒����ɕ\���B
			right      = 0x0008L, /// �E�ɕ\���B
			bottom     = 0x0020L, /// ��ɕ\���B
			vCentor    = 0x0010L, /// ���������̒����ɕ\���B
			vertical   = 0x0040L, /// �ʒu�𒲐�����Ƃ��ɐ���������D�悷��B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Flags);
	};

public:
	/// ��̃|�b�v�A�b�v���j���[���쐬�B
	PopupMenu();
	PopupMenu(PopupMenu&& value);
	/// �q���ڂ̏��z�񂩂�쐬�B
	PopupMenu(ArrayRange<const Menu::ItemInfo> itemInfos);
	virtual ~PopupMenu();
	PopupMenu& operator=(PopupMenu&& value);

public:
	/// �|�b�v�A�b�v���j���[��\�����钼�O�̃C�x���g�B
	Listener<Menu::PopupBegin&>& onPopupBegin();
	/// �|�b�v�A�b�v���j���[��\�����I������C�x���g�B
	Listener<Menu::PopupEnd&>& onPopupEnd();
	/// �I�[�i�[�R���g���[���ƃI�[�i�[�̃N���C�A���g���W���w�肵�ă|�b�v�A�b�v���j���[��\������B
	void show(Control& owner, const Point& position, PopupMenu::Flags flags = Flags::bothButton | Flags::vertical);
	void show(Control& owner, int x, int y, PopupMenu::Flags flags = Flags::bothButton | Flags::vertical);
};



	}
}