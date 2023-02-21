SRC = tester.c
LIB = ./Libft/libft.a

debug:
	@sh check_python.sh
	@rm -rf tester
	@gcc $(SRC) $(LIB) -D TIMING=8000 -o tester
	@python3 number_generator.py

tests:
	@sh check_python.sh
	@rm -rf tester
	@gcc $(SRC) $(LIB) -D TIMING=1 -o tester
	@python3 number_generator.py
