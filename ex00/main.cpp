#include <iostream>
#include <fstream>
#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		std::ifstream	file(av[1]);
		if (!file.is_open())
			std::cerr << "Error: could not open file." << std::endl;
		else
		{
			try
			{
				BitcoinExchange btc;
				std::string		line;
				getline(file, line);
				if (line != "date | value")
				{
					std::cerr << "Error: wrong input format." << std::endl;
					return 0;
				}
				while (getline(file, line))
					btc.calculateValue(line);
				file.close();
			}
			catch (const std::exception& e)
			{
				std::cerr << e.what() << std::endl;
			}
		}
	}
	else
		std::cout << "Usage: ./btc [input_database]" << std::endl;
	return 0;
}