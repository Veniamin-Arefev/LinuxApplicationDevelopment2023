EXECUTABLE = esub
CC= gcc
TRASH = *.o *.out *.true temp
CFLAGS = -Wall -Werror -fPIC -O0 -g

all: $(EXECUTABLE)

test: $(EXECUTABLE)
	@./$(EXECUTABLE) a+ lala 123aaabcdefg > 1.out
	@echo "123aaabcdefg" > temp
	@sed -E s/a+/lala/ temp > 1.true

	@./$(EXECUTABLE) a+ \\0 123aaabcdefg > 2.out
	@echo "123aaabcdefg" > temp
	@sed -E s/a+/\\0/ temp > 2.true


	@if cmp -s 1.out 1.true && cmp -s 2.out 2.true ; then \
		echo TEST SUCCESS; \
	fi

clean:
	rm -rf $(EXECUTABLE) $(TRASH)
