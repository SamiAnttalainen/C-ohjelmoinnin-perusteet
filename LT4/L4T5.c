// Tekijä: Sami Anttalainen
// Opiskelijanumero: 001067291
// Päivämäärä: 7.2.2023
// Tehtävä: L4T5.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valikko(int iValinta);

int tulostaEtuperin(char *pMerkkijono, int iPituus, int iAloitus);

int tulostaTakaperin(char *pMerkkijono, int iPituus, int iAloitus);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Et antanut tarpeeksi parametreja.\n");
    } else if (argc > 2) {
        printf("Annoit liikaa parametreja.\n");
    } else {
    int iValinta, iPituus, iAloitus = 0;
    iPituus = strlen(argv[1]);

    do {
        iValinta = valikko(iValinta);

        if (iValinta == 1) {
            tulostaEtuperin(argv[1], iPituus, iAloitus);
        } else if (iValinta == 2) {
            tulostaTakaperin(argv[1], iPituus, iAloitus);
        } else if (iValinta == 0) {
            printf("Lopetetaan.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");

    } while (iValinta != 0);

    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
    }
}

int valikko(int iValinta) {
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Tulosta merkkijono\n");
    printf("2) Tulosta merkkijono takaperin\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    return iValinta;
}

int tulostaEtuperin(char *pMerkkijono, int iPituus, int iAloitus) {

    if (iAloitus == iPituus) {
        return(1);
    } else {
        printf("%c\n", pMerkkijono[iAloitus]);
        return tulostaEtuperin(pMerkkijono, iPituus, iAloitus + 1);
    }
}

int tulostaTakaperin(char *pMerkkijono, int iPituus, int iAloitus) {
    
    if (iAloitus == iPituus) {
        return(1);
    } else {
        printf("%c\n", pMerkkijono[iPituus-1]);
        return tulostaTakaperin(pMerkkijono, iPituus - 1, iAloitus);
    }
}

// eof