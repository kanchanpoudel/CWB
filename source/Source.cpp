#pragma once 
#include<iostream>
#include <GLFW/glad.h>
#include <GLFW/glfw3.h>
#include"..\include\DataBuffer.h"
#include"..\include\shader.h"
#include"..\include\Board.h"
#include"..\include\mouse.h"
#include"..\include\server.h"
#include"..\include\client.h"
int main()
{

	std::cout << "c or s?";
	char f;
	std::cin >> f;
	if (f == 's')
	{
		Board::first.push_back(0);
		Board wins;
		Mouse mouse;
		wins.initGLFW();
		wins.RenderBoard();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl; return 2;
		}

		Buffer b;
		Shader s;
		b.generateBuffers(1, 1);

		Server server;
		server.connectToClient();

		server.serverWindow(wins, b, mouse, s);

	}

	if (f == 'c')
	{
		Board::first.push_back(0);
		Board wins;
		Mouse mouse;
		wins.initGLFW();
		wins.RenderBoard();

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl; return 2;
		}

		Buffer b;
		Shader s;
		b.generateBuffers(1, 1);
		Client client;
		client.connectToServer();

		client.clientWindow(wins, b, s);



	}
	glfwTerminate();
}