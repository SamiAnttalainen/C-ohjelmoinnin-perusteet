// Tekijä: Sami Anttalainen
// Päivämäärä: 30.1.2023
// Tehtävä: L3T4.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void asetaSeed();

int kysyMaara();

char *arvoMerkkijono(int iMaara, char *cMerkkijono1);

void tarkistaMerkkijono(char *Merkkijono);

int main(void) {
    char *cMerkkijono, cMerkkijono1[30];
    int iMaara;
    printf("Tämä ohjelma luo satunnaisia merkkijonoja.\n");
    asetaSeed();
    iMaara = kysyMaara();
    printf("\n");
    cMerkkijono = arvoMerkkijono(iMaara, cMerkkijono1);
    tarkistaMerkkijono(cMerkkijono);
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}

void asetaSeed() {
    int iSiemen;
    printf("Anna satunnaisgeneraattorin siemenluku: ");
    scanf("%d", &iSiemen);
    srand(iSiemen);
    return;
}

int kysyMaara() {
    int iMaara;
    printf("Anna arvottavien merkkien määrä: ");
    scanf("%d", &iMaara);
    return iMaara;
}

char *arvoMerkkijono(int iMaara, char *cMerkkijono1) {
    int i = 0, j = 0, iLuku;
    char cMerkki;
    while (i < iMaara) {
        iLuku = (rand() % 95) + 32;
        cMerkki = iLuku;
        if (isalnum(cMerkki) || isspace(cMerkki)) {
            cMerkkijono1[j] = cMerkki;
            j++;
        }
        i++;
    }
    cMerkkijono1[j] = '\0';
    return cMerkkijono1;
}

void tarkistaMerkkijono(char *Merkkijono) {
    int iPituus;  //, i = 0, j = 0;
    iPituus = strlen(Merkkijono);
    char cMerkki = 'c';
    
    if (memchr(Merkkijono, cMerkki, iPituus) == NULL) {
        printf("Merkkijonossa ei ollut merkkiä 'c'.\n");
    } else {
        printf("Merkkijonosta löydettiin merkki 'c'.\n");
    }
   printf("Generoitiin merkkijono '%s', jossa on %d merkkiä.\n", Merkkijono, iPituus);
}

// eof
