#pragma once

#include <vector>

#include <balor/gui/Control.hpp>
#include <balor/gui/Padding.hpp>
#include <balor/Enum.hpp>


namespace balor {
	namespace gui {



/**
 * �q�R���g���[����e�̘g�Ƀh�b�L���O�����郌�C�A�E�g�B
 * 
 * ���C�A�E�g�����͎����ōs���Ȃ��̂� onResized �C�x���g���Ŏ蓮�ōX�V����K�v������B
 * �q�R���g���[����e�ɒǉ��������i�\���D��x�j�̓��C�A�E�g�ɉe����^����B
 * DockLayout::Style::fill �̃R���g���[���͕K���Ō�ɒǉ�����Ȃ���΂Ȃ�Ȃ��B
 * �l�ӂɃh�b�L���O����ꍇ�͒ǉ��������ɓ����ɂނ����Ĕz�u�����B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"DockLayout Sample");

	Button left(frame, 0, 0, 200, 200, L"����");
	Button top(frame, 0, 0, 200, 200, L"�㑤");
	Button bottom(frame, 0, 0, 200, 200, L"����");
	Button right(frame, 0, 0, 200, 200, L"�E��");
	Button center(frame, 0, 0, 0, 0, L"����");

	DockLayout layout(frame);
	layout.setStyle(left, DockLayout::Style::left);
	layout.setStyle(top, DockLayout::Style::top);
	layout.setStyle(bottom, DockLayout::Style::bottom);
	layout.setStyle(right, DockLayout::Style::right);
	layout.setStyle(center, DockLayout::Style::fill);
	layout.perform();
	frame.onResized() = [&] (Frame::Resized& ) {
		layout.perform();
	};

	// �t���[�����������������ăR���g���[�����ׂ�Ȃ��悤�ɂ���B
	layout.setMinimumSize(center, center.getPreferredSize());
	frame.onResizing() = [&] (Frame::Resizing& e) {
		e.minTrackSize(layout.preferredSize());
	};

	frame.runMessageLoop();
 * </code></pre>
 */
class DockLayout : private NonCopyable {
public:
	/// �ǂ��Ƀh�b�L���O���邩�B
	struct Style {
		enum _enum {
			none  , /// �������Ȃ��B
			left  , /// ���Ƀh�b�L���O�B
			top   , /// �㕔�Ƀh�b�L���O�B
			right , /// �E�Ƀh�b�L���O�B
			bottom, /// �����Ƀh�b�L���O�B
			fill  , /// �󂢂Ă��钆�S���̋�Ԃ��߂�B
		};
		BALOR_NAMED_ENUM_MEMBERS(Style);
	};

public:
	DockLayout();
	DockLayout(DockLayout&& value);
	DockLayout(Control& target);
	~DockLayout();
	DockLayout& operator=(DockLayout&& value);

public:
	/// �q�̍ŏ��̑傫���B�����l�� Size(0, 0)�B
	Size getMinimumSize(Control& child) const;
	/// �q�̃h�b�L���O�ʒu�B�����l�� DockLayout::Style::none�B
	DockLayout::Style getStyle(Control& child) const;
	/// �e�̘g�Ǝq�R���g���[���̊Ԃ̌��Ԃ̑傫���B�����l�� Padding(0, 0, 0, 0)�B
	Padding padding() const;
	void padding(const Padding& value);
	void padding(int left, int top, int right, int bottom);
	/// ���C�A�E�g���X�V����B
	void perform();
	/// �S�Ă̎q�R���g���[�����\���ł��A�h�b�L���O����q�R���g���[���Ƃ��̑��̃R���g���[�����d�Ȃ�Ȃ��Œ���̑傫���B
	Size preferredSize() const;
	/// Scaler ���g���ă��C�A�E�g�ݒ���X�P�[�����O����B�R���g���[���͕ʓr�X�P�[�����O���K�v�B
	void scale(const Scaler& scaler);
	/// �q�̍ŏ��̑傫����ݒ肷��B
	void setMinimumSize(Control& child, const Size value);
	void setMinimumSize(Control& child, int width, int height);
	/// �q�̃h�b�L���O�ʒu��ݒ肷��B
	void setStyle(Control& child, DockLayout::Style value);
	/// ���C�A�E�g�Ώۂ̐e�R���g���[���B
	Control* target();

private:
	struct ChildInfo {
		ChildInfo();
		Reference<Control> child;
		Style style;
		Size minimumSize;
	};

	const ChildInfo* _findInfo(Control& child) const;
	ChildInfo& _getInfo(Control& child);

	Reference<Control> _target;
	Padding _padding;
	std::vector<ChildInfo> _childInfos;
};



	}
}