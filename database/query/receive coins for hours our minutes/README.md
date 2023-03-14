    USE [GunzDB]
    GO
    SET ANSI_NULLS ON
    GO
    SET QUOTED_IDENTIFIER ON
    GO
    ALTER PROC [dbo].[spUpdateCharPlayTime]
       @PlaytimeInc    int,
       @Cid            int
    AS
    SET NOCOUNT ON
    DECLARE @Coins int
    DECLARE  @Aid int
    SELECT  @Aid=AID FROM Character(nolock) WHERE CID =  @Cid

    BEGIN

    SELECT @Coins =  @PlaytimeInc / 18000 /* Time add here*/

    UPDATE Character 
    SET PlayTime=PlayTime+  @PlaytimeInc), LastTime=GETDATE() 
    WHERE CID  @Cid

    UPDATE Account 
    SET Coins = Coins+(@Coins) 
    WHERE AID =  @Aid
    END
