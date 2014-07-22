#pragma once


namespace balor {
	namespace graphics {



/**
 * GDI+ ���C�u�����̏������ƏI��������������B
 * 
 * balor �̃N���X�������Ŏg�p���Ă���A��ɉ摜�̓ǂݍ��݂�ۑ����ɏ����������B
 * ���[�U�v���O�������ł���ȏ�� GDI+ �͎g��Ȃ��ꍇ�� uninitialize() ���ĂԂ��Ƃ��o����B
 * uninitialize() ���Ă΂Ȃ������ꍇ�ł��v���Z�X�I�����Ɏ����I�ɌĂ΂��B
 */
class GdiplusInitializer {
public:
	/// GDI+�̏��������s��.
	/// ���� initialize �֐����Ă΂�Ă����牽�����Ȃ��B
	static void initialize();
	/// �����ς݂��ۂ���Ԃ�
	static bool initialized();
	/// GDI+�̏I���������s��.
	/// initialize �֐����Ă΂�Ă��Ȃ������� uninitialize �֐����Ă΂�Ă����牽�����Ȃ��B
	static void uninitialize();
};



	}
}