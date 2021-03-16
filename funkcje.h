#include <stdio.h>

//void czytaj_dane(int N, int M,int **tab,FILE *in);
void fix(int N, int M, int **tab);
//void update(int iteracje, int zasady_gry);
void update(int N, int M, int **tab, int zasady_gry);
void make_pbm(int N,int M, int **tab,int i);
void save_pbm(int N, int M,int **tab);
void save(char *ostatnia_generacja, int N, int M, int **tab);
