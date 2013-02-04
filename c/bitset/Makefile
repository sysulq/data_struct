CPPFLAGS = -I../
CFLAGS = -g

test: test.c bitset.c
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $^ 
	./test
