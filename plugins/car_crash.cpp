/* @author AOL
 * @brief  Makes car crashes more realistic.
*/
#include "../inc/util.hpp"

static const char CRASH_THRESH = 24;           // Damage threshold for crashes.
static const float BOUNCE_MULT = 0.005;        // How much bounce?
static const float LAUNCH_MULT = 0.3;          // How far are the humans launched?
static const float UP_VEL = 0.1;               // How much bounce on the humans?

static Hook VehicleDamageHook(
    &VehicleDamage,
    [](int &vehicleID, int &damage)
    {
        Vehicle* veh = &Engine::vehicles[vehicleID];
        if (damage >= CRASH_THRESH)
        {
            veh->steerControl = 0.0f;
            veh->getRigidBody()->vel.y += (float)damage * BOUNCE_MULT; // Bounces car. : )
            for (int i = 0; i < MAX_NUM_OF_HUMANS; i++)
            {
                // Finds the humans in the car that crashed and launches them from the car.
                Human* man = &Engine::humans[i];
                if (man->getVehicle() == nullptr) continue;
                if (man->getVehicle()->getIndex() == vehicleID)
                {
                    man->setVehicle(nullptr);
                    man->setVelocity(Vector{veh->getRigidBody()->vel.x*LAUNCH_MULT, UP_VEL, veh->getRigidBody()->vel.z*LAUNCH_MULT});
                }
            }
            for (int i = 0; i < 8; i++)
            {
                if (!veh->getIsWindowBroken(i))
                {
                    veh->setIsWindowBroken(i, true);
                    veh->updateDestruction(0, i, &veh->getRigidBody()->pos, &veh->getRigidBody()->vel);
                }
            }
        }
        return HOOK_CONTINUE;
    }
);
