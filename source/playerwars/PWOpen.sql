USE [UGGunzDB]
GO

/****** Object:  StoredProcedure [dbo].[spPWOpen]    Script Date: 10/22/2022 7:39:14 PM ******/
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

