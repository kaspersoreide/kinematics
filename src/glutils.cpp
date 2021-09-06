#include "glutils.h"

GLuint makeVertexArray(int sizes[], int numAttribs) {
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
    int stride = 0;
    for (int i = 0; i < numAttribs; i++) {
        stride += sizeof(float) * sizes[i];
    }
    int offset = 0;
    for (int i = 0; i < numAttribs; i++) {
        glEnableVertexAttribArray(i);
	    glVertexAttribPointer(
	    	i,
	    	sizes[i],
	    	GL_FLOAT,
	    	GL_FALSE,
	    	stride,
	    	(void*)(offset * sizeof(float))
	    );
        offset += sizes[i];
    }

	return VAO;
}

GLuint makeVertexArray(const std::vector<float> &vertices, int sizes[], int numAttribs) {
    GLuint vertexBuffer;
    
    glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    return makeVertexArray(sizes, numAttribs);
}