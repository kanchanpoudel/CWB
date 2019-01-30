#include<..\..\server.h>
#include<iostream>
#include<fstream>
int main()
{

	std::cout << "c or s?";
	char f;
	std::cin >> f;
	if (f == 's')
	{
		sf::TcpListener listener;

		if (listener.listen(53000) != sf::Socket::Done)
		{
			std::cout << "Hi";
		}

		// accept a new connection
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "Hi2";

		}
		char data[100] = "I'm server";


		if (client.send(data, 100) != sf::Socket::Done)
		{
			std::cout << "error sending";
		}
		std::size_t received;

		// TCP socket:
		if (client.receive(data, 100, received) != sf::Socket::Done)
		{
			// error...
		}
		std::cout << "Received " << received << " bytes" << std::endl;
		std::ofstream myfile;
		myfile.open("server.txt");
		myfile << data;
	}
	if(f=='c')
	{sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("10.100.60.141", 53000);
	if (status != sf::Socket::Done)
	{
		std::cout << "Hi3";
	}
	char data[100] = "I'm clent";

	
	if (socket.send(data, 100) != sf::Socket::Done)
	{
		std::cout << "error sending";
	}
	std::size_t received;

	// TCP socket:
	if (socket.receive(data, 100, received) != sf::Socket::Done)
	{
		// error...
	}
	std::cout << "Received " << received << " bytes" << std::endl;
	std::ofstream myfile;
	myfile.open("client.txt");
	myfile << data;

	}
	
	
	
}