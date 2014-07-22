#pragma once


namespace balor {
	namespace test {



/**
 * ���j�b�g�e�X�g�̏�������s�����������񋟂���B
 *
 * testCase �}�N�����g���ăe�X�g�P�[�X�̊֐���o�^���A�֐��̒��ł� testAssert, testThrow ���̃}�N�����g���ăe�X�g�R�[�h�������B
 * UnitTest::run() �֐��Ńe�X�g�����s���A���ʂ� Debug::write() �֐��ŏo�͂����B
 *
 * <h3>�E���ӁI</h3>
 * run �����o�֐��ł� assert �}�N���̎��s���e�X�g����ׂɂb�����^�C���� abort �֐����Ă΂��� balor::test::UnitTest::AssertionFailedException ��O�𓊂���悤�ɂ��Ă���B
 * abort �֐����g�p����v���O�����̃e�X�g�ł͂�����l������K�v������B
 */
class UnitTest {
public:
	/// registerTestCase���ĂԂ��߂����̃N���X�BtestCase�}�N�����Ŏg����B
	class FunctionRegister {
	public:
		FunctionRegister(void (*function) (), const char* functionName, const char* fileName, int line);
	};

	/// ���j�b�g�e�X�g���� assert �Ɏ��s����ƃX���[������O.
	struct AssertionFailedException {
	};

public:
	/// ���݂̃e�X�g�P�[�X�ł̓n���h�����[�N�̃`�F�b�N���K�v�Ȃ����Ƃ�ʒm����B
	static void ignoreHandleLeakCheck();
	/// �e�X�g�����s���ł��邩�ۂ���Ԃ��B
	static bool isRunning();
	/// �e�X�g�P�[�X�̊֐���o�^����BtestCase�}�N�����Ŏg����B
	static void registerTestCase(void (*function) (), const char* functionName, const char* fileName, int line);
	/// �e�X�g���ʂ����|�[�g����BtestAssert�AtestThrow�AtstAssert�}�N�����Ŏg����B
	static void report(bool result, const char* expression, int line);
	/// �o�^���ꂽ�e�X�g�P�[�X��S�Ď��s����B
	static void run();
	/// �o�^���ꂽ�e�X�g�P�[�X�̂����A�t�@�C������pettern�Ŏ�����鐳�K�\���Ɉ�v������̂��������s����B
	static void run(const char* pettern);
};


// ���j�b�g�e�X�g�R�[�h�Ŏg�p����}�N���֐��Q�B


/// �e�X�g�P�[�X�֐���o�^���A��`����B
#define testCase(functionName) \
void functionName();\
::balor::test::UnitTest::FunctionRegister functionName##Register(functionName, #functionName, __FILE__, __LINE__);\
void functionName()


/// expression �� true ���ǂ������e�X�g����B
#define testAssert(expression) ::balor::test::UnitTest::report((expression) ? true : false, #expression, __LINE__);


/// expression �� assert �Ɏ��s���邩�ǂ������e�X�g����BNDEBUG�}�N������`����Ă���ꍇ�͎��s���炵�Ȃ����Ƃɒ��ӂ���B
#if defined(NDEBUG)
#define testAssertionFailed(expression) ::balor::test::UnitTest::report(true, #expression, __LINE__);
#else
#define testAssertionFailed(expression) try { expression; ::balor::test::UnitTest::report(false, #expression, __LINE__); } catch (::balor::test::UnitTest::AssertionFailedException& ) { ::balor::test::UnitTest::report(true, #expression, __LINE__); }
#endif


/// expression ����O�� throw ���Ȃ����ǂ������e�X�g����B
#define testNoThrow(expression) try { expression; ::balor::test::UnitTest::report(true, #expression, __LINE__); } catch (...) { ::balor::test::UnitTest::report(false, #expression, __LINE__); }


/// expression �� exception �� throw ���邩�ǂ������e�X�g����B
#define testThrow(expression, exception) try { expression; ::balor::test::UnitTest::report(false, #expression, __LINE__); } catch (exception& ) { ::balor::test::UnitTest::report(true, #expression, __LINE__); }



	}
}