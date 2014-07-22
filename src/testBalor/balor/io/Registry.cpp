#include <balor/io/Registry.hpp>


#include <algorithm>
#include <cstdint>
#include <vector>
#pragma warning(push, 3)
#include <boost/assign/std/vector.hpp>
#pragma warning(pop)

#include <balor/system/EnvironmentVariable.hpp>
#include <balor/system/windows.hpp>
#include <balor/test/HandleLeakChecker.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/scopeExit.hpp>
#include <balor/String.hpp>


namespace balor {
	namespace io {
		namespace testRegistry {

using std::vector;
using std::move;
using namespace boost::assign;
using namespace balor::system;


namespace {
const wchar_t testKeyName[] = L"testBalor_io_Registry_a6rui97onfk1678kklhu8i";


Registry getTestKeyParent() {
	return Registry::currentUser().openKey(L"Software");
}


void testKeyDeleteFunction() {
	getTestKeyParent().removeKey(testKeyName, true);
};


Registry getTestKey() {
	testKeyDeleteFunction();
	return getTestKeyParent().createKey(testKeyName, true);
}


bool findExistKeyAndValue(const Registry& key) {
	if (0 < key.valueCount()) {
		auto names = key.valueNamesIterator();
		if (names) {
			key.getBinary(*names);
			return true;
		}
	}
	if (0 < key.keyCount()) {
		auto names = key.keyNamesIterator();
		for (; names; ++names) {
			auto subKey = key.openKey(*names);
			if (findExistKeyAndValue(subKey)) {
				return true;
			}
		}
	}
	return false;
}
} // namespace


testCase(rootKeys) {
	testAssert(0 < Registry::classesRoot().keyCount());
	testAssert(0 < Registry::currentConfig().keyCount());
	testAssert(0 < Registry::currentUser().keyCount());
	testAssert(0 < Registry::localMachine().keyCount());
	testAssert(0 < Registry::users().keyCount());
}


testCase(constructAndAssignment) {
	{// �f�t�H���g�R���X�g���N�^
		Registry emptyKey;
		testAssert(!emptyKey);
	}
	{// rvalue �R���X�g���N�^
		Registry sourceKey = Registry::currentUser();
		Registry rvalueConstructKey = move(sourceKey);
		testAssert(!sourceKey);
		testAssert(rvalueConstructKey.keyCount() == Registry::currentUser().keyCount());
	}
	{// rvalue ������Z�q
		Registry sourceKey = Registry::currentUser();
		Registry rvalueAssignmentKey;
		rvalueAssignmentKey = move(sourceKey);
		testAssert(!sourceKey);
		testAssert(rvalueAssignmentKey.keyCount() == Registry::currentUser().keyCount());
	}
	{// �R���e�i�i�[
		vector<Registry> keys;
		keys.push_back(Registry::classesRoot());
		keys.push_back(Registry::currentConfig());
		keys.push_back(Registry::currentUser());
		keys.pop_back();
		keys.insert(++keys.begin(), Registry::localMachine());
		keys.erase(++++keys.begin());
		testAssert((HKEY)keys[0] == (HKEY)Registry::classesRoot());
		testAssert((HKEY)keys[1] == (HKEY)Registry::localMachine());
	}
}


testCase(constructWithName) {
	{ // �����ȃ��[�g�L�[��
		testAssertionFailed(Registry(L"\\"));
		testAssertionFailed(Registry(L""));
	}
	{ // ���݂��Ȃ��T�u�L�[��
		testAssert(!Registry(L"HKEY_CLASSES_ROOT\\a\\b\\c\\d\\e0123456"));
	}
	// ���ꂼ��̃��[�g�L�[����l�̎擾
	testAssert(findExistKeyAndValue(Registry::classesRoot()));
	testAssert(findExistKeyAndValue(Registry::currentConfig()));
	testAssert(findExistKeyAndValue(Registry::currentUser()));
	testAssert(findExistKeyAndValue(Registry::localMachine()));
	testAssert(findExistKeyAndValue(Registry::users()));

	{// ���ϐ��Ŏ擾�����l�̓��e���e�X�g
		String path;
		testNoThrow(path = EnvironmentVariable::get(L"PATH"));
		auto value = Registry(L"HKEY_LOCAL_MACHINE\\System\\CurrentControlSet\\Control\\Session Manager\\Environment").getString(L"PATH");
		value = EnvironmentVariable::expandStrings(value);
		testAssert(path.startsWith(value));
	}
}


testCase(destruct) {
	balor::test::HandleLeakChecker checker;
	{
		auto key = Registry::currentUser().openKey(L"Software");
		testAssert(checker.getSystemHandleChange() == 1);
	}
	testAssert(checker.getSystemHandleChange() == 0);
}


testCase(createKey) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.createKey(L" "));
	}
	// �T�u�L�[�̍쐬��������Ȃ����W�X�g���L�[
	testThrow(Registry::localMachine().createKey(testKeyName), Registry::InvalidParameterException);

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// �����ȃp�����[�^
	testAssertionFailed(testKey.createKey(L""));
	// �T�u�L�[�̍쐬
	Registry subKey;
	testNoThrow(subKey = testKey.createKey(L"subKey"));
	testAssert(subKey);
	// �f�t�H���g�����ł͏������݌�������
	testThrow(subKey.setDword(L"dwordValue", std::uint32_t(0)), Registry::AccessDeniedException);
	// ���ɑ��݂���L�[�͂��̂܂܊J���B���łɏ������݌����t�^�B
	testNoThrow(subKey = testKey.createKey(L"subKey", true));
	testAssert(subKey);
	// �������݌����L��
	testNoThrow(subKey.setDword(L"dwordValue", std::uint32_t(2)));
	testAssert(subKey.getDword(L"dwordValue") == 2);
	// ���ɍ폜���ꂽ���W�X�g���L�[�ō쐬���悤�Ƃ���
	testKey.removeKey(L"subKey");
	testAssert(!testKey.openKey(L"subKey"));
	testThrow(subKey.createKey(L"subsubKey"), Registry::KeyDeletedException);
	// �����̊K�w����C�ɍ쐬
	testNoThrow(subKey = testKey.createKey(L"subKey\\subsubKey\\subsubsubKey"));
	testAssert(testKey.openKey(L"subKey").openKey(L"subsubKey").openKey(L"subsubsubKey"));
	// �r���܂ő��݂��镡���̊K�w����C�ɍ쐬
	testNoThrow(subKey = testKey.createKey(L"subKey\\hogeKey\\hogehogeKey"));
	testAssert(testKey.openKey(L"subKey").openKey(L"hogeKey").openKey(L"hogehogeKey"));

	// Caution: RegistryOptions::volatileSubTree �̃e�X�g��PC�̃��O�I�t��ċN�����K�v�ȈׁA
	//          ���L�̃T�u�L�[���쐬����A���O�I�t��ɏ����邱�Ƃ�ڎ��Ŋm�F����B
	//Registry::currentUser().openKey(L"Software").createKey(L"testBalor", true, RegistryOptions::volatileSubTree);
}


testCase(flush) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.flush());
	}

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	testKey.setString(L"value", L"test");
	testNoThrow(testKey.flush()); // ���ʂ��ǂ����肷��Ηǂ��̂�����Ȃ�
}


testCase(getValue) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.getString(L" "));
	}

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	testKey.setString(L"string0", L"test");
	testKey.setDword(L"dword0", 0);

	{// binary�̎擾
		testThrow(testKey.getBinary(L"test"), Registry::ValueNotFoundException);
		vector<std::uint8_t> binary;
		testNoThrow(testKey.setBinary(L"binary", binary));
		testAssert(testKey.getBinary(L"binary") == binary);
		testAssert(testKey.getValueKind(L"binary") == Registry::ValueKind::binary);
		binary += 0, 1, 2, 3;
		testNoThrow(testKey.setBinary(L"binary", binary));
		testAssert(testKey.getBinary(L"binary") == binary);
		binary.clear();
		const wchar_t text[] = L"test";
		binary.assign(reinterpret_cast<const unsigned char*>(text), reinterpret_cast<const unsigned char*>(text + 5));
		testAssert(testKey.getBinary(L"string0") == binary);
	}
	{// dword�̎擾
		testThrow(testKey.getDword(L"test"), Registry::ValueNotFoundException);
		testThrow(testKey.getDword(L"string0"), Registry::ValueKindMismatchException);
		std::uint32_t dword = 0;
		testNoThrow(testKey.setDword(L"dword", dword));
		testAssert(testKey.getDword(L"dword") == dword);
		testAssert(testKey.getValueKind(L"dword") == Registry::ValueKind::dword);
		testNoThrow(testKey.setDword(L"dword2", dword));
		testAssert(testKey.getDword(L"dword2") == dword);
		testAssert(testKey.getValueKind(L"dword2") == Registry::ValueKind::dword);
		dword = 1024;
		testNoThrow(testKey.setDword(L"dword", dword));
		testAssert(testKey.getDword(L"dword") == dword);
		testNoThrow(testKey.setDword(L"dword2", dword));
		testAssert(testKey.getDword(L"dword2") == dword);
	}
	{// string�̎擾
		testThrow(testKey.getString(L"test"), Registry::ValueNotFoundException);
		testThrow(testKey.getString(L"dword0"), Registry::ValueKindMismatchException);
		String string;
		testNoThrow(testKey.setString(L"string", string));
		testAssert(testKey.getString(L"string") == string);
		testAssert(testKey.getValueKind(L"string") == Registry::ValueKind::string);
		string = L"abc";
		testNoThrow(testKey.setString(L"string", string));
		testAssert(testKey.getString(L"string") == string);
	}
	{// expandString�̎擾
		String expandString;
		testNoThrow(testKey.setString(L"expandString", expandString, Registry::ValueKind::expandString));
		testAssert(testKey.getString(L"expandString") == expandString);
		testAssert(testKey.getValueKind(L"expandString") == Registry::ValueKind::expandString);
		expandString = L"%PATH%";
		testNoThrow(testKey.setString(L"expandString", expandString, Registry::ValueKind::expandString));
		testAssert(testKey.getString(L"expandString") == expandString);
	}
	{// multiString�̎擾
		String multiString;
		testNoThrow(testKey.setString(L"multiString", multiString, Registry::ValueKind::multiString));
		testAssert(testKey.getString(L"multiString") == multiString);
		testAssert(testKey.getValueKind(L"multiString") == Registry::ValueKind::multiString);
		multiString = String(L"a\0b\0c", 5);
		testNoThrow(testKey.setString(L"multiString", multiString, Registry::ValueKind::multiString));
		testAssert(testKey.getString(L"multiString") == multiString);
	}
	{// qword�̎擾
		testThrow(testKey.getQword(L"test"), Registry::ValueNotFoundException);
		testThrow(testKey.getQword(L"string0"), Registry::ValueKindMismatchException);
		std::uint64_t qword = 0;
		testNoThrow(testKey.setQword(L"qword", qword));
		testAssert(testKey.getQword(L"qword") == qword);
		testAssert(testKey.getValueKind(L"qword") == Registry::ValueKind::qword);
		testNoThrow(testKey.setQword(L"qword2", qword));
		testAssert(testKey.getQword(L"qword2") == qword);
		testAssert(testKey.getValueKind(L"qword2") == Registry::ValueKind::qword);
		qword = 2048;
		testNoThrow(testKey.setQword(L"qword", qword));
		testAssert(testKey.getQword(L"qword") == qword);
		testNoThrow(testKey.setQword(L"qword2", qword));
		testAssert(testKey.getQword(L"qword2") == qword);
	}
	{// ����l�̎擾
		String string = L"test";
		testNoThrow(testKey.setString(L"", string));
		testAssert(testKey.getString(L"") == string);
		testAssert(testKey.getValueKind(L"") == Registry::ValueKind::string);
	}
	{// �T�|�[�g���Ȃ��^�̒l�̎擾
		DWORD value = 1;
		testAssert(RegSetValueExW(testKey, L"unknown", 0, REG_DWORD_BIG_ENDIAN, reinterpret_cast<const BYTE*>(&value), sizeof(value)) == ERROR_SUCCESS);
		vector<std::uint8_t> binary;
		binary += 1, 0, 0, 0;
		testAssert(testKey.getBinary(L"unknown") == binary);
		testAssert(testKey.getValueKind(L"unknown") == Registry::ValueKind::unknown);
	}
	{// �폜���ꂽ�L�[����l�̎擾
		Registry subKey = testKey.createKey(L"subKey", true);
		subKey.setString(L"value", L"testValue");
		testKey.removeKey(L"subKey");
		testThrow(subKey.getString(L"value"), Registry::KeyDeletedException);
		testThrow(subKey.getValueKind(L"value"), Registry::KeyDeletedException);
	}
	{// �l�̓ǂݎ�茠���̂Ȃ��L�[����l���擾
		testKey.createKey(L"subKey", true).setString(L"value", L"test");
		HKEY handle;
		testAssert(RegOpenKeyExW(testKey, L"subKey", 0, STANDARD_RIGHTS_READ, &handle) == ERROR_SUCCESS);
		Registry subKey;
		*(HKEY*)&subKey = handle;
		testThrow(subKey.getString(L"value"), Registry::AccessDeniedException);
		testThrow(subKey.getValueKind(L"value"), Registry::AccessDeniedException);
	}
}


testCase(getValueKind) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.getValueKind(L" "));
	}

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// ���݂��Ȃ��l
	testAssert(testKey.getValueKind(L"value") == Registry::ValueKind::notFound);
	// �e�^�̃e�X�g�� testCase(getValue) �ɂăe�X�g�ς�

	// �폜���ꂽ�L�[����l�̌^�̎擾�� testCase(getValue) �ɂăe�X�g�ς�

	// �l�̓ǂݎ�茠���̂Ȃ��L�[����^�̎擾�� testCase(getValue) �ɂăe�X�g�ς�
}


testCase(name) {
	// testCase(createKey)�ɂăe�X�g�ς�
}


testCase(keyCount) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.keyCount());
	}

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// �T�u�L�[�̐�
	testAssert(testKey.keyCount() == 0);
	testKey.createKey(L"subKey0");
	testKey.createKey(L"subKey1");
	testKey.createKey(L"subKey2");
	testAssert(testKey.keyCount() == 3);

	{// �폜���ꂽ���W�X�g���L�[����T�u�L�[�̐����擾
		Registry subKey = testKey.createKey(L"subKey");
		testKey.removeKey(L"subKey");
		testThrow(subKey.keyCount(), Registry::KeyDeletedException);
	}
	{// �����̖����L�[�ł̃T�u�L�[�̐��̎擾
		testKey.createKey(L"subKey");
		HKEY handle;
		testAssert(RegOpenKeyExW(testKey, L"subKey", 0, STANDARD_RIGHTS_READ, &handle) == ERROR_SUCCESS);
		Registry subKey;
		*(HKEY*)&subKey = handle;
		testThrow(subKey.keyCount(), Registry::AccessDeniedException);
	}
}


testCase(keyNamesIterator) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.keyNamesIterator());
	}

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// ��̃T�u�L�[�����X�g�̎擾
	testAssert(!testKey.keyNamesIterator());
	{// �T�u�L�[�����X�g�̎擾
		wchar_t names[][8] = {L"subKey0", L"subKey1", L"subKey2"};
		for (int i = 0; i < 3; ++i) {
			testKey.createKey(names[i]);
		}
		auto subKeyNames = testKey.keyNamesIterator();
		for (int i = 0; i < 3; ++i, ++subKeyNames) {
			bool find = false;
			for (int j = 0; j < 3; ++j) {
				if (String::equals(names[j], *subKeyNames)) {
					find = true;
					break;
				}
			}
			testAssert(find);
		}
		testAssert(!subKeyNames);
	}
	{// �폜���ꂽ���W�X�g���L�[����T�u�L�[�����X�g�̎擾
		Registry subKey = testKey.createKey(L"subKey");
		testKey.removeKey(L"subKey");
		testThrow(subKey.keyNamesIterator(), Registry::KeyDeletedException);
	}
	{// �T�u�L�[���̗񋓌����̖����L�[�ł̗�
		testKey.createKey(L"subKey");
		HKEY handle;
		testAssert(RegOpenKeyExW(testKey, L"subKey", 0, STANDARD_RIGHTS_READ, &handle) == ERROR_SUCCESS);
		Registry subKey;
		*(HKEY*)&subKey = handle;
		testThrow(subKey.keyNamesIterator(), Registry::AccessDeniedException);
	}
}


testCase(openKey) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.openKey(L" "));
	}

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// �����ȃp�����[�^
	testAssertionFailed(testKey.openKey(L""));
	// ���݂��Ȃ��T�u�L�[
	testAssert(!testKey.openKey(L"subKey"));
	{// ���݂���T�u�L�[
		Registry createdSubKey = testKey.createKey(L"subKey");
		Registry subKey = testKey.openKey(L"subKey");
		testAssert(subKey);
	}
	// �������݌����Ȃ�
	testThrow(testKey.openKey(L"subKey").setString(L"value", L"test"), Registry::AccessDeniedException);
	// �������݌�������
	testNoThrow(testKey.openKey(L"subKey", true).setString(L"value", L"test"));
	{// �폜���ꂽ�L�[�ŃT�u�L�[���I�[�v��
		Registry subKey = testKey.openKey(L"subKey");
		testKey.removeKey(L"subKey");
		testThrow(subKey.openKey(L"subsubKey"), Registry::KeyDeletedException);
	}
	// Caution: ���݂̃��[�U�̓ǂݎ������ۂ����L�[���쐬���A�I�[�v�������Registry::AccessDeniedException�𓊂��邱�Ƃ�ڎ��Ŋm�F
	//Registry::currentUser().openKey(L"Software\\balor_test");
}


testCase(removeKey) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.removeKey(L" "));
	}

	// �폜��������Ȃ��L�[
	testThrow(Registry::localMachine().removeKey(L"SECURITY"), Registry::AccessDeniedException);

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// �����ȃp�����[�^
	testAssertionFailed(testKey.removeKey(L""));
	// ���݂��Ȃ��T�u�L�[�̍폜
	testNoThrow(testKey.removeKey(L"subKey"));
	// ���݂���T�u�L�[�̍폜
	testKey.createKey(L"subKey");
	testNoThrow(testKey.removeKey(L"subKey"));
	testAssert(!testKey.openKey(L"subKey"));
	// �T�u�L�[�����݂���L�[�̍폜
	Registry subKey = testKey.createKey(L"subKey");
	Registry subsubKey = subKey.createKey(L"subsubKey", true);
	testThrow(testKey.removeKey(L"subKey"), Registry::AccessDeniedException);
	testAssert(testKey.openKey(L"subKey"));
	// �l�͂����Ă��폜�ł���
	subsubKey.setString(L"value", L"test");
	testNoThrow(subKey.removeKey(L"subsubKey"));
	testAssert(!subKey.openKey(L"subsubKey"));
	// �폜���ꂽ�L�[�ō폜�����s
	subsubKey = subKey.createKey(L"subsubKey");
	testKey.removeKey(L"subKey", true);
	testAssert(!testKey.openKey(L"subKey"));
	testThrow(subKey.removeKey(L"subsubKey"), Registry::KeyDeletedException);
}


testCase(removeKeyRecursive) {
	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// ���݂��Ȃ��T�u�L�[�̍폜
	testNoThrow(testKey.removeKey(L"subKey", true));
	// ���݂���T�u�L�[�̍폜
	Registry subKey = testKey.createKey(L"subKey");
	subKey.createKey(L"subsubKey");
	subKey.createKey(L"subsubKey2");
	Registry subKey2 = testKey.createKey(L"subKey2");
	subKey2.createKey(L"subsubKey2");
	subKey2.createKey(L"subsubKey22");
	testNoThrow(testKey.removeKey(L"subKey", true));
	testAssert(!testKey.openKey(L"subKey"));
}


testCase(removeValue) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.removeValue(L" "));
	}

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// ���݂��Ȃ��l�̍폜
	testNoThrow(testKey.removeValue(L"value"));
	// ���݂���l�̍폜
	Registry subKey = testKey.createKey(L"subKey", true);
	subKey.setString(L"value", L"test");
	testAssert(subKey.getString(L"value") == L"test");
	testNoThrow(subKey.removeValue(L"value"));
	testThrow(subKey.getString(L"value"), Registry::ValueNotFoundException);
	// ����l�̍폜
	subKey.setString(L"", L"default");
	testAssert(subKey.getString(L"") == L"default");
	testNoThrow(subKey.removeValue(L""));
	testThrow(subKey.getString(L""), Registry::ValueNotFoundException);
	// �������݌����̖����L�[�Œl�̍폜
	subKey.setString(L"value", L"test");
	subKey = testKey.openKey(L"subKey");
	testThrow(subKey.removeValue(L"value"), Registry::AccessDeniedException);
	testAssert(subKey.getString(L"value") == L"test");
	// �폜���ꂽ�L�[�Œl�̍폜
	subKey = testKey.openKey(L"subKey", true);
	testKey.removeKey(L"subKey");
	testThrow(subKey.removeValue(L"value"), Registry::KeyDeletedException);
}


testCase(setValue) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.setString(L"", L""));
		testAssertionFailed(emptyKey.setBinary(L"", vector<std::uint8_t>()));
		testAssertionFailed(emptyKey.setDword(L"", uint32_t()));
		testAssertionFailed(emptyKey.setQword(L"", uint64_t()));
	}

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// ���݂��Ȃ��l�͍쐬�����
	testKey.setString(L"value", L"test");
	testAssert(testKey.getString(L"value") == L"test");
	// ���݂���l�͏㏑�������
	testKey.setString(L"value", L"test2");
	testAssert(testKey.getString(L"value") == L"test2");

	// �l�ƌ^�̃~�X�}�b�`
	testAssertionFailed(testKey.setString(L"value", String(), Registry::ValueKind::binary));

	// ����ȊO�̊e�^�̒l�̐ݒ�̃e�X�g�� testCase(getValue) �ɂăe�X�g�ς�

	{// �폜���ꂽ�L�[�ɒl�̐ݒ�
		Registry subKey = testKey.createKey(L"subKey", true);
		testKey.removeKey(L"subKey");
		testThrow(subKey.setString(L"value", L""), Registry::KeyDeletedException);
		testThrow(subKey.setBinary(L"value", vector<std::uint8_t>()), Registry::KeyDeletedException);
		testThrow(subKey.setDword(L"value", uint32_t()), Registry::KeyDeletedException);
		testThrow(subKey.setQword(L"value", uint64_t()), Registry::KeyDeletedException);
	}

	{// �������݌����̂Ȃ��L�[�ɒl�̐ݒ�
		Registry subKey = testKey.createKey(L"subKey");
		testThrow(subKey.setString(L"value", L""), Registry::AccessDeniedException);
		testThrow(subKey.setBinary(L"value", vector<std::uint8_t>()), Registry::AccessDeniedException);
		testThrow(subKey.setDword(L"value", uint32_t()), Registry::AccessDeniedException);
		testThrow(subKey.setQword(L"value", uint64_t()), Registry::AccessDeniedException);
	}
}


testCase(valueCount) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.valueCount());
	}

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// �l�̐�
	testAssert(testKey.valueCount() == 0);
	testKey.setString(L"value0", L"test");
	testKey.setString(L"value1", L"test");
	testKey.setString(L"value2", L"test");
	testAssert(testKey.valueCount() == 3);
	// �K��l
	testKey.setString(L"", L"test");
	testAssert(testKey.valueCount() == 4);

	{// �폜���ꂽ���W�X�g���L�[����l�̐����擾
		Registry subKey = testKey.createKey(L"subKey");
		testKey.removeKey(L"subKey");
		testThrow(subKey.valueCount(), Registry::KeyDeletedException);
	}
	{// �����̖����L�[�ł̒l�̎擾
		testKey.createKey(L"subKey");
		HKEY handle;
		testAssert(RegOpenKeyExW(testKey, L"subKey", 0, STANDARD_RIGHTS_READ, &handle) == ERROR_SUCCESS);
		Registry subKey;
		*(HKEY*)&subKey = handle;
		testThrow(subKey.valueCount(), Registry::AccessDeniedException);
	}
}


testCase(valueNamesIterator) {
	{// ��̃��W�X�g���L�[
		Registry emptyKey;
		testAssertionFailed(emptyKey.valueNamesIterator());
	}

	// �e�X�g�p���W�X�g���L�[�̏���
	Registry testKey = getTestKey();
	scopeExit(&testKeyDeleteFunction);

	// ��̒l�����X�g�̎擾
	testAssert(!testKey.valueNamesIterator());
	{// �l�����X�g�̎擾
		wchar_t names[][8] = {L"value0", L"value1", L""};
		for (int i = 0; i < 3; ++i) {
			testKey.setString(names[i], L"test");
		}
		auto valueNames = testKey.valueNamesIterator();
		for (int i = 0; i < 3; ++i, ++valueNames) {
			bool find = false;
			for (int j = 0; j < 3; ++j) {
				if (String::equals(names[j], *valueNames)) {
					find = true;
					break;
				}
			}
			testAssert(find);
		}
		testAssert(!valueNames);
	}
	{// �폜���ꂽ���W�X�g���L�[����l�����X�g�̎擾
		Registry subKey = testKey.createKey(L"subKey");
		testKey.removeKey(L"subKey");
		testThrow(subKey.valueNamesIterator(), Registry::KeyDeletedException);
	}
	{// �T�u�L�[���̗񋓌����̖����L�[�ł̗�
		testKey.createKey(L"subKey");
		HKEY handle;
		testAssert(RegOpenKeyExW(testKey, L"subKey", 0, STANDARD_RIGHTS_READ, &handle) == ERROR_SUCCESS);
		Registry subKey;
		*(HKEY*)&subKey = handle;
		testThrow(subKey.valueNamesIterator(), Registry::AccessDeniedException);
	}
}




		}
	}
}