#include "stdafx.h"
#include "ZDiscord.h"

namespace {
	volatile bool interrupted{ false };
}

ZDiscord::ZDiscord() : InicioDiscord(false), Actual(GUNZ_NA), Despues(GUNZ_MAX)
{
}

discord::Result ZDiscord::DiscordInt()
{
	auto result = discord::Core::Create(960199229349953536, DiscordCreateFlags_NoRequireDiscord, &core);

	return static_cast<discord::Result>(result);
}

void ZDiscord::OnCreate()
{
	ResultDiscord = DiscordInt();

	if (ResultDiscord != discord::Result::Ok)
	{
		state.core.reset(core);

		if (!state.core)
		{
			MLog("[DISCORD] Discord Fail!\n");
			InicioDiscord = false;
		}
		else
		{
			MLog("[DISCORD] Discord LIVE!\n");
			InicioDiscord = true;
		}

		Actual = ZGetGameInterface()->GetState();
	}
	else
	{
		InicioDiscord = false;
	}

	state.core->SetLogHook(
		discord::LogLevel::Debug, [](discord::LogLevel level, const char* message) {
			MLog("DiscordLog(%s %s)\n ", static_cast<uint32_t>(level), message);
		});
}

bool ZDiscord::OnUpdate()
{
	if (InicioDiscord == false)
		return false;

	Actual = ZGetGameInterface()->GetState();

	if (Despues == Actual)
		return false;

	state.core->RunCallbacks();
	OnDiscordState(Actual);
	state.core->RunCallbacks();

	MLog("ZDiscord::OnUpdate() - updating activity!\n");

	Despues = Actual;

	return true;
}

void ZDiscord::OnDiscordState(GunzState nState)
{
	discord::Activity activity{};

	switch (nState)
	{
	case GUNZ_NA:
		activity.SetDetails("Running Gunz");
		activity.SetState("Pop Snacks");
		break;
	case GUNZ_GAME:
	{
		bool bClanGame = ZGetGameClient()->IsLadderGame();
		MMATCH_GAMETYPE nGameType = ZGetGameClient()->GetMatchStageSetting()->GetGameType();
		MCHANNEL_TYPE nChannelType = ZGetGameClient()->GetChannelType();
		int nStageType = ZGetGameClient()->GetMatchStageSetting()->GetStageType();

		ZCharacter* pChar = (ZCharacter*)ZGetCharacterManager()->Find(ZGetMyUID());
		char CharAndLevel[256];
		char CharandClan[256];
		char Nmrandnamesrage[256];
		sprintf_safe(CharAndLevel, "%d Lv. %s", pChar->GetProperty()->nLevel, pChar->GetProperty()->GetName());
		sprintf_safe(CharandClan, "%d Clan %d", pChar->GetProperty()->GetName(), pChar->GetProperty()->GetClanName());
		sprintf_safe(Nmrandnamesrage, "[%03d] %s", ZGetGameClient()->GetStageNumber(), ZGetGameClient()->GetStageName());
		auto RedScore = ZGetGame()->GetMatch()->GetTeamScore(MMT_RED);
		auto BlueScore = ZGetGame()->GetMatch()->GetTeamScore(MMT_BLUE);

		if (bClanGame)
		{
			switch (nStageType)
			{
			case (MST_LADDER):
				activity.SetDetails(CharAndLevel);
				activity.SetState("Ladder");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MST_CLAN):
				activity.SetDetails(CharandClan);
				activity.SetState("Clan War");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MST_LADDER_CLAN):
				activity.SetDetails(CharAndLevel);
				activity.SetState("Ladder / Clan War");
				activity.GetTimestamps().SetStart(0);
			default:
				break;
			}
		}
		else
		{
			switch (nGameType)
			{
			case (MMATCH_GAMETYPE_DEATHMATCH_SOLO):
				activity.SetDetails(CharAndLevel);
				activity.SetState("DEATHMATCH SOLO");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MMATCH_GAMETYPE_DEATHMATCH_TEAM):
				activity.SetDetails(CharAndLevel);
				activity.SetState("DEATHMATCH TEAM");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MMATCH_GAMETYPE_GLADIATOR_SOLO):
				activity.SetDetails(CharAndLevel);
				activity.SetState("GLADIATOR SOLO");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MMATCH_GAMETYPE_BERSERKER):
				activity.SetDetails(CharAndLevel);
				activity.SetState("BERSERKER");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MMATCH_GAMETYPE_GLADIATOR_TEAM):
				activity.SetDetails(CharAndLevel);
				activity.SetState("GLADIATOR TEAM");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MMATCH_GAMETYPE_ASSASSINATE):
				activity.SetState("GLADIATOR TEAM");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MMATCH_GAMETYPE_TRAINING):
				activity.SetDetails(CharAndLevel);
				activity.SetState("TRAINING");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MMATCH_GAMETYPE_SURVIVAL):
				activity.SetDetails(CharAndLevel);
				activity.SetState("SURVIVAL");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MMATCH_GAMETYPE_QUEST):
				activity.SetDetails(CharAndLevel);
				activity.SetState("QUEST");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MMATCH_GAMETYPE_DEATHMATCH_TEAM2):
				activity.SetState("DEATHMATCHTEAM2");
				activity.GetTimestamps().SetStart(0);
				break;
			case (MMATCH_GAMETYPE_DUEL):
				activity.SetDetails(CharAndLevel);
				activity.SetState("DUEL");
				activity.GetTimestamps().SetStart(0);
				break;
			default:
				break;
			}
		}
	}
	break;
	case GUNZ_LOGIN:
		activity.SetDetails("In Select Server");
		break;
	case GUNZ_LOBBY:
		activity.SetDetails("In Lobby");
		break;
	case GUNZ_STAGE:
		activity.SetDetails("In Stage");
		break;
	case GUNZ_CHARSELECTION:
		activity.SetDetails("In Select Character");
		break;
	case GUNZ_CHARCREATION:
		activity.SetDetails("In Create Character");
		break;
	default:
		activity.SetDetails("Running Gunz");
		activity.SetState("Pop Snacks");
		break;
	}

	activity.SetType(discord::ActivityType::Playing);

	state.core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
		MLog("%s updating activity!\n", ((result == discord::Result::Ok) ? "Succeeded" : "Failed"));
		});
}

ZDiscord* ZDiscord::GetInstance()
{
	static ZDiscord g_ZDiscordMgr;
	return &g_ZDiscordMgr;
}