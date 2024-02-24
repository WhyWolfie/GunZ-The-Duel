Hey everyone, im releasing here the crosshair color change, also you have to put your crosshairs ingame with white colors!

im giving jetman82 some credits for hes camera distance code :)

Open ZConfiguration.cpp
Search:

    childElement.GetChildContents(&m_Etc.nCrossHair, ZTOK_ETC_CROSSHAIR);
    
Add:

    childElement.GetChildContents(&m_Etc.nCrossColor, ZTOK_ETC_CROSSCOLOR);


Search:

    parentElement.AppendText("\n\t\t");
    aElement = parentElement.CreateChildElement(ZTOK_ETC_CROSSHAIR);
    sprintf(temp, "%d", m_Etc.nCrossHair);
    aElement.SetContents(temp);

Add Under:

    // crosscolor
    parentElement.AppendText("\n\t\t");
    aElement = parentElement.CreateChildElement(ZTOK_ETC_CROSSCOLOR);
    sprintf(temp, "%d", m_Etc.nCrossColor);
    aElement.SetContents(temp);

Search: 

    m_Etc.nCrossHair = 0;

Add under: 

    m_Etc.nCrossColor = 0;


Open ZConfiguration.h

Search:

    int nCrossHair;

Add under: 

    int nCrossColor;

Search:

    #define ZTOK_ETC_CROSSHAIR "CROSSHAIR"

Add under:

    #define ZTOK_ETC_CROSSCOLOR "CROSSCOLOR"

Search:

    #define Z_ETC_CROSSHAIR (ZGetConfiguration()->GetEtc()->nCrossHair)

Add under:

    #define Z_ETC_CROSSCOLOR (ZGetConfiguration()->GetEtc()->nCrossColor)

Search:

    ZCanvas* pCrossHairPreview = (ZCanvas*)pResource->FindWidget("CrossHairPreviewCanvas");
    if (pCrossHairPreview)
    {
    pCrossHairPreview->SetOnDrawCallback(ZCrossHair::OnDrawOptionCrossHairPreview);
    }

Add under:

    pComboBox = (MComboBox*)pResource->FindWidget("CrossColor");
    if (pComboBox)
    {
    pComboBox->SetSelIndex(Z_ETC_CROSSCOLOR);
    ZGetCombatInterface()->GetCrossHair()->RSetCrossColor(Z_ETC_CROSSCOLOR);
    }

Search:

    MComboBox* pComboBox = (MComboBox*)pResource->FindWidget("CrossHairComboBox");
    if (pComboBox)
    {
    Z_ETC_CROSSHAIR = pComboBox->GetSelIndex();
    }

Add under:

    pComboBox = (MComboBox*)pResource->FindWidget("CrossColor");
    if (pComboBox)
    {
    Z_ETC_CROSSCOLOR = pComboBox->GetSelIndex();
    ZGetCombatInterface()->GetCrossHair()->RSetCrossColor(Z_ETC_CROSSCOLOR);
    }

Open ZCrossHair.h
Search:

    void Destroy();
    
Add under:

    void RSetCrossColor(unsigned short nCrossColor);


Open ZCrossHair.cpp

At the top, above 
Search:

    ZCrossHair::ZCrossHair(), 

Add under:

    MCOLOR g_nCrossColor = 0;

Search for Draw(MDrawContext* pDC), above it, add this:

    void ZCrossHair::RSetCrossColor(unsigned short nCrossColor)
    {
    switch (nCrossColor)
    {
    case 0: { g_nCrossColor = MCOLOR(255, 255, 255); } break;
    case 1: { g_nCrossColor = MCOLOR(255, 0, 0); } break;
    case 2: { g_nCrossColor = MCOLOR(0, 255, 0); } break;
    case 3: { g_nCrossColor = MCOLOR(0, 0, 255); } break;
    case 4: { g_nCrossColor = MCOLOR(255, 255, 0); } break;
    case 5: { g_nCrossColor = MCOLOR(128, 0, 128); } break;
    case 6: { g_nCrossColor = MCOLOR(0, 0, 0); } break;
    case 7: { g_nCrossColor = MCOLOR(255, 0, 255); } break;
    case 8: { g_nCrossColor = MCOLOR(0, 255, 255); } break;
    default: { g_nCrossColor = MCOLOR(255, 255, 255); } break;
    }
    }

Inside, void DrawCrossHair, replace this:

    if(ppBitmaps[CH_CENTER])
    {
    sizex = ppBitmaps[CH_CENTER]->GetWidth() * fSizeFactor ;
    sizey = ppBitmaps[CH_CENTER]->GetHeight() * fSizeFactor ;
    
    pDC->SetBitmap(ppBitmaps[CH_CENTER]);
    pDC->Draw(center.x-sizex/2,center.y-sizey/2,sizex,sizey);
    }

with this:

    if(ppBitmaps[CH_CENTER])
    {
    sizex = ppBitmaps[CH_CENTER]->GetWidth() * fSizeFactor ;
    sizey = ppBitmaps[CH_CENTER]->GetHeight() * fSizeFactor ;
    
    MCOLOR originalColor = pDC->GetBitmapColor();
    pDC->SetBitmapColor(g_nCrossColor);
    pDC->SetBitmap(ppBitmaps[CH_CENTER]);
    pDC->Draw(center.x-sizex/2,center.y-sizey/2,sizex,sizey);
    pDC->SetBitmapColor(originalColor);
    }

Open Option.xml

    <LABEL item="Label" parent="EtcOptionGroup">
    <FONT>FONTa10_O2Wht</FONT>
    <TEXTCOLOR>
    <R>205</R>
    <G>205</G>
    <B>205</B>
    </TEXTCOLOR>
    <BOUNDS>
    <X>2</X>
    <Y>300</Y>
    <W>300</W>
    <H>24</H>
    </BOUNDS>
    <TEXT>Crosshair Color</TEXT>
    </LABEL>
    <COMBOBOX item="CrossColor" parent="EtcOptionGroup">
    <LISTBOXLOOK>CustomListBoxLook</LISTBOXLOOK>
    <BUTTONLOOK>ListBoxButtonLook</BUTTONLOOK>
    <FONT>FONTa10_O2Wht</FONT>
    <TEXTCOLOR>
    <R>205</R>
    <G>205</G>
    <B>205</B>
    </TEXTCOLOR>
    <TEXTALIGN>
    <VALIGN>center</VALIGN>
    <HALIGN>left</HALIGN>
    </TEXTALIGN>
    <BOUNDS>
    <X>105</X>
    <Y>300</Y>
    <W>90</W>
    <H>24</H>
    </BOUNDS>
    <ALIGN>
    <HALIGN>right</HALIGN>
    </ALIGN>
    <LISTITEM selected="true">White</LISTITEM>
    <LISTITEM>Red</LISTITEM>
    <LISTITEM>Green</LISTITEM>
    <LISTITEM>Blue</LISTITEM>
    <LISTITEM>Yellow</LISTITEM>
    <LISTITEM>Purple</LISTITEM>
    <LISTITEM>Black</LISTITEM>
    <LISTITEM>Pink</LISTITEM>
    <LISTITEM>Cyan</LISTITEM>
    <DROPSIZE>80</DROPSIZE>
    <COMBOTYPE>1</COMBOTYPE>
    </COMBOBOX>




















