#include<..\..\server.h>
#include<iostream>
#include<string>

int main()
{
	sf::TcpSocket socket;
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
}