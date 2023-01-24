#include <string.h>

#include "../lib/subhook/subhook.h"
#include "../inc/hook.hpp"
#include "../inc/hooks.hpp"
#include "../inc/engine.hpp"

#include "../inc/util.hpp"

const char NOT_SPECIAL = -1;

voidFuncHook ResetGame;
voidIntFuncHook EliminatorAnnounceDeath;
voidFuncHook Logic;
voidFuncHook LogicRace;
voidFuncHook LogicRound;
voidFuncHook LogicWorld;
voidFuncHook LogicEliminator;
voidFuncHook LogicCoop;
voidFuncHook LogicVersus;
voidFuncHook BulletSimulation;
voidIntFuncHook PlayerActions;
voidFuncHook Physics;
voidFuncHook ServerSend;
voidDoubleIntFuncHook CalculatePlayerVoice;
voidFuncHook EconomyCarMarket;
createAccountByJoinTicketFuncHook AccountTicket;
serverSendConnectResponseFuncHook SendConnectResponse;
voidTripleIntFuncHook ArmHuman;
linkItemFuncHook LinkItem;
itemComputerInputFuncHook ComputerInput;
voidIntFuncHook WeaponSimulation;
voidDoubleIntFuncHook SetBaseDoorState;
humanApplyDamageFuncHook HumanDamage;
voidDoubleIntFuncHook VehicleDamage;
voidDoubleIntFuncHook HumanCollisionVehicle;
humanLimbInverseKinematicsFuncHook HumanLimbInverseKinematics;
voidIntFuncHook GrenadeExplosion;
voidIntFuncHook PlayerDeathTax;
voidIntFuncHook AccountDeathTax;
voidTripleIntFuncHook PlayerGiveWantedLevel;
collideBodiesFuncHook CollideBodies;
collideBodyWithLevelFuncHook CollideBodyWithLevel;
createPlayerFuncHook CreatePlayer;
voidIntFuncHook DeletePlayer;
createHumanFuncHook CreateHuman;
voidIntFuncHook DeleteHuman;
createItemFuncHook CreateItem;
voidIntFuncHook DeleteItem;
createVehicleFuncHook CreateVehicle;
voidIntFuncHook DeleteVehicle;
createRigidBodyFuncHook CreateRigidBody;
serverPlayerMessageFuncHook PlayerMessage;
eventMessageFuncHook EventMessage;
voidIntFuncHook EventUpdatePlayer;
voidIntFuncHook EventUpdateItem;
eventUpdateVehicleFuncHook EventUpdateVehicle;
eventSoundFuncHook EventSound;
eventBulletHitFuncHook EventBulletHit;
voidFuncHook EventUpdateStocks;
eventGlassBreakFuncHook EventGlassBreak;

void h_ResetGame()
{
    subhook::ScopedHookRemove remove(&ResetGame.hook);
    bool shouldOverride = false;
    for (auto callback : ResetGame.callbacks)
        shouldOverride |= callback();
    ResetGame.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::resetGame();
        for (auto postCallback : ResetGame.postCallbacks)
            postCallback();
        ResetGame.clearOncePostHooks();
    }
}

void h_EliminatorAnnounceDeath(int playerID)
{
    subhook::ScopedHookRemove remove(&EliminatorAnnounceDeath.hook);
    bool shouldOverride = false;
    for (auto callback : EliminatorAnnounceDeath.callbacks)
        shouldOverride |= callback(playerID);
    EliminatorAnnounceDeath.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::eliminatorAnnounceDeath(playerID);
        for (auto postCallback : EliminatorAnnounceDeath.postCallbacks)
            postCallback(playerID);
        EliminatorAnnounceDeath.clearOncePostHooks();
    }
}

void h_Logic()
{
    subhook::ScopedHookRemove remove(&Logic.hook);
    bool shouldOverride = false;
    for (auto callback : Logic.callbacks)
        shouldOverride |= callback();
    Logic.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::logicSimulation();
        for (auto postCallback : Logic.postCallbacks)
            postCallback();
        Logic.clearOncePostHooks();
    }
}

void h_LogicRace()
{
    subhook::ScopedHookRemove remove(&LogicRace.hook);
    bool shouldOverride = false;
    for (auto callback : LogicRace.callbacks)
        shouldOverride |= callback();
    LogicRace.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::logicSimulationRace();
        for (auto postCallback : LogicRace.postCallbacks)
            postCallback();
        LogicRace.clearOncePostHooks();
    }
}

void h_LogicRound()
{
    subhook::ScopedHookRemove remove(&LogicRound.hook);
    bool shouldOverride = false;
    for (auto callback : LogicRound.callbacks)
        shouldOverride |= callback();
    LogicRound.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::logicSimulationRound();
        for (auto postCallback : LogicRound.postCallbacks)
            postCallback();
        LogicRound.clearOncePostHooks();
    }
}

void h_LogicWorld()
{
    subhook::ScopedHookRemove remove(&LogicWorld.hook);
    bool shouldOverride = false;
    for (auto callback : LogicWorld.callbacks)
        shouldOverride |= callback();
    LogicWorld.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::logicSimulationWorld();
        for (auto postCallback : LogicWorld.postCallbacks)
            postCallback();
        LogicWorld.clearOncePostHooks();
    }
}

void h_LogicTerminator()
{
    subhook::ScopedHookRemove remove(&LogicEliminator.hook);
    bool shouldOverride = false;
    for (auto callback : LogicEliminator.callbacks)
        shouldOverride |= callback();
    LogicEliminator.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::logicSimulationTerminator();
        for (auto postCallback : LogicEliminator.postCallbacks)
            postCallback();
        LogicEliminator.clearOnceHooks();
    }
}

void h_LogicCoop()
{
    subhook::ScopedHookRemove remove(&LogicCoop.hook);
    bool shouldOverride = false;
    for (auto callback : LogicCoop.callbacks)
        shouldOverride |= callback();
    LogicCoop.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::logicSimulationCoop();
        for (auto postCallback : LogicCoop.postCallbacks)
            postCallback();
        LogicCoop.clearOncePostHooks();
    }
}

void h_LogicVersus()
{
    subhook::ScopedHookRemove remove(&LogicVersus.hook);
    bool shouldOverride = false;
    for (auto callback : LogicVersus.callbacks)
        shouldOverride |= callback();
    LogicVersus.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::logicSimulationVersus();
        for (auto postCallback : LogicVersus.postCallbacks)
            postCallback();
        LogicVersus.clearOncePostHooks();
    }
}

void h_BulletSimulation()
{
    subhook::ScopedHookRemove remove(&BulletSimulation.hook);
    bool shouldOverride = false;
    for (auto callback : BulletSimulation.callbacks)
        shouldOverride |= callback();
    BulletSimulation.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::bulletSimulation();
        for (auto postCallback : BulletSimulation.postCallbacks)
            postCallback();
        BulletSimulation.clearOncePostHooks();
    }
}

void h_PlayerActions(int playerID)
{
    subhook::ScopedHookRemove remove(&PlayerActions.hook);
    bool shouldOverride = false;
    for (auto callback : PlayerActions.callbacks)
        shouldOverride |= callback(playerID);
    PlayerActions.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::logicPlayerActions(playerID);
        for (auto postCallback : PlayerActions.postCallbacks)
            postCallback(playerID);
        PlayerActions.clearOncePostHooks();
    }
}

void h_Physics()
{
    subhook::ScopedHookRemove remove(&Physics.hook);
    bool shouldOverride = false;
    for (auto callback : Physics.callbacks)
        shouldOverride |= callback();
    Physics.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::physicsSimulation();
        for (auto postCallback : Physics.postCallbacks)
            postCallback();
        Physics.clearOncePostHooks();
    }
}

void h_ServerSend()
{
    subhook::ScopedHookRemove remove(&ServerSend.hook);
    bool shouldOverride = false;
    for (auto callback : ServerSend.callbacks)
        shouldOverride |= callback();
    ServerSend.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::serverSend();
        for (auto postCallback : ServerSend.postCallbacks)
            postCallback();
        ServerSend.clearOncePostHooks();
    }
}

void h_CalculatePlayerVoice(int connectionID, int playerID)
{
    subhook::ScopedHookRemove remove(&CalculatePlayerVoice.hook);
    bool shouldOverride = false;
    for (auto callback : CalculatePlayerVoice.callbacks)
        shouldOverride |= callback(connectionID, playerID);
    CalculatePlayerVoice.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::calculatePlayerVoice(connectionID, playerID);
        for (auto postCallback : CalculatePlayerVoice.postCallbacks)
            postCallback(connectionID, playerID);
        CalculatePlayerVoice.clearOncePostHooks();
    }
}

void h_EconomyCarMarket()
{
    subhook::ScopedHookRemove remove(&EconomyCarMarket.hook);
    bool shouldOverride = false;
    for (auto callback : EconomyCarMarket.callbacks)
        shouldOverride |= callback();
    EconomyCarMarket.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::economyCarMarket();
        for (auto postCallback : EconomyCarMarket.postCallbacks)
            postCallback();
        EconomyCarMarket.clearOncePostHooks();
    }
}

int h_AccountTicket(int identifier, unsigned int ticket)
{
    subhook::ScopedHookRemove remove(&AccountTicket.hook);
    bool shouldOverride = false;
    for (auto callback : AccountTicket.callbacks)
        shouldOverride |= callback(identifier, ticket);
    AccountTicket.clearOnceHooks();
    if (!shouldOverride)
    {
        int accountID = Engine::createAccountByJoinTicket(identifier, ticket);
        for (auto postCallback : AccountTicket.postCallbacks)
            postCallback(accountID, identifier, ticket);
        AccountTicket.clearOncePostHooks();
        return accountID;
    }
    else
        return -1;
}

void h_SendConnectResponse(unsigned int address, unsigned int port, int unk, const char* message)
{
    subhook::ScopedHookRemove remove(&SendConnectResponse.hook);
    char* nonConstMessage = strdup(message);
    bool shouldOverride = false;
    for (auto callback : SendConnectResponse.callbacks)
        shouldOverride |= callback(address, port, unk, nonConstMessage);
    SendConnectResponse.clearOnceHooks();
    if (!shouldOverride)
    {
        const char* constMessage = nonConstMessage;
        Engine::serverSendConnectResponse(address, port, unk, constMessage);
        for (auto postCallback : SendConnectResponse.postCallbacks)
            postCallback(address, port, unk, constMessage);
        SendConnectResponse.clearOncePostHooks();
    }
}

void h_ArmHuman(int human, int weapon, int magCount)
{
    subhook::ScopedHookRemove remove(&ArmHuman.hook);
    bool shouldOverride = false;
    for (auto callback : ArmHuman.callbacks)
        shouldOverride |= callback(human, weapon, magCount);
    ArmHuman.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::scenarioArmHuman(human, weapon, magCount);
        for (auto postCallback : ArmHuman.postCallbacks)
            postCallback(human, weapon, magCount);
        ArmHuman.clearOncePostHooks();
    }
}

int h_LinkItem(int itemID, int childItemID, int parentHumanID, int slot)
{
    subhook::ScopedHookRemove remove(&LinkItem.hook);
    // Checks if it's the scenario of a human picking an item up off the ground.
    bool isPickUp = parentHumanID != -1 && Engine::items[itemID].parentHumanID == -1;
    bool shouldOverride = false;
    unsigned short i = 0;
    for (auto callback : LinkItem.callbacks)
    {
        if (LinkItem.parallelInfoVec[i] == NOT_SPECIAL)
            shouldOverride |= callback(itemID, childItemID, parentHumanID, slot);
        else if (isPickUp && itemID == LinkItem.parallelInfoVec[i])
            shouldOverride |= callback(itemID, childItemID, parentHumanID, slot);
        else if (isPickUp && itemID == LinkItem.parallelInfoVec[i] - MAX_NUM_OF_ITEMS)
        {
            shouldOverride |= callback(itemID, childItemID, parentHumanID, slot);
            LinkItem.removeHook(i);
        }
        i++;
    }
    LinkItem.clearOnceHooks();
    if (!shouldOverride)
    {
        int ret = Engine::linkItem(itemID, childItemID, parentHumanID, slot);
        for (auto postCallback : LinkItem.postCallbacks)
            postCallback((bool)ret, itemID, childItemID, parentHumanID, slot);
        LinkItem.clearOncePostHooks();
        return ret;
    }
    else
        return -1;
}

int h_ComputerInput(int itemID, unsigned int character)
{
    subhook::ScopedHookRemove remove(&ComputerInput.hook);
    bool shouldOverride = false;
    for (auto callback : ComputerInput.callbacks)
        shouldOverride |= callback(itemID, character);
    ComputerInput.clearOnceHooks();
    if (!shouldOverride)
    {
        int ret = Engine::itemComputerInput(itemID, character);
        for (auto postCallback : ComputerInput.postCallbacks)
            postCallback(itemID, character);
        ComputerInput.clearOncePostHooks();
        return ret;
    }
    else
        return -1;
}

void h_WeaponSimulation(int itemID)
{
    subhook::ScopedHookRemove remove(&WeaponSimulation.hook);
    bool shouldOverride = false;
    for (auto callback : WeaponSimulation.callbacks)
        shouldOverride |= callback(itemID);
    WeaponSimulation.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::itemWeaponSimulation(itemID);
        for (auto postCallback : WeaponSimulation.postCallbacks)
            postCallback(itemID);
        WeaponSimulation.clearOncePostHooks();
    }
}

void h_SetBaseDoorState(int teamID, int state)
{
    subhook::ScopedHookRemove remove(&SetBaseDoorState.hook);
    bool shouldOverride = false;
    for (auto callback : SetBaseDoorState.callbacks)
        shouldOverride |= callback(teamID, state);
    SetBaseDoorState.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::setBaseDoorState(teamID, state);
        for (auto postCallback : SetBaseDoorState.postCallbacks)
            postCallback(teamID, state);
        SetBaseDoorState.clearOncePostHooks();
    }
}

void h_HumanDamage(int humanID, int bone, int unk, int damage)
{
    subhook::ScopedHookRemove remove(&HumanDamage.hook);
    bool shouldOverride = false;
    for (auto callback : HumanDamage.callbacks)
        shouldOverride |= callback(humanID, bone, unk, damage);
    HumanDamage.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::humanApplyDamage(humanID, bone, unk, damage);
        for (auto postCallback : HumanDamage.postCallbacks)
            postCallback(humanID, bone, unk, damage);
        HumanDamage.clearOncePostHooks();
    }
}

void h_VehicleDamage(int vehicleID, int damage)
{
    subhook::ScopedHookRemove remove(&VehicleDamage.hook);
    bool shouldOverride = false;
    for (auto callback : VehicleDamage.callbacks)
        shouldOverride |= callback(vehicleID, damage);
    VehicleDamage.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::vehicleApplyDamage(vehicleID, damage);
        for (auto postCallback : VehicleDamage.postCallbacks)
            postCallback(vehicleID, damage);
        VehicleDamage.clearOncePostHooks();
    }
}

void h_HumanCollisionVehicle(int humanID, int vehicleID)
{
    subhook::ScopedHookRemove remove(&HumanCollisionVehicle.hook);
    bool shouldOverride = false;
    for (auto callback : HumanCollisionVehicle.callbacks)
        shouldOverride |= callback(humanID, vehicleID);
    HumanCollisionVehicle.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::humanCollisionVehicle(humanID, vehicleID);
        for (auto postCallback : HumanCollisionVehicle.postCallbacks)
            postCallback(humanID, vehicleID);
        HumanCollisionVehicle.clearOncePostHooks();
    }
}

void h_HumanLimbInverseKinematics(int humanID, int trunkBoneID, int branchBoneID,
                                  Vector* destination, RotMatrix* destinationAxis,
                                  Vector* vecA, float a, float rot,
                                  float strength, float* d,
                                  Vector* vecB, Vector* vecC, Vector* vecD,
                                  char flags)
{
    subhook::ScopedHookRemove remove(&HumanLimbInverseKinematics.hook);
    bool shouldOverride = false;
    for (auto callback : HumanLimbInverseKinematics.callbacks)
        shouldOverride |= callback(humanID, trunkBoneID, branchBoneID, destination, destinationAxis, vecA, a, rot, strength, d, vecB, vecC, vecD, flags);
    HumanLimbInverseKinematics.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::humanLimbInverseKinematics(humanID, trunkBoneID, branchBoneID, destination, destinationAxis, vecA, a, rot, strength, d, vecB, vecC, vecD, flags);
        for (auto postCallback : HumanLimbInverseKinematics.postCallbacks)
            postCallback(humanID, trunkBoneID, branchBoneID, destination, destinationAxis, vecA, a, rot, strength, d, vecB, vecC, vecD, flags);
        HumanLimbInverseKinematics.clearOncePostHooks();
    }
}

void h_GrenadeExplosion(int grenadeID)
{
    subhook::ScopedHookRemove remove(&GrenadeExplosion.hook);
    bool shouldOverride = false;
    for (auto callback : GrenadeExplosion.callbacks)
        shouldOverride |= callback(grenadeID);
    GrenadeExplosion.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::grenadeExplosion(grenadeID);
        for (auto postCallback : GrenadeExplosion.postCallbacks)
            postCallback(grenadeID);
        GrenadeExplosion.clearOncePostHooks();
    }
}

void h_PlayerDeathTax(int playerID)
{
    subhook::ScopedHookRemove remove(&PlayerDeathTax.hook);
    bool shouldOverride = false;
    for (auto callback : PlayerDeathTax.callbacks)
        shouldOverride |= callback(playerID);
    PlayerDeathTax.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::playerDeathTax(playerID);
        for (auto postCallback : PlayerDeathTax.postCallbacks)
            postCallback(playerID);
        PlayerDeathTax.clearOncePostHooks();
    }
}

void h_AccountDeathTax(int accountID)
{
    subhook::ScopedHookRemove remove(&AccountDeathTax.hook);
    bool shouldOverride = false;
    for (auto callback : AccountDeathTax.callbacks)
        shouldOverride |= callback(accountID);
    AccountDeathTax.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::accountDeathTax(accountID);
        for (auto postCallback : AccountDeathTax.postCallbacks)
            postCallback(accountID);
        AccountDeathTax.clearOncePostHooks();
    }
}

void h_PlayerGiveWantedLevel(int playerID, int victimPlayerID, int basePoints)
{
    subhook::ScopedHookRemove remove(&PlayerGiveWantedLevel.hook);
    bool shouldOverride = false;
    for (auto callback : PlayerGiveWantedLevel.callbacks)
        shouldOverride |= callback(playerID, victimPlayerID, basePoints);
    PlayerGiveWantedLevel.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::playerGiveWantedLevel(playerID, victimPlayerID, basePoints);
        for (auto postCallback : PlayerGiveWantedLevel.postCallbacks)
            postCallback(playerID, victimPlayerID, basePoints);
        PlayerGiveWantedLevel.clearOncePostHooks();
    }
}

void h_CollideBodies(int aBodyID, int bBodyID, Vector* aLocalPos,
                     Vector* bLocalPos, Vector* normal, float a,
                     float b, float c, float d)
{
    subhook::ScopedHookRemove remove(&CollideBodies.hook);
    bool shouldOverride = false;
    for (auto callback : CollideBodies.callbacks)
        shouldOverride |= callback(aBodyID, bBodyID, aLocalPos, bLocalPos, normal, a, b, c, d);
    CollideBodies.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::addCollisionRigidBodyOnRigidBody(aBodyID, bBodyID, aLocalPos, bLocalPos, normal, a, b, c, d);
        for (auto postCallback : CollideBodies.postCallbacks)
            postCallback(aBodyID, bBodyID, aLocalPos, bLocalPos, normal, a, b, c, d);
        CollideBodies.clearOncePostHooks();
    }
}

void h_CollideBodyWithLevel(int bodyID, Vector* localPos, Vector* normal,
                                    float a, float b, float c, float d)
{
    subhook::ScopedHookRemove remove(&CollideBodyWithLevel.hook);
    bool shouldOverride = false;
    for (auto callback : CollideBodyWithLevel.callbacks)
        shouldOverride |= callback(bodyID, localPos, normal, a, b, c, d);
    CollideBodyWithLevel.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::addCollisionRigidBodyOnLevel(bodyID, localPos, normal, a, b, c, d);
        for (auto postCallback : CollideBodyWithLevel.postCallbacks)
            postCallback(bodyID, localPos, normal, a, b, c, d);
        CollideBodyWithLevel.clearOncePostHooks();
    }
}

int h_CreatePlayer()
{
    subhook::ScopedHookRemove remove(&CreatePlayer.hook);
    bool shouldOverride = false;
    for (auto callback : CreatePlayer.callbacks)
        shouldOverride |= callback();
    CreatePlayer.clearOnceHooks();
    if (!shouldOverride)
    {
        int ret = Engine::createPlayer();
        for (auto postCallback : CreatePlayer.postCallbacks)
            postCallback(ret);
        CreatePlayer.clearOncePostHooks();
        return ret;
    }
    else
        return -1;
}

void h_DeletePlayer(int playerID)
{
    subhook::ScopedHookRemove remove(&DeletePlayer.hook);
    bool shouldOverride = false;
    for (auto callback : DeletePlayer.callbacks)
        shouldOverride |= callback(playerID);
    DeletePlayer.clearOnceHooks();
    if (!shouldOverride)
    {
        playerData[playerID].clear();
        Engine::deletePlayer(playerID);
        for (auto postCallback : DeletePlayer.postCallbacks)
            postCallback(playerID);
        DeletePlayer.clearOncePostHooks();
    }
}

int h_CreateHuman(Vector* pos, RotMatrix* rot, int playerID)
{
    subhook::ScopedHookRemove remove(&CreateHuman.hook);
    bool shouldOverride = false;
    for (auto callback : CreateHuman.callbacks)
        shouldOverride |= callback(pos, rot, playerID);
    CreateHuman.clearOnceHooks();
    if (!shouldOverride)
    {
        int humanID = Engine::createHuman(pos, rot, playerID);
        for (auto postCallback : CreateHuman.postCallbacks)
            postCallback(humanID, pos, rot, playerID);
        CreateHuman.clearOncePostHooks();
        return humanID;
    }
    else
        return -1;
}

void h_DeleteHuman(int humanID)
{
    subhook::ScopedHookRemove remove(&DeleteHuman.hook);
    bool shouldOverride = false;
    for (auto callback : DeleteHuman.callbacks)
        shouldOverride |= callback(humanID);
    DeleteHuman.clearOnceHooks();
    if (!shouldOverride)
    {
        humanData[humanID].clear();
        Engine::deleteHuman(humanID);
        for (auto postCallback : DeleteHuman.postCallbacks)
            postCallback(humanID);
        DeleteHuman.clearOncePostHooks();
    }
}

int h_CreateItem(int type, Vector* pos, Vector* vel, RotMatrix* rot)
{
    subhook::ScopedHookRemove remove(&CreateItem.hook);
    bool shouldOverride = false;
    for (auto callback : CreateItem.callbacks)
        shouldOverride |= callback(type, pos, vel, rot);
    CreateItem.clearOnceHooks();
    if (!shouldOverride)
    {
        int itemID = Engine::createItem(type, pos, vel, rot);
        for (auto postCallback : CreateItem.postCallbacks)
            postCallback(itemID, type, pos, vel, rot);
        CreateItem.clearOncePostHooks();
        return itemID;
    }
    else
        return -1;
}

void h_DeleteItem(int itemID)
{
    subhook::ScopedHookRemove remove(&DeleteItem.hook);
    for (int i = 0; i < LinkItem.parallelInfoVec.size(); i++)
        if (itemID == LinkItem.parallelInfoVec[i] ||
            itemID == LinkItem.parallelInfoVec[i] - MAX_NUM_OF_ITEMS) LinkItem.removeHook(i);

    bool shouldOverride = false;
    for (auto callback : DeleteItem.callbacks)
        shouldOverride |= callback(itemID);
    DeleteItem.clearOnceHooks();
    if (!shouldOverride)
    {
        itemData[itemID].clear();
        Engine::deleteItem(itemID);
        for (auto postCallback : DeleteItem.postCallbacks)
            postCallback(itemID);
        DeleteItem.clearOncePostHooks();
    }
}

int h_CreateVehicle(int type, Vector* pos, Vector* vel, RotMatrix* rot, int color)
{
    subhook::ScopedHookRemove remove(&CreateVehicle.hook);
    bool shouldOverride = false;
    for (auto callback : CreateVehicle.callbacks)
        shouldOverride |= callback(type, pos, vel, rot, color);
    CreateVehicle.clearOnceHooks();
    if (!shouldOverride)
    {
        int vehicleID = Engine::createVehicle(type, pos, vel, rot, color);
        for (auto postCallback : CreateVehicle.postCallbacks)
            postCallback(vehicleID, type, pos, vel, rot, color);
        CreateVehicle.clearOncePostHooks();
        return vehicleID;
    }
    else
        return -1;
}

void h_DeleteVehicle(int vehicleID)
{
    subhook::ScopedHookRemove remove(&DeleteVehicle.hook);
    bool shouldOverride = false;
    for (auto callback : DeleteVehicle.callbacks)
        shouldOverride |= callback(vehicleID);
    DeleteVehicle.clearOnceHooks();
    if (!shouldOverride)
    {
        vehicleData[vehicleID].clear();
        Engine::deleteVehicle(vehicleID);
        for (auto postCallback : DeleteVehicle.postCallbacks)
            postCallback(vehicleID);
        DeleteVehicle.clearOncePostHooks();
    }
}

int h_CreateRigidBody(int type, Vector* pos, RotMatrix* rot, Vector* vel,
                      Vector* scale, float mass)
{
    subhook::ScopedHookRemove remove(&CreateRigidBody.hook);
    bool shouldOverride = false;
    for (auto callback : CreateRigidBody.callbacks)
        shouldOverride |= callback(type, pos, rot, vel, scale, mass);
    CreateRigidBody.clearOnceHooks();
    if (!shouldOverride)
    {
        int rigidBodyID = Engine::createRigidBody(type, pos, rot, vel, scale, mass);
        if (rigidBodyID != -1)
            bodyData[rigidBodyID].clear();
        for (auto postCallback : CreateRigidBody.postCallbacks)
            postCallback(rigidBodyID, type, pos, rot, vel, scale, mass);
        CreateRigidBody.clearOncePostHooks();
        return rigidBodyID;
    }
    else
        return -1;
}

int h_PlayerMessage(int playerID, char* message)
{
    subhook::ScopedHookRemove remove(&PlayerMessage.hook);
    bool shouldOverride = false;
    for (auto callback : PlayerMessage.callbacks)
        shouldOverride |= callback(playerID, message);
    PlayerMessage.clearOnceHooks();
    if (!shouldOverride)
    {
        int ret = Engine::serverPlayerMessage(playerID, message);
        for (auto postCallback : PlayerMessage.postCallbacks)
            postCallback(playerID, message);
        PlayerMessage.clearOncePostHooks();
        return ret;
    }
    else
        return -1;
}

void h_EventMessage(int type, char* message, int speakerID, int distance)
{
    subhook::ScopedHookRemove remove(&EventMessage.hook);
    bool shouldOverride = false;
    for (auto callback : EventMessage.callbacks)
        shouldOverride |= callback(type, message, speakerID, distance);
    EventMessage.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::createEventMessage(type, message, speakerID, distance);
        for (auto postCallback : EventMessage.postCallbacks)
            postCallback(type, message, speakerID, distance);
        EventMessage.clearOncePostHooks();
    }
}

void h_EventUpdatePlayer(int playerID)
{
    subhook::ScopedHookRemove remove(&EventUpdatePlayer.hook);
    bool shouldOverride = false;
    for (auto callback : EventUpdatePlayer.callbacks)
        shouldOverride |= callback(playerID);
    EventUpdatePlayer.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::createEventUpdatePlayer(playerID);
        for (auto postCallback : EventUpdatePlayer.postCallbacks)
            postCallback(playerID);
        EventUpdatePlayer.clearOncePostHooks();
    }
}

void h_EventUpdateItem(int itemID)
{
    subhook::ScopedHookRemove remove(&EventUpdateItem.hook);
    bool shouldOverride = false;
    for (auto callback : EventUpdateItem.callbacks)
        shouldOverride |= callback(itemID);
    EventUpdateItem.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::createEventUpdateItem(itemID);
        for (auto postCallback : EventUpdateItem.postCallbacks)
            postCallback(itemID);
        EventUpdateItem.clearOncePostHooks();
    }
}

void h_EventUpdateVehicle(int vehicleID, int updateType, int partID,
                                Vector* pos, Vector* normal)
{
    subhook::ScopedHookRemove remove(&EventUpdateVehicle.hook);
    bool shouldOverride = false;
    for (auto callback : EventUpdateVehicle.callbacks)
        shouldOverride |= callback(vehicleID, updateType, partID, pos, normal);
    EventUpdateVehicle.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::createEventUpdateVehicle(vehicleID, updateType, partID, pos, normal);
        for (auto postCallback : EventUpdateVehicle.postCallbacks)
            postCallback(vehicleID, updateType, partID, pos, normal);
        EventUpdateVehicle.clearOncePostHooks();
    }
}

void h_EventSound(int soundType, Vector* pos, float volume, float pitch)
{
    subhook::ScopedHookRemove remove(&EventSound.hook);
    bool shouldOverride = false;
    for (auto callback : EventSound.callbacks)
        shouldOverride |= callback(soundType, pos, volume, pitch);
    EventSound.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::createEventSound(soundType, pos, volume, pitch);
        for (auto postCallback : EventSound.postCallbacks)
            postCallback(soundType, pos, volume, pitch);
        EventSound.clearOncePostHooks();
    }
}

void h_EventBulletHit(int unk, int hitType, Vector* pos, Vector* normal)
{
    subhook::ScopedHookRemove reomve(&EventBulletHit.hook);
    bool shouldOverride = false;
    for (auto callback : EventBulletHit.callbacks)
        shouldOverride |= callback(unk, hitType, pos, normal);
    EventBulletHit.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::createEventBulletHit(unk, hitType, pos, normal);
        for (auto postCallback : EventBulletHit.postCallbacks)
            postCallback(unk, hitType, pos, normal);
        EventBulletHit.clearOncePostHooks();
    }
}

void h_EventGlassBreak(int param_1, int param_2, int param_3, int param_4,
                             int param_5, int param_6, int* param_7, int* param_8)
{
    subhook::ScopedHookRemove remove(&EventGlassBreak.hook);
    bool shouldOverride = false;
    for (auto callback : EventGlassBreak.callbacks)
        shouldOverride |= callback(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8);
    EventGlassBreak.clearOnceHooks();
    if (!shouldOverride)
    {
        Engine::createEventGlassBreak(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8);
        for (auto postCallback : EventGlassBreak.postCallbacks)
            postCallback(param_1, param_2, param_3, param_4, param_5, param_6, param_7, param_8);
        EventGlassBreak.clearOncePostHooks();
    }
}

void InitializeHooks()
{
    ResetGame.install(Engine::resetGame, h_ResetGame);
    EliminatorAnnounceDeath.install(Engine::eliminatorAnnounceDeath, h_EliminatorAnnounceDeath);
    Logic.install(Engine::logicSimulation, h_Logic);
    LogicRace.install(Engine::logicSimulationRace, h_LogicRace);
    LogicRound.install(Engine::logicSimulationRound, h_LogicRound);
    LogicWorld.install(Engine::logicSimulationWorld, h_LogicWorld);
    LogicEliminator.install(Engine::logicSimulationTerminator, h_LogicTerminator);
    LogicCoop.install(Engine::logicSimulationCoop, h_LogicCoop);
    LogicVersus.install(Engine::logicSimulationVersus, h_LogicVersus);
    BulletSimulation.install(Engine::bulletSimulation, h_BulletSimulation);
    PlayerActions.install(Engine::logicPlayerActions, h_PlayerActions);
    Physics.install(Engine::physicsSimulation, h_Physics);
    ServerSend.install(Engine::serverSend, h_ServerSend);
    CalculatePlayerVoice.install(Engine::calculatePlayerVoice, h_CalculatePlayerVoice);
    EconomyCarMarket.install(Engine::economyCarMarket, h_EconomyCarMarket);
    AccountTicket.install(Engine::createAccountByJoinTicket, h_AccountTicket);
    SendConnectResponse.install(Engine::serverSendConnectResponse, h_SendConnectResponse);
    ArmHuman.install(Engine::scenarioArmHuman, h_ArmHuman);
    LinkItem.install(Engine::linkItem, h_LinkItem);
    ComputerInput.install(Engine::itemComputerInput, h_ComputerInput);
    WeaponSimulation.install(Engine::itemWeaponSimulation, h_WeaponSimulation);
    SetBaseDoorState.install(Engine::setBaseDoorState, h_SetBaseDoorState);
    HumanDamage.install(Engine::humanApplyDamage, h_HumanDamage);
    VehicleDamage.install(Engine::vehicleApplyDamage, h_VehicleDamage);
    HumanCollisionVehicle.install(Engine::humanCollisionVehicle, h_HumanCollisionVehicle);
    HumanLimbInverseKinematics.install(Engine::humanLimbInverseKinematics, h_HumanLimbInverseKinematics);
    GrenadeExplosion.install(Engine::grenadeExplosion, h_GrenadeExplosion);
    PlayerDeathTax.install(Engine::playerDeathTax, h_PlayerDeathTax);
    AccountDeathTax.install(Engine::accountDeathTax, h_AccountDeathTax);
    PlayerGiveWantedLevel.install(Engine::playerGiveWantedLevel, h_PlayerGiveWantedLevel);
    CollideBodies.install(Engine::addCollisionRigidBodyOnRigidBody, h_CollideBodies);
    CollideBodyWithLevel.install(Engine::addCollisionRigidBodyOnLevel, h_CollideBodyWithLevel);
    CreatePlayer.install(Engine::createPlayer, h_CreatePlayer);
    DeletePlayer.install(Engine::deletePlayer, h_DeletePlayer);
    CreateHuman.install(Engine::createHuman, h_CreateHuman);
    DeleteHuman.install(Engine::deleteHuman, h_DeleteHuman);
    CreateItem.install(Engine::createItem, h_CreateItem);
    DeleteItem.install(Engine::deleteItem, h_DeleteItem);
    CreateVehicle.install(Engine::createVehicle, h_CreateVehicle);
    DeleteVehicle.install(Engine::deleteVehicle, h_DeleteVehicle);
    CreateRigidBody.install(Engine::createRigidBody, h_CreateRigidBody);
    PlayerMessage.install(Engine::serverPlayerMessage, h_PlayerMessage);
    EventMessage.install(Engine::createEventMessage, h_EventMessage);
    EventUpdatePlayer.install(Engine::createEventUpdatePlayer, h_EventUpdatePlayer);
    EventUpdateItem.install(Engine::createEventUpdateItem, h_EventUpdateItem);
    EventUpdateVehicle.install(Engine::createEventUpdateVehicle, h_EventUpdateVehicle);
    EventSound.install(Engine::createEventSound, h_EventSound);
    EventBulletHit.install(Engine::createEventBulletHit, h_EventBulletHit);
    EventGlassBreak.install(Engine::createEventGlassBreak, h_EventGlassBreak);
}