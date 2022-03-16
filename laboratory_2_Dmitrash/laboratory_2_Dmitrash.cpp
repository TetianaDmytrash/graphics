#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <conio.h> 
#include <locale.h>
#include <cmath> 

#define GLUT_DISABLE_ATEXIT_HACK

#pragma comment(lib, "libs\\GL_AL\\glfw3.lib")
#pragma comment(lib, "libs\\GL_AL\\glut32.lib")
#pragma comment(lib, "libs\\GL_AL\\glut32.dll")
#pragma comment(lib, "libs\\GL_AL\\alut.lib")
#pragma comment(lib, "libs\\GL_AL\\glew32.lib")
#pragma comment(lib, "libs\\GL_AL\\glew32s.lib")
/*
#pragma comment(lib, "mavcrt.lib")
#pragma comment(lib, "mavcmrt.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")
*/
#include "libs\GL_AL\glew.h"
#include "libs\GL_AL\glfw3.h"
#include "libs\GL_AL\glut.h"

#include "libs\GL_AL\glm\glm.hpp"
#include "libs\GL_AL\glm\gtc\matrix_transform.hpp"
#include "libs\GL_AL\glm\gtc\type_ptr.hpp"
#include "libs\GL_AL\glm\gtc\random.hpp"

#include "libs\GL_AL\shader.h"

#define STB_IMAGE_IMPLEMENTATION

//openGL
#define PI 3.14159265
float colorRGB = 0.0;
int wigth, height;
float angle = 0;


namespace my_global {

	bool rotation = true;

	namespace Cube {
		float vertices[] = {
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,//три для вершин
			0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
			0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
			-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
			-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
		};

		unsigned int VBO;
		unsigned int VAO;

		Shader ourShader; //?

		void init(void) {
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		}
	};

	namespace Squares {
		GLfloat vertices[] = {
			0, 0, 0,
			1, 0, 0,
			1, 1, 0,
			0, 1, 0,

			0, 0, 0,
			0, 1, 0,
			-1, 1, 0,
			-1, 0, 0
		};

		GLfloat colors[] = {

			255, 0, 0,
			0, 255, 0,
			255, 0, 0,
			255, 255, 0,

			255, 0, 255,
			0, 100, 70,
			0, 0, 0,
			0, 0, 255
		};
	}

	namespace my_triangle2D {
		int N = 3 * 3 * 3;//три координаты на три точки на три треугольника

		GLfloat vertices[] = {
			0, 0, 0,
			1, 0, 0,
			1, 1, 0,

			0, 0, 0,
			0, 1, 0,
			-1, 1, 0,

			0, 0, 0,
			0, -1, 0,
			1, -1, 0
		};


		GLfloat colors[] = {

			255, 0, 0,
			0, 255, 0,
			255, 0, 0,

			0, 255, 0,
			0, 100, 70,
			255, 0, 255,

			0, 0, 255,
			0, 0, 0,
			255, 255, 0
		};
	}

	namespace my_fantasy2D {
		GLfloat colors[] = {

			255, 0, 37,
			0, 255, 0,
			255, 0, 200,

			0, 255, 0,
			0, 0, 255,
			255, 28, 0,

			105, 0, 20,
			0, 10, 51,
			255, 50, 0,

			255, 0, 100,
			50, 255, 0,
			50, 0, 255
		};
	}

	namespace my_quad2D {
		int N = 2 * 2 * 2;
		GLfloat vertices[] = {
			0, 0, 0,
			1, 0, 0,
			1, 1, 0,
			0, 1, 0,

			0, 0, 0,
			0, 1, 0,
			-1, 1, 0,
			-1, 0, 0
		};

		GLfloat colors[] = {
			255, 0, 0,
			0, 255, 0,
			255, 0, 0,
			255, 255, 0,

			255, 0, 255,
			0, 100, 70,
			0, 0, 0,
			0, 0, 255
		};
	}

}

using namespace std;
using namespace my_global;

#include "GLWindow.h"
#include "GLRenderSystem.h"
#include "GLCamera.h"
#include "GLShader.h"
glm::vec3 RGB = glm::vec3(0);

template <typename T>
void printn(T i) {
	cout << i << endl;
}

string operator+(string s, int i) {
	return s + to_string(i);
}

//println не заработало, где-то туплю, но пока не нашла
void argsEcho(int argc, char** argv) {
	cout << "____everything_is_ok____" << endl;
	if (argc == 0) {
		cout << "___you_forgot_something___ " << endl;
	}
	else {
		for (int i = 0; i < argc; i++) {
			cout << argv[i];
		}
	}
	cout << "____________" << endl;
}

void resize(GLFWwindow* window, int width, int height) {
	//println((string)"Width:" + width + "-Height:" + height);

	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//bool rotation = true;

//#include "glm\gtc\random.hpp"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		cout << "SPACE" << endl;
		RGB = glm::vec3(glm::linearRand(0, 1), glm::linearRand(0, 1), glm::linearRand(0, 1));
	}
}


int main(int argc, char** argv) {
	//char buffer[1*1024*1024] = {};

	argsEcho(argc, argv);
	cout << " Hello_openGL " << endl;
	cout << " Exercise 4 " << endl;
	cout << " Dmitrash Tetiana " << endl;

	bool FULL_SCREEN = false;
	bool openGL_33 = !false;

	ghost_player::GraphCore::GLRenderSystem* renderer;

	if (openGL_33) {
		renderer = new ghost_player::GraphCore::GLRender();
	}
	else {
		renderer = new ghost_player::GraphCore::GLRendererOld2_1();
	}
	renderer->init();

	GLFWwindow* window;
	if (!FULL_SCREEN) {
		window = glfwCreateWindow(800, 800, "Hello first", NULL, NULL);
	}
	else {
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
		window = glfwCreateWindow(mode->width, mode->height, "hello first", monitor, NULL);
	}

	if (window == NULL) {
		fprintf(stderr, "Невозможно открыть окно. Кто-то кого-то недопонял. Крепись.");
		glfwTerminate();
		return -1;
	}

	//ghost_player::GLWindow* Win3 = new ghost_player::GLWindow("hello my_fantasy", 640, 640);
	ghost_player::GLWindow* Win2 = new ghost_player::GLWindow("hello quads", 640, 480,window);
	ghost_player::GLWindow* Win1 = new ghost_player::GLWindow("hello triangles", 640, 640, window);

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);
	//инициализируем GLEW
	glewExperimental = true;//флаг необходим в core-режиме openGL
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Невозможно инициализировать GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetKeyCallback(window, keyCallback);

	//Cube::init();
	ghost_player::GraphCore::Camera* CamFree = new ghost_player::GraphCore::GL_camera_target();
	CamFree->set_perspective(glm::radians(45.0f), (float) GLUT_SCREEN_WIDTH / GLUT_SCREEN_HEIGHT, 0.01f, 1000.0f);
	glfwMakeContextCurrent(Win1->getGLFWHandle());
	CamFree->set_perspective(glm::radians(45.0f), (float)GLUT_SCREEN_WIDTH / GLUT_SCREEN_HEIGHT, 0.01f, 1000.0f);
	glfwMakeContextCurrent(Win2->getGLFWHandle());
	CamFree->set_perspective(glm::radians(45.0f), (float)GLUT_SCREEN_WIDTH / GLUT_SCREEN_HEIGHT, 0.01f, 1000.0f);

	ghost_player::GraphCore::GLShader* shaderBrightDim = new ghost_player::GraphCore::GLShader("BrightAndDim_VertexShader.vs", "BrightAndDim_FragmentShader.fs");

	// Проверяем нажатие клавиши Escape или закрытие окна
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {


		glfwMakeContextCurrent(window);

		angle = glfwGetTime() * 50.0f;
		CamFree->set_pos(glm::vec3(2 * cos(angle * PI / 180), 2, 2 * sin(angle * PI / 180)));
		CamFree->start();
		shaderBrightDim->use();
		shaderBrightDim->setVec3("rgb", RGB); // в видеокарту
		shaderBrightDim->setMat4("modelView", CamFree->getMat4ModelView());
		shaderBrightDim->setMat4("modelProj", CamFree->getMat4ModelProj());
		shaderBrightDim->setFloat("time", glfwGetTime());

		renderer->render(window);//шейдер применяется ко всей библиотеки
		glUseProgram(0);
		CamFree->end();
		glfwSwapBuffers(window);// Буферы сбросить
		glfwMakeContextCurrent(Win1->getGLFWHandle());
		CamFree->set_pos(glm::vec3(2 * cos(angle * PI / 180), 2, 2 * sin(angle * PI / 180)));
		CamFree->start();
		shaderBrightDim->use();
		shaderBrightDim->setVec3("rgb", RGB); // в видеокарту
		shaderBrightDim->setMat4("modelView", CamFree->getMat4ModelView());
		shaderBrightDim->setMat4("modelProj", CamFree->getMat4ModelProj());
		shaderBrightDim->setFloat("time", glfwGetTime());
		if (openGL_33) {
			renderer->render(window);
		}
		else {
			renderer->renderTriangleArray(my_triangle2D::vertices, my_triangle2D::colors, my_triangle2D::N);
		}
		glUseProgram(0);
		CamFree->end();
		// Сбрасываем буферы
		glfwSwapBuffers(Win1->getGLFWHandle());
		glfwMakeContextCurrent(Win2->getGLFWHandle());
		CamFree->set_pos(glm::vec3(2 * cos(angle * PI / 180), 2, 2 * sin(angle * PI / 180)));
		CamFree->start();
		shaderBrightDim->use();
		shaderBrightDim->setVec3("rgb", RGB); // в видеокарту
		shaderBrightDim->setMat4("modelView", CamFree->getMat4ModelView());
		shaderBrightDim->setMat4("modelProj", CamFree->getMat4ModelProj());
		shaderBrightDim->setFloat("time", glfwGetTime());
		if (openGL_33) {
			renderer->render(window);
		}
		else {
			renderer->renderQuadArray(my_quad2D::vertices, my_quad2D::colors, my_quad2D::N);
		}
		
		glfwSwapBuffers(Win2->getGLFWHandle());        // Сбрасываем буферы (не опять, а снова)
		glUseProgram(0);
		CamFree->end();

		glfwPollEvents();
	}

	cout << "time: " << glfwGetTime() << endl;
	cout << glm::pi<float>() << endl;
	glDeleteVertexArrays(1, &Cube::VAO);//VAO?
	glDeleteBuffers(1, &Cube::VBO);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
