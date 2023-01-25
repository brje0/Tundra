/**
 * @file  engine_structs.hpp
 * @brief Reverse engineered structures used by the engine.
          These are all from RosaServer or RosaLink, except for Vector and RotMatrix, which I've re-defined.
 */
#pragma once

#include <math.h>
#include <functional>
#include <variant>
#include <unordered_map>
#include <string>

// Note:
// In the SR source code, Vectors represent 1x3 matrices and RotMatrices represent 3x3 matrices.
// This means that the correct way to multiply a Vector and RotMatrix is Vector * RotMatrix.
struct Vector;
struct RotMatrix;

struct Action;
struct Bone;
struct BulletType;
struct Collision;
struct InventorySlot;
struct ItemType;
struct MenuButton;
struct Player;
struct Account;
struct Bond;
struct Bullet;
struct EarShot;
struct Connection;
struct Game;
struct Human;
struct Item;
struct Options;
struct WorldOptions;
struct VersusOptions;
struct RoundOptions;
struct LineIntersectResult;
struct StreetLane;
struct Street;
struct StreetIntersection;
struct Team;
struct TrafficCar;
struct Vehicle;
struct VehicleType;
struct ShopCar;
struct Event;
struct Voice;
struct Building;
struct RigidBody;

typedef std::variant<float, int, char, bool, std::string, Vector, RotMatrix> anyVar;

// The array sizes need to be explicitly declared.
// If you use MAX_NUM_OF_X it throws an error on compilation
// because the compiler can only see the current compilation
// unit and doesn't trust that you're referring to a constant
// integral expression.
extern std::unordered_map<std::string, anyVar> humanData[256];
extern std::unordered_map<std::string, anyVar> itemData[1024];
extern std::unordered_map<std::string, anyVar> playerData[256];
extern std::unordered_map<std::string, anyVar> bodyData[8192];
extern std::unordered_map<std::string, anyVar> vehicleData[512];

struct RotMatrix {
  // Default constructor initializes to identity matrix.
  RotMatrix();
  RotMatrix(float x1_in, float y1_in, float z1_in,
	          float x2_in, float y2_in, float z2_in,
	          float x3_in, float y3_in, float z3_in);
  RotMatrix operator*(RotMatrix other);
  void operator*=(RotMatrix other);

  Vector getRight();
  Vector getUp();
  Vector getForward();

  float x1, y1, z1;
  float x2, y2, z2;
  float x3, y3, z3;
};

struct Vector {
  Vector();
  Vector(float x_in, float y_in, float z_in);

  Vector operator-();
  Vector operator+(Vector other);
  void operator+=(Vector other);
  Vector operator-(Vector other);
  void operator-=(Vector other);

  Vector operator*(float scalar);
  void operator*=(float scalar);
  Vector operator/(float scalar);
  void operator/=(float scalar);

  Vector operator*(RotMatrix rot);
  void operator*=(RotMatrix rot);

  float length();
  float lengthSquare();
  void normalize();
  Vector getNormalized();
  float dist(Vector* other);
  float distSquare(Vector* other);

  float x;
  float y;
  float z;
};

struct Action {
  int type;       // 0x0
  int a;          // 0x4
  int b;          // 0x8
  int c;          // 0xc
  int d;          // 0x10
  char text[64];  // 0x14
};

struct Bone {
  int bodyID;             // 0x0
  Vector pos;             // 0x4
  Vector pos2;            // 0x10
  Vector vel;             // 0x1c
  Vector vel2;            // 0x28
  RotMatrix rot;          // 0x34
  char _field_0x58[44];   // 0x58
  float _field_0x84;      // 0x84
  char _field_0x88[176];  // 0x88
};

struct BulletType {
  float mass;           // 0x0
  char _field_0x4[20];  // 0x4
};

struct Collision {
  char _field_0x0[36];  // 0x0
};

struct InventorySlot {
  int count;           // 0x0
  int primaryItemID;   // 0x4
	int secondaryItemID; // 0x8
  char field_0xc[28];  // 0xc

  Item* getPrimaryItem();
  Item* getSecondaryItem();
};

struct ItemType {
  char field_0x0[4];           // 0x0
  int price;                   // 0x4
  float mass;                  // 0x8
  char field_0xc[4];           // 0xc
  int isGun;                   // 0x10
  int messedUpAiming;          // 0x14
  int fireRate;                // 0x18
  int bulletType;              // 0x1c
  char field_0x20[4];          // 0x20
  int magazineAmmo;            // 0x24
  float bulletVelocity;        // 0x28
  float bulletSPread;          // 0x2c
  char name[64];               // 0x30
  char field_0x70[12];         // 0x70
  int numHands;                // 0x7c
  Vector rightHandPos;         // 0x80
  Vector leftHandPos;          // 0x8c
  char field_0x98[24];         // 0x98
  float primaryGripStiffness;  // 0xb0
  char field_0xb4[8];          // 0xb4
  float primaryGripRotation;   // 0xbc
  float secondGripStiffness;   // 0xc0
  char field_0xc4[8];          // 0xc4
  float secondaryGripRotaion;  // 0xcc
  char field_0xd0[52];         // 0xd0
  Vector boundsCenter;         // 0x104
  char field_0x110[12];        // 0x110
  int canMountTo[45];          // 0x11c
  char field_0x1d0[4548];      // 0x1d0
  Vector gunHoldingPos;        // 0x1394
  char field_0x13a0[48];       // 0x13a0

  int getIndex();

  bool getCanMountTo(ItemType* parent);
  void setCanMountTo(ItemType* parent, bool canMount);
};

struct MenuButton {
  int menuID;     // 0x0
  char text[64];  // 0x4
  int unk;        // 0x44
};

struct Player {
  int isActive;                // 0x0
  char name[32];               // 0x4
  char _field_0x24[8];         // 0x24
  unsigned int subrosaID;      // 0x2c
  unsigned int phoneNumber;    // 0x30
  int isAdmin;                 // 0x34
  int adminAttempts;           // 0x38
  int accountID;               // 0x3c
  int cantSpeak;               // 0x40
  char _field_0x44[4];         // 0x44
  int isReady;                 // 0x48
  int money;                   // 0x4c
  char _field_0x50[8];         // 0x50
  int corporateRating;         // 0x58
  int criminalRating;          // 0x5c
  int godmodeEnabled;          // 0x60
  char _field_0x64[32];        // 0x64
  int team;                    // 0x84
  int teamSwitchTimer;         // 0x88
  int stocksOwned;             // 0x8c
  int isManager;               // 0x90
  char _field_0x94[4];         // 0x94
  int spawnTime;               // 0x98
  int humanID;                 // 0x9c
  char _field_0xa0[128];       // 0xa0
  unsigned int inputFlags;     // 0x120
  char _field_0x124[16];       // 0x124
  int zoomLevel;               // 0x134
  char _field_0x138[8];        // 0x138
  float _field_0x140;          // 0x140
  char _field_0x144[32];       // 0x144
  int menuTab;                 // 0x164
  char _field_0x168[76];       // 0x168
  int numActions;              // 0x1b4
  int lastNumActions;          // 0x1b8
  char _field_0x1bc[12];       // 0x1bc
  Action actions[64];          // 0x1c8
  char _field_0x16c8[1100];    // 0x16c8
  int numMenuButtons;          // 0x1b14
  MenuButton menuButtons[32];  // 0x1b18
  char _field_0x2418[2304];    // 0x2418
  int isBot;                   // 0x2d18
  int isZombie;                // 0x2d1c
  char _field_0x2d20[24];      // 0x2d20
  int botHasDestination;       // 0x2d38
  Vector botDestination;       // 0x2d3c
  char _field_0x2d48[2456];    // 0x2d48
  int missionTime;             // 0x36e0
  char _field_0x36e4[200];     // 0x36e4
  int gender;                  // 0x37ac
  int skinColor;               // 0x37b0
  int hairColor;               // 0x37b4
  int hair;                    // 0x37b8
  int eyeColor;                // 0x37bc
  int model;                   // 0x37c0
  int suitColor;               // 0x37c4
  int tieColor;                // 0x37c8
  char _field_0x37cc[4];       // 0x37cc
  int head;                    // 0x37d0
  int necklace;                // 0x37d4
  int _field_0x37d8[23];       // 0x37d8

  int getIndex();
  void remove();

  void kick();

  Event* update();
  Event* updateFinance();
  Event* sendMessage(const std::string& message);
  void sendMessageWrap(std::string message);

  Human* getHuman();
  void setHuman(Human* human);
  Account* getAccount();
  void setAccount(Account* account);
  Voice* getVoice();
  Connection* getConnection();
  MenuButton* getMenuButton(unsigned int index);

  template<typename T>
  T getData(const std::string& key)
  {
    return std::get<T>(playerData[getIndex()][key]);
  }
  template<typename T>
  void setData(const std::string& key, T value)
  {
    playerData[getIndex()][key] = value;
  }
};

struct Account {
  int subRosaID;        // 0x0
  int phoneNumber;      // 0x4
  long long steamID;    // 0x8
  char name[32];        // 0x10
  char _field_0x30[4];  // 0x30
  int money;            // 0x34
  int corporateRating;  // 0x38
  int criminalRating;   // 0x3c
  int spawnTimer;       // 0x40
  int playTime;         // 0x44
  char _field_0x48[4];  // 0x48
  int _unkRandom1;      // 0x4c
  int _unkRandom2;      // 0x50
  int _unkRandom3;      // 0x54
  char _field_0x58[8];  // 0x58
  int banTime;          // 0x60
  int isAdmin;          // 0x64
  char _field_0x68[8];  // 0x68

  int getIndex();

  void ban(int minutes, const std::string& reason, const std::string& adminName);
  void addBan(int minutes, const std::string& reason, const std::string& adminName);
  void punish(int count, const std::string& reason, const std::string& adminName);
  void warn(const std::string& warning);
};

struct Bond {
  int active;             // 0x0
  int type;               // 0x4
  char _field_0x8[4];     // 0x8
  int despawnTime;        // 0xc
  char _field_0x10[136];  // 0x10
  int bodyID;             // 0x98
  int otherBodyID;        // 0x9c
  char _field_0xa0[84];   // 0xa0

  int getIndex();

  RigidBody* getBody();
  RigidBody* getOtherBody();

  template<typename T>
  T getData(const std::string& key)
  {
    return std::get<T>(bodyData[getIndex()][key]);
  }
  template<typename T>
  void setData(const std::string& key, T value)
  {
    bodyData[getIndex()][key] = value;
  }
};

struct Bullet {
  unsigned int type;     // 0x0
  int time;              // 0x4
  int playerID;          // 0x8
  char field_0xc[8];     // 0xc
  RotMatrix field_0x14;  // 0x14
  char field_0x38[36];   // 0x38

  // No getIndex() because bullets can move around in memory every tick.
  Player* getPlayer();
};

struct EarShot {
  int active;              // 0x0
  int playerId;            // 0x4
  int humanId;             // 0x8
  int recivingItemId;      // 0xc
  int transmittingItemId;  // 0x10
  char field_0x14[12];     // 0x14
  float distance;          // 0x20
  float volume;            // 0x24
};

struct Connection {
  unsigned int address;       // 0x0
  unsigned int port;          // 0x4
  char _field_0x8[12];        // 0x8
  int adminVisible;           // 0x14
  int playerID;               // 0x18
  char _field_0x1c[4];        // 0x1c
  int bandwidtdh;             // 0x20
  int timeout;                // 0x24
  char _field_0x28[36];       // 0x28
  int numRecievedEvents;      // 0x4c
  char _field_0x50[12];       // 0x50
  EarShot earShots[8];         // 0x5c
  int spectatingHumanId;      // 0x19c
  char _field_0x1a0[188480];  // 0x1a0

  EarShot* getEarShot(int index);
  void disconnect();
  std::string getAddress();
};

struct Game {
  int dayOfWeek;             // 0x0
  char _field_0x4[4];        // 0x4
  int gameState;             // 0x8
  char _field_0xc[4];        // 0xc
  int gameTimer;             // 0x10
  char _field_0x14[8];       // 0x14
  int roundTimer;            // 0x1c
  char _field_0x20[4];       // 0x20
  int teamDamage;            // 0x24
  char _field_0x28[72];      // 0x28
  int tick;                  // 0x70
  char _field_0x74[520075];  // 0x74
};

struct Human {
  int isActive;                             // 0x0
  int physicsSim;                         // 0x4
  int playerID;                           // 0x8
  int accountID;                          // 0xc
  char _field_0x10[12];                   // 0x10
  int stamina;                            // 0x1c
  int maxStamina;                         // 0x20
  char _field_0x24[4];                    // 0x24
  int vehicleID;                          // 0x28
  int vehicleSeat;                        // 0x2c
  int lastVehicleId;                      // 0x30
  int lastVehicleCooldown;                // 0x34
  unsigned int despawnTime;               // 0x38
  int oldHealth;                          // 0x3c
  int isImmortal;                         // 0x40
  char _field_0x44[12];                   // 0x44
  unsigned int spawnProtection;           // 0x50
  int isOnGround;                         // 0x54
  int movementState;                      // 0x58
  /*
	0=normal
	1=jumping/falling
	2=sliding
	5=getting up?
	*/
  char _field_0x5c[4];                    // 0x5c
  int zoomLevel;                          // 0x60
  char _field_0x64[20];                   // 0x64
  int strengthDamage;                     // 0x78
  int isStanding;                         // 0x7c
  Vector pos;                             // 0x80
  Vector pos2;                            // 0x8c
  float viewYaw;                          // 0x98
  float viewPitch;                        // 0x9c
  char _field_0xa0[140];                  // 0xa0
  float strafeInput;                      // 0x12c
  char _field_0x130[4];                   // 0x130
  float walkInput;                        // 0x134
  char _field_0x138[220];                 // 0x138
  unsigned int inputFlags;                // 0x214
  unsigned int lastInputFlags;            // 0x218
  char _field_0x21c[4];                   // 0x21c
  Bone bones[16];                         // 0x220
  char _field_0x15a0;                     // 0x15a0
  char _field_0x15a1[7767];               // 0x15a1
  int isGrabbingRight;                    // 0x33f8
  int grabbingRightHumanID;               // 0x33fc
  char _field_0x3400[4];                  // 0x3400
  int grabbingRightBone;                  // 0x3404
  char _field_0x3408[40];                 // 0x3408
  int isGrabbingLeft;                     // 0x3430
  int grabbingLeftHumanID;                // 0x3434
  char _field_0x3438[4];                  // 0x3438
  int grabbingLeftBone;                   // 0x343c
  char _field_0x3440[13968];              // 0x3440
  InventorySlot inventorySlots[6];        // 0x6ad0
  char _field_0x6bc0[400];                // 0x6bc0
  int consciousness;                      // 0x6d50
  int newHealth;                          // 0x6d54
  int isBleeding;                         // 0x6d58
  int chestHp;                            // 0x6d5c
  char _field_0x6d60[4];                  // 0x6d60
  int headHp;                             // 0x6d64
  char _field_0x6d68[4];                  // 0x6d68
  int leftArmHp;                          // 0x6d6c
  char _field_0x6d70[4];                  // 0x6d70
  int rightArmHp;                         // 0x6d74
  char _field_0x6d78[4];                  // 0x6d78
  int leftLegHp;                          // 0x6d7c
  char _field_0x6d80[4];                  // 0x6d80
  int rightLegHp;                         // 0x6d84
  char _field_0x6d88[84];                 // 0x6d88
  int progressBar;                        // 0x6ddc
  int inventoryAnimationFlags;            // 0x6de0
  float inventoryAnimationProgress;       // 0x6de4
  int inventoryAnimationDuration;         // 0x6de8
  int inventoryAnimationHand;             // 0x6dec
  int inventoryAnimationSlot;             // 0x6df0
  int inventoryAnimationCounterFinished;  // 0x6df4
  int inventoryAnimationCounter;          // 0x6df8
  char _field_0x6dfc[388];                // 0x6dfc
  int gender;                             // 0x6f80
  int head;                               // 0x6f84
  int skinColor;                          // 0x6f88
  int hairColor;                          // 0x6f8c
  int hair;                               // 0x6f90
  int eyeColor;                           // 0x6f94
  int model;                              // 0x6f98
  int suitColor;                          // 0x6f9c
  int tieColor;                           // 0x6fa0
  char _field_0x6fa4[4];                  // 0x6fa4
  int necklace;                           // 0x6fa8
  int lastUpdatedWantedGroup;             // 0x6fac
  char _field_0x6fb0[72];                 // 0x6fb0

  int getIndex();
  void remove();

  void arm(int weaponType, int magCount);
  void setVelocity(Vector vel);
  void addVelocity(Vector vel);
  Player* getPlayer();
  void setPlayer(Player* player);
  RigidBody* getRigidBody(int index);
  Vehicle* getVehicle();
  void setVehicle(Vehicle* vehicle);
  void speak(const std::string& message, int volumeLevel);
  bool mountItem(Item* childItem, unsigned int slot);
  void applyDamage(int bone, int item);

  template<typename T>
  T getData(const std::string& key)
  {
    return std::get<T>(humanData[getIndex()][key]);
  }
  template<typename T>
  void setData(const std::string& key, T value)
  {
    humanData[getIndex()][key] = value;
  }
};

struct Item {
  int isActive;                      // 0x0
  int physicsSim;                    // 0x4
  int physicsSettled;                // 0x8
  int physicsSettledTimer;           // 0xc
  int isStatic;                      // 0x10
  int type;                          // 0x14
  float field_0x18;                  // 0x18
  int despawnTime;                   // 0x1c
  int grenadePrimerID;               // 0x20
  int parentHumanID;                 // 0x24
  int parentItemID;                  // 0x28
  int parentSlot;                    // 0x2c
  int inPocket;                      // 0x30
  int childCount;                    // 0x34
  int childID[8];                    // 0x38
  int bodyID;                        // 0x58
  Vector pos;                        // 0x5c
  Vector pos2;                       // 0x68
  Vector vel;                        // 0x74
  Vector vel2;                       // 0x80
  Vector vel3;                       // 0x8c
  Vector vel4;                       // 0x98
  char field_0xa4[152];              // 0xa4
  int coolDown;                      // 0x13c
  char field_0x140[4];               // 0x140
  int bullets;                       // 0x144
  char field_0x148[4];               // 0x148
  int triggerHeldTicks;              // 0x14c
  int trigger;                       // 0x150
  char field_0x154[8];               // 0x154
  int connectedPhoneNumber;          // 0x15c
  int phoneNumber;                   // 0x160
  char field_0x164[4];               // 0x164
  int displayPhoneNumber;            // 0x168
  int enteredPhoneNumber;            // 0x16c
  char field_0x170[8];               // 0x170
  int keyVehicleID;                  // 0x178
  char field_0x17c[252];             // 0x17c
  int isSecondaryPhone;              // 0x278
  char field_0x27c[4];               // 0x27c
  int vehicleID;                     // 0x280
  char field_0x284[124];             // 0x284
  Vector payPhonePos;                // 0x300
  char field_0x30c[44];              // 0x30c
  int fileID;                        // 0x338
  char field_0x33c[44];              // 0x33c
  unsigned int computerCurrentLine;  // 0x368
  unsigned int computerTopLine;      // 0x36c
  int computerCursor;                // 0x370
  char computerLines[32][64];        // 0x374
  char computerLineColors[32][64];   // 0xb74
  char field_0x1374[740];            // 0x1374
  int computerTeam;                  // 0x1658
  char field_0x165c[1316];           // 0x165c

  int getIndex();
  void remove();
  void update();

  bool mount(Item* childItem, int slot);
  bool unmount();
  void speak(const std::string& message, int volumeLevel);
  void explode();
  // Max 1023 characters
  void setMemo(const std::string& message);
  // Computers only
  void computerTransmitLine(unsigned int line);
  void computerIncrementLine();
  void computerSetLine(unsigned int line, const std::string& newLine);
  void computerSetLineColors(unsigned int line, std::string_view colors);
  void computerSetColor(unsigned int line, unsigned int column, unsigned char color);
  // Cash only
  void cashAddBill(int position, int value);
  void cashRemoveBill(int position);
  int cashGetBillValue();

  RigidBody* getRigidBody();

  template<typename T>
  T getData(const std::string& key)
  {
    return std::get<T>(itemData[getIndex()][key]);
  }
  template<typename T>
  void setData(const std::string& key, T value)
  {
    itemData[getIndex()][key] = value;
  }

  void pickUpHook(std::function<bool(int &itemID, int &childItemID, int &parentHumanID, int &slot)> funcToAdd);
  void pickUpHook(std::function<bool(int &itemID, int &childItemID, int &parentHumanID, int &slot)> funcToAdd, char priority);
  void pickUpHookOnce(std::function<bool(int &itemID, int &childItemID, int &parentHumanID, int &slot)> funcToAdd);
  void pickUpHookOnce(std::function<bool(int &itemID, int &childItemID, int &parentHumanID, int &slot)> funcToAdd, char priority);
  bool hasPickUpHook();
  bool removePickUpHook();
};

struct Options {
  int port;                     // 0x0
  int servermaxbytespersecond;  // 0x4
  char field_0x8[4];            // 0x8
  char name[30];                // 0xc
  char field_0x2a[482];         // 0x2a
  char servername[50];          // 0x20c
  char field_0x23e[462];        // 0x23e
  char adminpassword[50];       // 0x40c
  char field_0x43e[462];        // 0x43e
  char serverpassword[50];      // 0x60c
  char field_0x63e[478];        // 0x63e
  int soundvolume;              // 0x81c
  int musicvolume;              // 0x820
  char field_0x824[44];         // 0x824
  int floatDepthBuffer;         // 0x850
  char field_0x854[4];          // 0x854
  int invertmouse;              // 0x858
  char field_0x85c[12];         // 0x85c
  int maxnumofplayers;          // 0x868
  int gametype;                 // 0x86c
  int roundtime;                // 0x870
  int setcpuaffinity;           // 0x874
  int occlusion;                // 0x878
  int voicemin;                 // 0x87c
  int voicechat;                // 0x880
  int voiceholdtotalk;          // 0x884
  int voicekey;                 // 0x888
  int voicemb;                  // 0x88c
  int help;                     // 0x890
  char field_0x894[4];          // 0x894
  int verticalSync;             // 0x898
  float voicecboost;            // 0x89c
  char field_0x8a0[8];          // 0x8a0
  int playerGender;             // 0x8a8
  int playerHead;               // 0x8ac
  int playerSkinColor;          // 0x8b0
  int playerHairColor;          // 0x8b4
  int playerHairStyle;          // 0x8b8
  int playerColor;              // 0x8bc
  int manualHandss;             // 0x8c0
  int frameSmoothing;           // 0x8c4
};

struct WorldOptions {
  int traffic;              // 0x0
  int crimecivciv;          // 0x4
  int crimecivteam;         // 0x8
  int crimeteamciv;         // 0xc
  int crimeteamteam;        // 0x10
  int crimeteamteaminbase;  // 0x14
  int crimevscriminal;      // 0x18
  int crimenobuy;           // 0x1c
  int crimenorespawn;       // 0x20
  int crimekick;            // 0x24
  int startcash;            // 0x28
  int mincash;              // 0x2c
  int showJoinExit;         // 0x30
  int respawnteam;          // 0x34
};

struct VersusOptions {
  int allowrespawn;      // 0x0
  int startcash;         // 0x4
  int roundtime;         // 0x8
  int movedelay;         // 0xc
  int bonusratio;        // 0x10
  int teamdamage;        // 0x14
  int nextMap;           // 0x18
  char map01[30];        // 0x1c
  char field_0x3a[34];   // 0x3a
  char map02[30];        // 0x5c
  char field_0x7a[34];   // 0x7a
  char map03[30];        // 0x9c
  char field_0xba[34];   // 0xba
  char map04[30];        // 0xdc
  char field_0xfa[34];   // 0xfa
  char map05[30];        // 0x11c
  char field_0x13a[34];  // 0x13a
  char map06[30];        // 0x15c
  char field_0x17a[34];  // 0x17a
  char map07[30];        // 0x19c
  char field_0x1ba[34];  // 0x1ba
  char map08[30];        // 0x1dc
};

struct RoundOptions {
  int roundtime;   // 0x0
  int startcash;   // 0x4
  int weekly;      // 0x8
  int bonusratio;  // 0xc
  int teamdamage;  // 0x10
};

struct LineIntersectResult {
  Vector pos;           // 0x0
  Vector normal;        // 0xc
  float fraction;       // 0x18
  char field_0x1c[20];  // 0x1c
  int vehicleFace;      // 0x30
  int humanBone;        // 0x34
  char field_0x38[32];  // 0x38
  int blockX;           // 0x58
  int blockY;           // 0x5c
  int blockZ;           // 0x60
  char field_0x64[8];   // 0x64
  int matMaybe;         // 0x6c
  char field_0x70[20];  // 0x70
};

struct MasterServer {
  typedef unsigned int IP;      // 0x0
  typedef unsigned short port;  // 0x4
  char field_0x6[514];          // 0x6
};

struct RigidBody {
  int active;            // 0x0
  int type;              // 0x4
  int settled;           // 0x8
  char _field_0xc[8];    // 0xc
  float mass;            // 0x14
  Vector pos;            // 0x18
  Vector vel;            // 0x24
  Vector startVel;       // 0x30
  RotMatrix rot;         // 0x3c
  RotMatrix rotVel;      // 0x60
  Vector scale;          // 0x84
  char _field_0x90[44];  // 0x90

  int getIndex();

  Bond* bondTo(RigidBody* other, Vector* thisLocalPos, Vector* otherLocalPos);
  Bond* bondRotTo(RigidBody* other);
  Bond* bondToLevel(Vector* localPos, Vector* globalPos);
  void collideLevel(Vector* localPos, Vector* normal, float a, float b, float c, float d);

  template <typename T>
  T getData(const std::string& key);
  template <typename T>
  void setData(const std::string& key, T value);
};

struct StreetLane {
  int direction;  // 0x0
  Vector posA;    // 0x4
  Vector posB;    // 0x10
};

struct Street {
  char name[32];
  int unk0;               // 20
  int intersectionA;      // 24
  int intersectionB;      // 28
  int unk1[3];            // 2c
  int numLanes;           // 38
  StreetLane lanes[16];   // 3c
  float unk2[6];          // 1fc
  Vector trafficCuboidA;  // 214
  Vector trafficCuboidB;  // 220
  int numTraffic;         // 22c
  char unk3[0x630 - 0x22c - 4];

  int getIndex();
  StreetIntersection* getIntersectionA();
  StreetIntersection* getIntersectionB();
  StreetLane* getLane(unsigned int index);
};

struct StreetIntersection {
  char field_0x0[12];   // 0x0
  Vector pos;           // 0xc
  int streetEast;       // 0x18
  int streetSouth;      // 0x1c
  int streetWest;       // 0x20
  int streetNorth;      // 0x24
  char field_0x28[28];  // 0x28
  int lightState;       // 0x44
  int lightsTimer;      // 0x48
  int lightsTimerMax;   // 0x4c
  int lightEast;        // 0x50
  int lightSouth;       // 0x54
  int lightWest;        // 0x58
  int lightNorth;       // 0x5c
  char field_0x60[40];  // 0x60

  int getIndex();
  Street* getStreetEast();
  Street* getStreetSouth();
  Street* getStreetWest();
  Street* getStreetNorth();
};

struct Team {
  char field_0x0[23492];  // 0x0
};

struct TrafficCar {
  int type;               // 0x0
  int humanID;            // 0x4
  int vehicleID;          // 0x8
  char field_0xc[4];      // 0xc
  Vector pos;             // 0x10
  Vector vel;             // 0x1c
  float yaw;              // 0x28
  RotMatrix rot;          // 0x2c
  char field_0x50[1416];  // 0x50
  int color;              // 0x5d8
  char field_0x5dc[32];   // 0x5dc

  int getIndex();

  VehicleType* getType();
  void setType(VehicleType* vehicleType);
  Human* getHuman();
  void setHuman(Human* human);
  Vehicle* getVehicle();
  void setVehicle(Vehicle* vehicle);
};

struct Vehicle {
  int isActive;
  unsigned int type;      // 04
  int controllableState;  // 08
  // default 100
  int health;              // 0c
  int unk1;                // 10
  int lastDriverPlayerID;  // 14
  unsigned int color;      // 18
  // -1 = won't despawn
  short despawnTime;   // 1c
  short spawnedState;  // 1e
  int isLocked;        // 20
  int unk3;            // 24
  int bodyID;          // 28
  Vector pos;          // 2c
  Vector pos2;         // 38
  RotMatrix rot;       // 44
  int unk4;            // 68
  Vector vel;          // 6c
  char unk5[0x27fc - 0x6c - 12];
  int windowStates[8];  // 27fc
  char unk6[0x3600 - 0x27fc - (4 * 8)];
  float gearX;         // 3600
  float steerControl;  // 3604
  float gearY;         // 3608
  float gasControl;    // 360c
  char unk7[0x3648 - 0x360c - 4];
  int trafficCarID;  // 3648
  char unk8[0x3930 - 0x3648 - 4];
  int engineRPM;  // 3930
  char unk9[0x4fa8 - 0x3930 - 4];
  int bladeBodyID;  // 4fa8
  char unk10[0x50dc - 0x4fa8 - 4];
  int numSeats;  // 50dc
  char unk11[0x5168 - 0x50dc - 4];

  int getIndex();

  VehicleType* getType();
  Event* updateType();
  Event* updateDestruction(int updateType, int partID, Vector* pos, Vector* normal);
  void remove();
  Player* getLastDriver();
  RigidBody* getRigidBody();
  TrafficCar* getTrafficCar();
  void setTrafficCar(TrafficCar* trafficCar);
  bool getIsWindowBroken(unsigned int index);
  void setIsWindowBroken(unsigned int index, bool isBroken);

  template<typename T>
  T getData(const std::string& key)
  {
    return std::get<T>(vehicleData[getIndex()][key]);
  }
  template<typename T>
  void setData(const std::string& key, T value)
  {
    vehicleData[getIndex()][key] = value;
  }
};

struct VehicleType {
  int usesExternalModel;     // 0x0
  char field_0x4[4];         // 0x4
  int controllableState;     // 0x8
  char field_0xc[8];         // 0xc
  char name[32];             // 0x14
  int price;                 // 0x34
  float mass;                // 0x38
  char field_0x3c[96308];    // 0x3c
  int field_0x17870;         // 0x17870
  char field_0x17874[2716];  // 0x17874
  int numOfSeats;            // 0x18310
  char field_0x18314[684];   // 0x18314

  int getIndex();
};

struct ShopCar {
  int type;
  int price;
  int color;

  VehicleType* getType();
  void setType(VehicleType* vehicleType);
};

// From RosaServer
// 128 bytes (80)
struct Event {
  int type;          // 00
  int tickCreated;   // 04
  Vector vectorA;    // 08
  Vector vectorB;    // 14
  int a;             // 20
  int b;             // 24
  int c;             // 28
  int d;             // 2c
  float floatA;      // 30
  float floatB;      // 34
  int unk0;          // 38
  int unk1;          // 3c
  char message[64];  // 40
};

// From RosaServer
// 131604 bytes (20214)
struct Voice {
  int isSilenced;
  int unk0;                        // 04
  int volumeLevel;                 // 08
  int currentFrame;                // 0c
  int unk1;                        // 10
  int frameVolumeLevels[64];       // 14
  int frameSizes[64];              // 114
  unsigned char frames[64][2048];  // 214
};

// From RosaServer
// 56076 bytes (DB0C)
struct Building {
  int type;                // 00
  int unk0[3];             // 04
  Vector pos;              // 10
  RotMatrix spawnRot;      // 1c
  Vector interiorCuboidA;  // 40
  Vector interiorCuboidB;  // 4C
  char unk1[0xC9F4 - 0x4c - 12];
  int numShopCars;       // C9F4
  ShopCar shopCars[16];  // C9F8
  int shopCarSales;      // CAB8
  char unk2[0xDB0C - 0xCAB8 - 4];

  int getIndex();

  ShopCar* getShopCar(int index);
};
