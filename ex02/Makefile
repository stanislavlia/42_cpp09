NAME			= PmergeMe

CC				= c++

RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror -std=c++98

HEADERS			=	PmergeMe.hpp

SRCS			=	main.cpp
					

OBJS			= $(SRCS:.cpp=.o)

%.o: %.cpp $(HEADERS)
		${CC} ${CFLAGS} -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS) $(HEADERS)
				$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re