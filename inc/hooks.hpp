/**
 * @brief Hooks for functions in subrosadedicated.x64
 */
#pragma once

#include "hook.hpp"

void InitializeHooks();

extern voidFuncHook ResetGame;
extern voidIntFuncHook EliminatorAnnounceDeath;
extern voidFuncHook Logic;
extern voidFuncHook LogicRace;
extern voidFuncHook LogicRound;
extern voidFuncHook LogicWorld;
extern voidFuncHook LogicEliminator;
extern voidFuncHook LogicCoop;
extern voidFuncHook LogicVersus;
extern voidIntFuncHook PlayerActions;
extern voidFuncHook Physics;
extern voidFuncHook ServerSend;
extern voidDoubleIntFuncHook CalculatePlayerVoice;
extern voidFuncHook EconomyCarMarket;
extern createAccountByJoinTicketFuncHook AccountTicket;
extern serverSendConnectResponseFuncHook SendConnectResponse;
extern voidTripleIntFuncHook ArmHuman;
extern linkItemFuncHook LinkItem;
extern itemComputerInputFuncHook ComputerInput;
extern voidIntFuncHook WeaponSimulation;
extern voidDoubleIntFuncHook SetBaseDoorState;
extern humanApplyDamageFuncHook HumanDamage;
extern voidDoubleIntFuncHook VehicleDamage;
extern voidDoubleIntFuncHook HumanCollisionVehicle;
extern humanLimbInverseKinematicsFuncHook HumanLimbInverseKinematics;
extern voidIntFuncHook GrenadeExplosion;
extern voidIntFuncHook PlayerDeathTax;
extern voidIntFuncHook AccountDeathTax;
extern voidTripleIntFuncHook PlayerGiveWantedLevel;
extern collideBodiesFuncHook CollideBodies;
extern collideBodyWithLevelFuncHook CollideBodyWithLevel;
extern createPlayerFuncHook CreatePlayer;
extern voidIntFuncHook DeletePlayer;
extern createHumanFuncHook CreateHuman;
extern voidIntFuncHook DeleteHuman;
extern createItemFuncHook CreateItem;
extern voidIntFuncHook DeleteItem;
extern createVehicleFuncHook CreateVehicle;
extern voidIntFuncHook DeleteVehicle;
extern createRigidBodyFuncHook CreateRigidBody;
extern serverPlayerMessageFuncHook PlayerMessage;
extern eventMessageFuncHook EventMessage;
extern voidIntFuncHook EventUpdatePlayer;
extern voidIntFuncHook EventUpdateItem;
extern eventUpdateVehicleFuncHook EventUpdateVehicle;
extern eventSoundFuncHook EventSound;
extern eventBulletHitFuncHook EventBulletHit;
extern voidFuncHook EventUpdateStocks;
extern eventGlassBreakFuncHook EventGlassBreak;

extern voidFuncHook FUNH73910;