all: problem0.c
	gcc problem0.c -Wall -pedantic -O2 -pthread -o a
    
test:
	gcc -Wall -pedantic -O2 -pthread -o a problem0.c -fsanitize=address
	sh test.sh
