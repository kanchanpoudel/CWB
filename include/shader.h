#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include <GLFW/glad.h>
#include <GLFW/glfw3.h>
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCAll(x) GLClearError();\
x;\
ASSERT(GLLogCall())
class Shader
{
private:
	std::string vertexshader, fragmentshader;
	
public :
	
	void parseShader();
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	void ShaderProgram();
	
};