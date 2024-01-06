// Tekijä: Sami Anttalainen
// Päivämäärä: 20.2.2023
// Tehtävä: L6T3.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KOKO 30

typedef struct Laskut {
    int iluku, iLisa, iSumma;
    struct Laskut *pSeuraava;
} LASKUT;

int valikko();

void annaNimi(char *pNimi, char *pSyote);

LASKUT *lisaaLukuun(LASKUT *pAlku, int iTulos, int *pTulos);

LASKUT *kirjoitaTiedosto(LASKUT *pAlku);

LASKUT *lueTiedosto(LASKUT *pAlku);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Et antanut tarpeeksi parametreja.\n");
        exit(0);
    }

    if (argc > 2) {
        printf("Annoit liikaa parametreja.\n");
        exit(0);
    }

    int iTulos = atoi(argv[1]), iValinta, iTiedot = 0;
    //int *pTulos = &iTulos;
    LASKUT *pAlku = NULL, *pLukija = NULL;

    printf("Annoit luvun %d.\n", iTulos);

    do {
        iValinta = valikko();

        if (iValinta == 1) {
            pAlku = lisaaLukuun(pAlku, iTulos, &iTulos);
            iTiedot = 1;
        }
        else if (iValinta == 2) {
            if (iTiedot == 1) {
                pAlku = kirjoitaTiedosto(pAlku);
            }
             else {
                printf("\nEi kirjoitettavia tietoja.\n");
             }
        }
        else if  (iValinta == 3) {
            pAlku = lueTiedosto(pAlku);
            iTiedot = 1;
        }
        else if (iValinta == 0) {
            pLukija = pAlku;
            while (pLukija != NULL) {
                pAlku = pLukija->pSeuraava;
                free(pLukija);
                pLukija = pAlku;
            }
            pLukija = NULL;
            pAlku = NULL;
            printf("\nMuisti vapautettu.\n");
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
    printf("1) Lisää lukuun\n");
    printf("2) Kirjoita historia tiedostoon\n");
    printf("3) Lue historia tiedostosta\n");
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

LASKUT *lisaaLukuun(LASKUT *pAlku, int iTulos, int *pTulos) {
    int iLisa, iSumma;
    printf("\nAnna lukuun lisättävä kokonaisluku: ");
    scanf("%d", &iLisa);
    iSumma = iTulos + iLisa;
    printf("%d+%d=%d\n", iTulos, iLisa, iSumma);

    LASKUT *pUusi = NULL, *pLukija = NULL;

    // Varataan muisti tietueelle
    if ((pUusi = (LASKUT*)malloc(sizeof(LASKUT))) == NULL) {
        perror("Muistin varaaminen epäonnistui");
        exit(0);
    }

    // Asetetaan arvot tietueeseen
    pUusi->iluku = iTulos;
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

    // Tallennetaan summa tulosmuuttujaan.
    *pTulos = iSumma;
    return pAlku;
}


LASKUT *kirjoitaTiedosto(LASKUT *pAlku) {
    char aSyote[] = "kirjoitettavan", aKirjoita[KOKO];
    annaNimi(aKirjoita, aSyote);

    FILE *Tiedosto;

    LASKUT *pLukija = pAlku;
    while (pLukija != NULL) {
        printf("%d+%d=%d\n", pLukija->iluku, pLukija->iLisa, pLukija->iSumma);
        pLukija = pLukija->pSeuraava;
    }

    if ((Tiedosto = fopen(aKirjoita, "w")) == NULL) {
        perror("\nTiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    pLukija = pAlku;
    while (pLukija != NULL) {
        fprintf(Tiedosto, "%d+%d=%d\n", pLukija->iluku, pLukija->iLisa, pLukija->iSumma);
        pLukija = pLukija->pSeuraava;
    }
    fclose(Tiedosto);
    printf("\nTiedosto '%s' kirjoitettu.\n", aKirjoita);
    return pAlku;
}

LASKUT *lueTiedosto(LASKUT *pAlku) {
    char aSyote[] = "luettavan", aRivi[KOKO], *aSarake1, *aSarake2, *aSarake3;
    char aLuettava[KOKO];
    LASKUT *pUusi = NULL, *pLukija = NULL;
    FILE *Tiedosto;
    annaNimi(aLuettava, aSyote);
    if ((Tiedosto = fopen(aLuettava, "r")) == NULL) {
        
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    printf("Tiedostossa oleva laskuhistoria:\n");
    // Luetaan tiedosto
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
            exit(0);
        }
        // Varataan tietueelle muistia
        if ((pUusi = (LASKUT*)malloc(sizeof(LASKUT))) == NULL) {
            perror("Muistin varaaminen epäonnistui");
            exit(0);
        }

        //Lisätään rivin arvot tietueeseen.
        pUusi->iluku = atoi(aSarake1);
        pUusi->iLisa = atoi(aSarake2);
        pUusi->iSumma = atoi(aSarake3);
        pUusi->pSeuraava = NULL;

        // Lisätään tietue listaan
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
    printf("Tiedosto '%s' luettu ja tulostettu.\n", aLuettava);
    return pAlku;
}
