/*
	GunzConsole xDividerx @ Ragezone
	12/05/2021
	
	Released: 5/12/2022
	
	My Discord: MassDivide#3471
	
	


	This is a code snippet. Not the complete file.

	Use for refrence on how to invoke the console.



*/



void CGLEncription::CheckForParam()
{
	CFile file;
	CFileException ex;
	if (file.Open("GunzLauncher.ini", CFile::modeRead, &ex) == TRUE) // Change this to whatever ini file you want.
	{
		char* szBuff = new char[(unsigned int)file.GetLength()];
		file.Read(szBuff, (UINT)file.GetLength());


		if (strstr(szBuff, "@CONSOLEONLINE") != NULL) // Set @CONSOLEONLINE to whatever you want. This will skip encryption if enabled for faster debugging. You can sync this with @SKIP_UPDATE or whatever.
		{
			SkipEnc = true;
			EnableConsole = true; // CONSOLE WILL NOW ACTIVATE
			return;
		}
		delete[] szBuff;
		file.Close();
	}
	