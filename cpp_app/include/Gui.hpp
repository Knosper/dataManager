#pragma once
//#define GLEW_STATIC // Only define this if you are statically linking GLEW
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Macros.hpp"

GLuint loadImage(const char* imagePath, GLFWwindow* window);
void showDatabaseConfigWindow(Macros& params);
int appGui(Macros& params);