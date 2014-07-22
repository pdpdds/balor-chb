#pragma once

#include <balor/system/PerformanceCounter.hpp>
#include <balor/system/Process.hpp>
#include <balor/StringRange.hpp>


namespace balor {
	namespace test {



/// �t�@�C���Ȃǂ̃V�X�e���̃n���h���A�f�c�h�̃n���h���A�E�C���h�E�Ȃǂ̃��[�U�n���h���̂R��ނ̃n���h���̐����Ď�����B
class HandleLeakChecker {
public:
	HandleLeakChecker(StringRange exeFileName = L"");

public:
	int getGdiHandleChange();
	int getSystemHandleChange();
	int getUserHandleChange();

private:
	::balor::system::PerformanceCounter counter;
	::balor::system::Process process;
	int gdiHandleCount;
	int systemHandleCount;
	int userHandleCount;
};



	}
}