#include<thread>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<Network.hpp>
#include<time.h>
int main()
{
	sf::TcpSocket tcpSocket;
	tcpSocket.setBlocking(false);

	sf::TcpListener listener;
	listener.setBlocking(false);
	
	std::vector<sf::TcpSocket> clients;
	listener.listen(53000, "10.100.60.49");
	while (true)
	{
		sf::TcpSocket* client = new sf::TcpSocket;
		client->setBlocking(false);
		if (listener.accept(*client) == sf::Socket::Done)
		{
			std::cout << "New Connection" << std::endl;
			clients.push_back(*client);
		}
	}

	/*if (selector.wait())
	{
		if (selector.isReady(listner))
		{
			sf::TcpSocket* client = new sf::TcpSocket;
			if (listner.accept(*client) == sf::Socket::Done)
			{
				std::cout << "New Connection" << std::endl;
				clients.push_back(*client);
				selector.add(*client);
			}
			else
				delete client;
		}
		else
			for (std::vector<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
				sf::TcpSocket & client = **it;
		if (selector.isReady(*client))
		{
			std::string message[100];
			std::size_t size;
			if(client.recieve)
		}
	}*/
	return 0;
}