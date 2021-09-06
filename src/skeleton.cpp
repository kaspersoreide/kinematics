#include "skeleton.h"
#include "rng.h"

Skeleton::Skeleton() {
    for (int i = 0; i < 10; i++) {
        vec3 p((float)i, rng->randf(-0.1f, 0.1f), 0.0f);
        joints.push_back(new Joint(p));
        if (i > 0) {
            float d = length(joints[i]->pos - joints[i-1]->pos);
            bones.push_back(new Bone(joints[i], joints[i-1], d));
        }
    }
    joints[0]->locked = true;
    /*
    joints.push_back(Joint(vec3(0.0f)));
    joints[0].locked = true;
    joints.push_back(Joint(vec3(0.0f, 3.0f, 2.0f)));
    joints.push_back(Joint(vec3(1.0f, 3.0f, 1.0f)));

    bones.push_back(Bone(&joints[0], &joints[1], 5.0f));
    bones.push_back(Bone(&joints[1], &joints[2], sqrt(2.0f)));
    */
}

Skeleton::Joint::Joint(vec3 _pos) {
    pos = prevPos = _pos;
    b = new Ball();
    b->pos = pos;
    locked = false;
}

void Skeleton::render(const mat4& VP) {
    for (Joint* j : joints) {
        j->b->render(VP);
    }
}

void Skeleton::move() {
    for (Joint* j : joints) {
        if (j->locked) continue;
        vec3 tmp = j->pos;
        j->pos += j->pos - j->prevPos;
        j->pos += vec3(0.0f, 0.0f, -0.0001f);
        j->prevPos = tmp;
    }
    
    for (int i = 0; i < 3; i++) {
        for (Bone* bone : bones) {
            vec3 center = 0.5f * (bone->a->pos + bone->b->pos);
            vec3 dir = normalize(bone->b->pos - bone->a->pos);
            if (!bone->a->locked) {
                bone->a->pos = center - dir * 0.5f * bone->l;
            }
            if (!bone->b->locked) {
                bone->b->pos = center + dir * 0.5f * bone->l;
            }
        }
    }
    for (Joint* j : joints) {
        //j.b->vel *= 0.99f;
        //j.b->vel += 0.01f * (j.pos - j.b->pos);
        j->b->pos = j->pos;
        j->b->move();
    }
}