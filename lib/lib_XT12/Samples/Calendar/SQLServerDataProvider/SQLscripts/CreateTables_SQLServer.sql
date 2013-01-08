if exists (select * from sysobjects where id = object_id(N'[dbo].[CalendarEvents]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CalendarEvents]
GO

if exists (select * from sysobjects where id = object_id(N'[dbo].[CalendarRecurrencePatterns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[CalendarRecurrencePatterns]
GO

CREATE TABLE [dbo].[CalendarEvents] (
	[EventID] [int] IDENTITY (1, 1) NOT NULL ,
	[StartDateTime] [datetime] NULL ,
	[EndDateTime] [datetime] NULL ,
	[RecurrenceState] [int] NULL ,
	[Subject] [nvarchar] (255) NULL ,
	[Location] [nvarchar] (255) NULL ,
	[Body] [nvarchar] (255) NULL ,
	[BusyStatus] [int] NULL ,
	[ImportanceLevel] [int] NULL ,
	[LabelID] [int] NULL ,
	[ScheduleID] [int] NULL ,
	[RecurrencePatternID] [int] NULL ,
	[IsRecurrenceExceptionDeleted] [int] NULL ,
	[RExceptionStartTimeOrig] [datetime] NULL ,
	[RExceptionEndTimeOrig] [datetime] NULL ,
	[IsAllDayEvent] [int] NULL ,
	[IsMeeting] [int] NULL ,
	[IsPrivate] [int] NULL ,
	[IsReminder] [int] NULL ,
	[ReminderMinutesBeforeStart] [int] NULL ,
	[RemainderSoundFile] [nvarchar] (255) NULL ,
	[CustomPropertiesXMLData] [ntext] NULL ,
	[CustomIconsIDs] [ntext] NULL ,
	[Created] [datetime] NULL ,
	[Modified] [datetime] NULL 
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO

CREATE TABLE [dbo].[CalendarRecurrencePatterns] (
	[RecurrencePatternID] [int] IDENTITY (1, 1) NOT NULL ,
	[MasterEventID] [int] NULL ,
	[PatternStartDate] [datetime] NULL ,
	[PatternEndMethod] [int] NULL ,
	[PatternEndDate] [datetime] NULL ,
	[PatternEndAfterOccurrences] [int] NULL ,
	[EventStartTime] [datetime] NULL ,
	[EventDuration] [int] NULL ,
	[OptionsData1] [int] NULL ,
	[OptionsData2] [int] NULL ,
	[OptionsData3] [int] NULL ,
	[OptionsData4] [int] NULL ,
	[CustomPropertiesXMLData] [ntext] NULL 
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO

ALTER TABLE [dbo].[CalendarEvents] WITH NOCHECK ADD 
	CONSTRAINT [PK_CalendarEvents] PRIMARY KEY  NONCLUSTERED 
	(
		[EventID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [dbo].[CalendarRecurrencePatterns] WITH NOCHECK ADD 
	CONSTRAINT [PK_CalendarRecurrencePatterns] PRIMARY KEY  NONCLUSTERED 
	(
		[RecurrencePatternID]
	)  ON [PRIMARY] 
GO

