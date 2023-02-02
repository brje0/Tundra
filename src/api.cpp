#include <stdexcept>
#include <string>
#include <math.h>
#include <functional>

#include "../inc/hook.hpp"
#include "../inc/hooks.hpp"
#include "../inc/engine.hpp"
#include "../inc/util.hpp"
#include "../inc/engine_structs.hpp"

std::unordered_map<std::string, anyVar> humanData[256];
std::unordered_map<std::string, anyVar> itemData[1024];
std::unordered_map<std::string, anyVar> playerData[256];
std::unordered_map<std::string, anyVar> bodyData[8192];
std::unordered_map<std::string, anyVar> vehicleData[512];

// In minutes
const unsigned char START_BAN_MINS = 30;
// How much the ban is multiplied by each time the account is punished.
const unsigned char BAN_MULT = 4;

// Vector

Vector::Vector() { x = 0; y = 0; z = 0; }

Vector::Vector(float x_in, float y_in, float z_in)
{
    x = x_in; y = y_in; z = z_in;
}

Vector Vector::operator-() const { return Vector{-x, -y, -z}; }

Vector Vector::operator+(const Vector& other) const { return Vector{x + other.x, y + other.y, z + other.z}; }

void Vector::operator+=(const Vector& other) { x += other.x; y += other.y; z += other.z; }

Vector Vector::operator-(const Vector& other) const { return Vector{x - other.x, y - other.y, z - other.z}; }

void Vector::operator-=(const Vector& other) { x -= other.x; y -= other.y; z -= other.z; }

Vector Vector::operator*(float scalar) const { return Vector{x * scalar, y * scalar, z * scalar}; }

void Vector::operator*=(float scalar) { x *= scalar; y *= scalar; z *= scalar; }

Vector Vector::operator/(float scalar) const { return Vector{x / scalar, y / scalar, z / scalar}; }

void Vector::operator/=(float scalar) { x /= scalar; y /= scalar; z /= scalar; }

Vector Vector::operator*(const RotMatrix& rot) const
{
    return Vector{x * rot.x1 + y * rot.x2 + z * rot.x3,
                  x * rot.y1 + y * rot.y2 + z * rot.y3,
                  x * rot.z1 + y * rot.z2 + z * rot.z3};
}

void Vector::operator*=(const RotMatrix& rot)
{
    x = x * rot.x1 + y * rot.x2 + z * rot.x3;
    y = x * rot.y1 + y * rot.y2 + z * rot.y3;
    z = x * rot.z1 + y * rot.z2 + z * rot.z3;
}

float Vector::length() const { return sqrtf(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

float Vector::lengthSquare() const { return pow(x, 2) + pow(y, 2) + pow(z, 2); }

void Vector::normalize()
{
    float len = length();
    if (len == 0) return;
    float invLen = 1 / len;
    x *= invLen;
    y *= invLen;
    z *= invLen;
}

Vector Vector::getNormalized() const
{
    float len = length();
    if (len == 0) return Vector{};
    float invLen = 1 / len;
    return Vector{x * invLen, y * invLen, z * invLen};
}

float Vector::dist(const Vector& other) const
{
    return sqrtf(pow((x - other.x), 2) + pow((y - other.y), 2) + pow((z - other.z), 2));
}

float Vector::distSquare(const Vector& other) const
{
    return pow((x - other.x), 2) + pow((y - other.y), 2) + pow((z - other.z), 2);
}

float Vector::dotProduct(const Vector& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector Vector::crossProduct(const Vector& other) const
{
    return Vector{y * other.z - z * other.y,
                  z * other.x - x * other.z,
                  x * other.y - y * other.x};
}

bool Vector::isOrthogonal(const Vector& other) const
{
    return dotProduct(other) == 0;
}

// RotMatrix

// Default constructor initializes to identity matrix.
RotMatrix::RotMatrix()
{
    x1 = 1; y1 = 0; z1 = 0;
    x2 = 0; y2 = 1; z2 = 0;
    x3 = 0; y3 = 0; z3 = 1;
}

RotMatrix::RotMatrix(float x1_in, float y1_in, float z1_in,
                     float x2_in, float y2_in, float z2_in,
                     float x3_in, float y3_in, float z3_in)
{
    x1 = x1_in; y1 = y1_in; z1 = z1_in;
    x2 = x2_in; y2 = y2_in; z2 = z2_in;
    x3 = x3_in; y3 = y3_in; z3 = z3_in;
}

RotMatrix RotMatrix::operator*(RotMatrix other) const
{
    return RotMatrix{x1 * other.x1 + y1 * other.x2 + z1 * other.x3, x1 * other.y1 + y1 * other.y2 + z1 * other.y3, x1 * other.z1 + y1 * other.z2 + z1 * other.z3,
                     x2 * other.x1 + y2 * other.x2 + z2 * other.x3, x2 * other.y1 + y2 * other.y2 + z2 * other.y3, x2 * other.z1 + y2 * other.z2 + z2 * other.z3,
                     x3 * other.x1 + y3 * other.x2 + z3 * other.x3, x3 * other.y1 + y3 * other.y2 + z3 * other.y3, x3 * other.z1 + y3 * other.z2 + z3 * other.z3};
}

void RotMatrix::operator*=(RotMatrix other)
{
    x1 = x1 * other.x1 + y1 * other.x2 + z1 * other.x3; y1 = x1 * other.y1 + y1 * other.y2 + z1 * other.y3; z1 = x1 * other.z1 + y1 * other.z2 + z1 * other.z3;
    x2 = x2 * other.x1 + y2 * other.x2 + z2 * other.x3; y2 = x2 * other.y1 + y2 * other.y2 + z2 * other.y3; z2 = x2 * other.z1 + y2 * other.z2 + z2 * other.z3;
    x3 = x3 * other.x1 + y3 * other.x2 + z3 * other.x3; y3 = x3 * other.y1 + y3 * other.y2 + z3 * other.y3; z3 = x3 * other.z1 + y3 * other.z2 + z3 * other.z3;
}

Vector RotMatrix::getRight() const   { return  Vector{x1, y1, z1}; }
Vector RotMatrix::getUp() const      { return  Vector{x2, y2, z2}; }
Vector RotMatrix::getForward() const { return -Vector{x3, y3, z3}; }

// Player

int Player::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::players) / sizeof(*this);
}

void Player::remove()
{
    Engine::deletePlayer(getIndex());
}

void Player::kick()
{
    Connection* con = getConnection();
    if (con == nullptr) return;
    con->timeout = 50 * SERVER_TPS;
}

Event* Player::update()
{
    Engine::createEventUpdatePlayer(getIndex());
    return &Engine::events[*Engine::numEvents - 1];
}

Event* Player::updateFinance()
{
    Engine::createEventUpdatePlayerFinance(getIndex());
    return &Engine::events[*Engine::numEvents - 1];
}

Event* Player::sendMessage(const std::string& message)
{
    char* nonConstMessage = const_cast<char*>(message.c_str());
    Engine::createEventMessage(MESSAGE_PLAYER, nonConstMessage, getIndex(), 0);
    return &Engine::events[*Engine::numEvents - 1];
}

void Player::sendMessageWrap(std::string message)
{
    std::vector<std::string> lines;
    while (message.length() > 63)
    {
        lines.push_back(message.substr(0, 63));
        message.erase(0, 63);
    }
    lines.push_back(message);
    for (std::string line : lines)
        sendMessage(line);
}

Human* Player::getHuman()
{
    return humanID == -1 ? nullptr : &Engine::humans[humanID];
}

void Player::setHuman(Human* human)
{
    humanID = human == nullptr ? -1 : human->getIndex();
}

Account* Player::getAccount()
{
    return accountID == -1 ? nullptr : &Engine::accounts[accountID];
}

void Player::setAccount(Account* account)
{
	if (account == nullptr)
		throw std::invalid_argument("Cannot set account to nullptr");
	else
		accountID = account->getIndex();
}

Voice* Player::getVoice()
{
    return &Engine::voices[getIndex()];
}

Connection* Player::getConnection()
{
    for (int i = 0; i < *Engine::numConnections; i++)
    {
        if (&Engine::players[Engine::connections[i].playerID] == this)
            return &Engine::connections[i];
    }
    return nullptr;
}

MenuButton* Player::getMenuButton(unsigned int index)
{
	if (index > 31) throw std::runtime_error("Error: Player::getMenuButton index out of range.");
	return &menuButtons[index];
}

// Human

int Human::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::humans) / sizeof(*this);
}

void Human::remove()
{
    Engine::deleteHuman(getIndex());
}

void Human::arm(int weaponType, int magCount)
{
    Engine::scenarioArmHuman(getIndex(), weaponType, magCount);
}

void Human::setVelocity(const Vector& vel)
{
    for (int i = 0; i < 16; i++)
        Engine::bodies[bones[i].bodyID].vel = vel;
}

void Human::addVelocity(const Vector& vel)
{
    for (int i = 0; i < 16; i++)
        Engine::bodies[bones[i].bodyID].vel += vel;
}

void Human::teleport(const Vector& in_pos)
{
    Bone* bone;
    RigidBody* body;
    for (int i = 0; i < 16; i++)
    {
        bone = &bones[i];
        bone->pos = in_pos;
        bone->pos2 = in_pos;

        body = &Engine::bodies[bone->bodyID];
        body->pos = in_pos;
    }

    for (int i = 0; i < 3; i++)
    {
        Item* item = inventorySlots[i].getPrimaryItem();
        if (item != nullptr)
        {
            item->pos = in_pos;
            item->getRigidBody()->pos = in_pos;
        }
    }
}

Player* Human::getPlayer()
{
    return playerID == -1 ? nullptr : &Engine::players[playerID];
}

void Human::setPlayer(Player* player)
{
    playerID = player == nullptr ? -1 : player->getIndex();
}

RigidBody* Human::getRigidBody(int index)
{
	if (index > 15) throw std::runtime_error("Error: Human::getRigidBody index out of range.");
	return &Engine::bodies[bones[index].bodyID];
}

Vehicle* Human::getVehicle()
{
    return vehicleID == -1 ? nullptr : &Engine::vehicles[vehicleID];
}

void Human::setVehicle(Vehicle* vehicle)
{
    vehicleID = vehicle == nullptr ? -1 : vehicle->getIndex();
}

void Human::speak(const std::string& message, int volumeLevel)
{
    char* nonConstMessage = const_cast<char*>(message.c_str());
    Engine::createEventMessage(MESSAGE_HUMAN, nonConstMessage, getIndex(), volumeLevel);
}

bool Human::mountItem(Item* childItem, unsigned int slot)
{
    return (bool)Engine::linkItem(childItem->getIndex(), -1, getIndex(), slot);
}

void Human::applyDamage(int bone, int damage)
{
    Engine::humanApplyDamage(getIndex(), bone, 0, damage);
}

// Account

int Account::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::accounts) / sizeof(*this);
}

void Account::ban(int minutes, const std::string& reason, const std::string& adminName)
{
    banTime = minutes;
    adminLog(format("{} banned {} ({}) for {} minutes. Reason: {}", adminName.c_str(), name, dashPhoneNumber(phoneNumber), std::to_string(minutes), reason.c_str()));
}

void Account::addBan(int minutes, const std::string& reason, const std::string& adminName)
{
    banTime += minutes;
    adminLog(format("{} addBanned {} ({}) for {} minutes. Reason: {}", adminName, name, dashPhoneNumber(phoneNumber), std::to_string(minutes), reason));
}

void Account::punish(int count, const std::string& reason, const std::string& adminName)
{
    json adminPersistence = getJSONFromFile("punishments.json");
    std::string s_phoneNumber = std::to_string(phoneNumber);

    if (adminPersistence["punishments"].is_null())
        adminPersistence["punishments"] = json{};

    if (adminPersistence["punishments"][s_phoneNumber].is_null())
        adminPersistence["punishments"][s_phoneNumber] = 0;
    int numPunishments = adminPersistence["punishments"][s_phoneNumber];

    int banMinutes = 0;
    for (int i = 0; i < count; i++)
        banMinutes += START_BAN_MINS * pow(BAN_MULT, numPunishments++);
    adminPersistence["punishments"][s_phoneNumber] = numPunishments;

    // The += makes this similar to addBan().
    banTime += banMinutes;
    std::string playerName = name;
    adminLog(format("{} punished {} ({}) with count of {}. Reason: {}", adminName,
                     playerName, dashPhoneNumber(phoneNumber), std::to_string(count), reason));
    
    if (adminPersistence["warnings"].is_null())
        adminPersistence["warnings"] = json{};
    if (adminPersistence["warnings"][s_phoneNumber].is_null())
        adminPersistence["warnings"][s_phoneNumber] = std::vector<json>{};
    adminPersistence["warnings"][s_phoneNumber].push_back(json{{"reason", "Banned for: " + reason}, {"when", getDateTime()}});

    saveJSONToFile(adminPersistence, "punishments.json");
}

void Account::warn(const std::string& warning)
{
    json adminPersistence = getJSONFromFile("punishments.json");
    std::string s_phoneNumber = std::to_string(phoneNumber);

    if (adminPersistence["warnings"].is_null())
        adminPersistence["warnings"] = json{};
    if (adminPersistence["warnings"][s_phoneNumber].is_null())
        adminPersistence["warnings"][s_phoneNumber] = std::vector<json>{};
    adminPersistence["warnings"][s_phoneNumber].push_back(json{{"reason", warning}, {"when", getDateTime()}});

    saveJSONToFile(adminPersistence, "punishments.json");
}

// Item

int Item::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::items) / sizeof(*this);
}

void Item::remove()
{
    Engine::deleteItem(getIndex());
}

void Item::update()
{
    Engine::createEventUpdateItem(getIndex());
}

bool Item::mount(Item* childItem, int slot)
{
    return (bool)Engine::linkItem(getIndex(), childItem->getIndex(), -1, slot);
}

bool Item::unmount()
{
    return (bool)Engine::linkItem(getIndex(), -1, -1, 0);
}

void Item::speak(const std::string& message, int volumeLevel)
{
    char* nonConstMessage = const_cast<char*>(message.c_str());
    Engine::createEventMessage(MESSAGE_ITEM, nonConstMessage, getIndex(), volumeLevel);
}

void Item::explode()
{
    Engine::grenadeExplosion(getIndex());
}

void Item::setMemo(const std::string& memo)
{
    Engine::itemSetMemo(getIndex(), memo.c_str());
}

void Item::computerTransmitLine(unsigned int line)
{
    Engine::itemComputerTransmitLine(getIndex(), line);
}

void Item::computerIncrementLine()
{
    Engine::itemComputerIncrementLine(getIndex());
}

void Item::computerSetLine(unsigned int line, const std::string& newLine)
{
    if (line >= 32) throw std::runtime_error("Error: Item::computerSetLine index out of range.");
    std::strncpy(computerLines[line], newLine.c_str(), 63);
}

void Item::computerSetLineColors(unsigned int line, std::string_view colors)
{
    if (line >= 32) throw std::runtime_error("Error: Item::computerSetLineColors index out of range.");
    std::memcpy(computerLineColors[line], colors.data(),
	            std::min(std::size_t(63), colors.size()));
}

void Item::computerSetColor(unsigned int line, unsigned int column, unsigned char color)
{
	if (line >= 32 || column >= 64) throw std::runtime_error("Error: Item::computerSetColor index out of range.");
    computerLineColors[line][column] = color;
}

void Item::cashAddBill(int position, int value)
{
    if (value >= 8) throw std::runtime_error("Error: cashAddBill index out of range.");
    Engine::itemCashAddBill(getIndex(), position, value);
}

void Item::cashRemoveBill(int position)
{
    Engine::itemCashRemoveBill(getIndex(), position);
}

int Item::cashGetBillValue()
{
    return Engine::itemCashGetBillValue(getIndex());
}

RigidBody* Item::getRigidBody() { return &Engine::bodies[bodyID]; }

void Item::pickUpHook(std::function<bool(int &itemID, int &childItemID, int &parentHumanID, int &slot)> funcToAdd)
{
    Hook tempHook(&LinkItem, funcToAdd);
    LinkItem.parallelInfoVec[tempHook.index] = getIndex();
}

void Item::pickUpHook(std::function<bool(int &itemID, int &childItemID, int &parentHumanID, int &slot)> funcToAdd, char priority)
{
    Hook tempHook(&LinkItem, funcToAdd, priority);
    LinkItem.parallelInfoVec[tempHook.index] = getIndex();
}

void Item::pickUpHookOnce(std::function<bool(int &itemID, int &childItemID, int &parentHumanID, int &slot)> funcToAdd)
{
    Hook tempHook(&LinkItem, funcToAdd);
    LinkItem.parallelInfoVec[tempHook.index] = getIndex() + MAX_NUM_OF_ITEMS;
}

void Item::pickUpHookOnce(std::function<bool(int &itemID, int &childItemID, int &parentHumanID, int &slot)> funcToAdd, char priority)
{
    Hook tempHook(&LinkItem, funcToAdd, priority);
    LinkItem.parallelInfoVec[tempHook.index] = getIndex() + MAX_NUM_OF_ITEMS;
}

bool Item::hasPickUpHook()
{
    int index = getIndex();
    for (int info : LinkItem.parallelInfoVec)
        if (index == info || index == info - MAX_NUM_OF_ITEMS)
            return true;
    return false;
}

bool Item::removePickUpHook()
{
    int index = getIndex();
    unsigned short i = 0;
    for (int info : LinkItem.parallelInfoVec)
        if (index == info || index == info - MAX_NUM_OF_ITEMS)
        {
            LinkItem.removeHook(i);
            return true;
            i++;
        }
    return false;
}

// Vehicles

int Vehicle::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::vehicles) / sizeof(*this);
}

VehicleType* Vehicle::getType()
{
    return &Engine::vehicleTypes[type];
}

Event* Vehicle::updateType()
{
    Engine::createEventCreateVehicle(getIndex());
    return &Engine::events[*Engine::numEvents - 1];
}

Event* Vehicle::updateDestruction(int updateType, int partID, Vector* pos, Vector* normal)
{
    Engine::createEventUpdateVehicle(getIndex(), updateType, partID, pos, normal);
    return &Engine::events[*Engine::numEvents - 1];
}

void Vehicle::remove()
{
    Engine::deleteVehicle(getIndex());
}

Player* Vehicle::getLastDriver()
{
    return lastDriverPlayerID == -1 ? nullptr : &Engine::players[lastDriverPlayerID];
}

RigidBody* Vehicle::getRigidBody()
{
    return bodyID == -1 ? nullptr : &Engine::bodies[bodyID];
}

TrafficCar* Vehicle::getTrafficCar()
{
    return trafficCarID == -1 ? nullptr : &Engine::trafficCars[trafficCarID];
}

void Vehicle::setTrafficCar(TrafficCar* trafficCar)
{
    trafficCarID = trafficCar->getIndex();
}

bool Vehicle::getIsWindowBroken(unsigned int index)
{
    if (index > 7) throw std::runtime_error("Error: Vehicle::getIsWindowBroken index out of range.");
    return (bool)windowStates[index];
}

void Vehicle::setIsWindowBroken(unsigned int index, bool isBroken)
{
    if (index > 7) throw std::runtime_error("Error: Vehicle::setIsWindowBroken index out of range.");
    windowStates[index] = (int)isBroken;
}

// TrafficCar

int TrafficCar::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::trafficCars) / sizeof(*this);
}

VehicleType* TrafficCar::getType() { return &Engine::vehicleTypes[type]; }

void TrafficCar::setType(VehicleType* vehicleType)
{
	if (vehicleType == nullptr)
		throw std::runtime_error("Cannot set a traffic car's type to nullptr");
	type = vehicleType->getIndex();
}

Human* TrafficCar::getHuman()
{
	return humanID == -1 ? nullptr : &Engine::humans[humanID];
}

void TrafficCar::setHuman(Human* human)
{
	humanID = human == nullptr ? -1 : human->getIndex();
}

Vehicle* TrafficCar::getVehicle()
{
	return vehicleID == -1 ? nullptr : &Engine::vehicles[vehicleID];
}

void TrafficCar::setVehicle(Vehicle* vehicle)
{
	vehicleID = vehicle == nullptr ? -1 : vehicle->getIndex();
}

// ShopCar

VehicleType* ShopCar::getType() { return &Engine::vehicleTypes[type]; }

void ShopCar::setType(VehicleType* vehicleType)
{
	if (vehicleType == nullptr) {
		throw std::runtime_error("Cannot set a shop car's type to nullptr");
	}
	type = vehicleType->getIndex();
}

// Bullet

Player* Bullet::getPlayer()
{
    return playerID == -1 ? nullptr : &Engine::players[playerID];
}

// RigidBody

int RigidBody::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::bodies) / sizeof(*this);
}

Bond* RigidBody::bondTo(RigidBody* other, Vector* thisLocalPos, Vector* otherLocalPos)
{
    int bondID = Engine::createBondRigidBodyToRigidBody(getIndex(), other->getIndex(), thisLocalPos, otherLocalPos);
    return bondID == -1 ? nullptr : &Engine::bonds[bondID];
}

Bond* RigidBody::bondRotTo(RigidBody* other)
{
    int bondID = Engine::createBondRigidBodyRotRigidBody(getIndex(), other->getIndex());
    return bondID == -1 ? nullptr : &Engine::bonds[bondID];
}

Bond* RigidBody::bondToLevel(Vector* localPos, Vector* globalPos)
{
    int bondID = Engine::createBondRigidBodyToLevel(getIndex(), localPos, globalPos);
    return bondID == -1 ? nullptr : &Engine::bonds[bondID];
}

void RigidBody::collideLevel(Vector* localPos, Vector* normal, float a, float b, float c, float d)
{
	Engine::addCollisionRigidBodyOnLevel(getIndex(), localPos, normal, a, b, c, d);
}

// InventorySlot

Item* InventorySlot::getPrimaryItem()
{
    if (count < 1) return nullptr;
    return primaryItemID == -1 ? nullptr : &Engine::items[primaryItemID];
}

Item* InventorySlot::getSecondaryItem()
{
    if (count < 1) return nullptr;
    return secondaryItemID == -1 ? nullptr : &Engine::items[secondaryItemID];
}

// Bond

int Bond::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::bonds) / sizeof(*this);
}

RigidBody* Bond::getBody() { return &Engine::bodies[bodyID]; }

RigidBody* Bond::getOtherBody() { return &Engine::bodies[otherBodyID]; }

// Street

int Street::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::streets) / sizeof(*this);
}

StreetIntersection* Street::getIntersectionA()
{
	return &Engine::streetIntersections[intersectionA];
}

StreetIntersection* Street::getIntersectionB()
{
	return &Engine::streetIntersections[intersectionB];
}

StreetLane* Street::getLane(unsigned int index)
{
	if (index >= numLanes) throw std::runtime_error("Error: Street::getLane index out of range.");
	return &lanes[index];
}

// StreetIntersection


int StreetIntersection::getIndex()
{
	return ((uintptr_t)this - (uintptr_t)Engine::streetIntersections) / sizeof(*this);
}

Street* StreetIntersection::getStreetEast()
{
	return streetEast == -1 ? nullptr : &Engine::streets[streetEast];
}

Street* StreetIntersection::getStreetSouth()
{
	return streetSouth == -1 ? nullptr : &Engine::streets[streetSouth];
}

Street* StreetIntersection::getStreetWest()
{
	return streetWest == -1 ? nullptr : &Engine::streets[streetWest];
}

Street* StreetIntersection::getStreetNorth()
{
	return streetNorth == -1 ? nullptr : &Engine::streets[streetNorth];
}

// VehicleType

int VehicleType::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::vehicleTypes) / sizeof(*this);
}

// ItemType

int ItemType::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::itemTypes) / sizeof(*this);
}

bool ItemType::getCanMountTo(ItemType* parent)
{
    if (parent == nullptr) throw std::runtime_error("Error: ItemType::getCanMountTo passed nullptr.");
    return (bool)canMountTo[parent->getIndex()];
}

void ItemType::setCanMountTo(ItemType* parent, bool canMount)
{
    if (parent == nullptr) throw std::runtime_error("Error: ItemType::setCanMountTo passed nullptr.");
    canMountTo[parent->getIndex()] = (int)canMount;
}

// Building

int Building::getIndex()
{
    return ((uintptr_t)this - (uintptr_t)Engine::buildings) / sizeof(*this);
}

ShopCar* Building::getShopCar(int index)
{
    if (index > 15) throw std::runtime_error("Error: Building::getShopCar index out of range.");
    return &shopCars[index];
}

// Connection

EarShot* Connection::getEarShot(int index)
{
    if (index > 7) throw std::runtime_error("Error: Connection::getEarShot index out of range.");
    return &earShots[index];
}

void Connection::disconnect() { timeout = 50 * SERVER_TPS; }

std::string Connection::getAddress() { return addressFromInteger(address); }
