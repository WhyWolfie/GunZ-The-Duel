Disable Admin Halt (Same way as June 07)

    00479FB9 - CALL DWORD PTR DS:[EDX+58]

To

    00479FB9 - NOP

------------------------------------------------------------------------------------

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



------------------------------------------------------------------------------------


[theduel11.exe]
1. Unmasked Administrator / Developer Names and Levels.
2. Unmasked duel chat.
3. 126 maps enabled.
4. .mef disabled.
5. File list disabled.
6. Serialkey enabled.
7. XTrap disabled.
8. Client sided hacking detection disabled.
9. Stage max players over 17 selectable.
10. Quest mode menu already enabled.
11. Client sided character limit changed to 1~16. (Private channel names character limit is 32.)

[theduel11_2.exe]
1. Unmasked Administrator / Developer Names and Levels.
2. Unmasked duel chat.
3. 126 maps enabled.
4. .mef disabled.
5. File list disabled.
6. Serialkey enabled.
7. XTrap disabled.
8. Client sided hacking detection disabled.

[Map instructions]
You must add map information to this file. :

        channelrule.xml
        map.xml

Custom maps banner is does not show up in lobby. (All Mansion.) <br>
Client editing is not needed. bOnlyDuelMap is not ignored. <br>

        
------------------------------------------------------------------------------------

1) Hacking detection edit... <br>
Client sided detection. (theduel.exe) : <br>

        I'm hacker.
        00498FAD     EB 33          JMP SHORT 00498FE2

        Hacking detected
        00436B24     EB 35          JMP SHORT 00436B5B
        0043DE24     EB 35          JMP SHORT 0043DE5B
        0043ED7F     75 00          JNZ SHORT 0043ED81
        0043ED88     EB 35          JMP SHORT 0043EDBF
        0043ED5F     75 00          JNZ SHORT 0043ED61

        A hacking attempt was detected.
        004414B4     E9 86000000    JMP 0044153F
        004414B9     90             NOP
        
        
Server sided detection. (MatchServer.exe) :

        Note :Not tested. You should test this...
        004050EE     EB 17          JMP SHORT 00405107
        00408C98     EB 09          JMP SHORT 00408CA3

        0040C252     E9 CD030000    JMP 0040C624
        0040C257     90             NOP

        00433201     EB 1D          JMP SHORT 00433220
        00449808     0F8C 00000000  JL 0044980E
        00449811     0F8D 00000000  JGE 00449817
        0044981A     0F84 00000000  JE 00449820
        

Unmasking admin / dev names. :


    // Lobby List
    00423B76     EB 04          JMP SHORT 00423B7C
    00423B78     90             NOP
    00423B79     90             NOP
    00423B7A     90             NOP
    00423B7B     90             NOP

    // Stage List
    00424D8A     8D0E           LEA ECX,DWORD PTR DS:[ESI]
    00424D8C     EB 02          JMP SHORT 00424D90
    00424D8E     90             NOP
    00424D8F     90             NOP

    // Tab List
    00407808     8D81 D8030000  LEA EAX,DWORD PTR DS:[ECX+3D8]
    0040780E     EB 01          JMP SHORT 00407811
    00407810     90             NOP

    // Lobby Chat
    004C43D7     8D07           LEA EAX,DWORD PTR DS:[EDI]
    004C43D9     EB 02          JMP SHORT 004C43DD
    004C43DB     90             NOP
    004C43DC     90             NOP

    // Stage Chat
    004C5F6A     8D57 0C        LEA EDX,DWORD PTR DS:[EDI+C]
    004C5F6D     EB 01          JMP SHORT 004C5F70
    004C5F6F     90             NOP

    // Game Chat
    004AAEE9     8D97 D8030000  LEA EDX,DWORD PTR DS:[EDI+3D8]

    // Team Chat
    004AAD6D     8D8E D8030000  LEA ECX,DWORD PTR DS:[ESI+3D8]

    // Level Up and Down
    004C81A0     EB 04          JMP SHORT 004C81A6
    004C81A2     90             NOP
    004C81A3     90             NOP
    004C81A4     90             NOP
    004C81A5     90             NOP

    004C81BF     8D86 D8030000  LEA EAX,DWORD PTR DS:[ESI+3D8]
    004C81C5     EB 04          JMP SHORT 004C81CB
    004C81C7     90             NOP
    004C81C8     90             NOP
    004C81C9     90             NOP
    004C81CA     90             NOP

    004C8260     EB 04          JMP SHORT 004C8266
    004C8262     90             NOP
    004C8263     90             NOP
    004C8264     90             NOP
    004C8265     90             NOP

    004C827F     8D86 D8030000  LEA EAX,DWORD PTR DS:[ESI+3D8]
    004C8285     EB 04          JMP SHORT 004C828B
    004C8287     90             NOP
    004C8288     90             NOP
    004C8289     90             NOP
    004C828A     90             NOP

    // Head Name
    00403717     8D87 D8030000  LEA EAX,DWORD PTR DS:[EDI+3D8]
    0040371D     EB 07          JMP SHORT 00403726
    0040371F     90             NOP
    00403720     90             |NOP
    00403721     90             NOP
    00403722     90             NOP
    00403723     90             |NOP
    00403724     90             NOP
    00403725     90             NOP

    00403747     8D8F D8030000  LEA ECX,DWORD PTR DS:[EDI+3D8]

    00403753     EB 07          JMP SHORT 0040375C
    00403755     90             NOP
    00403756     90             |NOP
    00403757     90             NOP
    00403758     90             NOP
    00403759     90             |NOP
    0040375A     90             NOP
    0040375B     90             NOP

    0041047B     8D86 D8030000  LEA EAX,DWORD PTR DS:[ESI+3D8]
    00410481     EB 07          JMP SHORT 0041048A
    00410483     90             NOP
    00410484     90             NOP
    00410485     90             NOP
    00410486     90             NOP
    00410487     90             |NOP
    00410488     90             NOP
    00410489     90             NOP

    004104AB     8D8E D8030000  LEA ECX,DWORD PTR DS:[ESI+3D8]
    004104B1     EB 07          JMP SHORT 004104BA
    004104B3     90             NOP
    004104B4     90             |NOP
    004104B5     90             NOP
    004104B6     90             NOP
    004104B7     90             |NOP
    004104B8     90             NOP
    004104B9     90             NOP

    0040349B     8D87 D8030000  LEA EAX,DWORD PTR DS:[EDI+3D8]
    004034A1     EB 07          JMP SHORT 004034AA
    004034A3     90             NOP
    004034A4     90             |NOP
    004034A5     90             NOP
    004034A6     90             NOP
    004034A7     90             |NOP
    004034A8     90             NOP
    004034A9     90             NOP

    004034CB     8D8F D8030000  LEA ECX,DWORD PTR DS:[EDI+3D8]

    004034D7     EB 07          JMP SHORT 004034E0
    004034D9     90             NOP
    004034DA     90             |NOP
    004034DB     90             NOP
    004034DC     90             NOP
    004034DD     90             |NOP
    004034DE     90             NOP
    004034DF     90             NOP

    // Replay Name
    00410D1C     8DB9 D8030000  LEA EDI,DWORD PTR DS:[ECX+3D8]
    00410D22     EB 07          JMP SHORT 00410D2B
    00410D24     90             NOP
    00410D25     90             NOP
    00410D26     90             NOP
    00410D27     90             NOP
    00410D28     90             NOP
    00410D29     90             NOP
    00410D2A     90             NOP

    004114E3     8DB9 D8030000  LEA EDI,DWORD PTR DS:[ECX+3D8]
    004114E9     EB 07          JMP SHORT 004114F2
    004114EB     90             NOP
    004114EC     90             NOP
    004114ED     90             NOP
    004114EE     90             NOP
    004114EF     90             NOP
    004114F0     90             NOP
    004114F1     90             NOP

    // Killed Character Name
    004A8A76     8D87 D8030000  LEA EAX,DWORD PTR DS:[EDI+3D8]
    004A8A7C     EB 11          JMP SHORT 004A8A8F
    004A8A7E     90             NOP
    004A8A7F     90             NOP
    004A8A80     90             NOP
    004A8A81     90             NOP
    004A8A82     90             NOP
    004A8A83     90             NOP
    004A8A84     90             NOP
    004A8A85     90             NOP
    004A8A86     90             NOP
    004A8A87     90             NOP
    004A8A88     90             NOP
    004A8A89     90             NOP

    004A8AA6     8D86 D8030000  LEA EAX,DWORD PTR DS:[ESI+3D8]
    004A8AAC     EB 11          JMP SHORT 004A8ABF
    004A8AAE     90             NOP
    004A8AAF     90             NOP
    004A8AB0     90             NOP
    004A8AB1     90             NOP
    004A8AB2     90             NOP
    004A8AB3     90             NOP
    004A8AB4     90             NOP
    004A8AB5     90             NOP
    004A8AB6     90             NOP
    004A8AB7     90             NOP
    004A8AB8     90             NOP
    004A8AB9     90             NOP

    // Join and Leave
    004C7296     E9 92000000    JMP 004C732D
    004C729B     90             NOP

    004A91B9     8D93 D8030000  LEA EDX,DWORD PTR DS:[EBX+3D8]
    004A91BF     EB 0A          JMP SHORT 004A91CB
    004A91C1     90             NOP
    004A91C2     90             NOP
    004A91C3     90             NOP
    004A91C4     90             NOP
    004A91C5     90             NOP
    004A91C6     90             NOP
    004A91C7     90             NOP
    004A91C8     90             NOP
    004A91C9     90             NOP
    004A91CA     90             NOP

    004A92B7     8D92 D8030000  LEA EDX,DWORD PTR DS:[EDX+3D8]

    004A92D7     EB 0A          JMP SHORT 004A92E3
    004A92D9     90             NOP
    004A92DA     90             NOP
    004A92DB     90             NOP
    004A92DC     90             NOP
    004A92DD     90             NOP
    004A92DE     90             NOP
    004A92DF     90             NOP
    004A92E0     90             NOP
    004A92E1     90             NOP
    004A92E2     90             NOP

    // The Duel Match
    0040A677     8D87 D8030000  LEA EAX,DWORD PTR DS:[EDI+3D8]
    0040A67D     EB 07          JMP SHORT 0040A686
    0040A67F     90             NOP
    0040A680     90             NOP
    0040A681     90             NOP
    0040A682     90             NOP
    0040A683     90             NOP
    0040A684     90             NOP
    0040A685     90             NOP

    0040A78A     8D87 D8030000  LEA EAX,DWORD PTR DS:[EDI+3D8]
    0040A790     EB 07          JMP SHORT 0040A799
    0040A792     90             NOP
    0040A793     90             NOP
    0040A794     90             NOP
    0040A795     90             NOP
    0040A796     90             NOP
    0040A797     90             NOP
    0040A798     90             NOP

    0040A7E0     8D87 D8030000  LEA EAX,DWORD PTR DS:[EDI+3D8]
    0040A7E6     EB 07          JMP SHORT 0040A7EF
    0040A7E8     90             NOP
    0040A7E9     90             NOP
    0040A7EA     90             NOP
    0040A7EB     90             NOP
    0040A7EC     90             NOP
    0040A7ED     90             NOP
    0040A7EE     90             NOP

    0040A824     8D87 D8030000  LEA EAX,DWORD PTR DS:[EDI+3D8]
    0040A82A     EB 07          JMP SHORT 0040A833
    0040A82C     90             NOP
    0040A82D     90             NOP
    0040A82E     90             NOP
    0040A82F     90             NOP
    0040A830     90             NOP
    0040A831     90             NOP
    0040A832     90             NOP

    00410E84     8D8F D8030000  LEA ECX,DWORD PTR DS:[EDI+3D8]
    00410E8A     EB 07          JMP SHORT 00410E93
    00410E8C     90             NOP
    00410E8D     90             NOP
    00410E8E     90             NOP
    00410E8F     90             NOP
    00410E90     90             NOP
    00410E91     90             NOP
    00410E92     90             NOP

    00410F37     8D8F D8030000  LEA ECX,DWORD PTR DS:[EDI+3D8]
    00410F3D     EB 07          JMP SHORT 00410F46
    00410F3F     90             NOP
    00410F40     90             NOP
    00410F41     90             NOP
    00410F42     90             NOP
    00410F43     90             NOP
    00410F44     90             NOP
    00410F45     90             NOP

    00410FD9     8D8F D8030000  LEA ECX,DWORD PTR DS:[EDI+3D8]
    00410FDF     EB 07          JMP SHORT 00410FE8
    00410FE1     90             NOP
    00410FE2     90             NOP
    00410FE3     90             NOP
    00410FE4     90             NOP
    00410FE5     90             NOP
    00410FE6     90             NOP
    00410FE7     90             NOP

    // Result
    00405A6B     8D86 D8030000  LEA EAX,DWORD PTR DS:[ESI+3D8]
    00405A71     EB 07          JMP SHORT 00405A7A
    00405A73     90             NOP
    00405A74     90             |NOP
    00405A75     90             NOP
    00405A76     90             NOP
    00405A77     90             |NOP
    00405A78     90             NOP
    00405A79     90             NOP

    // Aim
    00402D21     8D8F D8030000  LEA ECX,DWORD PTR DS:[EDI+3D8]
    00402D27     EB 07          JMP SHORT 00402D30
    00402D29     90             NOP
    00402D2A     90             NOP
    00402D2B     90             NOP
    00402D2C     90             NOP
    00402D2D     90             NOP
    00402D2E     90             NOP
    00402D2F     90             NOP

    004031B3     8D82 D8030000  LEA EAX,DWORD PTR DS:[EDX+3D8]
    004031B9     EB 07          JMP SHORT 004031C2
    004031BB     90             NOP
    004031BC     90             NOP
    004031BD     90             NOP
    004031BE     90             NOP
    004031BF     90             NOP
    004031C0     90             NOP
    004031C1     90             NOP

    004031DA     8D80 D8030000  LEA EAX,DWORD PTR DS:[EAX+3D8]
    004031E0     EB 07          JMP SHORT 004031E9
    004031E2     90             NOP
    004031E3     90             NOP
    004031E4     90             NOP
    004031E5     90             NOP
    004031E6     90             NOP
    004031E7     90             NOP
    004031E8     90             NOP

    // Unknown
    004AAE16     8DB1 D8030000  LEA ESI,DWORD PTR DS:[ECX+3D8]
    004AAE1C     EB 01          JMP SHORT 004AAE1F
    004AAE1E     90             NOP

    004AAE25     EB 04          JMP SHORT 004AAE2B
    004AAE27     90             NOP
    004AAE28     90             NOP
    004AAE29     90             NOP
    004AAE2A     90             NOP

Unmasking admin / dev levels.

    // Lobby
    00423B62     C645 17 01     MOV BYTE PTR SS:[EBP+17],1
    00423B66     EB 1A          JMP SHORT 00423B82
    00423B68     90             NOP
    00423B69     90             NOP
    00423B6A     90             NOP
    00423B6B     90             NOP
    00423B6C     90             NOP
    00423B6D     90             NOP
    00423B6E     90             NOP
    00423B6F     90             NOP
    00423B70     90             NOP
    00423B71     90             NOP
    00423B72     90             NOP
    00423B73     90             NOP
    00423B74     90             NOP
    00423B75     90             NOP
    00423B76     90             NOP
    00423B77     90             NOP
    00423B78     90             NOP
    00423B79     90             NOP
    00423B7A     90             NOP
    00423B7B     90             NOP
    00423B7C     90             NOP
    00423B7D     90             NOP
    00423B7E     90             NOP
    00423B7F     90             NOP
    00423B80     90             NOP
    00423B81     90             NOP

    // Room
    00424D7F     C645 17 01     MOV BYTE PTR SS:[EBP+17],1
    00424D83     EB 1A          JMP SHORT 00424D9F
    00424D85     90             NOP
    00424D86     90             NOP
    00424D87     90             NOP
    00424D88     90             NOP
    00424D89     90             NOP
    00424D8A     90             NOP
    00424D8B     90             NOP
    00424D8C     90             NOP
    00424D8D     90             NOP
    00424D8E     90             NOP
    00424D8F     90             NOP
    00424D90     90             NOP
    00424D91     90             NOP
    00424D92     90             NOP
    00424D93     90             NOP
    00424D94     90             NOP
    00424D95     90             NOP
    00424D96     90             NOP
    00424D97     90             NOP
    00424D98     90             NOP
    00424D99     90             NOP
    00424D9A     90             NOP
    00424D9B     90             NOP
    00424D9C     90             NOP
    00424D9D     90             NOP
    00424D9E     90             NOP

    // Game result
    00405A80     EB 1D          JMP SHORT 00405A9F

    // Ranking
    00407811     C685 87FEFFFF >MOV BYTE PTR SS:[EBP-179],0FF
    00407818     C685 84FEFFFF >MOV BYTE PTR SS:[EBP-17C],0FF
    0040781F     C685 85FEFFFF >MOV BYTE PTR SS:[EBP-17B],80
    00407826     C685 86FEFFFF >MOV BYTE PTR SS:[EBP-17A],40
    0040782D     8B8D 84FEFFFF  MOV ECX,DWORD PTR SS:[EBP-17C]
    00407833     894F 7F        MOV DWORD PTR DS:[EDI+7F],ECX
    00407836     C687 83000000 >MOV BYTE PTR DS:[EDI+83],1
    0040783D     EB 2D          JMP SHORT 0040786C
    0040783F     90             NOP
    00407840     90             NOP
    00407841     90             NOP
    00407842     90             NOP
    00407843     90             NOP
    00407844     90             NOP
    00407845     90             NOP
    00407846     90             NOP
    00407847     90             NOP
    00407848     90             NOP
    00407849     90             NOP
    0040784A     90             NOP
    0040784B     90             NOP
    0040784C     90             NOP
    0040784D     90             NOP
    0040784E     90             NOP
    0040784F     90             NOP
    00407850     90             NOP
    00407851     90             NOP
    00407852     90             NOP
    00407853     90             NOP
    00407854     90             NOP
    00407855     90             NOP
    00407856     90             NOP
    00407857     90             NOP
    00407858     90             NOP
    00407859     90             NOP
    0040785A     90             NOP
    0040785B     90             NOP
    0040785C     90             NOP
    0040785D     90             NOP
    0040785E     90             NOP
    0040785F     90             NOP
    00407860     90             NOP
    00407861     90             NOP
    00407862     90             NOP

The Duel match chat block. :

    004C833B     EB 1C          JMP SHORT 004C8359
    004C900B     EB 2C          JMP SHORT 004C9039
    004AAEA8     EB 2E          JMP SHORT 004AAED8

Custom maps. :

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

.mef disabled. :

    004637D7  |. 6A 00          PUSH 0                                   ; /Arg2 = 00000000
    0048BFE5  |. 6A 00          PUSH 0                                   ; /Arg2 = 00000000
    00499C5A  |. 6A 00          PUSH 0                                   ; /Arg2 = 00000000
    00499C6D  |. 6A 00          PUSH 0                                   ; /Arg2 = 00000000
    00499C7C  |. 6A 00          PUSH 0                                   ; /Arg2 = 00000000
    0049A109  |. 6A 00          PUSH 0                                   ; /Arg2 = 00000000
    0049A5CF  |. 6A 00          PUSH 0                                   ; /Arg2 = 00000000
    004A08E5  |. 6A 00          PUSH 0                                   ; /Arg2 = 00000000
    
File list disabled. :

    00537964  |. 0F85 00000000  JNZ 0053796A

Serialkey enabled. :

    0049955B     75 51          JNZ SHORT 004995AE

XTrap disabled. :

    00498BE2   . EB 03          JMP SHORT 00498BE7
    00498BE4     90             NOP
    00498BE5     90             NOP
    00498BE6     90             NOP

    00498BF0   . EB 03          JMP SHORT 00498BF5
    00498BF2     90             NOP
    00498BF3     90             NOP
    00498BF4     90             NOP

    00498BF5   > EB 03          JMP SHORT 00498BFA
    00498BF7     90             NOP
    00498BF8     90             NOP
    00498BF9     90             NOP

Hacking detection. :

    00498FAD     EB 33          JMP SHORT 00498FE2
    00436B24     EB 35          JMP SHORT 00436B5B
    0043DE24     EB 35          JMP SHORT 0043DE5B
    0043ED7F     75 00          JNZ SHORT 0043ED81
    0043ED88     EB 35          JMP SHORT 0043EDBF
    0043ED5F     75 00          JNZ SHORT 0043ED61

    004414B4     E9 86000000    JMP 0044153F
    004414B9     90             NOP

Stage max players. :

    0045C279   . 7F 00          JG SHORT 0045C27B

Quest menu. :

    0045C741  |. 75 00          JNZ SHORT 0045C743

Character limits. :

    0042C96D  |. 83F8 01        CMP EAX,1
    0042C9C7  |> 83F8 10        CMP EAX,10
    0044D4A6  |> 83F8 01        CMP EAX,1
    0044D4CF  |> 83F8 10        CMP EAX,10
    0044EC43  |> 83F8 01        CMP EAX,1
    0044EC6B  |> 83F8 20        CMP EAX,20









        
        
        



