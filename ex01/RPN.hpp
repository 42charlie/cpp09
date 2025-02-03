#include <iostream>
#include <sstream>
#include <string>
#include <stack>

#ifndef _RPN_
#define _RPN_

class RPN{
	private:
		static std::stack<int> stack;

		RPN(void);
		RPN(const RPN &copy);
		RPN &operator=(const RPN &copy);
		~RPN(void);
	public:
		static int	processRPNLine(char *line);
		static void	executeOperation(char operation);
		static void	setNumbers(int *nbr1, int *nbr2);
};

#endif