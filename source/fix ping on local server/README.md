1. open cmd.exe -> ipconfig -> IPv4 Address. . . . . . . . . . . : 192.xxx.xxx.xxx <-- copy this ip-address. <br>
![cmd](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/fix%20ping%20on%20local%20server/ipconfig.png)


2. edit system.xml (gunz/system(.mrs)/system.xml) & (matchserver/system.xml) replace all 127.0.0.1 too your ipv4 from ipconfig. <br>

![system](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/fix%20ping%20on%20local%20server/system.png)

3. Locator 

    Change your -> IP="192.168.xxx.xxx"

4. MatchAgent

     ADDRESS ip="192.168.xxx.xxx" <br>
     MATCHSERVERADDRESS ip="192.168.xxx.xxx" <br>
     
5. MatchServer

    FREELOGINIP="192.168.xxx.xxx" <br>
    KEEPERIP="192.168.xxx.xxx" <br>
    DEBUGIP="192.168.xxx.xxx" <br>
    MONITORIP="192.168.xxx.xxx" <br>
    
SQL -> DBO.ServerStatus -> IP/AgentIP: 127.0.0.1 to 192.168.xxx.xxx


![lowpingbruh](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/fix%20ping%20on%20local%20server/lowpingbruh.jpg)
