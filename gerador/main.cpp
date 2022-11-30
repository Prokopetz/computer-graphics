// Internal
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <math.h>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

// Headers
#include "model/Shader.h"

int initGLFW();
int openGLSetup();
int systemSetup();
void run();
void finish();
void writeMaterial();
void writeObj();
void toFile();
void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
void update_bspline();
void createBuffers();
void updateBsplineInOut();
float calculateBsplinePoint(float t, float t_pow_3, float t_pow_2, float p1, float p2, float p3, float p4);

int main()
{

	if (initGLFW() != 0)
	{
		return EXIT_FAILURE;
	}
	if (openGLSetup() != 0)
	{
		return EXIT_FAILURE;
	}
	if (systemSetup() != 0)
	{
		return EXIT_FAILURE;
	}

	run();

	return 0;
}

const int WIDTH = 600, HEIGHT = 600;
int screenWidth, screenHeight;

GLFWwindow *window;
Shader coreShader;

GLuint vaoControlPoints, vboControlPoints;
GLuint vaoBspline, vboBspline;
GLuint vaoBsplineIn, vboBsplineIn;
GLuint vaoBsplineOut, vboBsplineOut;

vector<float> controlPoints, bspline, bsplineIn, bsplineOut;
double xLastPos = 0, yLastPos = 0;

int initGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Gerador", nullptr, nullptr);

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed no init GLEW." << std::endl;
		return EXIT_FAILURE;
	}

	glViewport(0, 0, screenWidth, screenHeight);

	return EXIT_SUCCESS;
}

int openGLSetup()
{

	glEnable(GL_BLEND); // Enables blending ( glBlendFunc )
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	return EXIT_SUCCESS;
}

int systemSetup()
{
	coreShader = Shader("./gerador/Shaders/Core/vertex.shader", "./gerador/Shaders/Core/fragment.shader");
	coreShader.Use();

	glm::mat4 proj = glm::ortho(0.0f, 600.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	coreShader.setMatrix4fv("projection", proj);

	return EXIT_SUCCESS;
}

void createBuffers()
{
	glGenBuffers(1, &vboControlPoints);
	glGenVertexArrays(1, &vaoControlPoints);

	glGenBuffers(1, &vboBspline);
	glGenVertexArrays(1, &vaoBspline);

	glGenBuffers(1, &vboBsplineIn);
	glGenVertexArrays(1, &vaoBsplineIn);

	glGenBuffers(1, &vboBsplineOut);
	glGenVertexArrays(1, &vaoBsplineOut);

	glBindVertexArray(vaoControlPoints);
	glBindBuffer(GL_ARRAY_BUFFER, vboControlPoints);
	glBufferData(GL_ARRAY_BUFFER, controlPoints.size() * sizeof(float), controlPoints.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vaoBspline);
	glBindBuffer(GL_ARRAY_BUFFER, vboBspline);
	glBufferData(GL_ARRAY_BUFFER, bspline.size() * sizeof(float), bspline.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vaoBsplineIn);
	glBindBuffer(GL_ARRAY_BUFFER, vboBsplineIn);
	glBufferData(GL_ARRAY_BUFFER, bsplineIn.size() * sizeof(float), bsplineIn.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vaoBsplineOut);
	glBindBuffer(GL_ARRAY_BUFFER, vboBsplineOut);
	glBufferData(GL_ARRAY_BUFFER, bsplineOut.size() * sizeof(float), bsplineOut.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

void run()
{
	coreShader.Use();
	createBuffers();

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			toFile();
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		coreShader.Use();

		glBindVertexArray(vaoControlPoints);
		glPointSize(5);
		glDrawArrays(GL_POINTS, 0, (float)controlPoints.size() / 3);

		glBindVertexArray(vaoBspline);
		glDrawArrays(GL_LINE_STRIP, 0, (float)bspline.size() / 3);

		glBindVertexArray(vaoBsplineIn);
		glDrawArrays(GL_LINE_STRIP, 0, (float)bsplineIn.size() / 3);

		glBindVertexArray(vaoBsplineOut);
		glDrawArrays(GL_LINE_STRIP, 0, (float)bsplineOut.size() / 3);

		glfwSwapBuffers(window);
	}
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double x_current_pos, y_current_pos;
		glfwGetCursorPos(window, &x_current_pos, &y_current_pos);

		if (xLastPos == x_current_pos && yLastPos == y_current_pos)
		{
			// just to not repeat
			return;
		}

		xLastPos = x_current_pos;
		yLastPos = y_current_pos;

		controlPoints.push_back(x_current_pos);
		controlPoints.push_back(y_current_pos);
		controlPoints.push_back(0.0f);

		glBindVertexArray(vaoControlPoints);
		glBindBuffer(GL_ARRAY_BUFFER, vboControlPoints);
		glBufferData(GL_ARRAY_BUFFER, controlPoints.size() * sizeof(float), controlPoints.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		if (controlPoints.size() > 3)
		{
			update_bspline();
			updateBsplineInOut();
		}
	}
}

void update_bspline()
{
	bspline.clear();
	int size = controlPoints.size();

	for (int i = 0; i < size + 1; i += 3)
	{
		for (float k = 0; k < 1; k += 0.01f)
		{

			float kPow3 = pow(k, 3);
			float kPow2 = pow(k, 2);

			float x = calculateBsplinePoint(k, kPow3, kPow2,
																			controlPoints[(i + 0) % size],
																			controlPoints[(i + 3) % size],
																			controlPoints[(i + 6) % size],
																			controlPoints[(i + 9) % size]);

			float y = calculateBsplinePoint(k, kPow3, kPow2,
																			controlPoints[(i + 0 + 1) % size],
																			controlPoints[(i + 3 + 1) % size],
																			controlPoints[(i + 6 + 1) % size],
																			controlPoints[(i + 9 + 1) % size]);

			float z = 0;

			bspline.push_back(x);
			bspline.push_back(y);
			bspline.push_back(z);
		}
	}

	glBindVertexArray(vaoBspline);
	glBindBuffer(GL_ARRAY_BUFFER, vboBspline);
	glBufferData(GL_ARRAY_BUFFER, bspline.size() * sizeof(float), bspline.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

float calculateBsplinePoint(float k, float kPow3, float kPow2, float p1, float p2, float p3, float p4)
{
	return (
			(
					(-1 * kPow3 + 3 * kPow2 - 3 * k + 1) * p1 +
					(+3 * kPow3 - 6 * kPow2 + 0 * k + 4) * p2 +
					(-3 * kPow3 + 3 * kPow2 + 3 * k + 1) * p3 +
					(+1 * kPow3 + 0 * kPow2 + 0 * k + 0) * p4) /
			6.0f);
}

void updateBsplineInOut()
{
	bsplineOut.clear();
	bsplineIn.clear();
	int size = bspline.size();
	float CURVE_DISTANCE = 20.0f;

	for (int i = 0; i < size - 3; i += 3)
	{

		float Ax = bspline[(i + 0) % size];
		float Ay = bspline[(i + 1) % size];

		float Bx = bspline[(i + 3) % size];
		float By = bspline[(i + 4) % size];

		float Ac = bspline[(i + 2) % size];

		float w = Bx - Ax;
		float h = By - Ay;
		float a = atan(h / w);

		float internalAngle, externalAngle;

		if (w < 0)
		{
			internalAngle = a + M_PI / 2;
			externalAngle = a - M_PI / 2;
		}
		else
		{
			internalAngle = a - M_PI / 2;
			externalAngle = a + M_PI / 2;
		}

		float internalCx = cos(internalAngle) * CURVE_DISTANCE + Ax;
		float internalCy = sin(internalAngle) * CURVE_DISTANCE + Ay;

		bsplineIn.push_back(internalCx);
		bsplineIn.push_back(internalCy);
		bsplineIn.push_back(Ac);

		float externalCx = cos(externalAngle) * CURVE_DISTANCE + Ax;
		float externalCy = sin(externalAngle) * CURVE_DISTANCE + Ay;

		bsplineOut.push_back(externalCx);
		bsplineOut.push_back(externalCy);
		bsplineOut.push_back(Ac);
	}

	glBindVertexArray(vaoBsplineIn);
	glBindBuffer(GL_ARRAY_BUFFER, vboBsplineIn);
	glBufferData(GL_ARRAY_BUFFER, bsplineIn.size() * sizeof(float), bsplineIn.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(vaoBsplineOut);
	glBindBuffer(GL_ARRAY_BUFFER, vboBsplineOut);
	glBufferData(GL_ARRAY_BUFFER, bsplineOut.size() * sizeof(float), bsplineOut.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

void toFile()
{
	writeMaterial();
	writeObj();
}

void writeMaterial()
{
	ofstream material("./objects/pista.mtl");
	material << "newmtl "
					 << "pista" << endl;
	material << "Ka 1.0 1.0 1.0" << endl;
	material << "Kd 1.0 1.0 1.0" << endl;
	material << "Ks 1.0 1.0 1.0" << endl;
	material << "Ns 64.0" << endl;
	material << "map_Kd "
					 << "Objects/pista.jpg" << endl;
	material.close();
}

void writeObj()
{
	float scale = 0.05f;
	ofstream obj("./objects/pista.obj");
	obj << "mtllib "
			<< "Objects/pista.mtl" << endl;
	obj << "g "
			<< "pista" << endl;
	obj << "usemtl "
			<< "pista" << endl;

	obj << "vn 0.0 1.0 0.0" << endl;
	obj << "vt 0.0 0.0" << endl;
	obj << "vt 0.0 0.5" << endl;
	obj << "vt 0.5 0.0" << endl;
	obj << "vt 0.5 0.5" << endl;

	int size = bsplineIn.size();
	int numberOfVertices = size / 3;
	for (int i = 0; i < size; i += 3)
	{
		obj << "v " << (bsplineIn[i] * scale) << " " << bsplineIn[i + 2] * scale << " " << (bsplineIn[i + 1] * scale) << endl;
	}
	for (int i = 0; i < size; i += 3)
	{
		obj << "v " << (bsplineOut[i] * scale) << " " << bsplineOut[i + 2] * scale << " " << (bsplineOut[i + 1] * scale) << endl;
	}
	for (int i = 1; i <= numberOfVertices - 3; i++)
	{
		obj << "f " << i << "/1/1 " << (i + 1) << "/2/1 " << i + numberOfVertices << "/4/1" << endl;
		obj << "f " << i + numberOfVertices << "/4/1 " << (i + 1) << "/2/1 " << i + 1 + numberOfVertices << "/3/1" << endl;
	}

	obj.close();
}

void finish()
{
	coreShader.Delete();

	glfwTerminate();
}