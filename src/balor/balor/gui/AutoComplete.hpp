#pragma once

#include <balor/system/ComPtr.hpp>
#include <balor/Enum.hpp>
#include <balor/Reference.hpp>
#include <balor/StringRangeArray.hpp>

struct IAutoComplete2;

namespace balor {
class String;
}


namespace balor {
	namespace gui {

class Edit;



/**
 * �G�f�B�b�g�R���g���[���ɓ���̕�������͂���ƕ�����̑����̌���񋓂������Ԃł���悤�ɂ���B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"AutoComplete Sample");

	Edit edit(frame, 20, 10, 0, 0, 10);
	const wchar_t* items[] = {
		L"012345",
		L"012abc",
		L"012������",
		L"abc",
		L"abcdef",
		L"������",
	};
	AutoComplete complete(edit, items);

	frame.runMessageLoop();
 * </code></pre>
 */
class AutoComplete : private NonCopyable {
public:
	/// �I�[�g�R���v���[�g�̓��샂�[�h�B
	struct Mode {
		enum _enum {
			append           = 0x40000000, /// �������ꂽ�����񂪃n�C���C�g����Ēǉ��\�������B
			suggest          = 0x10000000, /// �������ꂽ�����񂪃h���b�v�_�E�����X�g�ŕ\�������B
			appendAndSuggest = 0x50000000, /// append �� suggest �����B
		};
		BALOR_NAMED_ENUM_MEMBERS(Mode);
	};

	/// �V�X�e�����p�ӂ����I�[�g�R���v���[�g���镶���񃊃X�g�B�g�ݍ��킹�Ŏw�肷��B
	struct SystemItems {
		enum _enum {
			none                = 0         ,
			fileSystem          = 0x00000001, /// �t�@�C���V�X�e���̃p�X�B
			fileSystemDirectory = 0x00000020, /// �t�@�C���V�X�e���̃f�B���N�g���p�X�B
			urlHistory          = 0x00000002, /// �t�q�k�����B
			recentlyUsedUrl     = 0x00000004, /// �ŋߎg�����t�q�k���X�g�B
		};
		BALOR_NAMED_LOGICAL_ENUM_MEMBERS(SystemItems);
	};

public:
	AutoComplete();
	AutoComplete(AutoComplete&& value);
	/// �G�f�B�b�g�R���g���[���ƃI�[�g�R���v���[�g���镶����̔z�񂩂�쐬�B
	AutoComplete(Edit& target, StringRangeArray items, AutoComplete::Mode mode = Mode::appendAndSuggest);
	/// �G�f�B�b�g�R���g���[���ƃI�[�g�R���v���[�g���镶����̎�ނ���쐬�B
	AutoComplete(Edit& target, AutoComplete::SystemItems systemItems, AutoComplete::Mode mode = Mode::appendAndSuggest);
	~AutoComplete();
	AutoComplete& operator=(AutoComplete&& value);

public:
	/// �L�����ǂ����B
	bool enabled() const;
	void enabled(bool value);
	/// �I�[�g�R���v���[�g���镶����̔z��B
	std::vector<String, ::std::allocator<String> >& items() const;
	/// �I�[�g�R���v���[�g�̃��[�h�B
	AutoComplete::Mode mode() const;
	/// �V�X�e�����p�ӂ���I�[�g�R���v���[�g���镶����̔z��B
	AutoComplete::SystemItems systemItems() const;

private:
	class EnumString;

	Reference<Edit> _target;
	bool _enabled;
	Mode _mode;
	SystemItems _systemItems;
	::balor::system::ComPtr<::IAutoComplete2> _autoComplete;
	::balor::system::ComPtr<EnumString> _enumString;
};



	}
}