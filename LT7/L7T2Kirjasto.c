// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 27.2.2023
// Tehtävä: L7T2
// Tiedosto: L7T2Kirjasto.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "L7T2Kirjasto.h"
#define KOKO 30

int valikko() {
    int iValinta;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lisää lukuun\n");
    printf("2) Kirjoita historia tiedostoon\n");
    printf("3) Lue historia tiedostosta\n");
    printf("4) Poista viimeisin historiasta\n");
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

LASKUT *varaaMuisti(LASKUT *pUusi) {
    if ((pUusi = (LASKUT*)malloc(sizeof(LASKUT))) == NULL) {
        perror("Muistin varaaminen epäonnistui");
        exit(0);
    }
    return pUusi;
}

LASKUT *vapautaMuisti(LASKUT *pAlku) {
    LASKUT *pLukija = pAlku;

    while (pLukija != NULL) {
        pAlku = pLukija->pSeuraava;
        free(pLukija);
        pLukija = pAlku;
    }

    pAlku = NULL;
    printf("Muisti vapautettu.\n");
    return pAlku;
}

LASKUT *lisaaLukuun(LASKUT *pAlku, int iTulos, int *pSumma) {
    int iLisa, iSumma;
    LASKUT *pUusi = NULL, *pLukija = NULL;
    printf("\n");
    printf("Anna lukuun lisättävä kokonaisluku: ");
    scanf("%d", &iLisa);
    getchar();
    iSumma = iTulos + iLisa;
    printf("%d+%d=%d\n", iTulos, iLisa, iSumma);

    // Varataan muisti tietueelle
    pUusi = varaaMuisti(pUusi);

    // Lisätään arvot tietueeseen.
    pUusi->iLuku = iTulos;
    pUusi->iLisa = iLisa;
    pUusi->iSumma = iSumma;
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

    // Tallennetaan summa tulosmuuttujaan
    *pSumma = iSumma;
    return pAlku;
}

LASKUT *kirjoitaTiedosto(LASKUT *pAlku, char *pNimi) {
    FILE *Tiedosto;
    LASKUT *pLukija = pAlku;


    while (pLukija != NULL) {
        printf("%d+%d=%d\n", pLukija->iLuku, pLukija->iLisa, pLukija->iSumma);
        pLukija = pLukija->pSeuraava;
    }

    if ((Tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("\nTiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Alustetaan lukija uudestaan ja kirjoitetaan tiedot tiedostoon.
    pLukija = pAlku;
    while (pLukija != NULL) {
        fprintf(Tiedosto, "%d+%d=%d\n", pLukija->iLuku, pLukija->iLisa, pLukija->iSumma);
        pLukija = pLukija->pSeuraava;
    }
    fclose(Tiedosto);
    printf("\n");
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    return pAlku;
}

LASKUT *lueTiedosto(LASKUT *pAlku, char *pNimi) {
    FILE *Tiedosto;
    char aRivi[KOKO], *aSarake1, *aSarake2, *aSarake3;

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    printf("Tiedostossa oleva laskuhistoria:\n");
    while (fgets(aRivi, KOKO, Tiedosto) != NULL) {
        printf("%s", aRivi);

        if ((aSarake1 = strtok(aRivi, "+")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        if ((aSarake2 = strtok(NULL, "=")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        if ((aSarake3 = strtok(NULL, "\n")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
        }

        LASKUT *pUusi = NULL, *pLukija = NULL;

        // Varataan muisti tietueelle
        pUusi = varaaMuisti(pUusi);

        // Lisätään rivin tiedot tietueeseen

        pUusi->iLuku = atoi(aSarake1);
        pUusi->iLisa = atoi(aSarake2);
        pUusi->iSumma = atoi(aSarake3);
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
    printf("Tiedosto '%s' luettu ja tulostettu.\n", pNimi);
    return pAlku;
}

LASKUT *poistaViimeinen(LASKUT *pAlku, int *pSumma) {
    LASKUT *pLukija = pAlku;

    while (pLukija->pSeuraava->pSeuraava != NULL) {
        pLukija = pLukija->pSeuraava;
    }
    free(pLukija->pSeuraava);
    pLukija->pSeuraava = NULL;
    *pSumma = pLukija->iSumma;
    printf("\n");
    printf("Viimeisin laskutoimitus poistettu historiasta.\n");
    return pAlku;
}