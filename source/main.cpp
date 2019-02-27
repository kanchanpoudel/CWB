
#pragma once

#include<../imguiIncludes/imgui.h>
#include<../imguiIncludes/imgui_impl_glfw.h>
#include<../imguiIncludes/imgui_impl_opengl3.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include<GLFW/glad.h>
#include <GLFW/glfw3.h>
#include<GLFW\glfw3native.h>
#include"../imgui1.h"
#include"../include/imguiIncludes/menu.h"
#include<iostream>
#include<fstream>
#include<thread>
#include<sstream>
#include<string>
#include<vector>
#include<Network.hpp>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
int main(void)
{
	menu::server_mode = false;
	menu::client_mode = false;
	Server::mouseBlock = false;
	menu::clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	menu::brush_color = ImVec4(0.0f, 0.05f, 0.60f, 1.00f);
	ImGui1 ImG1;
	menu menu1;
	
	ImG1.ImGuiNeeds();
	GLFWwindow* window;

	
	if (!glfwInit())
		return -1;

	
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "COLLABORATIVE WHITEBOARD", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	
	ImG1.ImGuiInit();

	ImG1.ImGuiImpGLFW(window);

	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	while (!glfwWindowShouldClose(window))

	{
		glClear(GL_COLOR_BUFFER_BIT);
	
		glfwPollEvents();
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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}