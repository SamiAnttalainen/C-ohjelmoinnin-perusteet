// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 27.2.2023
// Tehtävä: L7T1
// Tiedosto: L7T1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "L7T1Kirjasto.h"
#define KOKO 10
#define LEN 30


int main(void) {

    int iSumma;
    TIEDOT aTiedot[KOKO];
    char aTiedostoNimi[LEN];
    annaTiedostoNimi(aTiedostoNimi);
    lueTiedosto(aTiedot, &iSumma, aTiedostoNimi);
    tulostaTiedot(aTiedot, iSumma);
    printf("\n");
    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}
















// eof