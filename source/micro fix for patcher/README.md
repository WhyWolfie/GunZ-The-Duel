This fix is for anyone whom has multiple files with the same name existing within their client. The default patcher will error out without a temp directory structure for those file names.

Example if you have a config.xml in the main gunz directory, but a Quest folder with a different config.xml, the patcher will error out forcing you to reattempt patching.

Structure
[GunZ]->config.xml "Gets CRC, downloads and patches"
[GunZ/Interface/]->config.xml "Thinks it is the config.xml above it, invalid crc, fails to patch, must be manually reattempted"
[GunZ/Custom/]->config.xml "Same issue as above"

If you have multiple required files with the same name, but in different locations, it will error out until keep trying to download them individually. To fix this, i've added a /dir/ inside of the PATCH directory specifying its location.

In ZUpdate.cpp replace:


    void GetTempFilePathName( const char* szFileName, char* szTmpFileName)
    {
        char szDir[ _MAX_DIR];
        GetCurrentDirectory( sizeof( szDir), szDir);
    
    
        char drive[ _MAX_PATH], dir[ _MAX_PATH], fname[ _MAX_PATH], ext[ _MAX_PATH];
        _splitpath( szFileName, drive, dir, fname, ext);
    
    
        sprintf( szTmpFileName, "%s\\%s\\%s\\%s%s_", szDir, STR_TEMP_DOWNLOADFOLDER, dir, fname, ext);
    }

Credits: xDividerx
