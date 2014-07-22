#pragma once

#include <balor/NonCopyable.hpp>


namespace balor {

class Referenceable;



/// Reference �N���X�̌^�Ɉˑ����Ȃ����������B
class ReferenceBase {
protected:
	friend Referenceable;

protected:
	ReferenceBase();
	ReferenceBase(const ReferenceBase& value);
	ReferenceBase(Referenceable* pointer);
	~ReferenceBase();

protected:
	void _attach(Referenceable* pointer);
	void _detach();

protected:
	Referenceable* _pointer;
	ReferenceBase* _next;
};



/**
 * �N���X�̈�Α��̎Q�ƃ|�C���^��\���B
 *
 * Referenceable �N���X�̔h���N���X�̃|�C���^�������邱�Ƃ��ł��A���̃|�C���^�̂悤�ɂӂ�܂��B
 * �Q�Ɛ�̃f�X�g���N�^���Ă΂��ƃ|�C���^�͎����I�Ƀk���ɂȂ�B
 * �܂��Q�Ɛ悪���[�u�Z�}���e�B�N�X�ɂ���Ĉړ��������A�|�C���^���ړ���ɍX�V�����B
 *
 * C++ �ł̓N���X���m�̎Q�Ƃ� shared_ptr ���g���������������ׂ̈ɂ̓N���X���q�[�v�������Ɋ��蓖�Ă���K�v������B
 * �E�Ӓl�Q�Ƃ̃T�|�[�g�ɂ���ăR�s�[�֎~�N���X�𖳗����X�}�[�g�|�C���^�ŊǗ�����K�v�������ꂽ�̂�
 * �N���X���m�̎Q�Ƃɂ��Ă����������蓖�Ă����邱�ƂȂ���������d�g�݂�������B���������l�Ȃ̂Ń��C�t�T�C�N���̊Ǘ��͂����܂Ŏ蓮�B
 *
 * <h3>�E�T���v���R�[�h</h3>
 * <pre><code>
	Frame frame(L"Reference Sample");

	Reference<Button> r;
	assert(!r);
	{
		Button button(frame, 20, 10, 0, 0, L"�{�^��");

		r = &button;
		assert(r);
		assert(r->text() == L"�{�^��");

		button = Button(frame, 20, 10, 0, 0, L"�{�^��2");
		assert(!r); // button �͍�蒼���ꂽ�̂Ŏ����I�ɎQ�Ƃ� nullptr �ɂȂ�B

		r = &button;
		assert(r);
		assert(r->text() == L"�{�^��2");
	}
	assert(!r); // button �͔j�����ꂽ�̂Ŏ����I�ɎQ�Ƃ� nullptr �ɂȂ�B
 * </code></pre>
 */
template<typename T>
class Reference : public ReferenceBase {
public:
	/// �k���|�C���^�Ƃ��č쐬�B
	Reference() {}
	Reference(const Reference& value) : ReferenceBase(value) {}
	/// �Q�Ɛ�̃|�C���^����쐬�B
	Reference(T* pointer) : ReferenceBase(pointer) {}
	~Reference() {}

	Reference& operator=(const Reference& value) {
		if (this != &value) {
			_detach();
			_attach(value._pointer);
		}
		return *this;
	}
	/// �Q�Ɛ�̃|�C���^��ύX�B
	Reference& operator=(T* pointer) {
		_detach();
		_attach(pointer);
		return *this;
	}

public:
	/// �Q�Ɛ�̃|�C���^�̎擾�B
	operator T*() const { return static_cast<T*>(_pointer); } // ������ reinterpret_cast ���g���Ă͂Ȃ�Ȃ��B���z�֐��������Ȃ���ꂩ�玝�h���N���X�ւ̃L���X�g������ɓ����Ȃ��B
	/// �Q�Ɛ�ւ̃A�N�Z�X�B
	T* operator->() const { return static_cast<T*>(_pointer); }
};



/**
 * Reference �N���X�ŎQ�Ƃł���N���X�̊��N���X�B
 * ���̃N���X���p������N���X�ł͕K���E�Ӓl�Q�ƃR���X�g���N�^�ƉE�Ӓl�Q�Ƒ�����Z�q���`����
 * ���̃N���X�̉E�Ӓl�Q�ƃR���X�g���N�^�ƉE�Ӓl�Q�Ƒ�����Z�q���ĂԕK�v������B
 * ���ۂ̎g������ Reference �N���X�̃h�L�������g���Q�ƁB
 */
class Referenceable : private NonCopyable { // ��Α��Q�ƂȂ̂ŃR�s�[�֎~
public:
	friend ReferenceBase;

protected:
	Referenceable();
	/// �h���N���X����ĂԕK�v������B
	Referenceable(Referenceable&& value);
	~Referenceable();
	/// �h���N���X����ĂԕK�v������B
	Referenceable& operator=(Referenceable&& value);

private:
	ReferenceBase* _first;
};



}