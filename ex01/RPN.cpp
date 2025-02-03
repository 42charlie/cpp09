#include "RPN.hpp"

std::stack<int> RPN::stack;

int RPN::processRPNLine(char *line)
{
	std::string _char;
	std::stringstream ss(line);

	while (ss.eof() == false)
	{
		getline(ss, _char, ' ');
		if (_char.size() != 1)
			throw std::invalid_argument("Error");
		else if (isdigit(_char[0]))
			stack.push(_char[0] - 48);
		else
			executeOperation(_char[0]);
	}
	if (stack.size() != 1)
		throw std::invalid_argument("Error");
	std::cout << stack.top() << "\n";
	return (0);
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
			break;
		default:
			throw std::invalid_argument("Error");
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