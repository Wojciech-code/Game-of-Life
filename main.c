#include <stdio.h>
#include <stdlib.h>
#include "count.h"
#include <getopt.h>
#include "gifenc.h"
#include "powieksz.h"

char *usage = " Usage: ./gof -d dane -i ilość iteracji -g nazwa pliku dla ostatniej iteracji -z zmienia zasady gry na neumanna -f tworzy gifa\n\n";
char *opis = "Jeśli plik z danymi nie jest podany program nie zacznie pracy\n"
"Jeśli ilość iteracji nie będzie podana program domyśnie przyjmie 5\n"
"Ostatnia generacja zostanie stworzona do pliku jeśli zostanie podana nazwa tego pliku\n"
"Dodanie flagi -z spowoduje zmienienie zasad gry na sąsiedztwo neumanna ( domyślnie jest to sąsiedztwo moora )\n";

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
			fprintf(stderr, usage, progname);
			fprintf(stderr,opis, progname);
			exit(EXIT_FAILURE);
			}
	}

	if(dane == NULL ){
		fprintf(stderr, usage, progname);
		fprintf(stderr, opis, progname);
		exit(EXIT_FAILURE);
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
	FILE *y = fopen("0.pbm", "w");
	fprintf(y, "P1\n%d %d\n", N ,M);

	for( int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++){
			fprintf(y, "%d ", tab[i][j] );
		}
		fprintf(y,"\n");
	}

	
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


	for(int i = 0; i < iteracje; i++){
	
	for( int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++){
		
			int otoczenie_zywych;

			if( zasady_gry == 0 ){
				  otoczenie_zywych = count_moora( N, M, tab, i, j );
			}
			if( zasady_gry == 1 ){
				  otoczenie_zywych = count_neumanna( N, M, tab, i, j );
			}
		
			if( tab[i][j] == 0 && otoczenie_zywych == 3 ){
				tab[i][j] = 2;
			}

			if( tab[i][j] == 1 && otoczenie_zywych != 2 && otoczenie_zywych != 3 ){
				tab[i][j] = 3;
			}
		}
	}


	//Naprawiamy tablicę
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			
			if(tab[i][j] == 3) tab[i][j] = 0;
			if(tab[i][j] == 2 ) tab[i][j] = 1;
		}
	}
	
	//tworzymy pliki .pbm
	char nazwa_pliku[1000];
	sprintf(nazwa_pliku, "%d.pbm", i+1);
	FILE *x = fopen(nazwa_pliku, "w");
	fprintf(x, "P1\n%d %d\n", N ,M);

	for( int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++){
			fprintf(x, "%d ", tab[i][j] );
		}
		fprintf(x,"\n");
	}
	

	if( gif == 1 ){
		int g = 0;
		int **tab2 = powieksz(tab, ile_razy, N, M );

		for(int i = 0; i < N*ile_razy; i++ ){
			for(int j = 0; j < M *ile_razy; j++ ){
				plik_gif->frame[g++] = tab2[i][j];
			}
		}

		ge_add_frame(plik_gif, 50);

	}

	
	}
	//Zapisujemy generacje po ostatniej iteracji do pliku podanego przez użytkownika
	// tylko jeśli nazwa pliku zostanie podana
	if( ostatnia_generacja != NULL ) {
		
		FILE *z = fopen(ostatnia_generacja, "w");
		fprintf(z, "%d %d\n", N ,M);

		for( int i = 0; i < N; i++ ){
			for(int j = 0; j < M; j++){
				fprintf(z, "%d ", tab[i][j] );
			}
			fprintf(z,"\n");
		}
	}

	if( gif == 1 ){
		ge_close_gif(plik_gif);
	}


	return 0;
}
