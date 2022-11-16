USE [GunzDB]
GO
/****** Objeto:  Table [dbo].[WebIpBan]    Fecha de la secuencia de comandos: 12/15/2012 19:59:36 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[WebIpBan](
	[id] [int] IDENTITY(1,1) NOT NULL,
	[ip] [varchar](40) NULL,
	[fecha] [varchar](50) NULL,
	[razon] [text] NULL
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO
SET ANSI_PADDING OFF