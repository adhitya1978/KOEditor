#pragma once
//#include "vcruntime_exception.h"
#include <exception>

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

using namespace std;

class MyKOException :
	public std::exception
{
public:
	MyKOException(const TCHAR* message = TEXT("Unknown Exception"));
	~MyKOException();

	/** Returns a pointer to the (constant) error description.
	*  @return A pointer to a const char*. The underlying memory
	*          is in posession of the Exception object. Callers must
	*          not attempt to free the memory.
	*/
	const char* what() const NOEXCEPT override;

	CString errorMessage() { return _msg; }

protected:
	CString _msg;
	int eCode;
};

