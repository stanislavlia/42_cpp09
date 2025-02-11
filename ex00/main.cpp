#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		std::cerr << "Incorrent number of arguments!!!!!" << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange btcExchange;
		btcExchange.loadBitcoinPrice("data.csv");

		std::ifstream inputFile(argv[1]);
		if (!inputFile.is_open())
		{
			std::cerr << "Error: Could not open file" << std::endl;
			return 1;
		}

		std::string line;
		std::getline(inputFile, line);
		if (line.empty() && inputFile.eof())
		{
			std::cerr << "Error: Empty file" << std::endl;
			return 1;
		}
		while (std::getline(inputFile, line))
		{
			btcExchange.processInput(line);
		}

		inputFile.close();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}