/* @author AOL
 * @brief  Adds more useful ban messages. Based on a plugin by jdb.
*/
#include "../inc/util.hpp"

static PostHook PostAccountTicketHook(
    &AccountTicket,
    [](int accountID, int identifier, unsigned int ticket)
    {
        if (accountID < 0) return;
        int banTime = Engine::accounts[accountID].banTime;
        if (banTime > 0)
            HookOnce SendConnectResponse_HookOnce(
                &SendConnectResponse,
                [banTime](unsigned int &address, unsigned int &port, int &unk, char* &message)
                {
                    std::string newMessage;
                    // 100 years
                    if (banTime > 52596000)
                        newMessage = "You are permanently banned!";
                    else
                        newMessage = format("You are still banned for {}!", getCleanTime(banTime));
                    message = const_cast<char*>(newMessage.c_str());
                    return HOOK_CONTINUE;
                },
                -1
            );
    },
    -1
);