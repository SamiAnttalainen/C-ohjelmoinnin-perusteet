// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 27.2.2023
// Tehtävä: L7T1
// Tiedosto: L7T1Kirjasto.h
#ifndef L7T1KIRJASTO_H
#define L7T1KIRJASTO_H



typedef struct tiedot {
    int iLkm, iVuosi;
}   TIEDOT;

void annaTiedostoNimi(char *pNimi);

void lueTiedosto(TIEDOT *pTiedot, int *pSumma, char *pNimi);

void tulostaTiedot(TIEDOT *pTiedot, int iSumma);

#endif