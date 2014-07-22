#pragma once

#include <balor/gui/FileDialog.hpp>


namespace balor {
	namespace gui {



/**
 * �t�@�C�����J���_�C�A���O�{�b�N�X�B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"OpenFileDialog Sample");

	Button open(frame, 20, 10, 0, 0, L"�t�@�C�����J��");
	Edit filePath(frame, 20, 50, 0, 0, 150);
	filePath.readOnly(true);
	const wchar_t* encodes[] = {
		L"acsii",
		L"ShiftJis",
		L"euc-jp"
	};
	ComboBox encode(frame, 20, 90, 0, 0, encodes);
	encode.selectedIndex(0);

	OpenFileDialog dialog;
	dialog.filter(L"�S�Ẵt�@�C��\n*.*\n�e�L�X�g�t�@�C��\n*.txt;*.log\n\n");
	dialog.readOnlyCheckBox(false);
	// �t�@�C�����J���_�C�A���O�� UI ���g������B
	Panel panel;
	Label label;
	ComboBox combo;
	dialog.onInit() = [&] (OpenFileDialog::Init& e) {
		auto clientSize = e.clientSize();
		panel = Panel::fromParentHandle(e.sender(), 0, clientSize.height, 0, 0);
		label = Label(panel, e.getControlBounds(OpenFileDialog::ControlId::filePathLabel).x, 0, 0, 0, L"�G���R�[�h");
		combo = ComboBox(panel, e.getControlBounds(OpenFileDialog::ControlId::filePathEdit).x, 0, 0, 0, encodes);
		combo.selectedIndex(encode.selectedIndex());
		combo.onSelect() = [&] (ComboBox::Select& e) {
			encode.selectedIndex(combo.selectedIndex());
		};
		panel.resize();
		e.clientSize(clientSize.width, clientSize.height + panel.size().height * 2);
	};

	open.onClick() = [&] (Button::Click& ) {
		if (dialog.show(frame)) {
			filePath.text(dialog.filePath());
		}
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class OpenFileDialog : public FileDialog {
public:
	OpenFileDialog();
	OpenFileDialog(OpenFileDialog&& value, bool checkSlicing = true);
	virtual ~OpenFileDialog();
	OpenFileDialog& operator=(OpenFileDialog&& value);

public:
	/// ���݂��Ȃ��t�@�C�����܂��̓t�@�C���p�X����͂��ĊJ���{�^�����������ꍇ�Ɍx�����邩�ǂ����B�����l�� true�B
	bool fileMustExist() const;
	void fileMustExist(bool value);
	/// ���݂��Ȃ��t�@�C���p�X����͂��ĊJ���{�^�����������ꍇ�Ɍx�����邩�ǂ����B�t�@�C�����͑��݂��Ȃ��Ă�������B�����l�� true�B
	bool pathMustExist() const;
	void pathMustExist(bool value);
	/// �ǂݎ���p�t�@�C���Ƃ��ĊJ�����邢�͊J�������ǂ����B�����l�� false�B
	bool readOnly() const;
	void readOnly(bool value);
	/// �ǂݎ���p�t�@�C���Ƃ��ĊJ���`�F�b�N�{�b�N�X��\�����邩�ǂ����B�����l�� true�B
	bool readOnlyCheckBox() const;
	void readOnlyCheckBox(bool value);
	/// �_�C�A���O�{�b�N�X��\������B�t�@�C����I���������ǂ�����Ԃ��B
	bool show(HWND owner);

protected:
};



	}
}