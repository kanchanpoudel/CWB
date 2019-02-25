#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include <GLFW/glad.h>
#include <GLFW/glfw3.h>
class Board
{private:
	GLFWwindow * window;
	public:
		static std::vector<float> positions;
		static std::vector<int> first, count;
		
		void initGLFW();
		void RenderBoard();
		void renderWindow();
		void DrawBoard(std::vector<float> &, std::vector<int> &, std::vector<int> &);
		GLFWwindow * getWin();
		bool windowState();
	
};