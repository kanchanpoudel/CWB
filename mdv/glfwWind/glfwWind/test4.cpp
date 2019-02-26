#pragma once
//imgui include file started
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include<glad\glad.h>
int win2(void);
#include <GLFW/glfw3.h>
#include<GLFW\glfw3native.h>
#include"../glfwWind/imgui1.h"
#include"menu.h"
#include<iostream>
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
int main(void)
{
	ImGui1 ImG1;
	menu menu1;
	//IMGUI Needed contents
	ImG1.ImGuiNeeds();
	//.


	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "COLLABORATIVE WHITEBOARD", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	//IMGUI CONTENTS INTIALIZATION
	ImG1.ImGuiInit();

	ImG1.ImGuiImpGLFW(window);

	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);//specifies drawing part of the window
	glMatrixMode(GL_PROJECTION);//defines properties of camera that views the object in the
								//coordinate frame
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);//essentially set coordinate sys
	glMatrixMode(GL_MODELVIEW);//defines how objects are transformed in your world
	glLoadIdentity();//starts us a fresh identity matrix
	while (!glfwWindowShouldClose(window))

	{
		glClear(GL_COLOR_BUFFER_BIT);
		///* Render here */
		//glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		//INTIALIZATION of ImGui frame
		ImG1.ImGuiInitFrame();
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
		
		menu1.win1(window);
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(window);
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwMakeContextCurrent(window);
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}