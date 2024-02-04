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
<<<<<<< HEAD
    if (appGui(params))
    {
        std::cout << "Error main.cpp!" << std::endl;
        return (EXIT_FAILURE);
    }
=======

    appGui();

>>>>>>> 3537d906568f46dfcb1b1be80b5e6dc1f349a199
    return (0);
}
