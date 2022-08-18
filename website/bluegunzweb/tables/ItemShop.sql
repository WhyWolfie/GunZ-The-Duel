USE [GunzDB]
GO
/****** Object:  Table [dbo].[ItemShop]    Script Date: 02/20/2011 11:23:32 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ItemShop](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Name] [varchar](50) NULL,
	[ItemID] [int] NULL,
	[Sex] [int] NULL,
	[Level] [int] NULL,
	[Price] [varchar](50) NULL,
	[Category] [varchar](50) NULL,
	[Type] [varchar](50) NULL,
	[Image] [varchar](50) NULL,
	[Damage] [int] NULL,
	[Delay] [int] NULL,
	[Magazine] [int] NULL,
	[HP] [int] NULL,
	[AP] [int] NULL,
	[Weight] [int] NULL,
 CONSTRAINT [ItemShop_PK] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON, FILLFACTOR = 90) ON [PRIMARY]
) ON [PRIMARY]

GO
SET ANSI_PADDING OFF