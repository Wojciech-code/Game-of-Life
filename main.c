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
	int iteracje = 20;
	int ostatnia_generacja = 0;
	int how_to_count_neigh = 0;
	char *progname = argv[0];
	int gif = 0;

	while( (opt = getopt(argc, argv, "d:i:gzf")) != -1 ){
		switch(opt){
			case 'd':
			dane = optarg;
			break;
			
			case 'i':
			iteracje = atoi( optarg );
			break;

			case 'g':
			ostatnia_generacja = 1;
			break;

			case 'z':
			how_to_count_neigh = 1;
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

	fclose(in);
	

	//Zapisujemy bierzącą generacje w pliku .pbm	
	save_pbm(N,M,tab);
	
	//gif
	int ile_razy = N >= M ? 750/N: 750/M;
	ge_GIF *plik_gif;
	if( gif == 1 ){
		   plik_gif = ge_new_gif(
      		  "zapis/iteracje.gif",  /* file name */
   		     N*ile_razy, M*ile_razy,           /* canvas size */
        	    (uint8_t []) {  /* palette */
            		0xFF, 0xFF, 0xFF, /* 0 -> white */
            		0x00, 0x00, 0xFF, /* 1 -> blue */
            		0x00, 0xFF, 0x00, /* 2 -> green */
            		0xFF, 0x00, 0x00, /* 3 -> red */
        		},
        	2,              /* palette depth == log2(# of colors) */
        	0               /* infinite loop */
   		 );
	
	}

	//przechodzimy po iteracjach
	for(int i = 0; i < iteracje; i++){
	
	//aktaualizuje otoczenie
	update(N, M, tab, how_to_count_neigh); 
	
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
	//jeśli -g
	if(ostatnia_generacja == 1 ){
		save(N, M, tab);
	}

	//gif
	if( gif == 1 ){
		ge_close_gif(plik_gif);
	}


	zwolnij_pamiec(N, M, tab);

	return 0;
}
