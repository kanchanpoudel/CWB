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


class Client
{
private:
	static sf::TcpSocket socket;
	static sf::Packet rpacket;
	static sf::Uint32 last;


public:

	void connectToServer();
	static void RecievingThread();
	void clientWindow(Board &, Buffer &, Shader &);
};