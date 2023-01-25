#include "../inc/util.hpp"

const unsigned char SERVER_TPS = 60;
const float DEFAULT_GRAVITY = 0.002722222;

const unsigned short MAX_NUM_OF_ACCOUNTS = 32768;
const unsigned short MAX_NUM_OF_BONDS = 16384;
const unsigned short MAX_NUM_OF_BULLETS = 16384;
const unsigned short MAX_NUM_OF_HUMANS = 256;
const unsigned short MAX_NUM_OF_ITEMS = 1024;
const unsigned short MAX_NUM_OF_PLAYERS = 256;
const unsigned short MAX_NUM_OF_RIGIDBODIES = 8192;
const unsigned short MAX_NUM_OF_VEHICLES = 512;
const unsigned short MAX_NUM_OF_ITEMTYPES = 46;
const unsigned short MAX_NUM_OF_VEHICLETYPES = 14;

const char STATE_PREGAME = 1;
const char STATE_GAME = 2;
const char STATE_RESTARTING = 3;

const char TYPE_DRIVING = 1;
const char TYPE_RACE = 2;
const char TYPE_ROUND = 3;
const char TYPE_WORLD = 4;
const char TYPE_TERMINATOR = 5;
const char TYPE_COOP = 6;
const char TYPE_VERSUS = 7;

const bool HOOK_OVERRIDE = true;
const bool HOOK_CONTINUE = false;

const Vector X_AXIS(1, 0, 0);
const Vector Y_AXIS(0, 1, 0);
const Vector Z_AXIS(0, 0, 1);

const std::string DISTANCE_NAMES[3] = {
    "Whisper",      // 0
    "Normal",       // 1
    "Yell"          // 2
};

const std::string VEHICLE_COLORS[6] = {
    "Black",    // 0
    "Red",      // 1
    "Blue",     // 2
    "Silver",   // 3
    "White",    // 4
    "Gold",     // 5
};

std::string clearChar(std::string toClear, char chr)
{
    for (int i = toClear.size() - 1; i > -1; i--)
    {
        if (toClear[i] == chr)
            toClear.erase(i, 1);
    }
    return toClear;
}

std::string addressFromInteger(unsigned int address)
{
    unsigned char bytes[4];
    bytes[3] = address & 0xFF;
    bytes[2] = (address >> 8) & 0xFF;
    bytes[1] = (address >> 16) & 0xFF;
    bytes[0] = (address >> 24) & 0xFF;
    char buf[16];
    sprintf(buf, "%i.%i.%i.%i", (int)bytes[0], (int)bytes[1], (int)bytes[2], (int)bytes[3]);
    return std::string{buf};
}

double getEpochTime()
{
    auto now = std::chrono::steady_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
    return microseconds / 1'000'000.;
}

std::string getDate()
{
    time_t now = time(0);
    struct tm tstruct = *localtime(&now);
    char buf[80];
    strftime(buf, sizeof(buf), "%m-%d-%Y", &tstruct);
    return std::string{buf};
}

std::string getTime()
{
    time_t now = time(0);
    struct tm tstruct = *localtime(&now);
    char buf[80];
    strftime(buf, sizeof(buf), "%T", &tstruct);
    return std::string{buf};
}

std::string getDateTime()
{
    return getDate() + " " + getTime();
}

std::string getCleanTime(int minutes)
{
    // Integer division
    int hours = minutes / 60;
    minutes %= 60;
    // Integer division
    int days = hours / 24;
    hours %= 24;
    std::string ret;
    if (days != 0)
    {
        ret = std::to_string(days) + " days";
        if (hours != 0 && minutes != 0)
        {
            ret += ", " + std::to_string(hours) + " hours";
            ret += ", and " + std::to_string(minutes) + " minutes";
        }
        else if (hours != 0)
            ret += " and " + std::to_string(hours) + " hours";
        else if (minutes != 0)
            ret += " and " + std::to_string(minutes) + " minutes";
    }
    else if (hours != 0)
    {
        ret = std::to_string(hours) + " hours";
        if (minutes != 0)
            ret += " and " + std::to_string(minutes) + " minutes";
    }
    else if (minutes != 0)
        ret = std::to_string(minutes) + " minutes";
    return ret;
}

void chatAnnounce(const std::string& message)
{
    Engine::createEventMessage(MESSAGE_GLOBAL, const_cast<char*>(message.c_str()), -1, 0);
}

Item* createItem(ItemType* type, Vector* pos)
{
    Vector vel;
    RotMatrix rot;
    int index = Engine::createItem(type->getIndex(), pos, &vel, &rot);
    return &Engine::items[index];
}

Item* createItem(ItemType* type, Vector* pos, Vector* vel)
{
    RotMatrix rot;
    int index = Engine::createItem(type->getIndex(), pos, vel, &rot);
    return &Engine::items[index];
}

Item* createItem(ItemType* type, Vector* pos, RotMatrix* rot)
{
    Vector vel;
    int index = Engine::createItem(type->getIndex(), pos, &vel, rot);
    return &Engine::items[index];
}

Item* createItem(ItemType* type, Vector* pos, Vector* vel, RotMatrix* rot)
{
    int index = Engine::createItem(type->getIndex(), pos, vel, rot);
    return &Engine::items[index];
}

Vehicle* createVehicle(VehicleType* type, Vector* pos)
{
    Vector vel;
    RotMatrix rot;
    int index = Engine::createVehicle(type->getIndex(), pos, &vel, &rot, randomInt(0, 5));
    return &Engine::vehicles[index];
}

// 3 args

Vehicle* createVehicle(VehicleType* type, Vector* pos, Vector* vel)
{
    RotMatrix rot;
    int index = Engine::createVehicle(type->getIndex(), pos, vel, &rot, randomInt(0, 5));
    return &Engine::vehicles[index];
}

Vehicle* createVehicle(VehicleType* type, Vector* pos, RotMatrix* rot)
{
    Vector vel;
    int index = Engine::createVehicle(type->getIndex(), pos, &vel, rot, randomInt(0, 5));
    return &Engine::vehicles[index];
}

Vehicle* createVehicle(VehicleType* type, Vector* pos, int color)
{
    Vector vel;
    RotMatrix rot;
    int index = Engine::createVehicle(type->getIndex(), pos, &vel, &rot, color);
    return &Engine::vehicles[index];
}

// 4 args

Vehicle* createVehicle(VehicleType* type, Vector* pos, Vector* vel, RotMatrix* rot)
{
    int index = Engine::createVehicle(type->getIndex(), pos, vel, rot, randomInt(0, 5));
    return &Engine::vehicles[index];
}

Vehicle* createVehicle(VehicleType* type, Vector* pos, RotMatrix* rot, int color)
{
    Vector vel;
    int index = Engine::createVehicle(type->getIndex(), pos, &vel, rot, color);
    return &Engine::vehicles[index];
}

Vehicle* createVehicle(VehicleType* type, Vector* pos, Vector* vel, int color)
{
    RotMatrix rot;
    int index = Engine::createVehicle(type->getIndex(), pos, vel, &rot, color);
    return &Engine::vehicles[index];
}

// 5 args

Vehicle* createVehicle(VehicleType* type, Vector* pos, Vector* vel, RotMatrix* rot, int color)
{
    int index = Engine::createVehicle(type->getIndex(), pos, vel, rot, color);
    return &Engine::vehicles[index];
}

ItemType* getItemTypeByName(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return std::tolower(c); });
    for (int i = 0; i < MAX_NUM_OF_ITEMTYPES; i++)
    {
        std::string typeName = Engine::itemTypes[i].name;
        std::transform(typeName.begin(), typeName.end(), typeName.begin(), [](unsigned char c){ return std::tolower(c); });
        if (!name.compare(typeName))
            return &Engine::itemTypes[i];
    }
    return nullptr;
}

int getItemTypeIndexByName(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return std::tolower(c); });
    for (int i = 0; i < MAX_NUM_OF_ITEMTYPES; i++)
    {
        std::string typeName = Engine::itemTypes[i].name;
        std::transform(typeName.begin(), typeName.end(), typeName.begin(), [](unsigned char c){ return std::tolower(c); });
        if (!name.compare(typeName))
            return i;
    }
    return -1;
}

VehicleType* getVehicleTypeByName(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return std::tolower(c); });
    for (int i = 0; i < MAX_NUM_OF_VEHICLETYPES; i++)
    {
        std::string typeName = Engine::vehicleTypes[i].name;
        std::transform(typeName.begin(), typeName.end(), typeName.begin(), [](unsigned char c){ return std::tolower(c); });
        if (!name.compare(typeName))
            return &Engine::vehicleTypes[i];
    }
    return nullptr;
}

int getVehicleTypeIndexByName(std::string name)
{
    std::transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ return std::tolower(c); });
    for (int i = 0; i < MAX_NUM_OF_VEHICLETYPES; i++)
    {
        std::string typeName = Engine::vehicleTypes[i].name;
        std::transform(typeName.begin(), typeName.end(), typeName.begin(), [](unsigned char c){ return std::tolower(c); });
        if (!name.compare(typeName))
            return i;
    }
    return -1;
}

int getVehicleColorByName(std::string name)
{
    std::transform(name.begin() + 1, name.end(), name.begin() + 1, [](unsigned char c){ return std::tolower(c); });
    name[0] = std::toupper(name[0]);
    for (int i = 0; i < 6; i++)
        if (!VEHICLE_COLORS[i].compare(name))
            return i;
    return -1;
}

json getJSONFromFile(const std::string& filepath)
{
    const std::filesystem::path origPath = std::filesystem::current_path();
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    std::string path;
    if (count != -1)
        path = dirname(result);
    else
        throw std::runtime_error("readlink() indicated error");
    // For some reason, the exe path will sometimes be returned with subrosadedicated.x64/userdirectory appended to the end.
    std::size_t found = path.find("/subrosadedicated.x64");
    if (found != std::string::npos)
        path.erase(found, std::string::npos);
    std::string_view dirPath;
    std::string name;
    std::size_t lastSlash = filepath.find_last_of('/');
    if (lastSlash != std::string::npos)
    {
        dirPath = filepath.substr(0, lastSlash + 1);
        name = filepath.substr(lastSlash + 1, std::string::npos);
    }
    else
        name = filepath;
    path += "/persistence";
    path += dirPath;
    std::filesystem::current_path(path);
    std::ifstream iFile(name);
    if (!iFile)
    {
        std::ofstream oFile(name);
        oFile << "{}";
        oFile.close();
        iFile.open(name);
    }
    json data = json::parse(iFile);
    iFile.close();
    std::filesystem::current_path(origPath);
    return data;
}

void saveJSONToFile(const json& data, const std::string& filepath)
{
    const std::filesystem::path origPath = std::filesystem::current_path();
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    std::string path;
    if (count != -1)
        path = dirname(result);
    else
        throw std::runtime_error("readlink() indicated error");
    std::size_t found = path.find("/subrosadedicated.x64");
    if (found != std::string::npos)
        path.erase(found, std::string::npos);
    std::string_view dirPath;
    std::string name;
    std::size_t lastSlash = filepath.find_last_of('/');
    if (lastSlash != std::string::npos)
    {
        dirPath = filepath.substr(0, lastSlash + 1);
        name = filepath.substr(lastSlash + 1, std::string::npos);
    }
    else
        name = filepath;
    path += "/persistence";
    path += dirPath;
    std::filesystem::current_path(path);
    std::ofstream oFile(name);
    oFile << data;
    oFile.close();
    std::filesystem::current_path(origPath);
}

// The handleResult function has to be passed in by value instead of reference because this function gets pulled
// into another thread and has to be called from there.
void httpGetSync(const std::string& scheme, const std::string& path, std::function<handleHTTPResultFunc> handleResult)
{
    httplib::Client cli(scheme);
    cli.set_connection_timeout(0, 300000);
    if (auto res = cli.Get(path))
        handleResult(res);
    else
    {
        auto err = res.error();
        std::cout << "HTTP GET error: " << httplib::to_string(err) << '\n';
    }
}

void httpGetSync(const std::string& scheme, const std::string& path, const httplib::Headers& headers,
                 std::function<handleHTTPResultFunc> handleResult)
{
    httplib::Client cli(scheme);
    cli.set_connection_timeout(0, 300000);
    if (auto res = cli.Get(path))
        handleResult(res);
    else
    {
        auto err = res.error();
        std::cout << "HTTP GET error: " << httplib::to_string(err) << '\n';
    }
}

void httpGet(const std::string& scheme, const std::string& path, const std::function<handleHTTPResultFunc>& handleResult)
{
    // We need to cast this to a specific type because std::thread doesn't like being passed overloaded functions.
    void(*getFunc)(const std::string& scheme, const std::string& path,
                   std::function<handleHTTPResultFunc> handleResult) = httpGetSync;
    std::thread httpGetThread(getFunc, scheme, path, handleResult);
    httpGetThread.detach();
}

void httpGet(const std::string& scheme, const std::string& path, const httplib::Headers& headers,
             const std::function<handleHTTPResultFunc>& handleResult)
{
    void(*getFunc)(const std::string& scheme, const std::string& path, const httplib::Headers& headers,
                   std::function<handleHTTPResultFunc> handleResult) = httpGetSync;
    std::thread httpGetThread(getFunc, scheme, path, headers, handleResult);
    httpGetThread.detach();
}

void httpPostSync(const std::string& scheme, const std::string& path, const std::string& body,
                  const std::string& contentType, std::function<handleHTTPResultFunc> handleResult)
{
    httplib::Client cli(scheme);
    cli.set_connection_timeout(0, 300000);
    httplib::Headers headers;
    if (auto res = cli.Post(path, headers, body, contentType))
        handleResult(res);
    else
    {
        auto err = res.error();
        std::cout << "HTTP POST error: " << httplib::to_string(err) << '\n';
    }
}

void httpPostSync(const std::string& scheme, const std::string& path, const httplib::Headers& headers, const std::string& body,
                  const std::string& contentType, std::function<handleHTTPResultFunc> handleResult)
{
    httplib::Client cli(scheme);
    cli.set_connection_timeout(0, 300000);
    if (auto res = cli.Post(path, headers, body, contentType))
        handleResult(res);
    else
    {
        auto err = res.error();
        std::cout << "HTTP POST error: " << httplib::to_string(err) << '\n';
    }
}

void httpPost(const std::string& scheme, const std::string& path, const std::string& body,
              const std::string& contentType, const std::function<handleHTTPResultFunc>& handleResult)
{
    void(*postFunc)(const std::string& scheme, const std::string& path, const std::string& body,
                    const std::string& contentType, std::function<handleHTTPResultFunc> handleResult) = httpPostSync;
    std::thread httpPostThread(postFunc, scheme, path, body, contentType, handleResult);
    httpPostThread.detach();
}

void httpPost(const std::string& scheme, const std::string& path, const httplib::Headers& headers, const std::string& body,
              const std::string& contentType, const std::function<handleHTTPResultFunc>& handleResult)
{
    void(*postFunc)(const std::string& scheme, const std::string& path, const httplib::Headers& headers, const std::string& body,
                    const std::string& contentType, std::function<handleHTTPResultFunc> handleResult) = httpPostSync;
    std::thread httpPostThread(postFunc, scheme, path, headers, body, contentType, handleResult);
    httpPostThread.detach();
}

void logToFile(std::string_view filepath, std::string_view message)
{
    const std::filesystem::path origPath = std::filesystem::current_path();
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    std::filesystem::path path;
    if (count != -1)
        path = dirname(result);
    else
        throw std::runtime_error("readlink() indicated error");
    std::string_view dirPath;
    std::string name;
    std::size_t lastSlash = filepath.find_last_of("/");
    if (lastSlash != std::string::npos)
    {
        dirPath = filepath.substr(0, lastSlash + 1);
        name = filepath.substr(lastSlash + 1, std::string::npos);
    }
    else
        name = filepath;
    path /= "logs";
    path /= dirPath;
    std::filesystem::current_path(path);
    std::ofstream log(name, std::ofstream::app);
    std::cout << message << std::endl;
    log << message << '\n';
    log.close();
    std::filesystem::current_path(origPath);
}

void logToFileDate(std::string_view filename, std::string_view message)
{
    logToFile(filename, format("[{}] {}", getDate(), message));
}

void logToFileTime(std::string_view filename, std::string_view message)
{
    logToFile(filename, format("[{}] {}", getTime(), message));
}

void logToFileDateTime(std::string_view filename, std::string_view message)
{
    logToFile(filename, format("[{}] {}", getDateTime(), message));
}

void adminLog(std::string_view message)
{
    logToFileDate("adminLog.txt", message);
}

Player* findPlayerByPhone(int phoneNumber)
{
    for (int i = 0; i < MAX_NUM_OF_PLAYERS; i++)
    {
        if (!Engine::players[i].isActive) continue;
        if (Engine::players[i].phoneNumber == phoneNumber)
            return &Engine::players[i];
    }
    return nullptr;
}

Account* findAccountByPhone(int phoneNumber)
{
    for (int i = 0; i < MAX_NUM_OF_ACCOUNTS; i++)
    {
        if (Engine::accounts[i].phoneNumber == 0) continue;
        if (Engine::accounts[i].phoneNumber == phoneNumber)
            return &Engine::accounts[i];
    }
    return nullptr;
}

// Technically this is the formula for pitch (rotation about the x-axis).
// However, Alex Austin's rotation axes are all Gosh-Darn Goofed Up.
RotMatrix yawToRotMatrix(float yaw)
{
    float s = sin(yaw);
    float c = cos(yaw);

    return RotMatrix{c, 0, s,
                     0, 1, 0,
                    -s, 0, c};
}

// This is technically roll.
RotMatrix pitchToRotMatrix(float pitch)
{
    float s = sin(pitch);
    float c = cos(pitch);
    
    return RotMatrix{1, 0, 0,
                     0, c,-s,
                     0, s, c};
}

// This is technically yaw.
RotMatrix rollToRotMatrix(float roll)
{
    float s = sin(roll);
    float c = cos(roll);

    return RotMatrix{c,-s, 0,
                     s, c, 0,
                     0, 0, 1};
}

RotMatrix axisAngleToRotMatrix(Vector axis, float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    float C = 1 - c;

    float x = axis.x;
    float y = axis.y;
    float z = axis.z;

    return RotMatrix{x*x*C + c, x*y*C - z*s, x*z*C + y*s,
                     y*x*C + z*s, y*y*C + c, y*z*C - x*s,
                     z*x*C - y*s, z*y*C + x*s, z*z*C + c};
}

RotMatrix pointTowards(Vector pos, Vector targetPos)
{
    float x = targetPos.x - pos.x;
    float y = targetPos.y - pos.y;
    float z = targetPos.z - pos.z;
    float d = sqrtf(x*x + z*z);

    float pitch = -atan2(y, d);
    float angle = M_PI - atan2(x, z);

    return pitchToRotMatrix(pitch) * axisAngleToRotMatrix(Y_AXIS, angle);
}

const RotMatrix NORTH = yawToRotMatrix(0.0f);
const RotMatrix NORTHEAST = yawToRotMatrix(M_PI / 4);
const RotMatrix EAST = yawToRotMatrix(M_PI / 2);
const RotMatrix SOUTHEAST = yawToRotMatrix(M_PI * 3 / 4);
const RotMatrix SOUTH = yawToRotMatrix(M_PI);
const RotMatrix SOUTHWEST = yawToRotMatrix(M_PI * 5 / 4);
const RotMatrix WEST = yawToRotMatrix(M_PI * 3 / 2);
const RotMatrix NORTHWEST = yawToRotMatrix(M_PI * 7 / 4);

std::pair<float, float> getCirclePoint(float radius, float angle)
{
    return std::pair{cos(angle) * radius, sin(angle) * radius};
}

std::vector<std::pair<float, float>> getCirclePoints(float radius, int numPoints)
{
    numPoints = std::max(numPoints, 1);
    std::vector<std::pair<float, float>> points;
    for (int i = 0; i < numPoints; i++)
    {
        float angle = i / numPoints * M_PI * 2;
        points.push_back(getCirclePoint(radius, angle));
    }
    return points;
}

std::vector<std::pair<float, float>> getCirclePoints(float radius, int numPoints, float angleOffset)
{
    numPoints = std::max(numPoints, 1);
    std::vector<std::pair<float, float>> points;
    for (int i = 0; i < numPoints; i++)
    {
        float angle = i / numPoints * M_PI * 2 + angleOffset;
        points.push_back(getCirclePoint(radius, angle));
    }
    return points;
}

int randomInt(int lower, int upper)
{
    return lower + (rand() % (upper - lower));
}

float randomFloat(float lower, float upper)
{
    return lower + (float)rand() * (upper - lower) / (float)RAND_MAX;
}

bool isVectorInCuboid(Vector pos, Vector cornerA, Vector cornerB)
{
    return (pos.x >= cornerA.x && pos.y >= cornerA.y && pos.z >= cornerA.z 
            && pos.x <= cornerB.x && pos.y <= cornerB.y && pos.z <= cornerB.z);
}

Vector vecRandBetween(Vector cornerA, Vector cornerB)
{
    float x = randomFloat(cornerA.x, cornerB.x);
    float y = randomFloat(cornerA.y, cornerB.y);
    float z = randomFloat(cornerA.z, cornerB.z);

    return Vector{x, y, z};
}

std::string dashPhoneNumber(int phoneNumber)
{
    return std::to_string(phoneNumber).insert(3, "-");
}

int undashPhoneNumber(std::string phoneNumber)
{
    // Can't combine this into one line because .erase() returns an iterator in this case (I think?).
    phoneNumber.erase(phoneNumber.begin() + 3);
    return std::stoi(phoneNumber);
}
