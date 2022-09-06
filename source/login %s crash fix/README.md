Someone crashed my server yesterday with that bug so im now releasing it to public so no one else can be crashed by this way..


MatchServer fix:

File : MMatchDBMgr.cpp (CSCommon\Source)




After

    bool MMatchDBMgr::GetLoginInfo(const TCHAR* szUserID, unsigned int* poutnAID, TCHAR* poutPassword)
    {

Put

    if(strstr(szUserID, "%")) return false;
    
Thanks too WooAF
