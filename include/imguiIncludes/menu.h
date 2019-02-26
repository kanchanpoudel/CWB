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
#include<iostream>
class menu
{
private:
	bool server_mode = false;
	bool client_mode = false;
	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 500;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
public:
	void win1(GLFWwindow*);
	int win2();
};