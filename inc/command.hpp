#pragma once

#include <string>
#include <vector>
#include <functional>

#include "engine.hpp"
#include "engine_structs.hpp"
#include "hook.hpp"
#include "util.hpp"

typedef bool(canCallFunc)(Player* player);
typedef void(commandFunc)(Player* player, std::vector<std::string> args);

extern std::vector<std::function<canCallFunc>> canCallFunctions;
extern std::vector<std::function<commandFunc>> commandFunctions;
extern std::vector<std::string> commands;

extern std::function<canCallFunc> defaultCanCall;

class Command
{
public:
    Command(std::string command, std::function<commandFunc> commandFunc)
    {
        canCallFunctions.push_back(defaultCanCall);
        commandFunctions.push_back(commandFunc);
        commands.push_back(command);
    }
    Command(std::string command, std::function<commandFunc> commandFunc, std::function<canCallFunc> canCallFunc)
    {
        canCallFunctions.push_back(canCallFunc);
        commandFunctions.push_back(commandFunc);
        commands.push_back(command);
    }
};