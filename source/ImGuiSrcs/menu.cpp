#pragma once
#include "../../include/imguiIncludes/menu.h"
#include"..\..\include\client.h"
#include"..\..\include\server.h"
#include<iostream>
bool Menu:: server_mode;
bool Menu:: client_mode;
bool Menu::draw_mode;
bool Menu::pick_mode;
ImVec4 Menu::clear_color;
ImVec4 Menu::brush_color;
Menu::Menu()
{
	Menu::server_mode = false;
	Menu::client_mode = false;
	Menu::clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	Menu::brush_color = ImVec4(0.0f, 0.05f, 0.60f, 1.00f);
}
Menu::~Menu(){}
int Menu::startMenu()
{
	ImGui1 ImG1;
	ImG1.ImGuiNeeds();
	Board win1(1000, 500, "Collaborative White Board");

	win1.initGLFW();

	win1.MakeWindow();
	win1.GladLoader();

	ImG1.ImGuiInit();

	ImG1.ImGuiImpGLFW(win1.getWin());

	win1.SetMatrices();
	while (win1.windowState())

	{



		ImG1.ImGuiInitFrame();
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
		ImGui::Begin("Collaborative WhiteBoard");
		ImGui::Text("Welcome To Collaborative whiteboard");
		ImGui::Text("CHOOSE MODE:");
		
		ImGui::Checkbox("CLIENT MODE", &client_mode);
		ImGui::Checkbox("SERVER MODE", &server_mode);
		if (ImGui::Button("EXIT"))
		{
			startMenuTerminate(win1.getWin());
			return 0;
		}
		ImGui::End();
		if (server_mode)
		{
			startMenuTerminate(win1.getWin());
			win2("SERVER");
		}
		if (client_mode)
		{
			startMenuTerminate(win1.getWin());
			win2("CLIENT");
		}

		ImGui::Render();

		win1.renderWindow();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(win1.getWin());
		glfwPollEvents();
	}


	startMenuTerminate(win1.getWin());
	
	

	

}
void Menu::startMenuTerminate(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

}

void Menu::win2(const std::string mode)
{
	ImGui1 ImG2;
	ImG2.ImGuiNeeds();

	Board::first.push_back(0);
	Board winc(1000, 500, mode);
	
	winc.initGLFW();
	winc.MakeWindow();
	winc.GladLoader();

	ImG2.ImGuiInit();

	ImG2.ImGuiImpGLFW(winc.getWin());

	winc.SetMatrices();
	Buffer b;
	Shader s;
	b.generateBuffers(1, 1);
	if (mode == "SERVER")
	{
		Mouse mouse;
		Server server;
		server.connectToClient();

		server.serverWindow(ImG2, winc, b, mouse, s);
	}

		if (mode == "CLIENT")
		{
			Client client;
			client.connectToServer();

			client.clientWindow(ImG2, winc, b, s);
		}
	
	
}