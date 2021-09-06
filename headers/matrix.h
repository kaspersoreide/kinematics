#pragma once
#include "glm/glm.hpp"
#include "GL/glew.h"

using namespace glm;

mat3 srotate(vec3 rot);

mat4 translateR(mat3 R, vec3 p);