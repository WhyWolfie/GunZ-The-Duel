Disable Admin Halt (Same way as June 07)

    00479FB9 - CALL DWORD PTR DS:[EDX+58]

To

    00479FB9 - NOP



The first post failed. <br>
1. Custom map banners in lobby enabled. <br>
2. Custom map world items spawn position fixed. <br>
3. Custom maps enabled in clan war with injecting ClanWarMaps.dll <br>
4. Get exp with custom maps in clan war. <br>

Nothing changes from alpha codes. <br>

theduel.exe <br>


        00513E56     8A0D 88ECDD01  MOV CL,BYTE PTR DS:[1DDEC88]
        00513E74     0905 88ECDD01  OR DWORD PTR DS:[1DDEC88],EAX
        00513E7A     B9 5CECDD01    MOV ECX,01DDEC5C
        00513E9C     B8 5CECDD01    MOV EAX,01DDEC5C
        006173A0     A1 88ECDD01    MOV EAX,DWORD PTR DS:[1DDEC88]
        006173A8     A3 88ECDD01    MOV DWORD PTR DS:[1DDEC88],EAX
        00620D50     B9 5CECDD01    MOV ECX,01DDEC5C

        00513448     83F8 7F        CMP EAX,7F
        0051BF1A     83FE 7F        CMP ESI,7F
        0051B0AE     83FE 7F        CMP ESI,7F
        005134E8     83F8 7F        CMP EAX,7F
        004AE1E7     83FE 7F        CMP ESI,7F
        005134C2     83FE 7F        CMP ESI,7F
        00513528     83F8 7F        CMP EAX,7F
        004C74C9     83FF 7F        CMP EDI,7F
        00513508     83F8 7F        CMP EAX,7F
        0050A0BC     83FE 7F        CMP ESI,7F
        00513482     83FE 7F        CMP ESI,7F

        00513540     8A0D 7867DE01   MOV CL,BYTE PTR DS:[1DE6778]
        0051354F     8B15 7867DE01   MOV EDX,DWORD PTR DS:[1DE6778]
        0051355C     8915 7867DE01   MOV DWORD PTR DS:[1DE6778],EDX
        
        
MatchServer.exe <br>

        0045AB60     8A0D 0C619000            MOV CL,BYTE PTR DS:[90610C]
        0045AB6F     8B15 0C619000            MOV EDX,DWORD PTR DS:[90610C]
        0045AB7A     C705 E8AA7E00 64A35500   MOV DWORD PTR DS:[7EAAE8],0055A364
        0045AB89     BF ECAA7E00              MOV EDI,007EAAEC
        0045AB93     8915 0C619000            MOV DWORD PTR DS:[90610C],EDX
        0045ABA4     B8 E8AA7E00              MOV EAX,007EAAE8
        00551460     C705 E8AA7E00 64A35500   MOV DWORD PTR DS:[7EAAE8],0055A364

        0045A758     83F8 7F        CMP EAX,7F
        0041CEE6     83FE 7F        CMP ESI,7F
        0045BC05     83FE 7F        CMP ESI,7F
        0045B7CF     83F8 7F        CMP EAX,7F
        00482F7A     83FE 7F        CMP ESI,7F
        004799BC     83FE 7F        CMP ESI,7F
        0045A798     83F8 7F        CMP EAX,7F
        0045A778     83F8 7F        CMP EAX,7F
        0045A738     83F8 7F        CMP EAX,7F
        0041CF53     83FE 7F        CMP ESI,7F
        00426BEC     83FD 7F        CMP EBP,7F
        0048D21E     83FB 7F        CMP EBX,7F
        00446D15     83F8 7F        CMP EAX,7F
        0048215E     83FE 7F        CMP ESI,7F
        0045A7B8     83F8 7F        CMP EAX,7F (Clan War exp fix. Not included in alpha code.)

        0045A7D0     8A0D E0AA7E00            MOV CL,BYTE PTR DS:[7EAAE0]
        0045A7DF     8B15 E0AA7E00            MOV EDX,DWORD PTR DS:[7EAAE0]
        0045A7EC     8915 E0AA7E00            MOV DWORD PTR DS:[7EAAE0],EDX

[Custom maps in clan war instructions.] <br>
ClanWarMaps.dll for using custom maps in clan war. <br>
(http://www.microsoft.com/downloads/details.aspx?displaylang=en&FamilyID=a5c84275-3b97-4ab7-a40d-3802b2af5fc2 is needed. Do not need it when it is already installed.) <br>

ClanWarMaps.dll <br>

        100010FD   . 833D 50330010 14   CMP DWORD PTR DS:[10003350],14


Change 14 to the number of your maps. (Hex. Not +1.) bOnlyDuelMap is ignored.<br>
Inject ClanWarMaps.dll to your server.<br>












        
        
