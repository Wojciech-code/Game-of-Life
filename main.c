#include <stdio.h>
#include <stdlib.h>

int count(int N, int M, int **tab, int i, int j);

int main( int argc, char **argv ){

	// 0 - martwa komórka
	// 1 - żywa
	// 2 - rodzi się
	// 3 - umiera
	
	if(argc < 2 ){
		printf("Nie podano danych z pierwszą generacją\n");
		return 1;
	}
		
	FILE *in = argc > 1 ? fopen(argv[1], "r") : stdin;
	
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

	//Zapisanie bierzącej generacji w pliku .pgm	
	FILE *y = fopen("0.pgm", "w");
	fprintf(y, "P2\n%d %d\n%d\n", N ,M, 1 );

	for( int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++){
			fprintf(y, "%d ", tab[i][j] );
		}
		fprintf(y,"\n");
	}

	int iteracje = argc > 2 ? atoi(argv[2]) : 3;

	for(int i = 0; i < iteracje; i++){
	
	for( int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++){
			
			int otoczenie_zywych = count( N, M, tab, i, j );
			
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
	
	//tworzymy pliki .pgm
	char nazwa_pliku[1000];
	sprintf(nazwa_pliku, "%d.pgm", i+1);
	FILE *x = fopen(nazwa_pliku, "w");
	fprintf(x, "P2\n%d %d\n%d\n", N ,M, 1 );

	for( int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++){
			fprintf(x, "%d ", tab[i][j] );
		}
		fprintf(x,"\n");
	}
	

	}

	//Zapisujemy generacje po ostatniej iteracji do pliku "ostatnia_generacja"
	FILE *z = fopen("ostatnia_generacja", "w");
	fprintf(z, "%d %d\n", N ,M);

	for( int i = 0; i < N; i++ ){
		for(int j = 0; j < M; j++){
			fprintf(z, "%d ", tab[i][j] );
		}
		fprintf(z,"\n");
	}


	return 0;
}
