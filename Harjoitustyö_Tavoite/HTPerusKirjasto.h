/*************************************************************************/
/* CT60A2500 C-ohjelmoinnin perusteet
* Tekijä: Sami Anttalainen
* Päivämäärä: 8.3.2023
* Kurssin oppimateriaalien lisäksi työhön ovat vaikuttaneet seuraavat
* lähteet ja henkilöt, ja se näkyy tehtävässä seuraavalla tavalla:
* Mahdollisen vilppiselvityksen varalta vakuutan, että olen tehnyt itse
* tämän tehtävän ja vain yllä mainitut henkilöt sekä lähteet ovat
* vaikuttaneet siihen yllä mainituilla tavoilla.
*/
/*************************************************************************/
/* Tehtävä HTTavoite, tiedoston nimi HTPerustaso.c */

#ifndef HTPERUSKIRJASTO_H
#define HTPERUSKIRJASTO_H
#define _XOPEN_SOURCE
#define KOKO 255
#define LEN 10
#define VIIKKO 7
#define SARAKKEET 5

typedef struct tiedot {
    char aSana[KOKO];
    int iLuokkaNro, iTaso;
    struct tm tm;
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
    SANAT aSanatTietueet[LEN];
} TULOKSET;

int valikko();

void annaTiedostoNimi(char *pNimi);

TIEDOT *varaaMuistiTietueelle(TIEDOT *pUusi);

TIEDOT *vapautaMuisti(TIEDOT *pAlku);

TIEDOT *lueTiedosto(TIEDOT *pAlku, char *pNimi);

TULOKSET *analysoiTiedot(TIEDOT *pAlku, TULOKSET *pTiedot);

TULOKSET *analysoiSanat(TIEDOT *pAlku, TULOKSET *pTiedot);

void kirjoitaTiedosto(char *pNimi, TULOKSET *pTiedot);

void tulostaTulokset(FILE *Tiedosto, TULOKSET *pTiedot);

void analysoiViikonPaivat(TIEDOT *pAlku, char *pNimi);

int **varaaMuistiMatriisille(int **pMatriisi, int iRiviLkm, int iEdellinenLkm);

void analysoiKieliTasot(TIEDOT *pAlku, char *pNimi);


#endif
// eof
