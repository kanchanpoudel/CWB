#pragma once
//imgui include file started
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include<glad\glad.h>
//.
#include <GLFW/glfw3.h>
#include<GLFW\glfw3native.h>
#include<iostream>
class ImGui1
{
private:
	const char* glsl_version = "#version 130";
	ImVec4 clear_color =ImVec4( 0.45f, 0.55f, 0.60f, 1.00f );
	bool whiteboard;
	bool server_window;
	bool client_window;
public:
	void ImGuiNeeds();
	void ImGuiInit();
	void ImGuiImpGLFW(GLFWwindow*);
	void ImGuiInitFrame();
	void server_clientModel();
	void ImGuiRenderContext(GLFWwindow*);
	void ImGuiCleanUp();
};