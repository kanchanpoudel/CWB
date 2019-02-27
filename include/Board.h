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
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	float line_width;
	std::string board_name;
	public:
		Board(const int, const int, const std::string);
		static std::vector<float> positions;
		static std::vector<int> first, count;
		
		void initGLFW();
		void MakeWindow();
		int GladLoader();
		void renderWindow();
		void SetMatrices();
		
		void DrawCalls(std::vector<float> &, std::vector<int> &, std::vector<int> &);
		GLFWwindow * getWin();
		bool windowState();
	
};