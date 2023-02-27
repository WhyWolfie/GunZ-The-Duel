#include <windows.h>
#include <stdio.h>


typedef void(__cdecl* ZChatOutputType)(const char*,int,int,DWORD);
ZChatOutputType ZChatOutput = (ZChatOutputType)0x0042B7D0;

typedef void(__cdecl* ZPostShotType)(float*,float*,int,int);
ZPostShotType ZPostShot = (ZPostShotType)0x00481360; 

typedef void(__cdecl* ZPostShotMeleeType)(float*,int);
ZPostShotMeleeType ZPostShotMelee = (ZPostShotMeleeType)0x00481440; 

typedef DWORD(__cdecl* ZGetGameClientType)();
ZGetGameClientType ZGetGameClient = (ZGetGameClientType)0x004AD700;

typedef DWORD(__cdecl* ZGetGameInterfaceType)();
ZGetGameInterfaceType ZGetGameInterface = (ZGetGameInterfaceType)0x004AD720;

typedef DWORD(__cdecl* ZPostPeerChatType)(char*,int);
ZPostPeerChatType ZPostPeerChat = (ZPostPeerChatType)0x0042AD30;

typedef DWORD(__cdecl* ZPostReloadType)();
ZPostReloadType ZPostReload = (ZPostReloadType)0x00433D30;

char BUFFER[1024];


typedef void(__cdecl* ZPostSkillType)(int,int);
ZPostSkillType ZPostSkill = (ZPostSkillType)0x00481260;

DWORD SetHPaddr = 0x00476DB0;
DWORD SetAPaddr = 0x00476DC0;

bool roomkill = 0;

struct MUID
{
unsigned long LowID;
unsigned long HighID;
};

//
typedef DWORD(__cdecl* ZPostStageEnterBattleType)(MUID*,MUID*);
ZPostStageEnterBattleType ZPostStageEnterBattle = (ZPostStageEnterBattleType)0x0051AFE0;
//
typedef DWORD(__cdecl* ZPostStageLeaveBattleType)(MUID*,MUID*);
ZPostStageLeaveBattleType ZPostStageLeaveBattle = (ZPostStageLeaveBattleType)0x00468240;



/*
typedef void(__cdecl* ZPostRequestSpawnType)(MUID*,float*,float*);
ZPostRequestSpawnType ZPostRequestSpawn = (ZPostRequestSpawnType)0x004B4090;
*/

DWORD ZPostRequestSpawnADDR = 0x004B4090;

//Crashes for some reason without assembly <.<
void ZPostRequestSpawn(MUID* uid,float *pos,float *dir)
{
__asm
{
PUSH dir
PUSH pos
PUSH uid
CALL ZPostRequestSpawnADDR
}
}

typedef void(__cdecl* ZPostStageTeamType)(MUID*,MUID*,int);
ZPostStageTeamType ZPostStageTeam = (ZPostStageTeamType)0x0044B2D0;

typedef void(__cdecl* ZPostChannelChatType)(MUID*,MUID*,char*);
ZPostChannelChatType ZPostChannelChat = (ZPostChannelChatType)0x0042AEB0;


typedef void(__cdecl* ZPostSpMotionType)(int);
ZPostSpMotionType ZPostSpMotion = (ZPostSpMotionType)0x004A2CE0;

//
typedef void(__cdecl* ZPostRequestSpawnWorldItemType)(MUID*,int,float*);
ZPostRequestSpawnWorldItemType ZPostRequestSpawnWorldItem = (ZPostRequestSpawnWorldItemType)0x00532130;


typedef void(__cdecl* ZPostCreateMyCharType)(MUID*,int,char*,int,int,int,int);
ZPostCreateMyCharType ZPostCreateMyChar = (ZPostCreateMyCharType)0x0044B490;


MUID *NewCHAR = new MUID();
MUID *NewSTAG = new MUID();
MUID *NewCHAN = new MUID();


DWORD *pGame = (DWORD*)0x006D46B0;

DWORD pChar()
{
if (pGame!=NULL && *pGame!=NULL){return *(DWORD*)(*pGame + 0x50);}
return NULL;
}

void SetHP(int hp)
{
DWORD ZChar = (DWORD)pChar();
__asm{
MOV ECX, ZChar
MOV EAX,SetHPaddr
PUSH hp
CALL EAX
}

}









//Created by LONE222

int NumberOfPeers = 0;
#define minexaust 1 
#define maxexaust 10000001
MUID Peers[maxexaust];

MUID GetPeerFromList(int Offset)
{
MUID Empty;
if (Offset>0 && Offset<=NumberOfPeers){return Peers[Offset];}else{return Empty;}
}




int GetPeersInMUIDList()
{
return NumberOfPeers;
}



bool IsPeerInList(MUID ThisPeer)
{
bool RETN = 0;
for(int i = 1;i<=GetPeersInMUIDList();i++)
{
if (GetPeerFromList(i).HighID == ThisPeer.HighID && RETN == 0){RETN = 1;}
}
return RETN;

}


void AddPeerToList(MUID ThisPeer)
{
//if (!IsPeerInList(ThisPeer)){
NumberOfPeers++;
Peers[NumberOfPeers] = ThisPeer;
//}
}



void RemovePeerFromList(MUID ThisPeer)
{
bool RETN = 0;
for(int i = 1;i<=GetPeersInMUIDList();i++)
{
if (GetPeerFromList(i).HighID == ThisPeer.HighID && RETN == 0){Peers[i].HighID = 0;Peers[i].LowID = 0;RETN = 1;}
}
}






void SetAP(int ap)
{
DWORD ZChar = (DWORD)pChar();
__asm{
MOV ECX, ZChar
MOV EAX,SetAPaddr
PUSH ap
CALL EAX
}

}

float Empty[] = {0,0,0,0};
MUID *NewEMPT = new MUID();

float *GetPlayerDirection()
{
return (float*)(DWORD)(pChar() + 0x5C);
}


DWORD ZCharacterManagerADDR     = 0x004A0D00;
DWORD ZCharacterManagerFindADDR = 0x0047D860;


DWORD GetZChar(MUID charZ)
{
unsigned long LOW = 0;
unsigned long HIGH = charZ.HighID;
DWORD result;

__asm
{
MOV EDX, LOW
MOV EBX, HIGH
MOV EAX, ZCharacterManagerADDR
CALL EAX
MOV ECX,EAX
PUSH EBX
PUSH EDX
MOV EAX, ZCharacterManagerFindADDR
CALL EAX
MOV result,EAX
}
return result;
}


float *GetObjectPosition(DWORD ZChar)
{
DWORD ECX = ZChar;
DWORD EAX = *(DWORD*)(ECX + 0x58);
ECX = *(DWORD*)(EAX + 0x20);
DWORD EDX = *(DWORD*)(EAX + 0xC);
EAX = *(DWORD*)(EDX + ECX * 0x4);
return (float*)EAX;
}

void SetPos(float *POS)
{
float *PointerToPosition = GetObjectPosition(pChar());
PointerToPosition[0] = POS[0];
PointerToPosition[1] = POS[1];
PointerToPosition[2] = POS[2];
}

void SetPosition(float X,float Y,float Z)
{
float *PointerToPosition = GetObjectPosition(pChar());
PointerToPosition[0] = X;
PointerToPosition[1] = Y;
PointerToPosition[2] = Z;
}

float GetXPosition()
{
float *PointerToPosition = GetObjectPosition(pChar());
return PointerToPosition[0];
}


float GetYPosition()
{
float *PointerToPosition = GetObjectPosition(pChar());
return PointerToPosition[1];
}

float GetZPosition()
{
float *PointerToPosition = GetObjectPosition(pChar());
return PointerToPosition[2];
}

 
MUID Attacker()
{
DWORD ZChar = (DWORD)pChar();
MUID Aa;
Aa.LowID = 0;

DWORD EAX = ZChar;
EAX = *(DWORD*)(EAX + 0x3BC);
EAX = *(DWORD*)(EAX + 0x20);

Aa.HighID = EAX;
return Aa;
}


MUID GetMe()
{
MUID Aa;
Aa.LowID = 0;
Aa.HighID = *(DWORD*)(ZGetGameClient() + 0x1A4);
return Aa;
}

char *LastInput()
{
return (char*)(0x0366DC38);
}
MUID GetStage()
{
MUID Aa;
Aa.LowID = 0;
Aa.HighID = *(DWORD*)(ZGetGameClient() + 0x1B4);
return Aa;
}

MUID GetChannel()
{
MUID Aa;
Aa.LowID = 0;
Aa.HighID = *(DWORD*)(ZGetGameClient() + 0x1AC);
return Aa;
}



int __speed = 20;

bool godmode = 0;
bool flipmower = 0;
bool lawnmower = 0;
bool massives = 0;
bool inv = 0;

int team = -1;
int Slot = 0;


void roomper()
{while(1){
if (roomkill==1 && Slot!=0 && GetZChar(GetPeerFromList(Slot))!=0)
{

    SetPosition(GetObjectPosition(GetZChar(GetPeerFromList(Slot)))[0],GetObjectPosition(GetZChar(GetPeerFromList(Slot)))[1],GetObjectPosition(GetZChar(GetPeerFromList(Slot)))[2]);

    ZPostSkill(2,7);
    ZPostShot(GetObjectPosition(pChar()),Empty,1,2);
    SetHP(9999);SetAP(9999);

}





Sleep(__speed);}}





void roomcheck()
{while(1){

if (roomkill){
if (pChar())
{
Slot = 0;

for(int i=1;i<=GetPeersInMUIDList();i++){
if (pChar()){Slot = i;
if (GetZChar(GetPeerFromList(Slot))!=0){Sleep(2000);}}}
}}


Sleep(__speed);}}


void addalltolist()
{while(1){
MUID NewCHAR2;
if (pChar()!=NULL)
{




    NumberOfPeers = 0;

    for(int b=minexaust;b<=maxexaust;b++)
    {
        NewCHAR2.LowID = 0;
        NewCHAR2.HighID = b;
        if (b != GetMe().HighID && GetZChar(NewCHAR2)!=0){
            AddPeerToList(NewCHAR2);
        }
    }

}
Sleep(10000);
}
}





void CheckKeys()
{





while(1){ 


/*

if (GetAsyncKeyState(VK_RETURN)&0x8000){

//char *lol = (char*)0x0366DC38;

sprintf(BUFFER,"String '%d'",LastInput()[1]);

//sprintf(BUFFER,"String '%X'",ZGetGameInterface());
//ZChatOutput(BUFFER,2,0,0xFFFFFFFF); 
//sprintf(BUFFER,"String '%X'",ZGetGameClient());
ZChatOutput(BUFFER,2,0,0xFFFFFFFF); Sleep(2000);


if (memcmp(LastInput(),"@male ",6)==0)
{
//Copy our string from offset 12
char MEMCMPSTR4[12];
for(int i = 6;i<=18;i++)

{
int Str = 0;

if (LastInput()[i] == ''){MEMCMPSTR4[i-6] = '\n';Str = 1;} //Alt + 0141  ; New Line
if (LastInput()[i] == ' '){MEMCMPSTR4[i-6] = '\t';Str = 1;} //Alt + 0160 ; Tab
//Alt + 255 also = space

if (Str == 0){MEMCMPSTR4[i-6] = LastInput()[i];}
}

NewCHAR->LowID = 0;
NewCHAR->HighID = GetMe().HighID;
for(int a = 0;a<=4;a++)ZPostCreateMyChar(NewCHAR,a,MEMCMPSTR4,0,4,0,1); //female = 1 ; male = 0 ; Male is first :( SEXIST!!!!


Sleep(1200);
}






if (memcmp(LastInput(),"@female ",8)==0)
{
//Copy our string from offset 12
char MEMCMPSTR5[12];
for(int i = 8;i<=20;i++)

{
int Str = 0;

if (LastInput()[i] == ''){MEMCMPSTR5[i-8] = '\n';Str = 1;} //Alt + 0141  ; New Line
if (LastInput()[i] == ' '){MEMCMPSTR5[i-8] = '\t';Str = 1;} //Alt + 0160 ; Tab
//Alt + 255 also = space

if (Str == 0){MEMCMPSTR5[i-8] = LastInput()[i];}
}

NewCHAR->LowID = 0;
NewCHAR->HighID = GetMe().HighID;
for(int a = 0;a<=4;a++)ZPostCreateMyChar(NewCHAR,a,MEMCMPSTR5,1,4,0,1); //female = 1 ; male = 0 ; Male is first :( SEXIST!!!!

Sleep(1200);
}
}


*/






if (pChar()) {


if (GetAsyncKeyState(VK_NUMPAD0)&0x8000){SetPosition(GetXPosition(),GetYPosition(),GetZPosition() - 100);}
if (GetAsyncKeyState(VK_NUMPAD1)&0x8000){SetPosition(GetXPosition(),GetYPosition(),GetZPosition() + 100);}

if (GetAsyncKeyState(VK_NUMPAD4)&0x8000){SetPosition(GetXPosition(),GetYPosition() - 100,GetZPosition());}
if (GetAsyncKeyState(VK_NUMPAD6)&0x8000){SetPosition(GetXPosition(),GetYPosition() + 100,GetZPosition());}

if (GetAsyncKeyState(VK_NUMPAD2)&0x8000){SetPosition(GetXPosition() + 100,GetYPosition(),GetZPosition());}
if (GetAsyncKeyState(VK_NUMPAD8)&0x8000){SetPosition(GetXPosition() - 100,GetYPosition(),GetZPosition());}

if (GetAsyncKeyState(0x12)&0x8000 && GetAsyncKeyState('O')&0x8000){inv=!inv;Sleep(500);}

if (GetAsyncKeyState(VK_NUMPAD3)&0x8000){for(int i=1;i<=15;i++)ZPostSpMotion(i);}

if (GetAsyncKeyState(VK_NUMPAD5)&0x8000){roomkill=!roomkill;Sleep(500);}


//if (GetAsyncKeyState(VK_TAB)&0x8000){ZPostReload();} <.< Patched, reloads once
}



if (GetAsyncKeyState(VK_NUMPAD7)&0x8000){
char name[12];
FILE * f = fopen("szCharName.txt","r");
fgets(name,12,f);
fclose(f);

NewCHAR->LowID=0;
NewCHAR->HighID=GetMe().HighID;

for(int i=0;i<=4;i++)ZPostCreateMyChar(NewCHAR,i,name,1,4,0,1);
;}

if (GetAsyncKeyState(VK_NUMPAD9)&0x8000){
char name[12];
FILE * f = fopen("szCharName.txt","r");
fgets(name,12,f);
fclose(f);

NewCHAR->LowID=0;
NewCHAR->HighID=GetMe().HighID;

for(int i=0;i<=4;i++)ZPostCreateMyChar(NewCHAR,i,name,0,4,0,1);
;}



if (GetAsyncKeyState(VK_PRIOR)&0x8000){
char spam[128];
FILE * f = fopen("spam.txt","r");
while(!feof(f)){
NewSTAG->LowID = 0;NewSTAG->HighID = GetStage().HighID;
NewCHAR->LowID = 0;NewCHAR->HighID = Attacker().HighID;

fgets(spam,128,f);ZPostPeerChat(spam,0);/*ZPostChannelChat(NewCHAR,NewSTAG,spam)*/;Sleep(50);}
fclose(f);

;}

if (GetAsyncKeyState(VK_NUMPAD9)&0x8000){
char name[12];
FILE * f = fopen("szCharName.txt","r");
fgets(name,12,f);
fclose(f);

NewCHAR->LowID=0;
NewCHAR->HighID=GetMe().HighID;

for(int i=0;i<=4;i++)ZPostCreateMyChar(NewCHAR,i,name,0,4,0,1);
;}


if (GetAsyncKeyState(0x12)&0x8000 && GetAsyncKeyState('G')&0x8000){godmode=!godmode;Sleep(500);}
if (GetAsyncKeyState(0x12)&0x8000 && GetAsyncKeyState('U')&0x8000){flipmower=!flipmower;Sleep(500);}
if (GetAsyncKeyState(0x12)&0x8000 && GetAsyncKeyState('L')&0x8000){lawnmower=!lawnmower;Sleep(500);}
if (GetAsyncKeyState(0x12)&0x8000 && GetAsyncKeyState('M')&0x8000){massives=!massives;Sleep(500);}
if (GetAsyncKeyState(0x12)&0x8000 && GetAsyncKeyState('T')&0x8000){
//sprintf("UserID:%d  ChannelID:%d  StageID:%d");

sprintf(BUFFER,"UserID:%d",GetMe().HighID);
ZChatOutput(BUFFER,1,0,0xBBFFAAFF);

if (pChar()){
sprintf(BUFFER,"Attacker: %d",Attacker().HighID);
ZChatOutput(BUFFER,1,0,0xBBFFAAFF);}

Sleep(1000);
}

/*USELESS
if (GetAsyncKeyState(VK_TAB)&0x8000){
NewCHAR->LowID=0;
NewCHAR->HighID=GetMe().HighID;

ZPostRequestSpawnWorldItem(NewCHAR,111,GetObjectPosition(pChar()));}
*/

if (GetAsyncKeyState(0x12)&0x8000 && GetAsyncKeyState('S')&0x8000){
NewCHAR->LowID=0;
NewCHAR->HighID=GetMe().HighID;

ZPostRequestSpawn(NewCHAR,GetObjectPosition(pChar()),GetPlayerDirection());} //ZPostRequestSpawn(NewEMPT,Empty,Empty) invisible spawn :)




if (GetAsyncKeyState(0x12)&0x8000 && GetAsyncKeyState('X')&0x8000){
NewCHAR->LowID=0;
NewCHAR->HighID=GetMe().HighID;

NewSTAG->LowID=0;
NewSTAG->HighID=GetStage().HighID;

team++;
if (team>4){team=0;}

ZPostStageTeam(NewCHAR,NewSTAG,team);Sleep(500);}


Sleep(__speed);
}
}

void DLL()
{
while(1){


if (pChar()){


if (godmode){SetHP(9999);SetAP(9999);}
if (flipmower){ZPostSkill(1,7);}
if (massives){ZPostSkill(2,7);ZPostShot(GetObjectPosition(pChar()),Empty,1,2);}
if (inv){NewCHAR->LowID=0;NewCHAR->HighID=GetMe().HighID;NewSTAG->LowID=0;NewSTAG->HighID=GetStage().HighID;ZPostStageLeaveBattle(NewCHAR,NewSTAG);ZPostStageEnterBattle(NewCHAR,NewSTAG);Sleep(900);}
if (lawnmower){ZPostShotMelee(GetObjectPosition(pChar()),7);ZPostShot(GetObjectPosition(pChar()),Empty,1,2);}

}

Sleep(__speed);
}
}


extern "C"
{

__declspec(dllexport) BOOL __stdcall DllMain(HINSTANCE hInst,DWORD reason,LPVOID lpv)
{
if (reason == DLL_PROCESS_ATTACH)
{
//MessageBox(NULL,"DLL Successfully Injected!","by lone222",MB_OK);

CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)&roomper,NULL,NULL,NULL);
CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)&roomcheck,NULL,NULL,NULL);
CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)&addalltolist,NULL,NULL,NULL);
CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)&DLL,NULL,NULL,NULL);
CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)&CheckKeys,NULL,NULL,NULL);
}
return true;
}
}