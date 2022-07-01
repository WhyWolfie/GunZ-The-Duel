<b> Players Online Channel </b>

![icon](https://i.imgur.com/2FB20rg.png) <br>

[Search: struct MCHANNELLISTNODE]
    
    int nOnlinePlayers;
    
    
Open: MMatchServer_Channel.cpp
Search: MMatchServer::ChannelList

    pNode->nOnlinePlayers = (int)m_Objects.size();


Open: ZGameClient.cpp
Search: ZGameClient::OnChannelList

    MLabel* pLabel = (MLabel*)pResource->FindWidget("OnlinePlayersLabel");
    char szText[128];
    sprintf(szText, "Players Online : %d", pNode->nOnlinePlayers);
    pLabel->SetText(szText);

From within the game interface you add this:


    <LABEL item="OnlinePlayersLabel" parent="ChannelListFrame">
        <FONT>FONTa10_O2Wht</FONT>
        <TEXTCOLOR>
            <R>255</R>
            <G>255</G>
            <B>255</B>
        </TEXTCOLOR>
        <BOUNDS>
            <X>10</X>
            <Y>395</Y>
            <W>300</W>
            <H>24</H>
        </BOUNDS>
        <TEXT></TEXT>
    </LABEL> 
    
    
 Credits to: jetman82
