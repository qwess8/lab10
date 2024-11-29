// labor10.cpp: определяет точку входа для консольного приложения.
//

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <locale.h>
#include <time.h>
#include <queue> 
using namespace std;

int** createG(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            G[i][j] =(rand()%2) ? 0 : rand() % 10;
            G[j][i] = (i == j) ? 0 : G[i][j];
        }
    }
    return G;
}

int** createGO(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            G[i][j] =(rand()%2) ? 0 : rand() % 10;
            if(i==j) G[i][j] = 0;
        }
    }
    return G;
}
 
void printG(int** G, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%2d ", G[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void DiFS(int** G, int size, int* dist, int s) {
    queue <int> q;
	dist[s] = 0;
    q.push(s); 
    while (!q.empty()) {
        s = q.front();
        q.pop();
        for (int i = 0; i < size; i++) {
            if (G[s][i] && dist[i]==-1) {
                q.push(i);
                dist[i] = dist[s] + G[s][i];
            }
        }
    }
}

void createD(int** G, int size, int** D, int* exs){
	int* dist = (int*)malloc(sizeof(int) * size);
	int max;
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++) dist[j] = -1;
		DiFS(G, size, dist, i);
		max = dist[0];
		for(int j = 0; j < size; j++){
			if(max < dist[j]) max = dist[j];
			D[i][j] = dist[j];
		}
		exs[i] = max;
	}
}

int diam(int* exs, int size){
	int max = exs[0];
	for(int i = 1; i < size; i++){
		if(max < exs[i]) max = exs[i];
	}
	return max;
}

int rad(int* exs, int size){
	int min = exs[0];
	for(int i = 1; i < size; i++){
		if(min > exs[i]) min = exs[i];
	}
	return min;
}

void PerCen(int* exs, int rad, int diam, int size){
	for(int i = 0; i < size; i++){
		if(rad == exs[i]) printf("Ver %d - centr\n", i);
		if(diam == exs[i]) printf("Ver %d - perif\n", i);
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
    int nG = 5;
	int* exs = (int*)malloc(nG * sizeof(int));
	int** D = (int**)malloc(sizeof(int*) * nG);
	for (int i = 0; i < nG; i++) {
        D[i] = (int*)malloc(nG * sizeof(int));
    }
	int** G = createGO(nG);

	printG(G,nG);

	createD(G, nG, D, exs);
	printf("\n");
	printf("\n");

	printG(D,nG);

	printf("\n");

	for (int i = 0; i < nG; i++) {
		printf("Exs[%d] = %d\n", i, exs[i]);
	}
	printf("\n");

	int radius = rad(exs, nG);
	int diametr = diam(exs, nG);

	printf("Radius = %d\n", radius);
	printf("Diametr = %d\n\n", diametr);

	PerCen(exs, radius, diametr, nG);
	

	getchar();
	return 0;
}

