#include<..\..\server.h>
#include<iostream>
int main()
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
	
}