#include<thread>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<Network.hpp>
#include<time.h>
int main()
{
	sf::Packet packet;
	std::cout << "c or s";
	char f;
	std::cin >> f;
	if (f == 's')
	{
		sf::TcpListener listener;
		listener.setBlocking(false);

		std::vector<sf::TcpSocket *> clients;
		listener.listen(53000, "10.100.60.49");
		time_t endwait;
		int seconds = 40;

		endwait = time(NULL) + seconds;
		
		while (time(NULL) < endwait)
		{
			sf::TcpSocket* client = new sf::TcpSocket;
			client->setBlocking(false);
			if (listener.accept(*client) == sf::Socket::Done)
			{
				std::cout << "New Connection" << std::endl;
				clients.push_back(client);
			}
		}
		
		int x = 4;
		packet <<x;
		for (int i = 0; i < clients.size(); ++i)
			clients[i]->send(packet);

	}
	if (f == 'c')
	{
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect("10.100.60.49", 53000);
		socket.receive(packet);
		int x;
		packet >>x;
		std::cout << x;
		std::cin.get();
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