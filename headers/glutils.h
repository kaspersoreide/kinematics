#pragma once

#include <GL/glew.h>
#include <vector>

/* 
 *  Function that generates a VAO for the current bound vertex buffer.
 */
GLuint makeVertexArray(int sizes[], int numAttribs);

GLuint makeVertexArray(const std::vector<float> &vertices, int sizes[], int numAttribs);