#include"funkcje.h"
#include"count.h"
#include<stdlib.h>
#include<stdio.h>
#include <getopt.h>
#include "gifenc.h"
#include "powieksz.h"

 //Zapisujemy bierzącą generacje w pliku .pbm
 void save_pbm(int N, int M,int **tab){
	FILE *y = fopen("0.pbm", "w");
 	fprintf(y, "P1\n%d %d\n", N ,M);
		for( int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++){
			fprintf(y, "%d ", tab[i][j] );
		}
 			fprintf(y,"\n");
		}
		fclose(y);
};

//Naprawiamy tablicę
void fix(int N, int M, int **tab){
	for(int i = 0; i < N; i++){
	for(int j = 0; j < M; j++){
		if(tab[i][j] == 3) tab[i][j] = 0;
		if(tab[i][j] == 2 ) tab[i][j] = 1;
	}
	}
};

//aktualizujemy swiat
void update(int N, int M, int **tab,int how_to_count_neigh){
        for( int i = 0; i < N; i++ ){
	for(int j = 0; j < M; j++ ) {
	int otoczenie_zywych;

		if( how_to_count_neigh == 0 ){
		otoczenie_zywych = count_moora( N, M, tab, i, j );
			 }
		
		if( how_to_count_neigh == 1 ){
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
 };


//tworzymy pliki pbm
void make_pbm(int N,int M, int **tab,int i){
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
		fclose(x);
};

 //Zapisujemy generacje po ostatniej iteracji
 //do pliku podanego przez użytkownika
 //tylko jeśli nazwa pliku zostanie podana
void save(char *ostatnia_generacja, int N, int M, int **tab){
    if( ostatnia_generacja != NULL ) {

	FILE *z = fopen(ostatnia_generacja, "w");
	fprintf(z, "%d %d\n", N ,M);

		for( int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++){
			fprintf(z, "%d ", tab[i][j] );
		}
			 fprintf(z,"\n");
		}

		fclose(z);
    }
};

void zwolnij_pamiec(int N, int M, int **tab ){

	for(int i = 0; i < N; i++ ){
		free( tab[i] );
	}

	free(tab);
}


//w pierwszym kroku funkcją powieksz() powiększamy obrazek ile_razy
//następnie w pętlach uzupełniamy ramkę-bufor 
//dodajemy ramkę funckją ge_add_frame() do gifa
void powiekszIgif(ge_GIF *plik_gif, int N, int M, int ile_razy, int **tab){
	int g = 0;
	int **tab2 = powieksz(tab, ile_razy, N, M );
		for(int i = 0; i < N*ile_razy; i++ ){
		for(int j = 0; j < M *ile_razy; j++ ){
			plik_gif->frame[g++] = tab2[i][j];
		}
		}
	ge_add_frame(plik_gif, 50);
	zwolnij_pamiec(N*ile_razy, M*ile_razy, tab2);
};


