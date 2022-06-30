#ifndef HEADER_H
#define HEADER_H
#include "datatype.h"

int izbornik(const char* const imeDatoteke);
void izbornikSortiranja(BILJKA* const poljeBiljaka);
void kreiranjeDatoteke(const char* const imeDatoteke);
int dodajBiljku(const char* const imeDatoteke);
void* ucitavanjeBiljaka(const char* const imeDatoteke);
void* ispisivanjeBiljaka(const BILJKA* const poljeBiljaka);
void brisanjeBiljaka(BILJKA** const pronadenaBiljka, BILJKA* const poljeBiljaka, const char* const imeDatoteke);
void azuriranje(const char* const imeDatoteke, BILJKA* const poljeBiljaka);
int izlazIzPrograma(BILJKA* poljeBiljaka, const char* const imeDatoteke);
void* kriterijPretrazivanja(BILJKA* const poljeBiljaka, const char* const imeDatoteke);
void zamjena(BILJKA*, BILJKA*);
void sortiranjeIme(BILJKA* poljeBiljaka);
void sortiranjeCijenaMin(BILJKA* poljeBiljaka);
void sortiranjeCijenaMax(BILJKA* poljeBiljaka);

#endif
