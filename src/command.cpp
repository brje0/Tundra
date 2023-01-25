#include "../inc/command.hpp"

const std::string ACCESS_DENIED_MESSAGE = "Error: Access denied.";

std::vector<std::function<canCallFunc>> canCallFunctions;
std::vector<std::function<commandFunc>> commandFunctions;
std::vector<std::string> commands;

std::function<canCallFunc> defaultCanCall = [](Player* player){ return true; };

std::vector<std::string> processInput(const std::string& input)
{
    std::vector<std::string> args;
    std::string curArg = "";
    bool inQuote = false;
    for (char c : input)
    {
        if (c == ' ' && !inQuote)
        {
            args.push_back(curArg);
            curArg = "";
        }
        else if (c == '\"')
            inQuote = !inQuote;
        else
            curArg += c;
    }
    if (curArg != "")
        args.push_back(curArg);
    return args;
}

Hook command_PlayerMessage(
    &PlayerMessage,
    [](int &playerID, char* &message){
        // Convert char* to std::string
        std::string tmp(message);
        std::vector<std::string> args = processInput(tmp);
        Player* player = &Engine::players[playerID];
        for (int i = 0; i < commandFunctions.size(); i++)
        {
            // If the first word matches the command
            if (!args[0].compare(commands[i]))
            {
                if (!canCallFunctions[i](player))
                {
                    player->sendMessage(ACCESS_DENIED_MESSAGE);
                    return HOOK_OVERRIDE;
                }
                else
                {
                    // Removes the "/command" from the args vector. Don't remove the "+ 0", because 
                    // that makes this work somehow. Maybe it converts the argument from iterator to int?
                    args.erase(args.begin() + 0);
                    commandFunctions[i](player, args);
                    return HOOK_OVERRIDE;
                }
            }
        }
        return HOOK_CONTINUE;
    },
    -1
);