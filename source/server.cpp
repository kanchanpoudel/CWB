#include"..\include\server.h"


sf::TcpSocket Server:: client;
sf::Packet Server::spacket;
sf::TcpListener Server::listener;
int Server::id;
void Server::connectToClient()
{
	listener.listen(53000, "10.100.60.49");
	listener.accept(client);
	std::thread worker(SendingThread);



	worker.detach();

	
}
void Server::serverWindow(Board & win , Buffer & b, Mouse & mouse, Shader & s)
{
	while (win.windowState())
	{
		win.renderWindow();


		mouse.mouseButtonPressed(win.getWin());

		mouse.recordCursor(win.getWin());

		b.CreateBuffer(Board::positions);
		s.parseShader();
		s.ShaderProgram();
		win.DrawBoard(Board::positions, Board::first, Board::count);

		b.unBindvaBuffer();

		glfwSwapBuffers(win.getWin());

		glfwPollEvents();
	}


	glfwTerminate();

 }
void Server::SendingThread()
{

	std::cout << "started thread id-" << std::this_thread::get_id() << std::endl;


	while (true)
	{

		spacket.clear();

		if (id == Mouse::next)
		{


			spacket << static_cast<sf::Uint32>(Board::positions.size());
			for (std::vector<float>::const_iterator it = Board::positions.begin(); it != Board::positions.end(); ++it)
				spacket << *it;



			if (client.send(spacket) == sf::Socket::Done)
			{
				id += 2;
			}




		}

	}

}