#include "System.h"

System::System()
{
}

System::~System()
{
}

int System::GLFWInit()
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
	glfwSetMouseButtonCallback(window, mouse_button_callback);

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

int System::OpenGLSetup()
{

	glEnable(GL_BLEND); // Enables blending ( glBlendFunc )
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	return EXIT_SUCCESS;
}

int System::SystemSetup()
{
	coreShader = Shader("./gerador/Shaders/Core/core.vert", "./gerador/Shaders/Core/core.frag");
	coreShader.Use();

	glm::mat4 proj = glm::ortho(0.0f, 600.0f, 600.0f, 0.0f, -1.0f, 1.0f);

	coreShader.setMatrix4fv("projection", proj);

	return EXIT_SUCCESS;
}

GLuint VAO_CP, VBO_CP;
GLuint VAO_BSPLINE, VBO_BSLINE;
GLuint VAO_BSPLINE_IN, VBO_BSLINE_IN;
GLuint VAO_BSPLINE_EX, VBO_BSLINE_EX;

vector<float> control_points, bspline, bspline_in, bspline_ex;

void System::Run()
{
	coreShader.Use();

	glGenBuffers(1, &VBO_CP);
	glGenVertexArrays(1, &VAO_CP);

	glGenBuffers(1, &VBO_BSLINE);
	glGenVertexArrays(1, &VAO_BSPLINE);

	glGenBuffers(1, &VBO_BSLINE_IN);
	glGenVertexArrays(1, &VAO_BSPLINE_IN);

	glGenBuffers(1, &VBO_BSLINE_EX);
	glGenVertexArrays(1, &VAO_BSPLINE_EX);

	glBindVertexArray(VAO_CP);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_CP);
	glBufferData(GL_ARRAY_BUFFER, control_points.size() * sizeof(float), control_points.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO_BSPLINE);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_BSLINE);
	glBufferData(GL_ARRAY_BUFFER, bspline.size() * sizeof(float), bspline.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO_BSPLINE_IN);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_BSLINE_IN);
	glBufferData(GL_ARRAY_BUFFER, bspline_in.size() * sizeof(float), bspline_in.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO_BSPLINE_EX);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_BSLINE_EX);
	glBufferData(GL_ARRAY_BUFFER, bspline_ex.size() * sizeof(float), bspline_ex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{

		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}

		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			to_obj();
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		coreShader.Use();

		glBindVertexArray(VAO_CP);
		glPointSize(5);
		glDrawArrays(GL_POINTS, 0, (float)control_points.size() / 3);

		glBindVertexArray(VAO_BSPLINE);
		glDrawArrays(GL_LINE_STRIP, 0, (float)bspline.size() / 3);

		glBindVertexArray(VAO_BSPLINE_IN);
		glDrawArrays(GL_LINE_STRIP, 0, (float)bspline_in.size() / 3);

		glBindVertexArray(VAO_BSPLINE_EX);
		glDrawArrays(GL_LINE_STRIP, 0, (float)bspline_ex.size() / 3);

		glfwSwapBuffers(window);
	}
}

double x_last_pos = -1.0, y_last_pos = -1.0;

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double x_current_pos, y_current_pos;
		glfwGetCursorPos(window, &x_current_pos, &y_current_pos);

		if (x_last_pos == x_current_pos && y_last_pos == y_current_pos)
		{
			// just to not repeat
			return;
		}

		x_last_pos = x_current_pos;
		y_last_pos = y_current_pos;

		control_points.push_back(x_current_pos);
		control_points.push_back(y_current_pos);
		control_points.push_back(0.0f);

		glBindVertexArray(VAO_CP);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_CP);
		glBufferData(GL_ARRAY_BUFFER, control_points.size() * sizeof(float), control_points.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		update_bspline();
		update_bspline_in_ex();
	}
}

void update_bspline()
{
	bspline.clear();
	int size = control_points.size();

	for (int i = 0; i < size + 3; i += 3)
	{
		for (float t = 0; t < 1; t += 0.03f)
		{

			float t_pow_3 = pow(t, 3);
			float t_pow_2 = pow(t, 2);

			float x = calculate_bspline_point(t, t_pow_3, t_pow_2,
																				control_points[(i + 0) % size],
																				control_points[(i + 3) % size],
																				control_points[(i + 6) % size],
																				control_points[(i + 9) % size]);

			float y = calculate_bspline_point(t, t_pow_3, t_pow_2,
																				control_points[(i + 0 + 1) % size],
																				control_points[(i + 3 + 1) % size],
																				control_points[(i + 6 + 1) % size],
																				control_points[(i + 9 + 1) % size]);

			float z = calculate_bspline_point(t, t_pow_3, t_pow_2,
																				control_points[(i + 0 + 2) % size],
																				control_points[(i + 3 + 2) % size],
																				control_points[(i + 6 + 2) % size],
																				control_points[(i + 9 + 2) % size]);

			bspline.push_back(x);
			bspline.push_back(y);
			bspline.push_back(z);
		}
	}

	glBindVertexArray(VAO_BSPLINE);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_BSLINE);
	glBufferData(GL_ARRAY_BUFFER, bspline.size() * sizeof(float), bspline.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

float calculate_bspline_point(float &t, float &t_pow_3, float &t_pow_2, float &p1, float &p2, float &p3, float &p4)
{
	return (
			(
					(-1 * t_pow_3 + 3 * t_pow_2 - 3 * t + 1) * p1 +
					(+3 * t_pow_3 - 6 * t_pow_2 + 0 * t + 4) * p2 +
					(-3 * t_pow_3 + 3 * t_pow_2 + 3 * t + 1) * p3 +
					(+1 * t_pow_3 + 0 * t_pow_2 + 0 * t + 0) * p4) /
			6.0f);
}

void update_bspline_in_ex()
{
	bspline_ex.clear();
	bspline_in.clear();
	int size = bspline.size();
	float CURVE_DISTANCE = 15.0f;

	for (int i = 0; i < size - 3; i += 3)
	{

		float Ax = bspline[(i + 0) % size];
		float Ay = bspline[(i + 1) % size];

		float Bx = bspline[(i + 3) % size];
		float By = bspline[(i + 4) % size];

		float Ac = bspline[(i + 2) % size];
		float Bc = bspline[(i + 5) % size];

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

		bspline_in.push_back(internalCx);
		bspline_in.push_back(internalCy);
		bspline_in.push_back(Ac);

		float externalCx = cos(externalAngle) * CURVE_DISTANCE + Ax;
		float externalCy = sin(externalAngle) * CURVE_DISTANCE + Ay;

		bspline_ex.push_back(externalCx);
		bspline_ex.push_back(externalCy);
		bspline_ex.push_back(Ac);
	}

	glBindVertexArray(VAO_BSPLINE_IN);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_BSLINE_IN);
	glBufferData(GL_ARRAY_BUFFER, bspline_in.size() * sizeof(float), bspline_in.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO_BSPLINE_EX);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_BSLINE_EX);
	glBufferData(GL_ARRAY_BUFFER, bspline_ex.size() * sizeof(float), bspline_ex.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

void to_obj()
{
	float GLOBAL_SCALE = 0.05f;
	float HEIGHT_SCALE = 0.05f;

	ofstream curva("./objects/coords.txt");
	float temp = bspline.size() / ((float)control_points.size() / 3);
	for (int i = 0; i < bspline.size() - temp; i += 3)
	{
		curva << bspline[i] * GLOBAL_SCALE << " " << bspline[i + 2] * HEIGHT_SCALE << " " << bspline[i + 1] * GLOBAL_SCALE << endl;
	}
	curva.close();

	ofstream material("./objects/pista.mtl");
	material << "newmtl "
					 << "pista" << endl;
	material << "Ka 0.7 0.7 0.7" << endl;
	material << "Kd 0.9 0.9 0.9" << endl;
	material << "Ks 1.0 1.0 1.0" << endl;
	material << "Ns 64.0" << endl;
	material << "map_Kd "
					 << "Objects/pista.jpg" << endl;
	material.close();

	ofstream obj("./objects/pista.obj");
	obj << "mtllib "
			<< "Objects/pista.mtl" << endl;
	obj << "g "
			<< "pista" << endl;
	obj << "usemtl "
			<< "pista" << endl;

	obj << "vn 0.0 1.0 0.0" << endl;
	obj << "vt 0.0 0.0" << endl;
	obj << "vt 0.0 1.0" << endl;
	obj << "vt 1.0 0.0" << endl;
	obj << "vt 1.0 1.0" << endl;

	int size = bspline_in.size();
	int vertices_size = size / 3;
	for (int i = 0; i < size; i += 3)
	{
		obj << "v " << (bspline_in[i] * GLOBAL_SCALE) << " " << bspline_in[i + 2] * HEIGHT_SCALE << " " << (bspline_in[i + 1] * GLOBAL_SCALE)
				<< endl;
	}
	for (int i = 0; i < size; i += 3)
	{
		obj << "v " << (bspline_ex[i] * GLOBAL_SCALE) << " " << bspline_ex[i + 2] * HEIGHT_SCALE << " " << (bspline_ex[i + 1] * GLOBAL_SCALE)
				<< endl;
	}

	for (int i = 1; i <= size / 3 - 3; i++)
	{
		obj << "f " << i << "/1/1 " << (i + 1) << "/2/1 " << i + vertices_size << "/4/1" << endl;
		obj << "f " << i + vertices_size << "/4/1 " << (i + 1) << "/2/1 " << i + 1 + vertices_size << "/3/1" << endl;
	}

	obj.close();
}

void System::Finish()
{
	coreShader.Delete();

	glfwTerminate();
}
