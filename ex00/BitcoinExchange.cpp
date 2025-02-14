#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
	std::ifstream	database("data.csv");
	if (!database.is_open())
		throw NoDatabaseException();
	std::string	line;
	getline(database, line);
	if (line != "date,exchange_rate")
		throw NoDatabaseException();
	while (getline(database, line))
	{
		size_t	pos = line.find(',');
		if (pos == std::string::npos)
			throw NoDatabaseException();
		std::string	date = line.substr(0, pos);
		std::string	price = line.substr(pos + 1);
		double	priceInDouble = strtod(price.c_str(), NULL);
		_exchangeRate[date] = priceInDouble;
	}
	database.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src)
{
	*this = src;
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs)
{
	if (this != &rhs)
	{
		_exchangeRate = rhs._exchangeRate;
	}
	return *this;
}

void	BitcoinExchange::calculateValue(std::string inputLine)
{
	std::string	date;
	double		amount;
	double		price;

	/* check bad input */
	if (inputLine.length() < 14 || inputLine.find(" | ") == std::string::npos)
	{
		std::cout << "Error: bad input => " << inputLine << std::endl;
		return;
	}
	/* parse input date and amount */
	if (inputLine.length() >= 14)
	{
		date = inputLine.substr(0, 10);
		if (!isValidDate(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			return;
		}
		amount = strtod(inputLine.substr(13).c_str(), NULL);
		if (amount <= 0)
			std::cout << "Error: not a positive number => " << inputLine.substr(13) << std::endl;
		if (amount > 1000)
			std::cout << "Error: too large a number => " << inputLine.substr(13) << std::endl;
		if (amount <= 0 || amount > 1000)
			return;
	}
	/* find exchange rate for date */
	if (_exchangeRate.find(date) != _exchangeRate.end())
		price = _exchangeRate.at(date);
	else if (_exchangeRate.upper_bound(date) == _exchangeRate.end())
	{
		std::cout << "Error: date not found => " << date << std::endl;
		return;	
	}
	else
		price = (--_exchangeRate.upper_bound(date))->second;
	/* calculate value and print result */
	double	value = price * amount;
	std::cout << date << " => " << amount << " = " << value << std::endl;
}

bool	BitcoinExchange::isValidDate(std::string date)
{
	std::stringstream ss(date);
	int		year;
	char	dash1;
	int		month;
	char	dash2;
	int		day;
	if (!(ss >> year >> dash1 >> month >> dash2 >> day))
		return false;
	if (dash1 != '-' || dash2 != '-')
		return false;
	if (year < 2009 || month < 1 || month > 12 || day < 1 || day > 31)
		return false;
	int	daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (year % 4 == 0 && year % 100 != 0)
		daysInMonth[1] = 29;
	if (day > daysInMonth[month - 1])
		return false;
	return true;
}

const char*	BitcoinExchange::NoDatabaseException::what() const throw()
{
	return "Error: no database found. Pls, provide data.csv file ";
}