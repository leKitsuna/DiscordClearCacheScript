#include <iostream>
#include <filesystem>
using namespace std;
using namespace filesystem;

const char *usernamechar = getenv("USERNAME");

int main() {

    string username;

    if (usernamechar != nullptr) {
        username = usernamechar;
    } else {
        abort();
    }

    path codecache = "C:/Users/" + username + "/AppData/Roaming/discord/Code Cache";
    path cache = "C:/Users/" + username + "/AppData/Roaming/discord/Cache";
    path gpucache = "C:/Users/" + username + "/AppData/Roaming/discord/GPUCache";

    system("taskkill /im Discord.exe /f /t");

    try {
        remove_all(codecache);
        remove_all(cache);
        remove_all(gpucache);
    }
    catch(const filesystem_error& e) {
        cerr << "An unexpected error has occured: " << e.what() << endl;
    }

    string discordPath = "C:/Users/" + username + "/AppData/Local/Discord/Update.exe --processStart Discord.exe";

    system(discordPath.c_str());

    return 0;
}
