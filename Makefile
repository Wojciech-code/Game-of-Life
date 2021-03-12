gof: main.o count_moora.o count_neumanna.o
	$(CC) -o gof main.o count_moora.o count_neumanna.o
	-rm *.o

count_moora.o: count.h
	$(CC) -c count_moora.c

count_neumanna.o: count.h
	$(CC) -c count_neumanna.c

clean:
	-rm ?.pbm gof
