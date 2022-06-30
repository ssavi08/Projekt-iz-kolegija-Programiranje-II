#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "header.h"

int izbornik(const char* const imeDatoteke) {
	
    
    int uvijet = 0;
	static BILJKA* poljeBiljaka = NULL;
	static BILJKA* trazenaBiljka = NULL;
    
   do {
    //opcije
        printf("\n\t:::::::::::::::");
        printf("O.P.G.  SAVI");
        printf(":::::::::::::::\n");
        printf("\t---");
        printf("Odaberite jednu od ponudenih opcija:");
        printf("---\n");
        printf("\tOpcija 1: dodavanje biljke!\n");
        printf("\tOpcija 2: ucitavanje biljke!\n");
        printf("\tOpcija 3: ispisivanje biljke!\n");
        printf("\tOpcija 4: pretrazivanje biljke!\n");
        printf("\tOpcija 5: brisanje biljke!\n");
        printf("\tOpcija 6: azuriranje biljke!\n");
        printf("\tOpcija 7: sortiranje!\n");
        printf("\tOpcija 8: izlaz iz programa!\n");
        printf("\t==========================================\n\n");
        
        do{
            scanf("%d", &uvijet);
            getchar();
        }while(uvijet < 1 || uvijet > 8);
    
        switch (uvijet) {
        case 1:
            dodajBiljku(imeDatoteke);
            break;
        case 2:
            if (poljeBiljaka != NULL) {
                free(poljeBiljaka);
                poljeBiljaka = NULL;
            }
            poljeBiljaka = (BILJKA*)ucitavanjeBiljaka(imeDatoteke);
            if (poljeBiljaka == NULL) {
                printf("Polje biljaka je prazno.\n");
            }
            break;
        case 3:
            if (poljeBiljaka != NULL) {
                free(poljeBiljaka);
                poljeBiljaka = NULL;
            }
            poljeBiljaka = (BILJKA*)ucitavanjeBiljaka(imeDatoteke);
    		if(poljeBiljaka == NULL) {
    			printf("Polje biljaka je prazno.\n");
    		}
            ispisivanjeBiljaka(poljeBiljaka);
            break;
         case 4:
            if (poljeBiljaka != NULL) {
                free(poljeBiljaka);
                poljeBiljaka = NULL;
            }
            poljeBiljaka = (BILJKA*)ucitavanjeBiljaka(imeDatoteke);
            trazenaBiljka = (BILJKA*)kriterijPretrazivanja(poljeBiljaka, imeDatoteke);
            break;
        case 5:
            if (poljeBiljaka != NULL) {
                free(poljeBiljaka);
                poljeBiljaka = NULL;
            }
            poljeBiljaka = (BILJKA*)ucitavanjeBiljaka(imeDatoteke);
            trazenaBiljka = (BILJKA*)kriterijPretrazivanja(poljeBiljaka, imeDatoteke);
            brisanjeBiljaka(&trazenaBiljka, poljeBiljaka, imeDatoteke);
            break;
        case 6:
            if (poljeBiljaka != NULL) {
                free(poljeBiljaka);
                poljeBiljaka = NULL;
            }
            poljeBiljaka = (BILJKA*)ucitavanjeBiljaka(imeDatoteke);
            azuriranje(imeDatoteke, poljeBiljaka);
            break;
        case 7:
            if (poljeBiljaka != NULL) {
                free(poljeBiljaka);
                poljeBiljaka = NULL;
            }
            poljeBiljaka = (BILJKA*)ucitavanjeBiljaka(imeDatoteke);
            izbornikSortiranja(poljeBiljaka);
            break;
        case 8:
            uvijet = izlazIzPrograma(poljeBiljaka, imeDatoteke);
            break;
        default:
            uvijet = 0;
        }
   
   }while(uvijet != 0);
   
   
    return uvijet;
}  
