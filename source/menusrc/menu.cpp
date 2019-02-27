#pragma once
#include "../../include/imguiIncludes/menu.h"
#include"..\..\include\client.h"
#include"..\..\include\server.h"
#include<iostream>
bool menu:: server_mode;
bool menu:: client_mode;
ImVec4 menu::clear_color;
void menu::win1(GLFWwindow* window)
{
	ImGui::Begin("Collaborative WhiteBoard");
	ImGui::Text("Welcome To Collaborative whiteboard");
	ImGui::Text("CHOOSE MODE:");
	ImGui::Checkbox("SERVER MODE", &server_mode);
	ImGui::Checkbox("CLIENT MODE", &client_mode);
	ImGui::End();
	if (server_mode)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(window);
		glfwTerminate();
		wins();
	}
	if (client_mode)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(window);
		glfwTerminate();
		winc();
	}
	ImGui::Render();
	int display_w, display_h;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwMakeContextCurrent(window);

}
void menu::wins()
{
	ImGui1 ImG2;
	ImG2.ImGuiNeeds();

	Board::first.push_back(0);
	Board wins;
	Mouse mouse;
	wins.initGLFW();
	wins.RenderBoard();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		std::cin.get();
		
	}

	ImG2.ImGuiInit();

	ImG2.ImGuiImpGLFW(wins.getWin());

	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);//specifies drawing part of the window
	glMatrixMode(GL_PROJECTION);//defines properties of camera that views the object in the
								//coordinate frame
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);//essentially set coordinate sys
	glMatrixMode(GL_MODELVIEW);//defines how objects are transformed in your world
	glLoadIdentity();//starts us a fresh identity matrix
	Buffer b;
	Shader s;
	Server server;
	b.generateBuffers(1, 1);

	
	server.connectToClient();

	server.serverWindow(ImG2, wins, b, mouse, s);
}
void menu::winc()
{
	ImGui1 ImG2;
	ImG2.ImGuiNeeds();

	Board::first.push_back(0);
	Board wins;
	Mouse mouse;
	wins.initGLFW();
	wins.RenderBoard();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		std::cin.get();

	}

	ImG2.ImGuiInit();

	ImG2.ImGuiImpGLFW(wins.getWin());

	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);//specifies drawing part of the window
	glMatrixMode(GL_PROJECTION);//defines properties of camera that views the object in the
								//coordinate frame
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);//essentially set coordinate sys
	glMatrixMode(GL_MODELVIEW);//defines how objects are transformed in your world
	glLoadIdentity();//starts us a fresh identity matrix
	Buffer b;
	Shader s;
	b.generateBuffers(1, 1);

	Client client;
	client.connectToServer();

	client.clientWindow(ImG2, wins, b, s);
}