main.bin: single_cache.o multi_cache.o main.c
	gcc single_cache.o multi_cache.o main.c -o main.bin

single_cache.o: types.h single_cache.h single_cache.c
	gcc -c single_cache.c

multi_cache.o: types.h multi_cache.h multi_cache.c
	gcc -c multi_cache.c

clean:
	rm -f *.o *.bin
