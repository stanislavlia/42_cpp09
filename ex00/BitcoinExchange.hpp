
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <fstream>
# include <map>
# include <iostream>
# include <cstdlib>
# include <sstream>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_exchangeRate;

	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& src);
		~BitcoinExchange();
		
		BitcoinExchange&	operator=(const BitcoinExchange& rhs);
		void				calculateValue(std::string inputLine);
		bool				isValidDate(std::string date);

		class NoDatabaseException : public std::exception
		{
			const char*	what() const throw();
		};
};

#endif