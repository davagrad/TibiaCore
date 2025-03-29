-- Combat settings
-- NOTE: valid values for worldType are: "pvp", "no-pvp" and "pvp-enforced"
worldType = "pvp"
--worldId = 1 sem
protectionLevel = 0
pzLocked = 60000
removeChargesFromRunes = 1
stairJumpExhaustion = 0
experienceByKillingPlayers = false
expFromPlayersLevelRange = 75

-- Casting System
enableLiveCasting = true
percentCastExp = 5

-- Player Options
-- Character Rooking
-- Level threshold is the level requirement to teleport players back to newbie town
teleportNewbies = true
newbieTownId = 11
newbieLevelThreshold = 5
allowChangeOutfit = true
autoStackCumulatives = true
freePremium = true
kickIdlePlayerAfterMinutes = 15
maxMessageBuffer = 20
showMonsterLoot = true
queryPlayerContainers = true
exhaustionNPC = true
exhaustionInSecondsNPC = 1
savePlayersLogs = true

-- Deaths
-- NOTE: Leave deathLosePercent as -1 if you want to use the default
-- death penalty formula. For the old formula, set it to 10. For
-- no skill/experience loss, set it to 0.
deathLosePercent = 10

-- Premium Account percent exp.
percentPremiumExp = 5

-- Account Type: 1 = Copper 2 = Silver 3 = Gold.
-- Exp bonus in percent and with deathLosePercent if > 0, but calc is (percents / copper = 70, Silver = 60, gold = 50) in round.
enableAccountBonus = true
percentBonusCopper = 15
percentBonusSilver = 25
percentBonusGold = 50

-- Player restore when uplevel.
upLevelRestoreFree = false
upLevelRestorePremium = true

-- Player can drop ammo.
dropSpearFree = true
dropSpearPremium = true

-- Player can make rune from backpack.
makeRuneBackpackFree = false
makeRuneBackpackPremium = true

-- Skull System
attackerPartyEnterPz = false
memberSafeSkullGuild = false
banLength = 7 * 24 * 60 * 60
whiteSkullTime = 15 * 60
redSkullTime = 15 * 24 * 60 * 60

killsDayRedSkull = 3
killsDayBanishment = 5

killsWeekRedSkull = 6
killsWeekBanishment = 8

killsMonthRedSkull = 12
killsMonthBanishment = 16

-- Rates - NOTE: rateExp is not used if you have enabled stages in data/XML/stages.xml
rateExp = 1
rateSkill = 1
rateLoot = 1
rateMagic = 1
rateSpawnPercent = 98
moneyRate = 1

-- Item Usage
timeBetweenActions = 200
timeBetweenExActions = 1000

-- Monsters
ignoreBlockRespawn = true
triggerRespawnEffect = true
-- default 200 radius, disable set 0.
respawnRadius = 0
-- set list name lowers of the mosnters to not respawn out radius.
ignoreMonsters = {""}

-- Houses
houseRentPeriod = "monthly"
firstPayRentOnFinalBid = false
daysBanAccountFromBid = 3
multiHousePricebyRent = 3
-- Houses bed system, when player are sleeping.
-- Every 30 seconds gains 1 regeneration, Default 30
ticksRegenBedGain = 5
-- Duration of food in bed ex: 1 = cherry 12 seconds, 2 = cherry 24 seconds, Default 1.
rateNutritionBed = 1
-- Multiplies regeneration each gain, Default 1
rateLifeBed = 2
rateManaBed = 2

-- Connection Config
-- NOTE: maxPlayers set to 0 means no limit
ip = "127.0.01"
bindOnlyGlobalAddress = false
loginProtocolPort = 7171
gameProtocolPort = 7172
statusProtocolPort = 7171
maxPlayers = 2000
motd = "Welcome to TibiaCore!"
onePlayerOnlinePerAccount = true
allowClones = false
serverName = "TibiaCore"
statusTimeout = 5000
replaceKickOnLogin = true
maxPacketsPerSecond = -1
autoStackCumulatives = true
moneyRate = 1

-- Deaths
-- NOTE: Leave deathLosePercent as -1 if you want to use the default
-- death penalty formula. For the old formula, set it to 10. For
-- no skill/experience loss, set it to 0.
deathLosePercent = -1

-- Houses
houseRentPeriod = "monthly"
multiHousePricebyRent = 3

-- Item Usage
timeBetweenActions = 200
timeBetweenExActions = 1000

-- Map
-- NOTE: set mapName WITHOUT .otbm at the end
mapName = "map"
mapAuthor = "CipSoft"

-- MySQL
mysqlHost = "127.0.0.1"
mysqlUser = "root"
mysqlPass = ""
mysqlDatabase = "tibiacore"
mysqlPort = 3306
mysqlSock = ""
encryptionType = "sha1"

-- Misc.
allowChangeOutfit = true
freePremium = false
kickIdlePlayerAfterMinutes = 15
maxMessageBuffer = 4
showMonsterLoot = true
queryPlayerContainers = true
exhaustionNPC = true
exhaustionInSecondsNPC = 1

-- Character Rooking
-- Level threshold is the level requirement to teleport players back to newbie town
teleportNewbies = true
newbieTownId = 11
newbieLevelThreshold = 5

-- Rates
-- NOTE: rateExp is not used if you have enabled stages in data/XML/stages.xml
rateExp = 2
rateSkill = 1
rateLoot = 2
rateMagic = 1
rateSpawn = 0

-- Monsters
deSpawnRange = 2
deSpawnRadius = 0

-- Scripts
warnUnsafeScripts = true
convertUnsafeScripts = true

-- Startup
-- NOTE: defaultPriority only works on Windows and sets process
-- priority, valid values are: "normal", "above-normal", "high"
defaultPriority = "high"
startupDatabaseOptimization = true

-- Status server information
ownerName = "RcPmG"
ownerEmail = ""
url = "tibiacore.servegame.com"
location = "Brazil"
