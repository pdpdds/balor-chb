#pragma once


namespace balor {
	namespace test {



/**
 * �}�N�����g��Ȃ� assert�B��Ƀw�b�_�݂̂Ŏ��������e���v���[�g�N���X�Ŏg�p����B
 *
 * balor �ł͓Ǝ��� assert �}�N���͎g���Ă��Ȃ����v���W�F�N�g�ɂ���Ă͉��� assert �}�N�����g����������Ȃ��̂ł��̑΍�B
 * noMacroAssert �֐����ł͒P��assert���s�����A�\�������\�[�X�R�[�h�ʒu�͌Œ肳��Ă��܂��̂Ń��j�b�g�e�X�g���f�o�b�K�ł̎g�p���O��B
 * �����[�X�R���p�C�����ɂ��c���Ă��܂�����̊֐��Ȃ̂ōœK���ō폜����邱�Ƃ����҂���B
 */
void noMacroAssert(bool expression);



	}
}