#pragma once
#include <random>
#include <glm/glm.hpp>

class RandomGenerator {
public:
    RandomGenerator();
    std::mt19937 mt;
    std::uniform_real_distribution<float> dist;
    float randf();
    float randf(float l, float h);
    glm::vec3 randvec3();
    glm::vec3 randvec3norm();
    glm::vec3 randvec3(float r);    //gives spherically distributed vec3 with max radius r
};

extern RandomGenerator *rng;