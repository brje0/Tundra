/* @author AOL
 * @brief  Removes stamina.
*/
#include "../inc/util.hpp"

static Hook LogicHook(
    &Logic,
    [](){
        for (int i = 0; i < MAX_NUM_OF_HUMANS; i++)
        {
            if (!Engine::humans[i].isActive) continue;
            Engine::humans[i].stamina = 127;
            Engine::humans[i].maxStamina = 127;
        }
        return HOOK_CONTINUE;
    }
);