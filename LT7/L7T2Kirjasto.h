// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 27.2.2023
// Tehtävä: L7T2
// Tiedosto: L7T2Kirjasto.h

#ifndef L7T2KIRJASTO_H
#define L7T2KIRJASTO_H
typedef struct laskut {
    int iLuku, iLisa, iSumma;
    struct laskut *pSeuraava;
} LASKUT;

int valikko();

void annaTiedostoNimi(char *pNimi, char *pSyote);

LASKUT *varaaMuisti(LASKUT *pUusi);

LASKUT *vapautaMuisti(LASKUT *pAlku);

LASKUT *lisaaLukuun(LASKUT *pAlku, int iTulos, int *pSumma);

LASKUT *kirjoitaTiedosto(LASKUT *pAlku, char *pNimi);

LASKUT *lueTiedosto(LASKUT *pAlku, char *pNimi);

LASKUT *poistaViimeinen(LASKUT *pAlku, int *pSumma);

#endif