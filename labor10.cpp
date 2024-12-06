// labor10.cpp: определяет точку входа для консольного приложения.
//

#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include <locale.h>
#include <time.h>
#include <queue> 
using namespace std;

int** createGOW(int size) {
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

int** createGO(int size) {
    int** G = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        G[i] = (int*)malloc(size * sizeof(int));
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            G[i][j] =rand()%2;
            if(i==j) G[i][j] = 0;
        }
    }
    return G;
}

void mirrorG(int** G, int size){
	for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
			G[i][j] =  G[j][i];
		}
	}
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



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
    int nG = 5, weighted = 0, oriented = 0;
	printf("Вы можете ввести размер(-n <знач>), ориентированность(-o) и взвешенность(-w) графа с помощью аргументов программы.\nПо умолчанию они заданы как размер = 5, неориентированный, невзвешанный.");
	getchar();
	if(argc > 1){
		for (int i = 0; i < argc; i++) {
			if(strcmp(argv[i], "-n")==0){
				nG = atoi(argv[i+1]);
				i++;
			}
			else if(strcmp(argv[i], "-w")==0) weighted = 1;
			else if(strcmp(argv[i], "-o")==0) oriented = 1;
		}
	}
	int* exs = (int*)malloc(nG * sizeof(int));
	int** D = (int**)malloc(sizeof(int*) * nG);
	for (int i = 0; i < nG; i++) {
        D[i] = (int*)malloc(nG * sizeof(int));
    }
	int** G = NULL;
	if(weighted) G = createGOW(nG);
	else G = createGO(nG);

	printG(G,nG);

	if(!oriented) mirrorG(G, nG);

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

