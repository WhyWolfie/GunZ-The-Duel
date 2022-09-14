This code manage, flashing usergrade color's and normal usergrade color's. The colors are readed from a xml file called 'UserGrade.xml'. <br>

CPP File <br>

    #pragma once


    #include "stdafx.h"
    #include <queue>


    enum ColorMode
    {
        COLOR_NORMAL,
        COLOR_FLASH,
    };


    struct UserGrade
    {
        ColorMode mode;
        int timeDelta;
        std::queue<unsigned long> colors;


        DWORD    time;
        int    count = 0;
    };


    class ZUserGradeManager : public map <int, UserGrade>
    {
    public:
        ZUserGradeManager::ZUserGradeManager() 
        {
        }


        ZUserGradeManager::~ZUserGradeManager()
        {
            clear();
        }


        static ZUserGradeManager* ZUserGradeManager::GetInstance()
        {
            static ZUserGradeManager getme;
            return &getme;
        }


        unsigned long ZUserGradeManager::GetColor(int c)
        {
            auto it = find(c);


            if (it == end())
                return 0xFFFFFFFF;
            else
            {
                DWORD time = timeGetTime();
                if (it->second.mode == COLOR_FLASH)
                {
                    if (time - it->second.time > it->second.timeDelta)
                    {
                        for (auto it = begin(); it != end(); it++)
                        {
                            unsigned long swapColor = it->second.colors.front();
                            it->second.colors.pop();
                            it->second.colors.push(swapColor);
                        }
                        it->second.time = time;
                    }
                }
                return it->second.colors.front();
            }
        }


        bool ZUserGradeManager::ReadXml(MZFileSystem* pFileSystem, const char* szFileName)
        {
            MXmlDocument    xmlIniData;
            xmlIniData.Create();


            char *buffer;
            MZFile mzf;


            if (pFileSystem)
            {
                if (!mzf.Open(szFileName, pFileSystem))
                {
                    if (!mzf.Open(szFileName))
                    {
                        xmlIniData.Destroy();
                        return false;
                    }
                }
            }
            else
            {
                if (!mzf.Open(szFileName))
                {
                    xmlIniData.Destroy();
                    return false;
                }
            }


            buffer = new char[mzf.GetLength() + 1];
            buffer[mzf.GetLength()] = 0;
            memset(buffer, 0, mzf.GetLength() + 1);


            mzf.Read(buffer, mzf.GetLength());


            if (!xmlIniData.LoadFromMemory(buffer))
            {
                xmlIniData.Destroy();
                return false;
            }


            delete[] buffer;
            mzf.Close();


            MXmlElement rootElement, chrElement, attrElement;
            char szTagName[256];


            rootElement = xmlIniData.GetDocumentElement();
            int iCount = rootElement.GetChildNodeCount();


            for (int i = 0; i < iCount; i++)
            {
                chrElement = rootElement.GetChildNode(i);
                chrElement.GetTagName(szTagName);
                if (szTagName[0] == '#') continue;


                if (!stricmp(szTagName, "USERGRADE"))
                {
                    if (!ParseGrade(chrElement))
                        return false;
                }
            }


            xmlIniData.Destroy();
            return true;
        }


    private:
        bool ZUserGradeManager::ParseGrade(MXmlElement& element)
        {
            int id = 0;
            int num = 0;
            char szAttrValue[256];
            char szAttrName[64];
            UserGrade pUserGrade;


            for (int i = 0; i < (int)element.GetAttributeCount(); i++)
            {
                memset(szAttrValue, 0, 256);
                memset(szAttrName, 0, 64);


                element.GetAttribute(i, szAttrName, szAttrValue);d
                if (!stricmp(szAttrName, "id"))
                    id = atoi(szAttrValue);
                else if (!stricmp(szAttrName, "flash"))
                    pUserGrade.mode = (ColorMode)atoi(szAttrValue);
                else if (sscanf(szAttrName, "color%i", &num))
                    pUserGrade.colors.push(strtoul(szAttrValue, NULL, 0));
                else if (!stricmp(szAttrName, "timedelta"))
                    pUserGrade.timeDelta = atoi(szAttrValue);
            }
            pUserGrade.time = timeGetTime();


            insert(std::pair<int, UserGrade>(id, pUserGrade));


            return true;
        }
    };
    inline ZUserGradeManager* ZGetUserGradeMgr() { return ZUserGradeManager::GetInstance(); }

XML Design. <br>

    <?xml version="1.0" encoding="UTF-8"?>
    <xml>
        <USERGRADE id="255" flash="1" color0="0xFF2700FF" color1="0xFFFFFFFF" color2="0xFFFF80F6" timedelta="500"/>
        <USERGRADE id="254" flash="0" color0="0xFF2700FF"/>
        <USERGRADE id="0" flash="0" color0="0xFFFFFFFF"/>
    </xml>

Usage: <br>
id = UGradeID <br>
color<num> = 0xFF<hex color> * <br>
timedelta = time in milliseconds to flash to next color <br>

* You can add unlimited flashing colors just count color0 - color1 - color2 etc <br>

NOTE: This source isn't correct, see grandao's his post. No support will be given. <br>

Credits to: Lib  <br>
