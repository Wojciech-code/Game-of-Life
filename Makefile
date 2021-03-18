gof: main.o count_moora.o count_neumanna.o gifenc.o powieksz.o funkcje.o help.o
	$(CC) -o gof main.o count_moora.o count_neumanna.o gifenc.o powieksz.o funkcje.o help.o
	-rm *.o

count_moora.o: count.h
	$(CC) -c count_moora.c

count_neumanna.o: count.h
	$(CC) -c count_neumanna.c

gifenc.o: gifenc.h
	$(CC) -c gifenc.c

powieksz.o: powieksz.h
	$(CC) -c powieksz.c

funkcje.o: funkcje.h
	$(CC) -c funkcje.c

help.o: help.h
	$(CC) -c help.c

clean:
	-rm *zapis.pbm gof zapis/iteracje.gif *.o
