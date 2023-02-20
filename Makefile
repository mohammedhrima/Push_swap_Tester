NAME= ./tester

ARG = ""
SRC = tester.c
LIB = ./Libft/libft.a

debug: clean
	@gcc $(SRC) $(LIB) -D TIMING=8000 -o tester
	@python3 number_generator.py
	@make fclean

tests: clean
	@gcc $(SRC) $(LIB) -D TIMING=1 -o tester
	@python3 number_generator.py
	@make fclean

	
clean:
	@$(RM) $(NAME) 

fclean: clean
re: clean all