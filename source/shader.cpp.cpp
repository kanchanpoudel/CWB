#pragma once 
#include"..\include\shader.h"
Shader& Shader::parseShader()
{
	enum class shaderIndex
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1

	};
	shaderIndex index = shaderIndex::NONE;
	std::ifstream infile("shader.Shader");


	std::string line;
	while (std::getline(infile, line))
	{

		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				index = shaderIndex::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				index = shaderIndex::FRAGMENT;

		}
		else
			shader[(int)index] << line << '\n';


	}

	vertexshader = shader[0].str;
    fragmentshader = shader[1].str;
}
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char *message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragement") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;


	}

	return id;
}
int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}
void Shader::ShaderProgram()
{
	



	unsigned int shader = CreateShader(vertexshader, fragmentshader);

	glUseProgram(shader);
	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location != -1);


	glUniform4f(location, 0.0f, 0.0f, 0.4f, 1.0f);
}