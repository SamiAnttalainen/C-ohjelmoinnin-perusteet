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
/* Tehtävä HTPerus, tiedoston nimi HTPerusKirjasto.c */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HTPerusKirjasto.h"


int valikko() {
    int iValinta;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Analysoi tiedot\n");
    printf("3) Kirjoita tulokset\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return iValinta;
}

void annaTiedostoNimi(char *pNimi, char *pSyote) {
    printf("Anna %s tiedoston nimi: ", pSyote);
    scanf("%s", pNimi);
    getchar();
    return;
}


TIEDOT *varaaMuisti(TIEDOT *pUusi) {
    if ((pUusi = (TIEDOT*)malloc(sizeof(TIEDOT))) == NULL) {
        perror("Muistin varaaminen epäonnistui");
        exit(0);
    }
    return pUusi;
}

TIEDOT *vapautaMuisti(TIEDOT *pAlku) {
    TIEDOT *pLukija = pAlku;
    while (pLukija != NULL) {
        pAlku = pLukija->pSeuraava;
        free(pLukija);
        pLukija = pAlku;
    }
    pAlku = NULL;
    printf("Muisti vapautettu.\n");
    return pAlku;
}

TIEDOT *lueTiedosto(TIEDOT *pAlku, char *pNimi) {
    char *aSarake1, *aSarake2, aRivi[KOKO];
    FILE *Tiedosto;
    TIEDOT *pUusi, *pLukija;

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fgets(aRivi, KOKO, Tiedosto); // Ohitetaan tiedoston otsikkorivi.

    while (fgets(aRivi, KOKO, Tiedosto) != NULL) {
        

        if ((aSarake1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui.", aRivi);
            exit(0);
        }

        if ((aSarake2 = strtok(NULL, ";")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui.", aRivi);
            exit(0);
        }

    
        // Varataan muisti
        pUusi = varaaMuisti(pUusi);

        // Lisätään tiedot tietueeseen
        strcpy(pUusi->aSana, aSarake1);
        pUusi->iLuokkaNro = atoi(aSarake2);
        pUusi->pSeuraava = NULL;

        // Lisätään tietue linkitettyyn listaan
        if (pAlku == NULL) {
            pAlku = pUusi;
        }
        else {
            pLukija = pAlku;
            while (pLukija->pSeuraava != NULL) {
                pLukija = pLukija->pSeuraava;
            }
            pLukija->pSeuraava = pUusi;
        }
    }
    fclose(Tiedosto);
    printf("Tiedosto '%s' luettu.\n", pNimi);
    return pAlku;
}

TULOKSET *analysoiTiedot(TIEDOT *pAlku, TULOKSET *pTietue) {
    TIEDOT *pLukija = pAlku;
    int iPituus, iSumma = 0, iLkm = 0;
    float fKeskiarvo;

    // Alustetaan arvot
    int iMaxPituus = strlen(pAlku->aSana), iMinPituus = strlen(pAlku->aSana);
    char aLyhinSana[KOKO], aPisinSana[KOKO], aEkaSana[KOKO], aVikaSana[KOKO];
    strcpy(aLyhinSana, pAlku->aSana);
    strcpy(aPisinSana, pAlku->aSana);
    strcpy(aEkaSana, pAlku->aSana);
    strcpy(aVikaSana, pAlku->aSana);

    // Luetaan linkitetty lista ja analysoidaan tiedot
    while (pLukija != NULL) {
        iPituus = strlen(pLukija->aSana);
        iSumma += iPituus;
        iLkm += 1;
        if (iPituus < iMinPituus) {
            iMinPituus = iPituus;
            strcpy(aLyhinSana, pLukija->aSana);
        }
        if (iPituus > iMaxPituus) {
            iMaxPituus = iPituus;
            strcpy(aPisinSana, pLukija->aSana);
        }
        if (strcmp(pLukija->aSana, aEkaSana) < 0) {
            strcpy(aEkaSana, pLukija->aSana);
        }
        if (strcmp(pLukija->aSana, aVikaSana) > 0) {
            strcpy(aVikaSana, pLukija->aSana);
        }
        pLukija = pLukija->pSeuraava;
    }

    // Varataan muisti tietueelle
    if ((pTietue = (TULOKSET*)malloc(sizeof(TULOKSET))) == NULL) {
        perror("Muistin varaaminen epäonnistui");
        exit(0);
    }

    // Lisätään analyysin tiedot tulokset tietueeseen
    fKeskiarvo = (float) iSumma / iLkm;
    pTietue->iLkm = iLkm;
    pTietue->fKeskiarvo = fKeskiarvo;
    pTietue->iMinimiPituus = iMinPituus;
    pTietue->iMaksimiPituus = iMaxPituus;
    strcpy(pTietue->aLyhinSana, aLyhinSana);
    strcpy(pTietue->aPisinSana, aPisinSana);
    strcpy(pTietue->aEkaSana, aEkaSana);
    strcpy(pTietue->aVikaSana, aVikaSana);

    printf("Analysoitu %d sanaa.\n", iLkm);
    return pTietue;
}

TULOKSET *analysoiSanat(TIEDOT *pAlku, TULOKSET *pTiedot) {
    TIEDOT *pLukija = pAlku;
    int i, iIndeksi;

    // Alustetaan tulokset tietuetaulukon arvot.
    for (i = 0; i < LEN; i++) {
        pTiedot->aSanatTaulukko[i].iLuokkaNumero = i + 1;
        pTiedot->aSanatTaulukko[i].iLkm = 0;
    }

    // Lasketaan sanaluokkiin kuuluvien sanojen määrät
    while (pLukija != NULL) {
        iIndeksi = pLukija->iLuokkaNro;
        pTiedot->aSanatTaulukko[iIndeksi-1].iLkm += 1;
        pLukija = pLukija->pSeuraava;
    }

    printf("Sanaluokittaiset lukumäärät analysoitu.\n");
    return pTiedot;
}


void kirjoitaTiedosto(char *pNimi, TULOKSET *pTiedot) {
    FILE *Tiedosto;

    // Tulostetaan tiedot
    tulostaTulokset(stdout, pTiedot);

    // Avataan tiedosto
    if ((Tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    // Tulostetaan tiedot ja kirjoitetaan tiedosto
    tulostaTulokset(Tiedosto, pTiedot);

    // Suljetaan tiedosto
    fclose(Tiedosto);
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    return;
}

void tulostaTulokset(FILE *Tiedosto, TULOKSET *pTiedot) {
    int i;

    // Kirjoitetaan tiedot tiedostoon
    fprintf(Tiedosto, "Tilastotiedot %d sanasta:\n", pTiedot->iLkm);
    fprintf(Tiedosto, "Keskimääräinen sanan pituus on %.1f merkkiä.\n", pTiedot->fKeskiarvo);
    fprintf(Tiedosto, "Pisin sana '%s' on %d merkkiä pitkä.\n", pTiedot->aPisinSana, pTiedot->iMaksimiPituus);
    fprintf(Tiedosto, "Lyhin sana '%s' on %d merkkiä pitkä.\n", pTiedot->aLyhinSana, pTiedot->iMinimiPituus);
    fprintf(Tiedosto, "Aakkosjärjestyksessä ensimmäinen sana on '%s'.\n", pTiedot->aEkaSana);
    fprintf(Tiedosto, "Aakkosjärjestyksessä viimeinen sana on '%s'.\n", pTiedot->aVikaSana);
    fprintf(Tiedosto, "\n");
    fprintf(Tiedosto, "Sanaluokka;Lkm\n");

    for (i = 0; i < LEN; i++) {
        fprintf(Tiedosto, "Luokka %d;%d\n", pTiedot->aSanatTaulukko[i].iLuokkaNumero, pTiedot->aSanatTaulukko[i].iLkm);
    }
    return;
}

// eof