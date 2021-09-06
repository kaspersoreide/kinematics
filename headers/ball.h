#pragma once

#include "object.h"

class Ball : public Object {
public:
    Ball() : Object() {}
    bool detectCollision(Ball& b);
    void collide(Ball& b);
    void render(const mat4& VP);

    static void Init();
    static GLuint vertexArray;
    static GLuint shader;
};