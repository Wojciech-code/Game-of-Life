#include"funkcje.h"
#include"count.h"
#include<stdlib.h>
#include<stdio.h>

/*ta funkcja mi nie działa jak tak zapisuje :(
void czytaj_dane(int N, int M,int **tab,FILE *in){
//FILE *in=fopen(dane,"r");
        //int N, M;

	fscanf(in, "%d", &N);
	fscanf(in, "%d", &M);

	tab = malloc( N * sizeof( int *) );
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
};
*/

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
}
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
	void update(int N, int M, int **tab,int zasady_gry){

	        for( int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++ ) {
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
};


//zapisujemy oststnia iteracje
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
    }
};


