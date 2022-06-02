#pragma once
#pragma comment(lib,"OpenGL32")
#define _CRT_SECURE_NO_WARNINGS
#include <GLFW/glfw3.h>
#include <thread>
#include <stdio.h>

static GLuint texName;

namespace TGame_Engine
{
	
	typedef struct tagBITMAPHEADER {
		BITMAPFILEHEADER bf;
		BITMAPINFOHEADER bi;
		RGBQUAD hRGB[256];
	}BITMAPHEADER;

	BYTE* LoadBitmapFile(BITMAPHEADER* bitmapHeader, int* imgSize, const char* filename)
	{
		FILE* fp = fopen(filename, "rb");
		if (fp == NULL)
		{
			printf("파일로딩에 실패했습니다.\n");
			return NULL;
		}
		else
		{
			fread(&bitmapHeader->bf, sizeof(BITMAPFILEHEADER), 1, fp);
			fread(&bitmapHeader->bi, sizeof(BITMAPINFOHEADER), 1, fp);
			fread(&bitmapHeader->hRGB, sizeof(RGBQUAD), 256, fp);

			int imgSizeTemp = bitmapHeader->bi.biWidth * bitmapHeader->bi.biHeight;
			*imgSize = imgSizeTemp;   // 이미지 사이즈를 상위 변수에 할당

			BYTE* image = (BYTE*)malloc(sizeof(BYTE) * imgSizeTemp);
			fread(image, sizeof(BYTE), imgSizeTemp, fp);
			fclose(fp);


			return image;
		}
	}

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


			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

		void ExitWindow()
		{

			glfwDestroyWindow(window);
			glfwTerminate();

			exit(EXIT_SUCCESS);
		}
		void EndScreen()
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);

        BITMAPHEADER originalHeader;
        int imgSize;
        BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "EndScreen.bmp");
        
        if (image == NULL) return;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(1, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_BLUE, GL_BYTE, image);
		

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texName);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);  glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0, 1.0);  glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0, 1.0);  glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0, 0.0);  glVertex3f(1.0f, -1.0f, 0.0f);


		glEnd();
		glFlush();
		glDisable(GL_TEXTURE_2D);
    }

    void StartScreen()
    {
        glClearColor(0.0, 0.0, 0.0, 0.0);

        BITMAPHEADER originalHeader;
        int imgSize;
        BYTE* image = LoadBitmapFile(&originalHeader, &imgSize, "StartScreen.bmp");

        if (image == NULL) return;

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glGenTextures(1, &texName);
        glBindTexture(GL_TEXTURE_2D, texName);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
            GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
            GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_BLUE, GL_BYTE, image);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glBindTexture(GL_TEXTURE_2D, texName);

		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);  glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0, 1.0);  glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0, 1.0);  glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0, 0.0);  glVertex3f(1.0f, -1.0f, 0.0f);


		glEnd();
		glFlush();
		glDisable(GL_TEXTURE_2D);
    }

	};


}