/****** Object:  StoredProcedure [dbo].[spPWRegularUpdateRanking]    Script Date: 09/13/2017 17:36:38 ******/
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

/****** Object:  StoredProcedure [dbo].[spPWOpen]    Script Date: 09/13/2017 17:36:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[spPWOpen]
AS
BEGIN
	SELECT TOP(1) Opened FROM PWStatus WHERE ID = 1;
END
GO
/****** Object:  StoredProcedure [dbo].[spPWGetCharacterInfo]    Script Date: 09/13/2017 17:36:38 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
-- =============================================
-- Author:		<Author,,Name>
-- Create date: <Create Date,,>
-- Description:	<Description,,>
-- =============================================
CREATE PROCEDURE [dbo].[spPWGetCharacterInfo]
	@CID int
AS
BEGIN
	SET NOCOUNT ON;
     IF NOT EXISTS(SELECT NULL FROM dbo.PWCharacterInfo where CID=@CID) BEGIN   
		INSERT dbo.PWCharacterInfo(CID)
			SELECT	@CID
	END  
	
	SELECT top 1 * FROM PWCharacterInfo pw WITH (NOLOCK) WHERE	pw.CID = @CID
END
GO














