#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS
#include <iostream>
#include <GL/glew.h>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <math.h>

#include "player.h"
#include "glutils.h"
#include "loadshaders.h"
#include "ball.h"
#include "rng.h"
#include "skeleton.h"

using namespace std;
using namespace glm;

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<float> fsec;

//resolution of window in pixels
int RESX = 1280;
int RESY = 720;

GLFWwindow* window;
bool closed = false, paused = false;
Player *player;
RandomGenerator *rng;
vec2 mouse;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_E) {
		if (action == GLFW_PRESS) player->rot[0] = true;
		if (action == GLFW_RELEASE) player->rot[0] = false;
	}
	if (key == GLFW_KEY_Q) {
		if (action == GLFW_PRESS) player->rot[1] = true;
		if (action == GLFW_RELEASE) player->rot[1] = false;
	}
	if (key == GLFW_KEY_LEFT) {
		if (action == GLFW_PRESS) player->rot[2] = true;
		if (action == GLFW_RELEASE) player->rot[2] = false;
	}
	if (key == GLFW_KEY_RIGHT) {
		if (action == GLFW_PRESS) player->rot[3] = true;
		if (action == GLFW_RELEASE) player->rot[3] = false;
	}
	if (key == GLFW_KEY_UP) {
		if (action == GLFW_PRESS) player->rot[4] = true;
		if (action == GLFW_RELEASE) player->rot[4] = false;
	}
	if (key == GLFW_KEY_DOWN) {
		if (action == GLFW_PRESS) player->rot[5] = true;
		if (action == GLFW_RELEASE) player->rot[5] = false;
	}

	if (key == GLFW_KEY_W) {
		if (action == GLFW_PRESS) player->mov[0] = true;
		if (action == GLFW_RELEASE) player->mov[0] = false;
	}
	if (key == GLFW_KEY_S) {
		if (action == GLFW_PRESS) player->mov[1] = true;
		if (action == GLFW_RELEASE) player->mov[1] = false;
	}
	if (key == GLFW_KEY_A) {
		if (action == GLFW_PRESS) player->mov[2] = true;
		if (action == GLFW_RELEASE) player->mov[2] = false;
	}
	if (key == GLFW_KEY_D) {
		if (action == GLFW_PRESS) player->mov[3] = true;
		if (action == GLFW_RELEASE) player->mov[3] = false;
	}
	if (key == GLFW_KEY_LEFT_SHIFT) {
		if (action == GLFW_PRESS) player->mov[4] = true;
		if (action == GLFW_RELEASE) player->mov[4] = false;
	}
	if (key == GLFW_KEY_LEFT_CONTROL) {
		if (action == GLFW_PRESS) player->mov[5] = true;
		if (action == GLFW_RELEASE) player->mov[5] = false;
	}
	if (key == GLFW_KEY_ESCAPE) {
		closed = true;
	}
	//if (key == GLFW_KEY_SPACE) {
	//	if (action == GLFW_PRESS) player->shooting = true;
	//	if (action == GLFW_RELEASE) player->shooting = false;
	//}
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
	//vec2 diff(xpos - mouse.x, ypos - mouse.y);
	//player->rotate(diff);
	//mouse = vec2(xpos, ypos);
	//player->rotate(mouse);
	//std::cout << "mouse x: " << xpos << ", y: " << ypos << "\n";
}

int init() {
	// Initialise GLFW
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(RESX, RESY, "Test", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// Initialize GLEW
	//glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	int error = glGetError();

	if (error != GL_NO_ERROR) {
		cout << "OpenGL error: " << error << "\n";
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

    rng = new RandomGenerator();

	return 0;
}

int main(void) {
	if (init() == -1) return -1;
    Ball::Init();
    player = new Player();
    player->pos = vec3(0.0f, 0.0f, 3.0f);
    mat4 Projection = perspective(1.2f, static_cast<float>(RESX) / RESY, 0.1f, 100.0f);
    mat4 VP;
    vector<Ball*> balls;
    Skeleton boo;
    for (int i = 0; i < 40; i++) {
        Ball *b = new Ball();
        b->pos = rng->randvec3(30.0f);
        balls.push_back(b);
    }   

    auto t0 = Time::now();
	while (!glfwWindowShouldClose(window) && !closed) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        auto t1 = Time::now();
		fsec t = t1 - t0;
        
        player->move();
        VP = Projection * player->getView();
        boo.move();
        boo.render(VP);

        /*
        for (Ball* b : balls) {
            b->move();
            b->render(VP);
        }*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}