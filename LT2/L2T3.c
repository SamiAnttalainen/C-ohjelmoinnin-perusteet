// Tekijä: Sami Anttalainen
// Tehtävä L2T3
// Ohjelma alkaa
#include <stdio.h>
#include <string.h>

int main(void) {

    char cMerkki;
    char cMerkkijono[15];
    int iSumma, i = 0, iPituus;


    printf("Anna merkki: ");
    scanf("%c", &cMerkki);
    printf("Merkki '%c' on ASCII-taulukon mukaan lukuna %d.\n", cMerkki, cMerkki);

    printf("Anna merkkijono: ");
    scanf("%s", cMerkkijono);
    iPituus = strlen(cMerkkijono); // Merkkijonon pituus, eli kesto for loopin kesto.

    while (i < iPituus) {
        iSumma += cMerkkijono[i];
        i++;
    }
    printf("Merkkijonon '%s' merkkien summa on %d.\n", cMerkkijono, iSumma);
    return(0);
}

// Ohjelma päättyy