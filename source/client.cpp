#include<thread>
#include<sstream>
#include<string>
#include<vector>
#include<Network.hpp>
#include <GLFW/glad.h>
#include <GLFW/glfw3.h>
#include"..\include\DataBuffer.h"
#include"..\include\shader.h"
#include"..\include\Board.h"
#include"..\include\mouse.h"
#include"..\include\client.h"
sf::TcpSocket Client::socket;
sf::Packet Client::rpacket;
sf::Uint32 Client::last;
void Client::connectToServer()
{
	sf::Socket::Status status = socket.connect("10.100.60.49", 53000);
	std::thread worker(RecievingThread);
	worker.detach();
}
void Client::clientWindow(ImGui1 & ImG2, Board & win, Buffer & b, Shader &s)
{

	while (win.windowState())
	{
		win.renderWindow();
		ImG2.ImGuiInitFrame();
		ImGui::SetNextWindowPos(ImVec2(700, 20), ImGuiCond_Always);
		{
			ImGui::Begin("TOOLS", &Menu::server_mode);
			ImGui::ColorEdit3("Board color", (float*)&Menu::clear_color);
			ImGui::ColorEdit3("Brushcolor", (float*)&Menu::brush_color);
			ImGui::End();
		}
		ImGui::Render();
		win.renderWindow();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		b.CreateBuffer(Board::positions);
		s.parseShader();
		s.ShaderProgram();
		win.DrawCalls(Board::positions, Board::first, Board::count);

		b.unBindvaBuffer();

		glfwSwapBuffers(win.getWin());

		glfwPollEvents();
	}

	ImG2.ImGuiCleanUp();

	glfwDestroyWindow(win.getWin());
	glfwTerminate();

	}



void Client::RecievingThread()
{
	while (true)
	{

		if (socket.receive(rpacket) == sf::Socket::Done)
		{
			sf::Uint32 size;
			rpacket >> size;
			for (sf::Uint32 i = 0; i < size; ++i)
			{
				float item;
				rpacket >> item;
				if (i >= last)
				{
					Board::positions.push_back(item);
					std::cout << item;

				}
			}
			last = size;
			std::cout << "---";
			int temp = (Board::positions.size()) / 2;
			Board::first.push_back(temp);

			Board::count.push_back((Board::first[Board::first.size() - 1] - Board::first[Board::first.size() - 2]));
		}

	}
}
