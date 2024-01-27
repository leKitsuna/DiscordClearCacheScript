#include <iostream>
#include <filesystem>
#include <windows.h>
#include <psapi.h>
using namespace std;
using namespace filesystem;

const char *usernamechar = getenv("USERNAME");

bool IsProcessRunning(const char* processName) {
    DWORD processes[1024], bytesReturned;
    if (!EnumProcesses(processes, sizeof(processes), &bytesReturned)) {
        return false;
    }
    DWORD numProcesses = bytesReturned / sizeof(DWORD);
    for (DWORD i = 0; i < numProcesses; ++i) {
        if (processes[i] != 0) {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);
            if (hProcess != NULL) {
                HMODULE hMod;
                DWORD bytesNeeded;
                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &bytesNeeded)) {
                    TCHAR szModName[MAX_PATH];
                    if (GetModuleBaseName(hProcess, hMod, szModName, sizeof(szModName))) {
                        if (_stricmp(szModName, processName) == 0) {
                            return true;
                        }
                    }
                }
            }
            CloseHandle(hProcess);
        }
    }
    return false;
}

int main() {
    string username;
    const char *process = "Discord.exe";
    if (usernamechar != nullptr) {
        username = usernamechar;
    } else {
        abort();
    }
    path codecache = "C:/Users/" + username + "/AppData/Roaming/discord/Code Cache";
    path cache = "C:/Users/" + username + "/AppData/Roaming/discord/Cache";
    path gpucache = "C:/Users/" + username + "/AppData/Roaming/discord/GPUCache";
    if (IsProcessRunning(process)) {
        system("taskkill /im Discord.exe /f /t");
    }
    try {
        remove_all(codecache);
        remove_all(cache);
        remove_all(gpucache);
    } catch(const filesystem_error& e) {
        cerr << "An unexpected error has occured: " << e.what() << endl;
    }
    system("cls");
    cout << "Success!" << endl << "Press any key to open discord" << endl;
    cin.ignore();
    string discordPath = "C:/Users/" + username + "/AppData/Local/Discord/Update.exe --processStart Discord.exe";
    system(discordPath.c_str());
    return 0;
}
