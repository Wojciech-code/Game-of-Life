

int count(int N, int M, int **tab, int i, int j ) {
	
	int alive = 0;

	// i to aktualny wiersz tablicy
	// j to aktualna kolumna
	// N to ilosc wierszy
	// M to ilosc kolumn
	
	//Sprawdzamy północ
	if( i - 1 >= 0 && ( tab[i-1][j] == 1 || tab[i-1][j] == 3 ) ) {
		alive++;
	}

	//Sprawdzamy południe
	if( i + 1 < N && ( tab[i+1][j] == 1  || tab[i+1][j] == 3 ) ) {
		alive++;
	}

	//Sprawdzamy wschód
	if( j + 1 < M && ( tab[i][j+1] == 1 || tab[i][j+1] == 3) ) {
	       alive++;
	}

	//Sprawdzamy zachód
	if( j - 1 >= 0 && ( tab[i][j-1] == 1 || tab[i][j-1] ==3 ) ) {
		alive++;
	}

	//Sprawdzamy północny-wschód
	if( i - 1 >= 0 && j + 1 < M && ( tab[i-1][j+1] == 1 || tab[i-1][j+1] == 3) ){
		alive++;
	}	

	//Sprawdzamy północny-zachód
	if( i - 1 >= 0 && j - 1 >= 0 && ( tab[i-1][j-1] == 1 || tab[i-1][j-1] == 3) ){
		alive++;
	}

	//Sprawdzamy połódniowy-wschód
	if( i + 1 < N && j + 1 < M && ( tab[i+1][j+1] == 1 || tab[i+1][j+1] == 3 ) ){
		alive++;
	}

	//Sprawdzamy południowy-zachód
	if( i + 1 < N && j - 1 >= 0 && ( tab[i+1][j-1] == 1 || tab[i+1][j-1] == 3 ) ){
		alive++;
	}
	
return alive;
}

#ifdef DEBUG

#include <stdio.h>

int main(){
	
	int tab[6][6];
	for(int i = 0; i < 6; i++){
		for(int j = 0; j <6; j++ ){
			tab[i][j] = 0;
		}
	}

	tab[0][0] = 1;	
	tab[0][1] = 1;
	tab[0][2] = 1;
	
	int alive = count( 6, 6, tab, 1, 1 );

	printf("ilość żywych komórek: %d\n", alive );
}

#endif
