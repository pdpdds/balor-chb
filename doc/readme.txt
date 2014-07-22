�����@

C++ ��WIN32 API ���g���� GUI �v���O���~���O���y�ɂ������B
��̓I�ɂ�Java SDK �� .NET Framework �̂悤�Ɏ�y�Ŏg���₷���A
MFC �̂悤�� WIN32 API �ƘA�g���₷�����C�u�������~�����B



��balor�Ƃ�

C++ Windows GUI ���C�u�����ł��B

Java �� .NET �̂悤�Ɏ�y�Ŏg���₷���A
MFC �̂悤�� WIN32 API �ƘA�g���₷�����C�u������ڎw���܂��B

������

�E.NET �� Java ���C�N�ȃC���^�[�t�F�[�X�B
�EWIN32 API �� STL �ƘA�g���₷���B
�E�����֐��i�����_���j�ɂ��C�x���g�L�q�B
�E�X�^�e�B�b�N�����N���C�u����
�E�E�Ӓl�Q�ƃT�|�[�g�ɂ���ăC���X�^���X�쐬�Ƀq�[�v���������蓖�Ă��������Ȃ��B
�EWinMain �֐��������ŏ�����B
�E���C�u�����w�b�_�t�@�C���� windows.h ���C���N���[�h���Ȃ��B
�E�C���e���Z���X�Ŋ֐��̃R�����g�\���B



���Ή��J����

Visau C++ 2010 Express Edition �ȍ~



�������

Windows XP �ȍ~
�U�S�r�b�g�ł͑Ή��\��B




�����C�Z���X

balor ���C�u�����ɂ��Ē��쌠�͕������܂���i�ł��Ȃ��j��
�z�z�����̓p�u���b�N�h���C���\�t�g�E�F�A (public domain software, PDS)�Ɠ����Ƃ��܂� �B
�񏤗p�A���p���킸�g�p�ɂ����萧���͂���܂���B
�{���C�u�������g�p���邱�ƂŐ����������Ȃ鑹�Q�ɂ��Ă��ӔC�͑S�Ďg�p�ғ��l�������܂��B





���g�p���@

�܂��o�b�� Visual C++ 2010 �ȍ~���C���X�g�[������Ă��Ȃ��ꍇ�̓C���X�g�[�����ĉ������B
���Ƀ_�E�����[�h���� balor �̈��k�t�@�C����K���ȃf�B���N�g���ɉ𓀂��܂��B
�𓀂����f�B���N�g�����́usamples�v�̒��ɃT���v���v���W�F�N�g������̂�
Visual C++ �ł��̂܂܃R���p�C���ł��邱�Ƃ��m�F���܂��B

Visual C++ ���N�����A�uWin32 �v���W�F�N�g�v��V�K�쐬���܂��B
�v���W�F�N�g�̃v���p�e�B���J����

�\���v���p�e�B���u�b�{�{�f�B���N�g�����C���N���[�h�f�B���N�g��

�� balor �f�B���N�g�����́uinclude�v�f�B���N�g����ǉ����܂��B

�\���v���p�e�B���u�b�{�{�f�B���N�g�������C�u�����f�B���N�g��

�� balor �f�B���N�g�����́ulib�v�f�B���N�g����ǉ����܂��B

�ȏ�̐ݒ�� balor ���C�u�������g����悤�ɂȂ�܂����B
�����Ɉȉ��� Hello world �T���v���R�[�h���R���p�C�����Č��ĉ������B

#include <Windows.h>
#include <balor/gui/all.hpp>

using namespace balor::gui;


int APIENTRY WinMain(HINSTANCE , HINSTANCE , LPSTR , int ) {
	Frame frame(L"Hello world");
	frame.onPaint() = [&] (Frame::Paint& e) {
		e.graphics().drawText(L"Hello world", 20, 10);
	};
	frame.runMessageLoop();
	return 0;
}



�������

syanji

����A�s��A�v�]�A�ӌ����͌����T�C�g�̃u���O�R�����g�ɂĎ󂯕t���܂��B
http://d.hatena.ne.jp/syanji/
