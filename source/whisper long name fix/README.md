Open(ZChat_Cmds.cpp) <br>
Find <br>

	int nNameLen = (int)strlen(szName);
	if ( nNameLen < MIN_CHARNAME)		// ÀÌ¸§ÀÌ ³Ê¹« Âª´Ù.
	{
		const char *str = ZErrStr( MERR_TOO_SHORT_NAME );
		if(str)
		{
			char text[1024];
			sprintf(text, "%s (E%d)", str, MERR_TOO_SHORT_NAME);
			ZChatOutput(MCOLOR(96,96,168), text, ZChat::CL_CURRENT);
		}
	}
	else if ( nNameLen > MAX_CHARNAME)		// ÀÌ¸§ÀÌ Á¦ÇÑ ±ÛÀÚ¼ö¸¦ ³Ñ¾ú´Ù.
	{
		const char *str = ZErrStr( MERR_TOO_LONG_NAME );
		if(str)
		{
			char text[1024];
			sprintf(text, "%s (E%d)", str, MERR_TOO_LONG_NAME);
			ZChatOutput(MCOLOR(96,96,168), text, ZChat::CL_CURRENT);
		}
	}
  
Replace <br>

	int nNameLen = (int)strlen(szName);
	if ( nNameLen < 1)		//Changed MIN_CHARNAME to 1 to fix whisper issues with short names.
	{
		const char *str = ZErrStr( MERR_TOO_SHORT_NAME );
		if(str)
		{
			char text[1024];
			sprintf(text, "%s (E%d)", str, MERR_TOO_SHORT_NAME);
			ZChatOutput(MCOLOR(96,96,168), text, ZChat::CL_CURRENT);
		}
	}
	//Changed > MAX_CHARNAME to 128, to fix whisper issues with long names.
	else if ( nNameLen > 128)		// ÀÌ¸§ÀÌ Á¦ÇÑ ±ÛÀÚ¼ö¸¦ ³Ñ¾ú´Ù.
	{
		const char *str = ZErrStr( MERR_TOO_LONG_NAME );
		if(str)
		{
			char text[1024];
			sprintf(text, "%s (E%d)", str, MERR_TOO_LONG_NAME);
			ZChatOutput(MCOLOR(96,96,168), text, ZChat::CL_CURRENT);
		}
	}
