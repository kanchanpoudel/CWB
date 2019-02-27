#include"..\include\Board.h"
#include"..\include\imguiIncludes\menu.h"
std::vector<float>Board::positions;
std::vector<int>Board::first;
std::vector<int>Board::count;
bool Board::windowState()
{
	if (!glfwWindowShouldClose(window))
		return true;
	else
		return false;

}
int Board::GladLoader()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

}
Board::Board(const int width, const int height, const std::string name)
{
	SCREEN_WIDTH=width;
	SCREEN_HEIGHT=height;
	board_name=name;
	line_width = 4;
}

void Board::initGLFW()
{
	glfwInit();
}

void Board::MakeWindow()
{
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, board_name.c_str(), NULL, NULL);
	glfwMakeContextCurrent(window);
	
}
GLFWwindow* Board::getWin()
{
	return window;
}
void Board::renderWindow()
{
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(menu::clear_color.x, menu::clear_color.y, menu:: clear_color.z, menu::clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Board::DrawCalls(std::vector<float> & positions, std::vector<int> & first, std::vector<int> & count)
{
	glPointSize(0.1);
	glLineWidth(line_width);
	glDrawArrays(GL_POINTS, 0, positions.size());
	glMultiDrawArrays(GL_LINE_STRIP, first.data(), count.data(), count.size());
}
void Board::SetMatrices()
{
	glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 }