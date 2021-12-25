all: problem3.c
	gcc problem3.c -Wall -Werror -O0 -o problem3 -fopenmp
    
test:
	gcc problem3.c -Wall -Werror -O0 -o problem3 -fopenmp -fsanitize=address
	sh test.sh
