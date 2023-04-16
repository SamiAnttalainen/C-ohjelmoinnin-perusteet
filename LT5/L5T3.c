// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 14.2.2023
// Tehtävä: L5T3.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KOKO 30


typedef struct Tiedot {
    int iLuku, iLisa, iSumma;
    char aLasku[KOKO];
} LASKUT;

int valikko();

char* varaaMuisti(char *pTaulukko);

void annaNimi(char *pNimi);

LASKUT *lisaaLukuun(LASKUT *pLaskut, int iIndex, int iTulos);

void kirjoitaTiedosto(LASKUT *aLaskut, int iIndex, char *pNimi);

void lueTiedosto(char *pNimi);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Et antanut tarpeeksi parametreja.\n");
    }
    
    else if (argc > 2) {
        printf("Annoit liikaa parametreja.\n");
    }

    else {
        int iIndex=0, iValinta, iTulos = atoi(argv[1]), iLuettu = 0, iKirjoitettu = 0;
        LASKUT *pLaskut = NULL;
        char *pTiedostoNimi = NULL;
        if ((pLaskut = (LASKUT*)malloc(KOKO * sizeof(LASKUT))) == NULL) {
        perror("Muistin varaus epäonnistui");
        exit(0);
    }
        printf("Annoit luvun %d.\n", iTulos);

        do {
            iValinta = valikko();

            if (iValinta == 1) {
                pTiedostoNimi = varaaMuisti(pTiedostoNimi);
                annaNimi(pTiedostoNimi);
                iLuettu = 1;
            }
            else if (iValinta == 2) {
                pLaskut = lisaaLukuun(pLaskut, iIndex, iTulos);
                iTulos = pLaskut[iIndex].iSumma;
                iIndex++;
                iKirjoitettu = 1;
            }
            else if (iValinta == 3) {
                if (iLuettu == 1 && iKirjoitettu == 1) {
                    kirjoitaTiedosto(pLaskut, iIndex, pTiedostoNimi);
                } else if (iKirjoitettu == 0 && iLuettu == 0) {
                    printf("\nEi kirjoitettavia tietoja.\n");
                }
                else {
                    printf("\nEi tiedoston nimeä, anna kirjoitettavan tiedoston nimi ensin.\n");
                }
            }
            else if (iValinta == 4) {

                if (iLuettu == 1 && iKirjoitettu == 1) {
                    lueTiedosto(pTiedostoNimi);
                } else if (iKirjoitettu == 1) {
                    printf("\nEi tiedoston nimeä, anna kirjoitettavan tiedoston nimi ensin.\n");
                }
                else {
                    printf("\nEi tiedoston nimeä, anna luettavan tiedoston nimi ensin.\n");
                }
            }
            else if (iValinta == 0) {
                free(pLaskut);
                pLaskut = NULL;
                free(pTiedostoNimi);
                pTiedostoNimi = NULL;
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
}

int valikko() {
    int iValinta;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Anna tiedoston nimi\n");
    printf("2) Lisää lukuun\n");
    printf("3) Kirjoita historia tiedostoon\n");
    printf("4) Lue historia tiedostosta\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    return iValinta;
}

char* varaaMuisti(char *pTaulukko) {
    if ((pTaulukko = (char *)malloc(KOKO * sizeof(char))) == NULL) {
        perror("Muistin varaus epäonnistui");
        exit(0);
    }
    return pTaulukko;
}

void annaNimi(char *pNimi) {
    printf("\nAnna kirjoitettavan tiedoston nimi: ");
    scanf("%s", pNimi);
    getchar();
    return;
}

LASKUT *lisaaLukuun(LASKUT *pLaskut, int iIndex, int iTulos) {
    int iLisa, iSumma;
    printf("\nAnna lukuun lisättävä kokonaisluku: ");
    scanf("%d", &iLisa);
    iSumma = iTulos + iLisa;
    printf("%d+%d=%d\n", iTulos, iLisa, iSumma);
    pLaskut[iIndex].iLuku = iTulos;
    pLaskut[iIndex].iLisa = iLisa;
    pLaskut[iIndex].iSumma = iSumma;
    return pLaskut;
}

void kirjoitaTiedosto(LASKUT *pLaskut, int iIndex, char *pNimi) {
    FILE *Tiedosto;
    int i;
    printf("\n");
    for (i = 0; i < iIndex; i++) {
        printf("%d+%d=%d\n", pLaskut[i].iLuku, pLaskut[i].iLisa, pLaskut[i].iSumma);
    }

    if ((Tiedosto = fopen(pNimi, "a")) == NULL) {
        perror("\nTiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    printf("\n");
    for (i = 0; i < iIndex; i++) {
        fprintf(Tiedosto, "%d+%d=%d\n", pLaskut[i].iLuku, pLaskut[i].iLisa, pLaskut[i].iSumma);
        
    }
    fclose(Tiedosto);
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    return;
}

void lueTiedosto(char *pNimi) {
    char aRivi[KOKO];
    FILE *Tiedosto;
    printf("\nTiedostossa oleva laskuhistoria:\n");

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    while (fgets(aRivi, KOKO, Tiedosto) != NULL) {
        printf("%s", aRivi);
    }
    fclose(Tiedosto);
    printf("Tiedosto '%s' luettu ja tulostettu.\n", pNimi);
    return;
}