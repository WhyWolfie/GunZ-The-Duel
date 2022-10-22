USE [UGGunzDB]
GO

/****** Object:  StoredProcedure [dbo].[PWInsertGameLog]    Script Date: 10/22/2022 7:37:56 PM ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE PROCEDURE [dbo].[PWInsertGameLog]
	@Winning varchar(200),
	@Losing varchar(200),
	@WinningScore int,
	@LosingScore int,
	@MapID int
AS
BEGIN
	SET NOCOUNT ON;
	insert into PWGameLog(WinnerMembers , LoserMembers, RoundWins, RoundLosses, MapID, RegDate) values (@Winning, @Losing, @WinningScore, @LosingScore, @MapID, GETDATE());
END

GO

