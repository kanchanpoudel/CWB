
#pragma once
//imgui include file started
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>
#include"..\glfwWind\imgui1.h"
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include<glad\glad.h>
//.
#include<ft2build.h>
//#include FT_FREETYPE_H
#include <GLFW/glfw3.h>
#include<GLFW\glfw3native.h>
#include<iostream>
const float SCREEN_WIDTH = 1000;
const float SCREEN_HEIGHT = 500;
int main(void)
{
	ImGui1 ImG;
	ImG.ImGuiNeeds();


	GLFWwindow* window;

	//Initialize the library 
	if (!glfwInit())
		return -1;

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "COLLABORATIVE WHITEBOARD", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	//Make the window's context current 
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	//IMGUI CONTENTS INTIALIZATION
	ImG.ImGuiInit();
	//ImGui Implementing glfw and opengl3
	ImG.ImGuiImpGLFW(window);
	//.

	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);//specifies drawing part of the window
	glMatrixMode(GL_PROJECTION);//defines properties of camera that views the object in the
	//coordinate frame
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);//essentially set coordinate sys
	glMatrixMode(GL_MODELVIEW);//defines how objects are transformed in your world
	glLoadIdentity();//starts us a fresh identity matrix
	//GLfloat pointVertex[] = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
	//Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		// Render here
		//glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();

		//INTIALIZATION of ImGui frame
		ImG.ImGuiInitFrame();
		ImG.setWhiteBoard(true);
		
		if (ImG.getWhiteBoard())
		{
			ImG.ImGuiFirstWindowRun();	//showing first window
			ImG.ImGuiRenderContext(window); //Rendering context
		}
		if (ImG.getServer_Window())
		{
			ImG.ImGuiServerWindowRun();
			ImG.ImGuiRenderContext(window);
		}
		if (ImG.getClient_Window())
		{
			ImG.ImGuiServerWindowRun();
			ImG.ImGuiRenderContext(window);
		}

		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}

	ImG.ImGuiCleanUp();// Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


