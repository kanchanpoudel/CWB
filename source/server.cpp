
#include<iostream>
#include<fstream>
#include<Network.hpp>
#include<string>
	

	


int main()
{

	std::cout << "c or s?";
	char f;
	std::cin >> f;
	if (f == 's')
	{
		sf::TcpListener listener;

		if (listener.listen(53000,"10.100.60.49") != sf::Socket::Done)
		{
			std::cout << "Hi";
		}

		// accept a new connection
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "Hi2";

		}
		sf::Packet packet;
		std::vector<sf::Int16> data, sdata;
		std::cout << "write";
		sf::Int16 x;
		char ans = 'y';
		while (ans == 'y')
		{
			
			std::cin >> x;
			sdata.push_back(x);
			std::cout << "y/n";
			std::cin >> ans;
		}
			
		packet << static_cast<sf::Uint32>(sdata.size());
		for (std::vector<sf::Int16>::const_iterator it = sdata.begin(); it != sdata.end(); ++it)
			packet << *it;

		if (client.send(packet) != sf::Socket::Done)
		{
			std::cout << "error sending";
		}
		std::size_t received;

		// TCP socket:
		if (client.receive(packet) != sf::Socket::Done)
		{
			// error...
		}
		
		sf::Uint32 size;
		packet >> size;
		for (sf::Uint32 i = 0; i < size; ++i)
		{
			sf::Int16 item;
			packet >> item;
			data.push_back(item);
		}
		std::ofstream output_file("./server.txt");
		std::ostream_iterator<sf::Int16 > output_iterator(output_file, "\n");
		std::copy(data.begin(), data.end(), output_iterator);
		
	}
	if(f=='c')
	{sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect("10.100.60.49", 53000);
	if (status != sf::Socket::Done)
	{
		std::cout << "Hi3";
	}
	sf::Packet packet;
	std::vector<sf::Int16> data, sdata;
	std::cout << "write";
	sf::Int16 x;
	char ans = 'y';
	while (ans == 'y')
	{

		std::cin >> x;
		sdata.push_back(x);
		std::cout << "y/n";
		std::cin >> ans;
	}
	packet << static_cast<sf::Uint32>(sdata.size());
	for (std::vector<sf::Int16>::const_iterator it = sdata.begin(); it != sdata.end(); ++it)
		packet << *it;
	
	
	if (socket.send(packet) != sf::Socket::Done)
	{
		std::cout << "error sending";
	}
	std::size_t received;

	// TCP socket:
	if (socket.receive(packet) != sf::Socket::Done)
	{
		// error...
	}
	
	sf::Uint32 size;
	packet >> size;
	for (sf::Uint32 i = 0; i < size; ++i)
	{
		sf::Int16 item;
		packet >> item;
		data.push_back(item);
	}
	std::ofstream output_file("client.txt");
	std::ostream_iterator<sf::Int16> output_iterator(output_file, "\n");
	std::copy(data.begin(), data.end(), output_iterator);

	
	}
	
	
	
}
