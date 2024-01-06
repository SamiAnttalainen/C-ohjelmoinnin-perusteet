// Tekijä: Sami Anttalainen
// Päivämäärä: 7.2.2023
// Tehtävä: L4T3.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KOKO 30

typedef struct laskut {
    int iSumma, iLuku, iLisatty, iSyote;
    char Laskutoimitus[KOKO];
} LASKUT;

int valikko(int iValinta);

int lisaaLukuun(LASKUT *aLaskut, int iTulos, int Indeksi);

void kirjoitaTiedosto(char *pTiedosto, LASKUT *aLaskut, int iIndeksi);

void lueTiedosto(char *pTiedosto);


int main(void) {
    LASKUT aLaskut[KOKO];
    char aKirjoita[KOKO];
    int iValinta, iIndeksi = 0, iTulos;
    printf("Anna kokonaisluku: ");
    scanf("%d", &iTulos);
    printf("Anna kirjoitettavan tiedoston nimi: ");
    scanf("%s", aKirjoita);

    do {
        printf("\n");
        iValinta = valikko(iValinta);

        if (iValinta == 1) {
            iTulos = lisaaLukuun(aLaskut, iTulos, iIndeksi);
            iIndeksi++;
        } else if (iValinta == 2) {
            kirjoitaTiedosto(aKirjoita, aLaskut, iIndeksi);
        } else if (iValinta == 3) {
            lueTiedosto(aKirjoita);
        } else if (iValinta == 0) {
            printf("\n");
            printf("Lopetetaan.\n");
        } else {
            printf("\nTuntematon valinta, yritä uudestaan.\n");
        }
    } while (iValinta != 0);
    printf("\n");
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}

int valikko(int iValinta) {
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lisää lukuun\n");
    printf("2) Kirjoita historia tiedostoon\n");
    printf("3) Lue historia tiedostosta\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    return(iValinta);
}

 int lisaaLukuun(LASKUT *aLaskut, int iTulos, int iIndeksi) {
    int iLisatty, iSumma;
    printf("\n");
    printf("Anna lukuun lisättävä kokonaisluku: ");
    scanf("%d", &iLisatty);
    iSumma = iTulos + iLisatty;
    printf("%d+%d=%d\n", iTulos, iLisatty, iSumma);
    aLaskut[iIndeksi].iLuku = iTulos;
    aLaskut[iIndeksi].iLisatty = iLisatty;
    aLaskut[iIndeksi].iSumma = iSumma;
    return iSumma;
}

void kirjoitaTiedosto(char *pTiedosto, LASKUT *aLaskut, int iIndeksi) {
    int i;
    FILE *Tiedosto;

    if ((Tiedosto = fopen(pTiedosto, "a")) == NULL) {
        perror("\nTiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    for (i = 0; i < iIndeksi; i++) {
        fprintf(Tiedosto, "%d+%d=%d\n", aLaskut[i].iLuku, aLaskut[i].iLisatty, aLaskut[i].iSumma);
    }
    fclose(Tiedosto);
    printf("\n");
    printf("Tiedosto '%s' kirjoitettu.\n", pTiedosto);
    return;
}

void lueTiedosto(char *pTiedosto) {
    char aRivi[KOKO];
    FILE *Tiedosto;
    if ((Tiedosto = fopen(pTiedosto, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    printf("\n");
    printf("Tiedostossa oleva laskuhistoria:\n");
    while (fgets(aRivi, KOKO, Tiedosto) != NULL) {
        printf("%s", aRivi);
    }
    fclose(Tiedosto);
    printf("Tiedosto '%s' luettu ja tulostettu.\n", pTiedosto);
    return;
}
// eof
