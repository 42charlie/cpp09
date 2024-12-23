#include <stack>
#include <iostream>
#ifndef _RPN_
#define _RPN_

class RPN{
	static std::stack<int> seq;
	public:
		static int	calculate(char *line);
		static void	exec(char operation);
};

#endif