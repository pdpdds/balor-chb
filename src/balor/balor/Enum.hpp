#pragma once


namespace balor {



/**
 * ���O�t�� enum �̒�`���T�|�[�g����}�N���֐��B
 *
 * enum �𖼑O�t�� struct �܂��� class �̒��ɓ���Ă��̃}�N���Ń����o�[�̒�`�����邱�Ƃ� enum �� struct �Ԃ̎����I�ȕϊ����s����悤�ɂ���B
 * name �� struct �����w�肷��B�񋓑̖��͕K�� _enum �Ƃ��邱�ƁB�l�̐������`�F�b�N�֐����K�v�ȏꍇ�� _validate �֐����������邱�ƁB
 */
#define BALOR_NAMED_ENUM_MEMBERS(name) \
	name () {}\
	explicit name (int value) : _value(static_cast<_enum>(value)) {}\
	name (_enum value) : _value(value) {}\
	operator _enum() const { return _value; }\
	static bool _validate(name value);\
	_enum _value;


/**
 * �_�����Z�\�Ȗ��O�t�� enum �̒�`���T�|�[�g����}�N���֐��B
 *
 * |�A&�A~ ���Z�q���T�|�[�g���鑼�� BALOR_NAMED_ENUM_MEMBERS �Ɠ����B
 */
#define BALOR_NAMED_LOGICAL_ENUM_MEMBERS(name) \
	BALOR_NAMED_ENUM_MEMBERS(name)\
	name& operator|=(_enum value) { _value = _enum(_value | value); return *this; }\
	friend _enum operator|(_enum lhs, _enum rhs) { return name::_enum(int(lhs) | rhs); }\
	friend _enum operator&(_enum lhs, _enum rhs) { return name::_enum(int(lhs) & rhs); }\
	friend _enum operator~(_enum value) { return name::_enum(~int(value)); }



}