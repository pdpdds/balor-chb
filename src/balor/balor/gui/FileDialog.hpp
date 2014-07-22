#pragma once

#include <vector>

#include <balor/gui/Control.hpp>


namespace balor {
	namespace gui {



/**
 * �t�@�C�����J���E�ۑ�����_�C�A���O�{�b�N�X�̊��N���X�B
 * 
 */
class FileDialog {
public:
	typedef Control::HWND HWND;
	typedef Control::Procedure Procedure;


	/// �_�C�A���O��̃R���g���[��ID�B
	struct ControlId {
		enum _enum {
			acceptButton      = 0x0001, /// ����{�^���B
			cancelButton      = 0x0002, /// �L�����Z���{�^���B
			directoryComboBox = 0x0471, /// ���݂̃f�B���N�g����\������R���{�{�b�N�X�B
			directoryLabel    = 0x0443, /// ���݂̃f�B���N�g����\������R���{�{�b�N�X�̃��x���B
			directoryListView = 0x0460, /// ���݂̃f�B���N�g����\�����郊�X�g�r���[�B
			filterComboBox    = 0x0470, /// �t�B���^�[��\������R���{�{�b�N�X�B
			filterLabel       = 0x0441, /// �t�B���^�[��\������R���{�{�b�N�X�̃��x���B
			filePathEdit      = 0x047c, /// �t�@�C���p�X����͂���G�f�B�b�g�R���g���[���B
			filePathLabel     = 0x0442, /// �t�@�C���p�X����͂���G�f�B�b�g�R���g���[���̃��x���B
			helpButton        = 0x0009, /// �w���v�{�^���B
			readOnlyCheckBox  = 0x0410, /// �ǂݎ���p�ŊJ���`�F�b�N�{�b�N�X�B
		};
		BALOR_NAMED_ENUM_MEMBERS(ControlId);
	};


	/// FileDialog �̃C�x���g�̐e�N���X�B
	struct Event : public balor::Event {
		Event(HWND sender);

		/// ���ݑI������Ă���t�@�C���p�X�܂��̓f�B���N�g���p�X�B
		String filePath() const;
		/// ���ݕ\�����Ă���f�B���N�g���B
		String directory() const;
		/// �_�C�A���O�̃E�C���h�E�n���h���B
		HWND sender() const;
		/// �_�C�A���O�̃N���C�A���g�̈�̑傫���B
		Size clientSize() const;

	private:
		HWND _sender;
	};

	typedef Event DirectoryChange;
	typedef Event HelpRequest;
	typedef Event Resize;
	typedef Event Select;


	/// ����{�^�����������C�x���g�B
	struct Accept : public Event {
		Accept(HWND sender);

		/// ������L�����Z�����邩�ǂ����B�����l�� false�B
		bool cancel() const;
		void cancel(bool value);

	private:
		bool _cancel;
	};


	/// �_�C�A���O������������C�x���g�B
	struct Init : public Event {
		Init(HWND sender);

		/// �_�C�A���O��̃R���g���[���̗̈�B
		Rectangle getControlBounds(FileDialog::ControlId id) const;
		/// �_�C�A���O��̃R���g���[�����\���ɂ���B
		void hideControl(FileDialog::ControlId id);
		/// �_�C�A���O�̃X�N���[�����W�ʒu�B
		/// ����ł̓A�v���P�[�V�����̃v���Z�X���N�����Ă���ŏ��̈�񂵂��ύX�ł��Ȃ��͗l�B���񂩂�͑O��̈ʒu����������Ă���B
		Point position() const;
		void position(const Point& value);
		void position(int x, int y);
		/// �_�C�A���O��̃R���g���[���̕������ύX����B
		void setControlText(FileDialog::ControlId id, StringRange text);
		/// �_�C�A���O�̃N���C�A���g�̈�̑傫���B
		using Event::clientSize;
		void clientSize(int width, int height);
		void clientSize(const Size& value);
	};


public:
	FileDialog();
	FileDialog(FileDialog&& value);
	virtual ~FileDialog() = 0;

	/// ���[�U���t�@�C�����Ɋg���q����͂��Ȃ������ꍇ�Ɏ����I�ɒǉ������g���q�B�J���}�͊܂܂Ȃ��B�����l�͋󕶎���B
	const String& defaultExtention() const;
	void defaultExtention(String value);
	/// �_�C�A���O�\���O�͏����\�������t�@�C���p�X�܂��̓t�@�C�����B�_�C�A���O�\����̓��[�U���I�������t�@�C���p�X�Bmultiselect() �� true �̏ꍇ�� filePaths() �̂ق����g�p����B�����l�͋󕶎���B
	const String& filePath() const;
	void filePath(String value);
	/// �_�C�A���O�Ń��[�U���I�������t�@�C���p�X���X�g�Bmultiselect() �� true �̏ꍇ�̂ݗL���B
	std::vector<String> filePaths() const;
	/// �_�C�A���O�őI���ł���t�@�C���̊g���q���Ɗg���q�̑g�̃��X�g�B�g���q���Ɗg���q��'\n'�ŋ�؂�A�g���q�̓Z�~�R�����ŋ�؂��ĕ����w��ł���B�����'\n'��؂�ŕ����̑g���w�肷��B
	/// "\n\n"�őg�̏I�[�ɂȂ�B�Ⴆ�Ή��L�̂悤�Ɏw�肷��B<br>
	/// "���ׂẴt�@�C��\n*.*\n�e�L�X�g�t�@�C��\n*.txt\nJPEG�t�@�C��\n*.jpg;*.jpeg\n\n"
	/// <br>��؂蕶����'\0'�ł��ǂ��������񃊃e������'\0'���܂܂��� String �̃R���X�g���N�^�͂����ŕ����񂪏I�����Ă���Ɣ��f���Ă��܂��̂� String::literal() �֐����g�p���邩�R���X�g���N�^�ŕ�����̒������w�肷�鎖�B
	/// �����l�͋󕶎���B
	const String& filter() const;
	void filter(String value);
	/// �_�C�A���O�\���O�� filter() �Ŏw�肵���g���q���X�g�̏����C���f�b�N�X�B�_�C�A���O�\����̓��[�U���Ō�ɑI�������C���f�b�N�X�B�����l�� 0�B
	int filterIndex() const;
	void filterIndex(int value);
	/// �w���v�{�^����\�����邩�ǂ����B�����l�� false�B
	bool helpButton() const;
	void helpButton(bool value);
	/// �_�C�A���O��\���������ɍŏ��ɕ\�������f�B���N�g���B������ filePath() �Ƀp�X���܂܂��ꍇ�͂������D�悷��B
	/// filePath() �� initialDirectory() ���󕶎���̏ꍇ�̓V�X�e���̃J�����g�f�B���N�g���ɂȂ�B�����l�͋󕶎���B
	const String& initialDirectory() const;
	void initialDirectory(String value);
	/// CTRL �L�[�������Ȃ���t�@�C���𕡐��I���ł��邩�ǂ����B�����l�� false�B
	bool multiselect() const;
	void multiselect(bool value);
	/// �����N�t�@�C�����w�肵�����Ƀ����N��Ƃ݂Ȃ��������N�t�@�C���Ƃ��ĊJ�����ǂ����B�����l�� false�B
	bool noDereferenceLinks() const;
	void noDereferenceLinks(bool value);
	/// ����{�^�����������C�x���g�B
	Listener<FileDialog::Accept&>& onAccept();
	/// �f�B���N�g����ύX�����C�x���g�B
	Listener<FileDialog::DirectoryChange&>& onDirectoryChange();
	/// �w���v�{�^���������ꂽ�C�x���g�BhelpButton() �� true �̏ꍇ�̂ݔ�������B
	Listener<FileDialog::HelpRequest&>& onHelpRequest();
	/// �_�C�A���O������������C�x���g�B
	Listener<FileDialog::Init&>& onInit();
	/// �_�C�A���O�̑傫����ύX�����C�x���g�B
	Listener<FileDialog::Resize&>& onResize();
	/// �t�@�C���܂��̓f�B���N�g����I�������C�x���g�B
	Listener<FileDialog::Select&>& onSelect();
	/// �_�C�A���O�̍����Ƀt�@�C���̏ꏊ���X�g��\�����邩�ǂ����B�����l�� true�B
	bool placesBar() const;
	void placesBar(bool value);
	/// �_�C�A���O�{�b�N�X�̃^�C�g���B�󕶎�����w�肵���ꍇ�̓V�X�e���f�t�H���g�ɂȂ�B�����l�͋󕶎���B
	const String& title() const;
	void title(String value);

protected:
	/// �t�b�N�������b�Z�[�W����������B
	virtual void processMessage(Message& msg);
	/// �_�C�A���O�{�b�N�X��\������B�t�@�C����I���������ǂ�����Ԃ��B
	bool show(HWND owner, bool open);

protected:
	String _defaultExtention;
	String _filePath;
	String _filter;
	int _filterIndex;
	int _flags;
	int _flagsEx;
	String _initialDirectory;
	String _title;
	Listener<FileDialog::Accept&> _onAccept;
	Listener<FileDialog::DirectoryChange&> _onDirectoryChange;
	Listener<FileDialog::HelpRequest&> _onHelpRequest;
	Listener<FileDialog::Init&> _onInit;
	Listener<FileDialog::Resize&> _onResize;
	Listener<FileDialog::Select&> _onSelect;
	Procedure _defaultProcedure;
};



	}
}