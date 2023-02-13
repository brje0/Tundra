cmake_minimum_required(VERSION 3.8)

project(tundra)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

add_compile_definitions(
	SUBHOOK_SEPARATE_SOURCE_FILES
	SUBHOOK_IMPLEMENTATION
)

find_package (OpenSSL REQUIRED)

add_library(tundra SHARED
    src/api.cpp
    src/engine.cpp
    src/hooks.cpp
    src/main.cpp
    src/tundra.cpp
    src/util.cpp
    src/command.cpp

    plugins/ban_messages.cpp
    plugins/moderation.cpp
    plugins/no_stamina.cpp
    plugins/car_crash.cpp
    plugins/spawning.cpp
    plugins/teleportation.cpp
    plugins/fall_guys.cpp
    plugins/logs.cpp
    plugins/short_chat.cpp
    plugins/warnings.cpp
    plugins/permabans.cpp
    plugins/spawn_timer.cpp
    plugins/tps.cpp

    lib/subhook/subhook.c
    lib/subhook/subhook_unix.c
    lib/subhook/subhook_x86.c
)

target_link_libraries(tundra libssl.so)
target_link_libraries(tundra libcrypto.so)

# If you only include this third party in PRIVATE source files, you do not need to install it
# when your main project gets installed.
set(JSON_Install OFF CACHE INTERNAL "")

add_subdirectory(lib/json)

set_target_properties(tundra PROPERTIES PREFIX "")
set_target_properties(tundra PROPERTIES OUTPUT_NAME "tundra")
set_target_properties(tundra PROPERTIES SUFFIX ".so")
