
#include<iostream>
#include<fstream>
#include<thread>
#include<sstream>
#include<string>

#include<vector>
#include<Network.hpp>
#include <GLFW/glad.h>
#include <GLFW/glfw3.h>


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCAll(x) GLClearError();\
x;\
ASSERT(GLLogCall())
using namespace std::literals::chrono_literals;
static sf::Int32 last = 0;

static int id = 0, next = 0;
static sf::TcpSocket client;
static sf::TcpSocket socket;
static int temp;
static double posX, pressX, pressY, posY;
static std::vector<float> positions;
static std::vector<int> first{0};
static std::vector<int>count;
static sf::Packet spacket;
static sf::Packet rpacket;
void DoWork()
{

	std::cout << "started thread id-" << std::this_thread::get_id() << std::endl;


	while (true)
	{

		spacket.clear();

		if (id == next)
		{
			

			spacket << static_cast<sf::Uint32>( positions.size());
			for (std::vector<float>::const_iterator it = positions.begin(); it != positions.end(); ++it)
				spacket << *it;



			if (client.send(spacket) == sf::Socket::Done)
			{
				id+=2;
			}
			
			
			
			
		}
		
	}
	
}
void DorWork()
{

	std::cout << "started thread id-" << std::this_thread::get_id() << std::endl;
	while (true)
	{
		
		if (socket.receive(rpacket) == sf::Socket::Done)
		{
			sf::Uint32 size;
		rpacket >> size;
		for (sf::Uint32 i = 0; i < size; ++i)
		{
			float item;
			rpacket >> item;
			if (i >= last)
			{
				positions.push_back(item);
				std::cout << item;

			}
		}
		last = size;
		std::cout << "---";
		int temp = (positions.size()) / 2;
		first.push_back(temp);

		count.push_back((first[first.size() - 1] - first[first.size() - 2]));
		}
		
		
		
	
		
		
	}
}
static void mouse_button_callback(GLFWwindow* window, int button, int action, int state)
{
	
	first.push_back((positions.size()) / 2);

	count.push_back((first[first.size() - 1] - first[first.size() - 2])); 
	
	
	

	next++;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//getting cursor position
		glfwGetCursorPos(window, &pressX, &pressY);
		std::cout << "Cursor Position at (" << pressX << " : " << pressY << std::endl;
		
		
	}
	
	
}

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
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragement") << std::endl;
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
int main()
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */

	window = glfwCreateWindow(1000, 500, "test Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl; return 2;
	}
	unsigned int buffer, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &buffer);
	glViewport(0, 0, 1000, 500);




	std::cout << "c or s?";
	char f;
	std::cin >> f;
	if (f == 's')
	{
		sf::TcpListener listener;
		

		listener.listen(53000, "10.100.60.49");
		

		listener.accept(client);
		std::thread worker(DoWork);



		worker.detach();


		while (true)
	{ 
			

		while (!glfwWindowShouldClose(window))
		{
			

			glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);



			glfwSetMouseButtonCallback(window, mouse_button_callback);
				




			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);

			int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
			if (state == GLFW_PRESS)
			{


				glfwGetCursorPos(window, &posX, &posY);
				positions.push_back((float)(-500 + posX) / 500);

				positions.push_back((float)(+250 - posY) / 250);

				std::cout << (float)(-500 + posX) / 500 << (float)(+250 - posY) / 250;





			}






			glBufferData(GL_ARRAY_BUFFER, (positions.size()) *(sizeof(float)), positions.data(), GL_STATIC_DRAW);


			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glBindVertexArray(0);





			shaderSource use = parseShader();
			glBindVertexArray(VAO);


			unsigned int shader = CreateShader(use.vertexshader, use.fragmentshader);

			glUseProgram(shader);
			int location = glGetUniformLocation(shader, "u_Color");
			ASSERT(location != -1);


			glUniform4f(location, 0.0f, 0.0f, 0.4f, 1.0f);
			glBindVertexArray(VAO);

			glPointSize(2);
			glLineWidth(6);
			glDrawArrays(GL_POINTS, 0, positions.size());


			glMultiDrawArrays(GL_LINE_STRIP, first.data(), count.data(), count.size());
			glBindBuffer(GL_ARRAY_BUFFER, 0);


			glBindVertexArray(0);








			glfwSwapBuffers(window);

			glfwPollEvents();




		}
	}
		



		

		glfwTerminate();




	}



	if (f == 'c')
	{
		
		
		sf::Socket::Status status = socket.connect("10.100.60.49", 53000);
		std::thread worker(DorWork);



		worker.detach();
		while(true)
		{
			
			while (!glfwWindowShouldClose(window))
			{
				

				glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);


				


				



				glBindVertexArray(VAO);
				glBindBuffer(GL_ARRAY_BUFFER, buffer);

				glBufferData(GL_ARRAY_BUFFER, (positions.size()) *(sizeof(float)), positions.data(), GL_STATIC_DRAW);


				glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glBindVertexArray(0);





				shaderSource use = parseShader();
				glBindVertexArray(VAO);


				unsigned int shader = CreateShader(use.vertexshader, use.fragmentshader);

				glUseProgram(shader);
				int location = glGetUniformLocation(shader, "u_Color");
				ASSERT(location != -1);


				glUniform4f(location, 0.0f, 0.0f, 0.4f, 1.0f);
				glBindVertexArray(VAO);

				glPointSize(2);
				glLineWidth(6);
				glDrawArrays(GL_POINTS, 0, positions.size());


				glMultiDrawArrays(GL_LINE_STRIP, first.data(), count.data(), count.size());
				glBindBuffer(GL_ARRAY_BUFFER, 0);


				glBindVertexArray(0);






				glfwSwapBuffers(window);

				glfwPollEvents();
			}
		}
		

				
		glfwTerminate();

			}




		





		}



	
