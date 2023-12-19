NAME = philo

CC = cc

HEADDER = philo.h

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g

PTHREAD = -lpthread

SRC =	main.c \
		job_moniter.c \
		job_thread.c \
		job_thread_1.c \
		time_utils.c \
		utils.c \
		init.c
	 
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADDER)
	$(CC)  $(CFLAGS) $(PTHREAD) $(OBJ)  -o $(NAME)

	
clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
