#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void enqueue(int a[], int *lenght, int b){
	a[(*lenght)++] = b;
}

int dequeue(int a[], int *lenght){
	int b = *a, *p;
	for(p = a; p < a + *lenght - 1; p++){
		*p = *(p + 1);
	}
	(*lenght)--;
	return b;
}

int izbi(int a[], const int *lenght, int b){
	int c = *a, *p;
	for(p = a; p < a + *lenght - 1; p++){
		*p = *(p + 1);
	}
	*p = b;
	return c;
}
