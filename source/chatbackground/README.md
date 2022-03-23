<b> Chat Background </b><br>
![chatbackground](https://i.imgur.com/5djF6cG.jpg)<br>

search "int MDrawContext::TextMultiLine" add above of

	int y = r.y;
	char* szCurrent = (char*)szText;
	MPOINT* pCurrentPos = pPositions;
	do {

replace too

	int y = r.y;
	char* szCurrent = (char*)szText;
	MPOINT* pCurrentPos = pPositions;
	do {
			MCOLOR prevColor = GetColor();
                        SetColor(0xFF000000); //Edit your color
			char* szCurrentCpy = GetPureText(szCurrent);
			FillRectangle(r.x, y, pFont->GetWidth(szCurrentCpy), pFont->GetHeight());
			pFont->GetWidth(szCurrentCpy), 200.f * 1.1 / 800.f * (float)MGetWorkspaceWidth();
			SetColor(prevColor);
