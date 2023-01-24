/* @author AOL
 * @brief  Provides moderation tools to admins.
*/
#include "../inc/util.hpp"

Command punish(
    "/punish",
    [](Player* player, std::vector<std::string> args)
    {
        if (args.size() < 2)
        {
            player->sendMessage("Error: more arguments required.");
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

        std::string s_count = args[1];
        it = s_count.begin();
        while (it != s_count.end() && std::isdigit(*it)) ++it;
        if (s_count.empty() || it != s_count.end())
        {
            if (args.size() == 2)
            {
                Account* targetAcc = findAccountByPhone(std::stoi(s_phoneNumber));
                if (targetAcc == nullptr)
                {
                    player->sendMessage("Error: no such account found.");
                    return;
                }
                targetAcc->punish(1, args[1], player->name);
                return;
            }
            player->sendMessage("Error: invalid count.");
            return;
        }

        std::string reason = args[2];
        int phoneNumber = std::stoi(s_phoneNumber);
        Account* targetAcc = findAccountByPhone(phoneNumber);
        if (targetAcc == nullptr)
        {
            player->sendMessage("Error: no such account found.");
            return;
        }

        int count = std::stoi(s_count);
        // punish() logs for us so no need to log.
        targetAcc->punish(count, reason, player->name);
    },
    [](Player* player){ return player->isAdmin; }
);

Command ban(
    "/ban",
    [](Player* player, std::vector<std::string> args)
    {
        if (args.size() < 3)
        {
            player->sendMessage("Error: more arguments required.");
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

        std::string s_minutes = args[1];
        it = s_minutes.begin();
        while (it != s_minutes.end() && std::isdigit(*it)) ++it;
        if (s_minutes.empty() || it != s_minutes.end())
        {
            player->sendMessage("Error: invalid number of minutes.");
            return;
        }

        std::string reason = args[2];
        int phoneNumber = std::stoi(s_phoneNumber);
        Account* targetAcc = findAccountByPhone(phoneNumber);
        if (false)
        {
            player->sendMessage("Error: no such account found.");
            return;
        }

        int minutes = std::stoi(s_minutes);
        targetAcc->ban(minutes, reason, player->name);
    },
    [](Player* player){ return player->isAdmin; }
);

Command addBan(
    "/addban",
    [](Player* player, std::vector<std::string> args)
    {
        if (args.size() < 3)
        {
            player->sendMessage("Error: more arguments required.");
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

        std::string s_minutes = args[1];
        it = s_minutes.begin();
        while (it != s_minutes.end() && std::isdigit(*it)) ++it;
        if (s_minutes.empty() || it != s_minutes.end())
        {
            player->sendMessage("Error: invalid number of minutes.");
            return;
        }

        std::string reason = args[2];
        int phoneNumber = std::stoi(s_phoneNumber);
        Account* targetAcc = findAccountByPhone(phoneNumber);
        if (targetAcc == nullptr)
        {
            player->sendMessage("Error: no such account found.");
            return;
        }

        int minutes = std::stoi(s_minutes);
        targetAcc->addBan(minutes, reason, player->name);
    },
    [](Player* player){ return player->isAdmin; }
);