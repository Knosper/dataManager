//main.cpp
#include "Data.hpp"
#include <cstdlib>

class TerminalSettingsManager {
public:
    TerminalSettingsManager() {
        // Save current terminal settings
        system("stty -g > tty_settings.sav");
    }

    ~TerminalSettingsManager() {
        // Restore terminal settings
        system("stty $(cat tty_settings.sav)");
        // Optionally, delete the temporary file
        system("rm tty_settings.sav");
    }
};

int main()
{
    Data params;
    TerminalSettingsManager tsm;
    params._cpuCores = std::thread::hardware_concurrency();
    if (params.initGui())
    {
        std::cout << "Error main.cpp!" << std::endl;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
