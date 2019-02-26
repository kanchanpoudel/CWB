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
		Server server;
		server.connectToClient();

		server.serverWindow(win, b, mouse, s);

	}

	if (f == 'c')
	{
		Client client;
		client.connectToServer();

		client.clientWindow(win, b, s);



	}
	glfwTerminate();
}