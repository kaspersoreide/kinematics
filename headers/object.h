#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

using namespace glm;

class Object {
public:
	Object() {};
	Object(vec3 _pos);
	void move();
	mat4 getView() { return inverse(Model); }
    void setSpin(vec3 _spin);

	vec3 pos = vec3(0.0f);
	vec3 spin = vec3(0.0f);
	vec3 vel = vec3(0.0f);
	mat3 Spin = mat3(1.0f);
	mat3 Rotation = mat3(1.0f);
	mat4 Model = mat4(1.0f);
	mat4 Scale = mat4(1.0f);
    float size = 1.0f;
};