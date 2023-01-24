/* @author AOL
 * @brief  Permanently bans certain players through both ID and IP bans.
*/
#include "../inc/util.hpp"

static std::vector<int> awaitConnectedIndices;

static const std::vector<int> PERMABANNED = {

};

static const std::vector<std::string> PERMABANNED_IPS = {

};

// ID banning
static PostHook PostAccountTicketHook(
    &AccountTicket,
    [](int accountID, int identifier, unsigned int ticket)
    {
        if (accountID < 0) return;
        int phoneNumber = Engine::accounts[accountID].phoneNumber;
        for (int bannedNumber : PERMABANNED)
            if (phoneNumber == bannedNumber)
                Engine::accounts[accountID].banTime = 999999999;
    },
    -127
);

// IP banning
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
        for (int i = 0; i < awaitConnectedIndices.size(); i++)
        {
            if (awaitConnectedIndices[i] == ID)
            {
                awaitConnectedIndices.erase(awaitConnectedIndices.begin() + i);
                return;
            }
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
            else
            {
                Connection* con = ply->getConnection();
                if (con != nullptr)
                {
                    awaitConnectedIndices.erase(awaitConnectedIndices.begin() + i);
                    std::string IP = con->getAddress();

                    for (std::string bannedIP : PERMABANNED_IPS)
                        if (!IP.compare(bannedIP))
                        {
                            Account* acc = ply->getAccount();
                            if (acc != nullptr)
                            {
                                acc->banTime = 999999999;
                                adminLog(format("{} banned permanently for matching IP {}", IP, bannedIP));
                                return HOOK_CONTINUE;
                            }
                        }
                }
            }
        }
        return HOOK_CONTINUE;
    }
);