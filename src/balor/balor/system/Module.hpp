#pragma once

#include <balor/NonCopyable.hpp>
#include <balor/StringRange.hpp>

struct HINSTANCE__;

namespace balor {
	namespace io {
		class File;
	}
}


namespace balor {
	namespace system {



/**
 * exe �t�@�C���� DLL �t�@�C����\���B���݂̃v���Z�X���W���[���̃p�X���擾������ADLL ���v���Z�X�̃A�h���X��ԓ��Ƀ}�b�v���A�֐��̃A�h���X���擾�ł���B
 */
class Module : private NonCopyable {
public:
	typedef ::HINSTANCE__* HMODULE; // HMODULE == HINSTANCE�B
	typedef ::balor::io::File File;

public:
	/// ���݂̃v���Z�X���W���[���ō쐬�B�i���k���n���h���ō쐬�j
	Module();
	///	�n���h������쐬�B
	explicit Module(HMODULE handle, bool owned = false);
	/// DLL ������쐬�B
	explicit Module(StringRange fileName);
	Module(Module&& value);
	~Module();
	Module& operator=(Module&& value);
	
public:
	/// ���݂̃v���Z�X�̃��W���[����Ԃ��B
	static Module current();
	/// ���W���[���t�@�C���̂���f�B���N�g����Ԃ��B
	File directory() const;
	/// ���W���[���t�@�C����Ԃ�
	File file() const;
	/// ���Ƀ��[�h����Ă��� DLL ��������ΕԂ��B������Ȃ���΋�� Module ��Ԃ��B
	static Module find(StringRange fileName);
	/// �֐��̌^���w�肵�Ċ֐������� DLL �Ɋ܂܂��֐��A�h���X��Ԃ��B�֐���������Ȃ���� nullptr ��Ԃ��B�֐����� Unicode �ł͂Ȃ����ɒ��ӁB
	template<typename Function> Function* getFunction(ByteStringRange functionName) { return reinterpret_cast<Function*>(_getVoidFunction(functionName)); }
	/// �f�X�g���N�^�Ńn���h����j�����邩�ǂ����B�ύX�͗v���ӁB
	bool owned() const;
	void owned(bool value);

public:
	/// ���W���[���n���h���ւ̎����ϊ��� null �`�F�b�N�p�B
	operator HMODULE() const { return _handle; }

private:
	void* _getVoidFunction(ByteStringRange functionName);

	HMODULE _handle;
	bool _owned;
};



	}
}