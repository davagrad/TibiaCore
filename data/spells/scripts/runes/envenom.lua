local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_EARTHDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_HITBYPOISON)
combat:setParameter(COMBAT_PARAM_DISTANCEEFFECT, CONST_ANI_ENERGY)

function onTargetCreature(creature, target)
	local player = Player(creature)
	
	local condition = Condition(CONDITION_POISON)
	condition:setTiming(computeFormula(player:getLevel(), player:getMagicLevel(), 70, 20))
	condition:setParameter(CONDITION_PARAM_OWNER, player:getId())
	target:addCondition(condition)
end

combat:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(player, variant, isHotkey)
    local tile = Tile(variant:getPosition())
    if tile then
        local topVisibleCreature = tile:getTopCreature(player)
        if topVisibleCreature then
            if topVisibleCreature:getId() ~= player:getId() or not topVisibleCreature:getGroup():getAccess() then
                return combat:execute(player, variant)
            end
        end

        local bottomVisibleCreature = tile:getBottomCreature(player)
        if bottomVisibleCreature then
            if bottomVisibleCreature:getId() ~= player:getId() or not bottomVisibleCreature:getGroup():getAccess() then
                return combat:execute(player, variant)
            end
        end
    end

    player:getPosition():sendMagicEffect(CONST_ME_POFF)
    player:sendCancelMessage(RETURNVALUE_CANONLYUSETHISRUNEONCREATURES)
    return false
end