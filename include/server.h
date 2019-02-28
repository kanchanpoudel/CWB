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
#include "../../include/imguiIncludes/menu.h"
using namespace std::literals::chrono_literals;


class Server
{   private:
	static sf::TcpSocket client;     
	static sf::Packet spacket;       
	static sf::TcpListener listener; 
	static int id;

	
	public:
		static bool mouseBlock;
		void connectToClient();
		static void SendingThread(); 
		int serverWindow(ImGui1&, Board &,Buffer &,Mouse &, Shader &);
};
