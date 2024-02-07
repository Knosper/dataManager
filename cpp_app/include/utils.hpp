#pragma once
#include <iostream>
#include <regex>
#include <imgui.h>
#include <string>
#include <sstream>


int CharFilterDatabaseName(ImGuiInputTextCallbackData* data);
int CharFilterDatabasePort(ImGuiInputTextCallbackData* data);
int CharFilterIpAddress(ImGuiInputTextCallbackData* data);
bool isValidIpAddress(const std::string& ip);
std::string longToIp(unsigned long val);
unsigned long ipToLong(const std::string& ip);
