#pragma once
#include "GL/glew.h"
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include "glm/glm.hpp"
#include <vector>

using namespace std;

GLuint loadObject(string path);

GLuint loadObjectNormalized(string path);

GLuint loadObjectNoNormals(string path);