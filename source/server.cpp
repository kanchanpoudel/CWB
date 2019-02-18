#include<windows.h>
#include<iostream>
#include<fstream>
#include<Network.hpp>
#include<string>
#include<thread>
static bool s_Finished = false;
static sf::Int16 x;
static sf::Packet packet;
static sf::TcpSocket client; 

using namespace std::literals::chrono_literals;
static std::vector<sf::Int16> data;
void DoWork()
{
	
	std::cout << "started thread id-" << std::this_thread::get_id() << std::endl;
	while (true)
	{
		if (client.send(packet) != sf::Socket::Done)
		{
			std::cout << "error sending";
		}


		std::this_thread::sleep_for(1s);
	}
}





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

		if (listener.accept(client) != sf::Socket::Done)
		{
			std::cout << "Hi2";

		}

		std::thread worker(DoWork);



		worker.detach();

		while (true)
		{

			
			



			std::cin >> x;
			packet << x;
			//sdata.push_back(x);


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
		sf::Packet rpacket;
		std::vector<sf::Int16> rdata;
		{
			
			while (true)

			{
				if (socket.receive(rpacket) == sf::Socket::Done)
				{

					sf::Uint32 size;
					rpacket >> size;
					for (sf::Uint32 i = 0; i < size; ++i)
					{
						sf::Int16 item;
						rpacket >> item;
						
						rdata.push_back(item);
					}
					
					//for (int i = 0; i < rdata.size(); ++i)

						//std::cout << rdata[i];
				}
				

			}
		}


	}
}