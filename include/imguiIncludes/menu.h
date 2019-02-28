#pragma once
#pragma once
//imgui include file started
#include<..\imguiIncludes\imgui.h>
#include<..\imguiIncludes\imgui_impl_glfw.h>
#include<..\imguiIncludes\imgui_impl_opengl3.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include<GLFW\glad.h>
#include <GLFW/glfw3.h>
#include<GLFW\glfw3native.h>
#include"..\imgui1.h"
#include"..\DataBuffer.h"
#include"..\shader.h"
#include"..\Board.h"
#include"..\mouse.h"
#include"..\server.h"
#include"..\client.h"
#include<iostream>
class Menu
{
private:
	
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 500;
	
public:
	static ImVec4 clear_color; 
	static ImVec4 brush_color;
	static bool server_mode;
	static bool client_mode;
	static bool draw_mode;
	static bool pick_mode;
	Menu();
	~Menu();

	int startMenu();
	static void startMenuTerminate(GLFWwindow*);

	void win2(const std::string);
	 
};