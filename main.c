#include <stdio.h>
#include <stdlib.h>
#include "count.h"
#include <getopt.h>
#include "gifenc.h"
#include "powieksz.h"
#include "funkcje.h"
#include "help.h"

int main( int argc, char **argv ){

	int opt;
	char *dane = NULL;
	int iteracje = 5;
	char *ostatnia_generacja = NULL;
	int zasady_gry = 0;
	char *progname = argv[0];
	int gif = 0;

	while( (opt = getopt(argc, argv, "d:i:g:zf")) != -1 ){
		switch(opt){
			case 'd':
			dane = optarg;
			break;
			
			case 'i':
			iteracje = atoi( optarg );
			break;

			case 'g':
			ostatnia_generacja = optarg;
			break;

			case 'z':
			zasady_gry = 1;
			break;

			case 'f':
			gif = 1;
			break;


			default:
			help_(progname);
			}
	}

	if(dane == NULL ){
		help_(progname);
	}
	
	// 0 - martwa komórka
	// 1 - żywa
	// 2 - rodzi się
	// 3 - umiera
	

	//Czytamy dane z pliku i przydzielamy pamięć	
	FILE *in = fopen(dane, "r");
	
	int N, M;

	fscanf(in, "%d", &N);
	fscanf(in, "%d", &M);

	int **tab = malloc( N * sizeof( int *) );
	for(int i = 0; i < N; i++){
		tab[i] = malloc( M * sizeof( int ) );
	}

	for(int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++){
			int x;
			fscanf(in, "%d", &x);
			tab[i][j] = x;
		}
	}
	

	//Zapisujemy bierzącą generacje w pliku .pbm	
	save_pbm(N,M,tab);
	
	//gif
	int ile_razy = 200;
	ge_GIF *plik_gif;
	if( gif == 1 ){
		   plik_gif = ge_new_gif(
      		  "iteracje.gif",  /* file name */
   		     N*ile_razy, M*ile_razy,           /* canvas size */
        	    (uint8_t []) {  /* palette */
            		0x00, 0x00, 0x00, /* 0 -> black */
            		0xFF, 0x00, 0x00, /* 1 -> red */
            		0x00, 0xFF, 0x00, /* 2 -> green */
            		0x00, 0x00, 0xFF, /* 3 -> blue */
        		},
        	2,              /* palette depth == log2(# of colors) */
        	0               /* infinite loop */
   		 );
	
	}

	//przechodzimy po iteracjach
	for(int i = 0; i < iteracje; i++){
	
	//aktaualizuje otoczenie
	update(N, M, tab, zasady_gry); 
	
	//Naprawiamy tablice
	fix(N,M,tab);

	//tworzymy pliki .pbm
	make_pbm(N,M,tab,i); 
	
	//gif
	if( gif == 1 ){
	//powieksza tabelke, zapisujemy do bufora
	//wykorzystuje funkcje ge_add
	powiekszIgif(plik_gif, N, M, ile_razy,tab);
	}
	}

	//Zapisujemy generacje po ostatniej iteracji
	//do pliku podanego przez użytkownika
	//tylko jeśli nazwa pliku zostanie podana
	save( ostatnia_generacja, N, M, tab);
	
	//gif
	if( gif == 1 ){
		ge_close_gif(plik_gif);
	}


	return 0;
}
