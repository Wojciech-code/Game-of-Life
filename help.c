#include<stdio.h>
#include<stdlib.h>
#include"help.h"


void help_(char *progname){
	char *usage = " Usage: ./gof -d dane/nazwa -i liczba iteracji -g nazwa pliku dla ostatniej generacji -z zmienia sąsiedztwo na neumanna -f tworzy gifa\n\n";
	char *opis = "Jeśli plik z danymi nie jest podany program nie zacznie pracy\n"
		"Jeśli liczba iteracji nie będzie podana program domyśnie przyjmie 5\n"
		"Ostatnia generacja zostanie stworzona do pliku jeśli zostanie podana nazwa tego pliku\n"
		"Dodanie flagi -z spowoduje zmienienie sąsiedztwa moora na sąsiedztwo neumanna \n";

	fprintf(stderr, usage, progname);
	fprintf(stderr, opis, progname);
	exit(EXIT_FAILURE);
};

