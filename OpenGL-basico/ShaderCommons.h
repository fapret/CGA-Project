#pragma once
#include <glad/glad.h>
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include <fstream>

GLuint initShaders(char* vertFile, char* fragFile, bool activate = true);

void printShaderError(GLint shader);

const char* loadFile(char* fname);