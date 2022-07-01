<b>pingbar</b></br>

![ping](https://i.imgur.com/pctLi3T.png)

zcombatinterface.cpp

         // Ping bar.         
         x = ITEM_XPOS[5];
        int nIconSize = .8f * linespace * (float)MGetWorkspaceHeight();
        float icony = itemy + (linespace - (float)nIconSize / (float)MGetWorkspaceHeight())*.5f;
        if (pItem->nPing == 0 || pItem->nPing == 999)
        {
            BitmapRelative(pDC, x, texty, nIconSize + 4, nIconSize, MBitmapManager::Get("AgentPing01.tga"));
        }
        else if (pItem->nPing >= 250)
        {
            BitmapRelative(pDC, x, texty, nIconSize + 4, nIconSize, MBitmapManager::Get("AgentPing03.tga"));
        }
        else if (pItem->nPing >= 1)
        {
            BitmapRelative(pDC, x, texty, nIconSize + 4, nIconSize, MBitmapManager::Get("AgentPing05.tga"));
        }
