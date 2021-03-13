gof: main.o count_moora.o count_neumanna.o gifenc.o powieksz.o
	$(CC) -o gof main.o count_moora.o count_neumanna.o gifenc.o powieksz.o
	-rm *.o

count_moora.o: count.h
	$(CC) -c count_moora.c

count_neumanna.o: count.h
	$(CC) -c count_neumanna.c

gifenc.o: gifenc.h
	$(CC) -c gifenc.c

powieksz.o: powieksz.h
	$(CC) -c powieksz.c

clean:
	-rm *.pbm gof iteracje.gif
