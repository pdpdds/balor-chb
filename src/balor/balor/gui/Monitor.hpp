#pragma once

#include <balor/Enum.hpp>
#include <balor/NonCopyable.hpp>

struct HMONITOR__;
struct HWND__;

namespace std {
template<typename T> class allocator;
template<typename T, typename A> class vector;
}

namespace balor {
	class Point;
	class Rectangle;
	class String;
}


namespace balor {
	namespace gui {



/**
 * �o�b�̃��j�^�[��\���B
 * 
 * ���z��ʂƂ̓}���`���j�^���ŕ����̃��j�^����̃��j�^�Ƃ��Ĉ��������z�I�ȋ��僂�j�^�̂��ƁB
 * ���z��ʍ��W�̓v���C�}�����j�^�̍�������_�Ƃ��A�v���C�}�����j�^�̍��ɂ��郂�j�^�ł͈ʒu�����̐��ɁA�E�ɂ��郂�j�^�ł͈ʒu�͐��̐��ɂȂ�B
 */
class Monitor : private NonCopyable {
public:
	typedef ::HMONITOR__* HMONITOR;
	typedef ::HWND__* HWND;

	/// ���j�^�̐ݒu�����B
	struct Orientation {
		enum _enum {
			angle0   = 0, /// ���ʂɒu���Ă���B
			angle90  = 1, /// ���v���ɂX�O�x��]���Ă���B
			angle180 = 2, /// ���v���ɂP�W�O�x��]���Ă���B
			angle270 = 3, /// ���v���ɂQ�V�O�x��]���Ă���B
		};
		BALOR_NAMED_ENUM_MEMBERS(Orientation);
	};


public:
	/// �n���h������쐬����Bnullptr �̏ꍇ�̓v���C�}�����j�^�B
	explicit Monitor(HMONITOR handle = nullptr);
	Monitor(Monitor&& value);
	Monitor& operator=(Monitor&& value);

public:
	/// �r�b�g�[�x�B
	int bitsPerPixel() const;
	/// ���z��ʏ�ł̈ʒu�ƃ��j�^�̉𑜓x�B
	Rectangle bounds() const;
	/// �f�o�C�X���B
	String deviceName() const;
	/// �w�肵���R���g���[���������Ƃ��傫�Ȗʐς��߂Ă��郂�j�^��Ԃ��B
	static Monitor fromControl(HWND control);
	/// �w�肵�����z��ʍ��W�ɂ��郂�j�^��Ԃ��B
	static Monitor fromPoint(const Point& point);
	//// �w�肵�����z��ʏ�̋�`���ł��傫�Ȗʐς��߂郂�j�^��Ԃ��B
	static Monitor fromRectangle(const Rectangle& rect);
	/// �S�Ẵ��j�^��񋓂���B���z�I�ȃf�o�C�X���񋓂���B
	static std::vector<Monitor, std::allocator<Monitor> > monitors();
	/// �S�Ẵ��j�^�������r�b�g�[�x���ǂ����B�i�������t�H�[�}�b�g�͈Ⴄ�\��������j
	static bool monitorsHasSameBitsPerPixel();
	/// ���j�^�̐ݒu�����B
	Monitor::Orientation orientation() const;
	/// �v���C�}�����j�^���ǂ����B
	bool primary() const;
	/// �v���C�}�����j�^���擾����B
	static Monitor primaryMonitor();
	/// ���t���b�V�����[�g�i�����������g���j�B�V�X�e���f�t�H���g�̏ꍇ�͂O�܂��͂P�B
	int refreshRate() const;
	static Rectangle virtualMonitorBounds();
	/// ���j�^�̐��Bmonitors().size() �Ƃ͕K��������v���Ȃ��B
	static int visibleMonitorsCount();
	/// �f�X�N�g�b�v�̍�Ɨ̈�Bbounds() ����^�X�N�o�[�̈�����������́B
	Rectangle workingArea() const;

private:
	HMONITOR _handle;
};



	}
}