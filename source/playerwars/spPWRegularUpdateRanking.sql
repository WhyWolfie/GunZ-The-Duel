USE [UGGunzDB]
GO

/****** Object:  StoredProcedure [dbo].[spPWRegularUpdateRanking]    Script Date: 10/22/2022 7:39:25 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[spPWRegularUpdateRanking] 				   
AS 
BEGIN 
     SET NOCOUNT ON 
  CREATE TABLE #pw_rank (rank INT IDENTITY, pw_id INT)

 INSERT INTO #pw_rank(pw_id)
 SELECT CID
 FROM PWCharacterInfo(NOLOCK)
 WHERE ((Wins <> 0) OR (Losses <> 0))
 ORDER BY SCORE DESC

 UPDATE PWCharacterInfo
 SET Ranking = cr.rank
 FROM #pw_rank cr
 WHERE CID = cr.pw_id

 DROP TABLE #pw_rank
END

GO

