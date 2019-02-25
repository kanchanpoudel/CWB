#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include <GLFW/glad.h>
#include <GLFW/glfw3.h>
#include"..\include\Board.h"
class Mouse
{
	double posX, pressX, pressY, posY;
	
public:
	
	static int next;
    
	
	
	static void mouse_button_callback(GLFWwindow* , int , int , int );
    void mouseButtonPressed(GLFWwindow*);
	void recordCursor(GLFWwindow*);
	
};