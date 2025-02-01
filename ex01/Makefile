NAME = RPN

CC = c++
MAND = main.cpp RPN.cpp
MAND_OBJS = $(MAND:%.cpp=%.o)
FLAGS = -std=c++98 -Wall -Werror -Wextra -g -fsanitize=address

all : $(NAME)

$(NAME) : $(MAND_OBJS)
	$(CC) $(FLAGS) $^ -o $@

%.o : %.cpp RPN.hpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(MAND_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all