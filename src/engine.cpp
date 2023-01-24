// Credit to RosaServer and RosaLink for the offsets.

#include "../inc/engine.hpp"
#include "../inc/util.hpp"

namespace Engine {
void InitializeEngine(char* base);

unsigned int* version;
unsigned int* subVersion;
char* serverName;
unsigned int* serverPort;

int* packetSize;
unsigned char* packet;

int* gameType;
char* mapName;
char* loadedMapName;
int* dayofWeek;
int* gameState;
int* gameTimer;
int* ticksSinceReset;
unsigned int* sunTime;

int* serverMaxBytesPerSecond;
char* adminPassword;
int* isPassworded;
char* password;
int* maxPlayers;

namespace World {
int* traffic;
int* startCash;
int* minCash;
bool* showJoinExit;
bool* respawnTeam;
namespace Crime {
int* civCiv;
int* civTeam;
int* teamCiv;
int* teamTeam;
int* teamTeamInBase;
int* noSpawn;
};  // namespace Crime
};  // namespace World

namespace Round {
int* roundTime;
int* startCash;
bool* weekly;
bool* bonusRatio;
int* teamDamage;
};  // namespace Round

int* isLevelLoaded;
float* gravity;
float originalGravity;

LineIntersectResult* lineIntersectResult;

Connection* connections;
Account* accounts;
Voice* voices;
Player* players;
Human* humans;
ItemType* itemTypes;
Item* items;
VehicleType* vehicleTypes;
Vehicle* vehicles;
Bullet* bullets;
RigidBody* bodies;
Bond* bonds;
Street* streets;
StreetIntersection* streetIntersections;
TrafficCar* trafficCars;
Building* buildings;
Event* events;

unsigned int* numConnections;
unsigned int* numBullets;
unsigned int* numStreets;
unsigned int* numStreetIntersections;
unsigned int* numTrafficCars;
unsigned int* numBuildings;
unsigned short* numEvents;

/*
  Misc
*/

int (*subRosaPuts)(const char* str);
int (*subRosa__printf_chk)(int flag, const char* format, ...);

void (*resetGame)();
void (*createTraffic)(int amount);
void (*trafficSimulation)();
void (*aiTrafficCar)(int id);
void (*aiTrafficCarDestination)(int id, int a, int b, int c, int d);
void (*eliminatorAnnounceDeath)(int playerId);

int (*areaCreateBlock)(int zero, int blockX, int blockY, int blockZ,
                              unsigned int flags, short unk[8]);
int (*areaDeleteBlock)(int zero, int blockX, int blockY, int blockZ);

void (*logicSimulation)();
void (*logicSimulationRace)();
void (*logicSimulationRound)();
void (*logicSimulationWorld)();
void (*logicSimulationTerminator)();
void (*logicSimulationCoop)();
void (*logicSimulationVersus)();
void (*logicPlayerActions)(int id);

void (*physicsSimulation)();
void (*rigidBodySimulation)();

int (*serverReceive)();
void (*serverSend)();

int (*packetWrite)(void* source, int elementSize, int elementCount);
void (*calculatePlayerVoice)(int connectionID, int playerID);
int (*sendPacket)(unsigned int address, unsigned short port);
void (*bulletSimulation)();
void (*bulletTimeToLive)();

void (*economyCarMarket)();
void (*saveAccountsServer)();

int (*createAccountByJoinTicket)(int identifier, unsigned int ticket);
void (*serverSendConnectResponse)(unsigned int address, unsigned int port,
                                         int unk, const char* message);

void (*scenarioArmHuman)(int human, int weapon, int magCount);
int (*linkItem)(int itemID, int childItemID, int parentHumanID, int slot);

int (*itemSetMemo)(int itemID, const char* memo);
int (*itemComputerTransmitLine)(int itemID, unsigned int line);
int (*itemCashAddBill)(int itemID, int zero, int amount);
void (*itemCashRemoveBill)(int itemID, int amount);
int (*itemCashGetBillValue)(int itemID);
void (*itemComputerIncrementLine)(int id);
int (*itemComputerInput)(int itemID, unsigned int character);
void (*itemWeaponSimulation)(int itemID);
void (*itemLogic)();
void (*setBaseDoorState)(int teamID, int state);

void (*humanApplyDamage)(int humanID, int bone, int unk, int damage);
void (*vehicleApplyDamage)(int vehicleID, int damage);
void (*humanCollisionVehicle)(int humanID, int vehicleID);
void (*humanLimbInverseKinematics)(int humanID, int trunkBoneID, int branchBoneID,
                                          Vector* destination, RotMatrix* destinationAxis,
                                          Vector* vecA, float a, float rot,
                                          float strength, float* d,
                                          Vector* vecB, Vector* vecC, Vector* vecD,
                                          char flags);
                                        
void (*grenadeExplosion)(int grenadeID);
int (*serverPlayerMessage)(int playerID, char* message);
void (*playerAI)(int playerID);
void (*playerDeathTax)(int playerID);
void (*accountDeathTax)(int accountID);
void (*playerGiveWantedLevel)(int playerID, int victimPlayerID, int basePoints);
bool (*isInsideBuilding)(float clearance, int buildingID, Vector* pos);

int (*createBondRigidBodyToRigidBody)(int aBodyID, int bBodyID, Vector* aLocalPos,
                                             Vector* bLocalPos);
int (*createBondRigidBodyRotRigidBody)(int aBodyID, int bBodyID);
int (*createBondRigidBodyToLevel)(int bodyID, Vector* localPos, Vector* globalPos);
void (*addCollisionRigidBodyOnRigidBody)(int aBodyID, int bBodyID, Vector* aLocalPos,
                                                Vector* bLocalPos, Vector* normal, float a,
                                                float b, float c, float d);
void (*addCollisionRigidBodyOnLevel)(int bodyID, Vector* localPos, Vector* normal,
                                            float a, float b, float c, float d);

// Object Handling

int (*createBullet)(int type, Vector* pos, Vector* vel, int playerID);
int (*createPlayer)();
void (*deletePlayer)(int playerID);
int (*createHuman)(Vector* pos, RotMatrix* rot, int playerID);
void (*deleteHuman)(int humanID);
int (*createItem)(int type, Vector* pos, Vector* vel, RotMatrix* rot);
void (*deleteItem)(int itemID);
int (*createRope)(Vector* pos, RotMatrix* rot);
int (*createVehicle)(int type, Vector* pos, Vector* vel, RotMatrix* rot, int color);
void (*deleteVehicle)(int vehicleID);
int (*createRigidBody)(int type, Vector* pos, RotMatrix* rot, Vector* vel,
                              Vector* scale, float mass);

// Events

void (*createEventMessage)(int type, char* message, int speakerID, int distance);
// Sends team, active, isBot, humanID, skinColor, hair, gender, head, necklace,
// eyeColor, tieColor, suitColor, shirtColor, hairColor, name
void (*createEventUpdatePlayer)(int playerID);
// Sends money, stocks, phoneNumber
void (*createEventUpdatePlayerFinance)(int playerID);
// Sends active, type, parentHumanID, parentItemID, parentSlot
void (*createEventUpdateItem)(int itemID);
// Sends type, color
void (*createEventCreateVehicle)(int vehicleID);
void (*createEventUpdateVehicle)(int vehicleID, int updateType, int partID,
                                        Vector* pos, Vector* normal);
void (*createEventSound)(int soundType, Vector* pos, float volume, float pitch);
void (*createEventExplosion)(int type, Vector* pos);
void (*createEventBullet)(int bulletType, Vector* pos, Vector* vel, int itemID);
void (*createEventBulletHit)(int unk, int hitType, Vector* pos, Vector* normal);
void (*createEventUpdateStocks)();
void (*createEventGlassBreak)(int param_1, int param_2, int param_3, int param_4,
                                     int param_5, int param_6, int* param_7, int* param_8);
void (*createEventOpenTeamDoor)(int teamID, int openState);

// Math

int (*lineIntersectLevel)(Vector* posA, Vector* posB, int includeCityObjects);
int (*lineIntersectHuman)(int humanID, Vector* posA, Vector* posB, float padding);
int (*lineIntersectVehicle)(int vehicleID, Vector* posA, Vector* posB, int includeWheels);
int (*lineIntersectTriangle)(Vector* outPos, Vector* normal,
                                    float* outFraction, Vector* posA,
                                    Vector* posB, Vector* triA,
                                    Vector* triB, Vector* triC);
};  // namespace Engine

namespace Engine {
void InitializeEngine(char* base)
{
 	// From RosaServer
	version = (unsigned int*)(base + 0x2e9f08);
	subVersion = (unsigned int*)(base + 0x2e9f04);
	serverPort = (unsigned int*)(base + 0x18db02a0);
	serverName = (char*)(base + 0x250ec1d4);
	serverPort = (unsigned int*)(base + 0x18db02a0);
	packetSize = (int*)(base + 0x39075c7c);
	packet = (unsigned char*)(base + 0x39075c84);
	serverMaxBytesPerSecond = (int*)(base + 0x18db02a4);
	adminPassword = (char*)(base + 0x18db06ac);
	isPassworded = (int*)(base + 0x250ec5f0);
	password = (char*)(base + 0x18db08ac);
	maxPlayers = (int*)(base + 0x250ec5f4);

	World::traffic = (int*)(base + 0x44f855e0);
	World::startCash = (int*)(base + 0x44f85608);
	World::minCash = (int*)(base + 0x44f8560c);
	World::showJoinExit = (bool*)(base + 0x44f85610);
	World::respawnTeam = (bool*)(base + 0x44f85614);
	World::Crime::civCiv = (int*)(base + 0x44f855e4);
	World::Crime::civTeam = (int*)(base + 0x44f855e8);
	World::Crime::teamCiv = (int*)(base + 0x44f855ec);
	World::Crime::teamTeam = (int*)(base + 0x44f855f0);
	World::Crime::teamTeamInBase = (int*)(base + 0x44f855f4);
	World::Crime::noSpawn = (int*)(base + 0x44f85600);

    Round::roundTime = (int*)(base + 0x44f855cc);
	Round::startCash = (int*)(base + 0x44f855d0);
	Round::weekly = (bool*)(base + 0x44f855d4);
	Round::bonusRatio = (bool*)(base + 0x44f855d8);
	Round::teamDamage = (int*)(base + 0x44f855dc);

    gameType = (int*)(base + 0x44ecaacc);
	mapName = (char*)(base + 0x44ecaad0);
	loadedMapName = (char*)(base + 0x39496124);
	//dayOfWeek = (int*)(base + 0x44ecace4); // I guessed at this offset. Hope it works!
	gameState = (int*)(base + 0x44ecacec);
	gameTimer = (int*)(base + 0x44ecacf4);
	ticksSinceReset = (int*)(base + 0x44ecad54);
	sunTime = (unsigned int*)(base + 0xdfb21e0);
	isLevelLoaded = (int*)(base + 0x39496120);

  	lineIntersectResult = (LineIntersectResult*)(base + 0x569ef720);

    connections = (Connection*)(base + 0x669b20);
	accounts = (Account*)(base + 0x357fd10);
	voices = (Voice*)(base + 0xaebed80);
	players = (Player*)(base + 0x15b35420);
	humans = (Human*)(base + 0xcefe1c8);
	itemTypes = (ItemType*)(base + 0x5a60d7c0);
	items = (Item*)(base + 0x8117920);
	vehicleTypes = (VehicleType*)(base + 0x4d03560);
	vehicles = (Vehicle*)(base + 0x1cf42740);
	bullets = (Bullet*)(base + 0x44835bc0);
	bodies = (RigidBody*)(base + 0x4f1ae0);
	bonds = (Bond*)(base + 0x24adc1c0);
	streets = (Street*)(base + 0x394b8188);
	streetIntersections = (StreetIntersection*)(base + 0x39496184);
	trafficCars = (TrafficCar*)(base + 0x5a80bea0);
	buildings = (Building*)(base + 0x3958a358);
	events = (Event*)(base + 0x5edcd80);
	numConnections = (unsigned int*)(base + 0x45ed7da8);
	numBullets = (unsigned int*)(base + 0x45e07380);
	numStreets = (unsigned int*)(base + 0x394b8184);
	numStreetIntersections = (unsigned int*)(base + 0x3949617c);
	numTrafficCars = (unsigned int*)(base + 0x15b253f8);
	numBuildings = (unsigned int*)(base + 0x3958a314);
	numEvents = (unsigned short*)(base + 0x45e07384);

	subRosaPuts = (int(*)(const char* str))(base + 0x1fd0);
	subRosa__printf_chk = (int(*)(int flag, const char* format, ...))(base + 0x2300);

	resetGame = (void(*)())(base + 0xbf380);
	createTraffic = (void(*)(int amount))(base + 0x9f690);
	trafficSimulation = (void(*)())(base + 0xa28d0);
	aiTrafficCar = (void(*)(int id))(base + 0xfe00);
	aiTrafficCarDestination = (void(*)(int id, int a, int b, int c, int d))(base + 0xf7a0);

	areaCreateBlock = (int(*)(int zero, int blockX, int blockY, int blockZ, 
							   unsigned int flags, short unk[8]))(base + 0x19920);
	areaDeleteBlock = (int(*)(int zero, int blockX, int blockY, int blockZ))(base + 0x13800);

	logicSimulation = (void(*)())(base + 0xc5f30);
	logicSimulationRace = (void(*)())(base + 0xc19d0);
	logicSimulationRound = (void(*)())(base + 0xc2150);
	logicSimulationWorld = (void(*)())(base + 0xc54e0);
	logicSimulationTerminator = (void(*)())(base + 0xc30d0);
	logicSimulationCoop = (void(*)())(base + 0xc1790);
	logicSimulationVersus = (void(*)())(base + 0xc4930);
	logicPlayerActions = (void(*)(int id))(base + 0xba950);

	physicsSimulation = (void(*)())(base + 0xa95e0);
	rigidBodySimulation = (void(*)())(base + 0x7f320);
	serverReceive = (int(*)())(base + 0xd0200);
	serverSend = (void(*)())(base + 0xcd200);
	packetWrite = (int(*)(void* source, int elementSize, int elementCount))(base + 0xc8230);
	calculatePlayerVoice = (void(*)(int connectionID, int playerID))(base + 0xb4c80);
	sendPacket = (int(*)(unsigned int address, unsigned short port))(base + 0xc7ff0);
	bulletSimulation = (void(*)())(base + 0x8b4c0);
	bulletTimeToLive = (void(*)())(base + 0x1ed50);

	economyCarMarket = (void(*)())(base + 0x26e70);
	saveAccountsServer = (void(*)())(base + 0xe260);

	createAccountByJoinTicket = (int(*)(int identifier, unsigned int ticket))(base + 0xdb70);
	serverSendConnectResponse = (void(*)(unsigned int address, unsigned int port, 
										 int unk, const char* message))(base + 0xc8610);

	scenarioArmHuman = (void(*)(int human, int weapon, int magCount))(base + 0x7ae30);
	linkItem = (int(*)(int itemID, int childItemID, int parentHumanID,
                        int slot))(base + 0x460e0);
	itemSetMemo = (int(*)(int itemID, const char* memo))(base + 0x3dbf0);
	itemComputerTransmitLine = (int(*)(int itemID, unsigned int line))(base + 0x3dd70);
	itemComputerIncrementLine = (void(*)(int id))(base + 0x3e0e0);
	itemComputerInput = (int(*)(int itemID, unsigned int character))(base + 0x78000);
	itemCashAddBill = (int(*)(int itemID, int zero, int amount))(base + 0x3c8a0);
	itemCashRemoveBill = (void(*)(int itemID, int amount))(base + 0x3c990);
	itemCashGetBillValue = (int(*)(int itemID))(base + 0x3c840);

	humanApplyDamage = (void(*)(int humanID, int bone, int unk, int damage))(base + 0x2b120);
	vehicleApplyDamage = (void(*)(int vehicleID, int damage))(base + 0x5e850);
	humanCollisionVehicle = (void(*)(int humanID, int vehicleID))(base + 0x68450);
	humanLimbInverseKinematics = (void(*)(int humanID, int trunkBoneID, int branchBoneID,
                                          Vector* destination, RotMatrix* destinationAxis,
                                          Vector* vecA, float a, float rot,
                                          float strength, float* d,
                                          Vector* vecB, Vector* vecC, Vector* vecD,
                                          char flags))(base + 0x718d0);
	grenadeExplosion = (void(*)(int id))(base + 0x43410);
	serverPlayerMessage = (int(*)(int playerID, char* message))(base + 0xb9050);
	playerAI = (void(*)(int id))(base + 0x89a60);
	playerDeathTax = (void(*)(int id))(base + 0x5d30);
	accountDeathTax = (void(*)(int id))(base + 0x5710);
	playerGiveWantedLevel = (void(*)(int playerID, int victimPlayerID,
                                     int basePoints))(base + 0x6bc0);
	createBondRigidBodyToRigidBody = (int(*)(int aBodyID, int bBodyID,
                                              Vector* aLocalPos, Vector* bLocalPos))(base + 0x1ae60);
	createBondRigidBodyRotRigidBody = (int(*)(int aBodyID, int bBodyID))(base + 0x1b0e0);
	createBondRigidBodyToLevel = (int(*)(int bodyID, Vector* localPos,
                                          Vector* globalPos))(base + 0x1ad40);
	addCollisionRigidBodyOnRigidBody = (void(*)(int aBodyID, int bBodyID,
                                            	Vector* aLocalPos,
                                            	Vector* bLocalPos,
                                                Vector* normal, float a,
                                                float b, float c, float d))(base + 0x1b1c0);
	addCollisionRigidBodyOnLevel = (void(*)(int bodyID, Vector* localPos,
                                            Vector* normal, float a, float b,
                                            float c, float d))(base + 0x1b350);

	createBullet = (int(*)(int type, Vector* pos, Vector* vel,
                            int playerID))(base + 0x1e880);
	createPlayer = (int(*)())(base + 0x6d040);
	deletePlayer = (void(*)(int playerID))(base + 0x6d330);
	createHuman = (int(*)(Vector* pos, RotMatrix* rot, int playerID))(base + 0x76b80);
	deleteHuman = (void(*)(int humanID))(base + 0x6ef0);
	createItem = (int(*)(int type, Vector* pos, Vector* vel,
                          RotMatrix* rot))(base + 0x777a0);
	deleteItem = (void(*)(int id))(base + 0x48ce0);
	createRope = (int(*)(Vector* pos, RotMatrix* rot))(base + 0x78b70);
	createVehicle = (int(*)(int type, Vector* pos, Vector* vel,
                             RotMatrix* rot, int color))(base + 0x7cf20);
	deleteVehicle = (void(*)(int id))(base + 0x7150);
	createRigidBody = (int(*)(int type, Vector* pos, RotMatrix* rot,
                        	   Vector* vel, Vector* scale, float mass))(base + 0x76940);

	createEventMessage = (void(*)(int type, char* message, int speakerID,
                                  int distance))(base + 0x58a0);
	createEventUpdatePlayer = (void(*)(int id))(base + 0x5ba0);
	createEventUpdatePlayerFinance = (void(*)(int id))(base + 0x5cc0);
	createEventCreateVehicle = (void(*)(int id))(base + 0x59c0);
	createEventUpdateVehicle = (void(*)(int vehicleID, int updateType,
                                        int partID, Vector* pos,
                                        Vector* normal))(base + 0x5a20);
	createEventSound = (void(*)(int soundType, Vector* pos, float volume,
                                float pitch))(base + 0x5e00);
	createEventExplosion = (void(*)(int type, Vector* pos))(base + 0x64d0);
	createEventBullet = (void(*)(int bulletType, Vector* pos, Vector* vel,
                                 int itemID))(base + 0x5760);
	createEventBulletHit = (void(*)(int unk, int hitType, Vector* pos,
                                    Vector* normal))(base + 0x57f0);

	lineIntersectHuman = (int(*)(int humanID, Vector* posA, Vector* posB,
                                  float padding))(base + 0x3a200);
	lineIntersectLevel = (int(*)(Vector* posA, Vector* posB,
                                  int includeCityObjects))(base + 0x88cf0);
	lineIntersectVehicle = (int(*)(int vehicleID, Vector* posA,
                                    Vector* posB, int includeWheels))(base + 0x6b2a0);
	lineIntersectTriangle = (int(*)(Vector* outPos, Vector* normal,
                                     float* outFraction, Vector* posA,
                                     Vector* posB, Vector* triA,
                                     Vector* triB, Vector* triC))(base + 0x8ef0);

 	// From RosaLink
	createEventUpdateItem = (void (*)(int itemID))(base + 0x5b20); // The parameter here might not be the item ID.
	setBaseDoorState = (void (*)(int teamID, int state))(base + 0x1d330);
	itemWeaponSimulation = (void (*)(int itemID))(base + 0x5d160);
	eliminatorAnnounceDeath = (void (*)(int playerID))(base + 0x67a0);
 	isInsideBuilding = (bool (*)(float clearance, int buildingId, Vector* pos))(base + 0x52c60);
 	createEventOpenTeamDoor = (void (*)(int teamId, int openState))(base + 0x5ec0);
  	createEventUpdateStocks = (void (*)())(base + 0x6270);
  	createEventGlassBreak = (void (*)(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int* param_7, int* param_8))(base + 0x63e0);
}
}