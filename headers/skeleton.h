#pragma once

#include "ball.h"
#include <vector>

class Skeleton : public Object {
public:
    struct Joint {
        Ball* b;
        vec3 pos;   //ball will just try to move to pos (add small amount to vel)
        vec3 prevPos;
        bool locked;
        Joint(vec3 pos);
    };

    struct Bone {
        Bone(Joint *a, Joint *b, float l) : a(a), b(b), l(l) {}
        Joint *a, *b;
        float l;
    };

    Skeleton();
    void move();
    void render(const mat4& VP);

    std::vector<Bone*> bones;
    std::vector<Joint*> joints;
};