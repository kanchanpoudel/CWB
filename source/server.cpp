
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
		char ans = 'y';
		if (listener.listen(53000, "10.100.60.49") != sf::Socket::Done)
		{
			std::cout << "Hi";
		}

		// accept a new connection
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "Hi2";

		}
		while (true)
		{
			sf::Packet packet;
			std::vector<sf::Int16> data, sdata;
			std::cout << "write";
			sf::Int16 x;



			std::cin >> x;
			packet << x;
			//sdata.push_back(x);

			if (client.send(packet) != sf::Socket::Done)
			{
				std::cout << "error sending";
			}

			/*packet << static_cast<sf::Uint32>(sdata.size());
			for (std::vector<sf::Int16>::const_iterator it = sdata.begin(); it != sdata.end(); ++it)
				packet << *it;

			
			std::cout << "y/n" << std::endl;
			std::cin >> ans;
			*/
		}
	}
		

		
	if (f == 'c')
	{
		char ans = 'y';
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect("10.100.60.49", 53000);
		if (status != sf::Socket::Done)
		{
			std::cout << "Hi3";
		}
		sf::Packet packet;
		std::vector<sf::Int16> data, sdata;
		
		while (true)
		{
			if (socket.receive(packet) == sf::Socket::Done)
			{
				sf::Int16 x;
				packet >> x;
				std::cout<< x;
				/*sf::Uint32 size;
				packet >> size;
				for (sf::Uint32 i = 0; i < size; ++i)
				{
					sf::Int16 item;
					packet >> item;
					std::cout << item;
					data.push_back(item);
				}
				std::ofstream output_file("client.txt");
				std::ostream_iterator<sf::Int16> output_iterator(output_file, "\n");
				std::copy(data.begin(), data.end(), output_iterator);
				*/
			}

			
			
			
		}
		

	}



}