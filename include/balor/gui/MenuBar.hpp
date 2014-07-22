#pragma once

#include <balor/gui/Menu.hpp>


namespace balor {
	namespace gui {



/**
 * ���j���[�o�[�B
 *
 * ���j���[�o�[�ɏ�ɕ\������Ă���ŏ�ʂ̍��ڂ̕ύX�𔽉f����ɂ� Frame::updateMenuBar() ���g�����ƁB
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"MenuBar Sample");

	typedef MenuBar::ItemInfo Item;
	Item fileMenuItems[] = {
		Item(L"�J��(&O)\tCtrl+O", Key::Modifier::ctrl | Key::o),
		Item(L"�ۑ�(&S)\tCtrl+S", Key::Modifier::ctrl | Key::s),
		Item(),
		Item(L"�I��(&X)\tAlt+F4", Key::Modifier::alt | Key::f4)
	};
	auto onSubMenuClick = [&] (Menu::Click& e) {
		e.sender().checked(!e.sender().checked());
	};
	Item subMenuItems[] = {
		Item(L"�`�F�b�N0", onSubMenuClick),
		Item(L"�`�F�b�N1", onSubMenuClick),
		Item(L"�`�F�b�N2", onSubMenuClick)
	};
	Item editMenuItems[] = {
		Item(L"�T�u���j���[(&S)", subMenuItems),
		Item(L"���j���[���\��(&H)", [&] (Menu::Click& ) {
			frame.menuBar(nullptr);
		})
	};
	Item menuItems[] = {
		Item(L"�t�@�C��(&F)", fileMenuItems),
		Item(L"�ҏW(&E)", editMenuItems)
	};
	MenuBar menuBar(menuItems);
	frame.menuBar(&menuBar);

	frame.onShortcutKey() = [&] (Frame::ShortcutKey& e) {
		switch (e.shortcut()) {
			case Key::Modifier::ctrl | Key::o : {
				MsgBox::show(L"�J�����j���[��I��");
				e.handled(true);
			} break;
			case Key::Modifier::ctrl | Key::s : {
				MsgBox::show(L"�ۑ����j���[��I��");
				e.handled(true);
			} break;
			case Key::Modifier::alt | Key::f4 : {
				frame.close();
				e.handled(true);
			} break;
		}
	};
 
	frame.runMessageLoop();
 * </code></pre>
 */
class MenuBar : public Menu {
public:
	/// ��̃��j���[�o�[���쐬�B
	MenuBar();
	MenuBar(MenuBar&& value);
	/// �q���ڂ̏��z�񂩂�쐬�B
	MenuBar(ArrayRange<const Menu::ItemInfo> itemInfos);
	virtual ~MenuBar();
	MenuBar& operator=(MenuBar&& value);

public:
	/// �q���ڂ�ǉ�����B
	virtual void add(const ItemInfo& itemInfo);
	/// �q���ڂ�}������B
	virtual void insert(int index, const ItemInfo& itemInfo);
	/// �q���ڂ̏��z����ꊇ�Őݒ肷��B
	using Menu::itemInfos;
	virtual void itemInfos(ArrayRange<const Menu::ItemInfo> value);
};



	}
}