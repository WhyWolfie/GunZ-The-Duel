/**************************************************************
TheGunzKidz_Public.dll Source Code Reversed By GunZeR 7/17/2011
***************************************************************/
#include <windows.h>

DWORD g_dwEnterCriticalSection;

bool g_bLawnmower = false;
bool g_bDashmower = false;
bool g_bEgomower = false;
bool g_bDantasticMode = false;
bool g_bButterflyHack = false;
bool g_bAdvertiseSpam = false;

struct MUID
{
    unsigned long Low;
    unsigned long High;
};

float *GetPosition( DWORD ZCharacter )
{
    DWORD dwEcx = *(DWORD*)( ZCharacter + 0x4B0 );
    DWORD dwEdx = ZCharacter + 0x4B0;
    dwEcx -= dwEdx;
    return (float*)( dwEcx - 0x66D6 );
}

float *GetDirection( DWORD ZCharacter )
{
    return (float*)( ZCharacter + 0x4B8 );
}

DWORD ZGetGame( )
{
    DWORD dwEax = *(DWORD*)0x727FC8;
    dwEax ? dwEax = *(DWORD*)dwEax : dwEax = 0;
    dwEax ? dwEax = *(DWORD*)( dwEax + 0x2EC ) : dwEax = 0;

    return dwEax;
}

DWORD ZMyCharacter( )
{
    if( ZGetGame( ) )
        return *(DWORD*)( ZGetGame( ) + 0x58 );

    return 0;
}

DWORD ZGetCharacterManager( )
{
    return ZGetGame( ) + 0x68;
}

DWORD ZGetGameClient( )
{
    return *(DWORD*)0x722B34;
}

MUID *GetPlayer( )
{
    return (MUID*)( ZGetGameClient( ) + 0x198 );
}

MUID *GetAttacker( )
{
    DWORD dwEax = *(DWORD*)( ZMyCharacter( ) + 0x3A8 );
    return (MUID*)( dwEax + 0x2C );
}

MUID *GetStage( )
{
    return (MUID*)( ZGetGameClient( ) + 0x23C );
}

MUID *GetChannel( )
{
    return (MUID*)( ZGetGameClient( ) + 0x1D0 );
}

char *GetKickString( )
{
    return (char*)( ZGetGameClient( ) + 0x7ED );
}

void SetPosition( float X, float Y, float Z )
{
    GetPosition( ZMyCharacter( ) )[0] = X;
    GetPosition( ZMyCharacter( ) )[1] = Y;
    GetPosition( ZMyCharacter( ) )[2] = Z;
}

DWORD ZCharacterManager__Find( DWORD dwLow, DWORD dwHigh )
{
    DWORD ZCharacter = 0;

    __asm
    {
        call ZGetCharacterManager
        mov ecx, eax
        push dwHigh
        push dwLow
        push 0x5E0F67
        mov eax, 0x49FE40
        jmp eax
        mov ZCharacter, eax
    }

    return ZCharacter;
}

DWORD UIDS[16];

void RefreshCharacters( )
{
    memset( UIDS, 0, sizeof( DWORD ) * 15 );

    DWORD Local8 = **(DWORD**)( ZGetGameClient( ) + 0x51C );
    int Local10 = 0;

    for( ; Local8 != *(DWORD*)( ZGetGameClient( ) + 0x51C ), Local10 != 16; Local10++ )
    {
        DWORD dwEax = *(DWORD*)( Local8 + 0x14 );
        DWORD dwEdx = *(DWORD*)( dwEax + 0x8 );

        UIDS[Local10] = dwEdx;

        ( ( void( __thiscall * )( DWORD * ) )0x478A40 )( &Local8 );
    }
}

void SetHP( DWORD ZModuleHPAP, float fHP )
{
    DWORD Local8 = ZModuleHPAP + 0x18;
    DWORD Local4 = *(DWORD*)( ZModuleHPAP + 0x18 );
    ZModuleHPAP += 0x8;
    Local4 -= Local8;
    Local8 = *(DWORD*)ZModuleHPAP;
    *(float*)( Local4 - 0x66D6 ) = fHP + 999.9f;
    Local8 -= ZModuleHPAP;
    *(float*)( Local8 - 0x66D6 ) = 999.9f;
}

void SetAP( DWORD ZModuleHPAP, float fAP )
{
    DWORD Local8 = ZModuleHPAP + 0x24;
    DWORD Local4 = *(DWORD*)( ZModuleHPAP + 0x24 );
    ZModuleHPAP += 0x8;
    Local4 -= Local8;
    Local8 = *(DWORD*)ZModuleHPAP;
    *(float*)( Local4 - 0x66D6 ) = fAP + 999.9f;
    Local8 -= ZModuleHPAP;
    *(float*)( Local8 - 0x66D6 ) = 999.9f;
}

void GodMode( )
{
    SetHP( *(DWORD*)( ZMyCharacter( ) + 0x52C ), 999.9f );
    SetAP( *(DWORD*)( ZMyCharacter( ) + 0x52C ), 999.9f );
}

void BonusHealth( )
{
    __asm
    {
        call ZMyCharacter
        add eax, 4
        sub eax, 5
        add eax, 1
        push eax
        add eax, 6
        sub eax, 8
        add eax, 2
        push 0x5E0F67
        mov eax, 0x4EAAA0
        jmp eax
    }
}

void SetAnimationUpper( int iAnimation )
{
    __asm
    {
        call ZMyCharacter
        mov ecx, eax
        add eax, 5
        sub eax, 5
        add eax, 0xA
        sub eax, 0xA
        mov eax, 0x49DE40
        push iAnimation
        call eax
    }
}

void SetAnimationLower( int iAnimation )
{
    __asm
    {
        call ZMyCharacter
        mov ecx, eax
        add eax, 5
        sub eax, 5
        add eax, 0xA
        sub eax, 0xA
        mov eax, 0x49DD70
        push iAnimation
        call eax
    }
}

void ZCharacter__WallJump2( )
{
    __asm
    {
        push label
        call ZMyCharacter
        mov ecx, eax
        add eax, 5
        sub eax, 5
        add eax, 0xA
        sub eax, 0xA
        push 0x5E0F67
        mov eax, 0x4A6FC0
        jmp eax
        label:
    }
}

void ZPostPeerChat( char *szMsg )
{
    __asm
    {
        push label
        add eax, 5
        sub eax, 5
        add eax, 0xA
        sub eax, 0xA
        push 0
        push szMsg
        push 0x5E0F67
        mov eax, 0x432650
        jmp eax
        label:
    }
}

void ZChatOutput( char *szMsg )
{
    __asm
    {
        push label
        add eax, 5
        sub eax, 5
        add eax, 0xA
        sub eax, 0xA
        push szMsg
        push 0x5E0F67
        mov eax, 0x432C00
        jmp eax
        label:
    }
}

class MCommandParameter
{
public:
    void *operator new( unsigned int nSize )
    {
        return ( ( void*( * )( unsigned int ) )0x67F427 )( nSize );
    }

    void *VTable;
    int m_nType;
    void *pData;
};

class MCommand
{
public:
    void AddParameter( MCommandParameter *pCmdParam )
    {
        ( ( void( __thiscall * )( void *, MCommandParameter * ) )0x54CED0 )( this, pCmdParam );
    }

    void *VTable;
    MCommand *next;
    MUID m_Sender;
    MUID m_Receiver;
};

class MCommandParameterInt : public MCommandParameter
{
public:
    int m_Value;

    MCommandParameterInt( int nParam )
    {
        ( ( void( __thiscall * )( void *, int ) )0x549D50 )( this, nParam );
    }
};

class MCommandParameterVector_1 : public MCommandParameter
{
public:
    float X, Y, Z;

    MCommandParameterVector_1( float X, float Y, float Z )
    {
        ( ( void( __thiscall * )( void *, float, float, float ) )0x497530 )( this, X, Y, Z );
    }
};

class MCommandParameterVector_3 : public MCommandParameter
{
public:
    float X, Y, Z;

    MCommandParameterVector_3( float X, float Y, float Z )
    {
        ( ( void( __thiscall * )( void *, float, float, float ) )0x4E8990 )( this, X, Y, Z );
    }
};

class MCommandParameterUID : public MCommandParameter
{
public:
    MUID mValue;

    MCommandParameterUID( MUID *mParam )
    {
        ( ( void( __thiscall * )( void *, MUID * ) )0x54A850 )( this, mParam );
    }
};

class MCommandParameterBlob : public MCommandParameter
{
public:
    void *m_Value;

    MCommandParameterBlob( void *pParam, int nSize )
    {
        ( ( void( __thiscall * )( void *, void *, int ) )0x54AA90 )( this, pParam, nSize );
    }
};

void __declspec(naked) WINAPI ZPostCommand( MCommand *pCmd )
{
    __asm
    {
        mov ecx, dword ptr ss:[esp]
        mov eax, dword ptr ds:[esp+4]
        mov dword ptr ds:[esp+4], ecx
        mov dword ptr ss:[esp], eax
        push 0x402EBA
        mov eax, 0x501820
        jmp eax
    }
}

MCommand *ZNewCmd( int iCmd )
{
    return ( ( MCommand*( * )( int ) )0x501590 )( iCmd );
}

struct ZPACKEDSHOTINFO
{
    float fShotTime;
    short posx;
    short poxy;
    short posz;
    short dirx;
    short diry;
    short dirz;
    int sel_type;
};

float fShotTime;

void ZPostShot( float *Position, float *Direction, int iSel )
{
    MCommand *pCommand = ZNewCmd( 0x2732 );
    ZPACKEDSHOTINFO ShotInfo = { fShotTime++,
                                 Position[0], Position[1], Position[2],
                                 Direction[0], Direction[1], Direction[2],
                                 iSel };
    pCommand->AddParameter( new MCommandParameterBlob( &ShotInfo, 20 ) );
    ZPostCommand( pCommand );
}

struct ZDashInfo
{
    float fShotTime;
    short posx;
    short poxy;
    short posz;
    short dirx;
    short diry;
    short dirz;
    char sel_type;
    short dash_unknown;
    char dash_unknown2;
};

void ZPostDash( float *vPos, float *vDir, char sel_type )
{
    MCommand *pCommand = ZNewCmd( 0x273D );
    ZDashInfo DashInfo = { fShotTime++,
                                 vPos[0], vPos[1], vPos[2],
                                 vDir[0], vDir[1], vDir[2],
                                 sel_type, 0, 0 };
    pCommand->AddParameter( new MCommandParameterBlob( &DashInfo, 20 ) );
    ZPostCommand( pCommand );
}

void ZPostSpMotion( int SelType )
{
    MCommand *pCommand = ZNewCmd( 0x273E );
    pCommand->AddParameter( new MCommandParameterInt( SelType ) );
    ZPostCommand( pCommand );
}

void ZPostSpawn( MUID *uidPlayer, float *Position, float *Direction )
{
    MCommand *pCommand = ZNewCmd( 0x273A );
    pCommand->AddParameter( new MCommandParameterUID( uidPlayer ) );
    pCommand->AddParameter( new MCommandParameterVector_1( Position[0], Position[1], Position[2] ) );
    pCommand->AddParameter( new MCommandParameterVector_3( Direction[0], Direction[1], Direction[2] ) );
    ZPostCommand( pCommand );
}

__declspec(naked) void EnterCriticalSectionHook( )
{
    __asm
    {
        cmp dword ptr ss:[esp], 0x4CF39F
        jnz retorig
        cmp dword ptr ss:[ebp+4], 0x501613
        jnz retorig
        mov eax, dword ptr ss:[ebp]
        cmp dword ptr ds:[eax+8], 0x238D
        jnz retorig
        mov esp, eax
        pop ebp
        add dword ptr ss:[esp], 9
        ret 4
        retorig:
        jmp g_dwEnterCriticalSection
    }
}

DWORD WINAPI HotKeyThread( LPVOID )
{
    while( 1 )
    {
        if( GetAsyncKeyState( VK_MENU )&0x8000 )
        {
            if( GetAsyncKeyState( 'L' )&0x8000 )
            {
                g_bLawnmower = !g_bLawnmower;
                Beep( 500, 500 );
            }

            else if( GetAsyncKeyState( 'X' )&0x8000 )
            {
                g_bDashmower = !g_bDashmower;
                Beep( 500, 500 );
            }

            else if( GetAsyncKeyState( 'E' )&0x8000 )
            {
                g_bEgomower = !g_bEgomower;
                Beep( 500, 500 );
            }

            else if( GetAsyncKeyState( 'D' )&0x8000 )
            {
                g_bDantasticMode = !g_bDantasticMode;
                Beep( 500, 500 );
            }

            else if( GetAsyncKeyState( 'B' )&0x8000 )
            {
                g_bButterflyHack = !g_bButterflyHack;
                Beep( 500, 500 );
            }

            else if( GetAsyncKeyState( 'A' )&0x8000 )
            {
                g_bAdvertiseSpam = !g_bAdvertiseSpam;
                Beep( 500, 500 );
            }
        }

        Sleep( 10 );
    }
}

DWORD WINAPI ExecuteThread( LPVOID )
{
    while( 1 )
    {
        if( ZMyCharacter( ) )
        {
            if( g_bLawnmower )
            {
                ZPostShot( GetPosition( ZMyCharacter( ) ), GetDirection( ZMyCharacter( ) ), 7 );
                ZPostShot( GetPosition( ZMyCharacter( ) ), GetDirection( ZMyCharacter( ) ), 1 );
            }

            if( g_bDashmower )
            {
                ZPostDash( GetPosition( ZMyCharacter( ) ), GetDirection( ZMyCharacter( ) ), 1 );
                ZPostDash( GetPosition( ZMyCharacter( ) ), GetDirection( ZMyCharacter( ) ), 7 );
            }

            if( g_bEgomower )
            {
                ZPostSpMotion( 3 );
            }

            if( g_bDantasticMode )
            {
                if( GetAsyncKeyState( VK_LBUTTON )&0x8000 )
                {
                    ZPostSpawn( GetPlayer( ), GetPosition( ZMyCharacter( ) ), GetDirection( ZMyCharacter( ) ) );
                    ZPostShot( GetPosition( ZMyCharacter( ) ), GetDirection( ZMyCharacter( ) ), 7 );
                    ZPostShot( GetPosition( ZMyCharacter( ) ), GetDirection( ZMyCharacter( ) ), 1 );
                    Sleep( 50 );
                }
            }

            if( g_bButterflyHack )
            {
                if( GetAsyncKeyState( VK_SHIFT )&0x8000 )
                {
                    ZPostShot( GetPosition( ZMyCharacter( ) ), GetDirection( ZMyCharacter( ) ), 7 );
                    SetAnimationUpper( 6 );
                    ZPostShot( GetPosition( ZMyCharacter( ) ), GetDirection( ZMyCharacter( ) ), 1 );
                    Sleep( 125 );
                }
            }

            if( g_bAdvertiseSpam )
            {
                ZPostPeerChat( "^2FREE GUNZ HACKS: www.thegunzkidz.com." );
                ZPostPeerChat( "^2FREE GUNZ HACKS: www.thegunzkidz.com." );
                ZPostPeerChat( "^2FREE GUNZ HACKS: www.thegunzkidz.com." );
            }

            Sleep( 10 );
        }
    }
}

BOOL WINAPI DllMain( HINSTANCE hInst, DWORD dwReason, LPVOID )
{
    if( dwReason == DLL_PROCESS_ATTACH )
    {
        *(DWORD*)0x2100E70 = 0x401013;
        g_dwEnterCriticalSection = *(DWORD*)0x69C2B8;
        *(DWORD*)0x69C2B8 = (DWORD)EnterCriticalSectionHook;
        CreateThread( 0, 0, HotKeyThread, 0, 0, 0 );
        CreateThread( 0, 0, ExecuteThread, 0, 0, 0 );
        ShellExecuteA( 0, "open", "http://www.thegunzkidz.com/", 0, 0, SW_SHOWNORMAL );
        Beep( 500, 500 );
    }

    return TRUE;
}