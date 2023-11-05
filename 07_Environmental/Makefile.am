CFLAGS = -g

bin_PROGRAMS=rhasher

rhasher_SOURCES=rhasher.c

TESTS=md5.sh

md5.sh:
	echo 'test "`./rhasher <<<'md5 "lala"' 2>&1`" = "Digest : LjgXKT/CddvudL1xzm6wVg=="' > $@
	chmod +x $@

gitclean:
	git clean -df