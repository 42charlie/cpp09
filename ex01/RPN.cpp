#include "RPN.hpp"

std::stack<int, std::list<int> > RPN::stack;

int RPN::processRPNLine(char *line)
{
	std::string			_char;
	std::stringstream	ss(line);

	while (ss.eof() == false)
	{
		getline(ss, _char, ' ');
		if ( _char.size() == 1 && std::strchr("+*-/", _char[0]) != NULL )
			executeOperation(_char[0]);
		else if (_char == "")
			;
		else
			insertNumber(_char);
	}
	if (stack.size() != 1)
		throw std::invalid_argument("Error");
	return (stack.top());
}

void RPN::insertNumber(std::string &_char)
{
	int					number;
	char				*delimiter;

	number = std::strtod(_char.c_str() , &delimiter);
	if ( *delimiter != '\0' || labs(number) >= 10 || _char.find('.') != std::string::npos )
		throw std::invalid_argument("Error: Invalid number format. Expected a valid integer value");
	else
		stack.push(number);
}

void RPN::executeOperation(char operation)
{
	int nbr1;
	int nbr2;

	setNumbers(&nbr1, &nbr2);
	switch (operation)
	{
		case '+':
			stack.push(nbr1 + nbr2);
			break;
		case '-':
			stack.push(nbr1 - nbr2);
			break;
		case '*':
			stack.push(nbr1 * nbr2);
			break;
		case '/':
			if (nbr2 == 0)
				throw std::runtime_error("Error : Division by zero!");
			stack.push(nbr1 / nbr2);
	}
}

void RPN::setNumbers(int *nbr1, int *nbr2)
{
	if (stack.size() < 2)
		throw std::invalid_argument("Error");
	*nbr2 = stack.top();
	stack.pop();
	*nbr1 = stack.top();
	stack.pop();
}

RPN::RPN(void)
{
	;
}
RPN::RPN(const RPN &copy)
{
	(void)copy;
}
RPN &RPN::operator=(const RPN &copy)
{
	(void)copy;
	return (*this);
}
RPN::~RPN(void)
{
	;
}