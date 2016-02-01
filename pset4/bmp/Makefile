all: resize whodunit

resize: resize.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o resize resize.c

whodunit: whodunit.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o whodunit whodunit.c

clean:
	rm -f *.o a.out core whodunit resize