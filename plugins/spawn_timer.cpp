/* @author AOL
 * @brief  Removes the spawn timer.
*/
#include "../inc/util.hpp"

static PostHook EventUpdatePlayerPostHook(
    &EventUpdatePlayer,
    [](int playerID)
    {
        Engine::players[playerID].spawnTime = 0;
    }
);