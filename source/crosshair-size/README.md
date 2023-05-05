<b>Crosshair Size</b><br>
I already have a long time of not posting something in this forum and I bring you this customization of the crosshair, it is only to increase or decrease the size of the crosshair.

![img](https://i.imgur.com/ZjiBrEs.png)
![img2](https://i.imgur.com/QiEJAFF.png)
![img3](https://i.imgur.com/Co20h6b.png)

ZConfiguration.cpp


		childElement.GetChildContents(&m_Etc.nCross_Size, ZTOK_ETC_CROSS_SIZE);
		if (m_Etc.nCross_Size < 50.0f || m_Etc.nCross_Size > 250.0f)
		m_Etc.nCross_Size = 50.0f;

		parentElement.AppendText("\n\t\t");
		aElement = parentElement.CreateChildElement(ZTOK_ETC_CROSS_SIZE);
		sprintf(temp, "%d", m_Etc.nCross_Size);
		aElement.SetContents(temp);

               m_Etc.nCross_Size = 100.0f;


ZConfiguration.h

     int   nCross_Size = 50.0f;
     #define ZTOK_ETC_CROSS_SIZE         "CROSSIZE"
     #define Z_ETC_CROSS_SIZE	    (ZGetConfiguration()->GetEtc()->nCross_Size)


ZOptionInterface.cpp

    pEdit = (MEdit*)pResource->FindWidget("CrossSize");
		if (pEdit)
		{
			if (Z_ETC_CROSS_SIZE < 50.0f || Z_ETC_CROSS_SIZE > 250.0f)
			Z_ETC_CROSS_SIZE = 50.0f;

			char szBuf[64];
			sprintf(szBuf, "%d", Z_ETC_CROSS_SIZE);
			pEdit->SetText(szBuf);
		}
           ///////////////////////////////
		pEdit = (MEdit*)pResource->FindWidget("CrossSize");
		if (pEdit)
		{
			float nCross_Size = atoi(pEdit->GetText());

			if (nCross_Size < 50.0f || nCross_Size > 250.0f)
				nCross_Size = 50.0f;

			Z_ETC_CROSS_SIZE = atoi(pEdit->GetText());
		}
    
    
    
ZCrossHair.cpp

      in void ZCrossHair::Draw... change these "const float sizefactor = (float)MGetWorkspaceWidth() / (float)800 * 1.f;" for  const float sizefactor = Z_ETC_CROSS_SIZE / 100.0f;
      void ZCrossHair::OnDrawOptionCrossHairPreview....
      change float sizefactor = 1.0f; to float sizefactor = Z_ETC_CROSS_SIZE / 100.0f;
    
XML Interface

    <LABEL item="Label" parent="EtcOptionGroup">
        <FONT>FONTa9</FONT>
        <TEXTCOLOR>
            <R>205</R>
            <G>205</G>
            <B>205</B>
        </TEXTCOLOR>
        <BOUNDS>
            <X>2</X>
            <Y>240</Y>
            <W>300</W>
            <H>24</H>
        </BOUNDS>
        <TEXT>Crosshair Size</TEXT>
    </LABEL>
    <EDIT item="CrossSize" parent="EtcOptionGroup">
        <BOUNDS>
            <X>105</X>
            <Y>240</Y>
            <W>60</W>
            <H>24</H>
        </BOUNDS>
    </EDIT> 
    
    
    
  
  
  
