#ifndef _NHNMODULE
#define _NHNMODULE


#include "ZNHNAuth.h"
#include "ZNHNRegistInfo.h"


class ZNHNModule
{
public :
	~ZNHNModule();

	ZNHNRegistInfo& GetRegistInfo() { return m_RegistInfo; }
	ZNHNAuth&		GetAuth() { return m_Auth; }

	static ZNHNModule& GetInstance()
	{
		static ZNHNModule module;
		return module;
	}

private :
	ZNHNModule();

private :
	ZNHNRegistInfo	m_RegistInfo;
	ZNHNAuth		m_Auth;
};


ZNHNModule& GetNHNModule();


#endif