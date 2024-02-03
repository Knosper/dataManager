#include <iostream>
#include <pqxx/pqxx>
#include <cstdlib>
#include <QApplication>
#include <QWidget>
#include <iostream>

// Function to get the value of an environment variable
const char* getEnvVar(const char* key, char* envp[])
{
    for (char **env = envp; *env != 0; env++) {
        if (strncmp(*env, key, strlen(key)) == 0) {
            return *env + strlen(key) + 1;  // Skip past 'key='
        }
    }
    return nullptr;
}

// Function to set an environment variable
void setEnvVar(const char* key, const char* value, int overwrite)
{
    if (value != nullptr) {
        setenv(key, value, overwrite);
    }
}

int main(int argc, char *argv[], char* envp[])
{
	for (char **env = envp; *env != 0; env++) {
        char *thisEnv = *env;
        std::cout << thisEnv << std::endl;  // prints each environment variable
    }
	const char* home = getEnvVar("HOME", envp);
    const char* user = getEnvVar("USER", envp);
    const char* display = getEnvVar("DISPLAY", envp);
    const char* xdg_runtime_dir = getEnvVar("XDG_RUNTIME_DIR", envp);

 	std::cout << "HOME=" << (home ? home : "Not found") << std::endl;
    std::cout << "USER=" << (user ? user : "Not found") << std::endl;
    std::cout << "DISPLAY=" << (display ? display : "Not found") << std::endl;
    std::cout << "XDG_RUNTIME_DIR=" << (xdg_runtime_dir ? xdg_runtime_dir : "Not found") << std::endl;

    // Set the necessary environment variables for Qt
    setEnvVar("HOME", home, 1);
    setEnvVar("User", user, 1);
    setEnvVar("DISPLAY", display, 1);
    setEnvVar("XDG_RUNTIME_DIR", xdg_runtime_dir, 1);

    QApplication app(argc, argv);

    // Create a QWidget, which will be our main window
    QWidget window;

    // Set some properties for the window
    window.resize(250, 150);
    window.setWindowTitle("Simple Qt Application");

    // Display the window
    window.show();

    // Start the Qt event loop
    return app.exec();
}
