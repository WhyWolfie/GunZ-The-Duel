#ifndef _NHNAUTH
#define _NHNAUTH


#include <string>
#include <vector>

using std::string;
using std::vector;


// Auth

#define NHN_GAMEID			"u_gunz"
#define NHN_AUTH_LENGTH		4096
#define NHN_OUTBUFF_LENGTH	1024



class ZNHNAuth
{
public :
	friend class ZNHNModule;

	~ZNHNAuth();


	const char* GetAuthStr() { return m_szAuthString; }

	bool InitAuth();

	const bool IsAlpha();
	const bool IsReal();

private :
	ZNHNAuth();

	void InitTok();
	bool GetGameStr( const string& strCmdLine, char* szOutGameStr, const int nOutGameStrLen );

private :
	char				m_szAuthString[ NHN_AUTH_LENGTH ];
	vector< string >	m_Tok;
	bool				m_bIsCompleted;
};




#endif