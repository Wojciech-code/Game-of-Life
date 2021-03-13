#include "powieksz.h"
#include <stdlib.h>

int **powieksz(int **tab, int x, int N, int M){

int **tab2 = malloc( N * x * sizeof( int * ) );

	for(int j = 0; j < N * x; j++ ){
		tab2[j] = malloc( M * x * sizeof( int ) );
	}


int buf[x*M];

int z = 0;


//iteruj po wierszach
for(int w = 0; w < N; w++ ){


//zapisz 'w' wiersz w buf x razy kazdy wyraz
for(int i = 0; i < M; i++ ){
	int y = tab[w][i];
	
		for(int v = 0; v < x; v++ ){
			buf[z++] = y;
		}

}

z = 0;


//przepisz 'w' wiersz z buff do tab2 x razy
for(int g = 0; g < x; g++ ){
	for(int f = 0; f < x*M; f++){
			tab2[(w*x) +g][f] = buf[f];
			}
	}


}

return tab2;
}

#ifdef TEST

#include <stdio.h>

int main(){

	int **tab = malloc( 3 * sizeof( int * ) );

	for(int i = 0; i < 3; i++){
		tab[i] = malloc( 3 * sizeof( int ));
	}

	

	int y = 0;
	int x = 3;

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++ ){
			tab[i][j] = y++;
		}
	}

	int **tab2 = powieksz(tab, x, 3, 3);

		
for(int j = 0; j < 3*x; j++ ){
	for(int i = 0; i < 3*x; i++){
		printf("%d ", tab2[j][i]);
			}
	printf("\n");
}


}


#endif

