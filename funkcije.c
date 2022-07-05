#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include "header.h"

static int brojBiljaka = 0;

int dodajBiljku(const char* const imeDatoteke) {

	FILE* pF = fopen(imeDatoteke, "rb+");
	if (pF == NULL) {
		perror("Greska prilikom otvaranja datoteke!\n");
		return 1;
	}
    
	fread(&brojBiljaka, sizeof(int), 1, pF);
	printf("broj biljaka: %d\n", brojBiljaka);
    
	BILJKA temp = { 0 };
	temp.idBiljke = brojBiljaka;
    
	printf("Unesite ime biljke!\n");
    scanf("%19[^\n]", temp.imeBiljke);
    getchar();
    
	printf("Unesite datum dostupnosti biljke! format: dan.mjesec.\n");
	scanf("%6[^\n]", temp.datumDostupnosti);
    getchar();
    
	printf("Unesite cjelobrojnu cijenu biljke u kunama!\n");
    float c1;
    do{                         //Provjera da li je cijena cijeli broj
        scanf("%f", &c1);
        getchar();
        temp.cijena = (int)c1;
        if(temp.cijena == 0 ){
            printf("Greska tijekom unosa cijene.");
            
            return 1;
        }
        
        if(c1 - temp.cijena != 0 || temp.cijena == 0 ){
            printf("Molimo zaokruzite cijenu na cijeli broj: ");
            
        }
    }while(c1 - temp.cijena != 0);

    
	printf("Unesite sezonu biljke: (jednosezonsko / trajnica)!\n");
	scanf("%13[^\n]", temp.sezona);
    getchar();
    
	printf("Unesite grupu biljke: (grmolik / viseci / puzavac)!\n");
	scanf("%9[^\n]", temp.grupa);
    getchar();
    
	fseek(pF, sizeof(BILJKA) * brojBiljaka, SEEK_CUR);
	fwrite(&temp, sizeof(BILJKA), 1, pF);
	rewind(pF);
	brojBiljaka++;
	fwrite(&brojBiljaka, sizeof(int), 1, pF);
    
	fclose(pF);
    
    return 0;
}

void* ucitavanjeBiljaka(const char* const imeDatoteke) {

	FILE* pF = fopen(imeDatoteke, "rb");

	if (pF == NULL) {
		perror("Greska prilikom otvaranja datoteke!\n");
		return NULL;
	}
    
	fread(&brojBiljaka, sizeof(int), 1, pF);
    if(brojBiljaka > 0){
        printf("Broj biljaka: %d\n", brojBiljaka);
    }
    if(brojBiljaka == 0){
        printf("Biljke ucitane.\n");
    }

    BILJKA* poljeBiljaka=(BILJKA*)calloc(brojBiljaka, sizeof(BILJKA));
        
        if (poljeBiljaka == NULL) {
            perror("Greska prilikom zauzimanja memorije za biljke.\n");
            return NULL;
        }
    
        fread(poljeBiljaka, sizeof(BILJKA), brojBiljaka, pF);
    
    fclose(pF);

	return poljeBiljaka;
}

void* ispisivanjeBiljaka(const BILJKA* const poljeBiljaka) {
    
    if(poljeBiljaka == NULL || brojBiljaka == 0){
        printf("Polje biljaka je prazno.\n");
        return NULL;
    }
    
	int i;
	for (i = 0; i < brojBiljaka; i++) {
		printf("Biljka broj: %d\tID: %d\tIme: %s\tDatum dostupnosti: %s\tCijena: %d kn\tSezona: %s\tGrupa: %s\n",
			i + 1,
			(poljeBiljaka + i)->idBiljke,
			(poljeBiljaka + i)->imeBiljke,
			(poljeBiljaka + i)->datumDostupnosti,
			(poljeBiljaka + i)->cijena,
			(poljeBiljaka + i)->sezona,
			(poljeBiljaka + i)->grupa);
	}
    
    return NULL;
}

void* kriterijPretrazivanja(BILJKA* const poljeBiljaka, const char* const imeDatoteke) {
    
    if(poljeBiljaka == NULL || brojBiljaka == 0){
        printf("Polje biljaka je prazno.\n");
        return NULL;
    }
    
    int uvijetp = 0;
	static BILJKA* pronadenaBiljka = NULL;
    
    printf("Odaberite kriterij pretrazivanja prema:\n");
	printf("\t1: id!\n");
	printf("\t2: imenu!\n");
	printf("\t3: cijeni!\n");
	printf("\t4: grupi!\n");
	printf("\t5: sezoni!\n");
	printf("\t6: datumu dostupnosti!\n");

    do {
        scanf("%d", &uvijetp);
        fflush(stdin);
        if(uvijetp < 1 || uvijetp > 6){
            printf("Unesite jedan od ponudenih brojeva:\n");
        }
    }while(uvijetp < 1 || uvijetp > 6);
    
    char trazeniChar[24] = { '\0' };
    int trazeniInt = 0;
    int i;
    
	switch (uvijetp) {
        
        case 1:
            printf("Unesite id biljke: ");
            scanf("%d", &trazeniInt);
            for (i = 0; i < brojBiljaka; i++) {
                if (trazeniInt == (poljeBiljaka + i)->idBiljke) {
                    printf("Biljka broj %d\tID: %d\tIme: %s\tDatum dostupnosti: %s\tCijena: %d kn\tSezona: %s\tGrupa: %s\n",
                        i + 1,
                        (poljeBiljaka + i)->idBiljke,
                        (poljeBiljaka + i)->imeBiljke,
                        (poljeBiljaka + i)->datumDostupnosti,
                        (poljeBiljaka + i)->cijena,
                        (poljeBiljaka + i)->sezona,
                        (poljeBiljaka + i)->grupa
                    );  return (poljeBiljaka + i); 
                  }
            }
            break;
        case 2:
            printf("Unesite ime biljke: ");
            scanf("%23[^\n]", trazeniChar);
            getchar();
            for (i = 0; i < brojBiljaka; i++) {
                if (!strcmp(trazeniChar, (poljeBiljaka + i)->imeBiljke)) {
                    printf("Biljka broj %d\tID: %d\tIme: %s\tDatum dostupnosti: %s\tCijena: %d kn\tSezona: %s\tGrupa: %s\n",
                        i + 1,
                        (poljeBiljaka + i)->idBiljke,
                        (poljeBiljaka + i)->imeBiljke,
                        (poljeBiljaka + i)->datumDostupnosti,
                        (poljeBiljaka + i)->cijena,
                        (poljeBiljaka + i)->sezona,
                        (poljeBiljaka + i)->grupa
                    );  return (poljeBiljaka + i); 
                }
            }
            break;
        case 3:
            printf("Unesite cijenu biljke: ");
            scanf("%d", &trazeniInt);
            getchar();
            for (i = 0; i < brojBiljaka; i++) {
                if (trazeniInt == (poljeBiljaka + i)->cijena) {
                    printf("Biljka broj %d\tID: %d\tIme: %s\tDatum dostupnosti: %s\tCijena: %d kn\tSezona: %s\tGrupa: %s\n",
                        i + 1,
                        (poljeBiljaka + i)->idBiljke,
                        (poljeBiljaka + i)->imeBiljke,
                        (poljeBiljaka + i)->datumDostupnosti,
                        (poljeBiljaka + i)->cijena,
                        (poljeBiljaka + i)->sezona,
                        (poljeBiljaka + i)->grupa
                    );  return (poljeBiljaka + i); 
                }
            }
            break;
        case 4:
            printf("Unesite grupu biljke: ");
            scanf("%23[^\n]", trazeniChar);
            getchar();
            for (i = 0; i < brojBiljaka; i++) {
                if (!strcmp(trazeniChar, (poljeBiljaka + i)->grupa)) {
                    printf("Biljka broj %d\tID: %d\tIme: %s\tDatum dostupnosti: %s\tCijena: %d kn\tSezona: %s\tGrupa: %s\n",
                        i + 1,
                        (poljeBiljaka + i)->idBiljke,
                        (poljeBiljaka + i)->imeBiljke,
                        (poljeBiljaka + i)->datumDostupnosti,
                        (poljeBiljaka + i)->cijena,
                        (poljeBiljaka + i)->sezona,
                        (poljeBiljaka + i)->grupa
                    );  return (poljeBiljaka + i); 
                }
            }
            break;
        case 5:
            printf("Unesite sezonu biljke: ");
            scanf("%23[^\n]", trazeniChar);
            getchar();
            for (i = 0; i < brojBiljaka; i++) {
                if (!strcmp(trazeniChar, (poljeBiljaka + i)->sezona)) {
                    printf("Biljka broj %d\tID: %d\tIme: %s\tDatum dostupnosti: %s\tCijena: %d kn\tSezona: %s\tGrupa: %s\n",
                        i + 1,
                        (poljeBiljaka + i)->idBiljke,
                        (poljeBiljaka + i)->imeBiljke,
                        (poljeBiljaka + i)->datumDostupnosti,
                        (poljeBiljaka + i)->cijena,
                        (poljeBiljaka + i)->sezona,
                        (poljeBiljaka + i)->grupa
                    );  return (poljeBiljaka + i); 
                }
        }
        break;
        case 6:
            printf("Unesite datum dostupnosti (u formatu: ""dan.mjesec."" ) biljke: ");
            scanf("%23[^\n]", trazeniChar);
            getchar();
            for (i = 0; i < brojBiljaka; i++) {
                if (!strcmp(trazeniChar, (poljeBiljaka + i)->datumDostupnosti)) {
                    printf("Biljka broj %d\tID: %d\tIme: %s\tDatum dostupnosti: %s\tCijena: %d kn\tSezona: %s\tGrupa: %s\n",
                        i + 1,
                        (poljeBiljaka + i)->idBiljke,
                        (poljeBiljaka + i)->imeBiljke,
                        (poljeBiljaka + i)->datumDostupnosti,
                        (poljeBiljaka + i)->cijena,
                        (poljeBiljaka + i)->sezona,
                        (poljeBiljaka + i)->grupa
                    );  return (poljeBiljaka + i);
                }
            }
            break;
        default:
            uvijetp = 0;
	}    printf("Biljka nije pronadena!");
    
	return NULL;

}

void brisanjeBiljaka(BILJKA** const trazenaBiljka, BILJKA* const poljeBiljaka, const char* const imeDatoteke) {

	FILE* pF = fopen(imeDatoteke, "wb");
	if (pF == NULL) {
		printf("Greska prilikom otvaranja datoteke!\n");
		return;
	}
	
	fseek(pF, sizeof(int), SEEK_SET);
	int i;
	int noviBrojacBiljaka = 0;
    
	for (i = 0; i < brojBiljaka; i++) { 
        if(*trazenaBiljka != (poljeBiljaka + i)) {
            (poljeBiljaka + i)->idBiljke = noviBrojacBiljaka;
			fwrite((poljeBiljaka + i), sizeof(BILJKA), 1, pF);
			noviBrojacBiljaka++;
		}
	}
    
    for (i = 0; i < brojBiljaka; i++) { 
        if(*trazenaBiljka == (poljeBiljaka + i)) {
            printf("Biljka je uspjesno obrisana!\n");
		}
	}
    
	rewind(pF);
	fwrite(&noviBrojacBiljaka, sizeof(int), 1, pF);
	fclose(pF);
	*trazenaBiljka = NULL;
}

void azuriranje(const char* const imeDatoteke, BILJKA* const poljeBiljaka) {
    
    if (poljeBiljaka == NULL || brojBiljaka == 0) {
		printf("Polje biljaka je prazno!\n");
		return;
	}
    
    int ispravak;
    
    FILE* pF = fopen(imeDatoteke, "rb+");
    if (pF == NULL){
		printf("Greska! Nema unesenih biljaka.\n");
        return;
    }
    
    printf("Unesite broj biljke koju zelite azurirati!\n");
    scanf("%d", &ispravak);
    getchar();
    
    if(ispravak > brojBiljaka || ispravak < brojBiljaka){
        printf("Greska.\n");
        return;
    }
    
    fseek(pF, sizeof(int) + (sizeof(BILJKA) * (ispravak - 1)), SEEK_SET);
    
    BILJKA azuriranaBiljka;
    azuriranaBiljka.idBiljke = ispravak - 1;
    
    printf("Unesite ime biljke!\n");
    scanf("%99[^\n]", azuriranaBiljka.imeBiljke);
    getchar();
    
    printf("Unesite datum dostupnosti biljke! format: dan.mjesec.\n");
    scanf("%19[^\n]", azuriranaBiljka.datumDostupnosti);
    getchar();

    printf("Unesite cjelobrojnu cijenu biljke u kunama!\n");
    float c1;
    do{                         //Provjera da li je cijena cijeli broj
        scanf("%f", &c1);
        fflush(stdin);
        azuriranaBiljka.cijena = (int)c1;
        if(azuriranaBiljka.cijena == 0 ){
            printf("Greska tijekom unosa cijene.");
            return;
        }
        
        if(c1 - azuriranaBiljka.cijena != 0 || azuriranaBiljka.cijena == 0 ){
            printf("Molimo zaokruzite cijenu na cijeli broj: ");
        }
    }while(c1 - azuriranaBiljka.cijena != 0);

    printf("Unesite sezonu biljke: (jednosezonsko / trajnica)!\n");
    scanf("%19s", azuriranaBiljka.sezona);
    getchar();
    
    printf("Unesite grupu biljke: (grmolik / viseci / puzavac)!\n");
    scanf("%19s", azuriranaBiljka.grupa);
    getchar();

    fwrite(&azuriranaBiljka, sizeof(BILJKA), 1, pF);
    rewind(pF);
    fwrite(&brojBiljaka, sizeof(int), 1, pF);
    fclose(pF);
    
}

void zamjena(BILJKA* veca, BILJKA* manja) {
    
    BILJKA temp = { 0 };
    temp = *manja;
	*manja = *veca;
	*veca = temp;
    
}

void izbornikSortiranja(BILJKA* poljeBiljaka) {
    
    if (poljeBiljaka == NULL || brojBiljaka == 0) {
		printf("Polje biljaka je prazno!\n");
		return;
	}
    
    int uvijets = 0;
    
    printf("Odaberite kriterij sortiranja prema:\n");
	printf("\t1: Ime A - Z!\n");
	printf("\t2: Cijeni od najmanje!\n");
	printf("\t3: Cijeni od najvece!\n");
    
    scanf("%d", &uvijets);
    
        switch(uvijets) {
            case 1: 
                sortiranjeIme(poljeBiljaka);
                break;
            case 2: 
                sortiranjeCijenaMin(poljeBiljaka);
                break;
            case 3: 
                sortiranjeCijenaMax(poljeBiljaka);
                break;
            default: 
                uvijets = 0;
                printf("Greska tijekom unosa.\n");
        }
    
}

void sortiranjeIme(BILJKA* poljeBiljaka) {
    
    int min = -1, i, j;
    BILJKA temp = { 0 };
    
    printf("Rezultat sortiranja:\n");
    
    //bubble sort
    for (i = 0; i < brojBiljaka; i++) {
			for (j = (i + 1); j < brojBiljaka; j++) {
				if (strcmp((poljeBiljaka + i)->imeBiljke, (poljeBiljaka + j)->imeBiljke) > 0) {
                    zamjena((poljeBiljaka + j), (poljeBiljaka + i));
				}
			}
		}
    
    ispisivanjeBiljaka(poljeBiljaka);

}

void sortiranjeCijenaMin(BILJKA* poljeBiljaka) {
    
    int min = -1, i, j;
    
	printf("Rezultat sortiranja:\n");
    
    //selection sort
	for (i = 0; i < brojBiljaka - 1; i++) {
		min = i;
		for (j = i + 1; j < brojBiljaka; j++) {
			if ((poljeBiljaka + j)->cijena < (poljeBiljaka + min)->cijena) {
				min = j;
			}
		}
		zamjena((poljeBiljaka + i), (poljeBiljaka + min));
	}
    
    ispisivanjeBiljaka(poljeBiljaka);

}

void sortiranjeCijenaMax(BILJKA* poljeBiljaka) {
    
    int min = -1, i, j;
    
    printf("Rezultat sortiranja:\n");
    
    //selection sort
    for (i = 0; i < brojBiljaka - 1; i++) {
		min = i;
		for (j = i + 1; j < brojBiljaka; j++) {
			if ((poljeBiljaka + j)->cijena > (poljeBiljaka + min)->cijena) {
				min = j;
			}
		}
		zamjena((poljeBiljaka + i), (poljeBiljaka + min));
	}
    
    ispisivanjeBiljaka(poljeBiljaka);
    
}

int izlazIzPrograma(BILJKA* poljeBiljaka, const char* const imeDatoteke) {
    
    printf("Izlazak iz programa? Unesite \"da\" , \"ne\" ili \"ob\" ako zelite obrisati datoteku %s tijekom izlaska iz programa: \n", imeDatoteke);
    
    char vrata[3];
    
    while(1){
        
        scanf("%2s", vrata);
        fflush(stdin);
        if(strcmp(vrata, "da") == 0 || strcmp(vrata, "ne") == 0 || strcmp(vrata, "ob") == 0){
            break;
        }
        printf("Pogresan unos.\n");
    }
    
	if (strcmp(vrata, "da") == 0) {
        
        free(poljeBiljaka);
		printf("\nIzlazak iz programa...");
		exit(EXIT_SUCCESS);
	}
    
    if (strcmp(vrata, "ob") == 0) {
        
        remove(imeDatoteke);
        printf("Uspjesno obrisana datoteka %s!\n", imeDatoteke);
        free(poljeBiljaka);
		printf("Izlazak iz programa...");
		exit(EXIT_SUCCESS);
	}
    
	if (strcmp(vrata, "ne") == 0) {
        printf("Vracanje u izbornik.\n");
        return 1;
	}

    return 0;

}
