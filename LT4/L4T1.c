// Tekijä: Sami Anttalainen
// Päivämäärä: 6.2.2023
// Tehtävä: L4T1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PITUUS 50
#define LKM 4

typedef struct tiedot {
    char aKappale[PITUUS], aEsittaja[PITUUS], aKesto[PITUUS];
    int iVuosi;
} TIEDOT;

int main(void) {
    int iPituus;

    TIEDOT aTiedot;

    printf("Anna kappaleen nimi: ");
    fgets(aTiedot.aKappale, PITUUS, stdin);
    iPituus = strlen(aTiedot.aKappale);
    aTiedot.aKappale[iPituus-1] = '\0';
    printf("Anna kappaleen esittäjä: ");
    fgets(aTiedot.aEsittaja, PITUUS, stdin);
    iPituus = strlen(aTiedot.aEsittaja);
    aTiedot.aEsittaja[iPituus-1] = '\0';
    printf("Anna kappaleen pituus: ");
    fgets(aTiedot.aKesto, PITUUS, stdin);
    iPituus = strlen(aTiedot.aKesto);
    aTiedot.aKesto[iPituus-1] = '\0';
    printf("Anna kappaleen julkaisuvuosi: ");
    scanf("%d", &aTiedot.iVuosi);

    printf("Kappaleen nimi on '%s' ja esittäjä '%s'.\n", aTiedot.aKappale, aTiedot.aEsittaja);
    printf("Kappale on %s minuuttia pitkä ja julkaistu vuonna %d.\n", aTiedot.aKesto, aTiedot.iVuosi);
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}

// eof
