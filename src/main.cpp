#include <unistd.h>
#include <ctime>
#include <fstream>
#include <string>
#include <thread>

#include "../inc/tundra.hpp"

// Return type should be char* so that pointer arithmetic can be done without errors.
// Credit to RosaLink for this.
char* GetBaseAddress()
{
    std::ifstream file("/proc/self/maps");
    std::string line;
    std::getline(file, line);
    std::size_t pos = line.find("-");
    std::string truncated = line.substr(0, pos);

    return (char*)std::stoul(truncated, nullptr, 16);
}


static void Attach()
{
    printf("Tundra attach thread running\n");
    printf("main.cpp compiled at %s %s\n", __DATE__, __TIME__);

    char* base = GetBaseAddress();
    printf("subrosadedicated base address %p\n", (void*)base);

    InitializeTundra(base);
}

int __attribute__((constructor)) Entry()
{
    std::thread mainThread(Attach);
    mainThread.detach();

    return 0;
}
