spGetAccountInfo :



    set ANSI_NULLS ON
    set QUOTED_IDENTIFIER ON
    GO
    ------------------------------------------------------------------------------------------------------------

    ALTER   PROC [dbo].[spGetAccountInfo]
       @Aid  int      
    ,   @serveriD int = 0
    AS    
    BEGIN  
     SET NOCOUNT ON    

     SELECT AID, UserID, UGradeID, Name, HackingType
     , DATEPART(yy, EndHackingBlockTime) AS HackBlockYear, DATEPART(mm, EndHackingBlockTime) AS HackBlockMonth    
     , DATEPART(dd, EndHackingBlockTime) AS HackBlockDay, DATEPART(hh, EndHackingBlockTime) AS HackBlockHour    
     , DATEPART(mi, EndHackingBlockTime) AS HackBlockMin
     , DATEDIFF(mi, GETDATE(), EndHackingBlockTime) AS 'HackingBlockTimeRemainderMin'
     , IsPowerLevelingHacker
     , DATEDIFF(mi, PowerLevelingRegDate, GETDATE()) AS 'PowerLevelingRegPassedTimeMin'
     , VIPWalls, LastVIPWall
     FROM Account(NOLOCK) WHERE AID =   @Aid      

     update Account set LastLoginTime = getdate(), ServerID =   @serveriD  where aid =   @Aid  
    END

spUpdateAccountLastLogoutTime

    set ANSI_NULLS ON
    set QUOTED_IDENTIFIER ON
    GO
    ALTER proc [dbo].[spUpdateAccountLastLogoutTime]
       @Aid int
    ,   @VIPWalls int
    , @LastVIPWall int
    as
     set nocount on

     update Account set LastLogoutTime = getdate(),
     VIPWalls =   @VIPWalls, LastVIPWall = @LastVIPWall where AID =   @Aid
     
Click on 'execute'

![execute](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/fix%20nationalgunz%20vipwall/1.png)


Find these <br>

![stored](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/fix%20nationalgunz%20vipwall/2.png)


Then go to Account > Modify(Design) add these <br>
Account -> VIPWalls, LastVIPWall <br>
Datatype -> int <br>
Default Value or binding -> 0 <br>
Picture : <br>

![vipwall](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/fix%20nationalgunz%20vipwall/4.png)

![vipwall2](https://raw.githubusercontent.com/WhyWolfie/GunZ-The-Duel/master/source/fix%20nationalgunz%20vipwall/3.png)

Then Save and open Account , then make VIPWalls , LastVIPWalls 60 for both and enjoy using VIP Wall <br>

![vipwall3](https://github.com/WhyWolfie/GunZ-The-Duel/blob/master/source/fix%20nationalgunz%20vipwall/5.png)
























