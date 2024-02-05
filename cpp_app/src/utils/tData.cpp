#include "tData.hpp"

T_data::T_data():_backgroundTextureID(), _iconTextureID(), _window(), _status(false)
{
    std::cout << "default T_data created" << std::endl; 
}

T_data::~T_data()
{
    std::cout << "T_data deleted" << std::endl; 
}