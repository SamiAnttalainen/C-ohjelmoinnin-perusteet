// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 31.1.2023
// Tehtävä: L3T3.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Koko 30

int valikko(int iValinta);

int lisaaLukuun(char *pNimi, int iLuku);

void tulostaTulokset(char *pNimi);

int main(void) {
    int iLuku, iValinta;
    char aKirjoitettava[Koko];

    printf("Anna kokonaisluku: ");
    scanf("%d", &iLuku);
    printf("Anna kirjoitettavan tiedoston nimi: ");
    scanf("%s", aKirjoitettava);
    //fgets(aKirjoitettava, Koko, stdin);
    
    do {
        iValinta = valikko(iValinta);
        printf("\n");

        if (iValinta == 1) {
            iLuku = lisaaLukuun(aKirjoitettava, iLuku);
        } else if (iValinta == 2) {
            tulostaTulokset(aKirjoitettava);
        } else if (iValinta == 0) {
            printf("Lopetetaan.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
    } while (iValinta != 0);
    printf("\n");
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}

int valikko(int iValinta) {
    printf("\n");
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lisää lukuun\n");
    printf("2) Tulosta tulokset\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    return(iValinta);
}

int lisaaLukuun(char *pNimi, int iLuku) {
    int iLuku2, iTulos;
    printf("Anna lukuun lisättävä kokonaisluku: ");
    scanf("%d", &iLuku2);
    iTulos = iLuku + iLuku2;
    printf("%d+%d=%d\n", iLuku, iLuku2, iTulos);
    FILE *Tiedosto;
    if ((Tiedosto = fopen(pNimi, "a")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    fprintf(Tiedosto, "%d+%d=%d\n", iLuku, iLuku2, iTulos);
    fclose(Tiedosto);
    return(iTulos);
}

void tulostaTulokset(char *pNimi) {
    char aRivi[50];
    FILE *Tiedosto;
    Tiedosto = fopen(pNimi, "r");
    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    printf("Tiedostossa oleva laskuhistoria:\n");
    while (fgets(aRivi, 50, Tiedosto) != NULL) {
        printf("%s", aRivi);
    }
    fclose(Tiedosto);
    printf("Tiedosto '%s' luettu ja tulostettu.\n", pNimi);
}

// eof