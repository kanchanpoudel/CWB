void imgui(bool whiteboard,bool another_window, ImVec4 clear_color)
{
if (whiteboard);
ImGui::ShowDemoWindow(&whiteboard);
// window contents.

static float f = 0.0f;
static int counter = 0;

ImGui::Begin("MODE");                          // Create a window called "MODE" and append into it.

ImGui::Text("choose mode");               // Display some text (you can use a format strings too)
ImGui::Checkbox("Demo Window", &whiteboard);      // Edit bools storing our window open/close state
ImGui::Checkbox("Another Window", &another_window);

ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

if (ImGui::Button("SERVER"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
{
	counter++;
	whiteboard = false;
	//ImGui::End();
}

if (ImGui::Button("CLIENT"))
{
	counter++;
	whiteboard = false;
	//ImGui::End();
}
ImGui::SameLine();
ImGui::Text("counter = %d", counter);

ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
ImGui::End();

//	Show another simple window.
if (another_window)
{
	ImGui::Begin("Another Window", &another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	ImGui::ColorEdit3("clear color", (float*)&clear_color);
	if (ImGui::Button("Close Me"))
		another_window = false;
	ImGui::End();
}

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