#include"..\include\mouse.h"
void Mouse:: mouse_button_callback(GLFWwindow* window, int button, int action, int state) 
{

	Board::first.push_back((Board::positions.size()) / 2);

	Board::count.push_back((Board::first[Board::first.size() - 1] - Board::first[Board::first.size() - 2]));




	next++;
	
}
	void Mouse:: mouseButtonPressed(GLFWwindow* win)
	{
		glfwSetMouseButtonCallback(win, mouse_button_callback);
	}
	int Mouse::next;
	void Mouse::recordCursor(GLFWwindow* win)
	{
		int state = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT);
		if (state == GLFW_PRESS)
		{


			glfwGetCursorPos(win, &posX, &posY);
			Board::positions.push_back((float)(-500 + posX) / 500);

			Board::positions.push_back((float)(+250 - posY) / 250);

			std::cout << (float)(-500 + posX) / 500 << (float)(+250 - posY) / 250;


		}
	}

