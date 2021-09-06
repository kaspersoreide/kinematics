#include "rng.h"

RandomGenerator::RandomGenerator() {
    std::random_device rd;
    mt = std::mt19937(rd());
    dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
}

float RandomGenerator::randf() {
    return dist(mt);
}

float RandomGenerator::randf(float l, float h) {
    float r = h - l;
    return r * randf() + l;
}

glm::vec3 RandomGenerator::randvec3() {
    return glm::vec3(randf(), randf(), randf());
}

glm::vec3 RandomGenerator::randvec3norm() {
    glm::vec3 v(
        randf(-1.0f, 1.0f),
        randf(-1.0f, 1.0f),
        randf(-1.0f, 1.0f)
    );
    return glm::normalize(v);
}

glm::vec3 RandomGenerator::randvec3(float r) {
    return r * randf() * randvec3norm();
}