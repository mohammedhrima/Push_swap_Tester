NAME= ./tester

SRC = tester.c
LIB = ./Libft/libft.a
T = 5000

$(NAME):
	gcc $(SRC) $(LIB) -D TIMING=$(T) -o tester

all:$(NAME)

clean:
	@$(RM) $(NAME) 

fclean: clean
re: clean all