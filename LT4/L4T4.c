// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 6.2.2023
// Tehtävä: L4T3.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RIVI 3
#define SARAKE 3
#define KOKO 60

void annaNimi(char *pNimi);

void kirjoitaMatriisit(char *pNimi);

int main(void) {
    char aKirjoita[KOKO];
    annaNimi(aKirjoita);
    kirjoitaMatriisit(aKirjoita);
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}

void annaNimi(char *pNimi) {
    //int iPituus;
    printf("Anna kirjoitettavan tiedoston nimi: ");
    scanf("%s", pNimi);
    //iPituus = strlen(pNimi);
    //pNimi[iPituus - 1] = '\0';
    return;
}

void kirjoitaMatriisit(char *pNimi) {
    int i, j;
    int Matriisi[RIVI][SARAKE];
    int Transpoosi[RIVI][SARAKE];
    FILE *Tiedosto;
    printf("Anna arvot lähtömatriisille: \n");
    for (i = 0; i < RIVI; i++) {
        for (j = 0; j < SARAKE; j++) {
            printf("Rivi %d, alkio %d: ", i+1, j+1);
            scanf("%d", &Matriisi[i][j]);
        }
    }
    if ((Tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    printf("\n");
    printf("Lähtömatriisi: \n");
    fprintf(Tiedosto, "Lähtömatriisi: \n");
    for (i = 0; i < RIVI; i++) {
        for (j = 0; j < SARAKE; j++) {
            if (j < SARAKE - 1 && j > 0) {
                printf("%5d", Matriisi[i][j]);
                fprintf(Tiedosto, "%5d", Matriisi[i][j]);
            } else if (j == 0) {
                printf("%4d", Matriisi[i][j]);
                fprintf(Tiedosto, "%4d", Matriisi[i][j]);
            } else {
                printf("%5d \n", Matriisi[i][j]);
                fprintf(Tiedosto, "%5d \n", Matriisi[i][j]);
            }
        }
    }

    for (i = 0; i < RIVI; i++) {
        for (j = 0; j < SARAKE; j++) {
            Transpoosi[j][i] = Matriisi[i][j];
        }
    }
    printf("\n");
    printf("Lähtömatriisin transpoosi: \n");
    fprintf(Tiedosto, "\nLähtömatriisin transpoosi: \n");
    for (i = 0; i < RIVI; i++) {
        for (j = 0; j < SARAKE; j++) {
            if (j < SARAKE - 1 && j > 0) {
                printf("%5d", Transpoosi[i][j]);
                fprintf(Tiedosto, "%5d", Transpoosi[i][j]);
            } else if (j == 0) {
                printf("%4d", Transpoosi[i][j]);
                fprintf(Tiedosto, "%4d", Transpoosi[i][j]);
            } else {
                printf("%5d \n", Transpoosi[i][j]);
                fprintf(Tiedosto, "%5d \n", Transpoosi[i][j]);
            }
        }
    }
    printf("\n");
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
}

// eof