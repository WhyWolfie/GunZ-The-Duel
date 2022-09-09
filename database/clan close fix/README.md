Well until finally I solved <br>
/clan close <nameclan> <br>
  
    USE [GunzDB] 
    GO 
    /****** Objeto:  StoredProcedure [dbo].[spReserveCloseClan]    Fecha de la secuencia de comandos: 02/23/2013 16:04:20 ******/ 
    SET ANSI_NULLS ON 
    GO 
    SET QUOTED_IDENTIFIER ON 
    GO 
    ALTER PROC [dbo].[spReserveCloseClan] 
    @CLID int 
    , @ClanName varchar(24) 
    , @MasterCID int 
    , @DeleteDate varchar(24) 
    AS 
    UPDATE Clan SET DeleteFlag=1, Name=NULL, DeleteName=@ClanName WHERE CLID=@CLID AND MasterCID=@MasterCID 
    DELETE FROM ClanMember WHERE CLID=@CLID 
  
  System->Message.xml

    <MSG id="1108"> This clan is dissolved. Please relog. </ Msg> 
