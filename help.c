#include<stdio.h>
#include<stdlib.h>
#include"help.h"


void help_(char *progname){
	char *usage = " Usage: ./gof -d dane/nazwa -i liczba iteracji -g <tworzy plik z ostatnią generacją> -z <zmienia sąsiedztwo na neumanna> -f <tworzy gifa>\n\n";
	char *opis = "Wszystkie pliki które tworzy program są zapisywane w katalogu: zapis\n"
		"Jeśli plik z danymi nie jest podany program nie zacznie pracy\n"
		"Jeśli liczba iteracji nie będzie podana program domyśnie przyjmie 20\n"
		"Ostatnia generacja zostanie zapisana w pliku ostatnia_generacja\n"
		"Gif zostanie zapisany pod nazwą iteracje.gif\n"
		"Dodanie flagi -z spowoduje zmienienie sąsiedztwa moora na sąsiedztwo neumanna \n\n"
		"Poleceniem make clean możemy usunąć wszystkie pliki z katalogu zapis\n";

	fprintf(stderr, usage, progname);
	fprintf(stderr, opis, progname);
	exit(EXIT_FAILURE);
};

