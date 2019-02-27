#include"..\include\server.h"


sf::TcpSocket Server:: client;
sf::Packet Server::spacket;
sf::TcpListener Server::listener;
int Server::id;
void Server::connectToClient()
{
	listener.listen(53000, "10.100.60.49");
	listener.accept(client);
	std::thread worker(SendingThread);



	worker.detach();

	
}
void Server::serverWindow(ImGui1 & ImG2, Board & win , Buffer & b, Mouse & mouse, Shader & s)
{
	while (win.windowState())
	{
		win.renderWindow();
		ImG2.ImGuiInitFrame();
		ImGui::SetNextWindowPos(ImVec2(700, 20), ImGuiCond_Always);
		{
			ImGui::Begin("TOOLS", &menu::server_mode);
			ImGui::Text("CHOOSE COLOR");
			ImGui::ColorEdit3("clear color", (float*)&menu::clear_color);
			if (ImGui::Button("DRAW"))
			{
				ImGui::Text("You're in Draw mode.");
			}
			ImGui::End();
		}
		ImGui::Render();
		int display_w, display_h;
		glfwMakeContextCurrent(win.getWin());
		glfwGetFramebufferSize(win.getWin(), &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(menu::clear_color.x,menu:: clear_color.y,menu:: clear_color.z, menu::clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		mouse.mouseButtonPressed(win.getWin());

		mouse.recordCursor(win.getWin());

		b.CreateBuffer(Board::positions);
		s.parseShader();
		s.ShaderProgram();
		win.DrawBoard(Board::positions, Board::first, Board::count);

		b.unBindvaBuffer();

		glfwSwapBuffers(win.getWin());

		glfwPollEvents();
	}

	ImG2.ImGuiCleanUp();

	glfwDestroyWindow(win.getWin());
	glfwTerminate();

 }
void Server::SendingThread()
{

	std::cout << "started thread id-" << std::this_thread::get_id() << std::endl;


	while (true)
	{

		spacket.clear();

		if (id == Mouse::next)
		{


			spacket << static_cast<sf::Uint32>(Board::positions.size());
			for (std::vector<float>::const_iterator it = Board::positions.begin(); it != Board::positions.end(); ++it)
				spacket << *it;



			if (client.send(spacket) == sf::Socket::Done)
			{
				id += 2;
			}




		}

	}

}