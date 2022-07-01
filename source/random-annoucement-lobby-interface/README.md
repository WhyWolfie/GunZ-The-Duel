<b>Random Annoucement Lobby Interface</b><br>
![img](https://i.imgur.com/LL9zM7H.png)

I bring you random announcement the lobby interface, and something very simple to add.

ZGameInterface.cpp
Search for: void ZGameInterface::OnDrawStateLobbyNStage(MDrawContext* pDC)
Added:

    pLabel = (MLabel*)pRes->FindWidget("Lobby_RandomAnnounce");
    int RandomMsg = (timeGetTime() / (3 * 60 * 1000) % 2); // 3 min 
    int i = 0;
    for (i = 0; i < RandomMsg; i++);
    switch (i)
    {
    case 0:
    sprintf(buf, "Update: 0.0.0.1");
    break;
    case 1:
    sprintf(buf, "Welcome The Gunz!");
    break;
    }
    if (pLabel) pLabel->SetText(buf);

Lobby.xml
Added:


    <LABEL item="Lobby_RandomAnnounce" parent="Lobby">
    <FONT>FONTa8_O2Wht</FONT>
    <TEXTCOLOR>
     <R>210</R>
     <G>210</G>
     <B>210</B>
    </TEXTCOLOR>
    <BOUNDS>
     <X>15</X>
     <Y>566</Y>
     <W>380</W>
     <H>20</H>
    </BOUNDS>
    <TEXT></TEXT>
    </LABEL> 
    
 
