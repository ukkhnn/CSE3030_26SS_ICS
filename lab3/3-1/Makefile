main.bin: single_cache.o main.c
	gcc single_cache.o main.c -o main.bin

single_cache.o: types.h single_cache.h single_cache.c
	gcc -c single_cache.c

clean:
	rm -f *.o *.bin
