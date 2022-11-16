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
