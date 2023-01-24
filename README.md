# Tundra
Tundra is a C++ Sub Rosa server modding API for Linux. Thanks to RosaServer (https://github.com/RosaServer) and RosaLink for some of the code used in Tundra.

# Downloading Tundra And Required Packages
1. To download the required packages for Tundra, execute these commands:  
`sudo apt install build-essential` (if you're on Debian/Ubuntu)  
`sudo apt install cmake`  
`sudo apt install libssl-dev`  
2. To download the Tundra source code, execute `git clone --recurse-submodules https://github.com/AOL99/Tundra`.
3. To build Tundra, execute `cmake .`, then `make`. This will produce `tundra.so`.

# Configuration
Edit `persistence/logSettings.json` if you would like to add a Discord webhook for logs.
Example: if your link is `discord.com/api/webhooks/abc/defgh`, modify `persistence/logSettings.json` from `{"webhookPath":null}` to `{"webhookPath":"abc/defg"}`.

# Using Tundra
To start creating plugins with Tundra, see the example plugins included in the plugins directory.
After writing a plugin and including it in the plugins directory, include the path to the plugin (e.g. `plugins/example.cpp`) in `CMakeLists.txt` and rebuild the source code with `make`.
After building `tundra.so` with all of your plugins included in the build, add `tundra.so` to a directory that contains `subrosadedicated.x64`, the `data` folder, `config.txt`, (these three can be found in any Sub Rosa installation), the `logs` directory, the `persistence` directory, and the `start` script (these three are in the Tundra source code). Alternatively, you could place the necessary items from your Sub Rosa installation directly into the folder containing the Tundra source code. This is often the easier option. Once all files are in place, execute `./start` to boot up the server.

# Documentation
Documentation for Tundra is coming soon. For now, most of the features are in `inc/util.hpp`, `src/api.cpp`, and `inc/engine_structs.cpp`.
