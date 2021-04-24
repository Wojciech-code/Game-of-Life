#include "powieksz.h"
#include <stdlib.h>
#include "funkcje.h"

/* jest wykorzystywana w funkcji powiekszIgif()
 * zadaniem funkcji jest powiększenie tablicy w taki sposób,
 * aby ta potem generowała większe obrazki,
 * każdy "wyraz" w tabeli zamienia na kwadracik
 * przykład działania dla ile_razy = 2
 * przyjmuje: 1 2 3 
 *            4 5 6 
 * zwraca: 1 1 2 2 3 3 
 *         1 1 2 2 3 3 
 *         4 4 5 5 6 6
 *         4 4 5 5 6 6  
 */
int **powieksz(int **tab, int ile_razy, int N, int M){

	int **tab2 = malloc( N * ile_razy * sizeof( int * ) );

	for(int j = 0; j < N * ile_razy; j++ ){
		tab2[j] = malloc( M * ile_razy * sizeof( int ) );
	}


	int buf[ile_razy*M];

	int z = 0;

	//iteruj po wierszach
	for(int w = 0; w < N; w++ ){


	//zapisz 'w' wiersz w buf ile_razy kazdy wyraz tego wiersza
	for(int i = 0; i < M; i++ ){
		int y = tab[w][i];
	
		for(int v = 0; v < ile_razy; v++ ){
		buf[z++] = y;
		}
	}
	z = 0;


	//przepisz 'w' wiersz z buff do tab2 x razy
	for(int j = 0; j < ile_razy; j++ ){
		for(int i = 0; i < ile_razy*M; i++){
			tab2[(w*ile_razy) +j][i] = buf[i];
			}
	}


	}

return tab2;
}

