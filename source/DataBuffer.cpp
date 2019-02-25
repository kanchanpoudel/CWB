#pragma once 
#include"..\include\DataBuffer.h"







	void Buffer::generateBuffers(unsigned int vabCount, unsigned int vbCount)
	{
		glGenVertexArrays(vabCount, &VAO);
		glGenBuffers(vbCount, &buffer);
	}
	void Buffer::CreateBuffer(const std::vector<float>& positions)
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, buffer);
		glBufferData(GL_ARRAY_BUFFER, (positions.size()) *(sizeof(float)), positions.data(), GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);


	}
	void Buffer::bindvaBuffer()
	{
		glBindVertexArray(VAO);

	}
	void Buffer::unBindvaBuffer()
	{
		glBindVertexArray(0);
	}
	void Buffer::unBindvBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}



