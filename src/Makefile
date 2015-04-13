C=gcc
CFLAGS=-Ddebug #to compile with debug mode
DEBUGG=-ggdb #to check code in GNU debbuger

prodtekst: generator.o statistic.o errors.o ngramstruct.o database.o textfile_analize.o
	$(CC) $(CFLAGS) $^ main.c -o $@ $(DEBUGG)

statistic.o: errors.o ngramstruct.o statistic.c
	$(CC) $(CFLAGS) $^ -c -o $@ $(DEBUGG)

textfile_analize.o: errors.o ngramstruct.o textfile_analize.c
	$(CC) $(CFLAGS) $^ -c -o $@ $(DEBUGG)

database.o: errors.o ngramstruct.o database.c
	$(CC) $(CFLAGS) $^ -c -o $@ $(DEBUGG)

generator.o: errors.o ngramstruct.o generator.c
	$(CC) $(CFLAGS) $^ -c -o $@ $(DEBUGG)

ngramstruct.o: errors.o ngramstruct.c
	$(CC) $(CFLAGS) $^ -c -o $@ $(DEBUGG)

errors.o: errors.c
	$(CC) $(CFLAGS) $^ -c -o $@ $(DEBUGG)

clean:
	rm -f *.o

.PHONY: all clean
