PROGRAM_NAME = prog
STATIC_NAME = prog-a
STATIC_OUT_PREFIX = _static
DYNAMIC_NAME =  prog-so
DYNAMIC_OUT_PREFIX = _dynamic
EXECUTABLES = $(PROGRAM_NAME) $(STATIC_NAME) $(DYNAMIC_NAME)
GENERATES = $(EXECUTABLES) liboutput_static.a liboutput.so
CC= gcc
TRASH = *.o *.out
CFLAGS = -Wall -Werror -fPIC
PARAMS_ZERO =
PARAMS_ONE = First
PARAMS_TWO = First Second

all: $(EXECUTABLES)

$(PROGRAM_NAME): const.o fun.o prog.o

$(STATIC_NAME): prog.o liboutput_static.a
	$(CC) -L. $(filter %.o,$^) $(patsubst lib%.a,-l%,$(filter %.a,$^)) -o $@

$(DYNAMIC_NAME): prog.o liboutput.so
	$(CC) -L. $(filter %.o,$^) $(patsubst lib%.so,-l%,$(filter %.so,$^)) -o $@

liboutput_static.a:	const.o fun.o
	ar -rcs $@ $^

liboutput.so: const.o fun.o
	$(CC)  -shared $^ -o $@

test: test_zero test_one test_two

test_zero: all
	@./$(PROGRAM_NAME) $(PARAMS_ZERO) > $@.out 2> /dev/null
	@./$(STATIC_NAME) $(PARAMS_ZERO) > $@$(STATIC_OUT_PREFIX).out 2> /dev/null
	@LD_LIBRARY_PATH=`pwd` ./$(DYNAMIC_NAME) $(PARAMS_ZERO) > $@$(DYNAMIC_OUT_PREFIX).out 2> /dev/null

	@if cmp -s $@.out $@$(STATIC_OUT_PREFIX).out && cmp -s $@.out $@$(DYNAMIC_OUT_PREFIX).out; then \
		echo TEST 0 DONE; \
	fi

test_one:
	@./$(PROGRAM_NAME) $(PARAMS_ONE) > $@.out 2> /dev/null
	@./$(STATIC_NAME) $(PARAMS_ONE) > $@_static.out 2> /dev/null
	@LD_LIBRARY_PATH=`pwd` ./$(DYNAMIC_NAME) $(PARAMS_ONE) > $@_dynamic.out 2> /dev/null

	@if cmp -s $@.out $@$(STATIC_OUT_PREFIX).out && cmp -s $@.out $@$(DYNAMIC_OUT_PREFIX).out; then \
		echo TEST 1 DONE; \
	fi

test_two:
	@./$(PROGRAM_NAME) $(PARAMS_TWO) > $@.out 2> /dev/null
	@./$(STATIC_NAME) $(PARAMS_TWO) > $@_static.out 2> /dev/null
	@LD_LIBRARY_PATH=`pwd` ./$(DYNAMIC_NAME) $(PARAMS_TWO) > $@_dynamic.out 2> /dev/null

	@if cmp -s $@.out $@$(STATIC_OUT_PREFIX).out && cmp -s $@.out $@$(DYNAMIC_OUT_PREFIX).out; then \
		echo TEST 2 DONE; \
	fi


clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)