// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 20.2.2023
// Tehtävä: L6T1.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KOKO 30


typedef struct Kirjaimet {
    char cKirjain[1];
    struct Kirjaimet *pSeuraava;
} KIRJAIMET;


int main(void) {
    KIRJAIMET *pAlku = NULL, *pLoppu = NULL;
    KIRJAIMET *pUusi, *pNext;
    char *pMerkki;
    if ((pMerkki = (char *)malloc(sizeof(char) * KOKO)) == NULL) {
        perror("Muistin varaus epäonnistui");
        exit(0);
    }
    int iLuku = 0;
    printf("Anna listan kirjaimet.\n");

    while (iLuku != 1) {
        printf("Anna kirjain, q lopettaa: ");
        scanf("%c", pMerkki);
        getchar();

        if (strchr(pMerkki, 'q') != NULL) {
            break;;
        }

        if ((pUusi = (KIRJAIMET*)malloc(sizeof(KIRJAIMET))) == NULL) {
            perror("Muistin varaus epäonnistui");
            exit(0);
        }

        strcpy(pUusi->cKirjain, pMerkki);
        pUusi->pSeuraava = NULL;

        if (pAlku == NULL) {
            pAlku = pUusi;
            pLoppu = pUusi;
        }
        else {
            pLoppu->pSeuraava = pUusi;
            pLoppu = pUusi;
        }
    }

    printf("Listassa on seuraavat kirjaimet:\n");

    pNext = pAlku;
    while (pNext != NULL) {
        printf("%s ", pNext->cKirjain);
        pNext = pNext->pSeuraava;
    }
    printf("\n");

    pNext = pAlku;
    while (pNext != NULL) {
        pAlku = pNext->pSeuraava;
        free(pNext);
        pNext = pAlku;
    }
    free(pMerkki);
    printf("\nMuisti vapautettu.\n");
    printf("Kiitos ohjelman käytöstä.\n");
    return 0;
}