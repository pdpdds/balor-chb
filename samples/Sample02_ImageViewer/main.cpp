#include <Windows.h>
#include <balor/graphics/all.hpp>
#include <balor/gui/all.hpp>

using namespace balor::graphics;
using namespace balor::gui;


int APIENTRY WinMain(HINSTANCE , HINSTANCE , LPSTR , int ) {
	Frame frame(L"ImageViewer");
	Bitmap bitmap;

	typedef Menu::ItemInfo Item;
	Item fileMenuItems[] = {
		Item(L"�J��(&O)\tCtrl+O", Key::Modifier::ctrl | Key::o),
		Item(),
		Item(L"�I��(&X)\tAlt+F4", Key::Modifier::alt | Key::f4)
	};
	Item menuBarItems[] = {
		Item(L"�t�@�C��(&F)", fileMenuItems),
		Item(L"�w���v(&H)", [&] (Menu::Click& ) { MsgBox::show(L"Image Viewer Ver 1.0", L"�o�[�W�������"); })
	};
	MenuBar menuBar(menuBarItems);
	frame.menuBar(&menuBar);

	frame.onShortcutKey() = [&] (Frame::ShortcutKey& e) {
		switch (e.shortcut()) {
			case Key::Modifier::ctrl | Key::o : {
				OpenFileDialog dialog;
				dialog.filter(L"�摜�t�@�C��\n*.bmp;*.gif;*.png;*.jpg;*.jpeg;*.tiff\n\n");
				if (dialog.show(frame)) {
					bitmap = Bitmap(dialog.filePath());
					if (bitmap != nullptr) {
						frame.scrollMinSize(bitmap.size()); // �E�C���h�E�T�C�Y���摜�T�C�Y�ȉ��Ȃ�X�N���[���ł���悤�ɂ���B
						frame.invalidate();
					}
				}
				e.handled(true);
			} break;
			case Key::Modifier::alt | Key::f4 : {
				frame.close();
				e.handled(true);
			} break;
		}
	};
	frame.onPaint() = [&] (Frame::Paint& e) {
		e.graphics().clear();
		if (bitmap != nullptr) {
			Graphics bitmapGraphics(bitmap);
			e.graphics().copy(frame.scrollPosition(), bitmapGraphics); // �X�N���[�������炵�ĉ摜���R�s�[����B
		}
	};

	frame.runMessageLoop();
	return 0;
}
