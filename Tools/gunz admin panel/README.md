Credits to: XZeenon <br>

SQL CODES: <br>

ZAPLog.dbo <br>

    USE [gunzdb]
    GO

    /****** Object:  Table [dbo].[ZAPLog]    Script Date: 03/09/2010 22:42:35 ******/
    SET ANSI_NULLS ON
    GO

    SET QUOTED_IDENTIFIER ON
    GO

    SET ANSI_PADDING ON
    GO

    CREATE TABLE [dbo].[ZAPLog](
      [ID] [int] IDENTITY(1,1) NOT NULL,
      [UserID] [varchar](20) NULL,
      [Date] [ntext] NULL,
      [Action] [ntext] NULL,
     CONSTRAINT [PK_ZAPLog] PRIMARY KEY CLUSTERED 
    (
      [ID] ASC
    )WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
    ) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

    GO

    SET ANSI_PADDING OFF
    GO

IPBans.dbo (For IP Banning)

    USE [GunzDB]
    GO

    /****** Object:  Table [dbo].[ipbans]    Script Date: 02/14/2010 12:57:29 By: XZeenon ******/
    SET ANSI_NULLS ON
    GO

    SET QUOTED_IDENTIFIER ON
    GO

    SET ANSI_PADDING ON
    GO

    CREATE TABLE [dbo].[ipbans](
      [UserID] [varchar](20) NULL,
      [IP] [varchar](20) NULL,
      [Reason] [ntext] NULL
    ) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

    GO

    SET ANSI_PADDING OFF
    GO

ZAPpm.dbo (Private messages)

    USE [gunzdb]
    GO

    /****** Object:  Table [dbo].[ZAPpm]    Script Date: 03/09/2010 23:59:13 ******/
    SET ANSI_NULLS ON
    GO

    SET QUOTED_IDENTIFIER ON
    GO

    SET ANSI_PADDING ON
    GO

    CREATE TABLE [dbo].[ZAPpm](
      [ID] [int] IDENTITY(1,1) NOT NULL,
      [From] [varchar](20) NULL,
      [To] [varchar](20) NULL,
      [Date] [ntext] NULL,
      [Message] [ntext] NULL,
     CONSTRAINT [PK_ZAPpm] PRIMARY KEY CLUSTERED 
    (
      [ID] ASC
    )WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
    ) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

    GO

    SET ANSI_PADDING OFF
    GO


NOTE: They are also included in my panel. (Database > Required Files > Tables) <br>

If someone wishes to post images, go ahead. I can add to main post if you ask.<br>

Also, PLEASE do not forget to hit the thanks button, 3 MONTHS were spent on this program, I would appreciate appreciation.<br>

Animation of program<br>

LOG <br>

    November 1st 2010
    -Fixed a bug which wouldn't let you send an item to your character.
    December 12th 2010
    -Changed the link for the Remote SQL tutorial.












