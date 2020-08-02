warnings_BAD: *.c
	gcc -Werror -Wall -g -std=gnu99 -o a4 *.c -lrt -lpthread
warnings_OK: *.c
	gcc -Wall -g -std=gnu99 -o a4 *.c -lrt -lpthread
clean: *.c
	rm a4
