#include <cmath>
#include <ctime>
#include <cstdio>
#include <windows.h>

#include "d3d9.h"
#include "d3dfont.h"
#include "detours.h"
#include "SIRC.h"
#include "freebase.h"
#include "stristr.cpp"

bool HookedTerminateProcess(void *process, unsigned int code)
{
	if(!exitStatus)
		ExitFreebase();

	return OriginalTerminateProcess(process, code);
}

char *GetCharName(unsigned long zcharacter)
{
	return (char *)(zcharacter + 0x348);
}

char *GetClanName(unsigned long zcharacter)
{
	return (char *)(zcharacter + 0x368);
}

char *MyChannelName()
{
	return (char *)(ZGetGameClient() + 0x500);
}

char *MyLastInput()
{
	return (char *)(ZGetGameInterface() + 0x3A8);
}

char *MyMapName()
{
	return (char *)(ZGetGameClient() + 0xCE0);
}

char *MyServerName()
{
	return (char *)(ZGetGameClient() + 0x1B8);
}

char *MyStageName()
{
	return (char *)(ZGetGameClient() + 0x680);
}

char *WhosBeingKicked()
{
	return (char *)(ZGetGameClient() + 0x7E5);
}

float *GetDirection(unsigned long zcharacter)
{
	return (float *)(zcharacter + 0x5C);
}

float *GetPosition(unsigned long zcharacter)
{
	float *position;

	_asm
	{
		mov ecx, zcharacter
		mov eax, dword ptr ds:[ecx + 0x58]
		mov ecx, dword ptr ds:[eax + 0x20]
		mov edx, dword ptr ds:[eax + 0xC]
		mov eax, dword ptr ds:[edx + ecx * 0x4]
		mov position, eax
	}
 
	return position;
}

float HookedGetGravityConst()
{
	return gravity;
}

// v by Harold
HRESULT GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if( FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)) )
		return E_FAIL;
	
	WORD colour16 =	((WORD)((colour32>>28)&0xF)<<12)
			|(WORD)(((colour32>>20)&0xF)<<8)
			|(WORD)(((colour32>>12)&0xF)<<4)
			|(WORD)(((colour32>>4)&0xF)<<0);

	D3DLOCKED_RECT d3dlr;    
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;

	for(int xy=0; xy < 8*8; xy++)
		*pDst16++ = colour16;

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}
// ^ by Harold

int GetAP(unsigned long zcharacter)
{
	_asm
	{
		mov ecx, zcharacter
		mov eax, ZCHARACTER_GETAP
		call eax
		mov zcharacter, eax
	}

	return (int)zcharacter;
}

int GetHP(unsigned long zcharacter)
{
	_asm
	{
		mov ecx, zcharacter
		mov eax, ZCHARACTER_GETHP
		call eax
		mov zcharacter, eax
	}

	return (int)zcharacter;
}

long HookedDrawIndexedPrimitive(IDirect3DDevice9 *device, D3DPRIMITIVETYPE type, int baseVertexIndex, unsigned int minVertexIndex, unsigned int numVertices, unsigned int startIndex, unsigned int primCount)
{
	if(!exitStatus)
	{
		if(chams && ((stride == 52) || (stride == 32)) && !exitStatus)
		{
			device->SetRenderState(D3DRS_ZENABLE, false);
			device->SetTexture(0, textures[COLOR_YELLOW]);
			device->DrawIndexedPrimitive(type, baseVertexIndex, minVertexIndex, numVertices, startIndex, primCount);
			device->SetRenderState(D3DRS_ZENABLE, true);
			device->SetTexture(0, textures[COLOR_GREEN]);
		}
	}

	return device->DrawIndexedPrimitive(type, baseVertexIndex, minVertexIndex, numVertices, startIndex, primCount);
}

long HookedEndScene(IDirect3DDevice9 *device)
{
	if(!exitStatus && hooked)
	{
		GetWindowRect(GetActiveWindow(), &rect);

		SetRect(&rect, 5, (rect.bottom - rect.top) - 16, 10000, 10000);

		font->DrawTextW((float)rect.left, (float)rect.top, 0xFFFFFFFF, info2, 0);
		
		if(!hideConsole && MyZCharacter())
		{
			GetWindowRect(GetActiveWindow(), &rect);

			SetRect(&rect, 20, (rect.bottom - rect.top) - 150, 10000, 10000);

			for(r = consolePosition; r < (consolePosition + 8); r++)
			{
				font->DrawTextW((float)rect.left, (float)rect.top, 0xFFFFFFFF, consoleText[r], 0);

				SetRect(&rect, 20, rect.top - 14, 10000, 10000);
			}
		}
	}

	return device->EndScene();
}

long HookedInitialize(IDirect3DDevice9 *device)
{
	if(!exitStatus)
	{
		hooked = true;

		for(r = 0; r < 120; r++)
			consoleText[r] = new wchar_t[1024 * 64];

		font = new CD3DFont(L"Arial", 9, 0);
		font->InitDeviceObjects(device);
		font->RestoreDeviceObjects();

		GenerateTexture(device, &textures[COLOR_ORANGE], D3DCOLOR_ARGB(255, 255, 140, 0));
		GenerateTexture(device, &textures[COLOR_RED], D3DCOLOR_ARGB(255, 255, 0, 0));
		GenerateTexture(device, &textures[COLOR_GREEN], D3DCOLOR_ARGB(255, 0, 255, 0));
		GenerateTexture(device, &textures[COLOR_WHITE], D3DCOLOR_ARGB(255, 255, 255, 255));
		GenerateTexture(device, &textures[COLOR_BLUE], D3DCOLOR_ARGB(255, 0, 0, 255));
		GenerateTexture(device, &textures[COLOR_YELLOW], D3DCOLOR_ARGB(255, 255, 255, 0));
		GenerateTexture(device, &textures[COLOR_PINK], D3DCOLOR_ARGB(255, 255, 192, 203));
		GenerateTexture(device, &textures[COLOR_BLACK], D3DCOLOR_ARGB(255, 0, 0, 0));
		GenerateTexture(device, &textures[COLOR_PURPLE], D3DCOLOR_ARGB(255, 160, 32, 240));
	}

	return S_OK;
}

long HookedSetRenderState(IDirect3DDevice9 *device, D3DRENDERSTATETYPE state, unsigned long value)
{
	if(!exitStatus)
	{
		if(noFog && (stride == 28) && !exitStatus)
		{
			if(wireframe)
				device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

			else if(!xray)
				device->SetRenderState(D3DRS_ZENABLE, true);

			return device->SetRenderState(D3DRS_FOGENABLE, false);
		}
		else if(wireframe && ((stride == 52) || (stride == 28) || (stride == 32)) && !exitStatus)
			return device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

		else if(xray && (stride == 28) && !exitStatus)
			return device->SetRenderState(D3DRS_ZENABLE, false);
	}

	return device->SetRenderState(state, value);
}

long HookedSetStreamSource(IDirect3DDevice9 *device, unsigned int stream, IDirect3DVertexBuffer9 *buf, unsigned int offset, unsigned int currentStride)
{
	if(!exitStatus)
	{
		if(!stream)
			stride = currentStride;
	}

	return device->SetStreamSource(stream, buf, offset, currentStride);
}

long HookedSetTexture(IDirect3DDevice9 *device, unsigned long stage, IDirect3DBaseTexture9 *texture)
{
	if(!exitStatus)
	{
		if(!exitStatus && coloredTextures && ((stride == 52) || (stride == 28) || (stride == 32)))
			return device->SetTexture(stage, textures[color]);
	}

	return device->SetTexture(stage, texture);
}

unsigned long GetLastAttackerId(unsigned long zcharacter)
{
	return *(unsigned long *)(*(unsigned long *)(zcharacter + 0x32C) + 0x20);
}

unsigned long GetZCharacter(unsigned long id)
{
	_asm
	{
		mov eax, ZGETCHARACTERMANAGER
		call eax
		mov ecx, eax
		push id
		push 0
		mov eax, ZCHARACTERMANAGER_FIND
		call eax
		mov id, eax
	}

	return id;
}

unsigned long MyChannelId()
{
	return  *(unsigned long *)(ZGetGameClient() + 0x1AC);
}

unsigned long MyZCharacter()
{
	if(ZGetGame())
		return *(unsigned long *)(ZGetGame() + 0x50);

	return 0;
}

unsigned long MyId()
{
	return *(unsigned long *)(ZGetGameClient() + 0x1A4);
}

unsigned long MyStageId()
{
	return *(unsigned long *)(ZGetGameClient() + 0x1B4);
}

void Aimbot()
{
	float aim[3];
	float attackerPosition[3];
	float distance = 0.0f;
	float position[3];

	unsigned long id = 0;

	while(!exitStatus)
	{
		if(!aimbot)
			break;

		if(MyZCharacter())
		{
			id = GetLastAttackerId(MyZCharacter());

			if(GetZCharacter(id) && id && (id != MyId()))
			{
				memcpy(attackerPosition, GetPosition(GetZCharacter(id)), sizeof(attackerPosition));   
				memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

				if((position[1] - attackerPosition[1]) > 0.0f)
					attackerPosition[0] -= 30;

				if((position[1] - attackerPosition[1]) <= 0.0f)
					attackerPosition[0] += 30;

				attackerPosition[2] -= 120;

				distance = sqrt(pow((attackerPosition[0] - position[0]), 2.0f) + pow((attackerPosition[1] - position[1]), 2.0f) + pow((attackerPosition[2] - position[2]), 2.0f));

				aim[0] = (attackerPosition[0] - position[0]) / distance;
				aim[1] = (attackerPosition[1] - position[1]) / distance;
				aim[2] = (attackerPosition[2] - position[2]) / distance;

				SetDirection(aim, MyZCharacter());
			}
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Aimbot was turned off");

			aimbot = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void Anchor()
{
	float position[3];

	if(MyZCharacter())
		memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

	while(!exitStatus)
	{
		if(!anchor)
			break;

		if(MyZCharacter())
			SetPosition(position);

		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Anchor was turned off");

			anchor = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void Antikick()
{
	bool justJoined = true;

	MUID me;
	MUID myStage;

	me.id = 0;
	me.zero = 0;

	myStage.id = 0;
	myStage.zero = 0;

	Sleep(30000);

	while(!MyChannelId())
		Sleep(10);

	while(!exitStatus)
	{
		if(MyZCharacter())
		{
			if(!antiKick)
			{
				if(justJoined)
				{
					Sleep(5000);

					justJoined = false;
				}

				if(stristr(WhosBeingKicked(), GetCharName(MyZCharacter())) && (stristr(WhosBeingKicked(), GetCharName(MyZCharacter())) == WhosBeingKicked()))
				{
					me.id = MyId();

					myStage.id = MyStageId();

					ZPostStageLeaveBattle(&me, &myStage);
					ZPostStageEnterBattle(&me, &myStage);

					ConsoleOutput("Anti-kick: Someone tried to kick you");

					strcpy(WhosBeingKicked(), "");
				}
			}
		}
		else
			justJoined = true;

		Sleep(dllSpeed);
	}
}

void Bot()
{
	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!bot)
			break;

		if(MyZCharacter())
		{
			peer.id = GetLastAttackerId(MyZCharacter());

			if(GetZCharacter(peer.id) && peer.id && (peer.id != MyId()))
				ZPostRequestExpelClanMember(&peer, "/*)_#$^Freebase&(+*/!@");
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, the last attacker Bot was turned off");

			bot = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void BotRoom()
{
	int i = 0;

	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!botRoom)
			break;

		if(MyZCharacter())
		{
			for(i = 0; i < totalPeers; i++)
			{
				if(MyZCharacter())
				{
					if(GetZCharacter(peers[i].id) && peers[i].id && (peers[i].id != MyId()))
					{
						peer.id = peers[i].id;

						ZPostRequestExpelClanMember(&peer, "/*)_#$^Freebase&(+*/!@");

						Sleep(dllSpeed);
					}
				}
			}
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, the room-wide bot was turned off");

			botRoom = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void BubbleAura()
{
	while(!exitStatus)
	{
		if(!bubbleAura)
			break;

		if(MyZCharacter())
			ZPostPeerChatIcon(1);

		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Bubble Aura was turned off");

			bubbleAura = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void CircleFastestVortex()
{
	float direction[3];

	if(MyZCharacter())
		memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));

	while(!exitStatus)
	{
		if(!circleFastestVortex)
			break;

		if(MyZCharacter())
		{
			direction[0] += 0.1f;
			direction[1] += 0.1f;
			direction[2] += 0.1f;

			ZPostDash(GetPosition(MyZCharacter()), direction, 1);
			ZPostDash(GetPosition(MyZCharacter()), direction, 7);
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Circle Vortex (Fastest) was turned off");

			circleFastestVortex = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void CircleMediumVortex()
{
	float direction[3];

	if(MyZCharacter())
		memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));

	while(!exitStatus)
	{
		if(!circleMediumVortex)
			break;

		if(MyZCharacter())
		{
			direction[0] += 0.05f;
			direction[1] += 0.05f;
			direction[2] += 0.05f;

			ZPostDash(GetPosition(MyZCharacter()), direction, 1);
			ZPostDash(GetPosition(MyZCharacter()), direction, 7);
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Circle Vortex (Medium) was turned off");

			circleMediumVortex = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void CircleSlowestVortex()
{
	float direction[3];

	if(MyZCharacter())
		memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));

	while(!exitStatus)
	{
		if(!circleSlowestVortex)
			break;

		if(MyZCharacter())
		{
			direction[0] += 0.01f;
			direction[1] += 0.01f;
			direction[2] += 0.01f;

			ZPostDash(GetPosition(MyZCharacter()), direction, 1);
			ZPostDash(GetPosition(MyZCharacter()), direction, 7);
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Circle Vortex (Slowest) was turned off");

			circleSlowestVortex = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void CollectIds()
{
	bool present = false;

	char *buft = new char[1024 * 64];

	int i = 0;

	MUID channel;
	MUID peer;
	MUID stage;

	unsigned long currentId = 0;

	channel.id = 0;
	channel.zero = 0;

	peer.id = 0;
	peer.zero = 0;

	stage.id = 0;
	stage.zero = 0;

	Sleep(30000);

	while(!MyChannelId())
		Sleep(10);

	while(!exitStatus)
	{
		if(botRoom || medicateRoom || medicineHatRoom || petMode || roomRape)
		{
			for(currentId = 0; currentId < 1500000; currentId++)
			{
				if(MyZCharacter())
				{
					peer.id = currentId;

					if(GetZCharacter(peer.id) && peer.id && (peer.id != MyId()))
					{
						for(i = 0; i < totalPeers; i++)
						{
							if(peers[i].id == peer.id)
								present = true;
						}

						if(!present)
						{
							totalPeers++;

							peers[totalPeers].id = peer.id;
						}

						present = false;

						Sleep(100);
					}
				}
				else
					break;
			}

			Sleep(dllSpeed + 100);
		}

		Sleep(1000);
	}

	delete buft;
}

void ConsoleOutput(char *message)
{
	if(hooked)
	{
		int i = 119;

		while(true)
		{
			memset(consoleText[i], 0, 1024 * 64);

			_snwprintf(consoleText[i], (1024 * 64) - 1, consoleText[i - 1]);

			if(i == 1)
				break;

			else
				i--;
		}

		memset(consoleText[0], 0, 1024 * 64);

		wmemset(message2, 0, 1024 * 64);

		mbstowcs(message2, message, (1024 * 64) - 1);

		_snwprintf(consoleText[0], (1024 * 64) - 1, message2);
	}
}

void DashVortex()
{
	float direction[3];

	while(!exitStatus)
	{
		if(!dashVortex)
			break;

		if(MyZCharacter())
		{
			memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));

			ZPostDash(GetPosition(MyZCharacter()), direction, 1);
			ZPostDash(GetPosition(MyZCharacter()), direction, 7);
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Dash Vortex was turned off");

			dashVortex = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

// v by Azorbix
void *DetourFunc(BYTE *src, const BYTE *dst, const int len)
{
	BYTE *jmp = (BYTE*)malloc(len+5);
	DWORD dwback;

	VirtualProtect(src, len, PAGE_READWRITE, &dwback);

	memcpy(jmp, src, len);	jmp += len;
	
	jmp[0] = 0xE9;
	*(DWORD*)(jmp+1) = (DWORD)(src+len - jmp) - 5;

	src[0] = 0xE9;
	*(DWORD*)(src+1) = (DWORD)(dst - src) - 5;

	VirtualProtect(src, len, dwback, &dwback);

	return (jmp-len);
}
// ^ by Azorbix

void ExitFreebase()
{
	ConsoleOutput("Exited Freebase");

	exitStatus = true;

	if(hooked)
	{
		for(int i = COLOR_ORANGE; i < COLOR_PURPLE; i++)
			textures[i]->Release();

		font->InvalidateDeviceObjects();
		font->DeleteDeviceObjects();
		font = 0;
	}

	DetourRemove((unsigned char *)GetGravityConst, (unsigned char *)HookedGetGravityConst);
	DetourRemove((unsigned char *)ZPostChatRoomChat, (unsigned char *)HookedZPostChatRoomChat);

	irc->Quit("Freebase");

	Sleep(2000);

	irc->~SIRC();

	delete[] *consoleText;
	delete font;
	delete irc;
	delete ircNick;
	delete message2;
	delete[] *textures;
}

void Flame()
{
	while(!exitStatus)
	{
		if(!flame)
			break;

		if(MyZCharacter())
			ZPostReaction(GetPosition(MyZCharacter()), 2);

		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Flame was turned off");

			flame = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void FlashbangSpam()
{
	float empty[3];
	float position[3];

	while(!exitStatus)
	{
		if(!flashbangSpam)
			break;

		if(MyZCharacter())
		{
			memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

			position[2] += 120;

			ZPostShotSp(position, GetDirection(MyZCharacter()), 3, 10);
			ZPostShot(empty, empty, 1, 2);

			Sleep(dllSpeed + 100);

			ZPostRequestSpawn(0, MyId(), GetPosition(MyZCharacter()), GetDirection(MyZCharacter()));
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Flashbang Spam was turned off");

			flashbangSpam = false;

			Sleep(1000);
		}
	}
}

void Flipmower()
{
	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!flipmower)
			break;

		if(MyZCharacter())
		{
			if(lastAttacker)
			{
				peer.id = GetLastAttackerId(MyZCharacter());

				if(GetZCharacter(peer.id) && peer.id && (peer.id != MyId()))
					SetPosition(GetPosition(GetZCharacter(peer.id)));
			}

			ZPostSkill(1, 7);
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Flipmower was turned off");

			flipmower = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void FragmentationGrenadeSpam()
{
	float empty[3];
	float position[3];

	while(!exitStatus)
	{
		if(!fragmentationGrenadeSpam)
			break;

		if(MyZCharacter())
		{
			memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

			position[2] += 120;

			ZPostShotSp(position, GetDirection(MyZCharacter()), 1, 10);
			ZPostShot(empty, empty, 1, 2);

			Sleep(dllSpeed + 100);

			ZPostRequestSpawn(0, MyId(), GetPosition(MyZCharacter()), GetDirection(MyZCharacter()));
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Fragmentation Grenade Spam was turned off");

			fragmentationGrenadeSpam = false;

			Sleep(1000);
		}
	}
}

void Godmode()
{
	while(!exitStatus)
	{
		if(!godmode)
			break;

		if(MyZCharacter())
		{
			SetHP(999, MyZCharacter());
			SetAP(999, MyZCharacter());
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Godmode was turned off");

			godmode = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

// v by UnnamedOne
void HideModule(HINSTANCE hModule)
{
   DWORD dwPEB_LDR_DATA = 0;
   _asm {
      pushad;
      pushfd;
      mov eax, fs:[30h]
         mov eax, [eax+0Ch]
         mov dwPEB_LDR_DATA, eax


      mov esi, [eax+0Ch]
         mov edx, [eax+10h]

LoopInLoadOrderModuleList:
      lodsd
         mov esi, eax
         mov ecx, [eax+18h]
         cmp ecx, hModule
         jne SkipA
         mov ebx, [eax]
         mov ecx, [eax+4]
         mov [ecx], ebx
         mov [ebx+4], ecx
         jmp InMemoryOrderModuleList

SkipA:
      cmp edx, esi
         jne LoopInLoadOrderModuleList

InMemoryOrderModuleList:
      mov eax, dwPEB_LDR_DATA
         mov esi, [eax+14h]
         mov edx, [eax+18h]

LoopInMemoryOrderModuleList:
      lodsd
         mov esi, eax
         mov ecx, [eax+10h]
         cmp ecx, hModule
         jne SkipB
         mov ebx, [eax]
         mov ecx, [eax+4]
         mov [ecx], ebx
         mov [ebx+4], ecx
         jmp InInitializationOrderModuleList

SkipB:
      cmp edx, esi
         jne LoopInMemoryOrderModuleList

InInitializationOrderModuleList:
      mov eax, dwPEB_LDR_DATA
         mov esi, [eax+1Ch]
         mov edx, [eax+20h]

LoopInInitializationOrderModuleList:
      lodsd
         mov esi, eax
         mov ecx, [eax+08h]
         cmp ecx, hModule
         jne SkipC
         mov ebx, [eax]
         mov ecx, [eax+4]
         mov [ecx], ebx
         mov [ebx+4], ecx
         jmp Finished

SkipC:
      cmp edx, esi
         jne LoopInInitializationOrderModuleList

Finished:
      popfd;
      popad;
   }
}
// ^ by UnnamedOne

void HookedExitProcess(unsigned int code)
{
	if(!exitStatus)
		ExitFreebase();

	OriginalExitProcess(code);
}

void HookedZPostChatRoomChat(char *chatRoom)
{
	char *buf = new char[1024 * 64];
	char *input = MyLastInput();
	char *input2= new char[1024 * 64];
	char *name = new char[1024];

	MUID me;
	MUID myChannel;

	me.id = 0;
	me.zero = 0;

	myChannel.id = 0;
	myChannel.zero = 0;

	if(input[0] == '@')
	{
		input++;

		if(input[0] == '&')
		{
			if(strlen(input) > 1)
			{
				input += strlen("&");

				_snprintf(buf, (1024 * 64) - 1, "PRIVMSG #freebase :%s\r\n", input);

				irc->Send(buf);

				memset(buf, 0, 1024 * 64);

				_snprintf(buf, (1024 * 64) - 1, "[IRC] <%s> %s", ircNick, input);

				ConsoleOutput(buf);

				memset(buf, 0, 1024 * 64);
			}
			else
				ConsoleOutput("Usage: @&message");
		}
		else if(stristr(input, "/fadd") == input)
		{
			if(strlen(input) > (strlen("/fadd") + 1))
			{
				input += strlen("/fadd");

				if(input[0] == ' ')
				{
					input++;

					ZPostFriendAdd(input);
				}
				else
					ConsoleOutput("Usage: @/fadd name");
			}
			else
				ConsoleOutput("Usage: @/fadd name");
		}
		else if(stristr(input, "/fcreate") == input)
		{
			if(strlen(input) > (strlen("/fcreate") + 1))
			{
				input += strlen("/fcreate");

				if(input[0] == ' ')
				{
					input++;

					me.id = MyId();

					for(int i = 0; i < 5; i++)
						ZPostCreateMyChar(&me, i, input, 1, 4, 0, 1);
				}
				else
					ConsoleOutput("Usage: @/fcreate name");
			}
			else
				ConsoleOutput("Usage: @/fcreate name");
		}
		else if(stristr(input, "/fremove") == input)
		{
			if(strlen(input) > (strlen("/fremove") + 1))
			{
				input += strlen("/fremove");

				if(input[0] == ' ')
				{
					input++;

					ZPostFriendRemove(input);
				}
				else
					ConsoleOutput("Usage: @/remove name");
			}
			else
				ConsoleOutput("Usage: @/fremove name");
		}
		else if(stristr(input, "/global") == input)
		{
			if(strlen(input) > (strlen("/global") + 1))
			{
				input += strlen("/global");

				if(input[0] == ' ')
				{
					input++;

					me.id = MyId();

					for(int i = 0; i < 20; i++)
					{
						myChannel.id = i;

						ZPostChannelChat(&me, &myChannel, input);
					}
				}
				else
					ConsoleOutput("Usage: @/global message");
			}
			else
				ConsoleOutput("Usage: @/global message");
		}
		else if(stristr(input, "/gset") == input)
		{
			if(strlen(input) > (strlen("/gset") + 1))
			{
				input += strlen("/gset");

				if(input[0] == ' ')
				{
					input++;

					_snprintf(buf, (1024 * 64) - 1, "Gravity set to: %.1f", (float)atof(input));

					ConsoleOutput(buf);

					memset(buf, 0, 1024 * 64);

					gravity = (float)atof(input);
				}
				else
					ConsoleOutput("Usage: @/gset gravity");
			}
			else
				ConsoleOutput("Usage: @/gset gravity");
		}
		else if(stristr(input, "/greset") == input)
		{
			ConsoleOutput("Gravity set to: 1.0");

			gravity = 1.0f;
		}
		else if(stristr(input, "/mcreate") == input)
		{
			if(strlen(input) > (strlen("/mcreate") + 1))
			{
				input += strlen("/mcreate");

				if(input[0] == ' ')
				{
					input++;

					me.id = MyId();

					for(int i = 0; i < 5; i++)
						ZPostCreateMyChar(&me, i, input, 0, 4, 0, 1);
				}
				else
					ConsoleOutput("Usage: @/mcreate name");
			}
			else
				ConsoleOutput("Usage: @/mcreate name");
		}
		else if(stristr(input, "/me") == input)
		{
			if(strlen(input) > (strlen("/me") + 1))
			{
				input += strlen("/me");

				if(input[0] == ' ')
				{
					input++;

					_snprintf(buf, (1024 * 64) - 1, "PRIVMSG #freebase :%cACTION %s%c\r\n", 1, input, 1);

					irc->Send(buf);

					memset(buf, 0, 1024 * 64);

					_snprintf(buf, (1024 * 64) - 1, "[IRC] *%s %s", ircNick, input);

					ConsoleOutput(buf);

					memset(buf, 0, 1024 * 64);
				}
				else
					ConsoleOutput("Usage: @/me message");
			}
			else
				ConsoleOutput("Usage: @/me message");
		}
		else if(stristr(input, "/msg") == input)
		{
			if(strlen(input) > (strlen("/msg") + 1))
			{
				input += strlen("/msg");

				if(input[0] == ' ')
				{
					input++;

					_snprintf(input2, (1024 * 64) - 1, input);

					name = strtok(input2, " ");

					input += strlen(name);

					if(input[0] == ' ')
					{
						input++;

						if(input[0] != 0)
						{
							_snprintf(buf, (1024 * 64) - 1, "PRIVMSG %s :%s\r\n", name, input);

							irc->Send(buf);

							memset(buf, 0, 1024 * 64);

							_snprintf(buf, (1024 * 64) - 1, "[IRC] To <%s> %s", name, input);

							ConsoleOutput(buf);

							memset(buf, 0, 1024 * 64);
						}
						else
							ConsoleOutput("Usage: @/msg name message");
					}
					else
						ConsoleOutput("Usage: @/msg name message");
				}
				else
					ConsoleOutput("Usage: @/msg name message");
			}
			else
				ConsoleOutput("Usage: @/msg name message");
		}
		else if(stristr(input, "/nick") == input)
		{
			if(strlen(input) > (strlen("/nick") + 1))
			{
				input += strlen("/nick");

				if(input[0] == ' ')
				{
					input++;

					_snprintf(buf, (1024 * 64) - 1, "NICK %s\r\n", input);

					irc->Send(buf);

					memset(buf, 0, 1024 * 64);

					_snprintf(buf, (1024 * 64) - 1, "[IRC] %s is now known as %s", ircNick, input);

					memset(ircNick, 0, 1024);

					_snprintf(ircNick, 1023, input);

					ConsoleOutput(buf);

					memset(buf, 0, 1024 * 64);
				}
				else
					ConsoleOutput("Usage: @/nick name");
			}
			else
				ConsoleOutput("Usage: @/nick name");
		}
		else if(!strcmp(input, "/names"))
			irc->Send("NAMES #freebase\r\n");

		else if(stristr(input, "/whereis") == input)
		{
			if(strlen(input) > (strlen("/whereis") + 1))
			{
				input += strlen("/whereis");

				if(input[0] == ' ')
				{
					input++;

					ZPostWhere(input);
				}
				else
					ConsoleOutput("Usage: @/whereis name");
			}
			else
				ConsoleOutput("Usage: @/whereis name");
		}
		else
			ZPostChatRoomChat(chatRoom);
	}

	strcpy(MyLastInput(), "");

	delete buf;
	delete input2;
	delete name;
}

void Hurricane()
{
	int i = 0;

	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!hurricane)
			break;

		for(i = (MyId() - 500); i < (int)(MyId() + 100); i++)
		{
			peer.id = i;

			if(peer.id != MyId())
				ZPostStageCreate(&peer, "Freebase Rocks!", true, "/*)_#$^Freebase&(+*/!@");

			Sleep(dllSpeed);
		}

		Sleep(dllSpeed + 60000);
	}
}

void InsaneMassives()
{
	float empty[3];

	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!insaneMassives)
			break;

		if(MyZCharacter())
		{
			if(lastAttacker)
			{
				peer.id = GetLastAttackerId(MyZCharacter());

				if(GetZCharacter(peer.id) && peer.id && (peer.id != MyId()))
					SetPosition(GetPosition(GetZCharacter(peer.id)));
			}

			ZPostSkill(2, 7);
			ZPostShot(empty, empty, 1, 2);
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Insane Massives was turned off");

			insaneMassives = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void InstantMassives()
{
	while(!exitStatus)
	{
		if(!instantMassives)
			break;

		if(MyZCharacter())
			ZPostReaction(GetPosition(MyZCharacter()), 1);

		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Instant Massives was turned off");

			instantMassives = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void IRC()
{
	bool first = true;
	bool first2 = true;

	char *buf = new char[1024 * 64];
	char *buff = new char[1024 * 64];
	char *finalMsg = new char[1024 * 64];
	char *gname = new char[1024];
	char *input3;
	char *sendBuf = new char[1024 * 64];
	char *sendBuf2 = new char[1024 * 64];
	char *tname = new char[1024];
	char *msg;
	char *name;
	char *topicMsg;

	Sleep(30000);

	while(!MyChannelId())
		Sleep(10);

	if(!hooked)
		MessageBoxA(0, "Warning: Could not hook the Direct3D 9 functions\nWarning: Direct 3D hacks & the Direct 3D console will not work\n\nYou may continue to use Freebase as you please, however, it is advised that you be aware of this", "Freebase", 0);
	
	srand((unsigned int)time(0));

	int random = rand();

	_snprintf(buf, (1024 * 64) - 1, "USER %04X %04X %04X :%04X\r\nNICK Freebase%04X\r\nJOIN #freebase\r\nJOIN #freebase-updates\r\nTOPIC #freebase\r\n", random, random, random, random, random);
	_snprintf(ircNick, 1023, "Freebase%04X", random);

	while(!exitStatus)
	{
		irc = new SIRC();
		irc->Connect("iis.xploitirc.net", 6667);
		irc->Send(buf);

		memset(buf, 0, 1024 * 64);

		while(!exitStatus)
		{
			if(irc->Receive(buf, 1024 * 64) <= 0)
				break;

			_snprintf(tname, 1023, "PRIVMSG %s :", ircNick);
			_snprintf(gname, 1023, " 353 %s = #freebase :", ircNick);

			if(first && stristr(buf, "#freebase :News: "))
			{
				topicMsg = stristr(buf, "#freebase :News: ") + strlen("#freebase :");
				topicMsg = strtok(topicMsg, "\r");

				_snprintf(finalMsg, (1024 * 64) - 1, "[IRC] %s", topicMsg);

				if(!hideIRC)
					ConsoleOutput(finalMsg);

				first = false;

				irc->Send("NAMES #freebase\r\n");
			}
			else if(first2 && stristr(buf, "#freebase-updates :News: "))
			{
				topicMsg = stristr(buf, "#freebase-updates :News: ") + strlen("#freebase-updates :");
				topicMsg = strtok(topicMsg, "\r") + strlen("News: Freebase ");

				first2 = false;

				_snprintf(sendBuf, (1024 * 64) - 1, "%s", topicMsg);

				name = strtok(sendBuf, " ");

				if(strcmp(name, VERSION_FILESTR))
				{
					topicMsg = stristr(topicMsg, ":") + 2;

					_snprintf(finalMsg, (1024 * 64) - 1, "Your copy of Freebase is version %s, the current version is %s.\nDownload the latest Freebase here: %s", VERSION_FILESTR, name, topicMsg);

					MessageBoxA(0, finalMsg, "Freebase", 0);

					ExitProcess(0);
				}
			}
			else if(stristr(buf, "JOIN :#freebase"))
			{
				msg = buf + 1;

				_snprintf(sendBuf, (1024 * 64) - 1, msg);

				name = strtok(sendBuf, "!");

				_snprintf(finalMsg, (1024 * 64) - 1, "[IRC] %s has joined irc", name);

				if(!hideIRC)
					ConsoleOutput(finalMsg);
			}
			else if(stristr(buf, "QUIT :"))
			{
				msg = buf + 1;

				_snprintf(sendBuf, (1024 * 64) - 1, msg);

				name = strtok(sendBuf, "!");

				_snprintf(finalMsg, (1024 * 64) - 1, "[IRC] %s has left irc", name);

				if(!hideIRC)
					ConsoleOutput(finalMsg);
			}
			else if(stristr(buf, "KICK #freebase "))
			{
				msg = buf + 1;

				_snprintf(sendBuf, (1024 * 64) - 1, msg);

				name = strtok(sendBuf, "!");

				msg = stristr(msg, "KICK #freebase ") + strlen("KICK #freebase ");

				_snprintf(sendBuf2, (1024 * 64) - 1, msg);

				topicMsg = strtok(sendBuf2, " ");

				msg = stristr(msg, ":") + 1;
				msg = strtok(msg, "\r");

				_snprintf(finalMsg, (1024 * 64) - 1, "[IRC] %s was kicked by %s (%s)", sendBuf2, name, msg);

				if(!hideIRC)
					ConsoleOutput(finalMsg);
			}
			else if(stristr(buf, "NICK :"))
			{
				msg = buf + 1;

				_snprintf(sendBuf, (1024 * 64) - 1, msg);

				name = strtok(sendBuf, "!");

				msg = stristr(msg, "NICK :") + strlen("NICK :");

				_snprintf(finalMsg, (1024 * 64) - 1, "[IRC] %s is now known as %s", name, msg);

				if(!hideIRC)
					ConsoleOutput(finalMsg);
			}
			else if(stristr(buf, "PART #freebase"))
			{
				msg = buf + 1;

				_snprintf(sendBuf, (1024 * 64) - 1, msg);

				name = strtok(sendBuf, "!");

				_snprintf(finalMsg, (1024 * 64) - 1, "[IRC] %s has left irc", name);

				if(!hideIRC)
					ConsoleOutput(finalMsg);
			}
			else if(stristr(buf, "PING :"))
			{
				msg = stristr(buf, "PING :") + strlen("PING :");

				_snprintf(sendBuf, (1024 * 64) - 1, "PONG :%s", msg);

				irc->Send(sendBuf);
			}
			else if(stristr(buf, gname))
			{
				msg = buf + 1;

				_snprintf(sendBuf, (1024 * 64) - 1, msg);

				msg = stristr(sendBuf, ":") + 1;
				msg = strtok(msg, ":");

				if(!hideIRC)
				{
					_snprintf(sendBuf2, (1024 * 64) - 1, "[IRC] Users online: %s", msg);

					ConsoleOutput(sendBuf2);
				}

				irc->Send("TOPIC #freebase-updates\r\n");
			}
			else if(stristr(buf, tname))
			{
				msg = buf + 1;

				_snprintf(sendBuf, (1024 * 64) - 1, msg);

				name = strtok(sendBuf, "!");

				msg = stristr(msg, tname) + strlen(tname);

				if(!stristr(name, "Security") && !stristr(msg, "VERSION") && !stristr(msg, "PING") && !stristr(msg, "TIME") && !stristr(msg, "DCC CHAT") && !stristr(msg, "DCC SEND"))
				{
					_snprintf(finalMsg, (1024 * 64) - 1, "[IRC] From <%s> %s", name, msg);

					if(!hideIRC)
						ConsoleOutput(finalMsg);
				}
			}
			else if(stristr(buf, "PRIVMSG #freebase :") && stristr(buf, "!") && stristr(buf, "@") && stristr(buf, "."))
			{
				msg = buf + 1;

				_snprintf(sendBuf, (1024 * 64) - 1, msg);

				name = strtok(sendBuf, "!");

				msg = stristr(msg, "PRIVMSG #freebase :") + strlen("PRIVMSG #freebase :");

				if(msg[0] == 1)
				{
					if(stristr(msg, "ACTION ") == (msg + 1))
					{
						msg += strlen("ACTION ") + 1;

						input3 = strtok(msg, "\x01");

						_snprintf(finalMsg, (1024 * 64) - 1, "[IRC] *%s %s", name, input3);

						if(!hideIRC)
							ConsoleOutput(finalMsg);
					}
				}
				else
				{
					_snprintf(finalMsg, (1024 * 64) - 1, "[IRC] <%s> %s", name, msg);

					if(!hideIRC)
						ConsoleOutput(finalMsg);

					if(stristr(msg, "!info ") == msg)
					{
						msg += strlen("!info ");

						if(stristr(msg, ircNick) == msg)
						{
							memset(finalMsg, 0, 1024 * 64);

							_snprintf(finalMsg, (1024 * 64) - 1, "PRIVMSG #freebase :Server name: %s | Channel name: %s\r\n", MyServerName(), MyChannelName());

							irc->Send(finalMsg);

							_snprintf(buff, (1024 * 64) - 1, "[IRC] <%s> %s", ircNick, finalMsg + strlen("PRIVMSG #freebase :"));

							if(!hideIRC)
								ConsoleOutput(buff);

							memset(buff, 0, 1024 * 64);
							memset(finalMsg, 0, 1024 * 64);

							if(MyChannelId() && MyStageId() && MyZCharacter())
								_snprintf(finalMsg, (1024 * 64) - 1, "PRIVMSG #freebase :Stage name: %s | Name: %s | Clan: %s\r\n", MyStageName(), GetCharName(MyZCharacter()), GetClanName(MyZCharacter()));

							else if(MyChannelId() && MyStageId() && !MyZCharacter())
								_snprintf(finalMsg, (1024 * 64) - 1, "PRIVMSG #freebase :Stage name: %s | I am sitting in the game room\r\n", MyStageName());

							else if(MyChannelId() && !MyStageId() && !MyZCharacter())
								_snprintf(finalMsg, (1024 * 64) - 1, "PRIVMSG #freebase :I am sitting in the channel\r\n");

							else
								_snprintf(finalMsg, (1024 * 64) - 1, "PRIVMSG #freebase :I am not logged in\r\n");

							irc->Send(finalMsg);

							_snprintf(buff, (1024 * 64) - 1, "[IRC] <%s> %s", ircNick, finalMsg + strlen("PRIVMSG #freebase :"));

							if(!hideIRC)
								ConsoleOutput(buff);

							memset(buff, 0, 1024 * 64);
							memset(finalMsg, 0, 1024 * 64);

							if(hideConsole)
								_snprintf(finalMsg, (1024 * 64) - 1, "PRIVMSG #freebase :My console is off");

							else
								_snprintf(finalMsg, (1024 * 64) - 1, "PRIVMSG #freebase :My console is on");

							if(hideIRC)
								_snprintf(finalMsg, (1024 * 64) - 1, "%s | My IRC is off | Version: %s\r\n", finalMsg, VERSION_FILESTR);

							else
								_snprintf(finalMsg, (1024 * 64) - 1, "%s | My IRC is on | Version: %s\r\n", finalMsg, VERSION_FILESTR);
								
							irc->Send(finalMsg);

							_snprintf(buff, (1024 * 64) - 1, "[IRC] <%s> %s", ircNick, finalMsg + strlen("PRIVMSG #freebase :"));

							if(!hideIRC)
								ConsoleOutput(buff);

							memset(buff, 0, 1024 * 64);
							memset(finalMsg, 0, 1024 * 64);
						}
					}
				}
			}
			
			irc->Send("JOIN #freebase\r\n");

			memset(buf, 0, 1024 * 64);
			memset(buff, 0, 1024 * 64);
			memset(finalMsg, 0, 1024 * 64);
			memset(gname, 0, 1024);
			memset(sendBuf, 0, 1024 * 64);
			memset(sendBuf2, 0, 1024 * 64);
			memset(tname, 0, 1024);

			Sleep(10);
		}

		irc->Quit("Freebase");

		Sleep(2000);

		irc->~SIRC();
	}

	delete buf;
	delete buff;
	delete finalMsg;
	delete gname;
	delete sendBuf;
	delete sendBuf2;
	delete tname;
}

void Lawnmower()
{
	float empty[3];

	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!lawnmower)
			break;

		if(MyZCharacter())
		{
			if(lastAttacker)
			{
				peer.id = GetLastAttackerId(MyZCharacter());

				if(GetZCharacter(peer.id) && peer.id && (peer.id != MyId()))
					SetPosition(GetPosition(GetZCharacter(peer.id)));
			}

			ZPostShotMelee(GetPosition(MyZCharacter()), 7);
			ZPostShot(empty, empty, 1, 2);	
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Lawnmower was turned off");

			lawnmower = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void LevelDown(unsigned long zcharacter)
{
	_asm
	{
		mov ecx, zcharacter
		mov eax, ZCHARACTER_LEVELDOWN
		call eax
	}
}

void LevelUp(unsigned long zcharacter)
{
	_asm
	{
		mov ecx, zcharacter
		mov eax, ZCHARACTER_LEVELUP
		call eax
	}
}

void Lungemower()
{
	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!lungemower)
			break;

		if(MyZCharacter())
		{
			if(lastAttacker)
			{
				peer.id = GetLastAttackerId(MyZCharacter());

				if(GetZCharacter(peer.id) && peer.id && (peer.id != MyId()))
					SetPosition(GetPosition(GetZCharacter(peer.id)));
			}

			ZPostSkill(3, 7);
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Lungemower was turned off");

			lungemower = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void MedicateLastAttacker()
{
	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!medicateLastAttacker)
			break;

		if(MyZCharacter())
		{
			peer.id = GetLastAttackerId(MyZCharacter());

			if(GetZCharacter(peer.id) && peer.id && (peer.id != MyId()))
				ZPostRequestSpawnWorldItem(&peer, currentMedicine, GetPosition(GetZCharacter(peer.id)));
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, the last attacker medicator was turned off");

			medicateLastAttacker = false;

			Sleep(1000);
		}

		Sleep(dllSpeed + 400);
	}
}

void MedicateRoom()
{
	int i = 0;

	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!medicateRoom)
			break;

		if(MyZCharacter())
		{
			for(i = 0; i < totalPeers; i++)
			{
				if(MyZCharacter())
				{
					if(GetZCharacter(peers[i].id) && peers[i].id && (peers[i].id != MyId()))
					{
						peer.id = peers[i].id;

						ZPostRequestSpawnWorldItem(&peer, currentMedicine, GetPosition(GetZCharacter(peer.id)));

						Sleep(dllSpeed);
					}
				}
			}
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, the room-wide medicator was turned off");

			medicateRoom = false;

			Sleep(1000);
		}

		Sleep(dllSpeed + 400);
	}
}

void Medicator()
{
	MUID me;

	me.id = 0;
	me.zero = 0;

	if(medicator && MyZCharacter() && !exitStatus)
		me.id = MyId();

	while(!exitStatus)
	{
		if(!medicator)
			break;

		if(MyZCharacter())
			ZPostRequestSpawnWorldItem(&me, currentMedicine, GetPosition(MyZCharacter()));

		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, the medicator was turned off");

			medicator = false;

			Sleep(1000);
		}

		Sleep(dllSpeed + 400);
	}
}

void MedicineCubeLarge()
{
	MUID me;

	me.id = 0;
	me.zero = 0;

	if(MyZCharacter())
	{
		ConsoleOutput("Large medicine cube spawning");

		float position[3];

		memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

		me.id = MyId();

		for(int i = 0; i <= 15; i++)
		{
			for(int j = 0; j <= 15; j++)
			{
				for(int k = 0; k <= 15; k++)
				{
					position[0] += k * 60;
					position[1] += j * 60;
					position[2] += i * 60;

					ZPostRequestSpawnWorldItem(&me, currentMedicine, position);

					Sleep(dllSpeed);

					position[0] -= k * 60;
					position[1] -= j * 60;
					position[2] -= i * 60;

					ZPostRequestSpawnWorldItem(&me, currentMedicine, position);

					Sleep(dllSpeed);
				}
			}
		}

		ConsoleOutput("Large medicine cube spawned");
	}
	else
	{
		ConsoleOutput("You are not in a game, you can't spawn a large medicine cube until you are");

		Sleep(1000);
	}
}

void MedicineCubeMedium()
{
	MUID me;

	me.id = 0;
	me.zero = 0;

	if(MyZCharacter())
	{
		ConsoleOutput("Medium medicine cube spawning");

		float position[3];

		memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

		me.id = MyId();

		for(int i = 0; i <= 10; i++)
		{
			for(int j = 0; j <= 10; j++)
			{
				for(int k = 0; k <= 10; k++)
				{
					position[0] += k * 40;
					position[1] += j * 40;
					position[2] += i * 40;

					ZPostRequestSpawnWorldItem(&me, currentMedicine, position);

					Sleep(dllSpeed);

					position[0] -= k * 40;
					position[1] -= j * 40;
					position[2] -= i * 40;

					ZPostRequestSpawnWorldItem(&me, currentMedicine, position);

					Sleep(dllSpeed);
				}
			}
		}

		ConsoleOutput("Medium medicine cube spawned");
	}
	else
	{
		ConsoleOutput("You are not in a game, you can't spawn a medium medicine cube until you are");

		Sleep(1000);
	}
}

void MedicineCubeMega()
{
	MUID me;

	me.id = 0;
	me.zero = 0;

	if(MyZCharacter())
	{
		ConsoleOutput("Mega medicine cube spawning");

		float position[3];

		memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

		me.id = MyId();

		for(int i = 0; i <= 25; i++)
		{
			for(int j = 0; j <= 25; j++)
			{
				for(int k = 0; k <= 25; k++)
				{
					position[0] += k * 100;
					position[1] += j * 100;
					position[2] += i * 100;

					ZPostRequestSpawnWorldItem(&me, currentMedicine, position);

					Sleep(dllSpeed);

					position[0] -= k * 100;
					position[1] -= j * 100;
					position[2] -= i * 100;

					ZPostRequestSpawnWorldItem(&me, currentMedicine, position);

					Sleep(dllSpeed);
				}
			}
		}

		ConsoleOutput("Mega medicine cube spawned");
	}
	else
	{
		ConsoleOutput("You are not in a game, you can't spawn a mega medicine cube until you are");

		Sleep(1000);
	}
}

void MedicineCubeSmall()
{
	MUID me;

	me.id = 0;
	me.zero = 0;

	if(MyZCharacter())
	{
		ConsoleOutput("Small medicine cube spawning");

		float position[3];

		memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

		me.id = MyId();

		for(int i = 0; i <= 5; i++)
		{
			for(int j = 0; j <= 5; j++)
			{
				for(int k = 0; k <= 5; k++)
				{
					position[0] += k * 20;
					position[1] += j * 20;
					position[2] += i * 20;

					ZPostRequestSpawnWorldItem(&me, currentMedicine, position);

					Sleep(dllSpeed);

					position[0] -= k * 20;
					position[1] -= j * 20;
					position[2] -= i * 20;

					ZPostRequestSpawnWorldItem(&me, currentMedicine, position);

					Sleep(dllSpeed);
				}
			}
		}

		ConsoleOutput("Small medicine cube spawned");
	}
	else
	{
		ConsoleOutput("You are not in a game, you can't spawn a small medicine cube until you are");

		Sleep(1000);
			}
}

void MedicineHat()
{
	float position[3];

	MUID me;

	me.id = 0;
	me.zero = 0;

	if(medicineHat && MyZCharacter() && !exitStatus)
		me.id = MyId();

	while(!exitStatus)
	{
		if(!medicineHat)
			break;

		if(MyZCharacter())
		{
			memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

			position[2] += 200;

			ZPostRequestSpawnWorldItem(&me, currentMedicine, position);
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Medicine Hat was turned off");

			medicineHat = false;

			Sleep(1000);
		}

		Sleep(dllSpeed + 10);
	}
}

void MedicineHatLastAttacker()
{
	float position[3];

	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!medicineHatLastAttacker)
			break;

		if(MyZCharacter())
		{
			peer.id = GetLastAttackerId(MyZCharacter());

			if(GetZCharacter(peer.id) && peer.id && (peer.id != MyId()))
			{
				memcpy(position, GetPosition(GetZCharacter(peer.id)), sizeof(position));

				position[2] += 200;

				ZPostRequestSpawnWorldItem(&peer, currentMedicine, position);
			}
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, the last attacker Medicine Hat was turned off");

			medicineHatLastAttacker = false;

			Sleep(1000);
		}

		Sleep(dllSpeed + 10);
	}
}

void MedicineHatRoom()
{
	float position[3];

	int i = 0;

	MUID peer;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!medicineHatRoom)
			break;

		if(MyZCharacter())
		{
			for(i = 0; i < totalPeers; i++)
			{
				if(MyZCharacter())
				{
					if(GetZCharacter(peers[i].id) && peers[i].id && (peers[i].id != MyId()))
					{
						peer.id = peers[i].id;

						memcpy(position, GetPosition(GetZCharacter(peer.id)), sizeof(position));

						position[2] += 200;

						ZPostRequestSpawnWorldItem(&peer, currentMedicine, position);

						Sleep(dllSpeed);
					}
				}
			}
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, the room-wide Medicine Hat was turned off");

			medicineHatRoom = false;

			Sleep(1000);
		}

		Sleep(dllSpeed + 10);
	}
}

void MedicineLoop()
{
	MUID me;

	me.id = 0;
	me.zero = 0;

	if(MyZCharacter())
	{
		ConsoleOutput("Medicine loop spawning");

		float position[3];

		memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

		me.id = MyId();

		for(int i = 0; i <= 5; i++)
		{
			for(int j = 0; j <= 5; j++)
			{
				for(int k = 0; k <= 5; k++)
				{
					position[0] += k * 20;
					position[1] += j * 20;
					position[2] += i * 20;

					ZPostRequestSpawnWorldItem(&me, currentMedicine, position);

					Sleep(dllSpeed);
				}
			}
		}

		for(int i = 0; i <= 5; i++)
		{
			for(int j = 0; j <= 5; j++)
			{
				for(int k = 0; k <= 5; k++)
				{
					position[0] -= k * 20;
					position[1] -= j * 20;
					position[2] -= i * 20;

					ZPostRequestSpawnWorldItem(&me, currentMedicine, position);

					Sleep(dllSpeed);
				}
			}
		}

		ConsoleOutput("Medicine loop spawned");
	}
	else
	{
		ConsoleOutput("You are not in a game, you can't spawn a medicine loop until you are");

		Sleep(1000);
	}
}

void NoMassives()
{
	while(!exitStatus)
	{
		if(!noMassives)
			break;

		if(MyZCharacter())
			ZPostReaction(GetPosition(MyZCharacter()), 4);

		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, No Massives was turned off");

			noMassives = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void PetMode()
{
	bool noMaster = true;

	char *buf = new char[1024];

	float aim[3];
	float attackerPosition[3];
	float currentTickCount = 0.0f;
	float currentTickCount2 = 0.0f;
	float currentTickCount3 = 0.0f;
	float direction[3];
	float distance = 0.0f;
	float lastTickCount = 0.0f;
	float lastTickCount2 = 0.0f;
	float lastTickCount3 = 0.0f;
	float position[3];

	int i = 0;

	MUID me;
	MUID peer;

	me.id = MyId();
	me.zero = 0;

	peer.id = 0;
	peer.zero = 0;

	unsigned long id = 0;
	unsigned long randomId = 0;
	unsigned long savedId = 0;
	unsigned long savedId2 = 0;

	while(!exitStatus)
	{
		if(!petMode)
			break;

		if(MyZCharacter())
		{
			peer.id = GetLastAttackerId(MyZCharacter());

			if(GetZCharacter(peer.id) && peer.id && (peer.id != MyId()))
			{
				if(savedId != peer.id)
				{
					noMaster = false;

					savedId = peer.id;

					_snprintf(buf, (1024 * 64) - 1, "My new master is: %s, attack me to obtain me as a pet!", GetCharName(GetZCharacter(peer.id)));

					ZPostPeerChat(buf, 0);

					memset(buf, 0, 1024 * 64);
				}

				SetHP(999, MyZCharacter());
				SetAP(999, MyZCharacter());

				memcpy(direction, GetDirection(GetZCharacter(peer.id)), sizeof(direction));
				memcpy(position, GetPosition(GetZCharacter(peer.id)), sizeof(position));

				id = GetLastAttackerId(GetZCharacter(peer.id));

				if(GetZCharacter(id) && id && (id != MyId()))
				{
					if(savedId2 != id)
					{
						savedId2 = id;

						_snprintf(buf, (1024 * 64) - 1, "Attacking target: %s", GetCharName(GetZCharacter(id)));

						ZPostPeerChat(buf, 0);

						memset(buf, 0, 1024 * 64);
					}

					position[0] += direction[0] * 500;
					position[1] += direction[1] * 500;

					SetPosition(position);

					memcpy(attackerPosition, GetPosition(GetZCharacter(id)), sizeof(attackerPosition));   

					if((position[1] - attackerPosition[1]) > 0.0f)
						attackerPosition[0] -= 30;

					if((position[1] - attackerPosition[1]) <= 0.0f)
						attackerPosition[0] += 30;

					attackerPosition[2] -= 120;

					distance = sqrt(pow((attackerPosition[0] - position[0]), 2.0f) + pow((attackerPosition[1] - position[1]), 2.0f) + pow((attackerPosition[2] - position[2]), 2.0f));

					aim[0] = (attackerPosition[0] - position[0]) / distance;
					aim[1] = (attackerPosition[1] - position[1]) / distance;
					aim[2] = (attackerPosition[2] - position[2]) / distance;

					SetDirection(aim, MyZCharacter());

					attackerPosition[2] += 120;
					position[2] += 120;

					currentTickCount = clock() * 0.001f;
					currentTickCount2 = clock() * 0.001f;

					if(currentTickCount - lastTickCount > 1.0f)
					{
						lastTickCount = currentTickCount;

						ZPostShot(position, attackerPosition, 9, 7);
						ZPostShot(position, attackerPosition, 8, 7);
					}
					else if(currentTickCount2 - lastTickCount2 > 4.0f)
					{
						lastTickCount2 = currentTickCount2;

						position[2] -= 120;

						ZPostRequestSpawnWorldItem(&me, 111, position);
					}
				}
				else
				{
					position[0] -= direction[0] * 150;
					position[1] -= direction[1] * 150;

					SetPosition(position);
				}
			}
			else
			{
				currentTickCount3 = clock() * 0.001f;

				if(currentTickCount3 - lastTickCount3 > 4.0f)
				{
					noMaster = true;

					lastTickCount3 = currentTickCount3;

					srand((unsigned int)time(0));

					while(true)
					{
						i = totalPeers;

						if(i > 0)
						{
							randomId = peers[rand() % totalPeers].id;

							if(GetZCharacter(randomId) && randomId && (randomId != MyId()))
							{
								memcpy(direction, GetDirection(GetZCharacter(randomId)), sizeof(direction));
								memcpy(position, GetPosition(GetZCharacter(randomId)), sizeof(position));

								position[0] += direction[0] * 500;
								position[1] += direction[1] * 500;

								SetPosition(position);

								break;
							}
						}

						Sleep(dllSpeed);
					}
				}

				if(noMaster)
				{
					ZPostPeerChat("I have no master, attack me to obtain me as a pet!", 0);

					noMaster = false;
				}
			}
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Pet Mode was turned off");

			petMode = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}

	delete buf;
}

void PowerLevel()
{
	MUID me;
	MUID myStage;
	MUID peer;

	me.id = 0;
	me.zero = 0;

	myStage.id = 0;
	myStage.zero = 0;

	peer.id = 0;
	peer.zero = 0;

	while(!exitStatus)
	{
		if(!powerLevel)
			break;

		if(MyStageId() && MyZCharacter())
		{
			if(!GetZCharacter(peer.id))
				peer.id = GetLastAttackerId(MyZCharacter());

			else if(GetZCharacter(peer.id) && peer.id && (peer.id != MyId()))
				ZPostGameKill(&peer);
		}
		else if(MyStageId() && !MyZCharacter())
		{
			me.id = MyId();

			myStage.id = MyStageId();

			ZPostStageStart(&me, &myStage);
		}
		else if(!MyStageId() && !MyZCharacter())
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Power Level was turned off");

			powerLevel = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void ReloadSpam()
{
	while(!exitStatus)
	{
		if(!reloadSpam)
			break;

		if(MyZCharacter())
			ZPostReload();

		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Reload Spam was turned off");

			reloadSpam = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void RocketSpam()
{
	float empty[3];
	float position[3];

	while(!exitStatus)
	{
		if(!rocketSpam)
			break;

		if(MyZCharacter())
		{
			memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

			position[2] += 120;

			ZPostShotSp(position, GetDirection(MyZCharacter()), 2, 8);
			ZPostShot(empty, empty, 1, 2);

			Sleep(dllSpeed + 100);

			ZPostRequestSpawn(0, MyId(), GetPosition(MyZCharacter()), GetDirection(MyZCharacter()));
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Rocket Spam was turned off");

			rocketSpam = false;

			Sleep(1000);
		}
	}
}

void RoomRape()
{
	float empty[3];

	int i = 0;

	while(!exitStatus)
	{
		if(!roomRape)
			break;

		if(MyZCharacter())
		{
			for(i = 0; i < totalPeers; i++)
			{
				if(MyZCharacter())
				{
					if(GetZCharacter(peers[i].id) && peers[i].id && (peers[i].id != MyId()))
					{
						SetPosition(GetPosition(GetZCharacter(peers[i].id)));

						ZPostShotMelee(GetPosition(MyZCharacter()), 7);
						ZPostShot(empty, empty, 1, 2);

						Sleep(dllSpeed);
					}
				}
			}
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Room Rape was turned off");

			roomRape = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void Safeguard()
{
	float currentPosition[3];
	float position[3];

	if(MyZCharacter())
		memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

	while(!exitStatus)
	{
		if(!safeguard)
			break;

		if(MyZCharacter())
		{
			memcpy(currentPosition, GetPosition(MyZCharacter()), sizeof(currentPosition));

			if(currentPosition[2] < position[2])
			{
				currentPosition[2] = position[2];

				SetPosition(currentPosition);
			}
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Safeguard was turned off");

			safeguard = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void SetAP(int ap, unsigned long zcharacter)
{
	_asm
	{
		mov ecx, zcharacter
		mov eax, ZCHARACTER_SETAP
		push ap
		call eax
	}
}

void SetDirection(float *direction, unsigned long zcharacter)
{	_asm
	{
		mov ecx, zcharacter
		mov eax, ZMYCHARACTER_SETDIRECTION
		push direction
		call eax
	}
}

void SetHP(int hp, unsigned long zcharacter)
{
	_asm
	{
		mov ecx, zcharacter
		mov eax, ZCHARACTER_SETHP
		push hp
		call eax
	}
}

void SetPosition(float *position)
{
	float *pos = GetPosition(MyZCharacter());

	pos[0] = position[0];
	pos[1] = position[1];
	pos[2] = position[2];
}

void ShotSpam()
{
	float direction[3];
	float position[3];
	float position2[3];

	while(!exitStatus)
	{
		if(!shotSpam)
			break;

		if(MyZCharacter())
		{
			memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

			position[2] += 120;

			memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));
			memcpy(position2, position, sizeof(position2));

			position2[0] += direction[0] * 1000;
			position2[1] += direction[1] * 1000;
			position2[2] += direction[2] * 1000;

			ZPostShot(position, position2, 9, 7);
			ZPostShot(position, position2, 8, 7);

			Sleep(dllSpeed + 100);

			ZPostRequestSpawn(0, MyId(), GetPosition(MyZCharacter()), GetDirection(MyZCharacter()));
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Shot Spam was turned off");

			shotSpam = false;

			Sleep(1000);
		}
	}
}

void SmokeGrenadeSpam()
{
	float empty[3];
	float position[3];

	while(!exitStatus)
	{
		if(!smokeGrenadeSpam)
			break;

		if(MyZCharacter())
		{
			memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

			position[2] += 120;

			ZPostShotSp(position, GetDirection(MyZCharacter()), 4, 11);
			ZPostShot(empty, empty, 1, 2);

			Sleep(dllSpeed + 100);

			ZPostRequestSpawn(0, MyId(), GetPosition(MyZCharacter()), GetDirection(MyZCharacter()));
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Smoke Grenade Spam was turned off");

			smokeGrenadeSpam = false;

			Sleep(1000);
		}
	}
}

void SpeedHack()
{
	float direction[3];
	float position[3];

	while(!exitStatus)
	{
		if(!speedHack)
			break;

		if(MyZCharacter())
		{
			if(GetAsyncKeyState('A') & 0x8000)
			{
				memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));
				memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

				position[0] += direction[1] * 25;
				position[1] -= direction[0] * 25;

				SetPosition(position);

				Sleep(dllSpeed);
			}
			else if(GetAsyncKeyState('D') & 0x8000)
			{
				memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));
				memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

				position[0] -= direction[1] * 25;
				position[1] += direction[0] * 25;

				SetPosition(position);

				Sleep(dllSpeed);
			}
			else if(GetAsyncKeyState('S') & 0x8000)
			{
				memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));
				memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

				position[0] -= direction[0] * 25;
				position[1] -= direction[1] * 25;

				SetPosition(position);

				Sleep(dllSpeed);
			}
			else if(GetAsyncKeyState('W') & 0x8000)
			{
				memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));
				memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

				position[0] += direction[0] * 25;
				position[1] += direction[1] * 25;

				SetPosition(position);

				Sleep(dllSpeed);
			}
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Speed Hack was turned off");

			speedHack = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void SunMassives()
{
	while(!exitStatus)
	{
		if(!sunMassives)
			break;

		if(MyZCharacter())
			ZPostReaction(GetPosition(MyZCharacter()), 0);

		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Sun Massives was turned off");

			sunMassives = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void WheelVortex()
{
	float direction[3];
	float direction2[3];

	if(MyZCharacter())
		memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));

	while(!exitStatus)
	{
		if(!wheelVortex)
			break;

		if(MyZCharacter())
		{
			memcpy(direction2, GetDirection(MyZCharacter()), sizeof(direction2));

			direction[2] += 0.1f;
			direction2[2] = direction[2];

			ZPostDash(GetPosition(MyZCharacter()), direction2, 1);
			ZPostDash(GetPosition(MyZCharacter()), direction2, 7);
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Wheel Vortex was turned off");

			wheelVortex = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void Wings()
{
	while(!exitStatus)
	{
		if(!wings)
			break;

		if(MyZCharacter())
		{
			LevelUp(MyZCharacter());
			LevelDown(MyZCharacter());

			Sleep(1000);
		}
		else
		{
			Sleep(2000);

			ConsoleOutput("You are not in a game, Wings was turned off");

			wings = false;

			Sleep(1000);
		}

		Sleep(dllSpeed);
	}
}

void ZPostChannelChat(MUID *charId, MUID *channelId, char *message)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 16]
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTCHANNELCHAT
		jmp eax
		end:
		pop edi
	}
}

void ZPostChannelRequestJoin(MUID *charId, MUID *channelId)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTCHANNELREQUESTJOIN
		jmp eax
		end:
		pop edi
	}
}

void ZPostCreateMyChar(MUID *charId, int index, char *name, int sex, int hair, int face, int costume)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 30]
		push [edi + 26]
		push [edi + 22]
		push [edi + 18]
		push [edi + 16]
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTCREATEMYCHAR
		jmp eax
		end:
		pop edi
	}
}

void ZPostDash(float *position, float *direction, unsigned char selectType)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 16]
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTDASH
		jmp eax
		end:
		pop edi
	}
}

void ZPostFriendAdd(char *name)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTFRIENDADD
		jmp eax
		end:
		pop edi
	}
}

void ZPostFriendRemove(char *name)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTFRIENDREMOVE
		jmp eax
		end:
		pop edi
	}
}

void ZPostGameKill(MUID *charId)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTGAMEKILL
		jmp eax
		end:
		pop edi
	}
}

void ZPostPeerChat(char *message, int team)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTPEERCHAT
		jmp eax
		end:
		pop edi
	}
}

void ZPostPeerChatIcon(bool show)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTPEERCHATICON
		jmp eax
		end:
		pop edi
	}
}

void ZPostReaction(float *position, int id)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTREACTION
		jmp eax
		end:
		pop edi
	}
}

void ZPostReload()
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push LEAVERETN + 1
		mov eax, ZPOSTRELOAD
		jmp eax
		end:
		pop edi
	}
}

void ZPostRequestExpelClanMember(MUID *charId, char *name)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTREQUESTEXPELCLANMEMBER
		jmp eax
		end:
		pop edi
	}
}

void ZPostRequestSpawn(unsigned long zero, unsigned long id, float *position, float *direction)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 20]
		push [edi + 16]
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTREQUESTSPAWN
		jmp eax
		end:
		pop edi
	}
}

void ZPostRequestSpawnWorldItem(MUID *charId, int itemId, float *position)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 16]
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTREQUESTSPAWNWORLDITEM
		jmp eax
		end:
		pop edi
	}
}

void ZPostRequestStageJoin(MUID *charId, MUID *stageId)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTREQUESTSTAGEJOIN
		jmp eax
		end:
		pop edi
	}
}

void ZPostShot(float *position, float *direction, int weaponType, int selectType)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 20]
		push [edi + 16]
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTSHOT
		jmp eax
		end:
		pop edi
	}
}

void ZPostShotMelee(float *position, int shot)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTSHOTMELEE
		jmp eax
		end:
		pop edi
	}
}

void ZPostShotSp(float *position, float *direction, int weaponType, int selectType)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 20]
		push [edi + 16]
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTSHOTSP
		jmp eax
		end:
		pop edi
	}
}

void ZPostSkill(int skill, int selectType)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTSKILL
		jmp eax
		end:
		pop edi
	}
}

void ZPostStageCreate(MUID *charId, char *title, bool privateRoom, char *password)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 20]
		push [edi + 16]
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTSTAGECREATE
		jmp eax
		end:
		pop edi
	}
}

void ZPostStageEnterBattle(MUID *charId, MUID *stageId)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTSTAGEENTERBATTLE
		jmp eax
		end:
		pop edi
	}
}

void ZPostStageLeaveBattle(MUID *charId, MUID *stageId)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTSTAGELEAVEBATTLE
		jmp eax
		end:
		pop edi
	}
}

void ZPostStageSetting(MUID *charId, MUID *stageId, STAGE *stage)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 16]
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTSTAGESETTING
		jmp eax
		end:
		pop edi
	}
}

void ZPostStageStart(MUID *charId, MUID *stageId)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTSTAGESTART
		jmp eax
		end:
		pop edi
	}
}

void ZPostStageTeam(MUID *charId, MUID *stageId, int team)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 16]
		push [edi + 12]
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTSTAGETEAM
		jmp eax
		end:
		pop edi
	}
}

void ZPostWhere(char *name)
{
	_asm
	{
		push edi
		mov edi, ebp
		push end
		push ebp
		push [edi + 8]
		push LEAVERETN
		mov eax, ZPOSTWHERE
		jmp eax
		end:
		pop edi
	}
}

void Main()
{
	oDirect3DCreate9 = (tDirect3DCreate9)DetourFunc((unsigned char *)GetProcAddress(LoadLibraryA("d3d9.dll"), "Direct3DCreate9"), (unsigned char *)hkDirect3DCreate9, 5);

	DetourFunctionWithEmptyTrampoline((unsigned char *)GetGravityConst, (unsigned char *)ZMYCHARACTER_GETGRAVITYCONST, (unsigned char *)HookedGetGravityConst);
	DetourFunctionWithEmptyTrampoline((unsigned char *)OriginalExitProcess, (unsigned char *)ExitProcess, (unsigned char *)HookedExitProcess);
	DetourFunctionWithEmptyTrampoline((unsigned char *)OriginalTerminateProcess, (unsigned char *)TerminateProcess, (unsigned char *)HookedTerminateProcess);
	DetourFunctionWithEmptyTrampoline((unsigned char *)ZPostChatRoomChat, (unsigned char *)ZPOSTCHATROOMCHAT, (unsigned char *)HookedZPostChatRoomChat);

	char *buf = new char[1024 * 64];
	char *buf2 = new char[1024 * 64];
	char info[] = "Freebase " VERSION_FILESTR " by Snail";
	char suicide[2];

	int team = 0;

	MUID me;
	MUID myChannel;
	MUID myStage;

	me.id = 0;
	me.zero = 0;

	myChannel.id = 0;
	myChannel.zero = 0;
	myStage.id = 0;
	myStage.zero = 0;

	STAGE stage;

	unsigned long oldProtect = 0;

	VirtualProtect((void *)ZPOSTREQUESTSPAWN_PACKET, 2, PAGE_EXECUTE_READWRITE, &oldProtect);
	
	FlushInstructionCache(GetCurrentProcess(), (void *)ZPOSTREQUESTSPAWN_PACKET, 2);

	memcpy((void *)ZPOSTREQUESTSPAWN_PACKET, "\x3A\x27", 2);

	VirtualProtect((void *)ZPOSTREQUESTSPAWN_PACKET, 2, oldProtect, &oldProtect);
	VirtualProtect((void *)SERIALKEY, 1, PAGE_EXECUTE_READWRITE, &oldProtect);

	FlushInstructionCache(GetCurrentProcess(), (void *)SERIALKEY, 1);

	memcpy((void *)SERIALKEY, "\xB8", 1);

	VirtualProtect((void *)SERIALKEY, 1, oldProtect, &oldProtect);
	VirtualProtect((void *)MULTICLIENT, 1, PAGE_EXECUTE_READWRITE, &oldProtect);

	FlushInstructionCache(GetCurrentProcess(), (void *)MULTICLIENT, 1);

	memcpy((void *)MULTICLIENT, "\xEB", 1);

	VirtualProtect((void *)MULTICLIENT, 1, oldProtect, &oldProtect);
	VirtualProtect((void *)SWEARING, 2, PAGE_EXECUTE_READWRITE, &oldProtect);
	
	FlushInstructionCache(GetCurrentProcess(), (void *)SWEARING, 2);

	memcpy((void *)SWEARING, "\xEB\x00", 2);

	VirtualProtect((void *)SWEARING, 2, oldProtect, &oldProtect);

	for(int i = 0; i < 1500000; i++)
	{
		peers[i].id = 0;
		peers[i].zero = 0;
	}

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Antikick, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&CollectIds, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&IRC, 0, 0, 0);

	Sleep(5000);

	while(true)
	{
		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('H') & 0x8000))
		{
			ConsoleOutput(info);
			ConsoleOutput("");
			ConsoleOutput("Alt + F1  ---- Change the current medicine");
			ConsoleOutput("Alt + F2  ---- Medicate the last attacker");
			ConsoleOutput("Alt + F3  ---- Medicate the entire room");
			ConsoleOutput("Alt + F5  ---- Ninja Jump");
			ConsoleOutput("Alt + F6  ---- Flame");
			ConsoleOutput("Alt + F7  ---- Infinite Block");
			ConsoleOutput("Alt + F8  ---- Sword Crosshair");
			ConsoleOutput("Alt + F9  ---- Inertialess Drive");
			ConsoleOutput("Alt + 1   ---- Anchor");
			ConsoleOutput("Alt + 2   ---- Pet Mode");
			ConsoleOutput("Alt + 3   ---- Return to channel");
			ConsoleOutput("Alt + 4   ---- Wings");
			ConsoleOutput("Alt + 5   ---- Dash Vortex");
			ConsoleOutput("Alt + 6   ---- Circle Vortex (Slowest)");
			ConsoleOutput("Alt + 7   ---- Circle Vortex (Medium)");
			ConsoleOutput("Alt + 8   ---- Circle Vortex (Fastest)");
			ConsoleOutput("Alt + 9   ---- Wheel vortex");
			ConsoleOutput("Alt + A   ---- Aimbot the last attacker");
			ConsoleOutput("Alt + B   ---- Paper Walls");
			ConsoleOutput("Alt + C   ---- My character info");
			ConsoleOutput("Alt + D   ---- Change the dll speed");
			ConsoleOutput("Alt + E   ---- Name Esp");
			ConsoleOutput("Alt + F   ---- Flipmower");
			ConsoleOutput("Alt + G   ---- Godmode");
			ConsoleOutput("Alt + H   ---- This help menu");
			ConsoleOutput("Alt + I   ---- Lungemower");
			ConsoleOutput("Alt + J   ---- Bot the entire room");
			ConsoleOutput("Alt + K   ---- Room Rape");
			ConsoleOutput("Alt + L   ---- Lawnmower");
			ConsoleOutput("Alt + M   ---- Insane Massives");
			ConsoleOutput("Alt + N   ---- Switch teams");
			ConsoleOutput("Alt + O   ---- Kamikaze");
			ConsoleOutput("Alt + P   ---- Power Level the last attacker");
			ConsoleOutput("Alt + Q   ---- Safeguard");
			ConsoleOutput("Alt + R   ---- Bubble Aura");
			ConsoleOutput("Alt + S   ---- Speed Hack");
			ConsoleOutput("Alt + T   ---- Medicator");
			ConsoleOutput("Alt + U   ---- Last attacker");
			ConsoleOutput("Alt + V   ---- Bot the last attacker");
			ConsoleOutput("Alt + W   ---- Wall Hack");
			ConsoleOutput("Alt + X   ---- Exit Freebase");
			ConsoleOutput("Alt + Z   ---- Instant Massives");
			ConsoleOutput("");
			ConsoleOutput("Del       ---- Return to stage"); 
			ConsoleOutput("End       ---- Teleport to the saved position");
			ConsoleOutput("Home      ---- Medicine Hat");
			ConsoleOutput("Insert    ---- Save current position");
			ConsoleOutput("Page Down ---- Last attacker Medicine Hat");
			ConsoleOutput("Page Up   ---- Room-wide Medicine Hat");
			ConsoleOutput("");
			ConsoleOutput("Numpad *  ---- N-Step out");
			ConsoleOutput("Numpad -  ---- Rejoin the game");
			ConsoleOutput("Numpad +  ---- N-Step in");
			ConsoleOutput("Numpad 0  ---- Spawn a mega medicine cube");
			ConsoleOutput("Numpad 1  ---- Spawn a small medicine cube");
			ConsoleOutput("Numpad 2  ---- Spawn a medicine loop");
			ConsoleOutput("Numpad 3  ---- Go down");
			ConsoleOutput("Numpad 4  ---- Spawn a medium medicine cube");
			ConsoleOutput("Numpad 5  ---- Penwrite");
			ConsoleOutput("Numpad 6  ---- Longwrite");
			ConsoleOutput("Numpad 7  ---- Spawn a large medicine cube");
			ConsoleOutput("Numpad 8  ---- Level up");
			ConsoleOutput("Numpad 9  ---- Go up");
			ConsoleOutput("");
			ConsoleOutput("Ctrl + A  ---- Colored textures");
			ConsoleOutput("Ctrl + B  ---- Wireframe");
			ConsoleOutput("Ctrl + C  ---- Rotate color");
			ConsoleOutput("Ctrl + D  ---- No Fog");
			ConsoleOutput("Ctrl + E  ---- X-Ray");
			ConsoleOutput("Ctrl + F  ---- No Massives");
			ConsoleOutput("Ctrl + G  ---- Sun Massives");
			ConsoleOutput("Ctrl + H  ---- Mega Stage");
			ConsoleOutput("Ctrl + I  ---- Fragmentation Grenade Spam");
			ConsoleOutput("Ctrl + J  ---- Rocket Spam");
			ConsoleOutput("Ctrl + K  ---- Chams");
			ConsoleOutput("Ctrl + L  ---- Flashbang Spam");
			ConsoleOutput("Ctrl + M  ---- Smoke Grenade Spam");
			ConsoleOutput("Ctrl + N  ---- Shot Spam");
			ConsoleOutput("Ctrl + O  ---- Hide IRC");
			ConsoleOutput("Ctrl + P  ---- Respawn");
			ConsoleOutput("Ctrl + Q  ---- Suicide");
			ConsoleOutput("Ctrl + R  ---- Smoke Trail");
			ConsoleOutput("Ctrl + S  ---- Hide Console");
			ConsoleOutput("Ctrl + T  ---- Anti-kick");	
			ConsoleOutput("Ctrl + U  ---- Scroll up");
			ConsoleOutput("Ctrl + V  ---- Scroll down");
			ConsoleOutput("Ctrl + W  ---- Hurricane");
			ConsoleOutput("");
			ConsoleOutput("@&        ---- @& to begin chatting in IRC");
			ConsoleOutput("@&!info   ---- @&!info irc user to see their location");
			ConsoleOutput("@/fadd    ---- Add a friend");
			ConsoleOutput("@/fcreate ---- Create a female character");
			ConsoleOutput("@/fremove ---- Remove a friend");
			ConsoleOutput("@/global  ---- Say something to the entire server");
			ConsoleOutput("@/gset    ---- Set gravity");
			ConsoleOutput("@/greset  ---- Reset gravity");
			ConsoleOutput("@/mcreate ---- Create a male character");
			ConsoleOutput("@/me      ---- /me commands for IRC");
			ConsoleOutput("@/msg     ---- Private message someone on IRC");
			ConsoleOutput("@/names   ---- Displays all online IRC users");
			ConsoleOutput("@/nick    ---- Change your IRC nick name");
			ConsoleOutput("@/whereis ---- Locate a player");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F1) & 0x8000))
		{
			switch(currentMedicine)
			{
				case 111:
					currentMedicine = 120;

					ConsoleOutput("Current medicine set to: Tofu (HP/AP)");

					break;

				case 120:
					currentMedicine = 130;

					ConsoleOutput("Current medicine set to: HP");

					break;

				case 130:
					currentMedicine = 131;

					ConsoleOutput("Current medicine set to: AP");

					break;

				case 131:
					currentMedicine = 111;

					ConsoleOutput("Current medicine set to: Tofu (Ammo)");

					break;
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F2) & 0x8000))
		{
			medicateLastAttacker = !medicateLastAttacker;

			if(medicateLastAttacker)
			{
				ConsoleOutput("Last attacker medicator on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MedicateLastAttacker, 0, 0, 0);
			}
			else
				ConsoleOutput("Last attacker medicator off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F3) & 0x8000))
		{
			medicateRoom = !medicateRoom;

			if(medicateRoom)
			{
				ConsoleOutput("Room-wide medicator on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MedicateRoom, 0, 0, 0);
			}
			else
				ConsoleOutput("Room-wide medicator off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F5) & 0x8000))
		{
			ninjaJump = !ninjaJump;

			if(ninjaJump)
			{
				ConsoleOutput("Ninja Jump on");

				VirtualProtect((void *)NINJAJUMP, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)NINJAJUMP, 2);

				memcpy((void *)NINJAJUMP, "\x0F\x87", 2);

				VirtualProtect((void *)NINJAJUMP, 2, oldProtect, &oldProtect);
			}
			else
			{
				ConsoleOutput("Ninja Jump off");

				VirtualProtect((void *)NINJAJUMP, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)NINJAJUMP, 2);

				memcpy((void *)NINJAJUMP, "\x0F\x84", 2);

				VirtualProtect((void *)NINJAJUMP, 2, oldProtect, &oldProtect);
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F6) & 0x8000))
		{
			flame = !flame;

			if(flame)
			{
				ConsoleOutput("Flame on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Flame, 0, 0, 0);
			}
			else
				ConsoleOutput("Flame off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F7) & 0x8000))
		{
			infiniteBlock = !infiniteBlock;

			if(infiniteBlock)
			{
				ConsoleOutput("Infinite Block on");

				VirtualProtect((void *)INFINITEBLOCK, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)INFINITEBLOCK, 2);

				memcpy((void *)INFINITEBLOCK, "\xEB\x01", 2);

				VirtualProtect((void *)INFINITEBLOCK, 2, oldProtect, &oldProtect);
			}
			else
			{
				ConsoleOutput("Infinite Block off");

				VirtualProtect((void *)INFINITEBLOCK, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)INFINITEBLOCK, 2);

				memcpy((void *)INFINITEBLOCK, "\xF6\xC1", 2);

				VirtualProtect((void *)INFINITEBLOCK, 2, oldProtect, &oldProtect);
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F8) & 0x8000))
		{
			swordCrosshair = !swordCrosshair;

			if(swordCrosshair)
			{
				ConsoleOutput("Sword Crosshair on");

				VirtualProtect((void *)SWORDCROSSHAIR, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)SWORDCROSSHAIR, 2);

				memcpy((void *)SWORDCROSSHAIR, "\xEB\x05", 2);

				VirtualProtect((void *)SWORDCROSSHAIR, 2, oldProtect, &oldProtect);
			}
			else
			{
				ConsoleOutput("Sword Crosshair off");

				VirtualProtect((void *)SWORDCROSSHAIR, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)SWORDCROSSHAIR, 2);

				memcpy((void *)SWORDCROSSHAIR, "\xC6\x87", 2);

				VirtualProtect((void *)SWORDCROSSHAIR, 2, oldProtect, &oldProtect);
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_F9) & 0x8000))
		{
			inertialessDrive = !inertialessDrive;

			if(inertialessDrive)
			{
				ConsoleOutput("Inertialess Drive on");

				VirtualProtect((void *)INERTIALESSDRIVE1, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)INERTIALESSDRIVE1, 2);

				memcpy((void *)INERTIALESSDRIVE1, "\xEB\x00", 2);

				VirtualProtect((void *)INERTIALESSDRIVE1, 2, oldProtect, &oldProtect);
				VirtualProtect((void *)INERTIALESSDRIVE2, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)INERTIALESSDRIVE2, 2);

				memcpy((void *)INERTIALESSDRIVE2, "\xEB\x01", 2);

				VirtualProtect((void *)INERTIALESSDRIVE2, 2, oldProtect, &oldProtect);
			}
			else
			{
				ConsoleOutput("Inertialess Drive off");

				VirtualProtect((void *)INERTIALESSDRIVE1, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)INERTIALESSDRIVE1, 2);

				memcpy((void *)INERTIALESSDRIVE1, "\x89\x16", 2);

				VirtualProtect((void *)INERTIALESSDRIVE1, 2, oldProtect, &oldProtect);
				VirtualProtect((void *)INERTIALESSDRIVE2, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)INERTIALESSDRIVE2, 2);

				memcpy((void *)INERTIALESSDRIVE2, "\x89\x46", 2);

				VirtualProtect((void *)INERTIALESSDRIVE2, 2, oldProtect, &oldProtect);
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('1') & 0x8000))
		{
			anchor = !anchor;

			if(anchor)
			{
				ConsoleOutput("Anchor on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Anchor, 0, 0, 0);
			}
			else
				ConsoleOutput("Anchor off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('2') & 0x8000))
		{
			petMode = !petMode;

			if(petMode)
			{
				ConsoleOutput("Pet Mode on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&PetMode, 0, 0, 0);
			}
			else
				ConsoleOutput("Pet Mode off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('3') & 0x8000))
		{
			if(MyZCharacter())
			{
				me.id = MyId();
				myChannel.id = MyChannelId();
				myStage.id = MyStageId();

				ZPostStageLeaveBattle(&me, &myStage);
				ZPostChannelRequestJoin(&me, &myChannel);

				ConsoleOutput("Returned to channel");
			}
			else
				ConsoleOutput("You are not in a game, you can't return to your channel until you are");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('4') & 0x8000))
		{
			wings = !wings;

			if(wings)
			{
				ConsoleOutput("Wings on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Wings, 0, 0, 0);
			}
			else
				ConsoleOutput("Wings off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('5') & 0x8000))
		{
			dashVortex = !dashVortex;

			if(dashVortex)
			{
				ConsoleOutput("Dash Vortex on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&DashVortex, 0, 0, 0);
			}
			else
				ConsoleOutput("Dash Vortex off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('6') & 0x8000))
		{
			circleSlowestVortex = !circleSlowestVortex;

			if(circleSlowestVortex)
			{
				ConsoleOutput("Circle Vortex (Slowest) on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&CircleSlowestVortex, 0, 0, 0);
			}
			else
				ConsoleOutput("Circle Vortex (Slowest) off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('7') & 0x8000))
		{
			circleMediumVortex = !circleMediumVortex;

			if(circleMediumVortex)
			{
				ConsoleOutput("Circle Vortex (Medium) on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&CircleMediumVortex, 0, 0, 0);
			}
			else
				ConsoleOutput("Circle Vortex (Medium) off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('8') & 0x8000))
		{
			circleFastestVortex = !circleFastestVortex;

			if(circleFastestVortex)
			{
				ConsoleOutput("Circle Vortex (Fastest) on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&CircleFastestVortex, 0, 0, 0);
			}
			else
				ConsoleOutput("Circle Vortex (Fastest) off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('9') & 0x8000))
		{
			wheelVortex = !wheelVortex;

			if(wheelVortex)
			{
				ConsoleOutput("Wheel Vortex on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&WheelVortex, 0, 0, 0);
			}
			else
				ConsoleOutput("Wheel Vortex off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('A') & 0x8000))
		{
			aimbot = !aimbot;

			if(aimbot)
			{
				ConsoleOutput("Aimbot on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Aimbot, 0, 0, 0);
			}
			else
				ConsoleOutput("Aimbot off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('B') & 0x8000))
		{
			paperWalls = !paperWalls;

			if(paperWalls)
			{
				ConsoleOutput("Paper Walls on");

				VirtualProtect((void *)PAPERWALLS, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)PAPERWALLS, 2);

				memcpy((void *)PAPERWALLS, "\xEB\x04", 2);

				VirtualProtect((void *)PAPERWALLS, 2, oldProtect, &oldProtect);
			}
			else
			{
				ConsoleOutput("Paper Walls off");

				VirtualProtect((void *)PAPERWALLS, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)PAPERWALLS, 2);

				memcpy((void *)PAPERWALLS, "\xD9\x9E", 2);

				VirtualProtect((void *)PAPERWALLS, 2, oldProtect, &oldProtect);
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('C') & 0x8000))
		{
			if(MyZCharacter())
			{
				_snprintf(buf2, (1024 * 64) - 1, "Id: %u | Last attacker id: %u | Channel id: %u | Stage id: %u | Peers: %u", MyId(), GetLastAttackerId(MyZCharacter()), MyChannelId(), MyStageId(), totalPeers);

				ConsoleOutput(buf2);

				memset(buf2, 0, 1024 * 64);

				_snprintf(buf2, (1024 * 64) - 1, "Name: %s | Clan: %s | Current HP: %u | Current AP: %u", GetCharName(MyZCharacter()), GetClanName(MyZCharacter()), GetHP(MyZCharacter()), GetAP(MyZCharacter()));

				ConsoleOutput(buf2);

				memset(buf2, 0, 1024 * 64);

				_snprintf(buf2, (1024 * 64) - 1, "Server name: %s | Channel name: %s", MyServerName(), MyChannelName());

				ConsoleOutput(buf2);

				memset(buf2, 0, 1024 * 64);

				_snprintf(buf2, (1024 * 64) - 1, "Map name: %s | Stage name: %s", MyMapName(), MyStageName());

				ConsoleOutput(buf2);

				memset(buf2, 0, 1024 * 64);
			}
			else
				ConsoleOutput("You are not in a game, you can't show your character info until you are");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('D') & 0x8000))
		{
			switch(dllSpeed)
			{
				case 1:
					dllSpeed = 10;

					ConsoleOutput("Dll speed set to: 10 ms");

					break;

				case 10:
					dllSpeed = 50;

					ConsoleOutput("Dll speed set to: 50 ms");

					break;

				case 50:
					dllSpeed = 100;

					ConsoleOutput("Dll speed set to: 100 ms");

					break;

				case 100:
					dllSpeed = 1;

					ConsoleOutput("Dll speed set to: 1 ms");

					break;
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('E') & 0x8000))
		{
			nameEsp = !nameEsp;

			if(nameEsp)
			{
				ConsoleOutput("Name Esp on");

				VirtualProtect((void *)NAMEESP, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)NAMEESP, 2);

				memcpy((void *)NAMEESP, "\x90\x90", 2);

				VirtualProtect((void *)NAMEESP, 2, oldProtect, &oldProtect);
			}
			else
			{
				ConsoleOutput("Name Esp off");

				VirtualProtect((void *)NAMEESP, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)NAMEESP, 2);

				memcpy((void *)NAMEESP, "\xEB\x08", 2);

				VirtualProtect((void *)NAMEESP, 2, oldProtect, &oldProtect);
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('F') & 0x8000))
		{
			flipmower = !flipmower;

			if(flipmower)
			{
				ConsoleOutput("Flipmower on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Flipmower, 0, 0, 0);
			}
			else
				ConsoleOutput("Flipmower off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('G') & 0x8000))
		{
			godmode = !godmode;

			if(godmode)
			{
				ConsoleOutput("Godmode on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Godmode, 0, 0, 0);
			}
			else
				ConsoleOutput("Godmode off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('I') & 0x8000))
		{
			lungemower = !lungemower;

			if(lungemower)
			{
				ConsoleOutput("Lungemower on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Lungemower, 0, 0, 0);
			}
			else
				ConsoleOutput("Lungemower off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('J') & 0x8000))
		{
			botRoom = !botRoom;

			if(botRoom)
			{
				ConsoleOutput("Room-wide bot on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&BotRoom, 0, 0, 0);
			}
			else
				ConsoleOutput("Room-wide bot off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('K') & 0x8000))
		{
			roomRape = !roomRape;

			if(roomRape)
			{
				ConsoleOutput("Room Rape on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&RoomRape, 0, 0, 0);
			}
			else
				ConsoleOutput("Room Rape off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('L') & 0x8000))
		{
			lawnmower = !lawnmower;

			if(lawnmower)
			{
				ConsoleOutput("Lawnmower on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Lawnmower, 0, 0, 0);
			}
			else
				ConsoleOutput("Lawnmower off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('M') & 0x8000))
		{
			insaneMassives = !insaneMassives;

			if(insaneMassives)
			{
				ConsoleOutput("Insane Massives on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&InsaneMassives, 0, 0, 0);
			}
			else
				ConsoleOutput("Insane Massives off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('N') & 0x8000))
		{
			me.id = MyId();
			myStage.id = MyStageId();

			ZPostStageTeam(&me, &myStage, team);

			char *buf = new char[1024];

			team++;

			if(team > 4)
				team = 0;

			_snprintf(buf, (1024 * 64) - 1, "Switched to team: %u", team);

			ConsoleOutput(buf);

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('O') & 0x8000))
		{
			if(MyZCharacter())
			{
				ConsoleOutput("Kamikaze deployed");

				ZPostPeerChat("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t", 0);
			}
			else
				ConsoleOutput("You are not in a game, you can't deploy Kamikaze until you are");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('P') & 0x8000))
		{
			powerLevel = !powerLevel;

			if(powerLevel)
			{
				ConsoleOutput("Power Level on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&PowerLevel, 0, 0, 0);
			}
			else
				ConsoleOutput("Power Level off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('Q') & 0x8000))
		{
			safeguard = !safeguard;

			if(safeguard)
			{
				ConsoleOutput("Safeguard on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Safeguard, 0, 0, 0);
			}
			else
				ConsoleOutput("Safeguard off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('R') & 0x8000))
		{
			bubbleAura = !bubbleAura;

			if(bubbleAura)
			{
				ConsoleOutput("Bubble Aura on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&BubbleAura, 0, 0, 0);
			}
			else
				ConsoleOutput("Bubble Aura off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('S') & 0x8000))
		{
			speedHack = !speedHack;

			if(speedHack)
			{
				ConsoleOutput("Speed Hack on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&SpeedHack, 0, 0, 0);
			}
			else
				ConsoleOutput("Speed Hack off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('T') & 0x8000))
		{
			medicator = !medicator;

			if(medicator)
			{
				ConsoleOutput("Medicator on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Medicator, 0, 0, 0);
			}
			else
				ConsoleOutput("Medicator off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('U') & 0x8000))
		{
			lastAttacker = !lastAttacker;

			if(lastAttacker)
				ConsoleOutput("Last attacker on");

			else
				ConsoleOutput("Last attacker off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('V') & 0x8000))
		{
			bot = !bot;

			if(bot)
			{
				ConsoleOutput("Bot on");
				
				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Bot, 0, 0, 0);
			}
			else
				ConsoleOutput("Bot off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('W') & 0x8000))
		{
			wallHack = !wallHack;

			if(wallHack)
			{
				ConsoleOutput("Wall Hack on");

				VirtualProtect((void *)WALLHACK, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)WALLHACK, 5);

				memcpy((void *)WALLHACK, "\x90\x90\x90\x90\x90", 5);

				VirtualProtect((void *)WALLHACK, 5, oldProtect, &oldProtect);
			}
			else
			{
				ConsoleOutput("Wall Hack off");

				VirtualProtect((void *)WALLHACK, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)WALLHACK, 5);

				memcpy((void *)WALLHACK, "\x89\x32\x89\x42\x04", 5);

				VirtualProtect((void *)WALLHACK, 5, oldProtect, &oldProtect);
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('X') & 0x8000))
			ExitFreebase();

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('Y') & 0x8000))
		{
			reloadSpam = !reloadSpam;

			if(reloadSpam)
			{
				ConsoleOutput("Reload Spam on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ReloadSpam, 0, 0, 0);
			}
			else
				ConsoleOutput("Reload Spam off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState('Z') & 0x8000))
		{
			instantMassives = !instantMassives;

			if(instantMassives)
			{
				ConsoleOutput("Instant Massives on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&InstantMassives, 0, 0, 0);
			}
			else
				ConsoleOutput("Instant Massives off");

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_DELETE) & 0x8000)
		{
			if(MyZCharacter())
			{
				me.id = MyId();
				myStage.id = MyStageId();

				ZPostStageLeaveBattle(&me, &myStage);
				ZPostRequestStageJoin(&me, &myStage);

				ConsoleOutput("Returned to stage");
			}
			else
				ConsoleOutput("You are not in a game, you can't return to stage until you are");


			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_END) & 0x8000)
		{
			if(MyZCharacter())
			{
				SetPosition(savedPosition);

				ConsoleOutput("Teleported to the saved position");
			}
			else
				ConsoleOutput("You are not in a game, you can't teleport to the saved position until you are");

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_HOME) & 0x8000)
		{
			medicineHat = !medicineHat;

			if(medicineHat)
			{
				ConsoleOutput("Medicine Hat on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MedicineHat, 0, 0, 0);
			}
			else
				ConsoleOutput("Medicine Hat off");

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_INSERT) & 0x8000)
		{
			if(MyZCharacter())
			{
				memcpy(savedPosition, GetPosition(MyZCharacter()), sizeof(savedPosition));

				ConsoleOutput("Position saved");
			}
			else
				ConsoleOutput("You are not in a game, you can't save your current position until you are");

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_NEXT) & 0x8000)
		{
			medicineHatLastAttacker = !medicineHatLastAttacker;

			if(medicineHatLastAttacker)
			{
				ConsoleOutput("Last attacker Medicine Hat on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MedicineHatLastAttacker, 0, 0, 0);
			}
			else
				ConsoleOutput("Last attacker Medicine Hat off");

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_PRIOR) & 0x8000)
		{
			medicineHatRoom = !medicineHatRoom;

			if(medicineHatRoom)
			{
				ConsoleOutput("Room-wide Medicine Hat on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MedicineHatRoom, 0, 0, 0);
			}
			else
				ConsoleOutput("Room-wide Medicine Hat off");

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_MULTIPLY) & 0x8000)
		{
			if(MyZCharacter())
			{
				ConsoleOutput("N-Stepped out");;

				me.id = MyId();
				myStage.id = MyStageId();

				ZPostStageLeaveBattle(&me, &myStage);
			}
			else
			{
				ConsoleOutput("You are not in a game, you can't N-Step out until you are");

				Sleep(1000);
			}

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_SUBTRACT) & 0x8000)
		{
			if(MyZCharacter())
			{
				ConsoleOutput("Rejoined the game");

				me.id = MyId();
				myStage.id = MyStageId();

				ZPostStageLeaveBattle(&me, &myStage);
				ZPostStageEnterBattle(&me, &myStage);
			}
			else
			{
				ConsoleOutput("You are not in a game, you can't rejoin the game until you are");

				Sleep(1000);
			}

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_ADD) & 0x8000)
		{
			if(MyZCharacter())
			{
				me.id = MyId();
				myStage.id = MyStageId();

				ZPostStageEnterBattle(&me, &myStage);

				ConsoleOutput("N-Stepped in");
			}
			else
				ConsoleOutput("You are not in a game, you can't N-Step in until you are");

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_NUMPAD0) & 0x8000)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MedicineCubeMega, 0, 0, 0);

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MedicineCubeSmall, 0, 0, 0);

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MedicineLoop, 0, 0, 0);

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
		{
			if(MyZCharacter())
			{
				float position[3];

				memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

				position[2] -= 100;

				SetPosition(position);
			}
			else
			{
				ConsoleOutput("You are not in a game, you can't go down until you are");

				Sleep(1000);
			}
		}

		if(GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MedicineCubeMedium, 0, 0, 0);

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_NUMPAD5) & 0x8000)
		{
			if(MyZCharacter())
			{
				float direction[3];
				float position[3];

				memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));
				memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

				me.id = MyId();

				position[2] += 170;
				position[0] += direction[0] * 1000;
				position[1] += direction[1] * 1000;
				position[2] += direction[2] * 1000;

				ZPostRequestSpawnWorldItem(&me, currentMedicine, position);
			}
			else
			{
				ConsoleOutput("You are not in a game, you can't use Penwrite until you are");

				Sleep(1000);
			}
		}

		if(GetAsyncKeyState(VK_NUMPAD6) & 0x8000)
		{
			if(MyZCharacter())
			{
				float direction[3];
				float position[3];

				memcpy(direction, GetDirection(MyZCharacter()), sizeof(direction));
				memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

				me.id = MyId();

				position[2] += 170;
				position[0] += direction[0] * 5000;
				position[1] += direction[1] * 5000;
				position[2] += direction[2] * 5000;

				ZPostRequestSpawnWorldItem(&me, currentMedicine, position);
			}
			else
			{
				ConsoleOutput("You are not in a game, you can't use Longwrite until you are");

				Sleep(1000);
			}
		}

		if(GetAsyncKeyState(VK_NUMPAD7) & 0x8000)
		{
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&MedicineCubeLarge, 0, 0, 0);

			Sleep(1000);
		}

		if(GetAsyncKeyState(VK_NUMPAD8) & 0x8000)
		{
			if(MyZCharacter())
				LevelUp(MyZCharacter());

			else
			{
				ConsoleOutput("You are not in a game, you can't level up until you are");

				Sleep(1000);
			}
		}

		if(GetAsyncKeyState(VK_NUMPAD9) & 0x8000)
		{
			if(MyZCharacter())
			{
				float position[3];

				memcpy(position, GetPosition(MyZCharacter()), sizeof(position));

				position[2] += 100;

				SetPosition(position);
			}
			else
			{
				ConsoleOutput("You are not in a game, you can't go up until you are");

				Sleep(1000);
			}
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('A') & 0x8000))
		{
			coloredTextures = !coloredTextures;

			if(coloredTextures)
				ConsoleOutput("Colored textures on");

			else
				ConsoleOutput("Colored textures off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('B') & 0x8000))
		{
			wireframe = !wireframe;

			if(wireframe)
				ConsoleOutput("Wireframe on");

			else
				ConsoleOutput("Wireframe off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('C') & 0x8000))
		{
			color++;

			if(color > COLOR_PURPLE)
				color = COLOR_ORANGE;

			_snprintf(buf2, (1024 * 64) - 1, "Current color: %d", color);

			ConsoleOutput(buf2);

			memset(buf2, 0, 1024 * 64);

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('D') & 0x8000))
		{
			noFog = !noFog;

			if(noFog)
				ConsoleOutput("No Fog on");

			else
				ConsoleOutput("No Fog off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('E') & 0x8000))
		{
			xray = !xray;

			if(xray)
				ConsoleOutput("X-Ray on");

			else
				ConsoleOutput("X-Ray off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('F') & 0x8000))
		{
			noMassives = !noMassives;

			if(noMassives)
			{
				ConsoleOutput("No Massives on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&NoMassives, 0, 0, 0);
			}
			else
				ConsoleOutput("No Massives off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('G') & 0x8000))
		{
			sunMassives = !sunMassives;

			if(sunMassives)
			{
				ConsoleOutput("Sun Massives on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&SunMassives, 0, 0, 0);
			}
			else
				ConsoleOutput("Sun Massives off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('H') & 0x8000))
		{
			sunMassives = !sunMassives;

			if(MyStageId() && !MyZCharacter())
			{
				ConsoleOutput("Mega Stage deployed");

				stage.x1 = 0;
				stage.x2 = 0;
				stage.x3 = 0;
				stage.gap = 0;
				stage.lateJoin = true;
				stage.mode1 = false;
				stage.mode2 = false;
				stage.mode3 = false;
				stage.mode4 = false;
				stage.players = 127;
				stage.rounds = 65535;
				stage.teamBalance = false;
				stage.friendlyFire = false;
				stage.minutes = 65535;

				strcpy(stage.mapName, "Shower Room");

				me.id = MyId();
				me.zero = 0;

				myStage.id = MyStageId();
				myStage.zero = 0;

				ZPostStageSetting(&me, &myStage, &stage);
			}
			else
				ConsoleOutput("You are not in a stage, you can't deploy Mega Stage until you are");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('I') & 0x8000))
		{
			fragmentationGrenadeSpam = !fragmentationGrenadeSpam;

			if(fragmentationGrenadeSpam)
			{
				ConsoleOutput("Fragmentation Grenade Spam on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&FragmentationGrenadeSpam, 0, 0, 0);
			}
			else
				ConsoleOutput("Fragmentation Grenade Spam off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('J') & 0x8000))
		{
			rocketSpam = !rocketSpam;

			if(rocketSpam)
			{
				ConsoleOutput("Rocket Spam on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&RocketSpam, 0, 0, 0);
			}
			else
				ConsoleOutput("Rocket Spam off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('K') & 0x8000))
		{
			chams = !chams;

			if(chams)
				ConsoleOutput("Chams on");

			else
				ConsoleOutput("Chams off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('L') & 0x8000))
		{
			flashbangSpam = !flashbangSpam;

			if(flashbangSpam)
			{
				ConsoleOutput("Flashbang Spam on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&FlashbangSpam, 0, 0, 0);
			}
			else
				ConsoleOutput("Flashbang Spam off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('M') & 0x8000))
		{
			smokeGrenadeSpam = !smokeGrenadeSpam;

			if(smokeGrenadeSpam)
			{
				ConsoleOutput("Smoke Grenade Spam on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&SmokeGrenadeSpam, 0, 0, 0);
			}
			else
				ConsoleOutput("Smoke Grenade Spam off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('N') & 0x8000))
		{
			shotSpam = !shotSpam;

			if(shotSpam)
			{
				ConsoleOutput("Shot Spam on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ShotSpam, 0, 0, 0);
			}
			else
				ConsoleOutput("Shot Spam off");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('O') & 0x8000))
		{
			hideIRC = !hideIRC;

			if(hideIRC)
			{
				ConsoleOutput("IRC off");

				_snprintf(buf, (1024 * 64) - 1, "PRIVMSG #freebase :%cACTION just turned IRC off%c\r\n", 1, 1);

				irc->Send(buf);

				memset(buf, 0, 1024 * 64);
			}
			else
			{
				ConsoleOutput("IRC on");

				_snprintf(buf, (1024 * 64) - 1, "PRIVMSG #freebase :%cACTION just turned IRC on%c\r\n", 1, 1);

				irc->Send(buf);

				memset(buf, 0, 1024 * 64);
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('P') & 0x8000))
		{
			ZPostRequestSpawn(0, MyId(), GetPosition(MyZCharacter()), GetDirection(MyZCharacter()));

			ConsoleOutput("Respawned");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('Q') & 0x8000))
		{
			memcpy(suicide, (void *)SUICIDE, 2);

			VirtualProtect((void *)SUICIDE, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

			FlushInstructionCache(GetCurrentProcess(), (void *)SUICIDE, 2);

			memcpy((void *)SUICIDE, "\xEB\x01", 2);

			VirtualProtect((void *)SUICIDE, 2, oldProtect, &oldProtect);

			ConsoleOutput("Suicided");

			Sleep(1000);

			VirtualProtect((void *)SUICIDE, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

			FlushInstructionCache(GetCurrentProcess(), (void *)SUICIDE, 2);

			memcpy((void *)SUICIDE, suicide, 2);

			VirtualProtect((void *)SUICIDE, 2, oldProtect, &oldProtect);

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('R') & 0x8000))
		{
			smokeTrail = !smokeTrail;

			if(smokeTrail)
			{
				VirtualProtect((void *)SMOKETRAIL, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)SMOKETRAIL, 2);

				memcpy((void *)SMOKETRAIL, "\xEB\x01", 2);

				VirtualProtect((void *)SMOKETRAIL, 2, oldProtect, &oldProtect);

				ConsoleOutput("Smoke Trail on");
			}
			else
			{
				VirtualProtect((void *)SMOKETRAIL, 2, PAGE_EXECUTE_READWRITE, &oldProtect);

				FlushInstructionCache(GetCurrentProcess(), (void *)SMOKETRAIL, 2);

				memcpy((void *)SMOKETRAIL, "\x74\x1A", 2);

				VirtualProtect((void *)SMOKETRAIL, 2, oldProtect, &oldProtect);

				ConsoleOutput("Smoke Trail off");
			}

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('S') & 0x8000))
		{
			hideConsole = !hideConsole;

			if(hideConsole)
			{
				ConsoleOutput("Console off");

				_snprintf(buf, (1024 * 64) - 1, "PRIVMSG #freebase :%cACTION just turned the console off%c\r\n", 1, 1);

				irc->Send(buf);

				memset(buf, 0, 1024 * 64);
			}
			else
			{
				ConsoleOutput("Console on");

				_snprintf(buf, (1024 * 64) - 1, "PRIVMSG #freebase :%cACTION just turned the console on%c\r\n", 1, 1);

				irc->Send(buf);

				memset(buf, 0, 1024 * 64);
			}
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('T') & 0x8000))
		{
			antiKick = !antiKick;

			if(antiKick)
				ConsoleOutput("Anti-kick off");

			else
				ConsoleOutput("Anti-kick on");

			Sleep(1000);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('U') & 0x8000))
		{
			if(consolePosition < 112)
				consolePosition++;

			Sleep(50);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('V') & 0x8000))
		{
			if(consolePosition > 0)
				consolePosition--;

			Sleep(50);
		}

		if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('W') & 0x8000))
		{
			hurricane = !hurricane;

			if(hurricane)
			{
				ConsoleOutput("Hurricane on");

				CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Hurricane, 0, 0, 0);
			}
			else
				ConsoleOutput("Hurricane off");

			Sleep(1000);
		}

		if(exitStatus)
			break;

		Sleep(dllSpeed);
	}

	delete buf;
	delete buf2;
}

int _stdcall DllMain(HINSTANCE instance, unsigned long reason, void *reserved)
{
	if(reason == DLL_PROCESS_ATTACH)
	{
		HideModule(instance);

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&Main, 0, 0, 0);
	}
	else if(reason == DLL_PROCESS_DETACH)
	{
		if(!exitStatus)
			ExitFreebase();
	}

	return 1;
}