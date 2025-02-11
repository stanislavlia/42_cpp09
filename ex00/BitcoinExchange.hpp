#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <map>

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange &operator=(const BitcoinExchange &src);
		~BitcoinExchange();

		void loadBitcoinPrice(const std::string &filename);
		double getExchangeRate(const std::string &date) const;
		void processInput(const std::string &line);

	private:
		std::map<std::string, double> _bitcoinPrices;
		bool isDateValid(const std::string &date);
		bool isValueValid(const std::string &value);
		static void trim(std::string &str);
};

#endif