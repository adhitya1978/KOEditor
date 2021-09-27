#include "stdafx.h"
#include "MyKOException.h"


MyKOException::MyKOException(const TCHAR* message) :
	_msg(message)
{
}


MyKOException::~MyKOException()
{
}

const char* MyKOException::what() const
{
	CT2A _umsg(_msg);

	return _umsg.m_psz;
}
