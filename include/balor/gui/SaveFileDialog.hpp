#pragma once

#include <balor/gui/FileDialog.hpp>


namespace balor {
	namespace gui {



/**
 * �t�@�C���ۑ��_�C�A���O�{�b�N�X�B
 * 
 * OFN_CREATEPROMPT �͓��삹���B�Ȃ��� GetOpenFileName �ł͓��삷��B.NET �ł͎��͂Ń��b�Z�[�W�{�b�N�X��\�����Ă���B
 * OFN_PATHMUSTEXIST �͐ݒ肵�Ă����Ȃ��Ă����݂��Ȃ��p�X�Ōx�����o��B���̏�t�@�C���쐬�x�����ł�B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"OpenFileDialog Sample");

	Button open(frame, 20, 10, 0, 0, L"�t�@�C����ۑ�����");
	Edit filePath(frame, 20, 50, 0, 0, 150);
	filePath.readOnly(true);

	SaveFileDialog dialog;
	dialog.filter(L"�S�Ẵt�@�C��\n*.*\n�e�L�X�g�t�@�C��\n*.txt;*.log\n\n");
	dialog.overwritePrompt(true);
	dialog.defaultExtention(L"txt");

	open.onClick() = [&] (Button::Click& ) {
		if (dialog.show(frame)) {
			filePath.text(dialog.filePath());
		}
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class SaveFileDialog : public FileDialog {
public:
	SaveFileDialog();
	SaveFileDialog(SaveFileDialog&& value, bool checkSlicing = true);
	virtual ~SaveFileDialog();
	SaveFileDialog& operator=(SaveFileDialog&& value);

public:
	/// ���݂���t�@�C�����܂��̓t�@�C���p�X����͂����ꍇ�ɏ㏑�����x�����邩�ǂ����B�����l�� true�B
	bool overwritePrompt() const;
	void overwritePrompt(bool value);
	/// �_�C�A���O�{�b�N�X��\������B�t�@�C����I���������ǂ�����Ԃ��B
	bool show(HWND owner);

protected:
};



	}
}