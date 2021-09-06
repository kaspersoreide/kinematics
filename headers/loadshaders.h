#include "GL/glew.h"
#include <iostream>
#include <fstream>

void loadShaderCodeFromFile(const char* file, GLuint shader);

void checkShaderError(GLuint shader, const char* name);

GLuint loadShaders(const char* vertex, const char* frag);

GLuint loadTFBShader(const char* vertex, const GLchar** varyings, int numVaryings);

GLuint loadGeometryShader(const char* vertex, const char* geo, const char* frag);

GLuint loadComputeShader(const char* compute);