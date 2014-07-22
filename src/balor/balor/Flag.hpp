#pragma once


namespace balor {



/**
 * �r�b�g���Z�� bool �l���g���Ă킩��₷������B
 * 
 * WIN32 API �ɑ������݂���t���O�萔��?��Ɏg�p����B
 * std::bitset �̓r�b�g�ʒu��?�X�N�ł͂Ȃ������ʒu�Ŏw�肹�˂΂Ȃ炸�A����?�Ƃ̑��ݕϊ����ȒP�ł͂Ȃ��B
 */
template<typename T>
class Flag {
public:
	/// �����������ɍ쐬�B
	Flag() {}
	/// �l����쐬�B
	Flag(T value) : _value(value) {}
	Flag(const Flag& value) : _value(value._value) {}

	/// �l����ԁB
	Flag& operator=(T value) { _value = value; return *this; }

public:
	/// �w�肵���r�b�g?�X�N�̃r�b�g���I���܂��I�t�ɂ���B
	Flag& set(T mask, bool on = true) { _value = on ? (_value | mask) : (_value & ~mask); return *this; }

public:
	/// �l�ɕϊ��B
	operator T() const { return _value; }
	/// �w�肵���r�b�g?�X�N�̃r�b�g�����ׂăI�����ǂ����B
	bool operator [] (T mask) const { return (_value & mask) == mask; }

private:
	T _value;
};


/// �C��?����t���O�ւ̕ϊ��֐�
template<typename T>
Flag<T> toFlag(T value) { return Flag<T>(value); }



}