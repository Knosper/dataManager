#include "tData.hpp"

T_data::T_data():_backgroundTextureID(), _iconTextureIDs(), _window(), _io(), _status(false)
{
    std::cout << "default T_data created" << std::endl; 
}

T_data::~T_data()
{
    std::cout << "T_data deleted" << std::endl; 
}

void T_data::addIconTextureID(const std::string& name, GLuint textureID)
{
    _iconTextureIDs[name] = textureID;
}