/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
* Tekijä: Sami Anttalainen
* Opiskelijanumero: 001067291
* Päivämäärä: 2.3.2023
* Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
* lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla:
* Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
* tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
* vaikuttaneet siihen yllä mainituilla tavoilla.
*/
/*************************************************************************/
/* Tehtävä HTPerus, tiedoston nimi HTPerusKirjasto.h */

#ifndef HTPERUSKIRJASTO_H
#define HTPERUSKIRJASTO_H
#define KOKO 255
#define LEN 10

typedef struct tiedot {
    char aSana[KOKO];
    int iLuokkaNro;
    struct tiedot *pSeuraava;
} TIEDOT;

typedef struct sanat {
    int iLuokkaNumero;
    int iLkm;
} SANAT;

typedef struct tulokset {
    int iLkm, iMinimiPituus, iMaksimiPituus;
    float fKeskiarvo;
    char aLyhinSana[KOKO], aPisinSana[KOKO], aEkaSana[KOKO], aVikaSana[KOKO];
    SANAT aSanatTaulukko[LEN]; 
} TULOKSET;

int valikko();

void annaTiedostoNimi(char *pNimi, char *pSyote);

TIEDOT *varaaMuisti(TIEDOT *pUusi);

TIEDOT *vapautaMuisti(TIEDOT *pAlku);

TIEDOT *lueTiedosto(TIEDOT *pAlku, char *pNimi);

TULOKSET *analysoiTiedot(TIEDOT *pAlku, TULOKSET *pTietue);

TULOKSET *analysoiSanat(TIEDOT *pAlku, TULOKSET *pSanat);

void kirjoitaTiedosto(char *pNimi, TULOKSET *pTiedot);

void tulostaTulokset(FILE *Tiedosto, TULOKSET *pTietue);


#endif

// eof