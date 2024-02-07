#include "utils.hpp"

int CharFilterDatabaseName(ImGuiInputTextCallbackData* data)
{
    if (isalnum((unsigned char)data->EventChar) || (data->EventChar == '_'))
    {
        if (data->EventChar > 128)
        {
            return 1;
        }
        return 0;
    }
    return 1;
}

int CharFilterDatabasePort(ImGuiInputTextCallbackData* data)
{
    if (isdigit((unsigned char)data->EventChar))
    {
        return 0;
    }
    return 1;
}

bool isValidIpAddress(const std::string& ip) {
    std::regex ipPattern(
        "^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}"
        "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    return std::regex_match(ip, ipPattern);
}

int CharFilterIpAddress(ImGuiInputTextCallbackData* data)
{
    if (isdigit((unsigned char)data->EventChar) || (data->EventChar == '.'))
    {
        return 0; // Allow the character
    }
    
    return 1; // Block the character
}

unsigned long ipToLong(const std::string& ip)
{
    unsigned long val = 0;
    std::stringstream ss(ip);
    std::string part;
    while (std::getline(ss, part, '.')) {
        val = val * 256 + std::stoi(part);
    }
    return val;
}

std::string longToIp(unsigned long val)
{
    std::stringstream ss;
    ss << ((val >> 24) & 0xFF) << '.';
    ss << ((val >> 16) & 0xFF) << '.';
    ss << ((val >> 8) & 0xFF) << '.';
    ss << (val & 0xFF);
    return ss.str();
}
