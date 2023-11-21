EXECUTABLES= gen_maze_0 gen_maze_1 gen_maze_2 gen_maze_3
CC= gcc
TRASH = *.o
CFLAGS = -Wall -Werror -fPIC -O0 -g

gen_maze_0:
	$(CC) gen_maze.c -o $@

gen_maze_1: gen_maze_0
	git apply 0001-Ninth-task-part-1.patch
	$(CC) gen_maze.c -o $@

gen_maze_2: gen_maze_1
	git apply 0002-Ninth-task-part-2.patch
	$(CC) gen_maze.c -o $@

gen_maze_3: gen_maze_2
	git apply 0003-Ninth-task-part-3.patch
	$(CC) gen_maze.c -o $@


all: $(EXECUTABLES)

run: all
	./gen_maze_0
	./gen_maze_1 6
	./gen_maze_2 .@ 6
	./gen_maze_3 55 .@ 6

clean:
	git checkout HEAD  -- gen_maze.c
	rm -rf $(EXECUTABLES) $(TRASH)
