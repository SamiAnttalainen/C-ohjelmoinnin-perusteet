// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 20.2.2023
// Tehtävä: L6T2.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KOKO 30
#define SIZE 5

typedef struct Tiedot {
    char aTunniste[SIZE];
    int iMaara;
    struct Tiedot *pSeuraava;
} TIEDOT;

void annaNimi(char *pNimi);

TIEDOT *varaaMuisti(TIEDOT *pUusi);

TIEDOT *vapautaMuisti(TIEDOT *pAlku);

TIEDOT *lueTiedosto(TIEDOT *pAlku, char *pNimi);

TIEDOT *tulostaTiedot(TIEDOT *pTiedot);

int main(void){
    char aTiedostoNimi[KOKO];
    TIEDOT *pAlku = NULL;

    annaNimi(aTiedostoNimi);
    pAlku = lueTiedosto(pAlku, aTiedostoNimi);
    pAlku = tulostaTiedot(pAlku);
    pAlku = vapautaMuisti(pAlku);
    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}

void annaNimi(char *pNimi) {
    printf("Anna luettavan tiedoston nimi: ");
    scanf("%s", pNimi);
    getchar();
    return;
}

TIEDOT *varaaMuisti(TIEDOT *pUusi) {
    if ((pUusi = (TIEDOT*)malloc(sizeof(TIEDOT))) == NULL) {
        perror("Muistin varaus epäonnistui");
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
    printf("Muisti vapautettu.\n");
    return pAlku;
}

TIEDOT *lueTiedosto(TIEDOT *pAlku, char *pNimi) {
    FILE *Tiedosto;
    TIEDOT *pUusi = NULL, *pLukija = NULL;
    char aRivi[KOKO], *aSarake1, *aSarake2;

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    // Luetaan tiedosto.
    while (fgets(aRivi, KOKO, Tiedosto) != NULL) {
        if ((aSarake1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        if ((aSarake2 =strtok(NULL, "\n")) == NULL) {
            printf("Merkkijonon '%s' pilkkominen epäonnistui.\n", aRivi);
            exit(0);
        }

        if ((pUusi = (TIEDOT*)malloc(sizeof(TIEDOT))) == NULL) {
            perror("Muistin varaus epäonnistui");
            exit(0);
        }

        // Kopioidaan merkkijonot tietueeseen.
        strcpy(pUusi->aTunniste, aSarake1);
        pUusi->iMaara = atoi(aSarake2);
        pUusi->pSeuraava = NULL;

        // Lisätään tietue listaan.
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
    printf("Tiedosto '%s' luettu linkitettyyn listaan.\n", pNimi);
    return pAlku;
}

TIEDOT *tulostaTiedot(TIEDOT *pAlku) {
    TIEDOT *pLukija = pAlku;
    printf("Tehtäviä tehtiin seuraavasti:\n");
    while (pLukija != NULL) {
        printf("Tehtävän %s teki %d opiskelijaa.\n", pLukija->aTunniste, pLukija->iMaara);
        pLukija = pLukija->pSeuraava;
    }
    printf("\n");
    return pAlku;
}

