#pragma once


namespace balor {
	namespace system {



/**
 * �v���Z�X�b������B
 */
class Process {
private:
	typedef void* HANDLE;

public:
	Process();
	~Process();

public:

public:
	int gdiHandleCount() const;
	int userHandleCount() const;

private:
	HANDLE _handle;
};



	}
}