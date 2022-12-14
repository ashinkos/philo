NAME= philo

SRC = philo.c fill_arguments.c philo_utils.c stop_philos.c\

CC = cc
FLAGS= -Wall -Werror -Wextra -g3 
PARA  = -c 

OBJ= $(SRC:.c=.o)

%.o : %.c 
	$(CC) $(PARA) $(FLAGS) $<  -o $@

all: $(NAME)
	
$(NAME): $(OBJ)
		${CC} $(OBJ) $(FLAGS) -o ${NAME}

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all