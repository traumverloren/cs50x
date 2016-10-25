#
# Makefile
#
# Computer Science 50
# Problem Set 6
#

server: server.c Makefile
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o server server.c -lm

clean:
	rm -f *.o core server



lookuptest: lookuptest.c Makefile
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -lcs50 -o lookuptest lookuptest.c -lm

parsetest: parsetest.c Makefile
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -lcs50 -o parsetest parsetest.c -lm
