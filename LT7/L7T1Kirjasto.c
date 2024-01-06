// Tekijä: Sami Anttalainen
// Päivämäärä: 27.2.2023
// Tehtävä: L7T1
// Tiedosto: L7T1Kirjasto.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "L7T1Kirjasto.h"
#define KOKO 10
#define LEN 30

void annaTiedostoNimi(char *pNimi) {
    printf("Anna luettavan tiedoston nimi: ");
    scanf("%s", pNimi);
    getchar();
    return;
}

void lueTiedosto(TIEDOT *pTiedot, int *pSumma, char *pNimi) {
    int i = 0, iSumma = 0;
    char aRivi[LEN], *aSarake1, *aSarake2;
    FILE *Tiedosto;

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    // Ohitetaan otsikkorivi
    fgets(aRivi, LEN, Tiedosto);

    // Luetaan tiedosto ja pilkotaan rivit
    while (fgets(aRivi, LEN, Tiedosto) != NULL) {
        
        if ((aSarake1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        if ((aSarake2 = strtok(NULL, "\n")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }


        // Tallennetaan tiedot tietueeseen ja lasketaan kokonaissumma
        pTiedot[i].iVuosi = atoi(aSarake1);
        pTiedot[i].iLkm = atoi(aSarake2);
        iSumma += atoi(aSarake2);
        i++;
    }
    fclose(Tiedosto);
    *pSumma = iSumma;
    printf("Tiedosto '%s' luettu.\n", pNimi);
    return;
}


void tulostaTiedot(TIEDOT *pTiedot, int iSumma) {
    int i;
    printf("Akvaariokalojen tuonti euroina:\n");
    for (i = 0; i < KOKO; i++) {
        printf("%d\t%d\n", pTiedot[i].iVuosi, pTiedot[i].iLkm);
    }
    printf("Ajanjaksolla tuonti oli yhteensä %d euroa.\n", iSumma);
    return;
}
