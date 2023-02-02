/* @author AOL
 * @brief  Adds teleportation commands for admins.
*/
#include "../inc/util.hpp"

Command find(
    "/find",
    [](Player* player, std::vector<std::string> args)
    {
        if (args.size() < 1)
        {
            player->sendMessage("Error: more arguments required.");
            return;
        }
        if (player->getHuman() == nullptr)
        {
            player->sendMessage("Error: you are not spawned in.");
            return;
        }

        std::string s_phoneNumber = args[0];
        std::string::const_iterator it = s_phoneNumber.begin();
        while (it != s_phoneNumber.end() && std::isdigit(*it)) ++it;
        if (s_phoneNumber.empty() || it != s_phoneNumber.end())
        {
            player->sendMessage("Error: invalid phone number.");
            return;
        }

        int phoneNumber = std::stoi(s_phoneNumber);
        Player* targetPly = findPlayerByPhone(phoneNumber);
        if (targetPly == nullptr)
        {
            player->sendMessage("Error: no such player found.");
            return;
        }
        Human* targetMan = targetPly->getHuman();
        if (targetMan == nullptr)
        {
            player->sendMessage("Error: player not spawned in.");
            return;
        }

        RigidBody* targetHead = targetPly->getHuman()->getRigidBody(3);
        Vector pos = targetMan->pos - targetHead->rot.getForward() * 2;
        pos.y = targetMan->pos.y;

        player->getHuman()->teleport(pos);
    },
    [](Player* ply){ return ply->isAdmin; }
);