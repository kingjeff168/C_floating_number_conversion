solution: newfloat.o
	gcc -o newfloat newfloat.o -lm

%.o: %.c
	gcc -c -o $@ $<

clean:
	rm -f *.o newfloat