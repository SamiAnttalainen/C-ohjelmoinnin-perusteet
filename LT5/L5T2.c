// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 13.2.2023
// Tehtävä: L5T1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KOKO 30

void annaTiedostoNimi(char *pNimi);

void analysoiTiedot(char *pNimi);

int main(void) {
    char aTiedosto[KOKO];
    annaTiedostoNimi(aTiedosto);
    analysoiTiedot(aTiedosto);
    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}

void annaTiedostoNimi(char *pNimi) {
    printf("Anna luettavan tiedoston nimi: ");
    scanf("%s", pNimi);
    getchar();
    return;
}

void analysoiTiedot(char *pNimi) {
    char *aSarake1, *aSarake2, aRivi[KOKO], aJoukkue[KOKO];
    char *aPienin;
    int iPienin, iLuku;
    FILE *Tiedosto;

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    fgets(aRivi, KOKO, Tiedosto);
    if ((aSarake1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
    }
    if ((aSarake2 = strtok(NULL, "\n")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
    }

    iPienin = atoi(aSarake2);
    aPienin = aSarake1;
 
    while (fgets(aRivi, KOKO, Tiedosto) != NULL) {
        if ((aSarake1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }
        if ((aSarake2 = strtok(NULL, "\n")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        iLuku = atoi(aSarake2);

        if (iLuku < iPienin) {
            iPienin = iLuku;
            strcpy(aJoukkue, aSarake1);
        }
    }
    fclose(Tiedosto);
    printf("Tiedosto '%s' luettu.\n", pNimi);
    printf("Pienin pistemäärä oli joukkueella '%s' %d pisteellä.\n", aJoukkue, iPienin);
    return;
}