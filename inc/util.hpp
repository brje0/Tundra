#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>
#include <libgen.h>         // dirname
#include <unistd.h>         // readlink
#include <linux/limits.h>   // PATH_MAX
#include <cstring>
#include <string>
#include <utility>
#include <algorithm>
#include <cstdlib>
#include <thread>
#include <memory>
#include <chrono>
#include <ctime>
#include <cstdio>
#include <typeinfo>

#include "../lib/json/single_include/nlohmann/json.hpp"
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../lib/cpp-httplib/httplib.h"
#include "hook.hpp"
#include "hooks.hpp"
#include "command.hpp"
#include "engine.hpp"
#include "engine_structs.hpp"

using json = nlohmann::json;

extern const unsigned char SERVER_TPS;
extern const float DEFAULT_GRAVITY;

extern const unsigned short MAX_NUM_OF_ACCOUNTS;
extern const unsigned short MAX_NUM_OF_BONDS;
extern const unsigned short MAX_NUM_OF_BULLETS;
extern const unsigned short MAX_NUM_OF_HUMANS;
extern const unsigned short MAX_NUM_OF_ITEMS;
extern const unsigned short MAX_NUM_OF_PLAYERS;
extern const unsigned short MAX_NUM_OF_RIGIDBODIES;
extern const unsigned short MAX_NUM_OF_VEHICLES;
extern const unsigned short MAX_NUM_OF_ITEMTYPES;
extern const unsigned short MAX_NUM_OF_VEHICLETYPES;

extern const char STATE_PREGAME;
extern const char STATE_GAME;
extern const char STATE_RESTARTING;

extern const bool HOOK_OVERRIDE;
extern const bool HOOK_CONTINUE;

extern const Vector X_AXIS;
extern const Vector Y_AXIS;
extern const Vector Z_AXIS;

extern const std::string DISTANCE_NAMES[3];
extern const std::string VEHICLE_COLORS[6];

typedef void(handleHTTPResultFunc)(httplib::Result& res);

/*
Note: all templated functions need to be both declared static and defined within this header.
If the templated function signature is declared here but defined in an external .cpp file,
other .cpp files will not be able to access this definition because the compiler can "see"
only one compilation unit at a time (in practice, this means that the .so will compile just
fine since the templated function is technically declared everywhere it's used, but when you
try to run it, you'll get a cryptic symbol lookup error since only one .cpp file "knows" the
definition). If the templated function is both declared and defined here, but it is not declared
static, then an additional (and equivalent) definition of the function will be created each time
this file is #included; this will make the linker scream at you.
*/

// Clears a specified character from a string.
// @param toClear The string to clear.
// @param char chr The character to clear from the string.
// @param std::string The new string.
std::string clearChar(std::string toClear, char chr);

// Returns a formatted string, similar to what printf would print.
// Curly braces, i.e."{}," indicate a position that should be replaced with an argument.
// @param int ? start The index in the string to begin searching in.
// @param std::string formatString The string to be formatted.
// @param T arg The argument(s) to populate the string with. Must be able to be validly passed to std::to_string or the std::string constructor.
//            Note that it is not an error to pass in more arguments than formatString expects.
//            E.g. format("{}", 0, 1) is valid.
// @return std::string The formatted string.
template <typename T>
static std::string format(std::string formatString, T arg);
template <typename T, typename... Ts>
static std::string format(std::string formatString, T arg, Ts... args);
static std::string format(int start, std::string formatString, std::string arg);
static std::string format(int start, std::string formatString, const char* arg);
static std::string format(int start, std::string formatString, char* arg);
template <typename T>
static std::string format(int start, std::string formatString, T arg);
template <typename... Ts>
static std::string format(int start, std::string formatString, std::string arg, Ts... args);
template <typename... Ts>
static std::string format(int start, std::string formatString, const char* arg, Ts... args);
template <typename... Ts>
static std::string format(int start, std::string formatString, char* arg, Ts... args);
template <typename T, typename... Ts>
static std::string format(int start, std::string formatString, T arg, Ts... args);

template <typename T>
static std::string format(std::string formatString, T arg)
{
    return format(0, formatString, arg);
}

template <typename T, typename... Ts>
static std::string format(std::string formatString, T arg, Ts... args)
{
    return format(0, formatString, arg, args...);
}

static std::string format(int start, std::string formatString, std::string s_arg)
{
    std::size_t pos = formatString.find("{}", start);
    if (pos != std::string::npos)
    {
        formatString.erase(pos, 2);
        formatString.insert(pos, s_arg);
    }
    return formatString;
}

static std::string format(int start, std::string formatString, std::string_view arg)
{
    std::size_t pos = formatString.find("{}", start);
    if (pos != std::string::npos)
    {
        std::string s_arg(arg);
        formatString.erase(pos, 2);
        formatString.insert(pos, s_arg);
    }
    return formatString;
}

static std::string format(int start, std::string formatString, const char* arg)
{
    std::size_t pos = formatString.find("{}", start);
    if (pos != std::string::npos)
    {
        std::string s_arg(arg);
        formatString.erase(pos, 2);
        formatString.insert(pos, s_arg);
    }
    return formatString;
}

static std::string format(int start, std::string formatString, char* arg)
{
    std::size_t pos = formatString.find("{}", start);
    if (pos != std::string::npos)
    {
        std::string s_arg(arg);
        formatString.erase(pos, 2);
        formatString.insert(pos, s_arg);
    }
    return formatString;
}

template <typename T>
static std::string format(int start, std::string formatString, T arg)
{
    std::size_t pos = formatString.find("{}", start);
    if (pos != std::string::npos)
    {
        std::string s_arg = std::to_string(arg);
        formatString.erase(pos, 2);
        formatString.insert(pos, s_arg);
    }
    return formatString;
}

template <typename... Ts>
static std::string format(int start, std::string formatString, std::string s_arg, Ts... args)
{
    std::size_t pos = formatString.find("{}", start);
    if (pos != std::string::npos)
    {
        formatString.erase(pos, 2);
        formatString.insert(pos, s_arg);
        return format(pos + s_arg.size(), formatString, args...);
    }
    return formatString;
}

template <typename... Ts>
static std::string format(int start, std::string formatString, std::string_view arg, Ts... args)
{
    std::size_t pos = formatString.find("{}", start);
    if (pos != std::string::npos)
    {
        std::string s_arg(arg);
        formatString.erase(pos, 2);
        formatString.insert(pos, s_arg);
    }
    return formatString;
}

template <typename... Ts>
static std::string format(int start, std::string formatString, const char* arg, Ts... args)
{
    std::size_t pos = formatString.find("{}", start);
    if (pos != std::string::npos)
    {
        std::string s_arg(arg);
        formatString.erase(pos, 2);
        formatString.insert(pos, s_arg);
        return format(pos + s_arg.size(), formatString, args...);
    }
    return formatString;
}

template <typename... Ts>
static std::string format(int start, std::string formatString, char* arg, Ts... args)
{
    std::size_t pos = formatString.find("{}", start);
    if (pos != std::string::npos)
    {
        std::string s_arg(arg);
        formatString.erase(pos, 2);
        formatString.insert(pos, s_arg);
        return format(pos + s_arg.size(), formatString, args...);
    }
    return formatString;
}

template <typename T, typename... Ts>
static std::string format(int start, std::string formatString, T arg, Ts... args)
{
    std::size_t pos = formatString.find("{}", start);
    if (pos != std::string::npos)
    {
        std::string s_arg = std::to_string(arg);
        formatString.erase(pos, 2);
        formatString.insert(pos, s_arg);
        return format(pos + s_arg.size(), formatString, args...);
    }
    return formatString;
}

// Returns a valid IP as a string from the integer provided.
// @param unsigned int address
// @return std::string
std::string addressFromInteger(unsigned int address);

// Returns the time since Jan 1st, 1970 accurate to the millisecond.
// @return double The time in seconds.
double getEpochTime();

// Returns the current date, formatted as MM-DD-YYYY.
// @return std::string
std::string getDate();

// Returns the current time, formatted as HH:MM:SS.
// @return std::string
std::string getTime();

// Returns the current date and time, formatted as a string.
// E.g. Thu Jan 1 00:00:00 1970
// @return std::string
std::string getDateTime();

// Converts a raw number of minutes to a readable string.
// @param minutes int
// @return std::string
std::string getCleanTime(int minutes);

// Announces a message in global chat.
// @param message std::string
void chatAnnounce(const std::string& message);

// Creates an item.
// @param ItemType* type
// @param Vector* pos
// @param Vector* ? vel
// @param RotMatrix* ? rot
// @return Item* The created item.
Item* createItem(ItemType* type, Vector* pos);
Item* createItem(ItemType* type, Vector* pos, Vector* vel);
Item* createItem(ItemType* type, Vector* pos, RotMatrix* rot);
Item* createItem(ItemType* type, Vector* pos, Vector* vel, RotMatrix* rot);

// Creates a vehicle.
// @param VehicleType* type
// @param Vector* pos
// @param Vector* ? vel
// @param RotMatrix* rot
// @param int color
// @return Vehicle* The created vehicle.
Vehicle* createVehicle(VehicleType* type, Vector* pos);
// 3 args
Vehicle* createVehicle(VehicleType* type, Vector* pos, Vector* vel);
Vehicle* createVehicle(VehicleType* type, Vector* pos, RotMatrix* rot);
Vehicle* createVehicle(VehicleType* type, Vector* pos, int color);
// 4 args
Vehicle* createVehicle(VehicleType* type, Vector* pos, Vector* vel, RotMatrix* rot);
Vehicle* createVehicle(VehicleType* type, Vector* pos, RotMatrix* rot, int color);
Vehicle* createVehicle(VehicleType* type, Vector* pos, Vector* vel, int color);
// 5 args
Vehicle* createVehicle(VehicleType* type, Vector* pos, Vector* vel, RotMatrix* rot, int color);

// Finds an ItemType by its name or returns nullptr if none is found.
// Not case-sensitive.
// @param name std::string
// @return ItemType* ?
ItemType* getItemTypeByName(std::string name);

// Finds an ItemType index by its name or returns -1 if none is found.
// Not case-sensitive.
// @param name std::string
// @return int
int getItemTypeIndexByName(std::string name);

// Finds a VehicleType by its name or returns nullptr if none is found.
// Not case-sensitive.
// @param name std::string
// @return VehicleType* ?
VehicleType* getVehicleTypeByName(std::string name);

// Finds a VehicleType index by its name or returns -1 if none is found.
// Not case-sensitive.
// @param name std::string
// @return int
int getVehicleTypeIndexByName(std::string name);

// Returns the number that corresponds to the color specified by the name, or -1 if no colors match.
// Not case-sensitive.
// @param std::string name
// @return int
int getVehicleColorByName(std::string name);

// Gets a JSON persistence file from the persistence directory.
// Will create a file if none is found.
// @param filename string Name of the file to be gotten.
// @return data json JSON object.
json getJSONFromFile(const std::string& filename);

// Saves a JSON object to a file.
// Will create a file if none is found.
// @param data json JSON data to save.
// @param filename string The name of the file.
void saveJSONToFile(const json& data, const std::string& filename);

// Sends a synchronous HTTP GET request.
// @param std::string scheme
// @param std::string path
// @param httplib::Header ? headers
// @param handleHTTPResultFunc handleResult The function to be called when the server responds.
//                                          This function will be passed the Result of the GET request in an http::Result object.
void httpGetSync(const std::string& scheme, const std::string& path, std::function<handleHTTPResultFunc> handleResult);
void httpGetSync(const std::string& scheme, const std::string& path, const httplib::Headers& headers,
                 std::function<handleHTTPResultFunc> handleResult);

// Sends an asynchronous HTTP GET request via a separate thread.
// @param std::string scheme
// @param std::string path
// @param httplib::Header ? headers
// @param handleHTTPResultFunc handleResult The function to be called when the server responds.
//                                              This function will be passed the Result of the GET request in an http::Result object.
void httpGet(const std::string& scheme, const std::string& path, const std::function<handleHTTPResultFunc>& handleResult);
void httpGet(const std::string& scheme, const std::string& path, const httplib::Headers& headers,
             const std::function<handleHTTPResultFunc>& handleResult);

// Sends a synchronous HTTP POST request.
// @param std::string scheme
// @param std::string path
// @param httplib::Header ? headers
// @param handleHTTPResultFunc handleResult The function to be called when the server responds.
//                                          This function will be passed the Result of the POST request in an http::Result object.
void httpPostSync(const std::string& scheme, const std::string& path, const std::string& body,
                  const std::string& contentType, std::function<handleHTTPResultFunc> handleResult);
void httpPostSync(const std::string& scheme, const std::string& path, const httplib::Headers& headers, const std::string& body,
                  const std::string& contentType, std::function<handleHTTPResultFunc> handleResult);

// Sends an asynchronous HTTP POST request via a separate thread.
// @param std::string scheme
// @param std::string path
// @param httplib::Header ? headers
// @param handleHTTPResultFunc handleResult The function to be called when the server responds.
//                                          This function will be passed the Result of the POST request in an http::Result object.
void httpPost(const std::string& scheme, const std::string& path, const std::string& body,
              const std::string& contentType, const std::function<handleHTTPResultFunc>& handleResult);
void httpPost(const std::string& scheme, const std::string& path, const httplib::Headers& headers, const std::string& body,
              const std::string& contentType, const std::function<handleHTTPResultFunc>& handleResult);

// Appends a message, prepended by a newline, into a file.
// @param std::string_view filename
// @param std::string_view message
void logToFile(std::string_view filename, std::string_view message);

// Appends a message, prepended by a newline, into a file alongside the date. e.g. [DATE] MESSAGE
// @param std::string_view filename
// @param std::string_view message
void logToFileDate(std::string_view filename, std::string_view message);

// Appends a message, prepended by a newline, into a file alongside the time. e.g. [TIME] MESSAGE
// @param std::string_view filename
// @param std::string_view message
void logToFileTime(std::string_view filename, std::string_view message);

// Appends a message, prepended by a newline, into a file alongside the date and time. e.g. [DATE TIME] MESSAGE
// @param std::string_view filename
// @param std::string_view message
void logToFileDateTime(std::string_view filename, std::string_view message);

// Appends a message, prepended by a newline, into adminLog.txt alongside the date and time.
// @param toLog string The message to log.
void adminLog(std::string_view toLog);

// Finds an active player by their phone number.
// @param phoneNumber int The phone number of the player you want to find.
// @return Player* or nullptr if not found
Player* findPlayerByPhone(int phoneNumber);

// Finds an account by their phone number.
// @param phoneNumber int The phone number of the account you want to find.
// @return Account* or nullptr if not found
Account* findAccountByPhone(int phoneNumber);

// Converts a yaw value to a rotation matrix.
// @param yaw radians
// @return RotMatrix
RotMatrix yawToRotMatrix(float yaw);

// Converts a pitch value to a rotation matrix.
// @param pitch radians
// @return RotMatrix
RotMatrix pitchToRotMatrix(float pitch);

// Converts a roll value to a rotation matrix.
// @param pitch radians
// @return RotMatrix
RotMatrix rollToRotMatrix(float roll);

// Generates an rotation matrix from a specified angle of rotation about a specified axis.
// @param axis Vector (must be unit vector)
// @param angle radians
// @return RotMatrix
RotMatrix axisAngleToRotMatrix(Vector axis, float angle);

// Returns a rotation matrix that will make an object at pos point towards targetPos.
// @param pos Vector
// @param targetPos Vector
// @return RotMatrix
RotMatrix pointTowards(Vector pos, Vector targetPos);

// TODO: Check that these line up with in-game directions.
extern const RotMatrix NORTH;
extern const RotMatrix NORTHEAST;
extern const RotMatrix EAST;
extern const RotMatrix SOUTHEAST;
extern const RotMatrix SOUTH;
extern const RotMatrix SOUTHWEST;
extern const RotMatrix WEST;
extern const RotMatrix NORTHWEST;

// Returns the x and y coordinates of a point on the edge of a circle given the radius and angle.
// @param radius float
// @param angle radians
// @return std::pair<float, float>
std::pair<float, float> getCirclePoint(float radius, float angle);

// Returns a vector of coordinates on the edge of a circle given the number of points to find,
// the radius, and possibly the angle to rotate the circle by initially.
// @param radius float
// @param numPoints int
// @param angleOffset? float The angle the circle should be rotated by before retrieving the points.
std::vector<std::pair<float, float>> getCirclePoints(float radius, int numPoints);
std::vector<std::pair<float, float>> getCirclePoints(float radius, int numPoints, float angleOffset);

// Returns a random integer in the range of lower to upper, inclusive.
// @param lower int
// @param upper int
int randomInt(int lower, int upper);

// Returns a random float in the range of lower to upper, inclusive.
// @param lower float
// @param upper int
float randomFloat(float lower, float upper);

// Determines whether a position is within a cuboid.
// @param pos Vector The position to be checked.
// @param cornerA Vector The lower corner of the cuboid.
// @param cornerB Vector The upper corner of the cuboid.
// @return bool
bool isVectorInCuboid(Vector pos, Vector cornerA, Vector cornerB);

// Generates a random position within a cuboid.
// @param cornerA Vector The lower corner of the cuboid.
// @param cornerB Vector The upper corner of the cuboid.
// @return Vector
Vector vecRandBetween(Vector cornerA, Vector cornerB);

// Inserts a dash into a phone number. E.g. 2564096 becomes "256-4096"
// @param phoneNumber int The phone number to be dashed.
// @return std::string The dashed phone number.
std::string dashPhoneNumber(int phoneNumber);

// Removes a dash from a phone number. E.g. "256-4096" becomes 2564096
// @param phoneNumber std::string The phone number to be undashed.
// @return int The undashed phone number.
int undashPhoneNumber(std::string phoneNumber);
