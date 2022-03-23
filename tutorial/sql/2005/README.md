<b>[SQL 2005]</b>
- SQL Management Studio Express: https://www.microsoft.com/en-us/download/details.aspx?id=14630
- SQL Server Express(x64): https://download.cnet.com/Microsoft-SQL-Server-2005-Express-Edition-Service-Pack-4/3001-10254_4-75452276.html
- Alternative SQL Server/Express(2005) Link: https://archive.org/details/SQLEXPR (both files)
- .NET Framework 2.0: https://www.microsoft.com/en-US/download/details.aspx?id=16614 (If you cant install)
- Database (GunZ 1.5): https://github.com/WhyWolfie/GunZ-The-Duel/tree/master/database/1.5

<b>[Setup - SQL Server Express]</b><br>
1. Press Setup -> Extracting Files <br>
![sqll](https://i.imgur.com/nl9KbWF.png)<br>
2. Press -> Yes <br>
![sqll2](https://i.imgur.com/PyEKOnf.png)<br>
3. Click on -> I accept the licensing terms and conditions -> Next ><br>
![sqll3](https://i.imgur.com/XmYFKhS.png)<br>
4. Press -> Install <br>
![sqll4](https://i.imgur.com/FPKqk4X.png)<br>
5. Press -> Next > <br>
![sqll5](https://i.imgur.com/uMBQXIh.png)<br>
6. Press -> Next > <br>
![sqll6](https://i.imgur.com/tUPCNbC.png)<br>
7. Press -> Next > <br>
![sqll7](https://i.imgur.com/MGPweUL.png)<br>
8. Fill in your name or Skip -> Next > <br>
![sqll8](https://i.imgur.com/rx3lNEj.png) <br>
9. Press -> Next > <br>
![sqll9](https://i.imgur.com/1Weh7Y0.png) <br>
10. Turn on Mixed Mode -> Enter Your Password -> Next >
![sqll10](https://i.imgur.com/Uh9UfGd.png) <br>
11. Press -> Next > <br>
![sqll11](https://i.imgur.com/FuCHRJ1.png) <br>
12. Press -> Next > <br>
![sqll12](https://i.imgur.com/j5Jt4A5.png) <br>
13. Press -> Install <br>
![sqll13](https://i.imgur.com/m3LJNki.png) <br>
14. Press -> Next >> <br>
![sqll14](https://i.imgur.com/j6tKAq1.png) <br>
15. Last time press -> Finish <br>
![sqll15](https://i.imgur.com/Q89l2fx.png) <br>
SQL Server Installed!<br>

<b>[Setup - SQL Management Studio Express]</b><br>
1. Click on Next ><br>
![sql](https://i.imgur.com/AV00KFi.png)<br>
2. I accept the terms in the license agreement -> Next ><br>
![sql2](https://i.imgur.com/IWIjEYP.png)<br>
3. Fill ur name or skip -> Next ><br>
![sql3](https://i.imgur.com/bUDX8jJ.png)<br>
4. Click on Management Studio Express -> Next ><br>
![sql4](https://i.imgur.com/Qw0w4xq.png)<br>
5. Press -> Install<br>
![sql5](https://i.imgur.com/mkJPI3F.png)<br>
6. Press -> Yes <br>
![sql6](https://i.imgur.com/IUC58sF.png)<br>
7. Waiting...<br>
![sql7](https://i.imgur.com/E21KrtO.png)<br>
8. Completed!<br>
![sql8](https://i.imgur.com/7kKc8R5.png)<br>
SQL Management Studio Express Installed!<br>

<b>[Login into SQL Server 2005]</b><br>
1. Check your Username<br>
![sqlserver](https://i.imgur.com/3LhjlMK.png)<br>
2. Authentication -> SQL Server Authentication<br>
![sqlserver2](https://i.imgur.com/yt6H207.png) <br>
3. Login: SA - Password: YOURPWD<br>
4. Press -> Remember Password -> Connect<br>
![sqlserver3](https://i.imgur.com/cnBXCSW.png)<br>

<b>[Setup Database]</b>
1. Database -> New Database... <br>
![db](https://i.imgur.com/oVtXpHe.png) <br>
2. Database name: 'GunzDB' -> Press on Ok <br>
![db2](https://i.imgur.com/jMDOs5p.png) <br>
3. Database created 'GunzDB' <br>
![db3](https://i.imgur.com/zqavfs4.png) <br>
4. Extract 'GunZDBFixed.zip' drag GunZDBFixed.sql in Microsoft SQL Server Management Studio Express <br>
![db4](https://i.imgur.com/K2nN6Vg.png) <br>
5. Set on 'GunzDB' -> After click on 'Execute' will load for a few mins
6. You will see this message 'Msg 3701, Level 11, State 5, Line 21' few 1 row (s) affected, so it's loaded
![db5](https://i.imgur.com/Y58QyOU.png) <br>

<b>[Setup Account]</b><br>
1. GunzDB -> Tables -> dbo.Account<br>
![acc](https://i.imgur.com/A3G5jVp.png)<br>
2. right mouse on 'dbo.Account' -> Open Table <br>
![acc2](https://i.imgur.com/i5TGRmB.png)<br>
3. Fill in the tables <br>
![acc3](https://i.imgur.com/7TbwETq.png)<br>
4. UserID: Test - UGradeID 255 - PGradeID 0 - RegDate: 3/23/2022 12:00:00 AM - Name: Test <br>
![acc4](https://i.imgur.com/YLXrCXU.png) <br>
5. Then you click on the other table so you now have a line <br>
6. Close the tab (dbo.Account) -> Reopen (dbo.Account)<br>
![acc6](https://i.imgur.com/92AGM3B.png)<br>
7. Look at 'AID' ID and remember that ID for me it is '2'<br>
![acc7](https://i.imgur.com/gkfK6Ae.png)<br>
8. Close the tab (dbo.Account) <br>
9. Scroll down if you find (dbo.Login) -> Open Table <br>
![acc8](https://i.imgur.com/eR7sms5.png)<br>
10. UserID: Test - AID (ur ID for me it was '2') - Password: 123(ur choice) - lastconndate: 3/23/2022 12:00:00 AM - 127.0.0.1 (localhost)
![acc9](https://i.imgur.com/TOkhzu7.png)<br>
11. Close the tab (dbo.Login) <br>
12. Well done your account is now created 🙃 <br>

<b>[Setup connection of the server]</b>
1. find 'dbo.ServerStatus' -> Open Table <br>
![server](https://i.imgur.com/OD97okS.png)<br>
2. Fill in the table <br>
![server2](https://i.imgur.com/CUcfGn1.png)<br>
3. ServerID: 1 - CurrPlayer: 0 - MaxPlayer: 50 (ur choice) - Time: 3/23/2022 12:00:00 AM - IP: 127.0.0.1 (localhost) - Port: 6000 <br>
3-2. Opened: 1 - Type: 4 - AgentIP: 127.0.0.1 - ServerName: GunZ -> Press other table and close it <br>
![server3](https://i.imgur.com/xCwPjij.png)<br>
4. Well done your server is now created 🙃 <br>





