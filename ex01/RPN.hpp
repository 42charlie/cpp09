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
		static int	calculate(char *line);
		static void	exec(char operation);
};

#endif