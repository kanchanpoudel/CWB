#pragma once
//imgui include file started
#include<imgui.h>
#include<imgui_impl_glfw.h>
#include<imgui_impl_opengl3.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include<glad\glad.h>
//.
#include<ft2build.h>
//#include FT_FREETYPE_H
#include <GLFW/glfw3.h>
#include<GLFW\glfw3native.h>
#include<iostream>
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
int main(void)
{

	//IMGUI Needed contents
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
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
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;


	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	//enable keyboard
	ImGui::StyleColorsDark();   //Classic and light are also available

	ImGui_ImplGlfw_InitForOpenGL(window, true);		//Setup render platforms
	ImGui_ImplOpenGL3_Init(glsl_version);	//Setup Bindings



	bool whiteboard = true;
	bool server_window = false;
	bool client_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//.

	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);//specifies drawing part of the window
	glMatrixMode(GL_PROJECTION);//defines properties of camera that views the object in the
								//coordinate frame
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);//essentially set coordinate sys
	glMatrixMode(GL_MODELVIEW);//defines how objects are transformed in your world
	glLoadIdentity();//starts us a fresh identity matrix
					 //GLfloat pointVertex[] = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
					 /* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		///* Render here */
		//glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		//INTIALIZATION of ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		if (whiteboard)
		{
			//showing first window
			//contents of this window
			static float f = 0.0f;
			static int m = 0;

			ImGui::Begin("COLLABOATIVE WHITEBOARD");
			ImGui::Text("Welcome To Collaborative whiteboard");
			ImGui::Text("CHOOSE MODE:");
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			//ImGui::ShowFontSelector("font");
			if (ImGui::Button("SERVER MODE"))
			{
				m++;
				whiteboard = false;
				server_window = true;
			}
			if (ImGui::Button("CLIENT MODE"))
			{
				m--;
				whiteboard = false;
				client_window = true;
			}
			ImGui::End();

			// Rendering
			ImGui::Render();
			int display_w, display_h;
			glfwMakeContextCurrent(window);
			glfwGetFramebufferSize(window, &display_w, &display_h);
			glViewport(0, 0, display_w, display_h);
			glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
			glClear(GL_COLOR_BUFFER_BIT);
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
		if (server_window)
		{
			ImGui::Begin("TOOLS");
			ImGui::Text("CHOOSE COLOR");
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			if (ImGui::Button("DRAW"))
			{
				ImGui::Text("You're in Draw mode.");
			}
			ImGui::End();
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
		if (client_window)
		{
			ImGui::Begin("TOOLS");
			ImGui::Text("CHOOSE COLOR");
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			if (ImGui::Button("DRAW"))
			{
				ImGui::Text("You're in Draw mode.");
			}
			ImGui::End();
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
