EXECUTABLE = range
CC= gcc
TRASH = *.o *.out
CFLAGS = -Wall -Werror -fPIC -O0 -g

all: $(EXECUTABLE)

test: $(EXECUTABLE)
	@gdb --batch --quiet --command=gdb1 --args ./$(EXECUTABLE) | grep '^@@@' > 1.out
	@gdb --batch --quiet --command=gdb2 --args ./$(EXECUTABLE) | grep '^@@@' > 2.out

	@if cmp -s 1.out 1.true && cmp -s 2.out 2.true; then \
		echo TEST SUCCESS; \
	fi

clean:
	rm -rf $(EXECUTABLE) $(TRASH)
