#pragma once
#pragma comment(lib,"OpenGL32")
#define _CRT_SECURE_NO_WARNINGS
#include <GLFW/glfw3.h>
#include <thread>
#include <stdio.h>


static GLuint texName;

namespace TGame_Engine
{
	class WindowManager
	{
		GLFWwindow* window;

		static void error_callback(int error, const char* description)
		{
			fputs(description, stderr);
		}
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int Mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, GL_TRUE);
		}
	public:

		int IsWindowClose()
		{
			return glfwWindowShouldClose(window);
		}
		void Initialize()
		{
			glfwSetErrorCallback(error_callback);
			if (!glfwInit()) {
				exit(EXIT_FAILURE);
			}
			window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
			if (!window)
			{
				glfwTerminate();
				exit(EXIT_FAILURE);
			}
			glfwMakeContextCurrent(window);
			glfwSetKeyCallback(window, key_callback);
		}

		void Release()
		{
			glfwDestroyWindow(window);
			glfwTerminate();
			exit(EXIT_SUCCESS);
		}

		void RenderStart()
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

		}
		void RenderEnd()
		{
			glfwSwapBuffers(window);
			glfwPollEvents();

		}

		void RenderPlayer(float x, float y)
		{
			glPointSize(30);
			glBegin(GL_POINTS);
			glColor3f(0.359375f, 0.99609375f, 0.81640625f);
			glVertex2f(x, y);
			glEnd();
		}

		void RenderEnemy(float x, float y)
		{
			glPointSize(30);
			glBegin(GL_POINTS);
			glColor3f(0,0,0);
			glVertex2f(x, y);
			glEnd();
		}


	};

}