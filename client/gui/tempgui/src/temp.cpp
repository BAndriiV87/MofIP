#include "temp.hpp"

#include <iostream>
#include <chrono>
#include <thread>

namespace tempgui {

	void Temp::number() {
		std::cout << "wait 5 second ";
		for (int i = 0; i < 5; ++i) {
			std::cout << ".";
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		std::cout << std::endl;
	}

}