/* @author AOL
 * @brief Makes Guys not Fall.
*/
#include "../inc/util.hpp"

static Hook HLIKHook(
    &HumanLimbInverseKinematics,
    [](int &humanID, int &trunkBoneID, int &branchBoneID,
       Vector* &destination, RotMatrix* &destinationAxis,
       Vector* &vecA, float &a, float &rot,
       float &strength, float* &d,
       Vector* &vecB, Vector* &vecC, Vector* &vecD,
       char &flags)
    {
        Engine::humans[humanID].strengthDamage = 0;
        return HOOK_CONTINUE;
    },
    -1
);