#pragma once


namespace balor {
	namespace test {



/**
 * �R���X�g���N�^�A�f�X�g���N�^�A������Z�q�̌Ăяo���񐔂�ǐՂ���B
 * 
 * �R���e�i�����̃N���X�̃e�X�g�ɗp����B
 * �O���[�o���ϐ����g�p���Ă���̂Ń}���`�X���b�h��DLL�ł̎g�p�͍l���čs�����ƁB
 */
class InstanceTracer {
public:
	InstanceTracer();
	InstanceTracer(const InstanceTracer& value);
	InstanceTracer(InstanceTracer&& value);
	~InstanceTracer();

	InstanceTracer& operator=(const InstanceTracer& value);
	InstanceTracer& operator=(InstanceTracer&& value);

public:
	static int defaultConstructCount();
	static int copyConstructCount();
	static int rvalueConstructCount();
	static int destructCount();
	static int operatorEqualCount();
	static int rvalueOperatorEqualCount();

public:
	static void clearAllCount();
	static bool checkAllCount(int defaultConstructCount
							 ,int copyConstructCount
							 ,int rvalueConstructCount
							 ,int destructCount
							 ,int operatorEqualCount = 0
							 ,int rvalueOperatorEqualCount = 0);
};



	}
}