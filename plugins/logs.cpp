/* @author AOL
 * @brief Logging useful things to the console and/or Discord. Based on a plugin by jdb.
 *        Webhook paths in logSettings.json should be formatted as "xxx/xxxxx"
*/
#include "../inc/util.hpp"

static std::vector<int> awaitConnectedIndices;

// The real max is 2000, but we need to allow room for extra formatting.
static const int MAX_DISCORD_LINE = 1950;
static const std::string WEBHOOK_HOST = "https://discord.com";
static std::string webhookPath = "/api/webhooks/";
static bool webhookEnabled = false;

static int cachedLinesTimer = 0;
static std::vector<std::string> cachedLines;

static std::string discordPostUsername;

static void log(std::string message)
{
    std::cout << message << '\n';
    logToFileTime("dailyLogs/" + getDate() + ".txt", message);
    if (webhookEnabled)
        cachedLines.push_back(message);
}

static void handleResult(httplib::Result& res)
{
    // status 200 is OK. status 204 is no content
    if (res->status != 200 && res->status != 204)
        std::cout << format("DISCORD LOGGING ERROR. CODE: {}", res->status) << '\n';
}

static HookOnce InitializeSettings(
    &Logic,
    []()
    {
        discordPostUsername = format("\"username\":\"{}\"", Engine::serverName);
        json settings = getJSONFromFile("logSettings.json");
        if (!settings["webhookPath"].is_null())
        {
            webhookEnabled = true;
            webhookPath += clearChar(settings["webhookPath"].dump(), '\"');
        }
        return HOOK_CONTINUE;
    }
);

static PostHook PostCreatePlayerHook(
    &CreatePlayer,
    [](int ID)
    {
        if (!webhookEnabled) return;
        awaitConnectedIndices.push_back(ID);
    }
);

static PostHook PostDeletePlayerHook(
    &DeletePlayer,
    [](int ID)
    {
        if (!webhookEnabled) return;
        for (int i = awaitConnectedIndices.size() - 1; i > -1; i--)
        {
            if (awaitConnectedIndices[i] == ID)
            {
                awaitConnectedIndices.erase(awaitConnectedIndices.begin() + i);
                break;
            }
        }
        Player* ply = &Engine::players[ID];
        if (!ply->isBot) log(format("[Exit] {} ({})", ply->name, dashPhoneNumber(ply->phoneNumber)));
    }
);

static Hook EventMessageHook(
    &EventMessage,
    [](int &type, char* &message, int &speakerID, int &distance)
    {
        if (!webhookEnabled || speakerID == -1) return HOOK_CONTINUE;
        
        Player* ply;
        Human* man;

        if (type == 0)
            ply = &Engine::players[speakerID];
        else if (type == 1)
        {
            man = &Engine::humans[speakerID];
            ply = man->getPlayer();
        }
        else return HOOK_CONTINUE;

        if (ply == nullptr || ply->isBot) return HOOK_CONTINUE;

        if (type == 1)
            log(format("[Chat][{}] {} ({}): {}", DISTANCE_NAMES[distance], ply->name, dashPhoneNumber(ply->phoneNumber), message));
        else if (type == 0)
            log(format("[Chat][X] {} ({}): {}", ply->name, dashPhoneNumber(ply->phoneNumber), message));
        return HOOK_CONTINUE;
    }
);

static Hook LogicHook(
    &Logic,
    []()
    {
        if (!webhookEnabled) return HOOK_CONTINUE;
        for (int i = awaitConnectedIndices.size() - 1; i > -1; i--)
        {
            int index = awaitConnectedIndices[i];
            Player* ply = &Engine::players[index];
            if (ply->isBot)
                awaitConnectedIndices.erase(awaitConnectedIndices.begin() + i);
            else
            {
                Connection* con = ply->getConnection();
                if (con != nullptr)
                {
                    awaitConnectedIndices.erase(awaitConnectedIndices.begin() + i);
                    log(format("[Join] {} ({}) from {}", ply->name, dashPhoneNumber(ply->phoneNumber), addressFromInteger(con->address)));
                }
            }
        }

        cachedLinesTimer++;
        if (cachedLines.size() > 0 && cachedLinesTimer > 10 * SERVER_TPS)
        {
            cachedLinesTimer = 0;

            std::string postLine;
            while (cachedLines.size() > 0)
            {
                std::string line = cachedLines[0] + "\\n";

                std::string newPostLine = postLine + line;
                if (newPostLine.length() > MAX_DISCORD_LINE)
                {
                    if (cachedLines.size() == 1)
                        cachedLines.clear();
                    break;
                }

                postLine = newPostLine;
                cachedLines.erase(cachedLines.begin() + 0);
            }

            if (webhookEnabled && postLine != "")
            {
                std::string jsonString = "{" + discordPostUsername + ",\"content\":\"```accesslog\\n" + postLine + "```\"}";
                httpPost(WEBHOOK_HOST, webhookPath, jsonString, "application/json", handleResult);
            }
        }
        else if (cachedLinesTimer > 10 * SERVER_TPS)
            cachedLinesTimer = 0;

        return HOOK_CONTINUE;
    }
);
