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