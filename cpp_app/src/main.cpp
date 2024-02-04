#include "Gui.hpp"
#include "Macros.hpp"

int main()
{
    Macros params;

    /*if (params.getDatabaseConnection())
    {
        std::cout << "Connection established!" << std::endl;
    } else {
        std::cout << "No connection to the database!" << std::endl;
    }*/
    if (appGui(params))
    {
        std::cout << "Error main.cpp!" << std::endl;
        return (EXIT_FAILURE);
    }
    return (0);
}
