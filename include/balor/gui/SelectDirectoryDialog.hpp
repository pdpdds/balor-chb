#pragma once

#include <balor/gui/FileDialog.hpp>


namespace balor {
	namespace gui {



/**
 * �f�B���N�g����I������_�C�A���O�{�b�N�X�B
 * 
 * SHBrowseForFolder API �͋@�\���n��Ȃ̂� FileOpenDialog ����������B
 * ���� SelectDirectoryDialog::Event::filePath() �֐��͐��������ʂ�Ԃ��Ȃ��B
 * ����� SelectDirectoryDialog::directoryPath() �����A���^�C���X�V�����̂ł�������g�����ƁB
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"SelectDirectoryDialog Sample");

	Button select(frame, 20, 10, 0, 0, L"�f�B���N�g����I������");
	Edit directoryPath(frame, 20, 50, 0, 0, 150);
	directoryPath.readOnly(true);

	SelectDirectoryDialog dialog;
	dialog.title(L"�f�B���N�g���̑I��");

	select.onClick() = [&] (Button::Click& ) {
		if (dialog.show(frame)) {
			directoryPath.text(dialog.directoryPath());
		}
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class SelectDirectoryDialog : protected FileDialog {
public:
	typedef FileDialog::ControlId ControlId;
	typedef FileDialog::Event Event;
	typedef FileDialog::HelpRequest HelpRequest;
	typedef FileDialog::Resize Resize;
	typedef FileDialog::Accept Accept;
	typedef FileDialog::Init Init;

public:
	SelectDirectoryDialog();
	SelectDirectoryDialog(SelectDirectoryDialog&& value);
	virtual ~SelectDirectoryDialog();
	SelectDirectoryDialog& operator=(SelectDirectoryDialog&& value);

public:
	/// �_�C�A���O�\���O�͏����\�������f�B���N�g���p�X�B�_�C�A���O�\����̓��[�U���I�������f�B���N�g���p�X�B�����l�͋󕶎���B
	const String& directoryPath() const;
	void directoryPath(String value);

	using FileDialog::helpButton;
	using FileDialog::onAccept;
	using FileDialog::onHelpRequest;
	using FileDialog::onInit;
	using FileDialog::onResize;
	using FileDialog::placesBar;

	/// �_�C�A���O�{�b�N�X��\������B�t�@�C����I���������ǂ�����Ԃ��B
	bool show(HWND owner);

	using FileDialog::title;

protected:
	/// �t�b�N�������b�Z�[�W����������B
	virtual void processMessage(Message& msg);

protected:
	Procedure _editDefaultProcedure;
};



	}
}