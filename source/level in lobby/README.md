I'm going to leave this simple code that did Androide28 and many have asked me. <br>
Open ZGameClient.cpp <br>
Find <br>

    void ZGameClient::OnChannelChat(const MUID& uidChannel, char* szName, char* szChat,int nGrade) 
    
Lines paste below <br>

    char szLevel[16]; 
    
Find <br>

    wsprintf(szText, "^4%s %s^9 : %s", szName, ZGetMyInfo()->, szChat); 

Replace <br>

    wsprintf(szText, "^4%s %s(Lv-%i)^9 : %s", szName, ZGetMyInfo()->, szChat); 


Find <br>

    ZGetMyInfo()-> szChat); 

Replace: <br>

    ZGetMyInfo()->GetLevel(), szChat); 

Find <br>

    wsprintf(szText, "%s : %s" , szName, szChat); 

Replace <br>

    wsprintf(szText, "%s %i : %s" , szName, szLevel, szChat); 


Credits: Androide28 and SkipChopJD <br>

![img](https://i.imgur.com/meofmB2.jpg)
