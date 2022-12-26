#pragma once

#include <iostream>
#include <csignal>
#include <thread>
#include <chrono>
#include <cctype>

#include "ZApplication.h"

#include "discord.h"

struct DiscordState {
	std::unique_ptr<discord::Core> core;
};

class ZDiscord
{
public:

	ZDiscord();
	~ZDiscord() = default;

	discord::Result DiscordInt();

	discord::Result ResultDiscord;

	void OnCreate();
	bool OnUpdate();
	void OnDiscordState(GunzState nState);

	static ZDiscord* GetInstance();

private:
	DiscordState state{};
	discord::Core* core{};

	GunzState Actual;
	GunzState Despues;
	bool InicioDiscord;
};

inline ZDiscord* ZGetDiscord() { return ZDiscord::GetInstance(); }
