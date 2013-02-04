CPPFLAGS = -I.
CFLAGS = -Wall -g -c

all: libdatastructure.a

array.o: array/array.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^

list.o: list/list.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^

map_buffer.o: map_buffer/map_buffer.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^

bitset.o: bitset/bitset.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^

tree.o: tree/tree.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^

graph.o: graph/graph.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $^

OBJECTS = array.o list.o map_buffer.o bitset.o tree.o graph.o

libdatastructure.a: $(OBJECTS)
	$(AR) -crv $@ $(OBJECTS)
	rm *.o

clean:
	rm libdatastructure.a *.o
