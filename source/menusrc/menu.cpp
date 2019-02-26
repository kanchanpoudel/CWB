#pragma once
#include "../../include/imguiIncludes/menu.h"
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
		win2();
	}
	if (client_mode)
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(window);
		glfwTerminate();
		win2();
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
int menu::win2()
{
	ImGui1 ImG2;
	ImG2.ImGuiNeeds();

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

	ImG2.ImGuiInit();

	ImG2.ImGuiImpGLFW(window);

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
		ImG2.ImGuiInitFrame();
		ImGui::SetNextWindowPos(ImVec2(700, 20), ImGuiCond_Always);
		{
			ImGui::Begin("TOOLS", &server_mode);
			ImGui::Text("CHOOSE COLOR");
			ImGui::ColorEdit3("clear color", (float*)&clear_color);
			if (ImGui::Button("DRAW"))
			{
				ImGui::Text("You're in Draw mode.");
			}
			ImGui::End();
		}
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(window);
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}
	ImG2.ImGuiCleanUp();

	glfwDestroyWindow(window);
	glfwTerminate();
}