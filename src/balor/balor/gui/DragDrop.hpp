#pragma once

#include <balor/gui/Control.hpp>
#include <balor/system/ComPtr.hpp>
#include <balor/Enum.hpp>
#include <balor/OutOfMemoryException.hpp>
#include <balor/StringRangeArray.hpp>

struct _IMAGELIST;
struct IDataObject;

namespace balor {
	namespace graphics {
		class Bitmap;
	}
	namespace io {
		class MemoryStream;
		class Stream;
	}
}


namespace balor {
	namespace gui {



/**
 * �h���b�O���h���b�v�@�\��񋟂���B
 * 
 * �h���b�O���J�n����R���g���[�����w�肵�� DragDrop::Source ���쐬���AControl::onDrag �C�x���g�܂��͔C�ӂ̃C�x���g���� DragDrop::Source::doDragDrop �֐��Ńh���b�O�h���b�v���J�n����B
 * �h���b�v����R���g���[�����w�肵�� DragDrop::Target ���쐬���ADragDrop::Target::onDrop �C�x���g�Ńh���b�v���ꂽ�f�[�^����������B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"DragDrop Sample");

	Label label(frame, 20, 10, 0, 0, L"�����ɕ�������h���b�O�A�܂��͂������當������h���b�O�ł���");
	label.edge(Label::Edge::client);
	label.resize();

	DragDrop::Target target(label);
	target.onDrop() = [&] (DragDrop::Drop& e) {
		if (e.data().containsText()) {
			label.text(e.data().getText());
		}
	};
	target.onMove() = [&] (DragDrop::Move& e) {
		if (!e.data().containsText()) {
			// ������̃h���b�O�łȂ���Ύ󂯕t���Ȃ��A�C�R���\���ɂ���B
			e.effect(DragDrop::Effect::none);
		}
	};

	DragDrop::Source source(label);
	label.onDrag() = [&] (Control::Drag& e) {
		if (e.lButton()) {
			Bitmap bitmap(label.size());
			label.drawTo(bitmap);
			ImageList list(label.size());
			list.add(bitmap);
			source.doDragDrop(label.text(), DragDrop::Effect::move, list, 0, e.position().x, e.position().y);
		}
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class DragDrop {
public:
	typedef ::_IMAGELIST* HIMAGELIST;
	typedef Control::HBITMAP HBITMAP;
	typedef Control::HCURSOR HCURSOR;
	typedef ::balor::graphics::Bitmap Bitmap;
	typedef ::balor::io::MemoryStream MemoryStream;
	typedef ::balor::io::Stream Stream;

	class Data;
	class Source;

private:
	class DropSource;
	class DropTarget;

public:
	/// ������������Ȃ������B
	struct OutOfMemoryException : public ::balor::OutOfMemoryException {};


	/// �h���b�O���h���b�v����B�g�ݍ��킹�Ŏw�肷��B
	struct Effect {
		enum _enum {
			none   = 0         , /// �����s���Ȃ������B
			copy   = 1         , /// �R�s�[������s���B
			move   = 2         , /// �ړ�������s���B
			link   = 4         , /// �V���[�g�J�b�g�̍쐬������s���B
			scroll = 0x80000000, ///
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(Effect);
	};


	/// �h���b�O���̃f�[�^���h���b�v�����C�x���g�B
	struct Drop : public Control::Event {
		Drop(Control& sender, const Data& data, Effect allowedEffects, int keyState, const Point& position);
		/// �h���b�O���������鑀��̑g�ݍ��킹�B
		DragDrop::Effect allowedEffects() const;
		/// ALT �L�[��������Ă��邩�ǂ����B
		bool alt() const;
		/// CTRL �L�[��������Ă��邩�ǂ����B
		bool ctrl() const;
		/// �h���b�O���Ă���f�[�^�B
		const DragDrop::Data& data() const;
		/// �h���b�O���h���b�v�̑���B�g�ݍ��킹�ł͂Ȃ��l�ɂȂ�B�����l�̓G�N�X�v���[���Ɠ��������B
		DragDrop::Effect effect() const;
		void effect(DragDrop::Effect value);
		/// �}�E�X�̍��{�^����������Ă��邩�ǂ����B
		bool lButton() const;
		/// �}�E�X�̒����{�^����������Ă��邩�ǂ����B
		bool mButton() const;
		/// �}�E�X�J�[�\���̈ʒu�B
		const Point& position() const;
		/// �}�E�X�̉E�{�^����������Ă��邩�ǂ����B
		bool rButton() const;
		/// Shift �L�[��������Ă��邩�ǂ����B
		bool shift() const;

	private:
		const Data& _data;
		Effect _allowedEffects;
		int _keyState;
		Point _position;
		Effect _effect;
	};


	/// �h���b�O���̃}�E�X�J�[�\�����R���g���[����ɓ������C�x���g�B
	typedef Drop Enter;


	/// �h���b�O���h���b�v�̑��� �ɑ΂��ēK�؂ȃJ�[�\����ݒ肷��C�x���g�B�ݒ肵�Ȃ������ꍇ�̓V�X�e���̃f�t�H���g�̋����ɂȂ�B
	/// DragDrop::Target �N���X�� onDragEnter �� onDragMove �C�x���g���̌�ɔ�������B
	struct Feedback : public Control::Event {
		Feedback(Control& sender, Effect effect);

		/// �J�[�\����ݒ肷��B�ݒ肵�Ȃ������ꍇ�̓V�X�e���̃f�t�H���g�̃J�[�\���ɂȂ�B
		void cursor(HCURSOR value);
		/// ����̃h���b�O���h���b�v�̑���B
		DragDrop::Effect effect() const;

	private:
		friend DropSource;

		Effect _effect;
		bool _useDefaultCursor;
	};


	/// �h���b�O���̃}�E�X�J�[�\�����R���g���[���ォ��o���C�x���g�B
	typedef Control::Event Leave;


	/// �h���b�O���Ƀ}�E�X�J�[�\�����R���g���[������ړ������C�x���g�B
	typedef Drop Move;


	/// �L�[���͏�ԓ�����h���b�O���h���b�v�𑱍s���邩�L�����Z�����邩���߂�C�x���g�B
	/// DragDrop::Target �N���X�� onDragEnter �� onDragMove �C�x���g���̑O�ɔ�������B
	struct QueryContinue : public Control::Event {
		QueryContinue(Control& sender, bool esc, int keyState);

		/// ALT �L�[��������Ă��邩�ǂ����B
		bool alt() const;
		/// �h���b�O���h���b�v���L�����Z�����邩�ǂ����B
		bool cancelDrag() const;
		void cancelDrag(bool value);
		/// CTRL �L�[��������Ă��邩�ǂ����B
		bool ctrl() const;
		/// �h���b�v���ăh���b�O���h���b�v���I�����邩�ǂ����B
		bool drop() const;
		void drop(bool value);
		/// ESC �L�[�������ꂽ���ǂ����B
		bool esc() const;
		/// �}�E�X�̍��{�^����������Ă��邩�ǂ����B
		bool lButton() const;
		/// �}�E�X�̒����{�^����������Ă��邩�ǂ����B
		bool mButton() const;
		/// �}�E�X�̉E�{�^����������Ă��邩�ǂ����B
		bool rButton() const;
		/// Shift �L�[��������Ă��邩�ǂ����B
		bool shift() const;

	private:
		bool _esc;
		int _keyState;
		bool _cancelDrag;
		bool _drop;
	};


public:
	/// �h���b�O���h���b�v����f�[�^��\���B
	/// ���[�U��`�̃f�[�^���g�p����ꍇ�� registerMemoryFormat �֐��ň�ӂȖ��O�Ń������t�H�[�}�b�g��o�^����B
	class Data  : private NonCopyable {
		friend Source;
	public:
		/// ��̃f�[�^���쐬�B
		Data();
		Data(Data&& value);
		/// �r�b�g�}�b�v�����f�[�^���쐬�B
		Data(HBITMAP bitmap);
		Data(const Bitmap& bitmap);
		/// ���[�U��`�̃������f�[�^�����f�[�^���쐬�B
		Data(int memoryFormat, MemoryStream& stream);
		/// ����������f�[�^���쐬�B
		Data(const String& text);
		Data(const wchar_t* text);
		Data(const std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t> >& text);
		Data(::IDataObject* dataObject);
		~Data();
		Data& operator=(Data&& value);

	public:
		/// �f�[�^�� �r�b�g�}�b�v���܂܂�邩�ǂ����B
		bool containsBitmap() const;
		/// �f�[�^�� DIB �r�b�g�}�b�v���܂܂�邩�ǂ����B
		bool containsDIB() const;
		/// �f�[�^�Ƀt�@�C���h���b�v���X�g���܂܂�邩�ǂ����B
		bool containsFileDropList() const;
		/// �f�[�^�Ƀ��[�U��`�̃������f�[�^���܂܂�邩�ǂ����B
		bool containsMemory(int memoryFormat) const;
		/// �f�[�^�ɕ����񂪊܂܂�邩�ǂ����B
		bool containsText() const;
		/// DDB �r�b�g�}�b�v���擾����B�����ꍇ�̓k���̃r�b�g�}�b�v��Ԃ��B
		Bitmap getBitmap() const;
		/// DIB �r�b�g�}�b�v���擾����B�����ꍇ�̓k���̃r�b�g�}�b�v��Ԃ��B
		Bitmap getDIB() const;
		/// �t�@�C���h���b�v���X�g���擾����B�����ꍇ�͋�̔z���Ԃ��B
		std::vector<String, std::allocator<String> > getFileDropList() const;
		/// ���[�U��`�̃������f�[�^���擾����B�����ꍇ�͋�̃������X�g���[����Ԃ��B
		MemoryStream getMemory(int memoryFormat) const;
		/// ��������擾����B�����ꍇ�͋󕶎����Ԃ��B
		String getText() const;
		/// ���[�U��`�̃������t�H�[�}�b�g����o�^���A�������t�H�[�}�b�g��Ԃ��B�������t�H�[�}�b�g�������̃v���Z�X�Ŋ��ɓo�^����Ă����瓯���������t�H�[�}�b�g��Ԃ��B
		static int registerMemoryFormat(StringRange memoryFormatName);
		/// DDB �r�b�g�}�b�v��ݒ肷��B
		void setBitmap(HBITMAP value);
		/// DIB �r�b�g�}�b�v��ݒ肷��B
		void setDIB(HBITMAP value);
		/// �t�@�C���h���b�v���X�g��ݒ肷��B
		void setFileDropList(StringRangeArray value);
		/// ���[�U��`�̃������f�[�^��ݒ肷��B
		void setMemory(int memoryFormat, Stream& stream);
		/// �������ݒ肷��B
		void setText(StringRange value);

	private:
		::balor::system::ComPtr<::IDataObject> _dataObject;
	};


	/// �h���b�O���h���b�v���J�n����R���g���[����\���B
	class Source : private NonCopyable {
	public:
		/// ����������ԁB
		Source();
		Source(Source&& value);
		/// �h���b�O���h���b�v�̊J�n�_�ƂȂ�R���g���[�����w�肵�č쐬�B
		Source(Control& control);
		~Source();
		Source& operator=(Source&& value);

	public:
		/// �h���b�O���h���b�v���J�n����B�ŏI�I�ɍs��ꂽ�����Ԃ��BallowedEffect �ɂ͋�����h���b�O���h���b�v����̑g�ݍ��킹��ݒ肷��B
		/// �܂��摜���X�g�Ƃ��̉摜�C���f�b�N�X�A�摜�̍��ォ��݂��}�E�X�J�[�\���̈ʒu���w�肵�ă}�E�X�J�[�\���ɏd�˂ĉ摜��\�����邱�Ƃ��ł���B
		DragDrop::Effect doDragDrop(const DragDrop::Data& data, DragDrop::Effect allowedEffects = Effect::copy | Effect::move | Effect::link | Effect::scroll
			, HIMAGELIST imageList = nullptr, int imageIndex = 0, int xHotSpot = 0, int yHotSpot = 0);
		/// �h���b�O���h���b�v�̑���ɑ΂��ēK�؂ȃJ�[�\����ݒ肷��C�x���g�B�ݒ肵�Ȃ������ꍇ�̓V�X�e���̃f�t�H���g�̋����ɂȂ�B
		Listener<DragDrop::Feedback&>& onFeedback();
		/// �L�[���͏�ԓ�����h���b�O���h���b�v�𑱍s���邩�L�����Z�����邩���߂�C�x���g�B
		Listener<DragDrop::QueryContinue&>& onQueryContinue();

	private:
		::balor::system::ComPtr<DropSource> _dropSource;
	};


	/// �h���b�O�����b�v���󂯎��R���g���[����\���B
	/// �v���ӁI���̃N���X�̓R���X�g���N�^�����ɓn���� Control ������ɔj�󂵂Ȃ��ƃ��������[�N����B
	class Target : private NonCopyable {
	public:
		/// ����������ԁB
		Target();
		Target(Target&& value);
		/// �h���b�O���h���b�v���󂯎��R���g���[�����w�肵�č쐬�B
		Target(Control& control);
		~Target();
		Target& operator=(Target&& value);

	public:
		/// �h���b�v�����C�x���g�B
		Listener<DragDrop::Drop&>& onDrop();
		/// �h���b�O���̃}�E�X�J�[�\�����R���g���[����ɓ������C�x���g�B������ DragDrop::Enter::data() �֐����ǂ̃f�[�^�������Ă��邩���ׂ�
		/// �����ł���f�[�^��������� DragDrop::Enter::effect() �� DragDrop::Effect::none ���w�肵���肷��B
		Listener<DragDrop::Enter&>& onEnter();
		/// �h���b�O���̃}�E�X�J�[�\�����R���g���[���ォ��o���C�x���g�B
		Listener<DragDrop::Leave&>& onLeave();
		/// �h���b�O���Ƀ}�E�X�J�[�\�����R���g���[������ړ������C�x���g�B������ DragDrop::Move::data() �֐����ǂ̃f�[�^�������Ă��邩���ׂ�
		/// �����ł���f�[�^��������� DragDrop::Move::effect() �� DragDrop::Effect::none ���w�肵���肷��B
		Listener<DragDrop::Move&>& onMove();

	private:
		::balor::system::ComPtr<DropTarget> _dropTarget;
	};


public:
	/// �}�E�X�{�^���������Ȃ���ړ��������Ƀh���b�O���h���b�v���J�n����ړ��͈͂̃V�X�e���W���B
	static Size defaultDragSize();
};



	}
}