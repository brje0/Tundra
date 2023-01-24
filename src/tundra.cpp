#include <cstdlib>
#include <time.h>

#include "../inc/engine.hpp"
#include "../inc/hooks.hpp"

void InitializeTundra(char* base)
{
    srand(time(0));
    Engine::InitializeEngine(base);
    InitializeHooks();
}