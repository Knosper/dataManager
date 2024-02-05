#pragma once
//#define GLEW_STATIC // Only define this if you are statically linking GLEW
#include "tData.hpp"

GLuint loadImage(const char* imagePath, GLFWwindow* window);
void showDatabaseConfigWindow(GLFWwindow* window, T_data& params);
int appGui(T_data& params);
