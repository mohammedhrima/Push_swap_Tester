NAME= ./tester

SRC = tester.c
LIB = ./Libft/libft.a
T = 5000

$(NAME): $(SRC)
	gcc $(SRC) $(LIB) -D TIMING=$(T) -o tester

all:$(NAME)

nums:
	@python3 number_generator.py


clean:
	@$(RM) $(NAME) 

fclean: clean
re: clean all