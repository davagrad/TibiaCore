/**
 * Tibia GIMUD Server - a free and open-source MMORPG server emulator
 * Copyright (C) 2017  Alejandro Mujica <alejandrodemujica@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "otpch.h"

#include "configmanager.h"
#include "game.h"

#if LUA_VERSION_NUM >= 502
#undef lua_strlen
#define lua_strlen lua_rawlen
#endif

extern Game g_game;

bool ConfigManager::load()
{
	lua_State* L = luaL_newstate();
	if (!L) {
		throw std::runtime_error("Failed to allocate memory");
	}

	luaL_openlibs(L);

	if (luaL_dofile(L, "config.lua")) {
		std::cout << "[Error - ConfigManager::load] " << lua_tostring(L, -1) << std::endl;
		lua_close(L);
		return false;
	}

	//parse config
	if (!loaded) { //info that must be loaded one time (unless we reset the modules involved)
		boolean[BIND_ONLY_GLOBAL_ADDRESS] = getGlobalBoolean(L, "bindOnlyGlobalAddress", false);
		boolean[OPTIMIZE_DATABASE] = getGlobalBoolean(L, "startupDatabaseOptimization", true);

		string[IP] = getGlobalString(L, "ip", "0.0.0.0");
		string[MAP_NAME] = getGlobalString(L, "mapName", "forgotten");
		string[MAP_AUTHOR] = getGlobalString(L, "mapAuthor", "Unknown");
		string[HOUSE_RENT_PERIOD] = getGlobalString(L, "houseRentPeriod", "never");
		string[MYSQL_HOST] = getGlobalString(L, "mysqlHost", "db");
		string[MYSQL_USER] = getGlobalString(L, "mysqlUser", "tfsuser");
		string[MYSQL_PASS] = getGlobalString(L, "mysqlPass", "StrongUserPassword!");
		string[MYSQL_DB] = getGlobalString(L, "mysqlDatabase", "tibiacore");
		string[MYSQL_SOCK] = getGlobalString(L, "mysqlSock", "");

		integer[SQL_PORT] = getGlobalNumber(L, "mysqlPort", 3306);
		integer[GAME_PORT] = getGlobalNumber(L, "gameProtocolPort", 7172);
		integer[LOGIN_PORT] = getGlobalNumber(L, "loginProtocolPort", 7171);
		integer[STATUS_PORT] = getGlobalNumber(L, "statusProtocolPort", 7171);
	}

	boolean[SHOW_MONSTER_LOOT] = getGlobalBoolean(L, "showMonsterLoot", true);
	boolean[ALLOW_CHANGEOUTFIT] = getGlobalBoolean(L, "allowChangeOutfit", true);
	boolean[ONE_PLAYER_ON_ACCOUNT] = getGlobalBoolean(L, "onePlayerOnlinePerAccount", true);
	boolean[REMOVE_RUNE_CHARGES] = getGlobalBoolean(L, "removeChargesFromRunes", true);
	boolean[EXPERIENCE_FROM_PLAYERS] = getGlobalBoolean(L, "experienceByKillingPlayers", false);
	boolean[FREE_PREMIUM] = getGlobalBoolean(L, "freePremium", false);
	boolean[REPLACE_KICK_ON_LOGIN] = getGlobalBoolean(L, "replaceKickOnLogin", true);
	boolean[ALLOW_CLONES] = getGlobalBoolean(L, "allowClones", false);
	boolean[WARN_UNSAFE_SCRIPTS] = getGlobalBoolean(L, "warnUnsafeScripts", true);
	boolean[CONVERT_UNSAFE_SCRIPTS] = getGlobalBoolean(L, "convertUnsafeScripts", true);
	boolean[TELEPORT_NEWBIES] = getGlobalBoolean(L, "teleportNewbies", true);
	boolean[STACK_CUMULATIVES] = getGlobalBoolean(L, "autoStackCumulatives", false);
	boolean[QUERY_PLAYER_CONTAINERS] = getGlobalBoolean(L, "queryPlayerContainers", false);
	boolean[RESTORE_UPLEVEL_FREE] = getGlobalBoolean(L, "upLevelRestoreFree", false);
	boolean[RESTORE_UPLEVEL_PREMIUM] = getGlobalBoolean(L, "upLevelRestorePremium", false);
	boolean[DROP_SPEAR_FREE] = getGlobalBoolean(L, "dropSpearFree", true);
	boolean[DROP_SPEAR_PREMIUM] = getGlobalBoolean(L, "dropSpearPremium", true);
	boolean[MAKE_RUNE_BACKPACK_FREE] = getGlobalBoolean(L, "makeRuneBackpackFree", false);
	boolean[MAKE_RUNE_BACKPACK_PREMIUM] = getGlobalBoolean(L, "makeRuneBackpackPremium", false);
	boolean[ENABLE_LIVE_CASTING] = getGlobalBoolean(L, "enableLiveCasting", false);
	boolean[SAVE_PLAYERS_LOGS] = getGlobalBoolean(L, "savePlayersLogs", false);
	boolean[IGNORE_BLOCK_RESPAWN] = getGlobalBoolean(L, "ignoreBlockRespawn", false);
	boolean[TRIGGER_RESPAWN_EFFECT] = getGlobalBoolean(L, "triggerRespawnEffect", false);
	boolean[FIRST_PAY_RENT_ON_FINAL_BID] = getGlobalBoolean(L, "firstPayRentOnFinalBid", false);
	boolean[ATTACKERPARTYENTERPZ] = getGlobalBoolean(L, "attackerPartyEnterPz", false);
	boolean[MEMBERSAFESKULLGUILD] = getGlobalBoolean(L, "memberSafeSkullGuild", false);

	string[DEFAULT_PRIORITY] = getGlobalString(L, "defaultPriority", "high");
	string[SERVER_NAME] = getGlobalString(L, "serverName", "");
	string[OWNER_NAME] = getGlobalString(L, "ownerName", "");
	string[OWNER_EMAIL] = getGlobalString(L, "ownerEmail", "");
	string[URL] = getGlobalString(L, "url", "");
	string[LOCATION] = getGlobalString(L, "location", "");
	string[MOTD] = getGlobalString(L, "motd", "");
	string[WORLD_TYPE] = getGlobalString(L, "worldType", "pvp");

	integer[MAX_PLAYERS] = getGlobalNumber(L, "maxPlayers");
	integer[PZ_LOCKED] = getGlobalNumber(L, "pzLocked", 60000);
	integer[RESPAWNRADIUS] = getGlobalNumber(L, "respawnRadius", 200);
	integer[RATE_EXPERIENCE] = getGlobalNumber(L, "rateExp", 5);
	integer[RATE_SKILL] = getGlobalNumber(L, "rateSkill", 3);
	integer[RATE_LOOT] = getGlobalNumber(L, "rateLoot", 2);
	integer[RATE_MAGIC] = getGlobalNumber(L, "rateMagic", 3);
	integer[RATE_SPAWN_PERCENT] = getGlobalNumber(L, "rateSpawnPercent", 0);
	integer[BAN_LENGTH] = getGlobalNumber(L, "banLength", 30 * 24 * 60 * 60);
	integer[ACTIONS_DELAY_INTERVAL] = getGlobalNumber(L, "timeBetweenActions", 200);
	integer[EX_ACTIONS_DELAY_INTERVAL] = getGlobalNumber(L, "timeBetweenExActions", 1000);
	integer[MAX_MESSAGEBUFFER] = getGlobalNumber(L, "maxMessageBuffer", 4);
	integer[KICK_AFTER_MINUTES] = getGlobalNumber(L, "kickIdlePlayerAfterMinutes", 15);
	integer[PROTECTION_LEVEL] = getGlobalNumber(L, "protectionLevel", 1);
	integer[DEATH_LOSE_PERCENT] = getGlobalNumber(L, "deathLosePercent", -1);
	integer[STATUSQUERY_TIMEOUT] = getGlobalNumber(L, "statusTimeout", 5000);
	integer[WHITE_SKULL_TIME] = getGlobalNumber(L, "whiteSkullTime", 15 * 60);
	integer[RED_SKULL_TIME] = getGlobalNumber(L, "redSkullTime", 30 * 24 * 60 * 60);
	integer[KILLS_DAY_RED_SKULL] = getGlobalNumber(L, "killsDayRedSkull", 3);
	integer[KILLS_WEEK_RED_SKULL] = getGlobalNumber(L, "killsWeekRedSkull", 5);
	integer[KILLS_MONTH_RED_SKULL] = getGlobalNumber(L, "killsMonthRedSkull", 10);
	integer[KILLS_DAY_BANISHMENT] = getGlobalNumber(L, "killsDayBanishment", 5);
	integer[KILLS_WEEK_BANISHMENT] = getGlobalNumber(L, "killsWeekBanishment", 8);
	integer[KILLS_MONTH_BANISHMENT] = getGlobalNumber(L, "killsMonthBanishment", 10);
	integer[STAIRHOP_DELAY] = getGlobalNumber(L, "stairJumpExhaustion", 2000);
	integer[EXP_FROM_PLAYERS_LEVEL_RANGE] = getGlobalNumber(L, "expFromPlayersLevelRange", 75);
	integer[MAX_PACKETS_PER_SECOND] = getGlobalNumber(L, "maxPacketsPerSecond", 25);
	integer[NEWBIE_TOWN] = getGlobalNumber(L, "newbieTownId", 1);
	integer[NEWBIE_LEVEL_THRESHOLD] = getGlobalNumber(L, "newbieLevelThreshold", 5);
	integer[MONEY_RATE] = getGlobalNumber(L, "moneyRate", 1);
	integer[HOUSE_PRICE] = getGlobalNumber(L, "multiHousePricebyRent", 1);
	integer[RATE_LIFE_BED] = getGlobalNumber(L, "rateLifeBed", 1);
	integer[RATE_MANA_BED] = getGlobalNumber(L, "rateManaBed", 1);
	integer[TICKS_REGEN_BED_GAIN] = getGlobalNumber(L, "ticksRegenBedGain", 30);
	integer[RATE_NUTRITION_BED] = getGlobalNumber(L, "rateNutritionBed", 1);
	integer[BAN_ACCOUNT_FROM_BID_DAY] = getGlobalNumber(L, "daysBanAccountFromBid", 0);

	//config.lua: ignoreMonsters = {"dog", "etc...", "etc...} only lowercase!
	listConfigs[IGNORE_MONSTER_RADIUS] = loadLuaTable(L, "ignoreMonsters");

	loaded = true;
	lua_close(L);
	return true;
}

bool ConfigManager::reload()
{
	bool result = load();
	if (transformToSHA1(getString(ConfigManager::MOTD)) != g_game.getMotdHash()) {
		g_game.incrementMotdNum();
	}
	return result;
}

const std::string& ConfigManager::getString(string_config_t what) const
{
	if (what >= LAST_STRING_CONFIG) {
		std::cout << "[Warning - ConfigManager::getString] Accessing invalid index: " << what << std::endl;
		return string[DUMMY_STR];
	}
	return string[what];
}

const std::list<std::string>& ConfigManager::getList(list_config_t what) const {
	auto it = listConfigs.find(what);
	if (it != listConfigs.end()) {
		return it->second;
	}
	else {
		static const std::list<std::string> emptyList;
		std::cout << "[Warning - ConfigManager::getList] Invalid index: " << what << std::endl;
		return emptyList;
	}
}


std::list<std::string> ConfigManager::loadLuaTable(lua_State* L, const char* identifier) {
	std::list<std::string> result;

	lua_getglobal(L, identifier);  // get table from lua
	if (lua_istable(L, -1)) {  // check if table
		lua_pushnil(L);  // first key

		while (lua_next(L, -2) != 0) {
			if (lua_isstring(L, -1)) {  // check is string
				result.push_back(lua_tostring(L, -1));
			}
			lua_pop(L, 1);
		}
	}
	else {
		std::cout << "[Warning] " << identifier << " is not a table!" << std::endl;
	}

	lua_pop(L, 1);  // remove table from stacke.
	return result;
}

bool ConfigManager::isMonsterIgnored(const std::string& monsterName) const {
	const std::list<std::string>& ignoreMonsters = getList(IGNORE_MONSTER_RADIUS);
	return std::find(ignoreMonsters.begin(), ignoreMonsters.end(), monsterName) != ignoreMonsters.end();
}

int32_t ConfigManager::getNumber(integer_config_t what) const
{
	if (what >= LAST_INTEGER_CONFIG) {
		std::cout << "[Warning - ConfigManager::getNumber] Accessing invalid index: " << what << std::endl;
		return 0;
	}
	return integer[what];
}

bool ConfigManager::getBoolean(boolean_config_t what) const
{
	if (what >= LAST_BOOLEAN_CONFIG) {
		std::cout << "[Warning - ConfigManager::getBoolean] Accessing invalid index: " << what << std::endl;
		return false;
	}
	return boolean[what];
}

std::string ConfigManager::getGlobalString(lua_State* L, const char* identifier, const char* defaultValue)
{
	lua_getglobal(L, identifier);
	if (!lua_isstring(L, -1)) {
		return defaultValue;
	}

	size_t len = lua_strlen(L, -1);
	std::string ret(lua_tostring(L, -1), len);
	lua_pop(L, 1);
	return ret;
}

int32_t ConfigManager::getGlobalNumber(lua_State* L, const char* identifier, const int32_t defaultValue)
{
	lua_getglobal(L, identifier);
	if (!lua_isnumber(L, -1)) {
		return defaultValue;
	}

	int32_t val = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return val;
}

bool ConfigManager::getGlobalBoolean(lua_State* L, const char* identifier, const bool defaultValue)
{
	lua_getglobal(L, identifier);
	if (!lua_isboolean(L, -1)) {
		if (!lua_isstring(L, -1)) {
			return defaultValue;
		}

		size_t len = lua_strlen(L, -1);
		std::string ret(lua_tostring(L, -1), len);
		lua_pop(L, 1);
		return booleanString(ret);
	}

	int val = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return val != 0;
}
