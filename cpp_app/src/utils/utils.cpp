//utils.cpp
#include "utils.hpp"

int CharFilterDatabasePort(ImGuiInputTextCallbackData* data)
{
    if (isdigit((unsigned char)data->EventChar))
    {
        return (false);
    }
    return (true);
}

int CharFilterIpAddress(ImGuiInputTextCallbackData* data)
{
    if (isdigit((unsigned char)data->EventChar) || (data->EventChar == '.'))
    {
        return (false); // Allow the character
    }
    return (true);
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

std::string longToIp(const unsigned long& val)
{
    std::stringstream ss;
    ss << ((val >> 24) & 0xFF) << '.';
    ss << ((val >> 16) & 0xFF) << '.';
    ss << ((val >> 8) & 0xFF) << '.';
    ss << (val & 0xFF);
    return ss.str();
}

bool isValidIpAddress(const char* ipAddress)
{
    int dots = 0;
    const char* ptr = ipAddress;

    if (ipAddress == nullptr) 
        return (false);

    while (*ptr)
    {
        if (*ptr == '.')
        {
            if (ptr == ipAddress) 
                return (false); // dot can't be at the beginning
            if (!isdigit(*(ptr-1))) 
                return (false); // dot follows a non-digit
            dots++;
        }
        else if (!isdigit(*ptr))
            return (false);
        ptr++;
    }
    if (dots != 3)
        return false; // an IP address must contain 3 dots
    // Re-checking each segment
    std::istringstream stream(ipAddress);
    std::string segment;
    while (std::getline(stream, segment, '.'))
    {
        if (segment.empty() || stoi(segment) > 255 || stoi(segment) < 0) return false;
    }
    return (true);
}