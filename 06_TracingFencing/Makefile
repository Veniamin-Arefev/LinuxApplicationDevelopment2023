EXECUTABLE= move
SHARED= protect
FUNCTION_NAME=check
CC= gcc
TRASH = *.o in out o *.so in_PROTECT_lalala
CFLAGS = -Wall -Werror -fPIC -O0 -g

all: $(EXECUTABLE)

file_prep:
	@dd if=/dev/random of=in bs=32000 count=1 2> /dev/null
	@rm -f out

test1: $(EXECUTABLE) file_prep
	@strace -foo -e fault=openat:error=EPERM:when=1 -y -P in -P out ./move in out > /dev/null 2>&1;:
	@if test -f in && ! test -f out ; then \
		echo $@ SUCCESS; \
  	else \
  	  	echo $@ FAILED; \
	fi

test2: $(EXECUTABLE) file_prep
	@strace -foo -e fault=openat:error=EPERM:when=2 -y -P in -P out ./move in out > /dev/null 2>&1;:
	@if test -f in && ! test -f out ; then \
		echo $@ SUCCESS; \
  	else \
  	  	echo $@ FAILED; \
	fi

test3: $(EXECUTABLE) file_prep
	@strace -foo -e fault=read:error=EINTR:when=2 -y -P in -P out ./move in out > /dev/null 2>&1;:
	@if test -f in && ! test -f out ; then \
		echo $@ SUCCESS; \
  	else \
  	  	echo $@ FAILED; \
	fi

test4: $(EXECUTABLE) file_prep
	@strace -foo -e fault=close:error=EINTR:when=1 -y -P in -P out ./move in out > /dev/null 2>&1;:
	@if test -f in && ! test -f out ; then \
		echo $@ SUCCESS; \
  	else \
  	  	echo $@ FAILED; \
	fi

$(SHARED).so: $(SHARED).c
	$(CC) -shared $< -D_GNU_SOURCE -o $@

test_preload: $(SHARED).so $(EXECUTABLE)
	@dd if=/dev/random of=in_PROTECT_lalala bs=32000 count=1 2> /dev/null
	@rm -f out
	@LD_PRELOAD=`pwd`/$(SHARED).so ./$(EXECUTABLE) in_PROTECT_lalala out 1> /dev/null;:

	@if test -f in_PROTECT_lalala && ! test -f out ; then \
		echo $@ SUCCESS; \
  	else \
  	  	echo $@ FAILED; \
	fi


test_all: test1 test2 test3 test4 test_preload

clean:
	rm -rf $(EXECUTABLE) $(TRASH)
