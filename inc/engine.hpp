/**
 * @file  engine.hpp
 * @brief The engine interface for the game engines functions and data.
 */
#pragma once

#include <string>

#include "engine_structs.hpp"

enum MessageTypeEnum {
  MESSAGE_GLOBAL = 0,  // Messages in global chat. If variation is 1 then it's in dead chat and the target is the playerID
  MESSAGE_HUMAN = 1,   // Message sent by a human. Target is the humanId and variation is the volume (whisper 0, talk 1, yell 2)
  MESSAGE_ITEM = 2,    // Message sent by an item (phones / walkie talkies). Target is the itemId and variation is the volume.
  MESSAGE_BANNER = 3,  // Banner message used to announce death in eliminator.
  MESSAGE_ADMIN = 4,   // Message in chat only visible by admins.
  MESSAGE_BILLBOARD = 5, // Billboard
  MESSAGE_PLAYER = 6,  // Message sent directly to a player displayed in red. Target is the playerId.
};

enum HitTypeEnum {
  HIT_BULLET_HOLE = 0, // Hit that creates a bullet hole (e.g. on a wall)
  HIT_BODY = 1,        // Hitting a human
  HIT_CAR = 2,         // Hitting a car
  HIT_BLOOD_DRIP = 3   // Hitting that causes a blood drip
};

enum VehicleUpdateTypeEnum {
  UPDATE_WINDOW = 0,
  UPDATE_TIRE = 1,
  UPDATE_BODY = 2
};

namespace Engine {
void InitializeEngine(char* base);

extern unsigned int* version;
extern unsigned int* subVersion;
extern char* serverName;
extern unsigned int* serverPort;

extern int* packetSize;
extern unsigned char* packet;

extern int* gameType;
extern char* mapName;
extern char* loadedMapName;
extern int* dayOfWeek; // Marker
extern int* gameState;
extern int* gameTimer;
extern int* ticksSinceReset;
extern unsigned int* sunTime;

extern int* serverMaxBytesPerSecond;
extern char* adminPassword;
extern int* isPassworded;
extern char* password;
extern int* maxPlayers;

namespace World {
extern int* traffic;
extern int* startCash;
extern int* minCash;
extern bool* showJoinExit;
extern bool* respawnTeam;
namespace Crime {
extern int* civCiv;
extern int* civTeam;
extern int* teamCiv;
extern int* teamTeam;
extern int* teamTeamInBase;
extern int* noSpawn;
};  // namespace Crime
};  // namespace World

namespace Round {
extern int* roundTime;
extern int* startCash;
extern bool* weekly;
extern bool* bonusRatio;
extern int* teamDamage;
};  // namespace Round

extern int* isLevelLoaded;
extern float* gravity;
extern float originalGravity;

extern LineIntersectResult* lineIntersectResult;

extern Connection* connections;
extern Account* accounts;
extern Voice* voices;
extern Player* players;
extern Human* humans;
extern ItemType* itemTypes;
extern Item* items;
extern VehicleType* vehicleTypes;
extern Vehicle* vehicles;
extern Bullet* bullets;
extern RigidBody* bodies;
extern Bond* bonds;
extern Street* streets;
extern StreetIntersection* streetIntersections;
extern TrafficCar* trafficCars;
extern Building* buildings;
extern Event* events;

extern unsigned int* numConnections;
extern unsigned int* numBullets;
extern unsigned int* numStreets;
extern unsigned int* numStreetIntersections;
extern unsigned int* numTrafficCars;
extern unsigned int* numBuildings;
extern unsigned short* numEvents;

/*
  Misc
*/

extern int (*subRosaPuts)(const char* str);
extern int (*subRosa__printf_chk)(int flag, const char* format, ...);

extern void (*resetGame)();
extern void (*createTraffic)(int amount);
extern void (*trafficSimulation)();
extern void (*aiTrafficCar)(int id);
extern void (*aiTrafficCarDestination)(int id, int a, int b, int c, int d);
extern void (*eliminatorAnnounceDeath)(int playerId);

extern int (*areaCreateBlock)(int zero, int blockX, int blockY, int blockZ,
                              unsigned int flags, short unk[8]);
extern int (*areaDeleteBlock)(int zero, int blockX, int blockY, int blockZ);

extern void (*logicSimulation)();
extern void (*logicSimulationRace)();
extern void (*logicSimulationRound)();
extern void (*logicSimulationWorld)();
extern void (*logicSimulationTerminator)();
extern void (*logicSimulationCoop)();
extern void (*logicSimulationVersus)();
extern void (*logicPlayerActions)(int id);

extern void (*physicsSimulation)();
extern void (*rigidBodySimulation)();

extern int (*serverReceive)();
extern void (*serverSend)();

extern int (*packetWrite)(void* source, int elementSize, int elementCount);
extern void (*calculatePlayerVoice)(int connectionID, int playerID);
extern int (*sendPacket)(unsigned int address, unsigned short port);
extern void (*bulletSimulation)();
extern void (*bulletTimeToLive)();

extern void (*economyCarMarket)();
extern void (*saveAccountsServer)();

extern int (*createAccountByJoinTicket)(int identifier, unsigned int ticket);
extern void (*serverSendConnectResponse)(unsigned int address, unsigned int port,
                                         int unk, const char* message);

extern void (*scenarioArmHuman)(int human, int weapon, int magCount);
extern int (*linkItem)(int itemID, int childItemID, int parentHumanID, int slot);

extern int (*itemSetMemo)(int itemID, const char* memo);
extern int (*itemComputerTransmitLine)(int itemID, unsigned int line);
extern int (*itemCashAddBill)(int itemID, int zero, int amount);
extern void (*itemCashRemoveBill)(int itemID, int amount);
extern int (*itemCashGetBillValue)(int itemID);
extern void (*itemComputerIncrementLine)(int id);
extern int (*itemComputerInput)(int itemID, unsigned int character);
extern void (*itemWeaponSimulation)(int itemID);
extern void (*itemLogic)();
extern void (*setBaseDoorState)(int teamID, int state);

extern void (*humanApplyDamage)(int humanID, int bone, int unk, int damage);
extern void (*vehicleApplyDamage)(int vehicleID, int damage);
extern void (*humanCollisionVehicle)(int humanID, int vehicleID);
extern void (*humanLimbInverseKinematics)(int humanID, int trunkBoneID, int branchBoneID,
                                          Vector* destination, RotMatrix* destinationAxis,
                                          Vector* vecA, float a, float rot,
                                          float strength, float* d /* Quaternion? */,
                                          Vector* vecB, Vector* vecC, Vector* vecD,
                                          char flags);
                                        
extern void (*grenadeExplosion)(int grenadeID);
extern int (*serverPlayerMessage)(int playerID, char* message);
extern void (*playerAI)(int playerID);
extern void (*playerDeathTax)(int playerID);
extern void (*accountDeathTax)(int accountID);
extern void (*playerGiveWantedLevel)(int playerID, int victimPlayerID, int basePoints);
extern bool (*isInsideBuilding)(float clearance, int buildingID, Vector* pos);

extern int (*createBondRigidBodyToRigidBody)(int aBodyID, int bBodyID, Vector* aLocalPos,
                                             Vector* bLocalPos);
extern int (*createBondRigidBodyRotRigidBody)(int aBodyID, int bBodyID);
extern int (*createBondRigidBodyToLevel)(int bodyID, Vector* localPos, Vector* globalPos);
extern void (*addCollisionRigidBodyOnRigidBody)(int aBodyID, int bBodyID, Vector* aLocalPos,
                                                Vector* bLocalPos, Vector* normal, float a,
                                                float b, float c, float d);
extern void (*addCollisionRigidBodyOnLevel)(int bodyID, Vector* localPos, Vector* normal,
                                            float a, float b, float c, float d);

// Object Handling

extern int (*createBullet)(int type, Vector* pos, Vector* vel, int playerID);
extern int (*createPlayer)();
extern void (*deletePlayer)(int playerID);
extern int (*createHuman)(Vector* pos, RotMatrix* rot, int playerID);
extern void (*deleteHuman)(int humanID);
extern int (*createItem)(int type, Vector* pos, Vector* vel, RotMatrix* rot);
extern void (*deleteItem)(int itemID);
extern int (*createRope)(Vector* pos, RotMatrix* rot);
extern int (*createVehicle)(int type, Vector* pos, Vector* vel, RotMatrix* rot, int color);
extern void (*deleteVehicle)(int vehicleID);
extern int (*createRigidBody)(int type, Vector* pos, RotMatrix* rot, Vector* vel,
                              Vector* scale, float mass);

// Events

extern void (*createEventMessage)(int type, char* message, int speakerID, int distance);
// Sends team, active, isBot, humanID, skinColor, hair, gender, head, necklace,
// eyeColor, tieColor, suitColor, shirtColor, hairColor, name
extern void (*createEventUpdatePlayer)(int playerID);
// Sends money, stocks, phoneNumber
extern void (*createEventUpdatePlayerFinance)(int playerID);
// Sends active, type, parentHumanID, parentItemID, parentSlot
extern void (*createEventUpdateItem)(int itemID);
// Sends type, color
extern void (*createEventCreateVehicle)(int vehicleID);
extern void (*createEventUpdateVehicle)(int vehicleID, int updateType, int partID,
                                        Vector* pos, Vector* normal);
extern void (*createEventSound)(int soundType, Vector* pos, float volume, float pitch);
extern void (*createEventExplosion)(int type, Vector* pos);
extern void (*createEventBullet)(int bulletType, Vector* pos, Vector* vel, int itemID);
extern void (*createEventBulletHit)(int unk, int hitType, Vector* pos, Vector* normal);
extern void (*createEventUpdateStocks)();
extern void (*createEventGlassBreak)(int param_1, int param_2, int param_3, int param_4,
                                     int param_5, int param_6, int* param_7, int* param_8);
extern void (*createEventOpenTeamDoor)(int teamID, int openState);

// Math

extern int (*lineIntersectLevel)(Vector* posA, Vector* posB, int includeCityObjects);
extern int (*lineIntersectHuman)(int humanID, Vector* posA, Vector* posB, float padding);
extern int (*lineIntersectVehicle)(int vehicleID, Vector* posA, Vector* posB, int includeWheels);
extern int (*lineIntersectTriangle)(Vector* outPos, Vector* normal,
                                    float* outFraction, Vector* posA,
                                    Vector* posB, Vector* triA,
                                    Vector* triB, Vector* triC);
};  // namespace Engine