#ifndef _ZNHNREGISTINFO
#define _ZNHNREGISTINFO



class ZNHNRegistInfo
{
public :
	friend class ZNHNModule;

	ZNHNRegistInfo();
	~ZNHNRegistInfo();


	const char* GetGunzPath();

private :
	char m_szRegistPath[ 1024 ];
};


#endif