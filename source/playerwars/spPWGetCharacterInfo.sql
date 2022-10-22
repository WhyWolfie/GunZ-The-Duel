USE [UGGunzDB]
GO

/****** Object:  StoredProcedure [dbo].[spPWGetCharacterInfo]    Script Date: 10/22/2022 7:39:05 PM ******/
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

