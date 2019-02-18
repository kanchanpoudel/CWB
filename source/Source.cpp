#include<iostream>
#include<thread>
#include<vector>
static bool s_Finished = false;
static int x;
void DoWork()
{
	using namespace std::literals::chrono_literals;
	std::cout << "started thread id-" << std::this_thread::get_id() << std::endl;
	while (true)
	{
		

		//std::this_thread::sleep_for(1s);
	}
}
int main()
{
	std::thread worker(DoWork);
	std::cin.get();
	
	std::cout << x;
	
	worker.join();
	std::cout << "Finished" << std:: endl;
	std::cout << "started thread id-" << std::this_thread::get_id() << std::endl;
	std::cin.get();
}
