Open(MPdb.cpp) <br>
Find <br>

    if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
    {
      mlog("LoadModuleSymbols,VER_PLATFORM_WIN32_NT\n");
      if (!EnumerateLoadedModules(hProcess, (PENUMLOADED_MODULES_CALLBACK)EnumLoadedModulesCallback, (PVOID)hProcess))
      {
        ::MessageBox(NULL,"EnumerateLoadedModules failed","error",MB_OK);
        mlog("LoadModuleSymbols,EnumerateLoadedModules failed\n");
      }
      return;
    }
    
Change <br>

	if (osver.dwPlatformId == VER_PLATFORM_WIN32_NT)
	{
		return;
	}
