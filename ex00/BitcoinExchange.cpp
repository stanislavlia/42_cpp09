#include "BitcoinExchange.hpp"

// Constructor, Destructor, Copy Constructor, Assignment Operator

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		_bitcoinPrices = src._bitcoinPrices;
	}
	return *this;
}

void BitcoinExchange::loadBitcoinPrice(const std::string &filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		throw std::runtime_error("Cannot open file");
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		std::istringstream iss(line);
		std::string date, valueStr;
		std::getline(iss, date, ',');
		std::getline(iss, valueStr);

		trim(date);
		trim(valueStr);

		double value = std::atof(valueStr.c_str());
		_bitcoinPrices[date] = value;
	}
	file.close();
}

double BitcoinExchange::getExchangeRate(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it = _bitcoinPrices.lower_bound(date);

	if (it != _bitcoinPrices.end() && it->first == date)
	{
		return it->second;
	}

	if (it == _bitcoinPrices.begin())
	{
		return it->second;
	}

	--it;
	return it->second;
}

void BitcoinExchange::processInput(const std::string &line)
{
	std::istringstream iss(line);
	std::string date, valueStr;
	std::getline(iss, date, '|');
	std::getline(iss, valueStr);

	trim(date);
	trim(valueStr);

	if (!isDateValid(date))
	{
		std::cerr << "Error: bad input => " << date << std::endl;
		return;
	}

	double value = std::atof(valueStr.c_str());
	if (value > 1000)
	{
		std::cerr << "Error: too large of a number." << std::endl;
		return;
	}
	if (!isValueValid(valueStr))
	{

		std::cerr << "Error: not a positive number." << std::endl;
		return;
	}

	try
	{
		double exchangeRate = getExchangeRate(date);
		std::cout << date << " => " << value << " = " << value * exchangeRate << std::endl;
	}
	catch (const std::runtime_error &e)
	{
		std::cerr << e.what() << std::endl;
	}
}

bool BitcoinExchange::isDateValid(const std::string &date)
{
	if (date.length() != 10 || date[4] != '-' || date[7] != '-')
	{
		return false;
	}
	for (int a = 0; a < 10; ++a)
	{
		if (a == 4 || a == 7)
			continue;
		if (!std::isdigit(date[a]))
			return false;
	}
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if (year < 0 || month < 1 || month > 12 || day < 1)
	{
		return false;
	}
	int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
	{
		daysInMonth[1] = 29;
	}
	if (day > daysInMonth[month - 1])
	{
		return false;
	}
	return true;
}

bool BitcoinExchange::isValueValid(const std::string &value)
{
	char *end;
	double val = std::strtod(value.c_str(), &end);
	return (*end == '\0' && val >= 0 && val <= 1000);
}

//removes spaces from start and end
void BitcoinExchange::trim(std::string &str)
{
	size_t first = str.find_first_not_of(' ');
	if (first == std::string::npos)
	{
		str.clear();
		return;
	}
	size_t last = str.find_last_not_of(' ');
	str = str.substr(first, last - first + 1);
}