#version 430

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

uniform mat4 MVP;
uniform mat4 Model;

out vec3 actualNormal;

void main() {
    gl_Position = MVP * vec4(pos, 1.0);
    actualNormal = (Model * vec4(normal, 0.0)).xyz;
}