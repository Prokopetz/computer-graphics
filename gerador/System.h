#ifndef SYSTEM_H
#define SYSTEM_H

// Internal
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <math.h>
#include <vector>

// External Libs
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Headers
#include "model/Shader.h"
#include "Time.h"

using namespace std;

void to_obj();
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void update_bspline();
void update_bspline_in_ex();
float calculate_bspline_point(float &t, float &t_pow_3, float &t_pow_2, float &p1, float &p2, float &p3, float &p4);

class System
{
private:
	// Screen
	const int WIDTH = 600, HEIGHT = 600;
	int screenWidth, screenHeight;

public:
	GLFWwindow *window;
	Shader coreShader;

public:
	System();
	~System();

	int GLFWInit();
	int OpenGLSetup();
	int SystemSetup();

	void Run();

	void Finish();
};

#endif