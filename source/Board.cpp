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
void Board::initGLFW()
{
	glfwInit();
}

void Board::RenderBoard()
{
	window = glfwCreateWindow(1000, 500, "test Window", NULL, NULL);
	glfwMakeContextCurrent(window);
	
}
GLFWwindow* Board::getWin()
{
	return window;
}
void Board::renderWindow()
{
	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Board::DrawBoard(std::vector<float> & positions, std::vector<int> & first, std::vector<int> & count)
{
	glPointSize(0.1);
	glLineWidth(6);
	glDrawArrays(GL_POINTS, 0, positions.size());
	glMultiDrawArrays(GL_LINE_STRIP, first.data(), count.data(), count.size());
}
 