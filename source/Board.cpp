#include"..\include\Board.h"
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
	
	glClear(GL_COLOR_BUFFER_BIT);
}
void Board::DrawCalls(std::vector<float> & positions, std::vector<int> & first, std::vector<int> & count)
{
	glPointSize(0.1);
	glLineWidth(line_width);
	glDrawArrays(GL_POINTS, 0, positions.size());
	glMultiDrawArrays(GL_LINE_STRIP, first.data(), count.data(), count.size());
}
 