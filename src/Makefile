C=gcc
CFLAGS=-Ddebug #to compile with debug mode

prodtekst: generator.o statistic.o errors.o ngramstruct.o database.o textfile_analize.o
	$(CC) $(CFLAGS) $^ main.c -o $@

statistic.o: errors.o ngramstruct.o statistic.c
	$(CC) $(CFLAGS) $^ -c -o $@

textfile_analize.o: errors.o ngramstruct.o textfile_analize.c
	$(CC) $(CFLAGS) $^ -c -o $@

database.o: errors.o ngramstruct.o database.c
	$(CC) $(CFLAGS) $^ -c -o $@

generator.o: errors.o ngramstruct.o generator.c
	$(CC) $(CFLAGS) $^ -c -o $@

ngramstruct.o: errors.o ngramstruct.c
	$(CC) $(CFLAGS) $^ -c -o $@

errors.o: errors.c
	$(CC) $(CFLAGS) $^ -c -o $@

clean:
	rm -f *.o

.PHONY: all clean
