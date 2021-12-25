all: problem1.c
	gcc problem1.c -Wall -Werror -O0 -o problem1
    
test:
	gcc -Wall -Werror -O0 -o problem1 problem1.c -fsanitize=address
	sh test.sh
