#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"
#include <errno.h>
int main() {
	
	int uvijet = 1;
	char imeDatoteke[20] = "biljke.bin";
    
    FILE* pF = NULL;
	pF = fopen(imeDatoteke, "rb");
    
	if (pF == NULL) {
		pF = fopen(imeDatoteke, "wb");
		int num = 0;
		fwrite(&num, sizeof(int), 1, pF);
		fprintf(stdout, "Datoteka %s stvorena je na disku.\n", imeDatoteke);
		fclose(pF);
	}
	else {
		fprintf(stdout, "Datoteka %s spremna.\n", imeDatoteke);
		fclose(pF);
	}
    
	while (uvijet) {
		uvijet = izbornik(imeDatoteke);
	}
    
	printf("Zavrsetak programa!\n");

	return 0;
    
}