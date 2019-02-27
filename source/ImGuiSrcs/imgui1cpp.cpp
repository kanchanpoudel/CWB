#include"..\..\include\imgui1.h"
void ImGui1::ImGuiNeeds()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}
void ImGui1::ImGuiInit()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
}
void ImGui1::ImGuiImpGLFW(GLFWwindow* window)
{
	ImGui_ImplGlfw_InitForOpenGL(window, true);		//Setup render platforms
	ImGui_ImplOpenGL3_Init(glsl_version);	//Setup Bindings
}
void ImGui1::ImGuiInitFrame()
{
	//INTIALIZATION of ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
void ImGui1::server_clientModel()
{
	ImGui::Begin("TOOLS");
	ImGui::Text("CHOOSE COLOR");
	ImGui::ColorEdit3("clear color", (float*)&clear_color);
	if (ImGui::Button("DRAW"))
	{
		ImGui::Text("You're in Draw mode.");
	}
	ImGui::End();
}

void ImGui1::ImGuiRenderContext(GLFWwindow* window)
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	int display_w, display_h;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwMakeContextCurrent(window);

}

void ImGui1::ImGuiCleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}