USE [GunzDB]
GO
/****** Object:  Table [dbo].[ipbans]    Script Date: 12/28/2010 01:51:25 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ipbans](
	[UserID] [varchar](20) NULL,
	[IP] [varchar](20) NULL
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF