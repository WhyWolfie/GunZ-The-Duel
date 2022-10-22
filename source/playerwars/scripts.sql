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

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

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
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[PWGetSideRanking]
@cid int
AS
BEGIN
	SET NOCOUNT ON;
	DECLARE @CurRank	INT;
	DECLARE @TotalUser	INT;

	SELECT @CurRank = cr.Ranking
	FROM PWCharacterInfo cr (NOLOCK) 
	WHERE cr.CID = @CID;
	
	SELECT @TotalUser = COUNT(*) 
	FROM PWCharacterInfo cr (NOLOCK) 
	
-----------------------------------------------------------------	

	DECLARE @FactorA INT;
	DECLARE @FactorB INT;

	IF( @CurRank = 1 OR @CurRank = 0 ) BEGIN
		SET @FactorA = 0;
		SET @FactorB = 4;
	END	ELSE IF( @CurRank = 2 ) BEGIN 
		SET @FactorA = 1;
		SET @FactorB = 3;
	END	ELSE IF( @CurRank - 1 = @TotalUser) BEGIN
		SET @FactorA = 4;
		SET @FactorB = 1;
	END	ELSE IF( @CurRank = @TotalUser ) BEGIN
		SET @FactorA = 4;
		SET @FactorB = 0;
	END ELSE IF( @CurRank IS NULL ) BEGIN
		SET @CurRank = 3;
		SET @FactorA = 2;
		SET @FactorB = 2;		
	END ELSE BEGIN
		SET @FactorA = 2;
		SET @FactorB = 2;

	END
	
-----------------------------------------------------------------

	SELECT c.Name, t.Wins, t.Losses, t.Ranking
	FROM
	(
		SELECT cr.CID, cr.Wins, cr.Losses, cr.Ranking
		FROM PWCharacterInfo cr WITH (NOLOCK)
		WHERE cr.Ranking > 0
			AND cr.Ranking BETWEEN @CurRank - @FactorA AND @CurRank + @FactorB
	) t, Character c WITH (NOLOCK)
	WHERE t.CID = c.CID
		AND c.DeleteFlag = 0
	ORDER BY t.Ranking
	
END
GO




