Code: <br>
ZGameInterface.cpp line 6834 <br>


    int MDrawContext::TextMultiLine(MRECT& r, const char* szText, int nLineGap, bool bAutoNextLine, int nIndentation, int nSkipLine, MPOINT* pPositions)
    {
        bool bColorSupport = true;

        MBeginProfile(99, "MDrawContext::TextMultiLine");

        int nLine = 0;
        MFont* pFont = GetFont();

        int nLength = (int)strlen(szText);
        int xRight = 0;
        int y = r.y;
        char* szCurrent = (char*)szText;
        MPOINT* pCurrentPos = pPositions;
        do {
            int nX = nLine == 0 ? 0 : nIndentation;

            int nOriginalCharCount = MMGetNextLinePos(pFont, szCurrent, r.w - nX, bAutoNextLine, true);

            if (nSkipLine <= nLine)
            {
                int nCharCount = min(nOriginalCharCount, 255);
                char buffer[256];
                if (bColorSupport) {

    #define FLUSHPOS(_Pos)        if(pCurrentPos!=NULL){    \
                    for (int i = 0; buffer[i] != NULL; i++){
                    \
                    pCurrentPos[i + szCurrent - szText].x = _Pos + pFont->GetWidth(buffer, i);    \
                    pCurrentPos[i + szCurrent - szText].y = y;    \
                    }    \
                }

    #define FLUSH                if(buffer[0]) { Text(r.x+nLastX+xRight, y, buffer); FLUSHPOS(r.x+nLastX); nLastX=nX; buffer[0]=0;pcurbuf=buffer; }

                int nLastX = nX;

                buffer[0] = 0;
                char *pcurbuf = buffer;
                for (int i = 0; i<nCharCount; i++){

                    unsigned char cminus = szCurrent[i - 1], c = szCurrent[i], cc = szCurrent[i + 1], ccc = szCurrent[i + 2], cccc = szCurrent[i + 3];

                    if (c == '^' && ('0' <= cc) && (cc <= 'Z'))
                    {
                        xRight = 0;
                        FLUSH;
                        i++;
                        continue;
                    }

                    else if (c == ':' && (cc == 'D' || cc == 'd'))
                    {
                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("1.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;
                        }
                        else if ((cminus == ' ') && (c == ':') && (cc == 'D' || cc == 'd') && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("1.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;
                        }
                    }


                    else if (c == ':' && (')' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("3.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == ':') && (cc == ')') && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("3.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;
                        }
                    }
                    else if (c == ':' && ('(' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("4.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == ':') && (cc == '(') && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("4.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;


                        }
                    }
                    else if (c == ':' && ('P' == cc || 'p' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("5.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == ':') && ('P' == cc || 'p' == cc) && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("5.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;


                        }
                    }
                    else if (c == ':' && ('/' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("6.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == ':') && (cc == '/') && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("6.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;


                        }
                    }
                    else if (c == '<' && ('3' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("7.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == '<') && (cc == '3') && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("7.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;


                        }
                    }
                    else if (c == '^' && ('_' == cc) && ('^' == ccc))
                    {
                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("8.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            ccc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            szCurrent[i + 2] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;
                        }
                        else if ((cminus == ' ') && (c == '^') && (cc == '_') && (ccc == '^') && (cccc == ' ' || !cccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("8.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            ccc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            szCurrent[i + 2] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;
                        }
                    }
                    else if ((c == 'O' || c == 'o') && (':' == cc) && (')' == ccc))
                    {
                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("9.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            ccc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            szCurrent[i + 2] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;
                        }
                        else if ((cminus == ' ') && (c == 'O' || c == 'o') && (cc == ':') && (ccc == ')') && (cccc == ' ' || !cccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("9.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            ccc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            szCurrent[i + 2] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;
                        }
                    }
                    else if (c == ':' && ('@' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("10.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == ':') && (cc == '@') && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("10.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;


                        }
                    }

                    else if (c == ';' && ('(' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("2.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == ';') && (cc == '(') && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("2.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;


                        }
                    }

                    else if (c == ';' && (')' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("12.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == ';') && (cc == ')') && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("12.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;


                        }
                    }
                    else if (c == ':' && ('O' == cc || 'o' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("13.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == ':') && ('O' == cc || 'o' == cc) && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("13.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;


                        }
                    }
                    else if (c == '-' && ('_' == cc) && ('-' == ccc))
                    {
                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("14.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            ccc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            szCurrent[i + 2] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;
                        }
                        else if ((cminus == ' ') && (c == '-') && (cc == '_') && (ccc == '-') && (cccc == ' ' || !cccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("14.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            ccc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            szCurrent[i + 2] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;
                        }
                    }
                    else if (c == ':' && ('*' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("15.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == ':') && (cc == '*') && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("15.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                    }
                    else if ((cminus == ' ') && (c == ':') && (cc == 'v') && (ccc == ' ' || !ccc)){
                        FLUSH;
                        SetBitmap(MBitmapManager::Get("16.png"));
                        Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                        c = ' ';
                        cc = ' ';
                        szCurrent[i] = ' ';
                        szCurrent[i + 1] = ' ';
                        xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                    }
                    }
                    else if (c == ':' && ('7' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("17.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                    else if (c == ':' && ('M' == cc || 'm' == cc))
                    {

                        if (strlen(szText) == strlen(ZGetMyInfo()->GetCharName()) + 5){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("maximo.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;

                        }
                        else if ((cminus == ' ') && (c == ':') && ('V' == cc || 'v' == cc) && (ccc == ' ' || !ccc)){
                            FLUSH;
                            SetBitmap(MBitmapManager::Get("maximo.png"));
                            Draw((r.x + nX), y, (float)RGetScreenWidth() / (float)800 * 11, (float)RGetScreenWidth() / (float)800 * 11);
                            c = ' ';
                            cc = ' ';
                            szCurrent[i] = ' ';
                            szCurrent[i + 1] = ' ';
                            xRight = (float)RGetScreenWidth() / (float)1920 * 6;
                        }
                    }

                    int w;

                    *(pcurbuf++) = c;
                    if (c>127 && i<nCharCount){
                        *(pcurbuf++) = cc;
                        w = pFont->GetWidth(szCurrent + i, 2);
                        i++;
                    }
                    else w = pFont->GetWidth(szCurrent + i, 1);

                    *pcurbuf = 0;

                    nX += w;
                }

                FLUSH;
                }
                else
                {
                    strncpy(buffer, szCurrent, nCharCount);
                    buffer[nCharCount] = 0;
                    Text(r.x + nX, y, buffer);
                    FLUSHPOS(r.x + nX);
                }
                y += pFont->GetHeight() + nLineGap;
            }

            szCurrent += nOriginalCharCount;
            nLine++;
            if (y >= r.y + r.h) break;
        } while (szCurrent<szText + nLength);

        MEndProfile(99);
        return nLine - nSkipLine;
    }
    #endif 
    
Credits: George
