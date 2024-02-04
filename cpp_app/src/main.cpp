#include "Gui.hpp"
#include "Macros.hpp"

int main()
{
    Macros params;

    if (params._dataBaseConnection)
    {
        std::cout << "Connection established!" << std::endl;
        render_gui();
    } else {
        std::cout << "No connection to the database!" << std::endl;
    }
    return (0);
}
