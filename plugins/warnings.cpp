/* @author AOL
 * @brief Displays warnings to previously banned players and allows admins to warn players without banning them.
*/
#include "../inc/util.hpp"

struct toWarn;

static const int SECONDS_PER_WARN = 60;
static const int DIVIDER_LENGTH = 48;
static const int INITIAL_WARN_TIME = 20;
static const int INITIAL_WARN_DIFF = SECONDS_PER_WARN - INITIAL_WARN_TIME;

static std::vector<int> awaitConnectedIndices;
static std::vector<toWarn> toWarnVec;
static json adminPersistence;

struct toWarn
{
    toWarn(int ID_in, double lastWarnTime_in)
    {
        ID = ID_in;
        lastWarnTime = lastWarnTime_in;
    }
    int ID;
    double lastWarnTime;
};

static void displayWarning(Player* ply, std::string when, std::string reason)
{
    if (ply == nullptr)
    {
        std::cout << "ERROR: nullptr passed into displayWarning." << '\n';
        return;
    }
    std::string divider(DIVIDER_LENGTH, '=');
    ply->sendMessage(divider);
    ply->sendMessageWrap("You have a warning from " + when + ":");
    ply->sendMessageWrap(reason);
    ply->sendMessage("Type /warned to acknowledge.");
    ply->sendMessage(divider);
}

static void loadDatabase()
{
    adminPersistence = getJSONFromFile("punishments.json");
    if (adminPersistence["warnings"].is_null())
        adminPersistence["warnings"] = json{};
}

static HookOnce InitializeDatabase(
    &Logic,
    []()
    {
        loadDatabase();
        return HOOK_CONTINUE;
    }
);

static PostHook PostCreatePlayerHook(
    &CreatePlayer,
    [](int ID)
    {
        awaitConnectedIndices.push_back(ID);
    }
);

static PostHook PostDeletePlayerHook(
    &DeletePlayer,
    [](int ID)
    {
        for (int i = awaitConnectedIndices.size() - 1; i > -1; i--)
            if (awaitConnectedIndices[i] == ID)
            {
                awaitConnectedIndices.erase(awaitConnectedIndices.begin() + i);
                break;
            }
        for (int i = toWarnVec.size() - 1; i > -1; i--)
            if (toWarnVec[i].ID == ID)
            {
                toWarnVec.erase(toWarnVec.begin() + i);
                break;
            }
    }
);

static Hook LogicHook(
    &Logic,
    []()
    {
        for (int i = awaitConnectedIndices.size() - 1; i > -1; i--)
        {
            int index = awaitConnectedIndices[i];
            Player* ply = &Engine::players[index];
            if (ply->isBot)
                awaitConnectedIndices.erase(awaitConnectedIndices.begin() + i);
            else if (ply->getConnection() != nullptr)
            {
                loadDatabase();
                awaitConnectedIndices.erase(awaitConnectedIndices.begin() + i);
                std::string s_phoneNumber = std::to_string(ply->phoneNumber);
                bool hasWarningVector = !adminPersistence["warnings"][s_phoneNumber].is_null();
                bool isWarningVectorEmpty = true;
                if (hasWarningVector)
                    isWarningVectorEmpty = adminPersistence["warnings"][s_phoneNumber].size() == 0;
                if (hasWarningVector && !isWarningVectorEmpty)
                    toWarnVec.push_back(toWarn{index, getEpochTime() - INITIAL_WARN_DIFF});
            }
        }

        for (int i = 0; i < toWarnVec.size(); i++)
        {
            toWarn *p_toWarnInfo = &toWarnVec[i];
            double secondsSinceWarn = getEpochTime() - p_toWarnInfo->lastWarnTime;
            if (secondsSinceWarn > SECONDS_PER_WARN)
            {
                Player* ply = &Engine::players[p_toWarnInfo->ID];
                std::string s_phoneNumber = std::to_string(ply->phoneNumber);
                bool hasWarningVector = !adminPersistence["warnings"][s_phoneNumber].is_null();
                bool isWarningVectorEmpty = true;
                if (hasWarningVector)
                    isWarningVectorEmpty = adminPersistence["warnings"][s_phoneNumber].size() == 0;
                if (!hasWarningVector || isWarningVectorEmpty)
                {
                    std::cout << "ERROR: Someone's in toWarnVec when they shouldn't be." << '\n';
                    continue;
                }

                std::string when = adminPersistence["warnings"][s_phoneNumber][0]["when"];
                std::string reason = adminPersistence["warnings"][s_phoneNumber][0]["reason"];

                displayWarning(ply, when, reason);
                p_toWarnInfo->lastWarnTime = getEpochTime();
            }
        }
        return HOOK_CONTINUE;
    }
);

Command warned(
    "/warned",
    [](Player* player, std::vector<std::string> args)
    {
        loadDatabase();

        std::string s_phoneNumber(std::to_string(player->phoneNumber));
        bool hasWarning = adminPersistence["warnings"][s_phoneNumber].size() > 0;

        if (!hasWarning)
        {
            player->sendMessage("Error: your account has no warnings.");
            return;
        }

        adminPersistence["warnings"][s_phoneNumber].erase(adminPersistence["warnings"][s_phoneNumber].begin() + 0);
        player->sendMessage("Warning cleared.");

        saveJSONToFile(adminPersistence, "punishments.json");

        if (adminPersistence["warnings"][s_phoneNumber].size() == 0)
            for (int i = 0; i < toWarnVec.size(); i++)
                if (toWarnVec[i].ID == player->getIndex())
                {
                    toWarnVec.erase(toWarnVec.begin() + i);
                    break;
                }
    }
);

Command warn(
    "/warn",
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

        int phoneNumber = std::stoi(s_phoneNumber);
        Account* targetAcc = findAccountByPhone(phoneNumber);
        if (targetAcc == nullptr)
        {
            player->sendMessage("Error: no such account found.");
            return;
        }

        targetAcc->warn(args[1]);
    },
    [](Player* player){ return player->isAdmin; }
);