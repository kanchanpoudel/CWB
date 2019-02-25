#pragma once
#include<iostream>
#include<fstream>
#include<thread>
#include<sstream>
#include<string>
#include<vector>
#include<Network.hpp>
#include"..\include\mouse.h"
#include"..\include\DataBuffer.h"
#include"..\include\shader.h"
#include"..\include\Board.h"
using namespace std::literals::chrono_literals;


class Server
{   private:
	static sf::TcpSocket client;     //static beause SendingThread() uses that is a static method
	static sf::Packet spacket;       //static beause SendingThread() uses that is a static method
	static sf::TcpListener listener; //static beause SendingThread() uses that is a static method
	static int id;

	
	public:
		
		void connectToClient();
		static void SendingThread(); //static because it needs to be called by connectToClient
		void serverWindow(Board &,Buffer &,Mouse &, Shader &);
};
