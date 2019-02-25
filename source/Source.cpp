#pragma once 
#include<iostream>
#include<fstream>
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

using namespace std::literals::chrono_literals;
static sf::Int32 last = 0;

static int id = 0;
static sf::TcpSocket client;
static sf::TcpSocket socket;
static int temp;


static sf::Packet spacket;
static sf::Packet rpacket;

void DoWork()
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
void DorWork()
{

	std::cout << "started thread id-" << std::this_thread::get_id() << std::endl;
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
 



int main()
{
	Board::first.push_back(0);
	Board win;
	Mouse mouse;
	win.initGLFW();
    win.RenderBoard();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl; return 2;
	}
	Buffer b;
	Shader s;
	b.generateBuffers(1, 1);
	std::cout << "c or s?";
	char f;
	std::cin >> f;
	if (f == 's')
	{
		sf::TcpListener listener;


		listener.listen(53000, "10.100.60.49");


		listener.accept(client);
		std::thread worker(DoWork);



		worker.detach();


		while (true)
		{


			while (!glfwWindowShouldClose(win.getWin()))
			{
				win.renderWindow();
				

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
		}

		glfwTerminate();
	}



	if (f == 'c')
	{


		sf::Socket::Status status = socket.connect("10.100.60.49", 53000);
		std::thread worker(DorWork);



		worker.detach();
		while (true)
		{

			while (win.windowState())
			{
				win.renderWindow();
				b.CreateBuffer(Board::positions);
				s.parseShader();
				s.ShaderProgram();

				win.DrawBoard(Board::positions, Board::first, Board::count);

				b.unBindvaBuffer();







				glfwSwapBuffers(win.getWin());

				glfwPollEvents();
			}
		}



		glfwTerminate();

	}
}