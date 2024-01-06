// Tekijä: Sami Anttalainen
// Päivämäärä: 21.2.2023
// Tehtävä: L6T4.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _XOPEN_SOURCE
#define __USE_XOPEN
#define _GNU_SOURCE
#include <time.h>
#define KOKO 30
#define LEN 12

typedef struct Tiedot {
    char aPvm[KOKO];
    float iLampo;
    struct Tiedot *pSeuraava;
} TIEDOT;

int valikko();

void annaNimi(char *pNimi, char *pSyote);

TIEDOT *varaaMuisti(TIEDOT *pUusi);

TIEDOT *vapautaMuisti(TIEDOT *pAlku);

TIEDOT *lueTiedosto(TIEDOT *pAlku);

TIEDOT *analysoiTiedot(TIEDOT *pAlku, float *pTaulu);

void *kirjoitaTiedosto(float *pTaulu);

int main(void) {
    float fTaulu[LEN];
    int iValinta, i, iLuettu = 0, iAnalysoitu = 0;
    TIEDOT *pAlku = NULL;

    for (i = 0; i < LEN; i++) {
        fTaulu[i] = 0;
    }

    do {
        iValinta = valikko();

        if (iValinta == 1) {
            pAlku = lueTiedosto(pAlku);
            iLuettu = 1;
        }
        else if (iValinta == 2) {
            if (iLuettu == 1) {
                pAlku = analysoiTiedot(pAlku, fTaulu);
                iAnalysoitu = 1;
            }
            else {
                printf("\nEi analysoitavia tietoja, lue tiedot ensin.\n");
            }
            
        }
        else if (iValinta == 3) {
            if (iAnalysoitu == 1) {
                kirjoitaTiedosto(fTaulu);
            }
            else {
                printf("\nEi kirjoitettavia tietoja, analysoi tiedot ensin.\n");
            }
        }
        else if (iValinta == 0) {
            pAlku = vapautaMuisti(pAlku);
            pAlku = NULL;
            printf("Lopetetaan.\n");
        }
        else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
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
    printf("2) Analysoi\n");
    printf("3) Kirjoita tiedosto\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return iValinta;
}

void annaNimi(char *pNimi, char *pSyote) {
    printf("\nAnna %s tiedoston nimi: ", pSyote);
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
    printf("\nMuisti vapautettu.\n");
    return pAlku;
}

TIEDOT *lueTiedosto(TIEDOT *pAlku) {
    char *aSarake1, *aSarake2, aRivi[KOKO], aSyote[] = "luettavan";
    char aLuettava[KOKO];
    annaNimi(aLuettava, aSyote);

    FILE *Tiedosto;

    if ((Tiedosto = fopen(aLuettava, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    while (fgets(aRivi, KOKO, Tiedosto) != NULL) {
        
        if ((aSarake1 = strtok(aRivi, ";")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui.", aRivi);
            exit(0);
        }

        if ((aSarake2 = strtok(NULL, "\n")) == NULL) {
            printf("Merkkijonon %s pilkkominen epäonnistui.", aRivi);
            exit(0);
        }

        TIEDOT *pUusi, *pLukija;

        //Varataan muisti
        pUusi = varaaMuisti(pUusi);

        //Lisätään tiedot tietueeseen
        strcpy(pUusi->aPvm, aSarake1);
        pUusi->iLampo = atof(aSarake2);

        //Lisätään tietue linkitettyyn listaan

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
    printf("Tiedosto '%s' luettu linkitettyyn listaan.\n", aLuettava);
    return pAlku;
}

TIEDOT *analysoiTiedot(TIEDOT *pAlku, float *pTaulu) {
    struct tm tm;
    int iKuukaudet[LEN], i;

    for (i = 0; i < LEN; i++) {
        iKuukaudet[i] = 0;
    }

    TIEDOT *pLukija = pAlku;
    while (pLukija != NULL) {
        memset(&tm, 0, sizeof(tm));
        strptime(pLukija->aPvm, "%d.%m.%Y", &tm);
        i = tm.tm_mon;
        pTaulu[i] += pLukija->iLampo;
        iKuukaudet[i] += 1;
        pLukija = pLukija->pSeuraava;
    }

    for (i = 0; i < LEN; i++) {
        if (iKuukaudet[i] != 0) {
            pTaulu[i] = pTaulu[i] / iKuukaudet[i];
        }
        else {
            pTaulu[i] = 0;
        }   
    }

    /*for (i = 0; i < LEN; i++) {
        printf("%.2f\n", pTaulu[i]);
    }*/
    printf("\nLaskettu lämpötilojen keskiarvot eri kuukausille.\n");
    return pAlku;
}

void *kirjoitaTiedosto(float *pTaulu) {
    int i;
    char aSyote[] = "kirjoitettavan", aKirjoita[KOKO];
    annaNimi(aKirjoita, aSyote);
    FILE *Tiedosto;

    printf("Kuukausi;Keskiarvo\n");
    for (i = 0; i < LEN; i++) {
        printf("KK %d;%.2f\n", i+1, pTaulu[i]);
    }

    if ((Tiedosto = fopen(aKirjoita, "w")) == NULL) {
        perror("\nTiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    fprintf(Tiedosto, "Kuukausi;Keskiarvo\n");
    for (i = 0; i < LEN; i++) {
        fprintf(Tiedosto, "KK %d;%.2f\n", i+1, pTaulu[i]);
    }
    fclose(Tiedosto);
    printf("\nTiedosto '%s' kirjoitettu.\n", aKirjoita);
    return pTaulu;
}

