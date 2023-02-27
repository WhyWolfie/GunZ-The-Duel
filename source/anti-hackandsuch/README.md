[Ant Hacker]

    #include <Windows.h> 
    #include <stdio.h> extern "C" BOOL __stdcall EndTask(HWND,BOOL,BOOL); void main() { HWND hwnd = FindWindow(0, "Cheat Engine 6.0"); 



    if(!hwnd) { printf("Escaneando\n"); 
    }else{ EndTask(hwnd, FALSE, TRUE); printf("Cheat Engine Fechado!\n"); Sleep(2000); 
    } system("pause"); 
    }  

Creditos: EletroBlack


[Ant inject]

    <?phpif() {
        $search = array("UPDATE", "INSERT","delete","insert","update character","drop table","show","show tables","login","password",login,"set","grade","ugradeid","clan","GunzDB","DB","union","update login","update password,"delete from","varchar","cast","exec","request",";",",","","*","x:","drop",);

        foreach($search as $k)
            if(in_array($k, explode(" ", strtoupper($s))))
                die("Uma tentativa de sql injection foi detectada.");
    }
    ?>





[Simples]
 
    void Log(const char* motivo) { FILE *pFile; pFile = fopen("Logs.txt", "w+"); fputs(motivo, pFile); fclose(pFile); 
    } void Fechar(int tempo) { //BlockInput(true); Sleep(tempo); __asm{ JE 0 } 
    } void HackEnable(const char* name) { 
        char buf[1024]; 
        sprintf(buf, "\"%s\" foi suspeito de programa ilegal sendo executado, por favor, feche-o e reinicie o jogo.\n",name); 
        Log(buf); 
        Fechar(1001); 
    } bool MemoryEdit() { HANDLE Processo = GetCurrentProcess();  WORD value[3]; DWORD byteslidos[3]; 

    if(ReadProcessMemory(Processo,(long *)0x0040A31F, &value[0], sizeof(long), &byteslidos[0])) { 
        if(value[0] != 2283) { 
        //if(!strstr(ZGetGameClient()->CurrentGame, "[ESP]")) { 
          // ESP DETECTADO 
          HackEnable("ESP"); 
        }else{ 
        return false; 
        } 
    } 
    } //12937 if(ReadProcessMemory(Processo,(long *)0x00502E43, &value[1], sizeof(long), &byteslidos[1])) { 
        if(value[1] != 8834) { 
        HackEnable("Wall Hack"); 
        } 
    } /*if(ReadProcessMemory(Processo,(long *)0x00485F8A, &value[2], sizeof(long), &byteslidos[2])) { 
        // inultiu n terminado  - jump hack 
    }*/ 
    /*if( *(DWORD*)::QueryPerformanceCounter != 2337669003) { 
        // uc 
    }*/ }  
    
<br>
[Anti Shotbot - Wizkid]


<br>




        #include <windows.h>

        DWORD g_dwLoadLibraryAJMP;

        /* HOOK FUNCTION */

        DWORD WINAPI jumphook( DWORD AddressToPerformJump, DWORD AddressOfMyFunction, DWORD LenghOfTheAreaToPerformTheJump )
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

    [Anti Shotbot - Wizkid]

    HHOOK MouseHook;

    LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
     if (nCode == HC_ACTION)
     {
      if(wParam == WM_RBUTTONDOWN || wParam == WM_LBUTTONDOWN)
      {
       MSLLHOOKSTRUCT *info=(MSLLHOOKSTRUCT*)lParam;     
       if((info->flags & LLMHF_INJECTED) == LLMHF_INJECTED)
       {
        ExitProcess(-1);
       }
      }
     }
     return CallNextHookEx(MouseHook,nCode,wParam,lParam);
    }


    void AntiShotbotLogger()
    {
        HINSTANCE hInstance = GetModuleHandle(NULL);

        MouseHook = SetWindowsHookEx( WH_MOUSE_LL, MouseHookProc, hInstance, NULL );
        MSG message;
        while (GetMessage(&message,NULL,0,0)) {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }

        UnhookWindowsHookEx(MouseHook);
        return;
    }


[antishotbot.cpp - Gunblade]

    #include "StdAfx.h"

    HHOOK MouseHook;

    LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
     if (nCode == HC_ACTION)
     {
      if(wParam == WM_RBUTTONDOWN || wParam == WM_LBUTTONDOWN)
      {
       MSLLHOOKSTRUCT *info=(MSLLHOOKSTRUCT*)lParam;     
       if((info->flags & LLMHF_INJECTED) == LLMHF_INJECTED)
       {
        ExitProcess(-1);
       }
      }
     }
     return CallNextHookEx(MouseHook,nCode,wParam,lParam);
    }


    void AntiShotbotLogger()
    {
        HINSTANCE hInstance = GetModuleHandle(NULL);

        MouseHook = SetWindowsHookEx( WH_MOUSE_LL, MouseHookProc, hInstance, NULL );
        MSG message;
        while (GetMessage(&message,NULL,0,0)) {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }

        UnhookWindowsHookEx(MouseHook);
        return;
    }

[go to main.cpp in the gunz solution and add]

    //Don't put this inside a function, Do it like somewhere at the top (Like line 96 or so)
            void AntiShotbotLogger();
    //Put this on line 197 under InitialLoading success
     CreateThread(0, 0, (LPTHREAD_START_ROUTINE)AntiShotbotLogger, 0, 0, 0);


[For the DLL users:]

    #include <windows.h>

    HHOOK MouseHook;

    LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
     if (nCode == HC_ACTION)
     {
      if(wParam == WM_RBUTTONDOWN || wParam == WM_LBUTTONDOWN)
      {
       MSLLHOOKSTRUCT *info=(MSLLHOOKSTRUCT*)lParam;     
       if((info->flags & LLMHF_INJECTED) == LLMHF_INJECTED)
       {
        ExitProcess(-1);
       }
      }
     }
     return CallNextHookEx(MouseHook,nCode,wParam,lParam);
    }


    void AntiShotbotLogger()
    {
        HINSTANCE hInstance = GetModuleHandle(NULL);

        MouseHook = SetWindowsHookEx( WH_MOUSE_LL, MouseHookProc, hInstance, NULL );
        MSG message;
        while (GetMessage(&message,NULL,0,0)) {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }


[Ant Update Hacker - Allan (Dogshow)]

    char* stristr( char* szStr1, char* szStr2 ){ 
        char *pCp = szStr1; 

        if( *szStr2 == NULL ){ 
            return szStr1; 
        } 

        char *pTemp1, 
             *pTemp2; 

        while( *pCp ){ 
            pTemp1 = pCp; 
            pTemp2 = szStr2; 

            while ( *pTemp1 && *pTemp2 && !( tolower( *pTemp1 ) - tolower( *pTemp2 ) ) ) { 
               pTemp1++, pTemp2++; 
            } 

            if( *pTemp2 == NULL ){ 
                return pCp; 
            } 

            pCp++; 
        } 

        return NULL; 
    } 
    bool HaveUpdateHack( void ){ 

        WIN32_FIND_DATA mData; 
        HANDLE hFile = FindFirstFile( "*.mrs", &mData ); 

        //! Falhou 
        if( hFile == INVALID_HANDLE_VALUE ){ 
            return false; 
        } 

        do{ 
            if( stristr( mData.cFileName, "update" ) ){ 
                if( _stricmp( mData.cFileName, "Update1.mrs" /*) && 
                    _stricmp( mData.cFileName, "Update2.mrs" */) ){ 


                        return true; 
                } 
            } 
        }while( FindNextFile( hFile, &mData ) ); 
        CloseHandle( hFile ); 

        return false; 
    } 
    void HackerDectado() 
    { 
        if(HaveUpdateHack() == true) 
        { 

        MessageBoxTimeoutA( NULL, "MRS Edit Detected!", "Ant-UpdateHacker.", MB_ICONHAND, NULL, 3000 ); 
        ((ULONG(__stdcall*)( HANDLE, ULONG ))GetProcAddress( LoadLibrary( "ntdll.dll" ), "ZwTerminateProcess" ))( GetCurrentProcess(), 0 ); 
        return; 
        } 
    }  

[Source Protect] <br>
It can be programmed to block any program, just by their name, which is shotbot's case, but it is easy to be broken, as for example if you can change the name of the executable, this protection will be useless.
I've seen it even in duality, because when I tried to use the Encrypt Tool 2 it blocked, I changed the executable name and got to use it.


    # Include "vsBuffer.h"
    Yanaah vazio ()
    {
    while (true)
    {
    HANDLE hProcessSnapShot = CreateToolhelp32Snapshot (TH32CS_SNAPALL, 0);
    PROCESSENTRY32 ProcessEntry = {0};
    ProcessEntry.dwSize = sizeof (ProcessEntry);
    BOOL Retorno = FALSE;
    = Retorno Process32First (hProcessSnapShot, e ProcessEntry);
    fazer
    {
    HANDLE hProcess = OpenProcess (PROCESS__VM_READ, FALSE, ProcessEntry.th32ProcessID);
    if (! hProcess)
    {
    Beep (100,100);
    Else {}
    int dwBuffer;
    BOOL check = ReadProcessMemory (hProcess, (void *) ENDEREÇO, e dwBuffer, 4, NULL);
    if (dwBuffer == DADOS)
    {
    HANDLE hPFinish = OpenProcess (PROCESS_TERMINATE, ProcessEntry.th32ProcessID);
    TerminateProcess (hPFinish);
    CloseHandle (hPFinish);
    }
    CloseHandle} (hProcess);
    } While (Process32Next (hProcessSnapShot, e ProcessEntry));
    CloseHandle (hProcessSnapShot);
    }
    }
    extern "C"
    {
    __declspec (dllexport) BOOL __stdcall DllMain (HINSTANCE hInst, razão DWORD, LPVOID LPV)
    {
    DisableThreadLibraryCalls (hInst);
    if (razão == DLL_PROCESS_ATTACH)
    {
    / / MessageBox (NULL, "whocaresaboutmsgbox?", "Nanimonai", MB_OK);
    CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE) & Yanaah, NULL, 0, NULL);
    }
    return true;
    }
    }

DATA = Change your data
ADDRESS = Change to your address

I am also releasing with this a parser, "Vanitas"
(Download available below)

Step 1: Make sure the process you want to block is running
Step 2: Find your process address in OllyDbg
Step 3: Enter your process name with exe (ex: "explorer.exe")
Step 4: Enter your process address with 0x (ex: 0x00478C74)

Change the source to the address you specified in the program
here:
Code:

BOOL check = ReadProcessMemory (hProcess, (void *) ADDRESS, and dwBuffer, 4, NULL);

The program will process the data you need for input in the
Code:

if (dwBuffer == DATA) <Ex:
Code:

BOOL check = ReadProcessMemory (hProcess, (void *) 0x00478C74, e dwBuffer, 4, NULL);
if (dwBuffer == - -2142260117)
{
cout <<"Process was found in memory" <If your doesnt address exists or the program is not running you will get an error message. = (

This will end up doing kernel driver life or terminating the process by its names.
The image below is AN EXAMPLE Check if the address exists in the executable program




















