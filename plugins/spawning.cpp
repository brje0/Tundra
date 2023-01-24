/* @author AOL
 * @brief Commands for spawning.
*/
#include "../inc/util.hpp"

static const std::string DEFAULT_VEHICLETYPE = "Town Car";

Command item(
    "/item",
    [](Player* player, std::vector<std::string> args)
    {
        if (args.size() < 1)
        {
            player->sendMessage("Error: more arguments required.");
            return;
        }
        if (player->getHuman() == nullptr)
        {
            player->sendMessage("Error: not spawned in.");
            return;
        }

        bool isIndex = true;
        std::string s_type = args[0];
        std::string::const_iterator it = s_type.begin();
        while (it != s_type.end() && std::isdigit(*it)) ++it;
        if (s_type.empty() || it != s_type.end())
            isIndex = false;

        RigidBody* head = player->getHuman()->getRigidBody(3);
        Vector pos = head->pos + head->rot.getForward() * 2;
        pos.y = head->pos.y;

        if (isIndex)
        {
            int index = std::stoi(s_type);
            if (index >= MAX_NUM_OF_ITEMTYPES)
            {
                player->sendMessage("Error: invalid index.");
                return;
            }
            createItem(&Engine::itemTypes[std::stoi(s_type)], &pos);
            return;
        }

        ItemType* type = getItemTypeByName(s_type);
        if (type == nullptr)
        {
            player->sendMessage("Error: invalid type.");
            return;
        }
        
        createItem(type, &pos);
    },
    [](Player* player) { return player->isAdmin; }
);

Command car(
    "/car",
    [](Player* player, std::vector<std::string> args)
    {
        if (player->getHuman() == nullptr)
        {
            player->sendMessage("Error: not spawned in.");
            return;
        }

        Human* man = player->getHuman();
        RigidBody* head = man->getRigidBody(3);
        Vector pos = head->pos + head->rot.getForward() * 2;
        pos.y = head->pos.y;
        RotMatrix rot = yawToRotMatrix(man->viewYaw);

        Vehicle* veh;

        if (args.size() == 0)
        {
            veh = createVehicle(getVehicleTypeByName(DEFAULT_VEHICLETYPE), &pos, &rot);
            man->vehicleID = veh->getIndex();
            return;
        }

        VehicleType* type;

        bool isIndex = true;
        std::string s_type = args[0];
        std::string::const_iterator it = s_type.begin();
        while (it != s_type.end() && std::isdigit(*it)) ++it;
        if (s_type.empty() || it != s_type.end())
            isIndex = false;

        if (isIndex)
        {
            int index = std::stoi(s_type);
            if (index >= MAX_NUM_OF_VEHICLETYPES)
            {
                player->sendMessage("Error: invalid index.");
                return;
            }
            type = &Engine::vehicleTypes[index];
        }
        else
        {
            type = getVehicleTypeByName(s_type);
            if (type == nullptr)
            {
                if (args.size() == 1)
                {
                    // Maybe they're trying to specify a color?
                    char color = getVehicleColorByName(s_type);
                    if (color != -1)
                    {
                        veh = createVehicle(getVehicleTypeByName(DEFAULT_VEHICLETYPE), &pos, &rot, color);
                        man->vehicleID = veh->getIndex();
                        return;
                    }
                }
                player->sendMessage("Error: invalid type.");
                return;
            }
        }

        if (args.size() == 1)
        {
            veh = createVehicle(type, &pos, &rot);
            man->vehicleID = veh->getIndex();
            return;
        }

        isIndex = true;
        std::string s_color = args[1];
        it = s_color.begin();
        while (it != s_color.end() && std::isdigit(*it)) ++it;
        if (s_color.empty() || it != s_color.end())
            isIndex = false;

        if (isIndex)
        {
            veh = createVehicle(type, &pos, &rot, std::stoi(s_color));
            man->vehicleID = veh->getIndex();
            return;
        }

        int color = getVehicleColorByName(s_color);
        if (color == -1)
        {
            player->sendMessage("Error: invalid color.");
            return;
        }

        veh = createVehicle(type, &pos, &rot, color);
        man->vehicleID = veh->getIndex();
    },
    [](Player* player){ return player->isAdmin; }
);