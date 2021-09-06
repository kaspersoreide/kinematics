#include "ball.h"
#include "loadshaders.h"
#include "loadOBJ.h"

GLuint Ball::vertexArray;
GLuint Ball::shader;

void Ball::Init() {
    shader = loadShaders("shaders/ball/vert.glsl", "shaders/ball/frag.glsl");
    vertexArray = loadObject("objects/icosahedron.obj");
}

bool Ball::detectCollision(Ball& b) {
	return (length(pos - b.pos) < size + b.size);
}

void Ball::collide(Ball& b) {
	if (!detectCollision(b)) return;
	pos -= vel;
	b.pos -= b.vel;

	vec3 poc = pos + size * (b.pos - pos) / length(b.pos - pos);
	vec3 r1 = poc - pos;
	vec3 r2 = poc - b.pos;
	vec3 totalVelThis = vel + cross(spin, r1);
	vec3 totalVelThat = b.vel + cross(b.spin, r2);
	vec3 dv = totalVelThat - totalVelThis;
	if (dot(r1, dv) > 0) return;

	float m1 = 2 * b.size / (size + b.size);
	float m2 = 2 * size / (size + b.size);
	totalVelThis += m1 * dv;
	totalVelThat -= m2 * dv;

	float dp1 = dot(totalVelThis, r1);
	vel = dp1 * r1 / dot(r1, r1);
	float dp2 = dot(totalVelThat, r2);
	b.vel = dp2 * r2 / dot(r2, r2);

	vec3 tangentThis = totalVelThis - vel;
	setSpin(cross(tangentThis, r1) / dot(r1, r1));
	vec3 tangentThat = totalVelThat - b.vel;
	b.setSpin(cross(tangentThat, r2) / dot(r2, r2));
}


void Ball::render(const mat4& VP) {
    glUseProgram(shader);
    glBindVertexArray(vertexArray);
    glUniformMatrix4fv(glGetUniformLocation(shader, "Model"), 1, GL_FALSE, &Model[0][0]);
    mat4 MVP = VP * Model;
    glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glDrawArrays(GL_TRIANGLES, 0, 3 * 20);
}
