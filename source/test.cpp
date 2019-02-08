#include <GLFW/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCAll(x) GLClearError();\
x;\
ASSERT(GLLogCall())
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

struct shaderSource
{
	std::string vertexshader;
	std::string fragmentshader;
};
	
static shaderSource parseShader()

{
	std::stringstream shader[2];
	
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
	
return{ shader[0].str(), shader[1].str() };

}
 static unsigned int CompileShader(unsigned int type, const std::string& source)
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
		std::cout << "Failed to compile " << (type==GL_VERTEX_SHADER ? "vertex":"fragement")<<std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;

		
	}
	
	return id;
}
static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
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


int main(void)

{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	glfwSwapInterval(60);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{ std::cout << "Failed to initialize GLAD" << std::endl; return 2; }
	unsigned int Indices[] = { 0, 1, 2,
							2,3,1 };

	float positions[8] = { -0.5f,0.5f,
							-0.5f,-0.5f,
							0.5f,0.5f,
						   0.5f,-0.5f
							};
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float),positions,GL_STATIC_DRAW);
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6* sizeof(unsigned int), Indices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0 );
	shaderSource use = parseShader();
	

	unsigned int shader = CreateShader(use.vertexshader, use.fragmentshader);
	
	glUseProgram(shader);
	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location!= -1);
     
	
	glUniform4f(location, 0.1f, 0.0f, 0.0f, 1.0f);
	                                                      
	float increment = 0.5f;
	float  r = 0.0f;
	glViewport(120, 40, 400, 400);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUniform4f(location, r, 0.0f, 0.0f, 1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		if (r > 1.0f)
			increment = -0.05f;
		else if (r < 0.0f)
			increment = 0.05f;
		
		r += increment;

		/* Swap front and back buffers */
	/*unsigned char pixels[16 * 16 * 4];
		memset(pixels, 0xff, sizeof(pixels));
		GLFWimage image;
		image.width = 16;
		image.height = 16;
		image.pixels = pixels;
		GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << xpos << ypos;
		*/
		glfwSwapBuffers(window);
		
		/*int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (state == GLFW_PRESS)
		{
			
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);
			
		}
			

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}