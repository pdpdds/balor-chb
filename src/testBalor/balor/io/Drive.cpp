#include <balor/io/Drive.hpp>

#include <vector>

#include <balor/io/File.hpp>
#include <balor/system/windows.hpp>
#include <balor/test/Debug.hpp>
#include <balor/test/UnitTest.hpp>
#include <balor/String.hpp>
#include <balor/StringBuffer.hpp>


namespace balor {
	namespace io {
		namespace testDrive {


using std::move;
using std::vector;
using namespace balor::io;


namespace {
Drive getReadyDrive() {
	for (auto i = Drive::drivesBegin(), end = Drive::drivesEnd(); i < end; ++i) {
		if ((*i).ready()) {
			return move(*i);
		}
	}
	throw Drive::NotFoundException();
}


Drive getNotFoundDrive() {
	auto last = *(--Drive::drivesEnd());
	return Drive(String(last.letter() + 1, 1) + L":\\");
}

Drive getNotReadyDrive() {
	for (auto i = Drive::drivesBegin(), end = Drive::drivesEnd(); i < end; ++i) {
		auto drive = *i;
		if (!drive.ready() && drive.type() == Drive::Type::cdRom) {
			return move(*i);
		}
	}
	balor::test::Debug::write("not ready��CD�h���C�u��������Ȃ������BCD�h���C�u��CD�������Ă���ꍇ��CD���o���Ă�������\n");
	throw Drive::NotFoundException();
}


bool isValidDriveType(Drive::Type type) {
	switch (type) {
		case Drive::Type::noRootDirectory :
		case Drive::Type::removable       :
		case Drive::Type::fixed           :
		case Drive::Type::remote          :
		case Drive::Type::cdRom           :
		case Drive::Type::ramDisk         : return true;
		case Drive::Type::unknown         :
		default : return false;
	}
}
} // namespace



testCase(constructAndAssignment) {
	{// ��̃h���C�u
		testAssertionFailed(Drive(L""));
	}
	{// �������Ȃ��`��
		testAssertionFailed(Drive(L' '));
		testAssertionFailed(Drive(L"abc"));
		testAssertionFailed(Drive(L"c::\\"));
		testAssertionFailed(Drive(L"\\network"));
		testNoThrow(Drive(L'A'));
		testNoThrow(Drive(L'z'));
		testNoThrow(Drive(L"a"));
		testNoThrow(Drive(L"Z"));
		testNoThrow(Drive(L"B:"));
		testNoThrow(Drive(L"c:\\"));
		testNoThrow(Drive(L"c:\\test"));
	}
}


testCase(availableFreeBytes) {
	__int64 availableFreeBytes;
	testNoThrow(availableFreeBytes = getReadyDrive().availableFreeBytes());
	testThrow(getNotFoundDrive().availableFreeBytes(), Drive::NotFoundException);
	testThrow(getNotReadyDrive().availableFreeBytes(), Drive::NotReadyException);

	// Caution: �g�p�\�̈悪���������Ƃ��e�}�V���Ŗڎ��Ŋm�F����
}


testCase(drivesBeginAndEnd) {
	//testCase(type) �ɂăe�X�g�B

	// Caution: �ꗗ�����������Ƃ��e�}�V���Ŗڎ��Ŋm�F����
}


testCase(fileSystem) {
	String fileSystem;
	testNoThrow(fileSystem = getReadyDrive().fileSystem());
	testThrow(getNotFoundDrive().fileSystem(), Drive::NotFoundException);
	testThrow(getNotReadyDrive().fileSystem(), Drive::NotReadyException);

	StringBuffer buffer;
	testNoThrow(getReadyDrive().fileSystemToBuffer(buffer));

	// Caution: �t�H�[�}�b�g�����񂪐��������Ƃ��e�}�V���Ŗڎ��Ŋm�F����
}


testCase(letter) {
	testAssert(Drive(L'a').letter() == L'a');
	testAssert(Drive(L'A').letter() == L'A');
	testAssert(Drive(L"C:\\").letter() == L'C');
	testAssert(Drive(L"C:\\test").letter() == L'C');
}


testCase(name) {
	Drive drive0(L"c");
	Drive drive1(L"c:");
	Drive drive2(L"c:\\test");
	testAssert(String::equals(drive0.name(), L"c:\\"));
	testAssert(String::equals(drive1.name(), L"c:\\"));
	testAssert(String::equals(drive2.name(), L"c:\\"));
}


testCase(ready) {
	testAssert(getReadyDrive().ready());
	testAssert(!getNotFoundDrive().ready());

	// Caution: CD����ꂽ��o�����肵�� ready �̌��ʂ̕ω���ڎ��Ŋm�F
}


testCase(totalFreeBytes) {
	__int64 totalFreeBytes;
	testNoThrow(totalFreeBytes = getReadyDrive().totalFreeBytes());
	testThrow(getNotFoundDrive().totalFreeBytes(), Drive::NotFoundException);
	testThrow(getNotReadyDrive().totalFreeBytes(), Drive::NotReadyException);

	// Caution: �󂫗̈悪���������Ƃ��e�}�V���Ŗڎ��Ŋm�F����
}


testCase(totalBytes) {
	__int64 totalBytes;
	testNoThrow(totalBytes = getReadyDrive().totalBytes());
	testThrow(getNotFoundDrive().totalBytes(), Drive::NotFoundException);
	testThrow(getNotReadyDrive().totalBytes(), Drive::NotReadyException);

	// Caution: �f�B�X�N���v�̈悪���������Ƃ��e�}�V���Ŗڎ��Ŋm�F����
}


testCase(type) {
	bool result = true;
	for (auto i = Drive::drivesBegin(), end = Drive::drivesEnd(); i < end; ++i) {
		if (!isValidDriveType((*i).type())) {
			result = false;
		}
	}
	testAssert(result);

	// Caution: �e�h���C�u�̎�ނ����������Ƃ��e�}�V���Ŗڎ��Ŋm�F����
}


testCase(volumeLabel) {
	testNoThrow(getReadyDrive().volumeLabel());
	testThrow(getNotFoundDrive().volumeLabel(), Drive::NotFoundException);
	testThrow(getNotReadyDrive().volumeLabel(), Drive::NotReadyException);

	testThrow(getNotFoundDrive().volumeLabel(L""), Drive::NotFoundException);

	StringBuffer buffer;
	testNoThrow(getReadyDrive().volumeLabelToBuffer(buffer));

	// Caution: �{�����[�����x�������������Ƃ��e�}�V���Ŗڎ��Ŋm�F����
	//          �{�����[�����x���̏����������e�}�V���Ŗڎ��Ŋm�F����
}



		}
	}
}