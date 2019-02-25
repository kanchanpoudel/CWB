#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include <GLFW/glad.h>
#include <GLFW/glfw3.h>
class Buffer {
private:
	unsigned int buffer, VAO;

public:
	void generateBuffers(unsigned int vabCount, unsigned int vbCount);
	void CreateBuffer(const std::vector<float>&);
	void bindvaBuffer();
	void unBindvaBuffer();
	void unBindvBuffer();
		
};

