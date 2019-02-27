
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


int main(void)
{
	menu::server_mode = false;
	menu::client_mode = false;
	Server::mouseBlock = false;
	menu::clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	menu::brush_color = ImVec4(0.0f, 0.05f, 0.60f, 1.00f);
	menu first;
	first.startMenu();
	
	
	
	
	return 0;
}