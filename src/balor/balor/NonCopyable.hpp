#pragma once


namespace balor {



/**
 * ���̃N���X���p������N���X�̃R�s�[���֎~����B
 *
 * boost::noncopyable �Ɠ����Bbalor ���C�u�����ł̓R�s�[���֎~���Ă���N���X�ł��E�Ӓl�Q�Ƃ������Ɏ��R���X�g���N�^�A������Z�q����������̂�
 * �R�s�[����邱�ƂȂ��֐��̖߂�l�ɂ��邱�Ƃ��ł��A�r�s�k�R���e�i�Ɋi�[���邱�Ƃ��ł��A�C�ӂ̃^�C�~���O�ňꎞ�I�u�W�F�N�g������đ�����ď��������ł���B
 *
 * ����Ȏԗւ̍Ĕ����͖{���ɂ������͂Ȃ����A����o�[�W������ boost �̃C���X�g�[���������������Ȃ��B
 */
class NonCopyable {
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable& );
	NonCopyable& operator=(const NonCopyable& );
};



}