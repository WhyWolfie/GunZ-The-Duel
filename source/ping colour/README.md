Open(ZCombatInterface.cpp) <br>
Find <br>

    x=ITEM_XPOS[5];
    sprintf(szText,"%d",pItem->nPing);
    TextRelative(pDC,x,texty,szText,true);

Replace <br>

		x=ITEM_XPOS[5];
		sprintf(szText,"%d",pItem->nPing);
		if(pItem->nPing == 0 || pItem->nPing > 250)
		pDC->SetColor( 255, 0, 0);
		else if(pItem->nPing > 1)
		pDC->SetColor( 50, 205, 50);
		else if(pItem->nPing > 150)
		pDC->SetColor( 250, 250, 210);
		TextRelative(pDC,x,texty,szText,true);
