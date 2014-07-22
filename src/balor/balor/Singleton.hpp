#pragma once


namespace balor {

namespace detail {
void* getSingletonInstance(const type_info& info, void* (*createInstanceFunction)());
}



/**
 * �V���O���g���p??���̎�����񋟂���B
 *
 * �����s��?�ȃO��?�o���ϐ����A?��?�X���b�h�ł�DLL�𒴂��Ă����S�ɊǗ�����B
 * �e���v��?�g�����ɓn���N���X�� Singleton �N���X�ɑ΂��� friend �錾������ŃR���X�g���N?�ƃf�X�g���N?�� private �錾����Ɨǂ��B
 * DLL �v���W�F�N�g���܂ޕ����̃v���W�F�N�g�� balor ���g�p����ꍇ�A���s�t?�C���Ɠ����f�B���N�g���� balor_singleton.dll ��u�����ƁB
 * ���� DLL ��������Ȃ��ꍇ�� DLL �̂��Ƃ��l�����Ȃ��V���O���g���ɂȂ�B
 *
 * ���ӁI DLL ���ŃV���O���g���ɏ��߂ăA�N�Z�X���A�V���O���g���̃C���X?���X�o?�������ꍇ�͂��� DLL ���A����?�h����?�C?���O�ɒ��ӂ��邱�ƁB
 * �A����?�h������?�œo?�����C���X?���X��?�C��?�������ɂȂ��Ă��܂��΂��肩�A�C���X?���X���o?���݂��ǂ����̒������s���ȏ����ŗ����Ă��܂��B
 *
 * C++ �ɂ�����V���O���g���̎����ɂ͂�������肪����A���ꂼ���������K�v������B
 * 
 * <h3>�����P�F�X?�e�B�b�N���C�u������ DLL �Ƀ����N����� DLL ���ƂɃO��?�o���ϐ��̈悪���������B</h3>
 * DLL ���ƂɃ����N�����̂ł���͓��R�ł���A�O��?�o���ϐ��̃A�h���X�����łȂ��A�֐�?�C��?�� DLL ���ƂɈقȂ�B
 * ���Ƃ� DLL ����ł������Ƃ��Ă��A�A�v���P?�V������ exe �t?�C���Ƃ�����g������v���O�C���� DLL ��
 * �����X?�e�B�b�N���C�u�������g�p����ꍇ�A�A�v���P?�V������ DLL �ŕʁX�Ƀ��C�u�����������N�����B
 * ���̖��͂��������X?�e�B�b�N���C�u�������g�p���Ȃ���Ή������邪�A
 * �����ł̓�?�U���X?�e�B�b�N���C�u�����ɂ���̂� DLL �ɂ���̂��I���ł���悤�ɂ������ꍇ�ǂ����邩���l����B
 * 
 * <h3>�����Q�Fstatic �ϐ��̏�������?��?�X���b�h�ł͂��܂������Ȃ��B</h3>
 * �X���b�h�P���ŏ��Ɋ֐����Ăяo����static�ϐ��̏����������ɓ�������A
 * �X���b�h�Q�������Ɋ֐����Ăяo���ƁA�����n�ɂ���邪�������������d�����đ����Ă��܂����A���邢��
 * ���ɏ������ς݂ł���Ɣ��f���ď������������X�L�b�v���A���������̃I�u�W�F�N�g�ɐG��Ă��܂��B
 * ���̖��̉�����Ƃ��ėǂ��m���Ă���̂� DCLP�iThe Double-Checked Locking Optimization Pattern�j����
 * ���̎�?�͊��Ɉˑ�������?���g��Ȃ�������S�ł͂Ȃ��B
 *
 * http://www.nwcpp.org/Downloads/2004/DCLP_notes.pdf
 * http://d.hatena.ne.jp/yupo5656/20041011/p1
 *
 * DCLP �͈ȉ��̂悤�ȃR?�h�ɂȂ邪
 * <pre><code>
 * static T* instance = 0;
 * if (instance == 0) { // ���C���P
 *     mutex::scoped_lock lock(mutex);
 *     if (instance == 0) { // �ēx?�F�b�N���Ȃ���Γ�d��new�y�уR���X�g���N�g����鋰�ꂪ����
 *         instance = new T(); // ���C���Q
 *     }
 * }
 * </code></pre>
 * ���̓��C���Q�ŁA�����ł� (1)T�̃��������蓖�āA(2)T�̃R���X�g���N?�A(3)instance�ւ̴��� �̎O�̏������s�����A
 * (1)��(2)��(3)�̏��ɏ��������Ȃ�Ζ��͔������Ȃ����R���p�C���̍œK���� CPU �̕�����s�ɂ����(1)��(3)��(2)�̂悤�Ɏ��s����邱�Ƃ����肤��B
 * �����Ȃ�ƃ��C���P�̔���ŏ��������I����Ă��Ȃ��̂ɏ��������ꂽ�Ɣ��f���ꂤ��B
 * �y?�p?�ɂ���悤�Ɋ��Ɉˑ������?�ŉ�����邱�Ƃ͉�?�����C���X?���X�̏��������������Ă�
 * mutex �̏������ɂ��Ă͓��X����ƂȂ��Ă���A��������Ȃ��B�܂��A���P�F���ˑR�Ƃ��Ďc��B
 *
 * <h3>��������:</h3>
 * ���P�F����������ׂɁAtype_info?���̂ւ�?�C��?�Ɗ��蓖�Ă�ꂽ�C���X?���X�ւ�?�C��?�̑g��
 * ������DLL�̒��ɕۑ�����Bstatic�ϐ��̏��������������邽�тɂ��� DLL �̊֐����Ă��
 * type_info::oprator== �����藧�� type_info ?���̂�?�C��?�����ɓo?����Ă��邩�ǂ������ׁA
 * �o?����Ă��Ȃ��ꍇ�̓C���X?���X���쐬���ĐV���ɓo?���A�o?����Ă���ꍇ�͓o?�ς݂̃C���X?���X��?�C��?��Ԃ��悤�ɂ���B
 * DLL ���ƂɕʁX�Ƀ����N���ꂽ���ꂼ��̃R?�h���ŁA����?�ɑ΂��� &typeid(?��) ���s���Ƃ��ꂼ��Ⴄ�A�h���X���Ԃ��Ă��邪�A
 * ���҂� typeid::operator== ���s���Ƃ����� true ���Ԃ鋓���Ɉˑ����Ă���B
 * ����ňقȂ�DLL�Ԃł����Ă������A�h���X��Ԃ����Ƃ��ۏ؂����B
 * �܂��A���� DLL �֐������� boost::mutex �Ŋ��S�Ƀ��b�N����B��������s����Ă����̂Ȃ������ł���A
 * ���b�N�Ƀ������o���A���܂܂��ׁADCLP �̂悤�Ȏ�?���s�v�ƂȂ�B
 * DLL�̃O��?�o���ϐ��̓v���Z�X�ɃA?�b?����O�ɏ���������邱�Ƃ��ۏ؂���Ă���ׁA
 * (http://msdn.microsoft.com/ja-jp/library/988ye33t(VS.80).aspx)
 * mutex �̏������͖��Ȃ��B
 * �������ADLL ���g�p���Ȃ��v���W�F�N�g�ł͂��̏������̂����ʂɂȂ�ׁA������ DLL ��������Ȃ��ꍇ�ɂ͂����̏������s��Ȃ��悤�ɂ���B
 * 
 *
 * <h3>����?�F</h3>
 * ������DLL�� exe �ɕt�������Ȃ���΂Ȃ�Ȃ��B
 * �O��?�o���ϐ��� mutex ���g�p����ׁA������?�̏��������������ʂ��ă��b�N�����B
 * �܂��Atype_info ?���̂ɂ� operator== �����Ȃ��̂� map ���g�����Avector �ɂ��S�������s���B
 * ���ׁ̈Astatic �ϐ��̏��������̂݃p�t�H??���X��?���ɂȂ�B
 * �Ȃ� type_info::name �֐���?�̔�r�ɗp���邱�Ƃ͂ł��Ȃ��B
 * �������O��Ԃ��g���ďd������?�����?�����ꍇ�Atype_info::name �֐��ł͗��҂���ʂł��Ȃ��B
 *
 * <h3>�E�T���v���R?�h</h3>
 * <pre><code>
	class MySingleton {
		friend Singleton<MySingleton>;
		MySingleton() {}
		~MySingleton() {}
	public:
		String text;
	};

	String text = Singleton<MySingleton>::get().text;
 * </code></pre>
 */
template<typename T>
class Singleton {
public:
	/// �V���O���g���C���X?���X�̎擾
	static T& get() {
		static T* instance = nullptr;

		if (!instance) {
			// ���̊֐��͕�������s����Ă����܂�Ȃ�
			instance = static_cast<T*>(::balor::detail::getSingletonInstance(typeid(T), Singleton<T>::createInstance));
			// lock �Ƀ������o���A���܂܂��̂Ń������œK���͂���Ȃ�
		}
		return *instance;
	}

	// ���C�u������?��?�X���b�h�Ŏg��Ȃ����ADLL �v���W�F�N�g���g��Ȃ��Ƃ����ꍇ�͂��̎����ŗǂ��B�ȒP�ȃA�v���P?�V�����̂قƂ�ǂɓ��Ă͂܂邾�낤�B
	// ���邢�� C++0x �Ɋ��S��?�������R���p�C���ł���΂��̎�����?��?�X���b�h�͖�肪�����Ȃ�B
	//static T& get() {
	//	static T instance;
	//	return instance;
	//}


private: // ��؂̐����A�R�s?�A�j�����ւ���
	Singleton();
	Singleton(const Singleton& );
	~Singleton();
	Singleton& operator=(const Singleton& );

private:
	static void* createInstance() {
		static T instance;
		return &instance;
	}
};



}