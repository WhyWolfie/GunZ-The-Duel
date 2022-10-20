Open(Main.cpp) <br>

    void ZPerformHooks();

Create a file: (AntiInject.h)

    #include <windows.h>
    #include "StdAfx.h"

    DWORD g_dwLoadLibraryAJMP;

    /* HOOK FUNCTION */

    DWORD WINAPI jumphook( DWORD AddressToPerformJump, DWORD AddressOfMyFunction, DWORD LenghOfTheAreaToPerformTheJump	)
    {
      if( LenghOfTheAreaToPerformTheJump < 5 )
        return 0;

      DWORD RelativeJump, 
          NextInstructionAddress,
          Flag;

      if ( ! VirtualProtect((LPVOID)AddressToPerformJump, LenghOfTheAreaToPerformTheJump, PAGE_EXECUTE_READWRITE, &Flag) )
        return 0;

      NextInstructionAddress = AddressToPerformJump + LenghOfTheAreaToPerformTheJump;

      *(BYTE*)AddressToPerformJump = 0xE9;

      for( DWORD i = 5; i < LenghOfTheAreaToPerformTheJump; i++)
        *(BYTE*)(AddressToPerformJump+i) = 0x90;

      RelativeJump = AddressOfMyFunction - AddressToPerformJump - 0x5;

      *(DWORD*)(AddressToPerformJump + 0x1) = RelativeJump;

      VirtualProtect((LPVOID)AddressToPerformJump, LenghOfTheAreaToPerformTheJump, Flag, &Flag);

      return NextInstructionAddress; 
    }

    /* END HOOK FUNCTION */

    HMODULE WINAPI hLoadLibraryA( LPCSTR lpLibFileName )
    {	
      __asm
      {
        mov eax, dword ptr ss:[esp + 0x18]
        cmp dword ptr ds:[eax-0x12], 0x8B55FF8B
        je erro
      }


      if( lpLibFileName )
      {
        if( !strcmp( lpLibFileName, "twain_32.dll" ) )
          __asm jmp g_dwLoadLibraryAJMP
      }			

      return LoadLibraryExA( lpLibFileName, 0, 0 );

    erro:

      /* dll injetada */


      ExitProcess( 0 );

      return 0;
    }

    void ZPerformHooks()
    {
      g_dwLoadLibraryAJMP = (DWORD)GetModuleHandle( "kernel32" ) + 0x6E2A1;

      jumphook( (DWORD)LoadLibraryA, (DWORD)&hLoadLibraryA, 57 );
    }
