#include "RPN.hpp"
#include <string>
#include <sstream>

std::stack<int> RPN::seq;

int RPN::calculate(char *line)
{
	std::string c;
	std::stringstream ss(line);
	std::string oper("+-/*");

	while (ss.eof() == false)
	{
		getline(ss, c, ' ');
		if (c.size() == 1 && oper.find(c[0]) != std::string::npos)
			exec(c[0]);
		else if (c.size() == 1 && isdigit(c[0]))
			seq.push(c[0] - 48);
		else
			throw std::invalid_argument("Error");
	}
	if (seq.size() != 1)
		throw std::invalid_argument("Error");
	std::cout << seq.top() << "\n";
	return (0);
}

void RPN::exec(char operation)
{
	int nbr1;
	int nbr2;

	if (seq.size() < 2)
		throw std::length_error("Error");
	nbr2 = seq.top();
	seq.pop();
	nbr1 = seq.top();
	seq.pop();
	switch (operation)
	{
		case '+':
			seq.push(nbr1 + nbr2);
			break;
		case '-':
			seq.push(nbr1 - nbr2);
			break;
		case '*':
			seq.push(nbr1 * nbr2);
			break;
		case '/':
			seq.push(nbr1 / nbr2);
			break;
	}
}
