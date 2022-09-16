Open(ZCombatInterface.cpp) <br>
Find <br>

    bool bGameRoomUser;
    
Add <br>

    char szGrade[100];
    
Find <br>

    x=ITEM_XPOS[4];
    sprintf(szText,"%d",pItem->nDeaths);
    TextRelative(pDC,x,texty,szText,true);

Add <br>

    x = ITEM_XPOS[0]-0.05f;    
    TextRelative(pDC,x,texty,pItem->szGrade,true);

Find <br>

    sprintf(pItem->szName,"%s", pCharacter->GetUserName());

Add <br>

    if(pCharacter->IsAdminName())
    sprintf(pItem->szGrade,"%s","Owner");
    else if(pCharacter->IsDeveloperName())
    sprintf(pItem->szGrade,"%s","DEV");
    else if(pCharacter->IsEventMasterName())
    sprintf(pItem->szGrade,"%s","GM");
    else
    sprintf(pItem->szGrade,"%s","");
    
![img](https://i.imgur.com/DWOPe6Z.png) <br>
Credits too Mocro. <br>
