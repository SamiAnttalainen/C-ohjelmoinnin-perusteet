// Tekijä: Sami Anttalainen
// Päivämäärä: 14.2.2023
// Tehtävä: L5T4.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KOKO 30

typedef struct Summat {
    char aMerkkijono[30];
    int iSumma, iIndex;

} TIEDOT;

int valikko();

void annaTiedostonNimi(char *pNimi, char *pSyote);

TIEDOT *lueTiedosto(TIEDOT *pTiedot, char *pNimi);

TIEDOT *varaaMuisti(TIEDOT *pOsoitin, int iIndex);

int laskeSumma(char *aMerkkijono, int iPituus);

void tulostaTiedot(char *pNimi, TIEDOT *aTiedot);

int main(void) {
    TIEDOT *pTiedot = NULL;
    char aSyote1[] = "luettavan", aSyote2[] = "kirjoitettavan";
    int iValinta, iLuettu = 0, iLaskettu = 0, iSumma, i, iPituus;
    char aLuettava[KOKO], aKirjoitettava[KOKO];
    do {
        iValinta = valikko();

        if (iValinta == 1) {
            annaTiedostonNimi(aLuettava, aSyote1);
            pTiedot = lueTiedosto(pTiedot, aLuettava);
            iLuettu = 1;
        }
        else if (iValinta == 2) {
            if (iLuettu == 1) {
                for (i = 0; i < pTiedot[0].iIndex; i++) {
                    iPituus = strlen(pTiedot[i].aMerkkijono);
                    iSumma = laskeSumma(pTiedot[i].aMerkkijono, iPituus);
                    pTiedot[i].iSumma = iSumma;
                }
                printf("\nSummat laskettu %d merkkijonolle.\n", pTiedot[0].iIndex);
                iLaskettu = 1;
            }
            else {
                printf("\nEi analysoitavaa, lue tiedosto ennen analyysia.\n");
            }
        }
        else if (iValinta == 3) {
            if (iLaskettu == 1) {
                annaTiedostonNimi(aKirjoitettava, aSyote2);
                tulostaTiedot(aKirjoitettava, pTiedot);
            }
            else {
                printf("\nEi kirjoitettavia tietoja, analysoi tiedot ennen tallennusta.\n");
            }
        
        }
        else if (iValinta == 0) {
            free(pTiedot);
            pTiedot = NULL;
            printf("\nMuisti vapautettu.\n");
            printf("Lopetetaan.\n");
        }
        printf("\n");
    } while (iValinta != 0);

    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}

int valikko() {
    int iValinta;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Laske merkkijonojen summa\n");
    printf("3) Kirjoita tiedosto\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    return iValinta;
}

void annaTiedostonNimi(char *pNimi, char *pSyote) {
    printf("\nAnna %s tiedoston nimi: ", pSyote);
    scanf("%s", pNimi);
    getchar();
    return;
}

TIEDOT *lueTiedosto(TIEDOT *pTiedot, char *pNimi) {
    int iIndex = 0, iSumma, iPituus;
    char aRivi[KOKO];

    FILE *Tiedosto;

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    while (fgets(aRivi, KOKO, Tiedosto) != NULL) {
        iIndex++;
        pTiedot = varaaMuisti(pTiedot, iIndex);
        aRivi[strlen(aRivi)-1] = '\0';
        iPituus = strlen(aRivi);
        strcpy(pTiedot[iIndex-1].aMerkkijono, aRivi);
        //printf("%s;%d\n", pTiedot[iIndex-1].aMerkkijono, pTiedot[iIndex-1].iSumma);
    }
    fclose(Tiedosto);
    pTiedot[0].iIndex = iIndex;
    printf("Tiedosto '%s' luettu.\n", pNimi);
    return pTiedot;
}

TIEDOT *varaaMuisti(TIEDOT *pOsoitin, int iIndex) {
    if ((pOsoitin = (TIEDOT*)realloc(pOsoitin, iIndex * sizeof(TIEDOT))) == NULL) {
        perror("Muistin varaus epäonnistui.");
        exit(0);
    }
    return pOsoitin;
}

int laskeSumma(char *pMerkkijono, int iPituus) {
    int i, iSumma = 0, iLuku;

    for (i = 0; i < iPituus; i++) {
        iLuku = pMerkkijono[i];
        iSumma += iLuku;
    }
    return iSumma;
}

void tulostaTiedot(char *pNimi, TIEDOT *pTiedot) {
    int i;
    FILE *Tiedosto;
    if ((Tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    printf("Tiedostoon kirjoitetaan seuraavat arvot:\n");
    printf("Nimi;Arvo\n");
    fprintf(Tiedosto, "Nimi;Arvo\n");
    for (i = 0; i < pTiedot[0].iIndex; i++) {
        printf("%s;%d\n", pTiedot[i].aMerkkijono, pTiedot[i].iSumma);
        fprintf(Tiedosto, "%s;%d\n", pTiedot[i].aMerkkijono, pTiedot[i].iSumma);
    }
    fclose(Tiedosto);
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    return;
}
