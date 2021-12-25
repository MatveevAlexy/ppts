all: l1_misses.c l2_misses.c c1_misses.c c2_misses.c s1_misses.c s2_misses.c 
	gcc l1_misses.c -Wall -Werror -O0 -o l1 -lpapi -I/usr/papi -L/usr/papi
	gcc l2_misses.c -Wall -Werror -O0 -o l2 -lpapi -I/usr/papi -L/usr/papi
	gcc c1_misses.c -Wall -Werror -O0 -o c1 -lpapi -I/usr/papi -L/usr/papi
	gcc c2_misses.c -Wall -Werror -O0 -o c2 -lpapi -I/usr/papi -L/usr/papi
	gcc s1_misses.c -Wall -Werror -O0 -o s1 -lpapi -I/usr/papi -L/usr/papi
	gcc s2_misses.c -Wall -Werror -O0 -o s2 -lpapi -I/usr/papi -L/usr/papi

test:
	gcc l1_misses.c -Wall -Werror -O0 -o l1 -lpapi -I/usr/papi -L/usr/papi -fsanitize=address
	gcc l2_misses.c -Wall -Werror -O0 -o l2 -lpapi -I/usr/papi -L/usr/papi -fsanitize=address
	gcc c1_misses.c -Wall -Werror -O0 -o c1 -lpapi -I/usr/papi -L/usr/papi -fsanitize=address
	gcc c2_misses.c -Wall -Werror -O0 -o c2 -lpapi -I/usr/papi -L/usr/papi -fsanitize=address
	gcc s1_misses.c -Wall -Werror -O0 -o s1 -lpapi -I/usr/papi -L/usr/papi -fsanitize=address
	gcc s2_misses.c -Wall -Werror -O0 -o s2 -lpapi -I/usr/papi -L/usr/papi -fsanitize=address
	sh test.sh
