gof: main.o count.o
	$(CC) -o gof main.o count.o
	-rm *.o

clean:
	-rm *.o ?.pgm ostatnia_generacja
