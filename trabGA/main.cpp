#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <math.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "newModel/NewShader.h"
#include "newModel/NewMesh.h"
#include "newModel/NewMaterial.h"
#include "newModel/NewGroup.h"
#include "newModel/NewFace.h"
#include "newModel/NewObject.h"
#include "utils/NewObjectReader.h"

float cameraSpeed = 0.1f;

glm::vec3 cameraPosition = glm::vec3(0.0f, 3.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
double lastTime = 0;

const GLint WIDTH = 1920, HEIGHT = 1080;

void createBuffersForObject(NewObject *object, Shader &shader)
{
	for (NewGroup *group : object->getMesh()->getGroups())
	{
		NewMaterial *material = object->getMesh()->getMaterial(group->getMaterial());
		shader.LoadTexture(strdup(material->getTexture().c_str()), "texture1", group->getName());

		vector<float> vertices;
		vector<float> normais;
		vector<float> textures;

		for (NewFace *face : group->getFaces())
		{
			for (int verticeID : face->getVertices())
			{
				glm::vec3 *vertice = object->getMesh()->vertice(verticeID - 1);
				vertices.push_back(vertice->x);
				vertices.push_back(vertice->y);
				vertices.push_back(vertice->z);

				group->increaseNumVertices();
			}

			for (int normalID : face->getNormais())
			{
				glm::vec3 *normal = object->getMesh()->normal(normalID - 1);
				normais.push_back(normal->x);
				normais.push_back(normal->y);
				normais.push_back(normal->z);
			}

			for (int textureID : face->getTextures())
			{
				glm::vec2 *texture = object->getMesh()->texture(textureID - 1);
				textures.push_back(texture->x);
				textures.push_back(texture->y);
			}
		}

		GLuint VBOvertices, VBOnormais, VBOtextures, VAO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBOvertices);
		glGenBuffers(1, &VBOnormais);
		glGenBuffers(1, &VBOtextures);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBOvertices);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, VBOnormais);
		glBufferData(GL_ARRAY_BUFFER, normais.size() * sizeof(float), normais.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, VBOtextures);
		glBufferData(GL_ARRAY_BUFFER, textures.size() * sizeof(float), textures.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid *)0);
		glEnableVertexAttribArray(2);

		group->setVAO(&VAO);
		glBindVertexArray(0);
	}
}

bool checkCollision(NewObject *one, NewObject *two)
{
	bool collisionX = one->getTranslate().x + one->getColliderSize().x * one->getScale().x >= two->getTranslate().x &&
										two->getTranslate().x + two->getColliderSize().x * two->getScale().x >= one->getTranslate().x;
	bool collisionY = one->getTranslate().z + one->getColliderSize().y * one->getScale().y >= two->getTranslate().z &&
										two->getTranslate().z + two->getColliderSize().y * two->getScale().y >= one->getTranslate().z;
	return collisionX && collisionY;
}

int main()
{
	GLFWwindow *window;
	int screenWidth, screenHeight;
	float yaw = 90.0f;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Trabalho Grau B", nullptr, nullptr);
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	if (window == nullptr)
	{
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		return EXIT_FAILURE;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, screenWidth, screenHeight);

	Shader coreShader = Shader("./trabGA/shaders/vertex.shader", "./trabGA/shaders/fragment.shader");
	coreShader.Use();

	glm::ortho(0.0f, (float)WIDTH, 0.0f, (float)HEIGHT, 0.1f, 100.0f);

	vector<NewObject *> objects;

	coreShader.setVec4("fogColor", vec4(0.8f, 0.9f, 1.0f, 1.0f));
	coreShader.setFloat("fogNear", 50.0f);
	coreShader.setFloat("fogFar", 150.0f);

	NewObject *ground = new NewObject("./trabGA/assets/ground/ground.obj");
	ground->setTranslate(glm::vec3(-40.0f, 0.0f, -40.0f));
	ground->setScale(glm::vec3(2.0f));
	ground->setRotation(glm::vec3(0.0f, 1.0f, 0.0f));
	ground->setRotationAngle(180.0f);
	objects.push_back(ground);

	NewObject *pista = new NewObject("./objects/pista.obj");
	pista->setTranslate(glm::vec3(0.0f, 0.1f, 0.0f));
	pista->setScale(glm::vec3(2.0f));
	objects.push_back(pista);

	NewObject *pikachu = new NewObject("./trabGA/assets/pokemon/Pikachu.obj");
	pikachu->setHasCollision(true);
	objects.push_back(pikachu);
	NewObject *pikachu1 = new NewObject("./trabGA/assets/pokemon/Pikachu.obj");
	pikachu1->setHasCollision(true);
	pikachu1->setTranslate(glm::vec3(-10.0f, 0.0f, -10.0f));
	objects.push_back(pikachu1);
	NewObject *pikachu2 = new NewObject("./trabGA/assets/pokemon/Pikachu.obj");
	pikachu2->setHasCollision(true);
	pikachu2->setTranslate(glm::vec3(-5.0f, 0.0f, 3.0f));
	objects.push_back(pikachu2);
	NewObject *pikachu3 = new NewObject("./trabGA/assets/pokemon/Pikachu.obj");
	pikachu3->setHasCollision(true);
	pikachu3->setTranslate(glm::vec3(5.0f, 0.0f, 2.0f));
	objects.push_back(pikachu3);

	for (NewObject *object : objects)
	{
		createBuffersForObject(object, coreShader);
	}

	float camX = 1.0f;
	float camY = 0.5f;
	float camZ = 1.0f;

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			cameraPosition += cameraSpeed * cameraFront;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			cameraPosition -= cameraSpeed * cameraFront;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			yaw += 1.0f;
			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw));
			direction.y = 0.0f;
			direction.z = sin(glm::radians(yaw));
			cameraFront = glm::normalize(direction);
		}

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			yaw -= 1.0f;
			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw));
			direction.y = 0.0f;
			direction.z = sin(glm::radians(yaw));
			cameraFront = glm::normalize(direction);
		}

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{

			double now = glfwGetTime();

			if (now - lastTime >= 0.5)
			{
				NewObject *bullet = new NewObject("./trabGA/assets/cube/cube.obj");

				bullet->setTranslate(cameraPosition);
				bullet->setVelocity(2.0f);
				bullet->setIsBullet(true);
				bullet->setHasCollision(true);
				bullet->setDirection(cameraFront);
				objects.push_back(bullet);
				createBuffersForObject(bullet, coreShader);
				lastTime = now;
			}
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		coreShader.Use();

		glm::mat4 view(1.0f);
		view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		coreShader.setMatrix4fv("projection", proj);
		coreShader.setMatrix4fv("view", view);

		coreShader.setVec3("lightColor", vec3(1.0f, 1.0f, 1.0f));
		coreShader.setVec3("lightPos", vec3(10.0f, 10.0f, 0.0f));
		coreShader.setVec3("viewPos", vec3(camX, camY, camZ));

		for (NewObject *object : objects)
		{
			if (!object->getShouldRender())
			{
				continue;
			}

			for (NewGroup *group : object->getMesh()->getGroups())
			{
				NewMaterial *material = object->getMesh()->getMaterial(group->getMaterial());
				coreShader.setVec3("materialAmbient", vec3(material->getAmbient()->x, material->getAmbient()->y, material->getAmbient()->z));
				coreShader.setVec3("materialDiffuse", vec3(material->getDiffuse()->x, material->getDiffuse()->y, material->getDiffuse()->z));
				coreShader.setVec3("materialSpecular", vec3(material->getSpecular()->x, material->getSpecular()->y, material->getSpecular()->z));
				coreShader.setFloat("materialShininess", material->getShininess());

				glm::mat4 model(1.0f);
				model = glm::scale(model, object->getScale());
				model = glm::rotate(model, glm::radians(object->getRotationAngle()), object->getRotation());

				if (object->getIsBullet())
				{
					model = glm::translate(model, object->getVelocity() * object->getDirection() + object->getTranslate());
					object->setTranslate(object->getVelocity() * object->getDirection() + object->getTranslate());
				}
				else
				{
					model = glm::translate(model, object->getTranslate());
				}

				coreShader.setMatrix4fv("model", model);

				coreShader.UseTexture(group->getName());
				glBindVertexArray(group->getVAO());
				glDrawArrays(GL_TRIANGLES, 0, group->getNumVertices());
				glBindVertexArray(0);
			}
		}

		int pos = 1;
		for (NewObject *obj1 : objects)
		{
			for (NewObject *obj2 : objects)
			{
				if (obj1 != obj2)
				{
					if (obj1->getHasCollision() && obj2->getHasCollision())
					{
						if (checkCollision(obj1, obj2))
						{
							obj1->setShouldRender(false);
							obj2->setShouldRender(false);
						}
					}
				}
			}
		}

		glfwSwapBuffers(window);
	}

	return EXIT_SUCCESS;
}
