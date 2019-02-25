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

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCAll(x) GLClearError();\
x;\
ASSERT(GLLogCall())
using namespace std::literals::chrono_literals;
static sf::Int32 last = 0;
static std::vector<float> positions;
static std::vector<int> first{ 0 } , count;
static int id = 0, next = 0;
static sf::TcpSocket client;
static sf::TcpSocket socket;
static int temp;
static double posX, pressX, pressY, posY;

static sf::Packet spacket;
static sf::Packet rpacket;

void DoWork()
{

	std::cout << "started thread id-" << std::this_thread::get_id() << std::endl;


	while (true)
	{

		spacket.clear();

		if (id == next)
		{


			spacket << static_cast<sf::Uint32>(positions.size());
			for (std::vector<float>::const_iterator it = positions.begin(); it != positions.end(); ++it)
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
					positions.push_back(item);
					std::cout << item;

				}
			}
			last = size;
			std::cout << "---";
			int temp = (positions.size()) / 2;
			first.push_back(temp);

			count.push_back((first[first.size() - 1] -first[first.size() - 2]));
		}






	}
}
static void mouse_button_callback(GLFWwindow* window, int button, int action, int state)
{

	first.push_back((positions.size()) / 2);

	count.push_back((first[first.size() - 1] - first[first.size() - 2]));




	next++;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		
		glfwGetCursorPos(window, &pressX, &pressY);
		std::cout << "Cursor Position at (" << pressX << " : " << pressY << std::endl;


	}


}

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);

}
static bool GLLogCall()
{
	while (GLenum  error = glGetError())
	{
		std::cout << "[OpenGl Error](" << error << ")" << std::endl;
		return false;
	}
	return true;
}



int main()
{
	Board win;
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
				

				glfwSetMouseButtonCallback(win.getWin(), mouse_button_callback);

				int state = glfwGetMouseButton(win.getWin(), GLFW_MOUSE_BUTTON_LEFT);
				if (state == GLFW_PRESS)
				{


					glfwGetCursorPos(win.getWin(), &posX, &posY);
					positions.push_back((float)(-500 + posX) / 500);

					positions.push_back((float)(+250 - posY) / 250);

					std::cout << (float)(-500 + posX) / 500 << (float)(+250 - posY) / 250;


				}

				b.CreateBuffer(positions);
				s.parseShader();
				s.ShaderProgram();
				win.DrawBoard(positions, first, count);

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

			while (!glfwWindowShouldClose(win.getWin()))
			{
				win.renderWindow();
				b.CreateBuffer(positions);
				s.parseShader();
				s.ShaderProgram();

				win.DrawBoard(positions, first, count);

				b.unBindvaBuffer();







				glfwSwapBuffers(win.getWin());

				glfwPollEvents();
			}
		}



		glfwTerminate();

	}
}