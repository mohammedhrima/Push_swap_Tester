NAME= ./tester

SRC = tester.c
LIB = ./Libft/libft.a
T = 100

$(NAME):
	gcc $(SRC) $(LIB) -D TIMING=$(T) -o tester

all:$(NAME)

clean:
	@$(RM) $(NAME) 

fclean: clean
re: clean all