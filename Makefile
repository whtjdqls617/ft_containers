CC = c++
CFLAGS = -Wall -Wextra -Werror
NAME = ft_containers
SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	${CC} $(CFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

clean:
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

re: 	fclean all

.PHONY: all clean fclean re