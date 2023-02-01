// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 30.1.2023
// Tehtävä: L3T2.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define Koko 30

int lueTiedosto(char pNimi[Koko]);

void kirjoitaTiedosto(char *pNimi, int iSumma);

int main(void) {
    int iSumma;
    char aLuettava[Koko], aKirjoitettava[Koko];

    printf("Tämä ohjelma laskee tiedostossa olevien lukujen summan.\n");
    printf("Anna luettavan tiedoston nimi: ");
    fgets(aLuettava, Koko, stdin);
    iSumma = lueTiedosto(aLuettava);
    printf("\n");
    printf("Anna kirjoitettavan tiedoston nimi: ");
    scanf("%s", aKirjoitettava);
    kirjoitaTiedosto(aKirjoitettava, iSumma);
    printf("\n");
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}

int lueTiedosto(char pNimi[Koko]) {
    char aRivi[50];
    int iSumma = 0, iLuku;
    FILE *Tiedosto;
    pNimi[strlen(pNimi) - 1] = '\0';
    Tiedosto = fopen(pNimi, "r");
    if (Tiedosto == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    while (fgets(aRivi, 50, Tiedosto) != NULL) {
        iLuku = atoi(aRivi);
        //sscanf(aRivi, "%d", &iLuku);
        iSumma += iLuku;
    }
    fclose(Tiedosto);
    printf("Tiedosto '%s' luettu, lukujen summa oli %d.\n", pNimi, iSumma);
    return(iSumma);
}

void kirjoitaTiedosto(char *pNimi, int iSumma) {
    FILE *Tiedosto;
    if ((Tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    fprintf(Tiedosto, "Lukujen summa oli %d.\n", iSumma);
    fclose(Tiedosto);
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    return;

}