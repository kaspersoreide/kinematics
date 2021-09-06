#version 430

in vec3 actualNormal;

out vec4 FragColor;

void main() {
    float shade = max(0.1, dot(actualNormal, vec3(1.0, 0.0, 0.0)));
    FragColor = shade * vec4(1.0, 1.0, 0.0, 1.0);
}