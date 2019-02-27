#pragma once
#include "../../include/imguiIncludes/menu.h"
#include"..\..\include\client.h"
#include"..\..\include\server.h"
#include<iostream>
bool menu:: server_mode;
bool menu:: client_mode;
bool menu::draw_mode;
bool menu::pick_mode;
ImVec4 menu::clear_color;
ImVec4 menu::brush_color;
void menu::startMenu()
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
		ImGui::Checkbox("SERVER MODE", &server_mode);
		ImGui::Checkbox("CLIENT MODE", &client_mode);
		ImGui::End();
		if (server_mode)
		{
			startMenuTerminate(win1.getWin());
			wins();
		}
		if (client_mode)
		{
			startMenuTerminate(win1.getWin());
			winc();
		}

		ImGui::Render();

		win1.renderWindow();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(win1.getWin());
		glfwPollEvents();
	}


	startMenuTerminate(win1.getWin());
	
	

	

}
void menu::startMenuTerminate(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(window);
	glfwTerminate();

}
void menu::wins()
{
	ImGui1 ImG2;
	ImG2.ImGuiNeeds();

	Board::first.push_back(0);
	Board wins(1000, 500,"server");
	Mouse mouse;
	wins.initGLFW();
	wins.MakeWindow();
	wins.GladLoader();

	ImG2.ImGuiInit();

	ImG2.ImGuiImpGLFW(wins.getWin());
	wins.SetMatrices();
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
	Board winc(1000, 500,"CLIENT");
	Mouse mouse;
	winc.initGLFW();
	winc.MakeWindow();
	winc.GladLoader();

	ImG2.ImGuiInit();

	ImG2.ImGuiImpGLFW(winc.getWin());

	winc.SetMatrices();
	Buffer b;
	Shader s;
	b.generateBuffers(1, 1);

	Client client;
	client.connectToServer();

	client.clientWindow(ImG2, winc, b, s);
}