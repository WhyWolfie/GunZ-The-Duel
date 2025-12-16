i found a workaround, it may still not support unicode language input but it is great for displaying Unicode.
I use Refined source
After opening the code and checking I found MXml.cpp I found they try to force the contents in xml to ASCII and that breaks the text display

MXml.h
#define _BSTRToAscii(s) (const char*)(_bstr_t)(s)
Replace

```
static inline std::string BSTRToUTF8(BSTR b)
{
    int len = WideCharToMultiByte(CP_UTF8, 0, b, -1, NULL, 0, NULL, NULL);
    std::string out;
    out.resize(len);
    WideCharToMultiByte(CP_UTF8, 0, b, -1, &out[0], len, NULL, NULL);
    return out;
}
```

MXml.cpp
Find

```
BSTR _AsciiToBSTR(const char* ascii)
{
    WCHAR wide[1024];
    int ret=::MultiByteToWideChar(CP_ACP, 0, ascii, -1, wide, 1024);
    MASSERT(ret!=0);
    return SysAllocString(wide);
}
```

Replace

```
BSTR _AsciiToBSTR(const char* utf8)
{
    if (!utf8) return SysAllocString(L"");

    int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
    WCHAR* wide = new WCHAR[wlen];
    MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wide, wlen);

    BSTR b = SysAllocString(wide);
    delete[] wide;
    return b;
}
```


Find

```
bool MXmlDocument::LoadFromFile(const char* m_sFileName)
{
    if (!m_bInitialized) return false;

    _variant_t varOut((bool)TRUE);
    varOut = (*m_ppDom)->load((_variant_t)m_sFileName);
    if ((bool)varOut == FALSE)
    {
//        _ASSERT(0);

        return false;
    }

    return true;
}
```

Replace

```
bool MXmlDocument::LoadFromFile(const char* filename)
{
    MLog("Loading XML: %s\n", filename);
    if (!m_bInitialized)
        return false;

    MZFile file;
    if (!file.Open(filename))
        return false;

    int len = file.GetLength();
    if (len <= 0)
        return false;

    std::string buf(len, '\0');
    file.Read(&buf[0], len);

    return LoadFromMemory(buf.c_str(), 0);
}
```

Find

```
bool MXmlDocument::LoadFromMemory(const char* szBuffer, LANGID lanid)
{
    if (!m_bInitialized) return false;

    // UTF8ÀÎÁö °Ë»çÇÑ´Ù
    string s;
    if ( (szBuffer[0] == (char)0xEF) && (szBuffer[1] == (char)0xBB) && (szBuffer[2] == (char)0xBF))
        s = MLocale::ConvUTF8ToAnsi( szBuffer, lanid);        // UTF8 -> ANSI ConvAnsiToUTF8
        //s = MLocale::ConvAnsiToUTF8(szBuffer, lanid);
    else
        s = szBuffer;                                        // ANSI

    // Custom: Safe XML hotfix
    s += " ";


    // XML ³»¿ëÀÇ ½ÃÀÛÀ» Ã£´Â´Ù
    int pos = s.find( "<XML>");                                // <XML>
    if ( pos == -1)
    {
        pos = s.find( "<xml>");                                // <xml>
      
        if ( pos == -1)
        {
            pos = s.find( "?>");                            // ?>
  
            if ( pos == -1)
            {
                s.clear();
                return false;
            }

            pos += 2;
        }
    }
    char* cp = &s[pos];


    // XML ³»¿ëÀÇ ³¡À» Ã£´Â´Ù
    pos = s.find( "</XML>");
    if ( pos == -1)
    {
        pos = s.find( "</xml>");
      
        if ( pos == -1)
        {
            s.clear();
            return false;
        }
    }
    s[pos+6] = 0;


    _bstr_t bsXML(cp);
    if ((*m_ppDom)->loadXML(BSTR(bsXML))!= -1)
    {
        MXmlDomParseErrorPtr errPtr = (*m_ppDom)->GetparseError();
        _bstr_t bstrErr(errPtr->reason);

#ifdef _DEBUG
        char szBuf[8192];

        sprintf(szBuf, "-------------------------------\n");
        OutputDebugString(szBuf);
        sprintf(szBuf, "Error In Load Xml Memory\n");     
        OutputDebugString(szBuf);
        sprintf(szBuf, "Code = 0x%x\n", errPtr->errorCode);
        OutputDebugString(szBuf);
        sprintf(szBuf, "Source = Line : %ld; Char : %ld\n", errPtr->line, errPtr->linepos);
        OutputDebugString(szBuf);
        sprintf(szBuf, "Error Description = %s\n", (char*)bstrErr);
        OutputDebugString(szBuf);
#endif

        _ASSERT(0);

        s.clear();
        return false;
    }

    s.clear();
    return true;
}
```

Replace

```
bool MXmlDocument::LoadFromMemory(const char* szBuffer, LANGID)
{
    if (!m_bInitialized)
        return false;

    const unsigned char* p = (const unsigned char*)szBuffer;
    if (p[0] == 0xEF && p[1] == 0xBB && p[2] == 0xBF)
        szBuffer += 3;   // skip BOM

    int wlen = MultiByteToWideChar(CP_UTF8, 0, szBuffer, -1, NULL, 0);
    if (wlen <= 0)
        return false;

    std::wstring wxml(wlen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, szBuffer, -1, &wxml[0], wlen);

    VARIANT_BOOL ok = (*m_ppDom)->loadXML(_bstr_t(wxml.c_str()));
    if (ok == VARIANT_FALSE)
    {
#ifdef _DEBUG
        MXmlDomParseErrorPtr err = (*m_ppDom)->GetparseError();
        char buf[2048];
        sprintf(buf,
            "[UTF8 XML Error]\nReason: %S\nLine: %ld Col: %ld\n",
            (wchar_t*)err->reason, err->line, err->linepos);
        OutputDebugStringA(buf);
#endif
        return false;
    }

    return true;
}
```

Mint4R2.cpp
Find

```
int MDrawContextR2::Text(int x, int y, const char* szText)
{
    MFontR2* pFont = (MFontR2*)m_pFont;

    if(m_pFont==NULL)
        pFont = (MFontR2*)MFontManager::Get(NULL);

    _ASSERT(pFont->m_nTypeID==MINT_R2_CLASS_TYPE);

    x += m_Origin.x;
    y += m_Origin.y;

    /*
    bool bShadow = false;

    if (pFont->m_nOutlineStyle <= 0) {    // ¾Æ¿ô¶óÀÎÆùÆ® ¾Æ´Ï¸é ±×¸²ÀÚµ¡´ë±â
        if (m_Color.r+m_Color.g+m_Color.b > 300) {
            bShadow = true;
//            pFont->m_Font.DrawText((float)x+1.0f, (float)y+1.0f, szText, MINT_ARGB(m_Color.a,0,0,0), pFont->m_fScale);
        }
    }

    pFont->m_Font.DrawText((float)x, (float)y, szText, m_Color.GetARGB(), pFont->m_fScale,bShadow,MINT_ARGB(m_Color.a,0,0,0));
*/
    DWORD dwColor = m_Color.GetARGB();
    if(pFont->m_nOutlineStyle==1)
        dwColor = 0xffffffff;

    pFont->m_Font.DrawText((float)x, (float)y, szText, dwColor , pFont->m_fScale);
    return 0;
}
```

Replace

```
int MDrawContextR2::Text(int x, int y, const char* szText)
{
    MFontR2* pFont = (MFontR2*)m_pFont;

    if (!m_pFont)
        pFont = (MFontR2*)MFontManager::Get(NULL);

    _ASSERT(pFont->m_nTypeID == MINT_R2_CLASS_TYPE);

    x += m_Origin.x;
    y += m_Origin.y;

    DWORD dwColor = m_Color.GetARGB();
    if (pFont->m_nOutlineStyle == 1)
        dwColor = 0xffffffff;

    // ----- UTF-8 → UTF-16 -----
    int wlen = MultiByteToWideChar(CP_UTF8, 0, szText, -1, NULL, 0);
    if (wlen <= 0)
        return 0;

    std::wstring wtext;
    wtext.resize(wlen);
    MultiByteToWideChar(CP_UTF8, 0, szText, -1, &wtext[0], wlen);

    // ----- Gọi DrawText phiên bản wchar_t -----
    pFont->m_Font.DrawText((float)x, (float)y, WStringView(wtext), dwColor, pFont->m_fScale);

    return 0;
}
```

and now okey let cook (korean & vietnamese display same time)

![unicode](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/refs/heads/master/source/unicode%20for%20client/unicode.png)

Credits Too: Desperate

