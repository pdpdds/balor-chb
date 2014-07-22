#pragma once

#include <balor/NonCopyable.hpp>
#include <balor/StringRange.hpp>


namespace balor {
	namespace system {



/**
 * �p�t�H�[�}���X�J�E���^�b������B
 */
class PerformanceCounter : private NonCopyable {
private:
	typedef void* HQUERY;
	typedef void* HCOUNTER;

public:
	PerformanceCounter(StringRange categoryName, StringRange counterName, StringRange instanceName = L"");
	~PerformanceCounter();

public:
	/// �w�肵���^�Œl���擾����B�w��ł���^�� int, long long, double�B
	template<typename T> T nextValue() const;

private:
	HQUERY _query;
	HCOUNTER _counter;
};



	}
}